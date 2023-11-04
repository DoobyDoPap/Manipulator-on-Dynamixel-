#include "motor_setup/position_control.hpp"

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>

#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_inf/srv/get_position.hpp"
#include "dynamixel_sdk_inf/msg/set_position.hpp" 

#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

namespace motor_setup
{

// Create a SetupDynamixel "component" that subclasses the generic rclcpp::Node base class.
// Components get built into shared libraries and as such do not write their own main functions.
// The process using the component's shared library will instantiate the class as a ROS node.
PositionControl::PositionControl(const rclcpp::NodeOptions & options)
: Node("position_control_node", options)
{
  RCLCPP_INFO(this->get_logger(), "Run setup dynamixel node");

  this->declare_parameter<int8_t>("qos_depth", 10);
  int8_t qos_depth = 0;
  this->get_parameter("qos_depth", qos_depth);

  this->declare_parameter<std::string>("device_name", "/dev/ttyUSB0");
  this->declare_parameter<int>("addr_present_position", 36);
  this->declare_parameter<int>("addr_goal_position", 30);
  this->declare_parameter<float>("protocol_version", 1.0);
  this->declare_parameter<int>("baudrate", 1000000);
  this->get_parameter("baudrate", baudrate);
  this->get_parameter("addr_goal_position", addr_goal_position);
  this->get_parameter("addr_present_position", addr_present_position);
  this->get_parameter("protocol_version", protocol_version);
  this->get_parameter("device_name", device_name);

  portHandler = dynamixel::PortHandler::getPortHandler(device_name.c_str());
  packetHandler = dynamixel::PacketHandler::getPacketHandler(protocol_version);

  const auto QOS_RKL10V =
    rclcpp::QoS(rclcpp::KeepLast(qos_depth)).reliable().durability_volatile();

  dxl_comm_result = portHandler->openPort();
  if (dxl_comm_result == false) {
    RCLCPP_ERROR(rclcpp::get_logger("setup_dynamixel_node"), "Failed to open the port!");
    rclcpp::shutdown();
    // return -1;
  } else {
    RCLCPP_INFO(rclcpp::get_logger("setup_dynamixel_node"), "Succeeded to open the port.");
  }

  // Set the baudrate of the serial port (use DYNAMIXEL Baudrate)
  dxl_comm_result = portHandler->setBaudRate(baudrate);
  if (dxl_comm_result == false) {
    RCLCPP_ERROR(rclcpp::get_logger("setup_dynamixel_node"), "Failed to set the baudrate!");
    rclcpp::shutdown();
  } else {
    RCLCPP_INFO(rclcpp::get_logger("setup_dynamixel_node"), "Succeeded to set the baudrate.");
  }

  auto set_motor_id =
    [this](  
      
    const std::shared_ptr<SetId::Request> request,
    std::shared_ptr<SetId::Response> response) -> void
    {
        response->set = true;
        for (uint8_t m_id : request->motor_ids) {
            dxl_comm_result = packetHandler->write1ByteTxRx(
                portHandler,
                m_id,
                addr_torque_enable,
                1,
                &dxl_error
            );
            // std::cout << (int)m_id << std::endl;
            if (dxl_comm_result != COMM_SUCCESS) {
                RCLCPP_ERROR(rclcpp::get_logger("setup_dynamixel_node"), "Failed to enable torque for id %d", (int)m_id);
                response->set = false;
            } else {
                RCLCPP_INFO(rclcpp::get_logger("setup_dynamixel_node"), "Succeeded to enable torque for id %d", (int)m_id);
                // response->set = true;
            }
        }
    };

  set_id_server_ = create_service<SetId>("set_id", set_motor_id);

  auto get_present_position =
    [this](
    const std::shared_ptr<GetPosition::Request> request,
    std::shared_ptr<GetPosition::Response> response) -> void
    {
      // Read Present Position (length : 4 bytes) and Convert uint32 -> int32
      // When reading 2 byte data from AX / MX(1.0), use read2ByteTxRx() instead.
      dxl_comm_result = packetHandler->read4ByteTxRx(
        portHandler,
        (uint8_t) request->id,
        addr_present_position,
        reinterpret_cast<uint32_t *>(&present_position),
        &dxl_error
      );

      RCLCPP_INFO(
        this->get_logger(),
        "Get [ID: %d] [Present Position: %d]",
        request->id,
        present_position
      );

      // if ((present_position - this->goal_position) > 20) {
      //   RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Difference is : %d", present_position - this->goal_position);
      // }

      response->position = present_position;
    };

    set_position_subscriber_ =
      this->create_subscription<SetPosition>(
      "set_position",
      QOS_RKL10V,
      [this](const SetPosition::SharedPtr msg) -> void
      { 
        uint8_t dxl_error = 0;

        // Position Value of X series is 4 byte data.
        // For AX & MX(1.0) use 2 byte data(uint16_t) for the Position Value.
        int goal_position[sizeof(msg->position)];
        for(int i=0;i<=sizeof(msg->position);i++){  
          
          goal_position[i] = (int)msg->position[i];   
            // Convert int32 -> uint32
      
          // Write Goal Position (length : 4 bytes)
          // When writing 2 byte data to AX / MX(1.0), use write2ByteTxRx() instead.
          dxl_comm_result =
          packetHandler->write4ByteTxRx(
          portHandler,
          (uint8_t) msg->id[i],
          addr_goal_position,
          goal_position[i],
          &dxl_error
        );

        if (dxl_comm_result != COMM_SUCCESS) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getRxPacketError(dxl_error));
        } else {
          RCLCPP_INFO(this->get_logger(), "Set [ID: %d] [Goal Position: %d]", msg->id, msg->position);
        }
      } 
      } 
    );

  get_position_server_ = create_service<GetPosition>("get_position", get_present_position);

}

PositionControl::~PositionControl()
{
}


}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(motor_setup::PositionControl)
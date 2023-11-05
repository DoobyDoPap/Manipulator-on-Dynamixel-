#include "motor_setup/pos_torque_control.hpp"

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>

#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_inf/srv/get_position.hpp"
#include "dynamixel_sdk_inf/msg/set_position.hpp"
#include "dynamixel_sdk_inf/srv/set_id.hpp"
#include "rcutils/cmdline_parser.h"
#include "rclcpp/rclcpp.hpp"

namespace motor_setup
{

// Create a SetupDynamixel "component" that subclasses the generic rclcpp::Node base class.
// Components get built into shared libraries and as such do not write their own main functions.
// The process using the component's shared library will instantiate the class as a ROS node.
PosTorqueControl::PosTorqueControl(const rclcpp::NodeOptions & options)
: Node("position_torque_control", options)
{
  RCLCPP_INFO(this->get_logger(), "Run setup dynamixel node");

  this->declare_parameter<int8_t>("qos_depth", 10);
  int8_t qos_depth = 0;
  this->get_parameter("qos_depth", qos_depth);

  this->declare_parameter<std::string>("device_name", "/dev/ttyUSB0");
  this->declare_parameter<int>("addr_present_position", 36);
  this->declare_parameter<int>("addr_torque_mode_enable", 70);
  this->declare_parameter<int>("addr_goal_torque", 71);
  this->declare_parameter<float>("protocol_version", 1.0);
  this->declare_parameter<int>("baudrate", 1000000);
  this->get_parameter("baudrate", baudrate);
  this->get_parameter("addr_goal_torque", addr_goal_torque);
  this->get_parameter("addr_torque_mode_enable", addr_torque_mode_enable);
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

  auto set_torque_control_mode =
    [this](
    const std::shared_ptr<SetMode::Request> request,
    std::shared_ptr<SetMode::Response> response) -> void
    {
        response->torque_mode = 1;
        for (uint8_t m_id : request->motor_ids) {
            dxl_comm_result = packetHandler->write1ByteTxRx(
                portHandler,
                m_id,
                addr_torque_mode_enable,
                1,
                &dxl_error
            );
            // std::cout << (int)m_id << std::endl;
            if (dxl_comm_result != COMM_SUCCESS) {
                RCLCPP_ERROR(rclcpp::get_logger("setup_dynamixel_node"), "Failed to enable torque control mode for id %d", (int)m_id);
                response->torque_mode = 0;
            } else {
                RCLCPP_INFO(rclcpp::get_logger("setup_dynamixel_node"), "Succeeded to enable torque control mode for id %d", (int)m_id);
                // response->torque_mode = 1;
            }
        }
    };

  set_torque_mode_server_ = create_service<SetMode>("set_mode", set_torque_control_mode);

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

    set_torque_subscriber_ =
      this->create_subscription<SetPosition>(
      "set_position",
      QOS_RKL10V,
      [this](const SetPosition::SharedPtr msg) -> void
      {
        uint8_t dxl_error = 0;

        int goal_position = msg->position;

        int difference = (goal_position - present_position)/4;
        std::cout<<present_position<<std::endl;
        // Torque Value of X series is 4 byte data.
        // For AX & MX(1.0) use 2 byte data(uint16_t) for the Position Value.
        uint16_t goal_torque;
        if (difference < 0){
          goal_torque = (unsigned int)std::abs(difference);  // Convert int32 -> uint32
          std::cout<<"Angle value "<<goal_torque<<std::endl;
        }
        else{
          goal_torque = (unsigned int)(1023 + std::abs(difference));
          std::cout<<"Angle value "<<goal_torque<<std::endl;
        }
        // Write Goal Torque (length : 2 bytes)
        // When writing 2 byte data to AX / MX(1.0), use write2ByteTxRx() instead.
        dxl_comm_result =
        packetHandler->write2ByteTxRx(
          portHandler,
          (uint8_t) msg->id,
          addr_goal_torque,
          goal_torque,
          &dxl_error
        );

        if (dxl_comm_result != COMM_SUCCESS) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getRxPacketError(dxl_error));
        } else {
          RCLCPP_INFO(this->get_logger(), "Set [ID: %d] [Goal Torque: %d]", msg->id, goal_torque);
        }
      }
    );

  get_position_server_ = create_service<GetPosition>("get_position", get_present_position);

}

PosTorqueControl::~PosTorqueControl()
{
}


}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(motor_setup::PosTorqueControl)
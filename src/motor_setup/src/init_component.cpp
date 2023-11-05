#include "motor_setup/init_component.hpp"

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>

#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_inf/srv/set_id.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

namespace motor_setup
{

// Create a SetupDynamixel "component" that subclasses the generic rclcpp::Node base class.
// Components get built into shared libraries and as such do not write their own main functions.
// The process using the component's shared library will instantiate the class as a ROS node.
SetupDynamixel::SetupDynamixel(const rclcpp::NodeOptions & options)
: Node("setup_dynamixel_node", options)
{
  RCLCPP_INFO(this->get_logger(), "Run setup dynamixel node");

  this->declare_parameter<int8_t>("qos_depth", 10);
  int8_t qos_depth = 0;
  this->get_parameter("qos_depth", qos_depth);

  this->declare_parameter<std::string>("device_name","/dev/ttyUSB0");
  this->declare_parameter<int>("addr_torque_enable", 24);
  this->declare_parameter<float>("protocol_version", 1.0);
  this->declare_parameter<int>("baudrate", 1000000);
  this->get_parameter("baudrate", baudrate);
  this->get_parameter("addr_torque_enable", addr_torque_enable);
  this->get_parameter("protocol_version", protocol_version);
  this->get_parameter("device_name", device_name);

  portHandler = dynamixel::PortHandler::getPortHandler(device_name.c_str());
  packetHandler = dynamixel::PacketHandler::getPacketHandler(protocol_version);

  //   Open Serial Port
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

  const auto QOS_RKL10V =
    rclcpp::QoS(rclcpp::KeepLast(qos_depth)).reliable().durability_volatile();
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
}

SetupDynamixel::~SetupDynamixel()
{
}


}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(motor_setup::SetupDynamixel)
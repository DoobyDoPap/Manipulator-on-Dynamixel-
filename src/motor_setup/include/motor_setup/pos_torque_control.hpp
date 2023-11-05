#ifndef COMPOSITION__POSITION_TORQUE_CONTROL_HPP_
#define COMPOSITION__POSITION_TORQUE_CONTROL_HPP_

#include <cstdio>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_inf/srv/get_position.hpp"
#include "dynamixel_sdk_inf/msg/set_position.hpp"
#include "dynamixel_sdk_inf/srv/set_id.hpp"
#include "dynamixel_sdk_inf/srv/set_mode.hpp"

#include "motor_setup/visibility_control.h"

namespace motor_setup
{

class PosTorqueControl : public rclcpp::Node
{
public:
//   COMPOSITION_PUBLIC
  using SetId = dynamixel_sdk_inf::srv::SetId;
  using SetMode = dynamixel_sdk_inf::srv::SetMode;
  using SetPosition = dynamixel_sdk_inf::msg::SetPosition;
  using GetPosition = dynamixel_sdk_inf::srv::GetPosition;

  COMPOSITION_PUBLIC
  explicit PosTorqueControl(const rclcpp::NodeOptions & options);
  virtual ~PosTorqueControl();

private:
  rclcpp::Subscription<SetPosition>::SharedPtr set_torque_subscriber_;
  rclcpp::Service<GetPosition>::SharedPtr get_position_server_;
  rclcpp::Service<SetId>::SharedPtr set_id_server_;
  rclcpp::Service<SetMode>::SharedPtr set_torque_mode_server_;
  rclcpp::TimerBase::SharedPtr timer_;
  dynamixel::PortHandler * portHandler;
  dynamixel::PacketHandler * packetHandler;
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;
  uint16_t addr_goal_torque;
  uint16_t addr_present_position;
  uint16_t addr_torque_mode_enable;
  float protocol_version;
  std::string device_name;
  int present_position;
  int baudrate;
  uint16_t addr_torque_enable = 24;
};

}  // namespace composition

#endif  // COMPOSITION__INIT_COMPONENT_HPP_

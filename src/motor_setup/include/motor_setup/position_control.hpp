#ifndef COMPOSITION__POSITION_CONTROL_HPP_
#define COMPOSITION__POSITION_CONTROL_HPP_

#include <cstdio>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_inf/srv/get_position.hpp"
#include "dynamixel_sdk_inf/msg/set_position.hpp"
#include "dynamixel_sdk_inf/srv/set_id.hpp"

#include "motor_setup/visibility_control.h"

namespace motor_setup
{

class PositionControl : public rclcpp::Node
{
public:
//   COMPOSITION_PUBLIC
  using SetId = dynamixel_sdk_inf::srv::SetId;
  using SetPosition = dynamixel_sdk_inf::msg::SetPosition;
  using GetPosition = dynamixel_sdk_inf::srv::GetPosition;
  COMPOSITION_PUBLIC
  explicit PositionControl(const rclcpp::NodeOptions & options);
  virtual ~PositionControl();

private:
  rclcpp::Subscription<SetPosition>::SharedPtr set_position_subscriber_; 
  rclcpp::Service<GetPosition>::SharedPtr get_position_server_;
  rclcpp::Service<SetId>::SharedPtr set_id_server_;
  rclcpp::TimerBase::SharedPtr timer_;
  dynamixel::PortHandler * portHandler;
  dynamixel::PacketHandler * packetHandler;
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;
  uint16_t addr_present_position;
  uint16_t addr_goal_position;
  float protocol_version;
  std::string device_name;
  int present_position;
  int baudrate; 
 
  int id; 
  uint16_t addr_torque_enable = 24;
};

}  // namespace composition

#endif  // COMPOSITION__INIT_COMPONENT_HPP_

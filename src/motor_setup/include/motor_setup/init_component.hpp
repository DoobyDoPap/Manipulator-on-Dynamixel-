#ifndef COMPOSITION__INIT_COMPONENT_HPP_
#define COMPOSITION__INIT_COMPONENT_HPP_

#include <cstdio>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_inf/srv/set_id.hpp"

#include "motor_setup/visibility_control.h"

namespace motor_setup
{

class SetupDynamixel : public rclcpp::Node
{
public:
//   COMPOSITION_PUBLIC
  using SetId = dynamixel_sdk_inf::srv::SetId;
  COMPOSITION_PUBLIC
  explicit SetupDynamixel(const rclcpp::NodeOptions & options);
  virtual ~SetupDynamixel();

protected:
  void on_timer();

private:
  rclcpp::Service<SetId>::SharedPtr set_id_server_;
  rclcpp::TimerBase::SharedPtr timer_;
  dynamixel::PortHandler * portHandler;
  dynamixel::PacketHandler * packetHandler;
  uint8_t dxl_error = 0;
  int dxl_comm_result = COMM_TX_FAIL;
  int baudrate;
  uint16_t addr_torque_enable;
  float protocol_version;
  std::string device_name;

};

}  // namespace composition

#endif  // COMPOSITION__INIT_COMPONENT_HPP_

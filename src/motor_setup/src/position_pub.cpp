#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include "dynamixel_sdk_inf/msg/set_position.hpp"

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <chrono>

using namespace std::chrono_literals; 
int motor;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class PositionPublisher : public rclcpp::Node
{  
   public:
    PositionPublisher()
    : Node("pos_pub"), count_(0)
    {
      publisher_ = this->create_publisher<dynamixel_sdk_inf::msg::SetPosition>("set_position", 1000); 
      timer_ = this->create_wall_timer(
      500ms, std::bind(&PositionPublisher::timer_callback, this));
    }  
     
    
  private:
    void timer_callback()
    { 
      std::cout<<"enter no of motors "<< std::endl; 
      std::cin>> motor;    
      
      auto pose_message = dynamixel_sdk_inf::msg::SetPosition(); 
      
      for(int i=0 ;i<motor;i++){ 
      std::cout<< "Enter the desired position for the motor, from 0  ~  4095\n";
      _Float32 x;
      std::cin>>x;  
      pose_message.position.push_back(x);
      std::cout<<"enter motor id:"<<std::endl;  
      uint8_t y; 
      std::cin>>y; 
      pose_message.id.push_back(y); 
      pose_message.id[i]=pose_message.id[i]-48; 
      RCLCPP_INFO(this->get_logger(), "Position: '%d' | ID: '%d'\n", pose_message.position[i], pose_message.id[i]);
      }
      publisher_->publish(pose_message); 
     
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<dynamixel_sdk_inf::msg::SetPosition>::SharedPtr publisher_; 
    size_t count_; 
  
 
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PositionPublisher>());
  rclcpp::shutdown();
  return 0;
}

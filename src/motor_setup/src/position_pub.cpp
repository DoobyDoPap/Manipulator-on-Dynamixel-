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
      this->create_subscription<dynamixel_sdk_inf::msg::SetPosition>( 
              "set_position_2" , 10 , std :: bind(&PositionSubscriber ::time_callback , this )
            );
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
      int32_t x;
      std::cin>>x;  
      pose_message.position.push_back(x);
      std::cout<<"enter motor id:"<<std::endl;  
      
      pose_message.id.push_back((uint8_t)i); 
      pose_message.id[i]=pose_message.id[i]-48; 
      RCLCPP_INFO(this->get_logger(), "Position: '%d' | ID: '%d'\n", pose_message.position[i], pose_message.id[i]);
      }
      publisher_->publish(pose_message); 
     
    } 
    private : 
          void time_callback(const dynamixel_sdk_inf_set_position::msg::uint8 &msg){   
               int set_id[sizeof(msg->id)]; 
               for(int i=0;i<=sizeof(msg->id);i++){ 
                   set_id[i]=(int)msg->id[i]; 

               };
               int net_theta[sizeof(msg->position)] ;
               for(int i=0 ; i<=sizeof(msg->position);i++){ 
                  net_theta[i]=(int)msg->position[i]; 
               }

               }; 
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

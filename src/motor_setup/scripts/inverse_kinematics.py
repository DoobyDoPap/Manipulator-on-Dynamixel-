#usr/bin/env/python3 
import rclpy 
from rclpy.node import Node  
from dynamixel_sdk_inf.msg import SetPosition
import math 

theta_0 ,theta_1,theta_2 = 0,90,90  

def angles():
         global theta_2, theta_0, theta_1        
         x = int(input("ENTER THE VALUE OF X: "))
         y = int(input("ENTER THE VALUE OF Y: "))
         z = int(input("ENTER THE VALUE OF Z:"))

         if  x <= 28 and  y <= 28 and   z <= 31:
           theta_0 = math.atan2(y, x)

         d = 6
         a = 14
         b = 14

       
         theta_2 = math.acos((x * x + y * y + (z - d) * (z - d) - a * a - b * b) / (2 * a * b)) 
         print((x * x + y * y + (z - d) * (z - d) - a * a - b * b) / (2 * a * b))
         print("Theta_2:", theta_2)

      
         if theta_0 != 90: 
            X1 = x / math.cos(theta_0) 
            num_1 = ((a + (b * math.cos(theta_2))) * (z - d) + a * math.sin(theta_2)) * X1 
            denom = (a + b) * math.cos(theta_2) * (a + b) * math.cos(theta_2) + b * math.sin(theta_2) * b * math.sin(theta_2)
            Z1 = num_1 / denom 
            print(Z1)
            theta_1 = math.asin(Z1) 
            if -1 <= math.sin(theta_1) <= 1:
                if -0.19 <= math.sin(theta_2):
                    print("Theta_1:", theta_1)
                else:
                    print("CANNOT REACH")
            else:
                print("ERROR: OUT OF RANGE")
            if theta_1 == 90:
                if -0.939 <= math.sin(theta_2):
                    pass
                else:
                    print("NOT POSSIBLE")
         elif theta_0 != 0:  
            Y1 = y / math.sin(theta_0) 
            num_2 = ((a + (b * math.cos(theta_2))) * (z - d) + a * math.sin(theta_2)) * Y1 
            denom = (a + b) * math.cos(theta_2) * (a + b) * math.cos(theta_2) + b * math.sin(theta_2) * b * math.sin(theta_2)
            Z2= num_2/denom  
            theta_1 = math.asin(Z2) 
            if -1<= math.sin(theta_1)<=1: 
                if -0.19 <= math.sin(theta_2): 
                    print("Theta_1: ",theta_1)
                else: 
                    print("cant reach ") 
            else : 
                print("out of range")

            
    
           
            
            

         else:
          print("Max length reached") 

class Inverse_Publisher(Node):  
      def __init__(self):
           super().__init__('inverse_publisher')
           self.publisher_ = self.create_publisher(SetPosition, 'set_position', 10)
           timer_period = 0.5  
           self.timer = self.create_timer(timer_period, self.timer_callback)
           self.i = 0 

      def timer_callback(self):
        msg = SetPosition() 
        
        angles()
        theta=[theta_0,theta_1,theta_2]
        print(theta, "\n")
        ids=[0,1,2] 
        for i in range(len(ids)): 
            y = abs(ids[i]-48)
            z =theta[i]
            msg.id.append(y) 
            msg.position.append(z)
        
         
        
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg) 
        self.i += 1 


     

def main(args=None) :  
     rclpy.init(args=args)
     inverse_publisher = Inverse_Publisher() 
     rclpy.spin(inverse_publisher) 

if __name__ == '__main__':
      main()




import rclpy
from rclpy.node import Node

from std_msgs.msg import Int32

class SumSubscriber(Node):

    def __init__(self):
        super().__init__('sum_subscriber')
        self.subscription1 = self.create_subscription(Int32, 'number1', self.listener_callback1, 10)  
        self.subscription2 = self.create_subscription(Int32, 'number2', self.listener_callback2, 10)

    def listener_callback1(self, msg):
        self.number1 = msg.data
        self.calculate_and_display_sum()

    def listener_callback2(self, msg):
        self.number2 = msg.data
        self.calculate_and_display_sum()

    def calculate_and_display_sum(self):
        try:
            sum_result = self.number1 + self.number2
            self.get_logger().info('Sum of {} and {} is: {}'.format(self.number1, self.number2, sum_result))

        except AttributeError:
            
            self.get_logger().info('Waiting for both numbers...')

def main(args=None):
    rclpy.init(args=args)

    sum_subscriber = SumSubscriber()

    rclpy.spin(sum_subscriber)
    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)

    sum_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

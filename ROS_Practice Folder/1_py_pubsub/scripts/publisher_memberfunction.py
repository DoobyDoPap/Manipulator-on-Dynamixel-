import rclpy
from rclpy.node import Node

from std_msgs.msg import Int32


class Publisher1(Node):

    def __init__(self):
        super().__init__('number1')
        self.publisher_ = self.create_publisher(Int32, 'topic', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = Int32()
        msg.data = int(raw_input("Enter first number: "))
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%d"' % msg.data)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    number1 = Publisher1()

    rclpy.spin(number1)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    number1.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

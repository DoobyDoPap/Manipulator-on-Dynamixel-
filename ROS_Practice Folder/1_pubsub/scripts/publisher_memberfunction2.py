import rclpy
from rclpy.node import Node

from std_msgs.msg import Int32


class Publisher2(Node):

    def __init__(self):
        super().__init__('number2')
        self.publisher_ = self.create_publisher(Int32, 'number2', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = Int32()
        msg.data = 3
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%d"' % msg.data)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    number2 = Publisher2()

    rclpy.spin(number2)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    number2.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

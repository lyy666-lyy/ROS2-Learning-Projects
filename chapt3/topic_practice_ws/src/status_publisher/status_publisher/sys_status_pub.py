import rclpy
from rclpy.node import Node
from status_interfaces.msg import SystemStatus
import psutil
import platform

class SysStatusPub(Node):
    def __init__(self):
        super().__init__('sys_status_publisher')
        self.publisher_ = self.create_publisher(SystemStatus, 'system_status', 10)
        timer_period = 2.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = SystemStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.cpu_percent = psutil.cpu_percent(interval=1)
        msg.memory_percent = psutil.virtual_memory().percent
        msg.memory_available = psutil.virtual_memory().available / (1024 * 1024)  # in MB
        msg.memory_total = psutil.virtual_memory().total / (1024 * 1024)  # in MB
        msg.net_sent = psutil.net_io_counters().bytes_sent / (1024 * 1024)  # in MB
        msg.net_recv = psutil.net_io_counters().bytes_recv / (1024 * 1024)  # in MB
        msg.host_name = platform.node()

        self.publisher_.publish(msg)
        self.get_logger().info(f'Published System Status: CPU {msg.cpu_percent}%, Memory {msg.memory_percent}%')

def main():
    rclpy.init()
    sys_status_pub = SysStatusPub()
    rclpy.spin(sys_status_pub)
    rclpy.shutdown()
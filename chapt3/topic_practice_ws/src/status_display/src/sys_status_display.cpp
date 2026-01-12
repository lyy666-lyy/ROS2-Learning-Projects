#include <QApplication>
#include <QLabel>
#include <QString>
#include <rclcpp/rclcpp.hpp>
#include "status_interfaces/msg/SystemStatus.hpp"

using SystemStatus = status_interfaces::msg::SystemStatus;

class SysStatusDisplay: public rclcpp::Node
{
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscriber_;
    QLabel* label_;
public:
    SysStatusDisplay(/* args */):Node("sys_status_display")
    {
        label_ = new QLabel();
        subscriber_ = this->create_subscription<SystemStatus>(
            "system_status", 10,
            [&](const SystemStatus::SharedPtr msg)
            {
                label_->setText(get_qstr_from_msg(msg));
            }
        );
        label_->setText(get_qstr_from_msg(SystemStatus::SharedPtr()));
        label_->show();
    };
   
    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg)
    {
        std::stringstream show_str;
            show_str <<"========提供状态可视化显示工具=========\n"<<
            "数 据 时 间:\t"<< msg->header.stamp.sec <<"\ts\n"<<
            "主 机 名 字:\t "<< msg->host_name <<"\t\n"<<
            "cpu  使用率:\t "<< msg->cpu_percent <<"\t%\n"<<
            "内存 使用率:\t "<< msg->memory_percent <<"\t%\n"<<
            "内存总大小 :\t "<< msg->memory_total <<"\tmb\n"<<
            "剩余有效内存:\t "<< msg->memory_available <<"\tmb\n"<<
            "网络发送量 :\t "<< msg->net_sent <<"\tmb\n"<<
            "网络接受量 :\t "<< msg->net_recv <<"\tmb\n"<<
            "====================================\n";
        return QString::fromStdString('hello qt');
    };
};




int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);// Initialize the Qt application
    auto node = std::make_shared<SysStatusDisplay>();
    std::thread spin_thread([&]() { rclcpp::spin(node); });
    spin_thread.detach();
    app.exec();

    return 0;
}
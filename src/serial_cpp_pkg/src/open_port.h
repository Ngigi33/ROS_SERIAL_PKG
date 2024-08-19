#include <libserial/SerialPort.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

LibSerial::SerialPort stm_;
std::string port_;

void open_port()
{

    port_ = "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A50285BI-if00-port0";

    stm_.Open(port_);
    stm_.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
    printf("Port open");
}

int main()
{
    open_port;
    while (1)
    {
        auto message = std_msgs::msg::String();
        if (stm_.IsDataAvailable())
        {
            stm_.ReadLine(message.data);
            //RCLCPP_INFO_STREAM(this->get_logger(), "MSG received from Stm:" << message.data);
        }
    }
}
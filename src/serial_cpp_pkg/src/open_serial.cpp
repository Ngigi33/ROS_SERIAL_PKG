#include <libserial/SerialPort.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

void open_port()
{
    LibSerial::SerialPort stm_;
    std::string port_;

    port_= "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A50285BI-if00-port0";

    stm_.Open(port_);
    stm_.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
    printf("Port open");
}

int main()
{
    open_port;
}
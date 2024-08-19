#include "open_port.h"

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "geometry_msgs/msg/twist.hpp"
#include <libserial/SerialPort.h>

using std::placeholders::_1;

// class Serial_Receiver : public rclcpp::Node
// {
// public:

// Serial_Receiver():Node("Receiver_Node")
// {

//     if (stm_.IsOpen())
//     {
//      RCLCPP_INFO(this->get_logger(), "PORT IS OPEN");
//     }

// }
// }
#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/string.hpp>
#include "example_interfaces/msg/string.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::placeholders::_1;

class D_Calc : public rclcpp::Node
{
public:
    D_Calc() : Node("Distance_Calculator_Node") // Create a node with name stated
    {
        wheel_odom_sub_ = this->create_subscription<std_msgs::msg::String>("/distance_finder", 1, std::bind(&D_Calc::receive_Msg, this, std::placeholders::_1));
        timer_ = this->create_wall_timer(std::chrono::microseconds(500), std::bind(&D_Calc::odom, this));
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr wheel_odom_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    float distance_btwn_wheels = 235.00;
    float wheel_diameter = 85.00;

    int rot_A;
    int rot_B;

    double distance_A;
    double distance_B;
    double distance_Avg;
    double orientation_change;

    void receive_Msg(const std_msgs::msg::String::SharedPtr msg)
    {

        std::string message = msg->data;
        // RCLCPP_INFO(this->get_logger(), "Data Received: %s", message.c_str());

        std::vector<std::string> text = split(message, ',');
        // RCLCPP_INFO(this->get_logger(), "Data Received: %s", text[1].c_str());

        rot_A = stoi(text[2]);
        rot_B = stoi(text[3]);
        // RCLCPP_INFO(this->get_logger(), "Rot A= %d , Rot B= %d", rot_A, rot_B);
    }

    double Distance_Calculation(const int rotation)
    {
        double distance = (rotation * 2 * 3.14159 * (wheel_diameter / 2));
        return distance;
    }

    void odom()
    {
        distance_A = Distance_Calculation(rot_A);
        distance_B = Distance_Calculation(rot_B);

        distance_Avg = ((distance_A + distance_B) / 2.0);

        orientation_change = ((distance_A - distance_B) / distance_btwn_wheels);
        RCLCPP_INFO(this->get_logger(), "Distance A= %f....Distance B= %f....Distance Avg=%f....Orientation =%f", distance_A, distance_B, distance_Avg, orientation_change);
    }

    std::vector<std::string> split(const std::string &s, char delimiter)
    {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delimiter))
        {
            result.push_back(item);
        }
        return result;
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);               // initialize ROS 2 communication
    auto node = std::make_shared<D_Calc>(); // creating a shared ponter to the node
    rclcpp::spin(node);                     // loop as node is executed
    rclcpp::shutdown();                     // shutdown the communication, stop spinning
    return 0;
}

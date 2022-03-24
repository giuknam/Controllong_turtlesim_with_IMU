#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"

#include <algorithm>
#include <ctime>

float front=0, front2=0;
// float side=0;
float rotate=0, rotate2=0;

unsigned long now = 0;
unsigned long pass = 0;
double ms=0;

void msgCallback(const sensor_msgs::Imu& msg2)
{
    // ROS_INFO("pitch.y=%f",front);
    // ROS_INFO("roll.x=%f",rotate);
    // ROS_INFO("roll.x=%f",rotate2);
    // ROS_INFO("speed=%f",ms);
    // ROS_INFO("hello?");

    // conversion

    // quaternion to euler 

    // front = pitch (radian) ==> m/s  (mapping: -1m/s ~ 1m/s 선형적으로 변환)
    // rotate = roll (radian) ==> rad/s (mapping: -1 rad/s ~ 1rad/s 선형적으로 변환 )

    // now = msg2.header.seq;
    // pass = msg2.header.seq;
    // ms = (now-pass) / 100;

    // front2 = msg.angular_velocity.y * ms;
    // rotate2 = msg2.angular_velocity.x;

    front = atan(-msg2.linear_acceleration.x / sqrt(pow(msg2.linear_acceleration.y, 2) + pow(msg2.linear_acceleration.z, 2)));
    rotate = atan(-msg2.linear_acceleration.y / sqrt(pow(msg2.linear_acceleration.x, 2) + pow(msg2.linear_acceleration.z, 2)));
    
    // side = msg2.orientation.y;
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtlesimcontroller_witn_imu");
    ros::NodeHandle nh;

    ros::Publisher imu_controller = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);

    ros::Subscriber turtlesim_processer = nh.subscribe("/imu/data", 100, msgCallback);
    
    ros::Rate loop_rate(10);
    
    while(ros::ok())
    {
        geometry_msgs::Twist msg;
        
        msg.linear.x=front;
        ROS_INFO("rotate=%f",front);
        
        msg.angular.z=rotate;
        ROS_INFO("rotate=%f",rotate);
        
        // msg.angular.z=rotate2;
        // ROS_INFO("rotate=%f",rotate2);

        imu_controller.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();

    }
    return 0;

}
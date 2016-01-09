#include "ros/ros.h"
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/CompressedImage.h>
#include "std_msgs/String.h"


void pictureCallback(const sensor_msgs::CompressedImage::ConstPtr& picture)
{
	ROS_INFO("I received a picture!! ");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "linefollower");

  ros::NodeHandle n;

  ros::Subscriber linefollow_sub = n.subscribe("camera/image/compressed", 50, pictureCallback);

  ros::Publisher linefollow_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 50);

  ros::Rate loop_rate(2);

  


  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::Twist tmsg;
    tmsg.linear.x = 1;
    tmsg.linear.y = 0;
    tmsg.linear.z = 0;
    tmsg.angular.x = 0;
    tmsg.angular.y = 0;
    tmsg.angular.z = 0;

    std_msgs::String tmsg_string;
    std::stringstream ss;
    ss << "linear: [" << 
	tmsg.linear.x << " " << tmsg.linear.y << " " << tmsg.linear.z << "] , angular: [" << tmsg.angular.x << " " << tmsg.angular.y << " " << tmsg.angular.z << "]";

    tmsg_string.data = ss.str();

    ROS_INFO("%s", tmsg_string.data.c_str());

    linefollow_pub.publish(tmsg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;

  }

  return 0;
}

#include "ros/ros.h"
#include <sstream>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "linefollower");

  ros::NodeHandle n;

  ros::Publisher linefollow_pub = n.advertise<geometry_msgs::Twist>("linefollower", 50);

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


    linefollow_pub.publish(tmsg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;

  }

  return 0;
}

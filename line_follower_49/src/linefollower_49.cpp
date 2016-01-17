/**
* Group number: 49
* Student 1:
* Jesse Arens, 4206231
* Student 2:
* Rick Brugsma, 4163788
*/

#include "ros/ros.h"
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/CompressedImage.h>
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>

void pictureCallback(const sensor_msgs::CompressedImage::ConstPtr& picture) {
	ROS_INFO("I received a picture!! ");
	
	//Pseudo-code for the Line following algorithm.
		/*
	 * 
	 * 1. Create a twist message:
	 *  tsmg.linear.x = 0;
	 * 	tsmg.linear.y = 0;
	 *  tsmg.linear.z = 0;
	 *  tsmg.angular.x = 0;
	 *	tmsg.angular.y = 0;
	 * 	tmsg.angular.z = 0;
	 * 
	 * 2. Read out the image in a grid of pixels:
	 * 	result:
	 * 	int[][] pixel[x][y]
	 * 3. Start halfway through the height(y-direction) of the image and declare two x-values
	 * 	int yhalve;
	 * 	int xhalve;
	 * 	int x1;
	 * 		int x2;
	 * 
	 * 4. Loop through the whole width (x-direction) of the picture at yhalve.
	 * for (int i=0;pixel.width;i++){
	 * 
	 * 5. Register the x-value for which the current pixel is white and the next picture is not white.
	 * 	if (pixel[i][yhalve] = white & pixel[i+1][yhalve] != white){
	 * 	x1 = i+1;
	 * 
	 * 6. If a line is detected, always move forwards.
	 * 	tmsg.linear.x = 1;
	 * 	}
	 * 
	 * 7. Register the x-value for which the current pixel is not white and the next picture is white.
	 * if (pixel[i][yhalve] =! white & pixel[i+1][yhalve] = white){
	 * 	x2 = i+1;
	 * 8. The angle that has to be made equals the difference between the average of the two line boundary positions and going straight ahead (xhalve).
	 * 	tmsg.angular.y = xhalve - (x1+x2)/2;
	 * }
	 * }
	 * 
	 * 9. Publish the altered twist message.
	 * linefollow_pub.publish(tmsg);
	 * 
	 * 	*/
	
}

int main(int argc, char **argv)
{
  //Setting up of the publisher/subscriber ros rode.
  ros::init(argc, argv, "linefollower");
  ros::NodeHandle n;
  ros::Subscriber linefollow_sub = n.subscribe("camera/image/compressed", 50, pictureCallback);
  ros::Publisher linefollow_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 50);
  ros::Rate loop_rate(2);

  int count = 0;
  
  //Continuous loop that checks for images and publishes a geometry_msg
  while (ros::ok())
  {
	//Create a Twist message.
    geometry_msgs::Twist tmsg;
    tmsg.linear.x = 1;
    tmsg.linear.y = 0;
    tmsg.linear.z = 0;
    tmsg.angular.x = 0;
    tmsg.angular.y = 0;
    tmsg.angular.z = 0;

	//Converting Twist message to a string-form to print in the terminal.
    std_msgs::String tmsg_string;
    std::stringstream ss;
    ss << "linear: [" << 
	tmsg.linear.x << " " << tmsg.linear.y << " " << tmsg.linear.z << "] , angular: [" << tmsg.angular.x << " " << tmsg.angular.y << " " << tmsg.angular.z << "]";

    tmsg_string.data = ss.str();

    ROS_INFO("%s", tmsg_string.data.c_str());
	
	//Publish the Twist message.
    linefollow_pub.publish(tmsg);

	//Check for images.
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
  return 0;
}


#include <ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;
//pins 1 are right motor, 2 is left
const int enablePin_1 = 24;
const int reversePin_1 = 7;
const int forwardPin_1 = 6;
const int enablePin_2 = 25;
const int reversePin_2 = 3;
const int forwardPin_2 = 2;

void MotormessageCb( const geometry_msgs::Twist& cmd_vel){
  digitalWrite(forwardPin_1,HIGH);
  digitalWrite(forwardPin_2,HIGH);

}
void StartMotors( const std_msgs::Empty& stop_msg){
  digitalWrite(forwardPin_1,HIGH);
  digitalWrite(forwardPin_2,HIGH);
}

void DisablemessageCb( const std_msgs::Empty& stop_msg){
  digitalWrite(reversePin_1,LOW);
digitalWrite(reversePin_2,LOW);
digitalWrite(forwardPin_1,LOW);
digitalWrite(forwardPin_2,LOW);
}

ros::Subscriber<std_msgs::Empty> substop("stop_msg", &DisablemessageCb);
ros::Subscriber<std_msgs::Empty> substart("start_msg", &StartMotors);
ros::Subscriber<geometry_msgs::Twist> subtwist("cmd_vel", &MotormessageCb);

void setup()
{ 
  pinMode(enablePin_1, INPUT);
  pinMode(enablePin_2, INPUT);
  pinMode(reversePin_1, OUTPUT);
  pinMode(reversePin_2,OUTPUT);
  pinMode(forwardPin_1,OUTPUT);
  pinMode(forwardPin_2,OUTPUT);
  
  nh.initNode();
  nh.subscribe(subtwist);
  nh.subscribe(substop);
  nh.subscribe(substart);
  //digitalWrite(enablePin_1, HIGH);
  //digitalWrite(enablePin_2, HIGH);
}

void loop()
{ 
  
  nh.spinOnce();
  delay(500);
}


#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;
//pins 1 are right motor, 2 is left
const int enablePin_1 = 24;
const int reversePin_1 = 7;
const int forwardPin_1 = 6;
const int enablePin_2 = 25;
const int reversePin_2 = 3;
const int forwardPin_2 = 2;

void MotormessageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(forwardPin_1,HIGH);
  digitalWrite(forwardPin_2,HIGH);

}

void DisablemessageCb( const std_msgs::Empty& stop_msg){
  digitalWrite(reversePin_1,LOW);
digitalWrite(reversePin_2,LOW);
digitalWrite(forwardPin_1,LOW);
digitalWrite(forwardPin_2,LOW);
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &MotormessageCb );
ros::Subscriber<std_msgs::Empty> substop("stop_msg", &DisablemessageCb);

void setup()
{ 
  pinMode(enablePin_1, INPUT);
  pinMode(enablePin_2, INPUT);
  pinMode(reversePin_1, OUTPUT);
  pinMode(reversePin_2,OUTPUT);
  pinMode(forwardPin_1,OUTPUT);
  pinMode(forwardPin_2,OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(substop);
  digitalWrite(enablePin_1, HIGH);
  digitalWrite(enablePin_2, HIGH);
}

void loop()
{ 
  
  nh.spinOnce();
  delay(500);
}

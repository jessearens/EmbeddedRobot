
#include <ros.h>

#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <elapsedMillis.h>

ros::NodeHandle  nh;
//pins 1 are right motor, 2 is left
const int enablePin_1 = 24;
const int reversePin_1 = 7;
const int forwardPin_1 = 6;
const int enablePin_2 = 25;
const int reversePin_2 = 3;
const int forwardPin_2 = 2;

elapsedMillis timeElapsed;

void MotormessageCb( const geometry_msgs::Twist& cmd_vel){
  timeElapsed = 0; //Set timer to zero if a twist message is received.
  if (cmd_vel.angular.z != 0){
    if (cmd_vel.angular.z > 0){
      turnleft();
    }
    else { 
      turnright();
    } 
  }
  
  if (cmd_vel.linear.x !=0){
    if (cmd_vel.linear.x > 0){
      moveforward();
    }
    else {
      movereverse();
    }
  }
}

void turnleft(){
  digitalWrite(forwardPin_1,HIGH);
  delay(500);
  digitalWrite(forwardPin_1,LOW);
}

void turnright(){
  digitalWrite(forwardPin_2,HIGH);
  delay(500);
  digitalWrite(forwardPin_2,LOW);
}

void moveforward(){
  digitalWrite(forwardPin_1,HIGH);
  digitalWrite(forwardPin_2,HIGH);
  delay(500);
  digitalWrite(forwardPin_1,LOW);
  digitalWrite(forwardPin_2,LOW);
}

void movereverse(){
  digitalWrite(reversePin_1,HIGH);
  digitalWrite(reversePin_2,HIGH);
  delay(500);
  digitalWrite(reversePin_1,LOW);
  digitalWrite(reversePin_2,LOW);
}

void Shutdown(){
digitalWrite(reversePin_1,LOW);
digitalWrite(reversePin_2,LOW);
digitalWrite(forwardPin_1,LOW);
digitalWrite(forwardPin_2,LOW);
}

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
}

void loop()
{ 
  if (timeElapsed > 3000){
    Shutdown();
  }
    
}

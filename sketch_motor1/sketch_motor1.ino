#include <ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <elapsedMillis.h>
#include <stdint.h>

//Setting the motor pins
//pins 1 are for right motor, 2 are for the left motor.
const int enablePin_1 = 24;
const int reversePin_1 = 7;
const int forwardPin_1 = 6;
const int enablePin_2 = 25;
const int reversePin_2 = 3;
const int forwardPin_2 = 2;

//Setting the pins for the ultrasonic sensor
#define usensor_triggerPin 23
#define usensor_echoPin 22

volatile int8_t usensor_interrupt = 0;
elapsedMillis timeElapsed;
ros::NodeHandle nh;

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
  
  if (timeElapsed > 300000){
    //stop entirely
    exit(0);
  }
}

void checkUSensor(){
  
  long minDistance = 1000;
  int count = 10;
  
  //TODO: try more than 10 times? check for latency. the robot should stop within a second.
  for(int i = 0; i < count; i++){
    long newDistance = getUsensorDistance();
    
    if(newDistance < minDistance){
      minDistance = newDistance;
    }  
  }
  
  //TODO: test for best value (corresponding to 10 cm distance)
  if(minDistance < 24){
    usensor_interrupt = 1;
    Shutdown();
    checkUSensor();
  }
  else{
    usensor_interrupt = 0;
  }
}

long getUsensorDistance(){
  
  long distance = 0;
  
  digitalWrite(usensor_triggerPin, LOW);
  delayMicroseconds(8);
  digitalWrite(usensor_triggerPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(usensor_triggerPin, LOW);
  distance = pulseIn(usensor_echoPin, HIGH);
  
  //to get distance in cm:
  distance /= 29.1;
  return distance;
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
  
  pinMode(usensor_triggerPin, OUTPUT);
  pinMode(usensor_echoPin, INPUT);
  
  nh.initNode();
  nh.subscribe(subtwist);
}

void loop()
{ 
  nh.spinOnce();
  if (timeElapsed > 3000){
    Shutdown();
  }
  checkUSensor();
  
}

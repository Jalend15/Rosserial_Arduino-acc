
#include <ros.h>
#include<ros/publisher.h>
#include<ros/subscriber.h>
#include<roscpp/Logger.h>
#include<ros/msg.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <string.h>

//#define X_Axis_Register_DATAX0 0x32
//#define X_Axis_Register_DATAX1 0x33 
//#define Power_Register 0x2D
//ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

 int messageCb(const std_msgs::String&msg){
  //Serial.println("%s",a);
//ROS_INFO("I heard: [%d]", msg.data.c_str());
 return 0;
}
ros::NodeHandle nh;
std_msgs::String str_msg;
int msg[3];
ros::Publisher p("acc", &str_msg);
ros::Subscriber <int>sub("acc",&messageCb);
//ros::Subscriber sub = n.subscribe("acc", 1000, messageCb);

void setup() {
  // put your setup code here, to run once:
   Wire.begin(); 
  Serial.begin(9600);
  delay(100);
  
  
  Wire.beginTransmission(0x53);//adxl address

  Wire.write(0x2D); //power register
  Wire.write(0);     //clears the register
   Wire.endTransmission();
    
  Wire.beginTransmission(0x53);

  Wire.write(0x2D);
  Wire.write(16);
   Wire.endTransmission();
  
  Wire.beginTransmission(0x53);

  Wire.write(0x2D);
  Wire.write(8);
   Wire.endTransmission();
  nh.initNode();

  nh.advertise(p);
  nh.subscribe(sub);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x53); 
  
  Wire.write(0x32);
  
  
  Wire.endTransmission(); 
  Wire.beginTransmission(0x53);
  Wire.requestFrom(0x53,6); 
  char output[512];
 int x=(((int)Wire.read())<<8) |  Wire.read(); 
  int  y=(((int)Wire.read())<<8) |  Wire.read();
   int z=(((int)Wire.read())<<8) |  Wire.read();
   sprintf(output,"%d %d %d",x,y,z);

    
    str_msg.data = output;
  
   p.publish(&str_msg);
   
 Serial.println(1);
  nh.logdebug("Debug Statement");
 nh.loginfo("Program info");
 nh.logwarn("Warnings.");
 nh.logerror("Errors..");
 nh.logfatal("Fatalities!");
 while(!nh.connected()){
  nh.spinOnce();
 }

  nh.spinOnce();
  delay(1000);
  
 // 
  
// ros::spin();
}

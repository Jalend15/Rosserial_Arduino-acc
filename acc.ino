
#include <ros.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <string.h>

//#define X_Axis_Register_DATAX0 0x32
//#define X_Axis_Register_DATAX1 0x33 
//#define Power_Register 0x2D
//ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher p("acc", &str_msg);

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); 
  Serial.begin(57600);
  delay(100);
  
  
  Wire.beginTransmission(0x53);//adxl address

  Wire.write(0x2D); //power register
  Wire.write(0);     //clears the register
  Wire.endTransmission();
    
  Wire.beginTransmission(0x53);

  Wire.write(0x2D);
  Wire.write(16);//sets for measure mode
  Wire.endTransmission();
  
  Wire.beginTransmission(0x53);

  Wire.write(0x2D);
  Wire.write(8);//disables sleep mode
  Wire.endTransmission();
  nh.initNode();
  nh.spinOnce();
  nh.advertise(p);
  nh.spinOnce();
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
  Wire.endTransmission(); 

  sprintf(output,"%d %d %d",x,y,z);

    
  str_msg.data = output; 
  p.publish(&str_msg);
//Serial.println("jddcbc");
  nh.spinOnce();
  delay(125);
  

}


#include <ros.h>
#include <std_msgs/String.h>
#include <Wire.h>

#define X_Axis_Register_DATAX0 0x32
#define X_Axis_Register_DATAX1 0x33 
#define Power_Register 0x2D

int ADXLAddress = 0x53; 
 ros::NodeHandle nh;
   
  std_msgs::String str_msg;
  ros::Publisher p("acc", &str_msg);
  

int x,y,z;
byte b[6];
char output[10];





void setup() {
  Wire.begin(); 
  Serial.begin(57600);
  delay(100);
  
  
  Wire.beginTransmission(ADXLAddress);

  Wire.write(Power_Register);
  Wire.write(0);
   Wire.endTransmission();
    
  Wire.beginTransmission(ADXLAddress);

  Wire.write(Power_Register);
  Wire.write(16);
   Wire.endTransmission();
  
   Wire.beginTransmission(ADXLAddress);

  Wire.write(Power_Register);
  Wire.write(8);
   Wire.endTransmission();
   
   nh.initNode();
   nh.advertise(p);
}
void loop() {
  
  Wire.beginTransmission(ADXLAddress); 
  
  Wire.write(X_Axis_Register_DATAX0);
  
  
  Wire.endTransmission(); 
  Wire.beginTransmission(ADXLAddress);
  Wire.requestFrom(ADXLAddress,6); 
  int j=0;
  while(Wire.available()) 
  {  
    b[j]=Wire.read();
    j++;
       
  }
   Wire.endTransmission(); 
   x=(((int)b[1])<<8) |  b[0]; 
   y=(((int)b[3])<<8) |  b[2];
   z=(((int)b[5])<<8) |  b[4];
   Serial.print(x);
 
  sprintf(output," %d %d %d",x,y,z);
  
  str_msg.data = output;
   p.publish( &str_msg );
   nh.spinOnce();
   delay(1000);
  
}

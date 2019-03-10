#include "ros/ros.h"
#include "std_msgs/String.h"
//#include <Arduino.h>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("(ax,ay,az)= (%s])", msg->data.c_str());
}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "acc");


  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("acc", 1000, chatterCallback);

  
  ros::spin();

  return 0;
}

cmake_minimum_required(VERSION 2.8.3)
project(acc)

find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
)
#generate_messages(DEPENDENCIES std_msgs)
catkin_package()

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

#rosserial_configure_client(
 # DIRECTORY #firmware
  #TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
#)

#rosserial_add_client_target(firmware hello ALL)
#rosserial_add_client_target(firmware hello-upload)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Generate added messages and services


## Declare a catkin package
catkin_package(
CATKIN_DEPENDS  std_msgs )
#add_message_files(DIRECTORY msg FILES Num.msg)
include_directories( ${catkin_INCLUDE_DIRS})
## Find catkin and any catkin packages
add_executable(acc src/acc1.cpp)
target_link_libraries(acc ${catkin_LIBRARIES})
add_dependencies(acc acc_generate_messages_cpp)

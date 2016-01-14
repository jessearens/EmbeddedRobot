cmake_minimum_required(VERSION 2.8.3)
project(line_follow)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  sensor_msgs
)



catkin_package()


##include_directories(
##  ${catkin_INCLUDE_DIRS}
##)
include_directories(include ${catkin_INCLUDE_DIRS})


## change location to scr/git_repo/src ??
add_executable(linefollower src/linefollower.cpp)
target_link_libraries(linefollower ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)



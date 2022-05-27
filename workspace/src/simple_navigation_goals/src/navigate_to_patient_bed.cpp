#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "sound_play/sound_play.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

std::string path_to_sounds;

int main(int argc, char** argv){
  ros::init(argc, argv, "navigate_to_patient_bed");

  sound_play::SoundClient sc;
  path_to_sounds= "/home/turtlebot/catkin_ws/src/gaitech_edu/src/sounds/";

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //set up frame params (map for absolute position)
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  
  //move towards goal

  //patient bed
  goal.target_pose.pose.position.x = 9.45;
  goal.target_pose.pose.position.y = -0.802828953706;
  goal.target_pose.pose.position.z = 0.0;
  

  //goal.target_pose.pose.position.x = 0.5;

  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = -0.731044000226;
  goal.target_pose.pose.orientation.w = 0.682330323036;


 //ROS_INFO("Sending goal");
 ac.sendGoal(goal);

 ac.waitForResult();

 if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) { 
   //ROS_INFO("Hooray, the base moved to patient bed!");
   sc.playWave(path_to_sounds+"ship_bell.wav");
   std::cout << 1 << std::endl;
   return 1;
 }
 else {
   //ROS_INFO("The base failed to move to goal for some reason");
   std::cout << 0 << std::endl;
   return 0;
 }

}

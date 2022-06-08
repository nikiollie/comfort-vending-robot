#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "sound_play/sound_play.h"

/* 
 * CSE 176A/276D Autonomous Navigation Script
 *
 * This file will specify coordinates for the robot to autonomously 
 * navigate to. After it sets the coordinates, it will send the goal 
 * and wait for the robot to return either a succeeded status or other.
 * If it has a succeeded status (goal reached), the program will output a 1
 * and it will play the selected arrival audio (in this case, a meow sound),
 * otherwise it will return a 0. 
 */

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
  
  //move towards goal: patient bed
  goal.target_pose.pose.position.x = 9.82;
  goal.target_pose.pose.position.y = -0.80;
  goal.target_pose.pose.position.z = 0.0;
  
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = -0.06;
  goal.target_pose.pose.orientation.w = 1.0;

 // sending goal coordinates
 ac.sendGoal(goal);

 // play sound (meow) when robot initially receives goal to indicate 
 // that it will start to autonomously navigate now
 if(ac.getState() == actionlib::SimpleClientGoalState::PENDING) {
   sc.playWave(path_to_sounds+"meow.wav");
 }
 
 ac.waitForResult();

 // check goal state
 if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) { 
   // base successfully moved to goal (patient bed), play sound and output 1
   sc.playWave(path_to_sounds+"meow.wav");
   std::cout << 1 << std::endl;
   return 1;
 }
 else {
   // base failed to move to goal for some reason, output 0
   std::cout << 0 << std::endl;
   return 0;
 }

}

#!/bin/bash

echo "Starting Navigation Script"
exec 2<> /dev/ttyACM0
sleep 1

source /opt/ros/melodic/setup.bash
source /home/turtlebot/catkin_ws/devel/setup.bash

echo "Launching navigation"
xterm -hold -e roslaunch turtlebot_navigation amcl_demo.launch map_file:=/home/turtlebot/turtlebot_custom_maps/final_cse_map.yaml &
sleep 3
xterm -hold -e rosrun sound_play soundplay_node.py &
sleep 1

echo "Starting..."
xterm -e 'rosrun simple_navigation_goals navigate_to_patient_bed > output' &
pid1=$!

wait $pid1
res=$(< output)
echo "$res"

if [ $res -eq 1 ] 
then 
  echo "1" >&2
fi

sleep 10

killall xterm

echo "Done"

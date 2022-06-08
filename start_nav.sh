#!/bin/bash

```
CSE 176A/276D Start Navigation Script

Runs various ROS programs and the main autonomous navigation script. 
Waits until ROS nav script is completed and checks output of program. 
If the goal was successfully reached, the nav script will output a one, 
or a zero if unsuccessful. If the output is a one, this bash script will send
a character to the Serial Monitor, which the Arduino is constantly reading from.
Once the Arduino file successfully reads a single character, it will trigger 
the LED color change and the vending mechanism.
```

echo "Starting Navigation Script"

# Arduino briefly resets when Serial Monitor is accessed so accessing it 
# at the beginning, also sending anything that comes from File Descriptor 2
# to te Serial Monitor (for later use)
exec 2<> /dev/ttyACM0
sleep 1

# read/execute setup scripts
source /opt/ros/melodic/setup.bash
source /home/turtlebot/catkin_ws/devel/setup.bash

# launch navigation/move_base nodes with amcl demo launch file and specified
# final cse map file
echo "Launching navigation"
xterm -hold -e roslaunch turtlebot_navigation amcl_demo.launch map_file:=/home/turtlebot/turtlebot_custom_maps/final_cse_map.yaml &
sleep 3

# launch sound_play node in order to play audio at arrival
xterm -hold -e rosrun sound_play soundplay_node.py &
sleep 1

# run the autonomous navigation script with specified coordinates and redirect 
# the output to a file
echo "Starting..."
xterm -e 'rosrun simple_navigation_goals navigate_to_patient_bed > output' &
pid1=$!

# when that process ends, save the output of the navigation script was
wait $pid1
res=$(< output)
echo "$res"

# if goal was reached (nav script output is 1) then send a character to 
# File Descriptor 2 (Serial Monitor) to trigger arrival alerts/vending 
if [ $res -eq 1 ] 
then 
  echo "1" >&2
fi

# wait until all arrival alerts and vending mechanisms are completed
sleep 10

# end all xterm processes
killall xterm

echo "Done"

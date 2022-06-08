# erica, an emergency room interactive care assistant

## Robot Description
A social robot that greatly reduces the time and energy physicians have to spend retrieving and delivering items for patients. Erica starts at a specified location (inventory cabinet) and when something is ordered for a patient (i.e. blankets, water, snacks, etc), she autonomously drives through the ED into an appropriate location in the patient’s room, and then automatically dispenses the requested item.

## Folder/Files Description
### turtlebot_custom_maps
There are three pairs of files in this directory. We had to map our environment three times to end up with one that was accurate and usable. `final_cse_map.pgm` and `final_cse_map.yaml` are the final versions of the map we ended up using.

### workspace
This represents the main workspace that is present on the onboard Turtlebot laptop (`catkin_ws`). However, we did not include any of the required library directories or other directories that were present, only the ROS programs we were actively running. In `workspace/src/simple_navigation_goals/src`, there are two files: `simple_navigation_goals.cpp` and `navigate_to_patient_bed.cpp`. The first file is based on the [SendingSimpleGoals ROS demo](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals), and the second file is one we used and ran for our project. It was copied from the demo file and modified with the following: custom coordinates (to the patient bed), the ability to play a sound at arrival (when goal is reached), and outputting a 0 or 1 (failure/success) of reaching the specified destination. 

### start_nav.sh
This is the startup automation and systems integration bash script. It launches the ROS navigation/move_base nodes with the specified `final_cse_map.yaml` from `turtlebot_custom_maps` and it launches sound_play in order to play audio later on at arrival. Finally, it runs the `navigate_to_patiend_bed` executable (file described above), redirects the output (0 or 1) to a file and saves this output in a bash scripting variable, and finally checks the variable value. If the goal was reached (and the output was 1), then it will send a character to the Serial Monitor in order to trigger the arrival alerts and vending (this is the method of communication between ROS and the Arduino). 

### arduino_files/Arrival_Script
This directory contains the file `Arrival_Script.ino`. This file is constantly reading from the Serial Monitor and checking for characters. As mentioned above, a character is only sent to the Serial Monitor from the `start_nav.sh` script when the robot successfully reaches its goal (when a 1 is output from the ROS program). When a character is then read from the Serial Monitor, this triggers the LEDs to change from blue to green and then starts the vending mechanism. 


## Running Program
* Unplug laptop charger
* Unplug turtlebot charger
* Place laptop on 2nd turtlebot plate and make sure necessary Turtlebot wires are plugged into laptop 
* Make sure necessary hardware (Arduino) is plugged into laptop. Servo should be attached to 5V power, Ground and Pin 10. The LED strip should be attached to 5V power, Ground, and Pin 9. 
* Turn on robot 
* Open Turtlebot laptop and login
* Make sure it's connected to UCSD protected
* Startup (only once): Follow instructions on [this Turtlebot Setup and Getting Started document](https://drive.google.com/file/d/1cM2zzCN2VDH9mN9XzmuOr9Q5l0cgQ_ZY/view?usp=sharing) about checking the IP address, `.bashrc` file, and running the following two commands: `roscore` and `roslaunch turtlebot_bringup minimal.launch`
* After these two commands are successfully running, then `cd catkin_ws` and `catkin_make`

* Make sure robot has enough space to move + not collide with anything and nothing is blocking sensors
* (in `catkin_ws` directory) Type `./start_nav.sh` 
* This will automatically start the program and will automatically close when it finished successfully or unsuccessfully so you can run it again to test again once the program finishes (just make sure it's in position again!)

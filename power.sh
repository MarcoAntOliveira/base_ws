#!/bin/bash

. up

connect_ps4
terminator --working-directory=/home/marcos/projects/base_ws/ -e "bash -i -c '. up && ros2 launch robot_pkg joy_launch.py; exec bash'"

fox 

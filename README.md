[![Udacity - Robotics NanoDegree Program](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](https://www.udacity.com/robotics)
# Go Chase IT
**The goal of this project is to design and build a mobile robot that is capable of chasing and following white colored balls.**

![Chase_the_ball](/images/chase_the_ball.gif)

# Project Setup

**First, install Gazebo and ROS on Linux.
Then, create a catkin workspace with a src/ directory and initialize the workspace:**
```  
$ mkdir -p catkin_ws/src
$ cd catkin_ws/src
$ catkin_init_workspace
```

**Next, download the packages within this repository called 'my_robot' and 'ball_chaser':**
`
$ download Go_Chase_it.zip package
`
**Then, build the packages:**
```
$ cd ..
`$ catkin_make
```
**To open gazebo with the robot in it:**
```
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```
**Finally, start the ball_chaser nodes in another terminal so that the robot can start following the white ball:**
```$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```

**Now, when the white ball is moved within view of the front-facing camera on the robot, the robot will begin to chase the white ball.**

## Directory Structure
```
Go-Chase-It               `            # Go Chase It Project
    ├── my_robot                       # my_robot package
    │   ├── launch                     # launch folder for launch files
    │   │   ├── robot_description.launch
    │   │   ├── world.launch
    │   ├── meshes                     # meshes folder for sensors
    │   │   ├── hokuyo.dae
    │   ├── urdf                       # urdf folder for xarco files
    │   │   ├── rc_robot.gazebo
    │   │   ├── rc_robot.xacro
    │   ├── world                      # world folder for world files
    │   │   ├── <yourworld>.world
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
    ├── ball_chaser                    # ball_chaser package
    │   ├── launch                     # launch folder for launch files
    │   │   ├── ball_chaser.launch
    │   ├── src                        # source folder for C++ scripts
    │   │   ├── drive_bot.cpp
    │   │   ├── process_images.cpp
    │   ├── srv                        # service folder for ROS services
    │   │   ├── DriveToTarget.srv
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
    └──
```

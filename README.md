# map-fusion

# Clone the repository into catkin workspace
```
git clone https://github.com/wesnjazz/map-fusion.git
move mapping_simulator ~/catkin_ws/src/
move gui /~catkin_ws/src/
```

# Install CImg
```
sudo apt-get update -y
sudo apt-get install -y cimg-dev
```


# HiTL-SLAM Gui tool install
```
https://github.com/ut-amrl/hitl-slam
dependencies:
$ sudo apt-get install g++ cmake libpopt-dev cimg-dev libncurses5-dev libglew-dev lua5.1 lua5.1-policy-dev
For compiling the ROS wrapper, rosbuild is used. rosbuild requires the path of the ROS wrapper to be added to the ROS_PACKAGE_PATH environment variable. To do this, add the following line in your .bashrc file.
$ export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/catkin_ws/src/gui/gui:~/catkin_ws/src/gui/vector_slam_msgs
```

# install dependencies (if needed)
```
https://anaconda.org/conda-forge/rospkg
conda install -c conda-forge rospkg
conda install -c conda-forge catkin_pkg
conda install -c conda-forge rosdep
conda install -c conda-forge glog
sudo apt-get install -y libgoogle-glog-dev
```


# QT version (if qt4 is not the default version)
```
sudo apt-get install qt4-default
```

# CMake
```
cd ~/catkin_ws
catkin_make
```

# How to run
```
rosrun mapping_simulator mapping_simulator_node [map file] [waypoints file] [speed] [delta_t] [origin]
ex) rosrun mapping_simulator mapping_simulator_node map01.txt waypoints01.txt 0.6 0.2 robot_frame01.txt
```

# Debug using GDB
```
catkin_make -DCMAKE_BUILD_TYPE=Debug
rosrun --prefix 'gdb --args' mapping_simulator mapping_simulator_node [map file] [waypoints file] [speed] [delta_t] [origin]
```

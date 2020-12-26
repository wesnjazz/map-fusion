# A Priori Map Alignment for Map Fusion (UMass Robotics Independent Study Research)
This project is a part of a research which is to produce a single accurate map by fusing multiple inaccurate maps generated from SLAM algotihm. 
The research is consist of three phases.
  1. Creating a simple 2D simulator to generate environment maps.
  2. Aligining collection of impoerfect maps.
  3. Fusing maps to produce a single highly accurate map.
This project will be done up to phase 1 and 2.

# Clone the repository into catkin workspace
For developer (Me)
```
1. Put git repository into catkin/src
  - go to ~/catkin_ws/src
  - backup current projects in src in catkin workspace
  - remove current projects in src in catkin workspace
  - go to ~/catkin_ws
  - git clone https://github.com/wesnjazz/map-fusion.git
  - mv map-fusion src (change map-fusion repository as src)
  - restore backupped projects into catkin workspace src folder
  - remove CMakeLists.txt in ~/catkin_ws/src
```

For others
```
go to your catkin workspace (catkin_ws)
cd ~/catkin_ws
git clone https://github.com/wesnjazz/map-fusion.git
cd map-fusion
move mapping_simulator ~/catkin_ws/src/
move gui /~catkin_ws/src/
```

# Install CImg
```
sudo apt-get update -y
sudo apt-get install -y cimg-dev
```


# HiTL-SLAM Gui tool install

https://github.com/ut-amrl/hitl-slam
dependencies:
```
$ sudo apt-get install g++ cmake libpopt-dev cimg-dev libncurses5-dev libglew-dev lua5.1 lua5.1-policy-dev
```

For compiling the ROS wrapper, rosbuild is used. rosbuild requires the path of the ROS wrapper to be added to the ROS_PACKAGE_PATH environment variable. To do this, add the following line in your .bashrc file.
```
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/catkin_ws/src/gui/gui:~/catkin_ws/src/gui/vector_slam_msgs
```

```
$ cd ~/catkin_ws/src/gui/vector_slam_msgs/
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd ~/catkin_ws/src/gui/gui/
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# install dependencies (if needed)
```
https://anaconda.org/conda-forge/rospkg
conda install -c conda-forge rospkg
conda install -c conda-forge catkin_pkg
conda install -c conda-forge rosdep
conda install -c conda-forge glog
sudo apt-get install -y libgoogle-glog-dev
sudo apt-get install libcanberra-gtk-module
```


# QT version (if qt4 is not the default version)
```
sudo apt-get install qt4-default
```

# catkin_make
```
cd ~/catkin_ws
catkin_make
```

# How to run HiTL-SLAM Gui tool
In a terminal, run roscore
```
roscore
```
In another terminal, run the gui tool using rosrun
```
rosrun gui localization_gui
```

# How to run the simulator
```
rosrun mapping_simulator mapping_simulator_node [map file] [waypoints file] [speed] [delta_t] [origin]
ex) rosrun mapping_simulator mapping_simulator_node map01.txt waypoints01.txt 0.6 0.2 robot_frame01.txt
```

# Debug using GDB
```
catkin_make -DCMAKE_BUILD_TYPE=Debug
rosrun --prefix 'gdb --args' mapping_simulator mapping_simulator_node [map file] [waypoints file] [speed] [delta_t] [origin]
```

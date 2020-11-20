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

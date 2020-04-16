# map-fusion

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

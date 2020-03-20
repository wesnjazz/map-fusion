# map-fusion

# How to run
```
rosrun mapping_simulator mapping_simulator_node [map file] [waypoints file] [speed] [delta_t]
ex) rosrun mapping_simulator mapping_simulator_node map01.txt waypoints01.txt 0.6 0.2
```

# Debug using GDB
```
rosrun --prefix 'gdb --args' mapping_simulator mapping_simulator_node [map file] [waypoints file] [speed] [delta_t]
```

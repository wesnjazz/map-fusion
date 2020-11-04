file(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/vector_slam_msgs/msg"
  "../src/vector_slam_msgs/srv"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/vector_slam_msgs/msg/__init__.py"
  "../src/vector_slam_msgs/msg/_CobotAnomalyMonitorMsg.py"
  "../src/vector_slam_msgs/msg/_CobotAnomalyMonitorRectangleMsg.py"
  "../src/vector_slam_msgs/msg/_CobotCameraMsg.py"
  "../src/vector_slam_msgs/msg/_CobotEventsMsg.py"
  "../src/vector_slam_msgs/msg/_CobotLocalization3DMsg.py"
  "../src/vector_slam_msgs/msg/_CobotLocalizationMsg.py"
  "../src/vector_slam_msgs/msg/_CobotOdometryMsg.py"
  "../src/vector_slam_msgs/msg/_CobotStatusMsg.py"
  "../src/vector_slam_msgs/msg/_GuiKeyboardEvent.py"
  "../src/vector_slam_msgs/msg/_GuiMouseClickEvent.py"
  "../src/vector_slam_msgs/msg/_GuiMouseMoveEvent.py"
  "../src/vector_slam_msgs/msg/_LidarDisplayMsg.py"
  "../src/vector_slam_msgs/msg/_LocalizationMsg.py"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

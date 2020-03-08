file(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/vector_slam_msgs/msg"
  "../src/vector_slam_msgs/srv"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/vector_slam_msgs/srv/__init__.py"
  "../src/vector_slam_msgs/srv/_CobotLocalizationSrv.py"
  "../src/vector_slam_msgs/srv/_CobotRemoteInterfaceSrv.py"
  "../src/vector_slam_msgs/srv/_LocalizationGuiCaptureSrv.py"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

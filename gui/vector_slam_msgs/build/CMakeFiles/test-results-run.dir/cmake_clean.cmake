file(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/vector_slam_msgs/msg"
  "../src/vector_slam_msgs/srv"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/test-results-run.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

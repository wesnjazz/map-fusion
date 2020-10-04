cmake_minimum_required(VERSION 2.8)
project( opencv02 )
find_package( OpenCV REQUIRED )
include_directories(
  /home/dpark/anaconda3/envs/map-fusion-py38/include/opencv4/opencv2
)
add_executable( opencv02 opencv02.cpp )
target_link_libraries( opencv02 ${OpenCV_LIBS} )

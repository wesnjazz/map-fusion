cmake_minimum_required(VERSION 2.8)
project( opencv01 )
find_package( OpenCV REQUIRED )
include_directories(
  /home/dpark/anaconda3/envs/map-fusion-py38/include/opencv4/opencv2
)
add_executable( opencv01 opencv01.cpp )
target_link_libraries( opencv01 ${OpenCV_LIBS} )

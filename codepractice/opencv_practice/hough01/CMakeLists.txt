cmake_minimum_required(VERSION 2.8)
project( hough03 )
find_package( OpenCV REQUIRED )
include_directories(
  /home/dpark/anaconda3/envs/map-fusion-py38/include/opencv4/opencv2
)
add_executable( hough03 hough03.cpp )
target_link_libraries( hough03 ${OpenCV_LIBS} )

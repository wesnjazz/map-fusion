cmake_minimum_required(VERSION 2.8)
project( opencv01 )
find_package( OpenCV REQUIRED )
add_executable( opencv01 opencv01.cpp )
target_link_libraries( opencv01 ${OpenCV_LIBS} )


# Install script for directory: /home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dpark/map-fusion/catkin_ws_Indep.Study/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visual_feature_server/msg" TYPE FILE FILES
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg"
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg"
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg"
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg"
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visual_feature_server/srv" TYPE FILE FILES
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv"
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visual_feature_server/cmake" TYPE FILE FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/build/visual_feature_server/catkin_generated/installspace/visual_feature_server-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/devel/include/visual_feature_server")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/devel/share/roseus/ros/visual_feature_server")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/devel/share/common-lisp/ros/visual_feature_server")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/devel/share/gennodejs/ros/visual_feature_server")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/dpark/map-fusion/catkin_ws_Indep.Study/devel/lib/python2.7/dist-packages/visual_feature_server")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/devel/lib/python2.7/dist-packages/visual_feature_server")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/build/visual_feature_server/catkin_generated/installspace/visual_feature_server.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visual_feature_server/cmake" TYPE FILE FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/build/visual_feature_server/catkin_generated/installspace/visual_feature_server-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visual_feature_server/cmake" TYPE FILE FILES
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/build/visual_feature_server/catkin_generated/installspace/visual_feature_serverConfig.cmake"
    "/home/dpark/map-fusion/catkin_ws_Indep.Study/build/visual_feature_server/catkin_generated/installspace/visual_feature_serverConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visual_feature_server" TYPE FILE FILES "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/package.xml")
endif()


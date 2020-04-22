# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "visual_feature_server: 5 messages, 2 services")

set(MSG_I_FLAGS "-Ivisual_feature_server:/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(visual_feature_server_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" "geometry_msgs/PoseWithCovarianceStamped:geometry_msgs/Pose:geometry_msgs/PoseWithCovariance:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" "geometry_msgs/PoseWithCovarianceStamped:geometry_msgs/Pose:geometry_msgs/PoseWithCovariance:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" "visual_feature_server/BlobFeatureMsg:geometry_msgs/PoseWithCovarianceStamped:visual_feature_server/CornerFeatureMsg:geometry_msgs/Pose:geometry_msgs/PoseWithCovariance:std_msgs/Header:visual_feature_server/EdgeFeatureMsg:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" "geometry_msgs/PoseWithCovarianceStamped:geometry_msgs/Pose:geometry_msgs/PoseWithCovariance:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" "visual_feature_server/BlobFeatureMsg:geometry_msgs/PoseWithCovarianceStamped:visual_feature_server/CornerFeatureMsg:visual_feature_server/FeatureMsg:geometry_msgs/Pose:geometry_msgs/PoseWithCovariance:std_msgs/Header:visual_feature_server/EdgeFeatureMsg:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" ""
)

get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" NAME_WE)
add_custom_target(_visual_feature_server_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_feature_server" "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)

### Generating Services
_generate_srv_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)
_generate_srv_cpp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
)

### Generating Module File
_generate_module_cpp(visual_feature_server
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(visual_feature_server_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(visual_feature_server_generate_messages visual_feature_server_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_cpp _visual_feature_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_feature_server_gencpp)
add_dependencies(visual_feature_server_gencpp visual_feature_server_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_feature_server_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)
_generate_msg_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)
_generate_msg_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)
_generate_msg_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)
_generate_msg_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)

### Generating Services
_generate_srv_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)
_generate_srv_eus(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
)

### Generating Module File
_generate_module_eus(visual_feature_server
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(visual_feature_server_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(visual_feature_server_generate_messages visual_feature_server_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_eus _visual_feature_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_feature_server_geneus)
add_dependencies(visual_feature_server_geneus visual_feature_server_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_feature_server_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)
_generate_msg_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)

### Generating Services
_generate_srv_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)
_generate_srv_lisp(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
)

### Generating Module File
_generate_module_lisp(visual_feature_server
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(visual_feature_server_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(visual_feature_server_generate_messages visual_feature_server_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_lisp _visual_feature_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_feature_server_genlisp)
add_dependencies(visual_feature_server_genlisp visual_feature_server_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_feature_server_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)
_generate_msg_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)
_generate_msg_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)
_generate_msg_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)
_generate_msg_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)

### Generating Services
_generate_srv_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)
_generate_srv_nodejs(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
)

### Generating Module File
_generate_module_nodejs(visual_feature_server
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(visual_feature_server_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(visual_feature_server_generate_messages visual_feature_server_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_nodejs _visual_feature_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_feature_server_gennodejs)
add_dependencies(visual_feature_server_gennodejs visual_feature_server_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_feature_server_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)
_generate_msg_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)
_generate_msg_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)
_generate_msg_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)
_generate_msg_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovarianceStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)

### Generating Services
_generate_srv_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)
_generate_srv_py(visual_feature_server
  "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
)

### Generating Module File
_generate_module_py(visual_feature_server
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(visual_feature_server_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(visual_feature_server_generate_messages visual_feature_server_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/EdgeFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/CornerFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/BlobFeatureMsg.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/msg/FeaturePoses.msg" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/PickleSrv.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dpark/map-fusion/catkin_ws_Indep.Study/src/visual_feature_server/srv/Convert2DPoint.srv" NAME_WE)
add_dependencies(visual_feature_server_generate_messages_py _visual_feature_server_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_feature_server_genpy)
add_dependencies(visual_feature_server_genpy visual_feature_server_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_feature_server_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_feature_server
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(visual_feature_server_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(visual_feature_server_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_feature_server
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(visual_feature_server_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(visual_feature_server_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_feature_server
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(visual_feature_server_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(visual_feature_server_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_feature_server
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(visual_feature_server_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(visual_feature_server_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_feature_server
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(visual_feature_server_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(visual_feature_server_generate_messages_py std_msgs_generate_messages_py)
endif()

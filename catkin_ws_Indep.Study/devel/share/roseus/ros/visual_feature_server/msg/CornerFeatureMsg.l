;; Auto-generated. Do not edit!


(when (boundp 'visual_feature_server::CornerFeatureMsg)
  (if (not (find-package "VISUAL_FEATURE_SERVER"))
    (make-package "VISUAL_FEATURE_SERVER"))
  (shadow 'CornerFeatureMsg (find-package "VISUAL_FEATURE_SERVER")))
(unless (find-package "VISUAL_FEATURE_SERVER::CORNERFEATUREMSG")
  (make-package "VISUAL_FEATURE_SERVER::CORNERFEATUREMSG"))

(in-package "ROS")
;;//! \htmlinclude CornerFeatureMsg.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass visual_feature_server::CornerFeatureMsg
  :super ros::object
  :slots (_threshold _centroid ))

(defmethod visual_feature_server::CornerFeatureMsg
  (:init
   (&key
    ((:threshold __threshold) 0)
    ((:centroid __centroid) (instance geometry_msgs::PoseWithCovarianceStamped :init))
    )
   (send-super :init)
   (setq _threshold (round __threshold))
   (setq _centroid __centroid)
   self)
  (:threshold
   (&optional __threshold)
   (if __threshold (setq _threshold __threshold)) _threshold)
  (:centroid
   (&rest __centroid)
   (if (keywordp (car __centroid))
       (send* _centroid __centroid)
     (progn
       (if __centroid (setq _centroid (car __centroid)))
       _centroid)))
  (:serialization-length
   ()
   (+
    ;; uint8 _threshold
    1
    ;; geometry_msgs/PoseWithCovarianceStamped _centroid
    (send _centroid :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _threshold
       (write-byte _threshold s)
     ;; geometry_msgs/PoseWithCovarianceStamped _centroid
       (send _centroid :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _threshold
     (setq _threshold (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; geometry_msgs/PoseWithCovarianceStamped _centroid
     (send _centroid :deserialize buf ptr-) (incf ptr- (send _centroid :serialization-length))
   ;;
   self)
  )

(setf (get visual_feature_server::CornerFeatureMsg :md5sum-) "f86d11aa7264d820fbf8de0199829dfe")
(setf (get visual_feature_server::CornerFeatureMsg :datatype-) "visual_feature_server/CornerFeatureMsg")
(setf (get visual_feature_server::CornerFeatureMsg :definition-)
      "uint8 threshold
#uint8 scale

geometry_msgs/PoseWithCovarianceStamped centroid

================================================================================
MSG: geometry_msgs/PoseWithCovarianceStamped
# This expresses an estimated pose with a reference coordinate frame and timestamp

Header header
PoseWithCovariance pose

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/PoseWithCovariance
# This represents a pose in free space with uncertainty.

Pose pose

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :visual_feature_server/CornerFeatureMsg "f86d11aa7264d820fbf8de0199829dfe")



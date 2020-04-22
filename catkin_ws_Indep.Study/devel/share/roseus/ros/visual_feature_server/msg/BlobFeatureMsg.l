;; Auto-generated. Do not edit!


(when (boundp 'visual_feature_server::BlobFeatureMsg)
  (if (not (find-package "VISUAL_FEATURE_SERVER"))
    (make-package "VISUAL_FEATURE_SERVER"))
  (shadow 'BlobFeatureMsg (find-package "VISUAL_FEATURE_SERVER")))
(unless (find-package "VISUAL_FEATURE_SERVER::BLOBFEATUREMSG")
  (make-package "VISUAL_FEATURE_SERVER::BLOBFEATUREMSG"))

(in-package "ROS")
;;//! \htmlinclude BlobFeatureMsg.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass visual_feature_server::BlobFeatureMsg
  :super ros::object
  :slots (_hHigh _sHigh _vHigh _hLow _sLow _vLow _threshold _centroid ))

(defmethod visual_feature_server::BlobFeatureMsg
  (:init
   (&key
    ((:hHigh __hHigh) 0)
    ((:sHigh __sHigh) 0)
    ((:vHigh __vHigh) 0)
    ((:hLow __hLow) 0)
    ((:sLow __sLow) 0)
    ((:vLow __vLow) 0)
    ((:threshold __threshold) 0)
    ((:centroid __centroid) (instance geometry_msgs::PoseWithCovarianceStamped :init))
    )
   (send-super :init)
   (setq _hHigh (round __hHigh))
   (setq _sHigh (round __sHigh))
   (setq _vHigh (round __vHigh))
   (setq _hLow (round __hLow))
   (setq _sLow (round __sLow))
   (setq _vLow (round __vLow))
   (setq _threshold (round __threshold))
   (setq _centroid __centroid)
   self)
  (:hHigh
   (&optional __hHigh)
   (if __hHigh (setq _hHigh __hHigh)) _hHigh)
  (:sHigh
   (&optional __sHigh)
   (if __sHigh (setq _sHigh __sHigh)) _sHigh)
  (:vHigh
   (&optional __vHigh)
   (if __vHigh (setq _vHigh __vHigh)) _vHigh)
  (:hLow
   (&optional __hLow)
   (if __hLow (setq _hLow __hLow)) _hLow)
  (:sLow
   (&optional __sLow)
   (if __sLow (setq _sLow __sLow)) _sLow)
  (:vLow
   (&optional __vLow)
   (if __vLow (setq _vLow __vLow)) _vLow)
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
    ;; uint8 _hHigh
    1
    ;; uint8 _sHigh
    1
    ;; uint8 _vHigh
    1
    ;; uint8 _hLow
    1
    ;; uint8 _sLow
    1
    ;; uint8 _vLow
    1
    ;; uint8 _threshold
    1
    ;; geometry_msgs/PoseWithCovarianceStamped _centroid
    (send _centroid :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _hHigh
       (write-byte _hHigh s)
     ;; uint8 _sHigh
       (write-byte _sHigh s)
     ;; uint8 _vHigh
       (write-byte _vHigh s)
     ;; uint8 _hLow
       (write-byte _hLow s)
     ;; uint8 _sLow
       (write-byte _sLow s)
     ;; uint8 _vLow
       (write-byte _vLow s)
     ;; uint8 _threshold
       (write-byte _threshold s)
     ;; geometry_msgs/PoseWithCovarianceStamped _centroid
       (send _centroid :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _hHigh
     (setq _hHigh (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sHigh
     (setq _sHigh (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _vHigh
     (setq _vHigh (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hLow
     (setq _hLow (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sLow
     (setq _sLow (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _vLow
     (setq _vLow (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _threshold
     (setq _threshold (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; geometry_msgs/PoseWithCovarianceStamped _centroid
     (send _centroid :deserialize buf ptr-) (incf ptr- (send _centroid :serialization-length))
   ;;
   self)
  )

(setf (get visual_feature_server::BlobFeatureMsg :md5sum-) "c25be8f3f0fd93ffc579284ad0e9abf8")
(setf (get visual_feature_server::BlobFeatureMsg :datatype-) "visual_feature_server/BlobFeatureMsg")
(setf (get visual_feature_server::BlobFeatureMsg :definition-)
      "uint8 hHigh
uint8 sHigh
uint8 vHigh
uint8 hLow
uint8 sLow
uint8 vLow
#uint8 scale
uint8 threshold

#pose of the feature
geometry_msgs/PoseWithCovarianceStamped centroid
#geometry_msgs/PoseWithCovarianceStamped top_left
#geometry_msgs/PoseWithCovarianceStamped top_right
#geometry_msgs/PoseWithCovarianceStamped bottom_left
#geometry_msgs/PoseWithCovarianceStamped bottom_right

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



(provide :visual_feature_server/BlobFeatureMsg "c25be8f3f0fd93ffc579284ad0e9abf8")



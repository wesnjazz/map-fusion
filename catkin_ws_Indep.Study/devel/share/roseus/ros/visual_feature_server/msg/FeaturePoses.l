;; Auto-generated. Do not edit!


(when (boundp 'visual_feature_server::FeaturePoses)
  (if (not (find-package "VISUAL_FEATURE_SERVER"))
    (make-package "VISUAL_FEATURE_SERVER"))
  (shadow 'FeaturePoses (find-package "VISUAL_FEATURE_SERVER")))
(unless (find-package "VISUAL_FEATURE_SERVER::FEATUREPOSES")
  (make-package "VISUAL_FEATURE_SERVER::FEATUREPOSES"))

(in-package "ROS")
;;//! \htmlinclude FeaturePoses.msg.html


(defclass visual_feature_server::FeaturePoses
  :super ros::object
  :slots (_stamp _features ))

(defmethod visual_feature_server::FeaturePoses
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:features __features) (let (r) (dotimes (i 0) (push (instance visual_feature_server::FeatureMsg :init) r)) r))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _features __features)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:features
   (&rest __features)
   (if (keywordp (car __features))
       (send* _features __features)
     (progn
       (if __features (setq _features (car __features)))
       _features)))
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; visual_feature_server/FeatureMsg[] _features
    (apply #'+ (send-all _features :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; visual_feature_server/FeatureMsg[] _features
     (write-long (length _features) s)
     (dolist (elem _features)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; visual_feature_server/FeatureMsg[] _features
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _features (let (r) (dotimes (i n) (push (instance visual_feature_server::FeatureMsg :init) r)) r))
     (dolist (elem- _features)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get visual_feature_server::FeaturePoses :md5sum-) "8329d4cd40eb21004182798fbd3b3cb5")
(setf (get visual_feature_server::FeaturePoses :datatype-) "visual_feature_server/FeaturePoses")
(setf (get visual_feature_server::FeaturePoses :definition-)
      "time stamp

FeatureMsg[] features

================================================================================
MSG: visual_feature_server/FeatureMsg
uint8 CORNER=1
uint8 BLOB=2
uint8 EDGE=3
string CORNER_STR=\"corner\"
string BLOB_STR=\"blob\"
string EDGE_STR=\"edge\"

string name
int32 type

float32 image_scale
float32 world_scale

BlobFeatureMsg blobFeature
CornerFeatureMsg cornerFeature
EdgeFeatureMsg edgeFeature

#recognition confidence
float32 confidence
int32 x_pixel
int32 y_pixel

================================================================================
MSG: visual_feature_server/BlobFeatureMsg
uint8 hHigh
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

================================================================================
MSG: visual_feature_server/CornerFeatureMsg
uint8 threshold
#uint8 scale

geometry_msgs/PoseWithCovarianceStamped centroid

================================================================================
MSG: visual_feature_server/EdgeFeatureMsg
uint8 threshold
#uint8 scale

# geometry_msgs/PoseWithCovarianceStamped p1
# geometry_msgs/PoseWithCovarianceStamped p2
geometry_msgs/PoseWithCovarianceStamped centroid

")



(provide :visual_feature_server/FeaturePoses "8329d4cd40eb21004182798fbd3b3cb5")



;; Auto-generated. Do not edit!


(when (boundp 'visual_feature_server::FeatureMsg)
  (if (not (find-package "VISUAL_FEATURE_SERVER"))
    (make-package "VISUAL_FEATURE_SERVER"))
  (shadow 'FeatureMsg (find-package "VISUAL_FEATURE_SERVER")))
(unless (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG")
  (make-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))

(in-package "ROS")
;;//! \htmlinclude FeatureMsg.msg.html


(intern "*CORNER*" (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(shadow '*CORNER* (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(defconstant visual_feature_server::FeatureMsg::*CORNER* 1)
(intern "*BLOB*" (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(shadow '*BLOB* (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(defconstant visual_feature_server::FeatureMsg::*BLOB* 2)
(intern "*EDGE*" (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(shadow '*EDGE* (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(defconstant visual_feature_server::FeatureMsg::*EDGE* 3)
(intern "*CORNER_STR*" (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(shadow '*CORNER_STR* (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(defconstant visual_feature_server::FeatureMsg::*CORNER_STR* "\"corner\"")
(intern "*BLOB_STR*" (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(shadow '*BLOB_STR* (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(defconstant visual_feature_server::FeatureMsg::*BLOB_STR* "\"blob\"")
(intern "*EDGE_STR*" (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(shadow '*EDGE_STR* (find-package "VISUAL_FEATURE_SERVER::FEATUREMSG"))
(defconstant visual_feature_server::FeatureMsg::*EDGE_STR* "\"edge\"")
(defclass visual_feature_server::FeatureMsg
  :super ros::object
  :slots (_name _type _image_scale _world_scale _blobFeature _cornerFeature _edgeFeature _confidence _x_pixel _y_pixel ))

(defmethod visual_feature_server::FeatureMsg
  (:init
   (&key
    ((:name __name) "")
    ((:type __type) 0)
    ((:image_scale __image_scale) 0.0)
    ((:world_scale __world_scale) 0.0)
    ((:blobFeature __blobFeature) (instance visual_feature_server::BlobFeatureMsg :init))
    ((:cornerFeature __cornerFeature) (instance visual_feature_server::CornerFeatureMsg :init))
    ((:edgeFeature __edgeFeature) (instance visual_feature_server::EdgeFeatureMsg :init))
    ((:confidence __confidence) 0.0)
    ((:x_pixel __x_pixel) 0)
    ((:y_pixel __y_pixel) 0)
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _type (round __type))
   (setq _image_scale (float __image_scale))
   (setq _world_scale (float __world_scale))
   (setq _blobFeature __blobFeature)
   (setq _cornerFeature __cornerFeature)
   (setq _edgeFeature __edgeFeature)
   (setq _confidence (float __confidence))
   (setq _x_pixel (round __x_pixel))
   (setq _y_pixel (round __y_pixel))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:image_scale
   (&optional __image_scale)
   (if __image_scale (setq _image_scale __image_scale)) _image_scale)
  (:world_scale
   (&optional __world_scale)
   (if __world_scale (setq _world_scale __world_scale)) _world_scale)
  (:blobFeature
   (&rest __blobFeature)
   (if (keywordp (car __blobFeature))
       (send* _blobFeature __blobFeature)
     (progn
       (if __blobFeature (setq _blobFeature (car __blobFeature)))
       _blobFeature)))
  (:cornerFeature
   (&rest __cornerFeature)
   (if (keywordp (car __cornerFeature))
       (send* _cornerFeature __cornerFeature)
     (progn
       (if __cornerFeature (setq _cornerFeature (car __cornerFeature)))
       _cornerFeature)))
  (:edgeFeature
   (&rest __edgeFeature)
   (if (keywordp (car __edgeFeature))
       (send* _edgeFeature __edgeFeature)
     (progn
       (if __edgeFeature (setq _edgeFeature (car __edgeFeature)))
       _edgeFeature)))
  (:confidence
   (&optional __confidence)
   (if __confidence (setq _confidence __confidence)) _confidence)
  (:x_pixel
   (&optional __x_pixel)
   (if __x_pixel (setq _x_pixel __x_pixel)) _x_pixel)
  (:y_pixel
   (&optional __y_pixel)
   (if __y_pixel (setq _y_pixel __y_pixel)) _y_pixel)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; int32 _type
    4
    ;; float32 _image_scale
    4
    ;; float32 _world_scale
    4
    ;; visual_feature_server/BlobFeatureMsg _blobFeature
    (send _blobFeature :serialization-length)
    ;; visual_feature_server/CornerFeatureMsg _cornerFeature
    (send _cornerFeature :serialization-length)
    ;; visual_feature_server/EdgeFeatureMsg _edgeFeature
    (send _edgeFeature :serialization-length)
    ;; float32 _confidence
    4
    ;; int32 _x_pixel
    4
    ;; int32 _y_pixel
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; int32 _type
       (write-long _type s)
     ;; float32 _image_scale
       (sys::poke _image_scale (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _world_scale
       (sys::poke _world_scale (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; visual_feature_server/BlobFeatureMsg _blobFeature
       (send _blobFeature :serialize s)
     ;; visual_feature_server/CornerFeatureMsg _cornerFeature
       (send _cornerFeature :serialize s)
     ;; visual_feature_server/EdgeFeatureMsg _edgeFeature
       (send _edgeFeature :serialize s)
     ;; float32 _confidence
       (sys::poke _confidence (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _x_pixel
       (write-long _x_pixel s)
     ;; int32 _y_pixel
       (write-long _y_pixel s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _type
     (setq _type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _image_scale
     (setq _image_scale (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _world_scale
     (setq _world_scale (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; visual_feature_server/BlobFeatureMsg _blobFeature
     (send _blobFeature :deserialize buf ptr-) (incf ptr- (send _blobFeature :serialization-length))
   ;; visual_feature_server/CornerFeatureMsg _cornerFeature
     (send _cornerFeature :deserialize buf ptr-) (incf ptr- (send _cornerFeature :serialization-length))
   ;; visual_feature_server/EdgeFeatureMsg _edgeFeature
     (send _edgeFeature :deserialize buf ptr-) (incf ptr- (send _edgeFeature :serialization-length))
   ;; float32 _confidence
     (setq _confidence (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _x_pixel
     (setq _x_pixel (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _y_pixel
     (setq _y_pixel (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get visual_feature_server::FeatureMsg :md5sum-) "93ea47ac84f852fc7e6fbfcdf7865fee")
(setf (get visual_feature_server::FeatureMsg :datatype-) "visual_feature_server/FeatureMsg")
(setf (get visual_feature_server::FeatureMsg :definition-)
      "uint8 CORNER=1
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



(provide :visual_feature_server/FeatureMsg "93ea47ac84f852fc7e6fbfcdf7865fee")



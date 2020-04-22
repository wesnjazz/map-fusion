; Auto-generated. Do not edit!


(cl:in-package visual_feature_server-msg)


;//! \htmlinclude FeaturePoses.msg.html

(cl:defclass <FeaturePoses> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (features
    :reader features
    :initarg :features
    :type (cl:vector visual_feature_server-msg:FeatureMsg)
   :initform (cl:make-array 0 :element-type 'visual_feature_server-msg:FeatureMsg :initial-element (cl:make-instance 'visual_feature_server-msg:FeatureMsg))))
)

(cl:defclass FeaturePoses (<FeaturePoses>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FeaturePoses>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FeaturePoses)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_feature_server-msg:<FeaturePoses> is deprecated: use visual_feature_server-msg:FeaturePoses instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <FeaturePoses>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:stamp-val is deprecated.  Use visual_feature_server-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'features-val :lambda-list '(m))
(cl:defmethod features-val ((m <FeaturePoses>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:features-val is deprecated.  Use visual_feature_server-msg:features instead.")
  (features m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FeaturePoses>) ostream)
  "Serializes a message object of type '<FeaturePoses>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'features))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'features))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FeaturePoses>) istream)
  "Deserializes a message object of type '<FeaturePoses>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'features) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'features)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'visual_feature_server-msg:FeatureMsg))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FeaturePoses>)))
  "Returns string type for a message object of type '<FeaturePoses>"
  "visual_feature_server/FeaturePoses")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FeaturePoses)))
  "Returns string type for a message object of type 'FeaturePoses"
  "visual_feature_server/FeaturePoses")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FeaturePoses>)))
  "Returns md5sum for a message object of type '<FeaturePoses>"
  "8329d4cd40eb21004182798fbd3b3cb5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FeaturePoses)))
  "Returns md5sum for a message object of type 'FeaturePoses"
  "8329d4cd40eb21004182798fbd3b3cb5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FeaturePoses>)))
  "Returns full string definition for message of type '<FeaturePoses>"
  (cl:format cl:nil "time stamp~%~%FeatureMsg[] features~%~%================================================================================~%MSG: visual_feature_server/FeatureMsg~%uint8 CORNER=1~%uint8 BLOB=2~%uint8 EDGE=3~%string CORNER_STR=\"corner\"~%string BLOB_STR=\"blob\"~%string EDGE_STR=\"edge\"~%~%string name~%int32 type~%~%float32 image_scale~%float32 world_scale~%~%BlobFeatureMsg blobFeature~%CornerFeatureMsg cornerFeature~%EdgeFeatureMsg edgeFeature~%~%#recognition confidence~%float32 confidence~%int32 x_pixel~%int32 y_pixel~%~%================================================================================~%MSG: visual_feature_server/BlobFeatureMsg~%uint8 hHigh~%uint8 sHigh~%uint8 vHigh~%uint8 hLow~%uint8 sLow~%uint8 vLow~%#uint8 scale~%uint8 threshold~%~%#pose of the feature~%geometry_msgs/PoseWithCovarianceStamped centroid~%#geometry_msgs/PoseWithCovarianceStamped top_left~%#geometry_msgs/PoseWithCovarianceStamped top_right~%#geometry_msgs/PoseWithCovarianceStamped bottom_left~%#geometry_msgs/PoseWithCovarianceStamped bottom_right~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: visual_feature_server/CornerFeatureMsg~%uint8 threshold~%#uint8 scale~%~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%================================================================================~%MSG: visual_feature_server/EdgeFeatureMsg~%uint8 threshold~%#uint8 scale~%~%# geometry_msgs/PoseWithCovarianceStamped p1~%# geometry_msgs/PoseWithCovarianceStamped p2~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FeaturePoses)))
  "Returns full string definition for message of type 'FeaturePoses"
  (cl:format cl:nil "time stamp~%~%FeatureMsg[] features~%~%================================================================================~%MSG: visual_feature_server/FeatureMsg~%uint8 CORNER=1~%uint8 BLOB=2~%uint8 EDGE=3~%string CORNER_STR=\"corner\"~%string BLOB_STR=\"blob\"~%string EDGE_STR=\"edge\"~%~%string name~%int32 type~%~%float32 image_scale~%float32 world_scale~%~%BlobFeatureMsg blobFeature~%CornerFeatureMsg cornerFeature~%EdgeFeatureMsg edgeFeature~%~%#recognition confidence~%float32 confidence~%int32 x_pixel~%int32 y_pixel~%~%================================================================================~%MSG: visual_feature_server/BlobFeatureMsg~%uint8 hHigh~%uint8 sHigh~%uint8 vHigh~%uint8 hLow~%uint8 sLow~%uint8 vLow~%#uint8 scale~%uint8 threshold~%~%#pose of the feature~%geometry_msgs/PoseWithCovarianceStamped centroid~%#geometry_msgs/PoseWithCovarianceStamped top_left~%#geometry_msgs/PoseWithCovarianceStamped top_right~%#geometry_msgs/PoseWithCovarianceStamped bottom_left~%#geometry_msgs/PoseWithCovarianceStamped bottom_right~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: visual_feature_server/CornerFeatureMsg~%uint8 threshold~%#uint8 scale~%~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%================================================================================~%MSG: visual_feature_server/EdgeFeatureMsg~%uint8 threshold~%#uint8 scale~%~%# geometry_msgs/PoseWithCovarianceStamped p1~%# geometry_msgs/PoseWithCovarianceStamped p2~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FeaturePoses>))
  (cl:+ 0
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'features) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FeaturePoses>))
  "Converts a ROS message object to a list"
  (cl:list 'FeaturePoses
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':features (features msg))
))

; Auto-generated. Do not edit!


(cl:in-package visual_feature_server-msg)


;//! \htmlinclude BlobFeatureMsg.msg.html

(cl:defclass <BlobFeatureMsg> (roslisp-msg-protocol:ros-message)
  ((hHigh
    :reader hHigh
    :initarg :hHigh
    :type cl:fixnum
    :initform 0)
   (sHigh
    :reader sHigh
    :initarg :sHigh
    :type cl:fixnum
    :initform 0)
   (vHigh
    :reader vHigh
    :initarg :vHigh
    :type cl:fixnum
    :initform 0)
   (hLow
    :reader hLow
    :initarg :hLow
    :type cl:fixnum
    :initform 0)
   (sLow
    :reader sLow
    :initarg :sLow
    :type cl:fixnum
    :initform 0)
   (vLow
    :reader vLow
    :initarg :vLow
    :type cl:fixnum
    :initform 0)
   (threshold
    :reader threshold
    :initarg :threshold
    :type cl:fixnum
    :initform 0)
   (centroid
    :reader centroid
    :initarg :centroid
    :type geometry_msgs-msg:PoseWithCovarianceStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseWithCovarianceStamped)))
)

(cl:defclass BlobFeatureMsg (<BlobFeatureMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BlobFeatureMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BlobFeatureMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_feature_server-msg:<BlobFeatureMsg> is deprecated: use visual_feature_server-msg:BlobFeatureMsg instead.")))

(cl:ensure-generic-function 'hHigh-val :lambda-list '(m))
(cl:defmethod hHigh-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:hHigh-val is deprecated.  Use visual_feature_server-msg:hHigh instead.")
  (hHigh m))

(cl:ensure-generic-function 'sHigh-val :lambda-list '(m))
(cl:defmethod sHigh-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:sHigh-val is deprecated.  Use visual_feature_server-msg:sHigh instead.")
  (sHigh m))

(cl:ensure-generic-function 'vHigh-val :lambda-list '(m))
(cl:defmethod vHigh-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:vHigh-val is deprecated.  Use visual_feature_server-msg:vHigh instead.")
  (vHigh m))

(cl:ensure-generic-function 'hLow-val :lambda-list '(m))
(cl:defmethod hLow-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:hLow-val is deprecated.  Use visual_feature_server-msg:hLow instead.")
  (hLow m))

(cl:ensure-generic-function 'sLow-val :lambda-list '(m))
(cl:defmethod sLow-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:sLow-val is deprecated.  Use visual_feature_server-msg:sLow instead.")
  (sLow m))

(cl:ensure-generic-function 'vLow-val :lambda-list '(m))
(cl:defmethod vLow-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:vLow-val is deprecated.  Use visual_feature_server-msg:vLow instead.")
  (vLow m))

(cl:ensure-generic-function 'threshold-val :lambda-list '(m))
(cl:defmethod threshold-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:threshold-val is deprecated.  Use visual_feature_server-msg:threshold instead.")
  (threshold m))

(cl:ensure-generic-function 'centroid-val :lambda-list '(m))
(cl:defmethod centroid-val ((m <BlobFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:centroid-val is deprecated.  Use visual_feature_server-msg:centroid instead.")
  (centroid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BlobFeatureMsg>) ostream)
  "Serializes a message object of type '<BlobFeatureMsg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hHigh)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sHigh)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vHigh)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hLow)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sLow)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vLow)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'threshold)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'centroid) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BlobFeatureMsg>) istream)
  "Deserializes a message object of type '<BlobFeatureMsg>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hHigh)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sHigh)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vHigh)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hLow)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sLow)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vLow)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'threshold)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'centroid) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BlobFeatureMsg>)))
  "Returns string type for a message object of type '<BlobFeatureMsg>"
  "visual_feature_server/BlobFeatureMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BlobFeatureMsg)))
  "Returns string type for a message object of type 'BlobFeatureMsg"
  "visual_feature_server/BlobFeatureMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BlobFeatureMsg>)))
  "Returns md5sum for a message object of type '<BlobFeatureMsg>"
  "c25be8f3f0fd93ffc579284ad0e9abf8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BlobFeatureMsg)))
  "Returns md5sum for a message object of type 'BlobFeatureMsg"
  "c25be8f3f0fd93ffc579284ad0e9abf8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BlobFeatureMsg>)))
  "Returns full string definition for message of type '<BlobFeatureMsg>"
  (cl:format cl:nil "uint8 hHigh~%uint8 sHigh~%uint8 vHigh~%uint8 hLow~%uint8 sLow~%uint8 vLow~%#uint8 scale~%uint8 threshold~%~%#pose of the feature~%geometry_msgs/PoseWithCovarianceStamped centroid~%#geometry_msgs/PoseWithCovarianceStamped top_left~%#geometry_msgs/PoseWithCovarianceStamped top_right~%#geometry_msgs/PoseWithCovarianceStamped bottom_left~%#geometry_msgs/PoseWithCovarianceStamped bottom_right~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BlobFeatureMsg)))
  "Returns full string definition for message of type 'BlobFeatureMsg"
  (cl:format cl:nil "uint8 hHigh~%uint8 sHigh~%uint8 vHigh~%uint8 hLow~%uint8 sLow~%uint8 vLow~%#uint8 scale~%uint8 threshold~%~%#pose of the feature~%geometry_msgs/PoseWithCovarianceStamped centroid~%#geometry_msgs/PoseWithCovarianceStamped top_left~%#geometry_msgs/PoseWithCovarianceStamped top_right~%#geometry_msgs/PoseWithCovarianceStamped bottom_left~%#geometry_msgs/PoseWithCovarianceStamped bottom_right~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BlobFeatureMsg>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'centroid))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BlobFeatureMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'BlobFeatureMsg
    (cl:cons ':hHigh (hHigh msg))
    (cl:cons ':sHigh (sHigh msg))
    (cl:cons ':vHigh (vHigh msg))
    (cl:cons ':hLow (hLow msg))
    (cl:cons ':sLow (sLow msg))
    (cl:cons ':vLow (vLow msg))
    (cl:cons ':threshold (threshold msg))
    (cl:cons ':centroid (centroid msg))
))

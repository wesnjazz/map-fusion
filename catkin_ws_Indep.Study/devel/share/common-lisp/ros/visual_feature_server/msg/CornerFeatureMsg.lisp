; Auto-generated. Do not edit!


(cl:in-package visual_feature_server-msg)


;//! \htmlinclude CornerFeatureMsg.msg.html

(cl:defclass <CornerFeatureMsg> (roslisp-msg-protocol:ros-message)
  ((threshold
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

(cl:defclass CornerFeatureMsg (<CornerFeatureMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CornerFeatureMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CornerFeatureMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_feature_server-msg:<CornerFeatureMsg> is deprecated: use visual_feature_server-msg:CornerFeatureMsg instead.")))

(cl:ensure-generic-function 'threshold-val :lambda-list '(m))
(cl:defmethod threshold-val ((m <CornerFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:threshold-val is deprecated.  Use visual_feature_server-msg:threshold instead.")
  (threshold m))

(cl:ensure-generic-function 'centroid-val :lambda-list '(m))
(cl:defmethod centroid-val ((m <CornerFeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:centroid-val is deprecated.  Use visual_feature_server-msg:centroid instead.")
  (centroid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CornerFeatureMsg>) ostream)
  "Serializes a message object of type '<CornerFeatureMsg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'threshold)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'centroid) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CornerFeatureMsg>) istream)
  "Deserializes a message object of type '<CornerFeatureMsg>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'threshold)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'centroid) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CornerFeatureMsg>)))
  "Returns string type for a message object of type '<CornerFeatureMsg>"
  "visual_feature_server/CornerFeatureMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CornerFeatureMsg)))
  "Returns string type for a message object of type 'CornerFeatureMsg"
  "visual_feature_server/CornerFeatureMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CornerFeatureMsg>)))
  "Returns md5sum for a message object of type '<CornerFeatureMsg>"
  "f86d11aa7264d820fbf8de0199829dfe")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CornerFeatureMsg)))
  "Returns md5sum for a message object of type 'CornerFeatureMsg"
  "f86d11aa7264d820fbf8de0199829dfe")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CornerFeatureMsg>)))
  "Returns full string definition for message of type '<CornerFeatureMsg>"
  (cl:format cl:nil "uint8 threshold~%#uint8 scale~%~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CornerFeatureMsg)))
  "Returns full string definition for message of type 'CornerFeatureMsg"
  (cl:format cl:nil "uint8 threshold~%#uint8 scale~%~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CornerFeatureMsg>))
  (cl:+ 0
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'centroid))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CornerFeatureMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'CornerFeatureMsg
    (cl:cons ':threshold (threshold msg))
    (cl:cons ':centroid (centroid msg))
))

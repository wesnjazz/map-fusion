; Auto-generated. Do not edit!


(cl:in-package visual_feature_server-msg)


;//! \htmlinclude FeatureMsg.msg.html

(cl:defclass <FeatureMsg> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (type
    :reader type
    :initarg :type
    :type cl:integer
    :initform 0)
   (image_scale
    :reader image_scale
    :initarg :image_scale
    :type cl:float
    :initform 0.0)
   (world_scale
    :reader world_scale
    :initarg :world_scale
    :type cl:float
    :initform 0.0)
   (blobFeature
    :reader blobFeature
    :initarg :blobFeature
    :type visual_feature_server-msg:BlobFeatureMsg
    :initform (cl:make-instance 'visual_feature_server-msg:BlobFeatureMsg))
   (cornerFeature
    :reader cornerFeature
    :initarg :cornerFeature
    :type visual_feature_server-msg:CornerFeatureMsg
    :initform (cl:make-instance 'visual_feature_server-msg:CornerFeatureMsg))
   (edgeFeature
    :reader edgeFeature
    :initarg :edgeFeature
    :type visual_feature_server-msg:EdgeFeatureMsg
    :initform (cl:make-instance 'visual_feature_server-msg:EdgeFeatureMsg))
   (confidence
    :reader confidence
    :initarg :confidence
    :type cl:float
    :initform 0.0)
   (x_pixel
    :reader x_pixel
    :initarg :x_pixel
    :type cl:integer
    :initform 0)
   (y_pixel
    :reader y_pixel
    :initarg :y_pixel
    :type cl:integer
    :initform 0))
)

(cl:defclass FeatureMsg (<FeatureMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FeatureMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FeatureMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_feature_server-msg:<FeatureMsg> is deprecated: use visual_feature_server-msg:FeatureMsg instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:name-val is deprecated.  Use visual_feature_server-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:type-val is deprecated.  Use visual_feature_server-msg:type instead.")
  (type m))

(cl:ensure-generic-function 'image_scale-val :lambda-list '(m))
(cl:defmethod image_scale-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:image_scale-val is deprecated.  Use visual_feature_server-msg:image_scale instead.")
  (image_scale m))

(cl:ensure-generic-function 'world_scale-val :lambda-list '(m))
(cl:defmethod world_scale-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:world_scale-val is deprecated.  Use visual_feature_server-msg:world_scale instead.")
  (world_scale m))

(cl:ensure-generic-function 'blobFeature-val :lambda-list '(m))
(cl:defmethod blobFeature-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:blobFeature-val is deprecated.  Use visual_feature_server-msg:blobFeature instead.")
  (blobFeature m))

(cl:ensure-generic-function 'cornerFeature-val :lambda-list '(m))
(cl:defmethod cornerFeature-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:cornerFeature-val is deprecated.  Use visual_feature_server-msg:cornerFeature instead.")
  (cornerFeature m))

(cl:ensure-generic-function 'edgeFeature-val :lambda-list '(m))
(cl:defmethod edgeFeature-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:edgeFeature-val is deprecated.  Use visual_feature_server-msg:edgeFeature instead.")
  (edgeFeature m))

(cl:ensure-generic-function 'confidence-val :lambda-list '(m))
(cl:defmethod confidence-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:confidence-val is deprecated.  Use visual_feature_server-msg:confidence instead.")
  (confidence m))

(cl:ensure-generic-function 'x_pixel-val :lambda-list '(m))
(cl:defmethod x_pixel-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:x_pixel-val is deprecated.  Use visual_feature_server-msg:x_pixel instead.")
  (x_pixel m))

(cl:ensure-generic-function 'y_pixel-val :lambda-list '(m))
(cl:defmethod y_pixel-val ((m <FeatureMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-msg:y_pixel-val is deprecated.  Use visual_feature_server-msg:y_pixel instead.")
  (y_pixel m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<FeatureMsg>)))
    "Constants for message type '<FeatureMsg>"
  '((:CORNER . 1)
    (:BLOB . 2)
    (:EDGE . 3)
    (:CORNER_STR . "corner")
    (:BLOB_STR . "blob")
    (:EDGE_STR . "edge"))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'FeatureMsg)))
    "Constants for message type 'FeatureMsg"
  '((:CORNER . 1)
    (:BLOB . 2)
    (:EDGE . 3)
    (:CORNER_STR . "corner")
    (:BLOB_STR . "blob")
    (:EDGE_STR . "edge"))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FeatureMsg>) ostream)
  "Serializes a message object of type '<FeatureMsg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let* ((signed (cl:slot-value msg 'type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'image_scale))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'world_scale))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'blobFeature) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cornerFeature) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'edgeFeature) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'confidence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'x_pixel)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_pixel)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FeatureMsg>) istream)
  "Deserializes a message object of type '<FeatureMsg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'image_scale) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'world_scale) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'blobFeature) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cornerFeature) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'edgeFeature) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'confidence) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_pixel) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_pixel) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FeatureMsg>)))
  "Returns string type for a message object of type '<FeatureMsg>"
  "visual_feature_server/FeatureMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FeatureMsg)))
  "Returns string type for a message object of type 'FeatureMsg"
  "visual_feature_server/FeatureMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FeatureMsg>)))
  "Returns md5sum for a message object of type '<FeatureMsg>"
  "93ea47ac84f852fc7e6fbfcdf7865fee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FeatureMsg)))
  "Returns md5sum for a message object of type 'FeatureMsg"
  "93ea47ac84f852fc7e6fbfcdf7865fee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FeatureMsg>)))
  "Returns full string definition for message of type '<FeatureMsg>"
  (cl:format cl:nil "uint8 CORNER=1~%uint8 BLOB=2~%uint8 EDGE=3~%string CORNER_STR=\"corner\"~%string BLOB_STR=\"blob\"~%string EDGE_STR=\"edge\"~%~%string name~%int32 type~%~%float32 image_scale~%float32 world_scale~%~%BlobFeatureMsg blobFeature~%CornerFeatureMsg cornerFeature~%EdgeFeatureMsg edgeFeature~%~%#recognition confidence~%float32 confidence~%int32 x_pixel~%int32 y_pixel~%~%================================================================================~%MSG: visual_feature_server/BlobFeatureMsg~%uint8 hHigh~%uint8 sHigh~%uint8 vHigh~%uint8 hLow~%uint8 sLow~%uint8 vLow~%#uint8 scale~%uint8 threshold~%~%#pose of the feature~%geometry_msgs/PoseWithCovarianceStamped centroid~%#geometry_msgs/PoseWithCovarianceStamped top_left~%#geometry_msgs/PoseWithCovarianceStamped top_right~%#geometry_msgs/PoseWithCovarianceStamped bottom_left~%#geometry_msgs/PoseWithCovarianceStamped bottom_right~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: visual_feature_server/CornerFeatureMsg~%uint8 threshold~%#uint8 scale~%~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%================================================================================~%MSG: visual_feature_server/EdgeFeatureMsg~%uint8 threshold~%#uint8 scale~%~%# geometry_msgs/PoseWithCovarianceStamped p1~%# geometry_msgs/PoseWithCovarianceStamped p2~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FeatureMsg)))
  "Returns full string definition for message of type 'FeatureMsg"
  (cl:format cl:nil "uint8 CORNER=1~%uint8 BLOB=2~%uint8 EDGE=3~%string CORNER_STR=\"corner\"~%string BLOB_STR=\"blob\"~%string EDGE_STR=\"edge\"~%~%string name~%int32 type~%~%float32 image_scale~%float32 world_scale~%~%BlobFeatureMsg blobFeature~%CornerFeatureMsg cornerFeature~%EdgeFeatureMsg edgeFeature~%~%#recognition confidence~%float32 confidence~%int32 x_pixel~%int32 y_pixel~%~%================================================================================~%MSG: visual_feature_server/BlobFeatureMsg~%uint8 hHigh~%uint8 sHigh~%uint8 vHigh~%uint8 hLow~%uint8 sLow~%uint8 vLow~%#uint8 scale~%uint8 threshold~%~%#pose of the feature~%geometry_msgs/PoseWithCovarianceStamped centroid~%#geometry_msgs/PoseWithCovarianceStamped top_left~%#geometry_msgs/PoseWithCovarianceStamped top_right~%#geometry_msgs/PoseWithCovarianceStamped bottom_left~%#geometry_msgs/PoseWithCovarianceStamped bottom_right~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovarianceStamped~%# This expresses an estimated pose with a reference coordinate frame and timestamp~%~%Header header~%PoseWithCovariance pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: visual_feature_server/CornerFeatureMsg~%uint8 threshold~%#uint8 scale~%~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%================================================================================~%MSG: visual_feature_server/EdgeFeatureMsg~%uint8 threshold~%#uint8 scale~%~%# geometry_msgs/PoseWithCovarianceStamped p1~%# geometry_msgs/PoseWithCovarianceStamped p2~%geometry_msgs/PoseWithCovarianceStamped centroid~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FeatureMsg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'blobFeature))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cornerFeature))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'edgeFeature))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FeatureMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'FeatureMsg
    (cl:cons ':name (name msg))
    (cl:cons ':type (type msg))
    (cl:cons ':image_scale (image_scale msg))
    (cl:cons ':world_scale (world_scale msg))
    (cl:cons ':blobFeature (blobFeature msg))
    (cl:cons ':cornerFeature (cornerFeature msg))
    (cl:cons ':edgeFeature (edgeFeature msg))
    (cl:cons ':confidence (confidence msg))
    (cl:cons ':x_pixel (x_pixel msg))
    (cl:cons ':y_pixel (y_pixel msg))
))

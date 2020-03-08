; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude CobotAnomalyMonitorMsg.msg.html

(cl:defclass <CobotAnomalyMonitorMsg> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (anomaly
    :reader anomaly
    :initarg :anomaly
    :type cl:float
    :initform 0.0)
   (mean
    :reader mean
    :initarg :mean
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (var
    :reader var
    :initarg :var
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (nSamples
    :reader nSamples
    :initarg :nSamples
    :type cl:integer
    :initform 0))
)

(cl:defclass CobotAnomalyMonitorMsg (<CobotAnomalyMonitorMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotAnomalyMonitorMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotAnomalyMonitorMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<CobotAnomalyMonitorMsg> is deprecated: use vector_slam_msgs-msg:CobotAnomalyMonitorMsg instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CobotAnomalyMonitorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:header-val is deprecated.  Use vector_slam_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'anomaly-val :lambda-list '(m))
(cl:defmethod anomaly-val ((m <CobotAnomalyMonitorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:anomaly-val is deprecated.  Use vector_slam_msgs-msg:anomaly instead.")
  (anomaly m))

(cl:ensure-generic-function 'mean-val :lambda-list '(m))
(cl:defmethod mean-val ((m <CobotAnomalyMonitorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:mean-val is deprecated.  Use vector_slam_msgs-msg:mean instead.")
  (mean m))

(cl:ensure-generic-function 'var-val :lambda-list '(m))
(cl:defmethod var-val ((m <CobotAnomalyMonitorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:var-val is deprecated.  Use vector_slam_msgs-msg:var instead.")
  (var m))

(cl:ensure-generic-function 'nSamples-val :lambda-list '(m))
(cl:defmethod nSamples-val ((m <CobotAnomalyMonitorMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:nSamples-val is deprecated.  Use vector_slam_msgs-msg:nSamples instead.")
  (nSamples m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotAnomalyMonitorMsg>) ostream)
  "Serializes a message object of type '<CobotAnomalyMonitorMsg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'anomaly))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'mean))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'mean))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'var))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'var))
  (cl:let* ((signed (cl:slot-value msg 'nSamples)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotAnomalyMonitorMsg>) istream)
  "Deserializes a message object of type '<CobotAnomalyMonitorMsg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'anomaly) (roslisp-utils:decode-double-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'mean) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'mean)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'var) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'var)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'nSamples) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotAnomalyMonitorMsg>)))
  "Returns string type for a message object of type '<CobotAnomalyMonitorMsg>"
  "vector_slam_msgs/CobotAnomalyMonitorMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotAnomalyMonitorMsg)))
  "Returns string type for a message object of type 'CobotAnomalyMonitorMsg"
  "vector_slam_msgs/CobotAnomalyMonitorMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotAnomalyMonitorMsg>)))
  "Returns md5sum for a message object of type '<CobotAnomalyMonitorMsg>"
  "704f0ea26cbea2690711adde3ba16ce3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotAnomalyMonitorMsg)))
  "Returns md5sum for a message object of type 'CobotAnomalyMonitorMsg"
  "704f0ea26cbea2690711adde3ba16ce3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotAnomalyMonitorMsg>)))
  "Returns full string definition for message of type '<CobotAnomalyMonitorMsg>"
  (cl:format cl:nil "Header header~%~%float64 anomaly~%float64[] mean~%float64[] var~%int32 nSamples~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotAnomalyMonitorMsg)))
  "Returns full string definition for message of type 'CobotAnomalyMonitorMsg"
  (cl:format cl:nil "Header header~%~%float64 anomaly~%float64[] mean~%float64[] var~%int32 nSamples~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotAnomalyMonitorMsg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'mean) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'var) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotAnomalyMonitorMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotAnomalyMonitorMsg
    (cl:cons ':header (header msg))
    (cl:cons ':anomaly (anomaly msg))
    (cl:cons ':mean (mean msg))
    (cl:cons ':var (var msg))
    (cl:cons ':nSamples (nSamples msg))
))

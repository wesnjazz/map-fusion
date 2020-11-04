; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude LocalizationMsg.msg.html

(cl:defclass <LocalizationMsg> (roslisp-msg-protocol:ros-message)
  ((map_name
    :reader map_name
    :initarg :map_name
    :type cl:string
    :initform "")
   (location
    :reader location
    :initarg :location
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass LocalizationMsg (<LocalizationMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LocalizationMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LocalizationMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<LocalizationMsg> is deprecated: use vector_slam_msgs-msg:LocalizationMsg instead.")))

(cl:ensure-generic-function 'map_name-val :lambda-list '(m))
(cl:defmethod map_name-val ((m <LocalizationMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:map_name-val is deprecated.  Use vector_slam_msgs-msg:map_name instead.")
  (map_name m))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <LocalizationMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:location-val is deprecated.  Use vector_slam_msgs-msg:location instead.")
  (location m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <LocalizationMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:angle-val is deprecated.  Use vector_slam_msgs-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LocalizationMsg>) ostream)
  "Serializes a message object of type '<LocalizationMsg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'map_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'map_name))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'location) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LocalizationMsg>) istream)
  "Deserializes a message object of type '<LocalizationMsg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'map_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'location) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LocalizationMsg>)))
  "Returns string type for a message object of type '<LocalizationMsg>"
  "vector_slam_msgs/LocalizationMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LocalizationMsg)))
  "Returns string type for a message object of type 'LocalizationMsg"
  "vector_slam_msgs/LocalizationMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LocalizationMsg>)))
  "Returns md5sum for a message object of type '<LocalizationMsg>"
  "d97acce230cd4cd8961fb0e1730022b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LocalizationMsg)))
  "Returns md5sum for a message object of type 'LocalizationMsg"
  "d97acce230cd4cd8961fb0e1730022b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LocalizationMsg>)))
  "Returns full string definition for message of type '<LocalizationMsg>"
  (cl:format cl:nil "string map_name~%geometry_msgs/Vector3 location~%float32 angle~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LocalizationMsg)))
  "Returns full string definition for message of type 'LocalizationMsg"
  (cl:format cl:nil "string map_name~%geometry_msgs/Vector3 location~%float32 angle~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LocalizationMsg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'map_name))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'location))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LocalizationMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'LocalizationMsg
    (cl:cons ':map_name (map_name msg))
    (cl:cons ':location (location msg))
    (cl:cons ':angle (angle msg))
))

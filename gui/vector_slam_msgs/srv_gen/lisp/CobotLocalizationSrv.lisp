; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-srv)


;//! \htmlinclude CobotLocalizationSrv-request.msg.html

(cl:defclass <CobotLocalizationSrv-request> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0)
   (map
    :reader map
    :initarg :map
    :type cl:string
    :initform ""))
)

(cl:defclass CobotLocalizationSrv-request (<CobotLocalizationSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotLocalizationSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotLocalizationSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-srv:<CobotLocalizationSrv-request> is deprecated: use vector_slam_msgs-srv:CobotLocalizationSrv-request instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <CobotLocalizationSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:x-val is deprecated.  Use vector_slam_msgs-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <CobotLocalizationSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:y-val is deprecated.  Use vector_slam_msgs-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <CobotLocalizationSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:angle-val is deprecated.  Use vector_slam_msgs-srv:angle instead.")
  (angle m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <CobotLocalizationSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:map-val is deprecated.  Use vector_slam_msgs-srv:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotLocalizationSrv-request>) ostream)
  "Serializes a message object of type '<CobotLocalizationSrv-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'map))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'map))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotLocalizationSrv-request>) istream)
  "Deserializes a message object of type '<CobotLocalizationSrv-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'map) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotLocalizationSrv-request>)))
  "Returns string type for a service object of type '<CobotLocalizationSrv-request>"
  "vector_slam_msgs/CobotLocalizationSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotLocalizationSrv-request)))
  "Returns string type for a service object of type 'CobotLocalizationSrv-request"
  "vector_slam_msgs/CobotLocalizationSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotLocalizationSrv-request>)))
  "Returns md5sum for a message object of type '<CobotLocalizationSrv-request>"
  "46b19ca691c0681ae113f7efec3bb4b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotLocalizationSrv-request)))
  "Returns md5sum for a message object of type 'CobotLocalizationSrv-request"
  "46b19ca691c0681ae113f7efec3bb4b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotLocalizationSrv-request>)))
  "Returns full string definition for message of type '<CobotLocalizationSrv-request>"
  (cl:format cl:nil "~%float32 x~%float32 y~%float32 angle~%string map~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotLocalizationSrv-request)))
  "Returns full string definition for message of type 'CobotLocalizationSrv-request"
  (cl:format cl:nil "~%float32 x~%float32 y~%float32 angle~%string map~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotLocalizationSrv-request>))
  (cl:+ 0
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'map))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotLocalizationSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotLocalizationSrv-request
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':map (map msg))
))
;//! \htmlinclude CobotLocalizationSrv-response.msg.html

(cl:defclass <CobotLocalizationSrv-response> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0)
   (map
    :reader map
    :initarg :map
    :type cl:string
    :initform ""))
)

(cl:defclass CobotLocalizationSrv-response (<CobotLocalizationSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotLocalizationSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotLocalizationSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-srv:<CobotLocalizationSrv-response> is deprecated: use vector_slam_msgs-srv:CobotLocalizationSrv-response instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <CobotLocalizationSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:x-val is deprecated.  Use vector_slam_msgs-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <CobotLocalizationSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:y-val is deprecated.  Use vector_slam_msgs-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <CobotLocalizationSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:angle-val is deprecated.  Use vector_slam_msgs-srv:angle instead.")
  (angle m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <CobotLocalizationSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:map-val is deprecated.  Use vector_slam_msgs-srv:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotLocalizationSrv-response>) ostream)
  "Serializes a message object of type '<CobotLocalizationSrv-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'map))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'map))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotLocalizationSrv-response>) istream)
  "Deserializes a message object of type '<CobotLocalizationSrv-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'map) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotLocalizationSrv-response>)))
  "Returns string type for a service object of type '<CobotLocalizationSrv-response>"
  "vector_slam_msgs/CobotLocalizationSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotLocalizationSrv-response)))
  "Returns string type for a service object of type 'CobotLocalizationSrv-response"
  "vector_slam_msgs/CobotLocalizationSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotLocalizationSrv-response>)))
  "Returns md5sum for a message object of type '<CobotLocalizationSrv-response>"
  "46b19ca691c0681ae113f7efec3bb4b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotLocalizationSrv-response)))
  "Returns md5sum for a message object of type 'CobotLocalizationSrv-response"
  "46b19ca691c0681ae113f7efec3bb4b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotLocalizationSrv-response>)))
  "Returns full string definition for message of type '<CobotLocalizationSrv-response>"
  (cl:format cl:nil "~%float32 x~%float32 y~%float32 angle~%string map~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotLocalizationSrv-response)))
  "Returns full string definition for message of type 'CobotLocalizationSrv-response"
  (cl:format cl:nil "~%float32 x~%float32 y~%float32 angle~%string map~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotLocalizationSrv-response>))
  (cl:+ 0
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'map))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotLocalizationSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotLocalizationSrv-response
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':map (map msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'CobotLocalizationSrv)))
  'CobotLocalizationSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'CobotLocalizationSrv)))
  'CobotLocalizationSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotLocalizationSrv)))
  "Returns string type for a service object of type '<CobotLocalizationSrv>"
  "vector_slam_msgs/CobotLocalizationSrv")
; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-srv)


;//! \htmlinclude LocalizationGuiCaptureSrv-request.msg.html

(cl:defclass <LocalizationGuiCaptureSrv-request> (roslisp-msg-protocol:ros-message)
  ((filename
    :reader filename
    :initarg :filename
    :type cl:string
    :initform ""))
)

(cl:defclass LocalizationGuiCaptureSrv-request (<LocalizationGuiCaptureSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LocalizationGuiCaptureSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LocalizationGuiCaptureSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-srv:<LocalizationGuiCaptureSrv-request> is deprecated: use vector_slam_msgs-srv:LocalizationGuiCaptureSrv-request instead.")))

(cl:ensure-generic-function 'filename-val :lambda-list '(m))
(cl:defmethod filename-val ((m <LocalizationGuiCaptureSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:filename-val is deprecated.  Use vector_slam_msgs-srv:filename instead.")
  (filename m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LocalizationGuiCaptureSrv-request>) ostream)
  "Serializes a message object of type '<LocalizationGuiCaptureSrv-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'filename))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'filename))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LocalizationGuiCaptureSrv-request>) istream)
  "Deserializes a message object of type '<LocalizationGuiCaptureSrv-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'filename) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'filename) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LocalizationGuiCaptureSrv-request>)))
  "Returns string type for a service object of type '<LocalizationGuiCaptureSrv-request>"
  "vector_slam_msgs/LocalizationGuiCaptureSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LocalizationGuiCaptureSrv-request)))
  "Returns string type for a service object of type 'LocalizationGuiCaptureSrv-request"
  "vector_slam_msgs/LocalizationGuiCaptureSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LocalizationGuiCaptureSrv-request>)))
  "Returns md5sum for a message object of type '<LocalizationGuiCaptureSrv-request>"
  "c87d011601ff2433adb44eb46cc15573")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LocalizationGuiCaptureSrv-request)))
  "Returns md5sum for a message object of type 'LocalizationGuiCaptureSrv-request"
  "c87d011601ff2433adb44eb46cc15573")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LocalizationGuiCaptureSrv-request>)))
  "Returns full string definition for message of type '<LocalizationGuiCaptureSrv-request>"
  (cl:format cl:nil "string filename~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LocalizationGuiCaptureSrv-request)))
  "Returns full string definition for message of type 'LocalizationGuiCaptureSrv-request"
  (cl:format cl:nil "string filename~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LocalizationGuiCaptureSrv-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'filename))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LocalizationGuiCaptureSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'LocalizationGuiCaptureSrv-request
    (cl:cons ':filename (filename msg))
))
;//! \htmlinclude LocalizationGuiCaptureSrv-response.msg.html

(cl:defclass <LocalizationGuiCaptureSrv-response> (roslisp-msg-protocol:ros-message)
  ((error
    :reader error
    :initarg :error
    :type cl:fixnum
    :initform 0))
)

(cl:defclass LocalizationGuiCaptureSrv-response (<LocalizationGuiCaptureSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LocalizationGuiCaptureSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LocalizationGuiCaptureSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-srv:<LocalizationGuiCaptureSrv-response> is deprecated: use vector_slam_msgs-srv:LocalizationGuiCaptureSrv-response instead.")))

(cl:ensure-generic-function 'error-val :lambda-list '(m))
(cl:defmethod error-val ((m <LocalizationGuiCaptureSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:error-val is deprecated.  Use vector_slam_msgs-srv:error instead.")
  (error m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LocalizationGuiCaptureSrv-response>) ostream)
  "Serializes a message object of type '<LocalizationGuiCaptureSrv-response>"
  (cl:let* ((signed (cl:slot-value msg 'error)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LocalizationGuiCaptureSrv-response>) istream)
  "Deserializes a message object of type '<LocalizationGuiCaptureSrv-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'error) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LocalizationGuiCaptureSrv-response>)))
  "Returns string type for a service object of type '<LocalizationGuiCaptureSrv-response>"
  "vector_slam_msgs/LocalizationGuiCaptureSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LocalizationGuiCaptureSrv-response)))
  "Returns string type for a service object of type 'LocalizationGuiCaptureSrv-response"
  "vector_slam_msgs/LocalizationGuiCaptureSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LocalizationGuiCaptureSrv-response>)))
  "Returns md5sum for a message object of type '<LocalizationGuiCaptureSrv-response>"
  "c87d011601ff2433adb44eb46cc15573")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LocalizationGuiCaptureSrv-response)))
  "Returns md5sum for a message object of type 'LocalizationGuiCaptureSrv-response"
  "c87d011601ff2433adb44eb46cc15573")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LocalizationGuiCaptureSrv-response>)))
  "Returns full string definition for message of type '<LocalizationGuiCaptureSrv-response>"
  (cl:format cl:nil "~%int8 error~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LocalizationGuiCaptureSrv-response)))
  "Returns full string definition for message of type 'LocalizationGuiCaptureSrv-response"
  (cl:format cl:nil "~%int8 error~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LocalizationGuiCaptureSrv-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LocalizationGuiCaptureSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'LocalizationGuiCaptureSrv-response
    (cl:cons ':error (error msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'LocalizationGuiCaptureSrv)))
  'LocalizationGuiCaptureSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'LocalizationGuiCaptureSrv)))
  'LocalizationGuiCaptureSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LocalizationGuiCaptureSrv)))
  "Returns string type for a service object of type '<LocalizationGuiCaptureSrv>"
  "vector_slam_msgs/LocalizationGuiCaptureSrv")
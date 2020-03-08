; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude CobotLocalization3DMsg.msg.html

(cl:defclass <CobotLocalization3DMsg> (roslisp-msg-protocol:ros-message)
  ((timeStamp
    :reader timeStamp
    :initarg :timeStamp
    :type cl:float
    :initform 0.0)
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0)
   (angle_w
    :reader angle_w
    :initarg :angle_w
    :type cl:float
    :initform 0.0)
   (angle_x
    :reader angle_x
    :initarg :angle_x
    :type cl:float
    :initform 0.0)
   (angle_y
    :reader angle_y
    :initarg :angle_y
    :type cl:float
    :initform 0.0)
   (angle_z
    :reader angle_z
    :initarg :angle_z
    :type cl:float
    :initform 0.0)
   (conf
    :reader conf
    :initarg :conf
    :type cl:float
    :initform 0.0)
   (map
    :reader map
    :initarg :map
    :type cl:string
    :initform ""))
)

(cl:defclass CobotLocalization3DMsg (<CobotLocalization3DMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotLocalization3DMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotLocalization3DMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<CobotLocalization3DMsg> is deprecated: use vector_slam_msgs-msg:CobotLocalization3DMsg instead.")))

(cl:ensure-generic-function 'timeStamp-val :lambda-list '(m))
(cl:defmethod timeStamp-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:timeStamp-val is deprecated.  Use vector_slam_msgs-msg:timeStamp instead.")
  (timeStamp m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:x-val is deprecated.  Use vector_slam_msgs-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:y-val is deprecated.  Use vector_slam_msgs-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:z-val is deprecated.  Use vector_slam_msgs-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'angle_w-val :lambda-list '(m))
(cl:defmethod angle_w-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:angle_w-val is deprecated.  Use vector_slam_msgs-msg:angle_w instead.")
  (angle_w m))

(cl:ensure-generic-function 'angle_x-val :lambda-list '(m))
(cl:defmethod angle_x-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:angle_x-val is deprecated.  Use vector_slam_msgs-msg:angle_x instead.")
  (angle_x m))

(cl:ensure-generic-function 'angle_y-val :lambda-list '(m))
(cl:defmethod angle_y-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:angle_y-val is deprecated.  Use vector_slam_msgs-msg:angle_y instead.")
  (angle_y m))

(cl:ensure-generic-function 'angle_z-val :lambda-list '(m))
(cl:defmethod angle_z-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:angle_z-val is deprecated.  Use vector_slam_msgs-msg:angle_z instead.")
  (angle_z m))

(cl:ensure-generic-function 'conf-val :lambda-list '(m))
(cl:defmethod conf-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:conf-val is deprecated.  Use vector_slam_msgs-msg:conf instead.")
  (conf m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <CobotLocalization3DMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:map-val is deprecated.  Use vector_slam_msgs-msg:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotLocalization3DMsg>) ostream)
  "Serializes a message object of type '<CobotLocalization3DMsg>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'timeStamp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_w))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'conf))))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotLocalization3DMsg>) istream)
  "Deserializes a message object of type '<CobotLocalization3DMsg>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'timeStamp) (roslisp-utils:decode-double-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_w) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'conf) (roslisp-utils:decode-single-float-bits bits)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotLocalization3DMsg>)))
  "Returns string type for a message object of type '<CobotLocalization3DMsg>"
  "vector_slam_msgs/CobotLocalization3DMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotLocalization3DMsg)))
  "Returns string type for a message object of type 'CobotLocalization3DMsg"
  "vector_slam_msgs/CobotLocalization3DMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotLocalization3DMsg>)))
  "Returns md5sum for a message object of type '<CobotLocalization3DMsg>"
  "25565b272405f868405eb6f47a0058f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotLocalization3DMsg)))
  "Returns md5sum for a message object of type 'CobotLocalization3DMsg"
  "25565b272405f868405eb6f47a0058f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotLocalization3DMsg>)))
  "Returns full string definition for message of type '<CobotLocalization3DMsg>"
  (cl:format cl:nil "float64 timeStamp~%float32 x~%float32 y~%float32 z~%float32 angle_w~%float32 angle_x~%float32 angle_y~%float32 angle_z~%float32 conf~%string map~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotLocalization3DMsg)))
  "Returns full string definition for message of type 'CobotLocalization3DMsg"
  (cl:format cl:nil "float64 timeStamp~%float32 x~%float32 y~%float32 z~%float32 angle_w~%float32 angle_x~%float32 angle_y~%float32 angle_z~%float32 conf~%string map~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotLocalization3DMsg>))
  (cl:+ 0
     8
     4
     4
     4
     4
     4
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'map))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotLocalization3DMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotLocalization3DMsg
    (cl:cons ':timeStamp (timeStamp msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':angle_w (angle_w msg))
    (cl:cons ':angle_x (angle_x msg))
    (cl:cons ':angle_y (angle_y msg))
    (cl:cons ':angle_z (angle_z msg))
    (cl:cons ':conf (conf msg))
    (cl:cons ':map (map msg))
))

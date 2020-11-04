; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-srv)


;//! \htmlinclude CobotRemoteInterfaceSrv-request.msg.html

(cl:defclass <CobotRemoteInterfaceSrv-request> (roslisp-msg-protocol:ros-message)
  ((drive_x
    :reader drive_x
    :initarg :drive_x
    :type cl:float
    :initform 0.0)
   (drive_y
    :reader drive_y
    :initarg :drive_y
    :type cl:float
    :initform 0.0)
   (drive_r
    :reader drive_r
    :initarg :drive_r
    :type cl:float
    :initform 0.0)
   (max_vel_trans
    :reader max_vel_trans
    :initarg :max_vel_trans
    :type cl:float
    :initform 0.0)
   (max_vel_rot
    :reader max_vel_rot
    :initarg :max_vel_rot
    :type cl:float
    :initform 0.0)
   (command_num
    :reader command_num
    :initarg :command_num
    :type cl:integer
    :initform 0)
   (command_type
    :reader command_type
    :initarg :command_type
    :type cl:integer
    :initform 0)
   (loc_x
    :reader loc_x
    :initarg :loc_x
    :type cl:float
    :initform 0.0)
   (loc_y
    :reader loc_y
    :initarg :loc_y
    :type cl:float
    :initform 0.0)
   (orientation
    :reader orientation
    :initarg :orientation
    :type cl:float
    :initform 0.0)
   (distance_tolerance
    :reader distance_tolerance
    :initarg :distance_tolerance
    :type cl:float
    :initform 0.0)
   (angle_tolerance
    :reader angle_tolerance
    :initarg :angle_tolerance
    :type cl:float
    :initform 0.0)
   (map
    :reader map
    :initarg :map
    :type cl:string
    :initform ""))
)

(cl:defclass CobotRemoteInterfaceSrv-request (<CobotRemoteInterfaceSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotRemoteInterfaceSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotRemoteInterfaceSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-srv:<CobotRemoteInterfaceSrv-request> is deprecated: use vector_slam_msgs-srv:CobotRemoteInterfaceSrv-request instead.")))

(cl:ensure-generic-function 'drive_x-val :lambda-list '(m))
(cl:defmethod drive_x-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:drive_x-val is deprecated.  Use vector_slam_msgs-srv:drive_x instead.")
  (drive_x m))

(cl:ensure-generic-function 'drive_y-val :lambda-list '(m))
(cl:defmethod drive_y-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:drive_y-val is deprecated.  Use vector_slam_msgs-srv:drive_y instead.")
  (drive_y m))

(cl:ensure-generic-function 'drive_r-val :lambda-list '(m))
(cl:defmethod drive_r-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:drive_r-val is deprecated.  Use vector_slam_msgs-srv:drive_r instead.")
  (drive_r m))

(cl:ensure-generic-function 'max_vel_trans-val :lambda-list '(m))
(cl:defmethod max_vel_trans-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:max_vel_trans-val is deprecated.  Use vector_slam_msgs-srv:max_vel_trans instead.")
  (max_vel_trans m))

(cl:ensure-generic-function 'max_vel_rot-val :lambda-list '(m))
(cl:defmethod max_vel_rot-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:max_vel_rot-val is deprecated.  Use vector_slam_msgs-srv:max_vel_rot instead.")
  (max_vel_rot m))

(cl:ensure-generic-function 'command_num-val :lambda-list '(m))
(cl:defmethod command_num-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:command_num-val is deprecated.  Use vector_slam_msgs-srv:command_num instead.")
  (command_num m))

(cl:ensure-generic-function 'command_type-val :lambda-list '(m))
(cl:defmethod command_type-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:command_type-val is deprecated.  Use vector_slam_msgs-srv:command_type instead.")
  (command_type m))

(cl:ensure-generic-function 'loc_x-val :lambda-list '(m))
(cl:defmethod loc_x-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:loc_x-val is deprecated.  Use vector_slam_msgs-srv:loc_x instead.")
  (loc_x m))

(cl:ensure-generic-function 'loc_y-val :lambda-list '(m))
(cl:defmethod loc_y-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:loc_y-val is deprecated.  Use vector_slam_msgs-srv:loc_y instead.")
  (loc_y m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:orientation-val is deprecated.  Use vector_slam_msgs-srv:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'distance_tolerance-val :lambda-list '(m))
(cl:defmethod distance_tolerance-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:distance_tolerance-val is deprecated.  Use vector_slam_msgs-srv:distance_tolerance instead.")
  (distance_tolerance m))

(cl:ensure-generic-function 'angle_tolerance-val :lambda-list '(m))
(cl:defmethod angle_tolerance-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:angle_tolerance-val is deprecated.  Use vector_slam_msgs-srv:angle_tolerance instead.")
  (angle_tolerance m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <CobotRemoteInterfaceSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:map-val is deprecated.  Use vector_slam_msgs-srv:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotRemoteInterfaceSrv-request>) ostream)
  "Serializes a message object of type '<CobotRemoteInterfaceSrv-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'drive_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'drive_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'drive_r))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'max_vel_trans))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'max_vel_rot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'command_num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'command_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'loc_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'loc_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'orientation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance_tolerance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_tolerance))))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotRemoteInterfaceSrv-request>) istream)
  "Deserializes a message object of type '<CobotRemoteInterfaceSrv-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'drive_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'drive_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'drive_r) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_vel_trans) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_vel_rot) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command_num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command_type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'loc_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'loc_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'orientation) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance_tolerance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_tolerance) (roslisp-utils:decode-single-float-bits bits)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotRemoteInterfaceSrv-request>)))
  "Returns string type for a service object of type '<CobotRemoteInterfaceSrv-request>"
  "vector_slam_msgs/CobotRemoteInterfaceSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotRemoteInterfaceSrv-request)))
  "Returns string type for a service object of type 'CobotRemoteInterfaceSrv-request"
  "vector_slam_msgs/CobotRemoteInterfaceSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotRemoteInterfaceSrv-request>)))
  "Returns md5sum for a message object of type '<CobotRemoteInterfaceSrv-request>"
  "01146b8ee6bc341b195eb59880324094")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotRemoteInterfaceSrv-request)))
  "Returns md5sum for a message object of type 'CobotRemoteInterfaceSrv-request"
  "01146b8ee6bc341b195eb59880324094")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotRemoteInterfaceSrv-request>)))
  "Returns full string definition for message of type '<CobotRemoteInterfaceSrv-request>"
  (cl:format cl:nil "~%~%float32 drive_x~%float32 drive_y~%float32 drive_r~%float32 max_vel_trans~%float32 max_vel_rot~%~%~%int32 command_num~%~%~%~%~%~%~%~%~%~%~%int32 command_type~%~%~%float32 loc_x~%float32 loc_y~%float32 orientation~%float32 distance_tolerance~%float32 angle_tolerance~%string map~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotRemoteInterfaceSrv-request)))
  "Returns full string definition for message of type 'CobotRemoteInterfaceSrv-request"
  (cl:format cl:nil "~%~%float32 drive_x~%float32 drive_y~%float32 drive_r~%float32 max_vel_trans~%float32 max_vel_rot~%~%~%int32 command_num~%~%~%~%~%~%~%~%~%~%~%int32 command_type~%~%~%float32 loc_x~%float32 loc_y~%float32 orientation~%float32 distance_tolerance~%float32 angle_tolerance~%string map~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotRemoteInterfaceSrv-request>))
  (cl:+ 0
     4
     4
     4
     4
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
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotRemoteInterfaceSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotRemoteInterfaceSrv-request
    (cl:cons ':drive_x (drive_x msg))
    (cl:cons ':drive_y (drive_y msg))
    (cl:cons ':drive_r (drive_r msg))
    (cl:cons ':max_vel_trans (max_vel_trans msg))
    (cl:cons ':max_vel_rot (max_vel_rot msg))
    (cl:cons ':command_num (command_num msg))
    (cl:cons ':command_type (command_type msg))
    (cl:cons ':loc_x (loc_x msg))
    (cl:cons ':loc_y (loc_y msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':distance_tolerance (distance_tolerance msg))
    (cl:cons ':angle_tolerance (angle_tolerance msg))
    (cl:cons ':map (map msg))
))
;//! \htmlinclude CobotRemoteInterfaceSrv-response.msg.html

(cl:defclass <CobotRemoteInterfaceSrv-response> (roslisp-msg-protocol:ros-message)
  ((loc_x
    :reader loc_x
    :initarg :loc_x
    :type cl:float
    :initform 0.0)
   (loc_y
    :reader loc_y
    :initarg :loc_y
    :type cl:float
    :initform 0.0)
   (orientation
    :reader orientation
    :initarg :orientation
    :type cl:float
    :initform 0.0)
   (particles_x
    :reader particles_x
    :initarg :particles_x
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (particles_y
    :reader particles_y
    :initarg :particles_y
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (particles_weight
    :reader particles_weight
    :initarg :particles_weight
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (locations_weight
    :reader locations_weight
    :initarg :locations_weight
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (err_code
    :reader err_code
    :initarg :err_code
    :type cl:fixnum
    :initform 0))
)

(cl:defclass CobotRemoteInterfaceSrv-response (<CobotRemoteInterfaceSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotRemoteInterfaceSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotRemoteInterfaceSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-srv:<CobotRemoteInterfaceSrv-response> is deprecated: use vector_slam_msgs-srv:CobotRemoteInterfaceSrv-response instead.")))

(cl:ensure-generic-function 'loc_x-val :lambda-list '(m))
(cl:defmethod loc_x-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:loc_x-val is deprecated.  Use vector_slam_msgs-srv:loc_x instead.")
  (loc_x m))

(cl:ensure-generic-function 'loc_y-val :lambda-list '(m))
(cl:defmethod loc_y-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:loc_y-val is deprecated.  Use vector_slam_msgs-srv:loc_y instead.")
  (loc_y m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:orientation-val is deprecated.  Use vector_slam_msgs-srv:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'particles_x-val :lambda-list '(m))
(cl:defmethod particles_x-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:particles_x-val is deprecated.  Use vector_slam_msgs-srv:particles_x instead.")
  (particles_x m))

(cl:ensure-generic-function 'particles_y-val :lambda-list '(m))
(cl:defmethod particles_y-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:particles_y-val is deprecated.  Use vector_slam_msgs-srv:particles_y instead.")
  (particles_y m))

(cl:ensure-generic-function 'particles_weight-val :lambda-list '(m))
(cl:defmethod particles_weight-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:particles_weight-val is deprecated.  Use vector_slam_msgs-srv:particles_weight instead.")
  (particles_weight m))

(cl:ensure-generic-function 'locations_weight-val :lambda-list '(m))
(cl:defmethod locations_weight-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:locations_weight-val is deprecated.  Use vector_slam_msgs-srv:locations_weight instead.")
  (locations_weight m))

(cl:ensure-generic-function 'err_code-val :lambda-list '(m))
(cl:defmethod err_code-val ((m <CobotRemoteInterfaceSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-srv:err_code-val is deprecated.  Use vector_slam_msgs-srv:err_code instead.")
  (err_code m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotRemoteInterfaceSrv-response>) ostream)
  "Serializes a message object of type '<CobotRemoteInterfaceSrv-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'loc_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'loc_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'orientation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'particles_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'particles_x))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'particles_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'particles_y))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'particles_weight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'particles_weight))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'locations_weight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'locations_weight))
  (cl:let* ((signed (cl:slot-value msg 'err_code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotRemoteInterfaceSrv-response>) istream)
  "Deserializes a message object of type '<CobotRemoteInterfaceSrv-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'loc_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'loc_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'orientation) (roslisp-utils:decode-single-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'particles_x) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'particles_x)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'particles_y) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'particles_y)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'particles_weight) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'particles_weight)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'locations_weight) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'locations_weight)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'err_code) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotRemoteInterfaceSrv-response>)))
  "Returns string type for a service object of type '<CobotRemoteInterfaceSrv-response>"
  "vector_slam_msgs/CobotRemoteInterfaceSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotRemoteInterfaceSrv-response)))
  "Returns string type for a service object of type 'CobotRemoteInterfaceSrv-response"
  "vector_slam_msgs/CobotRemoteInterfaceSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotRemoteInterfaceSrv-response>)))
  "Returns md5sum for a message object of type '<CobotRemoteInterfaceSrv-response>"
  "01146b8ee6bc341b195eb59880324094")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotRemoteInterfaceSrv-response)))
  "Returns md5sum for a message object of type 'CobotRemoteInterfaceSrv-response"
  "01146b8ee6bc341b195eb59880324094")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotRemoteInterfaceSrv-response>)))
  "Returns full string definition for message of type '<CobotRemoteInterfaceSrv-response>"
  (cl:format cl:nil "~%float32 loc_x~%float32 loc_y~%float32 orientation~%~%float32[] particles_x~%float32[] particles_y~%float32[] particles_weight~%float32[] locations_weight~%~%int8 err_code~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotRemoteInterfaceSrv-response)))
  "Returns full string definition for message of type 'CobotRemoteInterfaceSrv-response"
  (cl:format cl:nil "~%float32 loc_x~%float32 loc_y~%float32 orientation~%~%float32[] particles_x~%float32[] particles_y~%float32[] particles_weight~%float32[] locations_weight~%~%int8 err_code~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotRemoteInterfaceSrv-response>))
  (cl:+ 0
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'particles_x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'particles_y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'particles_weight) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'locations_weight) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotRemoteInterfaceSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotRemoteInterfaceSrv-response
    (cl:cons ':loc_x (loc_x msg))
    (cl:cons ':loc_y (loc_y msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':particles_x (particles_x msg))
    (cl:cons ':particles_y (particles_y msg))
    (cl:cons ':particles_weight (particles_weight msg))
    (cl:cons ':locations_weight (locations_weight msg))
    (cl:cons ':err_code (err_code msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'CobotRemoteInterfaceSrv)))
  'CobotRemoteInterfaceSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'CobotRemoteInterfaceSrv)))
  'CobotRemoteInterfaceSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotRemoteInterfaceSrv)))
  "Returns string type for a service object of type '<CobotRemoteInterfaceSrv>"
  "vector_slam_msgs/CobotRemoteInterfaceSrv")
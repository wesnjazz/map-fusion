; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude CobotStatusMsg.msg.html

(cl:defclass <CobotStatusMsg> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (timestamp
    :reader timestamp
    :initarg :timestamp
    :type cl:float
    :initform 0.0)
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
   (currentNavCommand
    :reader currentNavCommand
    :initarg :currentNavCommand
    :type cl:fixnum
    :initform 0)
   (obsAvDir_x
    :reader obsAvDir_x
    :initarg :obsAvDir_x
    :type cl:float
    :initform 0.0)
   (obsAvDir_y
    :reader obsAvDir_y
    :initarg :obsAvDir_y
    :type cl:float
    :initform 0.0)
   (pathBlocked
    :reader pathBlocked
    :initarg :pathBlocked
    :type cl:boolean
    :initform cl:nil)
   (batteryVoltage
    :reader batteryVoltage
    :initarg :batteryVoltage
    :type cl:float
    :initform 0.0)
   (emergencyStop
    :reader emergencyStop
    :initarg :emergencyStop
    :type cl:boolean
    :initform cl:nil)
   (cobotMode
    :reader cobotMode
    :initarg :cobotMode
    :type cl:fixnum
    :initform 0)
   (currentCommand
    :reader currentCommand
    :initarg :currentCommand
    :type cl:fixnum
    :initform 0)
   (navComplete
    :reader navComplete
    :initarg :navComplete
    :type cl:boolean
    :initform cl:nil)
   (currentEdge
    :reader currentEdge
    :initarg :currentEdge
    :type cl:integer
    :initform 0)
   (edgeProgress
    :reader edgeProgress
    :initarg :edgeProgress
    :type cl:float
    :initform 0.0)
   (edgeRemaining
    :reader edgeRemaining
    :initarg :edgeRemaining
    :type cl:float
    :initform 0.0)
   (edgeNavDuration
    :reader edgeNavDuration
    :initarg :edgeNavDuration
    :type cl:float
    :initform 0.0)
   (pathPlan_x
    :reader pathPlan_x
    :initarg :pathPlan_x
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (pathPlan_y
    :reader pathPlan_y
    :initarg :pathPlan_y
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass CobotStatusMsg (<CobotStatusMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CobotStatusMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CobotStatusMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<CobotStatusMsg> is deprecated: use vector_slam_msgs-msg:CobotStatusMsg instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:header-val is deprecated.  Use vector_slam_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:timestamp-val is deprecated.  Use vector_slam_msgs-msg:timestamp instead.")
  (timestamp m))

(cl:ensure-generic-function 'loc_x-val :lambda-list '(m))
(cl:defmethod loc_x-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:loc_x-val is deprecated.  Use vector_slam_msgs-msg:loc_x instead.")
  (loc_x m))

(cl:ensure-generic-function 'loc_y-val :lambda-list '(m))
(cl:defmethod loc_y-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:loc_y-val is deprecated.  Use vector_slam_msgs-msg:loc_y instead.")
  (loc_y m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:orientation-val is deprecated.  Use vector_slam_msgs-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'particles_x-val :lambda-list '(m))
(cl:defmethod particles_x-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:particles_x-val is deprecated.  Use vector_slam_msgs-msg:particles_x instead.")
  (particles_x m))

(cl:ensure-generic-function 'particles_y-val :lambda-list '(m))
(cl:defmethod particles_y-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:particles_y-val is deprecated.  Use vector_slam_msgs-msg:particles_y instead.")
  (particles_y m))

(cl:ensure-generic-function 'particles_weight-val :lambda-list '(m))
(cl:defmethod particles_weight-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:particles_weight-val is deprecated.  Use vector_slam_msgs-msg:particles_weight instead.")
  (particles_weight m))

(cl:ensure-generic-function 'locations_weight-val :lambda-list '(m))
(cl:defmethod locations_weight-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:locations_weight-val is deprecated.  Use vector_slam_msgs-msg:locations_weight instead.")
  (locations_weight m))

(cl:ensure-generic-function 'currentNavCommand-val :lambda-list '(m))
(cl:defmethod currentNavCommand-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:currentNavCommand-val is deprecated.  Use vector_slam_msgs-msg:currentNavCommand instead.")
  (currentNavCommand m))

(cl:ensure-generic-function 'obsAvDir_x-val :lambda-list '(m))
(cl:defmethod obsAvDir_x-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:obsAvDir_x-val is deprecated.  Use vector_slam_msgs-msg:obsAvDir_x instead.")
  (obsAvDir_x m))

(cl:ensure-generic-function 'obsAvDir_y-val :lambda-list '(m))
(cl:defmethod obsAvDir_y-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:obsAvDir_y-val is deprecated.  Use vector_slam_msgs-msg:obsAvDir_y instead.")
  (obsAvDir_y m))

(cl:ensure-generic-function 'pathBlocked-val :lambda-list '(m))
(cl:defmethod pathBlocked-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:pathBlocked-val is deprecated.  Use vector_slam_msgs-msg:pathBlocked instead.")
  (pathBlocked m))

(cl:ensure-generic-function 'batteryVoltage-val :lambda-list '(m))
(cl:defmethod batteryVoltage-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:batteryVoltage-val is deprecated.  Use vector_slam_msgs-msg:batteryVoltage instead.")
  (batteryVoltage m))

(cl:ensure-generic-function 'emergencyStop-val :lambda-list '(m))
(cl:defmethod emergencyStop-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:emergencyStop-val is deprecated.  Use vector_slam_msgs-msg:emergencyStop instead.")
  (emergencyStop m))

(cl:ensure-generic-function 'cobotMode-val :lambda-list '(m))
(cl:defmethod cobotMode-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:cobotMode-val is deprecated.  Use vector_slam_msgs-msg:cobotMode instead.")
  (cobotMode m))

(cl:ensure-generic-function 'currentCommand-val :lambda-list '(m))
(cl:defmethod currentCommand-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:currentCommand-val is deprecated.  Use vector_slam_msgs-msg:currentCommand instead.")
  (currentCommand m))

(cl:ensure-generic-function 'navComplete-val :lambda-list '(m))
(cl:defmethod navComplete-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:navComplete-val is deprecated.  Use vector_slam_msgs-msg:navComplete instead.")
  (navComplete m))

(cl:ensure-generic-function 'currentEdge-val :lambda-list '(m))
(cl:defmethod currentEdge-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:currentEdge-val is deprecated.  Use vector_slam_msgs-msg:currentEdge instead.")
  (currentEdge m))

(cl:ensure-generic-function 'edgeProgress-val :lambda-list '(m))
(cl:defmethod edgeProgress-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:edgeProgress-val is deprecated.  Use vector_slam_msgs-msg:edgeProgress instead.")
  (edgeProgress m))

(cl:ensure-generic-function 'edgeRemaining-val :lambda-list '(m))
(cl:defmethod edgeRemaining-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:edgeRemaining-val is deprecated.  Use vector_slam_msgs-msg:edgeRemaining instead.")
  (edgeRemaining m))

(cl:ensure-generic-function 'edgeNavDuration-val :lambda-list '(m))
(cl:defmethod edgeNavDuration-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:edgeNavDuration-val is deprecated.  Use vector_slam_msgs-msg:edgeNavDuration instead.")
  (edgeNavDuration m))

(cl:ensure-generic-function 'pathPlan_x-val :lambda-list '(m))
(cl:defmethod pathPlan_x-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:pathPlan_x-val is deprecated.  Use vector_slam_msgs-msg:pathPlan_x instead.")
  (pathPlan_x m))

(cl:ensure-generic-function 'pathPlan_y-val :lambda-list '(m))
(cl:defmethod pathPlan_y-val ((m <CobotStatusMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:pathPlan_y-val is deprecated.  Use vector_slam_msgs-msg:pathPlan_y instead.")
  (pathPlan_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CobotStatusMsg>) ostream)
  "Serializes a message object of type '<CobotStatusMsg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'timestamp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'currentNavCommand)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'currentNavCommand)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obsAvDir_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obsAvDir_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pathBlocked) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'batteryVoltage))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'emergencyStop) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'cobotMode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'currentCommand)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'navComplete) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'currentEdge)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'edgeProgress))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'edgeRemaining))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'edgeNavDuration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'pathPlan_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'pathPlan_x))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'pathPlan_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'pathPlan_y))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CobotStatusMsg>) istream)
  "Deserializes a message object of type '<CobotStatusMsg>"
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
    (cl:setf (cl:slot-value msg 'timestamp) (roslisp-utils:decode-double-float-bits bits)))
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'currentNavCommand)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'currentNavCommand)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obsAvDir_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obsAvDir_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'pathBlocked) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'batteryVoltage) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'emergencyStop) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'cobotMode) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'currentCommand) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:slot-value msg 'navComplete) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'currentEdge) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'edgeProgress) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'edgeRemaining) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'edgeNavDuration) (roslisp-utils:decode-double-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'pathPlan_x) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'pathPlan_x)))
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
  (cl:setf (cl:slot-value msg 'pathPlan_y) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'pathPlan_y)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CobotStatusMsg>)))
  "Returns string type for a message object of type '<CobotStatusMsg>"
  "vector_slam_msgs/CobotStatusMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CobotStatusMsg)))
  "Returns string type for a message object of type 'CobotStatusMsg"
  "vector_slam_msgs/CobotStatusMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CobotStatusMsg>)))
  "Returns md5sum for a message object of type '<CobotStatusMsg>"
  "4e8dff9d792649b915399841b6e125a2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CobotStatusMsg)))
  "Returns md5sum for a message object of type 'CobotStatusMsg"
  "4e8dff9d792649b915399841b6e125a2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CobotStatusMsg>)))
  "Returns full string definition for message of type '<CobotStatusMsg>"
  (cl:format cl:nil "Header header~%~%float64 timestamp~%~%float32 loc_x~%float32 loc_y~%float32 orientation~%~%float32[] particles_x~%float32[] particles_y~%float32[] particles_weight~%float32[] locations_weight~%~%uint16 currentNavCommand~%float32 obsAvDir_x~%float32 obsAvDir_y~%bool pathBlocked~%~%float32 batteryVoltage~%bool emergencyStop~%~%# Cobot Operation modes:~%# 0 = JoystickMode~%# 1 = JoystickObstAvMode~%# 2 = MotionPrimitiveMode~%# 3 = MotionPrimitiveObstAvMode~%# 4 = TeleOpMode~%# 5 = TestMode~%# 6 = AllStopMode~%int16 cobotMode~%~%# Cobot Commands:~%# 0 = NavCmdNone~%# 1 = NavCmdGoTo~%# 2 = NavCmdMoveStraight~%# 3 = NavCmdMoveDownCorridor~%# 4 = NavCmdIntegratedTurn~%# 5 = NavCmdInPlaceTurn~%# 6 = NavCmdTurnAndMoveStraight~%# 7 = NavCmdAbort~%int16 currentCommand~%bool navComplete~%~%int32 currentEdge~%float32 edgeProgress~%float32 edgeRemaining~%float64 edgeNavDuration~%~%float32[] pathPlan_x~%float32[] pathPlan_y~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CobotStatusMsg)))
  "Returns full string definition for message of type 'CobotStatusMsg"
  (cl:format cl:nil "Header header~%~%float64 timestamp~%~%float32 loc_x~%float32 loc_y~%float32 orientation~%~%float32[] particles_x~%float32[] particles_y~%float32[] particles_weight~%float32[] locations_weight~%~%uint16 currentNavCommand~%float32 obsAvDir_x~%float32 obsAvDir_y~%bool pathBlocked~%~%float32 batteryVoltage~%bool emergencyStop~%~%# Cobot Operation modes:~%# 0 = JoystickMode~%# 1 = JoystickObstAvMode~%# 2 = MotionPrimitiveMode~%# 3 = MotionPrimitiveObstAvMode~%# 4 = TeleOpMode~%# 5 = TestMode~%# 6 = AllStopMode~%int16 cobotMode~%~%# Cobot Commands:~%# 0 = NavCmdNone~%# 1 = NavCmdGoTo~%# 2 = NavCmdMoveStraight~%# 3 = NavCmdMoveDownCorridor~%# 4 = NavCmdIntegratedTurn~%# 5 = NavCmdInPlaceTurn~%# 6 = NavCmdTurnAndMoveStraight~%# 7 = NavCmdAbort~%int16 currentCommand~%bool navComplete~%~%int32 currentEdge~%float32 edgeProgress~%float32 edgeRemaining~%float64 edgeNavDuration~%~%float32[] pathPlan_x~%float32[] pathPlan_y~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CobotStatusMsg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'particles_x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'particles_y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'particles_weight) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'locations_weight) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     2
     4
     4
     1
     4
     1
     2
     2
     1
     4
     4
     4
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'pathPlan_x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'pathPlan_y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CobotStatusMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'CobotStatusMsg
    (cl:cons ':header (header msg))
    (cl:cons ':timestamp (timestamp msg))
    (cl:cons ':loc_x (loc_x msg))
    (cl:cons ':loc_y (loc_y msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':particles_x (particles_x msg))
    (cl:cons ':particles_y (particles_y msg))
    (cl:cons ':particles_weight (particles_weight msg))
    (cl:cons ':locations_weight (locations_weight msg))
    (cl:cons ':currentNavCommand (currentNavCommand msg))
    (cl:cons ':obsAvDir_x (obsAvDir_x msg))
    (cl:cons ':obsAvDir_y (obsAvDir_y msg))
    (cl:cons ':pathBlocked (pathBlocked msg))
    (cl:cons ':batteryVoltage (batteryVoltage msg))
    (cl:cons ':emergencyStop (emergencyStop msg))
    (cl:cons ':cobotMode (cobotMode msg))
    (cl:cons ':currentCommand (currentCommand msg))
    (cl:cons ':navComplete (navComplete msg))
    (cl:cons ':currentEdge (currentEdge msg))
    (cl:cons ':edgeProgress (edgeProgress msg))
    (cl:cons ':edgeRemaining (edgeRemaining msg))
    (cl:cons ':edgeNavDuration (edgeNavDuration msg))
    (cl:cons ':pathPlan_x (pathPlan_x msg))
    (cl:cons ':pathPlan_y (pathPlan_y msg))
))

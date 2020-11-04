; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude GuiMouseMoveEvent.msg.html

(cl:defclass <GuiMouseMoveEvent> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (location
    :reader location
    :initarg :location
    :type geometry_msgs-msg:Point32
    :initform (cl:make-instance 'geometry_msgs-msg:Point32))
   (buttons
    :reader buttons
    :initarg :buttons
    :type cl:integer
    :initform 0)
   (modifiers
    :reader modifiers
    :initarg :modifiers
    :type cl:integer
    :initform 0))
)

(cl:defclass GuiMouseMoveEvent (<GuiMouseMoveEvent>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GuiMouseMoveEvent>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GuiMouseMoveEvent)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<GuiMouseMoveEvent> is deprecated: use vector_slam_msgs-msg:GuiMouseMoveEvent instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GuiMouseMoveEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:header-val is deprecated.  Use vector_slam_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <GuiMouseMoveEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:location-val is deprecated.  Use vector_slam_msgs-msg:location instead.")
  (location m))

(cl:ensure-generic-function 'buttons-val :lambda-list '(m))
(cl:defmethod buttons-val ((m <GuiMouseMoveEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:buttons-val is deprecated.  Use vector_slam_msgs-msg:buttons instead.")
  (buttons m))

(cl:ensure-generic-function 'modifiers-val :lambda-list '(m))
(cl:defmethod modifiers-val ((m <GuiMouseMoveEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:modifiers-val is deprecated.  Use vector_slam_msgs-msg:modifiers instead.")
  (modifiers m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GuiMouseMoveEvent>) ostream)
  "Serializes a message object of type '<GuiMouseMoveEvent>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'location) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buttons)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'buttons)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'buttons)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'buttons)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'modifiers)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GuiMouseMoveEvent>) istream)
  "Deserializes a message object of type '<GuiMouseMoveEvent>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'location) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buttons)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'buttons)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'buttons)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'buttons)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GuiMouseMoveEvent>)))
  "Returns string type for a message object of type '<GuiMouseMoveEvent>"
  "vector_slam_msgs/GuiMouseMoveEvent")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GuiMouseMoveEvent)))
  "Returns string type for a message object of type 'GuiMouseMoveEvent"
  "vector_slam_msgs/GuiMouseMoveEvent")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GuiMouseMoveEvent>)))
  "Returns md5sum for a message object of type '<GuiMouseMoveEvent>"
  "53a26cd1bb23d1ed61768f55e50f7f84")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GuiMouseMoveEvent)))
  "Returns md5sum for a message object of type 'GuiMouseMoveEvent"
  "53a26cd1bb23d1ed61768f55e50f7f84")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GuiMouseMoveEvent>)))
  "Returns full string definition for message of type '<GuiMouseMoveEvent>"
  (cl:format cl:nil "# Feedback in terms of mouse clicks on the localization GUI.~%#~%~%# Standard header. The frame should normally be \"map\", since the localization~%# GUI reports coordinates in the world (map) frame.~%std_msgs/Header header~%~%# The 2D location where the mouse pointer was moved to. The z coordinate of the~%# Point32 should be set to 0 by publishers, and ignored by subscribers.~%geometry_msgs/Point32 location~%~%# Binary mask of mouse buttons that were depressed, as enumerated by the~%# Qt::MouseButton enumerator. Comon values are:~%# 0x00 = No button~%# 0x01 = Left button~%# 0x02 = Right button~%# 0x04 = Middle button~%uint32 buttons~%~%# Binary mask of keyboard modifiers that were active when the mouse event occurred.~%# 0x01 = Alt key  modifier~%# 0x02 = Ctrl key modifier~%# 0x04 = Shift key modifier~%uint32 modifiers~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GuiMouseMoveEvent)))
  "Returns full string definition for message of type 'GuiMouseMoveEvent"
  (cl:format cl:nil "# Feedback in terms of mouse clicks on the localization GUI.~%#~%~%# Standard header. The frame should normally be \"map\", since the localization~%# GUI reports coordinates in the world (map) frame.~%std_msgs/Header header~%~%# The 2D location where the mouse pointer was moved to. The z coordinate of the~%# Point32 should be set to 0 by publishers, and ignored by subscribers.~%geometry_msgs/Point32 location~%~%# Binary mask of mouse buttons that were depressed, as enumerated by the~%# Qt::MouseButton enumerator. Comon values are:~%# 0x00 = No button~%# 0x01 = Left button~%# 0x02 = Right button~%# 0x04 = Middle button~%uint32 buttons~%~%# Binary mask of keyboard modifiers that were active when the mouse event occurred.~%# 0x01 = Alt key  modifier~%# 0x02 = Ctrl key modifier~%# 0x04 = Shift key modifier~%uint32 modifiers~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GuiMouseMoveEvent>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'location))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GuiMouseMoveEvent>))
  "Converts a ROS message object to a list"
  (cl:list 'GuiMouseMoveEvent
    (cl:cons ':header (header msg))
    (cl:cons ':location (location msg))
    (cl:cons ':buttons (buttons msg))
    (cl:cons ':modifiers (modifiers msg))
))

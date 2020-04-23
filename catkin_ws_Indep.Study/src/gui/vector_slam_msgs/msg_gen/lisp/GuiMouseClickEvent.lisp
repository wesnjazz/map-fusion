; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude GuiMouseClickEvent.msg.html

(cl:defclass <GuiMouseClickEvent> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (mouse_down
    :reader mouse_down
    :initarg :mouse_down
    :type geometry_msgs-msg:Point32
    :initform (cl:make-instance 'geometry_msgs-msg:Point32))
   (mouse_up
    :reader mouse_up
    :initarg :mouse_up
    :type geometry_msgs-msg:Point32
    :initform (cl:make-instance 'geometry_msgs-msg:Point32))
   (modifiers
    :reader modifiers
    :initarg :modifiers
    :type cl:integer
    :initform 0))
)

(cl:defclass GuiMouseClickEvent (<GuiMouseClickEvent>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GuiMouseClickEvent>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GuiMouseClickEvent)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<GuiMouseClickEvent> is deprecated: use vector_slam_msgs-msg:GuiMouseClickEvent instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GuiMouseClickEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:header-val is deprecated.  Use vector_slam_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'mouse_down-val :lambda-list '(m))
(cl:defmethod mouse_down-val ((m <GuiMouseClickEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:mouse_down-val is deprecated.  Use vector_slam_msgs-msg:mouse_down instead.")
  (mouse_down m))

(cl:ensure-generic-function 'mouse_up-val :lambda-list '(m))
(cl:defmethod mouse_up-val ((m <GuiMouseClickEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:mouse_up-val is deprecated.  Use vector_slam_msgs-msg:mouse_up instead.")
  (mouse_up m))

(cl:ensure-generic-function 'modifiers-val :lambda-list '(m))
(cl:defmethod modifiers-val ((m <GuiMouseClickEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:modifiers-val is deprecated.  Use vector_slam_msgs-msg:modifiers instead.")
  (modifiers m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GuiMouseClickEvent>) ostream)
  "Serializes a message object of type '<GuiMouseClickEvent>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'mouse_down) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'mouse_up) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'modifiers)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GuiMouseClickEvent>) istream)
  "Deserializes a message object of type '<GuiMouseClickEvent>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'mouse_down) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'mouse_up) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GuiMouseClickEvent>)))
  "Returns string type for a message object of type '<GuiMouseClickEvent>"
  "vector_slam_msgs/GuiMouseClickEvent")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GuiMouseClickEvent)))
  "Returns string type for a message object of type 'GuiMouseClickEvent"
  "vector_slam_msgs/GuiMouseClickEvent")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GuiMouseClickEvent>)))
  "Returns md5sum for a message object of type '<GuiMouseClickEvent>"
  "024d093145787d5820945b81ee2e9ed4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GuiMouseClickEvent)))
  "Returns md5sum for a message object of type 'GuiMouseClickEvent"
  "024d093145787d5820945b81ee2e9ed4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GuiMouseClickEvent>)))
  "Returns full string definition for message of type '<GuiMouseClickEvent>"
  (cl:format cl:nil "# Feedback in terms of mouse clicks on the localization GUI.~%#~%~%# Standard header. The frame should normally be \"map\", since the localization~%# GUI reports coordinates in the world (map) frame.~%std_msgs/Header header~%~%# The 2D location where the \"MouseDown\" event occurred. The z coordinate of the~%# Point32 should be set to 0 by publishers, and ignored by subscribers.~%geometry_msgs/Point32 mouse_down~%~%# The 2D location where the \"MouseUp\" event occurred. The z coordinate of the~%# Point32 should be set to 0 by publishers, and ignored by subscribers.~%geometry_msgs/Point32 mouse_up~%~%# Binary mask of keyboard modifiers that were active when the mouse event occurred.~%# 0x01 = Alt key  modifier~%# 0x02 = Ctrl key modifier~%# 0x04 = Shift key modifier~%uint32 modifiers~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GuiMouseClickEvent)))
  "Returns full string definition for message of type 'GuiMouseClickEvent"
  (cl:format cl:nil "# Feedback in terms of mouse clicks on the localization GUI.~%#~%~%# Standard header. The frame should normally be \"map\", since the localization~%# GUI reports coordinates in the world (map) frame.~%std_msgs/Header header~%~%# The 2D location where the \"MouseDown\" event occurred. The z coordinate of the~%# Point32 should be set to 0 by publishers, and ignored by subscribers.~%geometry_msgs/Point32 mouse_down~%~%# The 2D location where the \"MouseUp\" event occurred. The z coordinate of the~%# Point32 should be set to 0 by publishers, and ignored by subscribers.~%geometry_msgs/Point32 mouse_up~%~%# Binary mask of keyboard modifiers that were active when the mouse event occurred.~%# 0x01 = Alt key  modifier~%# 0x02 = Ctrl key modifier~%# 0x04 = Shift key modifier~%uint32 modifiers~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GuiMouseClickEvent>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'mouse_down))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'mouse_up))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GuiMouseClickEvent>))
  "Converts a ROS message object to a list"
  (cl:list 'GuiMouseClickEvent
    (cl:cons ':header (header msg))
    (cl:cons ':mouse_down (mouse_down msg))
    (cl:cons ':mouse_up (mouse_up msg))
    (cl:cons ':modifiers (modifiers msg))
))

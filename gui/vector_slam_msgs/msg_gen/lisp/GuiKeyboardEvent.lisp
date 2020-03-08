; Auto-generated. Do not edit!


(cl:in-package vector_slam_msgs-msg)


;//! \htmlinclude GuiKeyboardEvent.msg.html

(cl:defclass <GuiKeyboardEvent> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (keycode
    :reader keycode
    :initarg :keycode
    :type cl:integer
    :initform 0)
   (modifiers
    :reader modifiers
    :initarg :modifiers
    :type cl:integer
    :initform 0))
)

(cl:defclass GuiKeyboardEvent (<GuiKeyboardEvent>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GuiKeyboardEvent>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GuiKeyboardEvent)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vector_slam_msgs-msg:<GuiKeyboardEvent> is deprecated: use vector_slam_msgs-msg:GuiKeyboardEvent instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GuiKeyboardEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:header-val is deprecated.  Use vector_slam_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'keycode-val :lambda-list '(m))
(cl:defmethod keycode-val ((m <GuiKeyboardEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:keycode-val is deprecated.  Use vector_slam_msgs-msg:keycode instead.")
  (keycode m))

(cl:ensure-generic-function 'modifiers-val :lambda-list '(m))
(cl:defmethod modifiers-val ((m <GuiKeyboardEvent>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vector_slam_msgs-msg:modifiers-val is deprecated.  Use vector_slam_msgs-msg:modifiers instead.")
  (modifiers m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GuiKeyboardEvent>) ostream)
  "Serializes a message object of type '<GuiKeyboardEvent>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'keycode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'keycode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'keycode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'keycode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'modifiers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'modifiers)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GuiKeyboardEvent>) istream)
  "Deserializes a message object of type '<GuiKeyboardEvent>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'keycode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'keycode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'keycode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'keycode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'modifiers)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GuiKeyboardEvent>)))
  "Returns string type for a message object of type '<GuiKeyboardEvent>"
  "vector_slam_msgs/GuiKeyboardEvent")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GuiKeyboardEvent)))
  "Returns string type for a message object of type 'GuiKeyboardEvent"
  "vector_slam_msgs/GuiKeyboardEvent")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GuiKeyboardEvent>)))
  "Returns md5sum for a message object of type '<GuiKeyboardEvent>"
  "f0fec8e32de970ac60b5f38ede499ab5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GuiKeyboardEvent)))
  "Returns md5sum for a message object of type 'GuiKeyboardEvent"
  "f0fec8e32de970ac60b5f38ede499ab5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GuiKeyboardEvent>)))
  "Returns full string definition for message of type '<GuiKeyboardEvent>"
  (cl:format cl:nil "# Feedback in terms keyboard keypress events on the localization GUI.~%#~%~%# Standard header. The frame should normally be \"map\", since the localization~%# GUI reports coordinates in the world (map) frame.~%std_msgs/Header header~%~%# The Keycode constant, as enumerated in the Qt::Key enumerator.~%uint32 keycode~%~%# Binary mask of keyboard modifiers that were active when the mouse event occurred.~%# 0x01 = Alt key  modifier~%# 0x02 = Ctrl key modifier~%# 0x04 = Shift key modifier~%uint32 modifiers~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GuiKeyboardEvent)))
  "Returns full string definition for message of type 'GuiKeyboardEvent"
  (cl:format cl:nil "# Feedback in terms keyboard keypress events on the localization GUI.~%#~%~%# Standard header. The frame should normally be \"map\", since the localization~%# GUI reports coordinates in the world (map) frame.~%std_msgs/Header header~%~%# The Keycode constant, as enumerated in the Qt::Key enumerator.~%uint32 keycode~%~%# Binary mask of keyboard modifiers that were active when the mouse event occurred.~%# 0x01 = Alt key  modifier~%# 0x02 = Ctrl key modifier~%# 0x04 = Shift key modifier~%uint32 modifiers~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GuiKeyboardEvent>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GuiKeyboardEvent>))
  "Converts a ROS message object to a list"
  (cl:list 'GuiKeyboardEvent
    (cl:cons ':header (header msg))
    (cl:cons ':keycode (keycode msg))
    (cl:cons ':modifiers (modifiers msg))
))

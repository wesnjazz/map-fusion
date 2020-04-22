; Auto-generated. Do not edit!


(cl:in-package visual_feature_server-srv)


;//! \htmlinclude PickleSrv-request.msg.html

(cl:defclass <PickleSrv-request> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (filePath
    :reader filePath
    :initarg :filePath
    :type cl:string
    :initform ""))
)

(cl:defclass PickleSrv-request (<PickleSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PickleSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PickleSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_feature_server-srv:<PickleSrv-request> is deprecated: use visual_feature_server-srv:PickleSrv-request instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <PickleSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-srv:data-val is deprecated.  Use visual_feature_server-srv:data instead.")
  (data m))

(cl:ensure-generic-function 'filePath-val :lambda-list '(m))
(cl:defmethod filePath-val ((m <PickleSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-srv:filePath-val is deprecated.  Use visual_feature_server-srv:filePath instead.")
  (filePath m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PickleSrv-request>) ostream)
  "Serializes a message object of type '<PickleSrv-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
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
   (cl:slot-value msg 'data))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'filePath))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'filePath))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PickleSrv-request>) istream)
  "Deserializes a message object of type '<PickleSrv-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
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
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'filePath) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'filePath) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PickleSrv-request>)))
  "Returns string type for a service object of type '<PickleSrv-request>"
  "visual_feature_server/PickleSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PickleSrv-request)))
  "Returns string type for a service object of type 'PickleSrv-request"
  "visual_feature_server/PickleSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PickleSrv-request>)))
  "Returns md5sum for a message object of type '<PickleSrv-request>"
  "eb297acc7accecca58502296783fbde0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PickleSrv-request)))
  "Returns md5sum for a message object of type 'PickleSrv-request"
  "eb297acc7accecca58502296783fbde0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PickleSrv-request>)))
  "Returns full string definition for message of type '<PickleSrv-request>"
  (cl:format cl:nil "float64[] data~%string filePath~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PickleSrv-request)))
  "Returns full string definition for message of type 'PickleSrv-request"
  (cl:format cl:nil "float64[] data~%string filePath~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PickleSrv-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:length (cl:slot-value msg 'filePath))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PickleSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PickleSrv-request
    (cl:cons ':data (data msg))
    (cl:cons ':filePath (filePath msg))
))
;//! \htmlinclude PickleSrv-response.msg.html

(cl:defclass <PickleSrv-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass PickleSrv-response (<PickleSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PickleSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PickleSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_feature_server-srv:<PickleSrv-response> is deprecated: use visual_feature_server-srv:PickleSrv-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <PickleSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_feature_server-srv:success-val is deprecated.  Use visual_feature_server-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PickleSrv-response>) ostream)
  "Serializes a message object of type '<PickleSrv-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PickleSrv-response>) istream)
  "Deserializes a message object of type '<PickleSrv-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PickleSrv-response>)))
  "Returns string type for a service object of type '<PickleSrv-response>"
  "visual_feature_server/PickleSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PickleSrv-response)))
  "Returns string type for a service object of type 'PickleSrv-response"
  "visual_feature_server/PickleSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PickleSrv-response>)))
  "Returns md5sum for a message object of type '<PickleSrv-response>"
  "eb297acc7accecca58502296783fbde0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PickleSrv-response)))
  "Returns md5sum for a message object of type 'PickleSrv-response"
  "eb297acc7accecca58502296783fbde0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PickleSrv-response>)))
  "Returns full string definition for message of type '<PickleSrv-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PickleSrv-response)))
  "Returns full string definition for message of type 'PickleSrv-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PickleSrv-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PickleSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PickleSrv-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PickleSrv)))
  'PickleSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PickleSrv)))
  'PickleSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PickleSrv)))
  "Returns string type for a service object of type '<PickleSrv>"
  "visual_feature_server/PickleSrv")
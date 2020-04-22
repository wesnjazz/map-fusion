;; Auto-generated. Do not edit!


(when (boundp 'visual_feature_server::PickleSrv)
  (if (not (find-package "VISUAL_FEATURE_SERVER"))
    (make-package "VISUAL_FEATURE_SERVER"))
  (shadow 'PickleSrv (find-package "VISUAL_FEATURE_SERVER")))
(unless (find-package "VISUAL_FEATURE_SERVER::PICKLESRV")
  (make-package "VISUAL_FEATURE_SERVER::PICKLESRV"))
(unless (find-package "VISUAL_FEATURE_SERVER::PICKLESRVREQUEST")
  (make-package "VISUAL_FEATURE_SERVER::PICKLESRVREQUEST"))
(unless (find-package "VISUAL_FEATURE_SERVER::PICKLESRVRESPONSE")
  (make-package "VISUAL_FEATURE_SERVER::PICKLESRVRESPONSE"))

(in-package "ROS")





(defclass visual_feature_server::PickleSrvRequest
  :super ros::object
  :slots (_data _filePath ))

(defmethod visual_feature_server::PickleSrvRequest
  (:init
   (&key
    ((:data __data) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:filePath __filePath) "")
    )
   (send-super :init)
   (setq _data __data)
   (setq _filePath (string __filePath))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:filePath
   (&optional __filePath)
   (if __filePath (setq _filePath __filePath)) _filePath)
  (:serialization-length
   ()
   (+
    ;; float64[] _data
    (* 8    (length _data)) 4
    ;; string _filePath
    4 (length _filePath)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _data
     (write-long (length _data) s)
     (dotimes (i (length _data))
       (sys::poke (elt _data i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; string _filePath
       (write-long (length _filePath) s) (princ _filePath s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _data (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _data i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; string _filePath
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _filePath (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass visual_feature_server::PickleSrvResponse
  :super ros::object
  :slots (_success ))

(defmethod visual_feature_server::PickleSrvResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass visual_feature_server::PickleSrv
  :super ros::object
  :slots ())

(setf (get visual_feature_server::PickleSrv :md5sum-) "eb297acc7accecca58502296783fbde0")
(setf (get visual_feature_server::PickleSrv :datatype-) "visual_feature_server/PickleSrv")
(setf (get visual_feature_server::PickleSrv :request) visual_feature_server::PickleSrvRequest)
(setf (get visual_feature_server::PickleSrv :response) visual_feature_server::PickleSrvResponse)

(defmethod visual_feature_server::PickleSrvRequest
  (:response () (instance visual_feature_server::PickleSrvResponse :init)))

(setf (get visual_feature_server::PickleSrvRequest :md5sum-) "eb297acc7accecca58502296783fbde0")
(setf (get visual_feature_server::PickleSrvRequest :datatype-) "visual_feature_server/PickleSrvRequest")
(setf (get visual_feature_server::PickleSrvRequest :definition-)
      "float64[] data
string filePath

---
bool success

")

(setf (get visual_feature_server::PickleSrvResponse :md5sum-) "eb297acc7accecca58502296783fbde0")
(setf (get visual_feature_server::PickleSrvResponse :datatype-) "visual_feature_server/PickleSrvResponse")
(setf (get visual_feature_server::PickleSrvResponse :definition-)
      "float64[] data
string filePath

---
bool success

")



(provide :visual_feature_server/PickleSrv "eb297acc7accecca58502296783fbde0")



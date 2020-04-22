;; Auto-generated. Do not edit!


(when (boundp 'visual_feature_server::Convert2DPoint)
  (if (not (find-package "VISUAL_FEATURE_SERVER"))
    (make-package "VISUAL_FEATURE_SERVER"))
  (shadow 'Convert2DPoint (find-package "VISUAL_FEATURE_SERVER")))
(unless (find-package "VISUAL_FEATURE_SERVER::CONVERT2DPOINT")
  (make-package "VISUAL_FEATURE_SERVER::CONVERT2DPOINT"))
(unless (find-package "VISUAL_FEATURE_SERVER::CONVERT2DPOINTREQUEST")
  (make-package "VISUAL_FEATURE_SERVER::CONVERT2DPOINTREQUEST"))
(unless (find-package "VISUAL_FEATURE_SERVER::CONVERT2DPOINTRESPONSE")
  (make-package "VISUAL_FEATURE_SERVER::CONVERT2DPOINTRESPONSE"))

(in-package "ROS")





(defclass visual_feature_server::Convert2DPointRequest
  :super ros::object
  :slots (_stamp _x _y _source_frame _destination_frame ))

(defmethod visual_feature_server::Convert2DPointRequest
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:x __x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y __y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:source_frame __source_frame) "")
    ((:destination_frame __destination_frame) "")
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _x __x)
   (setq _y __y)
   (setq _source_frame (string __source_frame))
   (setq _destination_frame (string __destination_frame))
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:source_frame
   (&optional __source_frame)
   (if __source_frame (setq _source_frame __source_frame)) _source_frame)
  (:destination_frame
   (&optional __destination_frame)
   (if __destination_frame (setq _destination_frame __destination_frame)) _destination_frame)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64[] _x
    (* 8    (length _x)) 4
    ;; float64[] _y
    (* 8    (length _y)) 4
    ;; string _source_frame
    4 (length _source_frame)
    ;; string _destination_frame
    4 (length _destination_frame)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64[] _x
     (write-long (length _x) s)
     (dotimes (i (length _x))
       (sys::poke (elt _x i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _y
     (write-long (length _y) s)
     (dotimes (i (length _y))
       (sys::poke (elt _y i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; string _source_frame
       (write-long (length _source_frame) s) (princ _source_frame s)
     ;; string _destination_frame
       (write-long (length _destination_frame) s) (princ _destination_frame s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; string _source_frame
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _source_frame (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _destination_frame
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _destination_frame (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass visual_feature_server::Convert2DPointResponse
  :super ros::object
  :slots (_x_source _y_source _z_source _x_dest _y_dest _z_dest ))

(defmethod visual_feature_server::Convert2DPointResponse
  (:init
   (&key
    ((:x_source __x_source) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y_source __y_source) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:z_source __z_source) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:x_dest __x_dest) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y_dest __y_dest) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:z_dest __z_dest) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _x_source __x_source)
   (setq _y_source __y_source)
   (setq _z_source __z_source)
   (setq _x_dest __x_dest)
   (setq _y_dest __y_dest)
   (setq _z_dest __z_dest)
   self)
  (:x_source
   (&optional __x_source)
   (if __x_source (setq _x_source __x_source)) _x_source)
  (:y_source
   (&optional __y_source)
   (if __y_source (setq _y_source __y_source)) _y_source)
  (:z_source
   (&optional __z_source)
   (if __z_source (setq _z_source __z_source)) _z_source)
  (:x_dest
   (&optional __x_dest)
   (if __x_dest (setq _x_dest __x_dest)) _x_dest)
  (:y_dest
   (&optional __y_dest)
   (if __y_dest (setq _y_dest __y_dest)) _y_dest)
  (:z_dest
   (&optional __z_dest)
   (if __z_dest (setq _z_dest __z_dest)) _z_dest)
  (:serialization-length
   ()
   (+
    ;; float64[] _x_source
    (* 8    (length _x_source)) 4
    ;; float64[] _y_source
    (* 8    (length _y_source)) 4
    ;; float64[] _z_source
    (* 8    (length _z_source)) 4
    ;; float64[] _x_dest
    (* 8    (length _x_dest)) 4
    ;; float64[] _y_dest
    (* 8    (length _y_dest)) 4
    ;; float64[] _z_dest
    (* 8    (length _z_dest)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _x_source
     (write-long (length _x_source) s)
     (dotimes (i (length _x_source))
       (sys::poke (elt _x_source i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _y_source
     (write-long (length _y_source) s)
     (dotimes (i (length _y_source))
       (sys::poke (elt _y_source i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _z_source
     (write-long (length _z_source) s)
     (dotimes (i (length _z_source))
       (sys::poke (elt _z_source i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _x_dest
     (write-long (length _x_dest) s)
     (dotimes (i (length _x_dest))
       (sys::poke (elt _x_dest i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _y_dest
     (write-long (length _y_dest) s)
     (dotimes (i (length _y_dest))
       (sys::poke (elt _y_dest i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _z_dest
     (write-long (length _z_dest) s)
     (dotimes (i (length _z_dest))
       (sys::poke (elt _z_dest i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _x_source
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x_source (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x_source i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _y_source
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y_source (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y_source i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _z_source
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _z_source (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _z_source i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _x_dest
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x_dest (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x_dest i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _y_dest
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y_dest (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y_dest i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _z_dest
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _z_dest (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _z_dest i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass visual_feature_server::Convert2DPoint
  :super ros::object
  :slots ())

(setf (get visual_feature_server::Convert2DPoint :md5sum-) "da24dbed0bfc78862b40c7bfe16c141e")
(setf (get visual_feature_server::Convert2DPoint :datatype-) "visual_feature_server/Convert2DPoint")
(setf (get visual_feature_server::Convert2DPoint :request) visual_feature_server::Convert2DPointRequest)
(setf (get visual_feature_server::Convert2DPoint :response) visual_feature_server::Convert2DPointResponse)

(defmethod visual_feature_server::Convert2DPointRequest
  (:response () (instance visual_feature_server::Convert2DPointResponse :init)))

(setf (get visual_feature_server::Convert2DPointRequest :md5sum-) "da24dbed0bfc78862b40c7bfe16c141e")
(setf (get visual_feature_server::Convert2DPointRequest :datatype-) "visual_feature_server/Convert2DPointRequest")
(setf (get visual_feature_server::Convert2DPointRequest :definition-)
      "time stamp
float64[] x
float64[] y
string source_frame
string destination_frame

---

float64[] x_source
float64[] y_source
float64[] z_source

float64[] x_dest
float64[] y_dest
float64[] z_dest

")

(setf (get visual_feature_server::Convert2DPointResponse :md5sum-) "da24dbed0bfc78862b40c7bfe16c141e")
(setf (get visual_feature_server::Convert2DPointResponse :datatype-) "visual_feature_server/Convert2DPointResponse")
(setf (get visual_feature_server::Convert2DPointResponse :definition-)
      "time stamp
float64[] x
float64[] y
string source_frame
string destination_frame

---

float64[] x_source
float64[] y_source
float64[] z_source

float64[] x_dest
float64[] y_dest
float64[] z_dest

")



(provide :visual_feature_server/Convert2DPoint "da24dbed0bfc78862b40c7bfe16c141e")



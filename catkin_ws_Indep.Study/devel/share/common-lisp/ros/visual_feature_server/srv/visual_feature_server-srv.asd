
(cl:in-package :asdf)

(defsystem "visual_feature_server-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Convert2DPoint" :depends-on ("_package_Convert2DPoint"))
    (:file "_package_Convert2DPoint" :depends-on ("_package"))
    (:file "PickleSrv" :depends-on ("_package_PickleSrv"))
    (:file "_package_PickleSrv" :depends-on ("_package"))
  ))
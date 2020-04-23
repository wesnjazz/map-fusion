
(cl:in-package :asdf)

(defsystem "vector_slam_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "LocalizationGuiCaptureSrv" :depends-on ("_package_LocalizationGuiCaptureSrv"))
    (:file "_package_LocalizationGuiCaptureSrv" :depends-on ("_package"))
    (:file "CobotLocalizationSrv" :depends-on ("_package_CobotLocalizationSrv"))
    (:file "_package_CobotLocalizationSrv" :depends-on ("_package"))
    (:file "CobotRemoteInterfaceSrv" :depends-on ("_package_CobotRemoteInterfaceSrv"))
    (:file "_package_CobotRemoteInterfaceSrv" :depends-on ("_package"))
  ))
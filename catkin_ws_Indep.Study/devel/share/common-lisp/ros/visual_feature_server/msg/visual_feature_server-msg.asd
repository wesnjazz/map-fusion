
(cl:in-package :asdf)

(defsystem "visual_feature_server-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "BlobFeatureMsg" :depends-on ("_package_BlobFeatureMsg"))
    (:file "_package_BlobFeatureMsg" :depends-on ("_package"))
    (:file "CornerFeatureMsg" :depends-on ("_package_CornerFeatureMsg"))
    (:file "_package_CornerFeatureMsg" :depends-on ("_package"))
    (:file "EdgeFeatureMsg" :depends-on ("_package_EdgeFeatureMsg"))
    (:file "_package_EdgeFeatureMsg" :depends-on ("_package"))
    (:file "FeatureMsg" :depends-on ("_package_FeatureMsg"))
    (:file "_package_FeatureMsg" :depends-on ("_package"))
    (:file "FeaturePoses" :depends-on ("_package_FeaturePoses"))
    (:file "_package_FeaturePoses" :depends-on ("_package"))
  ))
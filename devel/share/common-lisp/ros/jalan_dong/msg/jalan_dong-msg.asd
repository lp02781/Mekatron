
(cl:in-package :asdf)

(defsystem "jalan_dong-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "image_msgs" :depends-on ("_package_image_msgs"))
    (:file "_package_image_msgs" :depends-on ("_package"))
  ))
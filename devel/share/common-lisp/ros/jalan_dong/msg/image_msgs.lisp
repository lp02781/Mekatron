; Auto-generated. Do not edit!


(cl:in-package jalan_dong-msg)


;//! \htmlinclude image_msgs.msg.html

(cl:defclass <image_msgs> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:fixnum
    :initform 0)
   (y
    :reader y
    :initarg :y
    :type cl:fixnum
    :initform 0))
)

(cl:defclass image_msgs (<image_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <image_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'image_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jalan_dong-msg:<image_msgs> is deprecated: use jalan_dong-msg:image_msgs instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <image_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jalan_dong-msg:x-val is deprecated.  Use jalan_dong-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <image_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jalan_dong-msg:y-val is deprecated.  Use jalan_dong-msg:y instead.")
  (y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <image_msgs>) ostream)
  "Serializes a message object of type '<image_msgs>"
  (cl:let* ((signed (cl:slot-value msg 'x)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <image_msgs>) istream)
  "Deserializes a message object of type '<image_msgs>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<image_msgs>)))
  "Returns string type for a message object of type '<image_msgs>"
  "jalan_dong/image_msgs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'image_msgs)))
  "Returns string type for a message object of type 'image_msgs"
  "jalan_dong/image_msgs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<image_msgs>)))
  "Returns md5sum for a message object of type '<image_msgs>"
  "6d78a6b8c9650c754bf0432d3d1707c3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'image_msgs)))
  "Returns md5sum for a message object of type 'image_msgs"
  "6d78a6b8c9650c754bf0432d3d1707c3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<image_msgs>)))
  "Returns full string definition for message of type '<image_msgs>"
  (cl:format cl:nil "int16 x~%int16 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'image_msgs)))
  "Returns full string definition for message of type 'image_msgs"
  (cl:format cl:nil "int16 x~%int16 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <image_msgs>))
  (cl:+ 0
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <image_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'image_msgs
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
))

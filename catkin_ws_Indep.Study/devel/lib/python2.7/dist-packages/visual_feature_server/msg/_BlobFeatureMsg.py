# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from visual_feature_server/BlobFeatureMsg.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import std_msgs.msg

class BlobFeatureMsg(genpy.Message):
  _md5sum = "c25be8f3f0fd93ffc579284ad0e9abf8"
  _type = "visual_feature_server/BlobFeatureMsg"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """uint8 hHigh
uint8 sHigh
uint8 vHigh
uint8 hLow
uint8 sLow
uint8 vLow
#uint8 scale
uint8 threshold

#pose of the feature
geometry_msgs/PoseWithCovarianceStamped centroid
#geometry_msgs/PoseWithCovarianceStamped top_left
#geometry_msgs/PoseWithCovarianceStamped top_right
#geometry_msgs/PoseWithCovarianceStamped bottom_left
#geometry_msgs/PoseWithCovarianceStamped bottom_right

================================================================================
MSG: geometry_msgs/PoseWithCovarianceStamped
# This expresses an estimated pose with a reference coordinate frame and timestamp

Header header
PoseWithCovariance pose

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/PoseWithCovariance
# This represents a pose in free space with uncertainty.

Pose pose

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
"""
  __slots__ = ['hHigh','sHigh','vHigh','hLow','sLow','vLow','threshold','centroid']
  _slot_types = ['uint8','uint8','uint8','uint8','uint8','uint8','uint8','geometry_msgs/PoseWithCovarianceStamped']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       hHigh,sHigh,vHigh,hLow,sLow,vLow,threshold,centroid

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(BlobFeatureMsg, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.hHigh is None:
        self.hHigh = 0
      if self.sHigh is None:
        self.sHigh = 0
      if self.vHigh is None:
        self.vHigh = 0
      if self.hLow is None:
        self.hLow = 0
      if self.sLow is None:
        self.sLow = 0
      if self.vLow is None:
        self.vLow = 0
      if self.threshold is None:
        self.threshold = 0
      if self.centroid is None:
        self.centroid = geometry_msgs.msg.PoseWithCovarianceStamped()
    else:
      self.hHigh = 0
      self.sHigh = 0
      self.vHigh = 0
      self.hLow = 0
      self.sLow = 0
      self.vLow = 0
      self.threshold = 0
      self.centroid = geometry_msgs.msg.PoseWithCovarianceStamped()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_7B3I().pack(_x.hHigh, _x.sHigh, _x.vHigh, _x.hLow, _x.sLow, _x.vLow, _x.threshold, _x.centroid.header.seq, _x.centroid.header.stamp.secs, _x.centroid.header.stamp.nsecs))
      _x = self.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.centroid.pose.pose.position.x, _x.centroid.pose.pose.position.y, _x.centroid.pose.pose.position.z, _x.centroid.pose.pose.orientation.x, _x.centroid.pose.pose.orientation.y, _x.centroid.pose.pose.orientation.z, _x.centroid.pose.pose.orientation.w))
      buff.write(_get_struct_36d().pack(*self.centroid.pose.covariance))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.centroid is None:
        self.centroid = geometry_msgs.msg.PoseWithCovarianceStamped()
      end = 0
      _x = self
      start = end
      end += 19
      (_x.hHigh, _x.sHigh, _x.vHigh, _x.hLow, _x.sLow, _x.vLow, _x.threshold, _x.centroid.header.seq, _x.centroid.header.stamp.secs, _x.centroid.header.stamp.nsecs,) = _get_struct_7B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.centroid.pose.pose.position.x, _x.centroid.pose.pose.position.y, _x.centroid.pose.pose.position.z, _x.centroid.pose.pose.orientation.x, _x.centroid.pose.pose.orientation.y, _x.centroid.pose.pose.orientation.z, _x.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.centroid.pose.covariance = _get_struct_36d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_7B3I().pack(_x.hHigh, _x.sHigh, _x.vHigh, _x.hLow, _x.sLow, _x.vLow, _x.threshold, _x.centroid.header.seq, _x.centroid.header.stamp.secs, _x.centroid.header.stamp.nsecs))
      _x = self.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.centroid.pose.pose.position.x, _x.centroid.pose.pose.position.y, _x.centroid.pose.pose.position.z, _x.centroid.pose.pose.orientation.x, _x.centroid.pose.pose.orientation.y, _x.centroid.pose.pose.orientation.z, _x.centroid.pose.pose.orientation.w))
      buff.write(self.centroid.pose.covariance.tostring())
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.centroid is None:
        self.centroid = geometry_msgs.msg.PoseWithCovarianceStamped()
      end = 0
      _x = self
      start = end
      end += 19
      (_x.hHigh, _x.sHigh, _x.vHigh, _x.hLow, _x.sLow, _x.vLow, _x.threshold, _x.centroid.header.seq, _x.centroid.header.stamp.secs, _x.centroid.header.stamp.nsecs,) = _get_struct_7B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.centroid.pose.pose.position.x, _x.centroid.pose.pose.position.y, _x.centroid.pose.pose.position.z, _x.centroid.pose.pose.orientation.x, _x.centroid.pose.pose.orientation.y, _x.centroid.pose.pose.orientation.z, _x.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.centroid.pose.covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=36)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_36d = None
def _get_struct_36d():
    global _struct_36d
    if _struct_36d is None:
        _struct_36d = struct.Struct("<36d")
    return _struct_36d
_struct_7B3I = None
def _get_struct_7B3I():
    global _struct_7B3I
    if _struct_7B3I is None:
        _struct_7B3I = struct.Struct("<7B3I")
    return _struct_7B3I
_struct_7d = None
def _get_struct_7d():
    global _struct_7d
    if _struct_7d is None:
        _struct_7d = struct.Struct("<7d")
    return _struct_7d

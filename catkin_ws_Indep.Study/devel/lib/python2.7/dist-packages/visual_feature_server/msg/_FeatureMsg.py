# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from visual_feature_server/FeatureMsg.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import std_msgs.msg
import visual_feature_server.msg

class FeatureMsg(genpy.Message):
  _md5sum = "93ea47ac84f852fc7e6fbfcdf7865fee"
  _type = "visual_feature_server/FeatureMsg"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """uint8 CORNER=1
uint8 BLOB=2
uint8 EDGE=3
string CORNER_STR="corner"
string BLOB_STR="blob"
string EDGE_STR="edge"

string name
int32 type

float32 image_scale
float32 world_scale

BlobFeatureMsg blobFeature
CornerFeatureMsg cornerFeature
EdgeFeatureMsg edgeFeature

#recognition confidence
float32 confidence
int32 x_pixel
int32 y_pixel

================================================================================
MSG: visual_feature_server/BlobFeatureMsg
uint8 hHigh
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

================================================================================
MSG: visual_feature_server/CornerFeatureMsg
uint8 threshold
#uint8 scale

geometry_msgs/PoseWithCovarianceStamped centroid

================================================================================
MSG: visual_feature_server/EdgeFeatureMsg
uint8 threshold
#uint8 scale

# geometry_msgs/PoseWithCovarianceStamped p1
# geometry_msgs/PoseWithCovarianceStamped p2
geometry_msgs/PoseWithCovarianceStamped centroid
"""
  # Pseudo-constants
  CORNER = 1
  BLOB = 2
  EDGE = 3
  CORNER_STR = r'"corner"'
  BLOB_STR = r'"blob"'
  EDGE_STR = r'"edge"'

  __slots__ = ['name','type','image_scale','world_scale','blobFeature','cornerFeature','edgeFeature','confidence','x_pixel','y_pixel']
  _slot_types = ['string','int32','float32','float32','visual_feature_server/BlobFeatureMsg','visual_feature_server/CornerFeatureMsg','visual_feature_server/EdgeFeatureMsg','float32','int32','int32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       name,type,image_scale,world_scale,blobFeature,cornerFeature,edgeFeature,confidence,x_pixel,y_pixel

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(FeatureMsg, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.name is None:
        self.name = ''
      if self.type is None:
        self.type = 0
      if self.image_scale is None:
        self.image_scale = 0.
      if self.world_scale is None:
        self.world_scale = 0.
      if self.blobFeature is None:
        self.blobFeature = visual_feature_server.msg.BlobFeatureMsg()
      if self.cornerFeature is None:
        self.cornerFeature = visual_feature_server.msg.CornerFeatureMsg()
      if self.edgeFeature is None:
        self.edgeFeature = visual_feature_server.msg.EdgeFeatureMsg()
      if self.confidence is None:
        self.confidence = 0.
      if self.x_pixel is None:
        self.x_pixel = 0
      if self.y_pixel is None:
        self.y_pixel = 0
    else:
      self.name = ''
      self.type = 0
      self.image_scale = 0.
      self.world_scale = 0.
      self.blobFeature = visual_feature_server.msg.BlobFeatureMsg()
      self.cornerFeature = visual_feature_server.msg.CornerFeatureMsg()
      self.edgeFeature = visual_feature_server.msg.EdgeFeatureMsg()
      self.confidence = 0.
      self.x_pixel = 0
      self.y_pixel = 0

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
      _x = self.name
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_i2f7B3I().pack(_x.type, _x.image_scale, _x.world_scale, _x.blobFeature.hHigh, _x.blobFeature.sHigh, _x.blobFeature.vHigh, _x.blobFeature.hLow, _x.blobFeature.sLow, _x.blobFeature.vLow, _x.blobFeature.threshold, _x.blobFeature.centroid.header.seq, _x.blobFeature.centroid.header.stamp.secs, _x.blobFeature.centroid.header.stamp.nsecs))
      _x = self.blobFeature.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.blobFeature.centroid.pose.pose.position.x, _x.blobFeature.centroid.pose.pose.position.y, _x.blobFeature.centroid.pose.pose.position.z, _x.blobFeature.centroid.pose.pose.orientation.x, _x.blobFeature.centroid.pose.pose.orientation.y, _x.blobFeature.centroid.pose.pose.orientation.z, _x.blobFeature.centroid.pose.pose.orientation.w))
      buff.write(_get_struct_36d().pack(*self.blobFeature.centroid.pose.covariance))
      _x = self
      buff.write(_get_struct_B3I().pack(_x.cornerFeature.threshold, _x.cornerFeature.centroid.header.seq, _x.cornerFeature.centroid.header.stamp.secs, _x.cornerFeature.centroid.header.stamp.nsecs))
      _x = self.cornerFeature.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.cornerFeature.centroid.pose.pose.position.x, _x.cornerFeature.centroid.pose.pose.position.y, _x.cornerFeature.centroid.pose.pose.position.z, _x.cornerFeature.centroid.pose.pose.orientation.x, _x.cornerFeature.centroid.pose.pose.orientation.y, _x.cornerFeature.centroid.pose.pose.orientation.z, _x.cornerFeature.centroid.pose.pose.orientation.w))
      buff.write(_get_struct_36d().pack(*self.cornerFeature.centroid.pose.covariance))
      _x = self
      buff.write(_get_struct_B3I().pack(_x.edgeFeature.threshold, _x.edgeFeature.centroid.header.seq, _x.edgeFeature.centroid.header.stamp.secs, _x.edgeFeature.centroid.header.stamp.nsecs))
      _x = self.edgeFeature.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.edgeFeature.centroid.pose.pose.position.x, _x.edgeFeature.centroid.pose.pose.position.y, _x.edgeFeature.centroid.pose.pose.position.z, _x.edgeFeature.centroid.pose.pose.orientation.x, _x.edgeFeature.centroid.pose.pose.orientation.y, _x.edgeFeature.centroid.pose.pose.orientation.z, _x.edgeFeature.centroid.pose.pose.orientation.w))
      buff.write(_get_struct_36d().pack(*self.edgeFeature.centroid.pose.covariance))
      _x = self
      buff.write(_get_struct_f2i().pack(_x.confidence, _x.x_pixel, _x.y_pixel))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.blobFeature is None:
        self.blobFeature = visual_feature_server.msg.BlobFeatureMsg()
      if self.cornerFeature is None:
        self.cornerFeature = visual_feature_server.msg.CornerFeatureMsg()
      if self.edgeFeature is None:
        self.edgeFeature = visual_feature_server.msg.EdgeFeatureMsg()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.name = str[start:end].decode('utf-8')
      else:
        self.name = str[start:end]
      _x = self
      start = end
      end += 31
      (_x.type, _x.image_scale, _x.world_scale, _x.blobFeature.hHigh, _x.blobFeature.sHigh, _x.blobFeature.vHigh, _x.blobFeature.hLow, _x.blobFeature.sLow, _x.blobFeature.vLow, _x.blobFeature.threshold, _x.blobFeature.centroid.header.seq, _x.blobFeature.centroid.header.stamp.secs, _x.blobFeature.centroid.header.stamp.nsecs,) = _get_struct_i2f7B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.blobFeature.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.blobFeature.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.blobFeature.centroid.pose.pose.position.x, _x.blobFeature.centroid.pose.pose.position.y, _x.blobFeature.centroid.pose.pose.position.z, _x.blobFeature.centroid.pose.pose.orientation.x, _x.blobFeature.centroid.pose.pose.orientation.y, _x.blobFeature.centroid.pose.pose.orientation.z, _x.blobFeature.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.blobFeature.centroid.pose.covariance = _get_struct_36d().unpack(str[start:end])
      _x = self
      start = end
      end += 13
      (_x.cornerFeature.threshold, _x.cornerFeature.centroid.header.seq, _x.cornerFeature.centroid.header.stamp.secs, _x.cornerFeature.centroid.header.stamp.nsecs,) = _get_struct_B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.cornerFeature.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.cornerFeature.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.cornerFeature.centroid.pose.pose.position.x, _x.cornerFeature.centroid.pose.pose.position.y, _x.cornerFeature.centroid.pose.pose.position.z, _x.cornerFeature.centroid.pose.pose.orientation.x, _x.cornerFeature.centroid.pose.pose.orientation.y, _x.cornerFeature.centroid.pose.pose.orientation.z, _x.cornerFeature.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.cornerFeature.centroid.pose.covariance = _get_struct_36d().unpack(str[start:end])
      _x = self
      start = end
      end += 13
      (_x.edgeFeature.threshold, _x.edgeFeature.centroid.header.seq, _x.edgeFeature.centroid.header.stamp.secs, _x.edgeFeature.centroid.header.stamp.nsecs,) = _get_struct_B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.edgeFeature.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.edgeFeature.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.edgeFeature.centroid.pose.pose.position.x, _x.edgeFeature.centroid.pose.pose.position.y, _x.edgeFeature.centroid.pose.pose.position.z, _x.edgeFeature.centroid.pose.pose.orientation.x, _x.edgeFeature.centroid.pose.pose.orientation.y, _x.edgeFeature.centroid.pose.pose.orientation.z, _x.edgeFeature.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.edgeFeature.centroid.pose.covariance = _get_struct_36d().unpack(str[start:end])
      _x = self
      start = end
      end += 12
      (_x.confidence, _x.x_pixel, _x.y_pixel,) = _get_struct_f2i().unpack(str[start:end])
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
      _x = self.name
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_i2f7B3I().pack(_x.type, _x.image_scale, _x.world_scale, _x.blobFeature.hHigh, _x.blobFeature.sHigh, _x.blobFeature.vHigh, _x.blobFeature.hLow, _x.blobFeature.sLow, _x.blobFeature.vLow, _x.blobFeature.threshold, _x.blobFeature.centroid.header.seq, _x.blobFeature.centroid.header.stamp.secs, _x.blobFeature.centroid.header.stamp.nsecs))
      _x = self.blobFeature.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.blobFeature.centroid.pose.pose.position.x, _x.blobFeature.centroid.pose.pose.position.y, _x.blobFeature.centroid.pose.pose.position.z, _x.blobFeature.centroid.pose.pose.orientation.x, _x.blobFeature.centroid.pose.pose.orientation.y, _x.blobFeature.centroid.pose.pose.orientation.z, _x.blobFeature.centroid.pose.pose.orientation.w))
      buff.write(self.blobFeature.centroid.pose.covariance.tostring())
      _x = self
      buff.write(_get_struct_B3I().pack(_x.cornerFeature.threshold, _x.cornerFeature.centroid.header.seq, _x.cornerFeature.centroid.header.stamp.secs, _x.cornerFeature.centroid.header.stamp.nsecs))
      _x = self.cornerFeature.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.cornerFeature.centroid.pose.pose.position.x, _x.cornerFeature.centroid.pose.pose.position.y, _x.cornerFeature.centroid.pose.pose.position.z, _x.cornerFeature.centroid.pose.pose.orientation.x, _x.cornerFeature.centroid.pose.pose.orientation.y, _x.cornerFeature.centroid.pose.pose.orientation.z, _x.cornerFeature.centroid.pose.pose.orientation.w))
      buff.write(self.cornerFeature.centroid.pose.covariance.tostring())
      _x = self
      buff.write(_get_struct_B3I().pack(_x.edgeFeature.threshold, _x.edgeFeature.centroid.header.seq, _x.edgeFeature.centroid.header.stamp.secs, _x.edgeFeature.centroid.header.stamp.nsecs))
      _x = self.edgeFeature.centroid.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_7d().pack(_x.edgeFeature.centroid.pose.pose.position.x, _x.edgeFeature.centroid.pose.pose.position.y, _x.edgeFeature.centroid.pose.pose.position.z, _x.edgeFeature.centroid.pose.pose.orientation.x, _x.edgeFeature.centroid.pose.pose.orientation.y, _x.edgeFeature.centroid.pose.pose.orientation.z, _x.edgeFeature.centroid.pose.pose.orientation.w))
      buff.write(self.edgeFeature.centroid.pose.covariance.tostring())
      _x = self
      buff.write(_get_struct_f2i().pack(_x.confidence, _x.x_pixel, _x.y_pixel))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.blobFeature is None:
        self.blobFeature = visual_feature_server.msg.BlobFeatureMsg()
      if self.cornerFeature is None:
        self.cornerFeature = visual_feature_server.msg.CornerFeatureMsg()
      if self.edgeFeature is None:
        self.edgeFeature = visual_feature_server.msg.EdgeFeatureMsg()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.name = str[start:end].decode('utf-8')
      else:
        self.name = str[start:end]
      _x = self
      start = end
      end += 31
      (_x.type, _x.image_scale, _x.world_scale, _x.blobFeature.hHigh, _x.blobFeature.sHigh, _x.blobFeature.vHigh, _x.blobFeature.hLow, _x.blobFeature.sLow, _x.blobFeature.vLow, _x.blobFeature.threshold, _x.blobFeature.centroid.header.seq, _x.blobFeature.centroid.header.stamp.secs, _x.blobFeature.centroid.header.stamp.nsecs,) = _get_struct_i2f7B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.blobFeature.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.blobFeature.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.blobFeature.centroid.pose.pose.position.x, _x.blobFeature.centroid.pose.pose.position.y, _x.blobFeature.centroid.pose.pose.position.z, _x.blobFeature.centroid.pose.pose.orientation.x, _x.blobFeature.centroid.pose.pose.orientation.y, _x.blobFeature.centroid.pose.pose.orientation.z, _x.blobFeature.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.blobFeature.centroid.pose.covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=36)
      _x = self
      start = end
      end += 13
      (_x.cornerFeature.threshold, _x.cornerFeature.centroid.header.seq, _x.cornerFeature.centroid.header.stamp.secs, _x.cornerFeature.centroid.header.stamp.nsecs,) = _get_struct_B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.cornerFeature.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.cornerFeature.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.cornerFeature.centroid.pose.pose.position.x, _x.cornerFeature.centroid.pose.pose.position.y, _x.cornerFeature.centroid.pose.pose.position.z, _x.cornerFeature.centroid.pose.pose.orientation.x, _x.cornerFeature.centroid.pose.pose.orientation.y, _x.cornerFeature.centroid.pose.pose.orientation.z, _x.cornerFeature.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.cornerFeature.centroid.pose.covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=36)
      _x = self
      start = end
      end += 13
      (_x.edgeFeature.threshold, _x.edgeFeature.centroid.header.seq, _x.edgeFeature.centroid.header.stamp.secs, _x.edgeFeature.centroid.header.stamp.nsecs,) = _get_struct_B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.edgeFeature.centroid.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.edgeFeature.centroid.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 56
      (_x.edgeFeature.centroid.pose.pose.position.x, _x.edgeFeature.centroid.pose.pose.position.y, _x.edgeFeature.centroid.pose.pose.position.z, _x.edgeFeature.centroid.pose.pose.orientation.x, _x.edgeFeature.centroid.pose.pose.orientation.y, _x.edgeFeature.centroid.pose.pose.orientation.z, _x.edgeFeature.centroid.pose.pose.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      start = end
      end += 288
      self.edgeFeature.centroid.pose.covariance = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=36)
      _x = self
      start = end
      end += 12
      (_x.confidence, _x.x_pixel, _x.y_pixel,) = _get_struct_f2i().unpack(str[start:end])
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
_struct_7d = None
def _get_struct_7d():
    global _struct_7d
    if _struct_7d is None:
        _struct_7d = struct.Struct("<7d")
    return _struct_7d
_struct_B3I = None
def _get_struct_B3I():
    global _struct_B3I
    if _struct_B3I is None:
        _struct_B3I = struct.Struct("<B3I")
    return _struct_B3I
_struct_f2i = None
def _get_struct_f2i():
    global _struct_f2i
    if _struct_f2i is None:
        _struct_f2i = struct.Struct("<f2i")
    return _struct_f2i
_struct_i2f7B3I = None
def _get_struct_i2f7B3I():
    global _struct_i2f7B3I
    if _struct_i2f7B3I is None:
        _struct_i2f7B3I = struct.Struct("<i2f7B3I")
    return _struct_i2f7B3I

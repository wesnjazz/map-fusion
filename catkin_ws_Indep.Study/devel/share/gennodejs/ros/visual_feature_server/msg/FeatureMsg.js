// Auto-generated. Do not edit!

// (in-package visual_feature_server.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let BlobFeatureMsg = require('./BlobFeatureMsg.js');
let CornerFeatureMsg = require('./CornerFeatureMsg.js');
let EdgeFeatureMsg = require('./EdgeFeatureMsg.js');

//-----------------------------------------------------------

class FeatureMsg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
      this.type = null;
      this.image_scale = null;
      this.world_scale = null;
      this.blobFeature = null;
      this.cornerFeature = null;
      this.edgeFeature = null;
      this.confidence = null;
      this.x_pixel = null;
      this.y_pixel = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
      if (initObj.hasOwnProperty('type')) {
        this.type = initObj.type
      }
      else {
        this.type = 0;
      }
      if (initObj.hasOwnProperty('image_scale')) {
        this.image_scale = initObj.image_scale
      }
      else {
        this.image_scale = 0.0;
      }
      if (initObj.hasOwnProperty('world_scale')) {
        this.world_scale = initObj.world_scale
      }
      else {
        this.world_scale = 0.0;
      }
      if (initObj.hasOwnProperty('blobFeature')) {
        this.blobFeature = initObj.blobFeature
      }
      else {
        this.blobFeature = new BlobFeatureMsg();
      }
      if (initObj.hasOwnProperty('cornerFeature')) {
        this.cornerFeature = initObj.cornerFeature
      }
      else {
        this.cornerFeature = new CornerFeatureMsg();
      }
      if (initObj.hasOwnProperty('edgeFeature')) {
        this.edgeFeature = initObj.edgeFeature
      }
      else {
        this.edgeFeature = new EdgeFeatureMsg();
      }
      if (initObj.hasOwnProperty('confidence')) {
        this.confidence = initObj.confidence
      }
      else {
        this.confidence = 0.0;
      }
      if (initObj.hasOwnProperty('x_pixel')) {
        this.x_pixel = initObj.x_pixel
      }
      else {
        this.x_pixel = 0;
      }
      if (initObj.hasOwnProperty('y_pixel')) {
        this.y_pixel = initObj.y_pixel
      }
      else {
        this.y_pixel = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FeatureMsg
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    // Serialize message field [type]
    bufferOffset = _serializer.int32(obj.type, buffer, bufferOffset);
    // Serialize message field [image_scale]
    bufferOffset = _serializer.float32(obj.image_scale, buffer, bufferOffset);
    // Serialize message field [world_scale]
    bufferOffset = _serializer.float32(obj.world_scale, buffer, bufferOffset);
    // Serialize message field [blobFeature]
    bufferOffset = BlobFeatureMsg.serialize(obj.blobFeature, buffer, bufferOffset);
    // Serialize message field [cornerFeature]
    bufferOffset = CornerFeatureMsg.serialize(obj.cornerFeature, buffer, bufferOffset);
    // Serialize message field [edgeFeature]
    bufferOffset = EdgeFeatureMsg.serialize(obj.edgeFeature, buffer, bufferOffset);
    // Serialize message field [confidence]
    bufferOffset = _serializer.float32(obj.confidence, buffer, bufferOffset);
    // Serialize message field [x_pixel]
    bufferOffset = _serializer.int32(obj.x_pixel, buffer, bufferOffset);
    // Serialize message field [y_pixel]
    bufferOffset = _serializer.int32(obj.y_pixel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FeatureMsg
    let len;
    let data = new FeatureMsg(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [type]
    data.type = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [image_scale]
    data.image_scale = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [world_scale]
    data.world_scale = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [blobFeature]
    data.blobFeature = BlobFeatureMsg.deserialize(buffer, bufferOffset);
    // Deserialize message field [cornerFeature]
    data.cornerFeature = CornerFeatureMsg.deserialize(buffer, bufferOffset);
    // Deserialize message field [edgeFeature]
    data.edgeFeature = EdgeFeatureMsg.deserialize(buffer, bufferOffset);
    // Deserialize message field [confidence]
    data.confidence = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [x_pixel]
    data.x_pixel = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [y_pixel]
    data.y_pixel = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.name.length;
    length += BlobFeatureMsg.getMessageSize(object.blobFeature);
    length += CornerFeatureMsg.getMessageSize(object.cornerFeature);
    length += EdgeFeatureMsg.getMessageSize(object.edgeFeature);
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visual_feature_server/FeatureMsg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '93ea47ac84f852fc7e6fbfcdf7865fee';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 CORNER=1
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FeatureMsg(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    if (msg.type !== undefined) {
      resolved.type = msg.type;
    }
    else {
      resolved.type = 0
    }

    if (msg.image_scale !== undefined) {
      resolved.image_scale = msg.image_scale;
    }
    else {
      resolved.image_scale = 0.0
    }

    if (msg.world_scale !== undefined) {
      resolved.world_scale = msg.world_scale;
    }
    else {
      resolved.world_scale = 0.0
    }

    if (msg.blobFeature !== undefined) {
      resolved.blobFeature = BlobFeatureMsg.Resolve(msg.blobFeature)
    }
    else {
      resolved.blobFeature = new BlobFeatureMsg()
    }

    if (msg.cornerFeature !== undefined) {
      resolved.cornerFeature = CornerFeatureMsg.Resolve(msg.cornerFeature)
    }
    else {
      resolved.cornerFeature = new CornerFeatureMsg()
    }

    if (msg.edgeFeature !== undefined) {
      resolved.edgeFeature = EdgeFeatureMsg.Resolve(msg.edgeFeature)
    }
    else {
      resolved.edgeFeature = new EdgeFeatureMsg()
    }

    if (msg.confidence !== undefined) {
      resolved.confidence = msg.confidence;
    }
    else {
      resolved.confidence = 0.0
    }

    if (msg.x_pixel !== undefined) {
      resolved.x_pixel = msg.x_pixel;
    }
    else {
      resolved.x_pixel = 0
    }

    if (msg.y_pixel !== undefined) {
      resolved.y_pixel = msg.y_pixel;
    }
    else {
      resolved.y_pixel = 0
    }

    return resolved;
    }
};

// Constants for message
FeatureMsg.Constants = {
  CORNER: 1,
  BLOB: 2,
  EDGE: 3,
  CORNER_STR: '"corner"',
  BLOB_STR: '"blob"',
  EDGE_STR: '"edge"',
}

module.exports = FeatureMsg;

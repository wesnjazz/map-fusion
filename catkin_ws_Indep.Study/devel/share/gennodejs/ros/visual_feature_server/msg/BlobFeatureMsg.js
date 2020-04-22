// Auto-generated. Do not edit!

// (in-package visual_feature_server.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class BlobFeatureMsg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.hHigh = null;
      this.sHigh = null;
      this.vHigh = null;
      this.hLow = null;
      this.sLow = null;
      this.vLow = null;
      this.threshold = null;
      this.centroid = null;
    }
    else {
      if (initObj.hasOwnProperty('hHigh')) {
        this.hHigh = initObj.hHigh
      }
      else {
        this.hHigh = 0;
      }
      if (initObj.hasOwnProperty('sHigh')) {
        this.sHigh = initObj.sHigh
      }
      else {
        this.sHigh = 0;
      }
      if (initObj.hasOwnProperty('vHigh')) {
        this.vHigh = initObj.vHigh
      }
      else {
        this.vHigh = 0;
      }
      if (initObj.hasOwnProperty('hLow')) {
        this.hLow = initObj.hLow
      }
      else {
        this.hLow = 0;
      }
      if (initObj.hasOwnProperty('sLow')) {
        this.sLow = initObj.sLow
      }
      else {
        this.sLow = 0;
      }
      if (initObj.hasOwnProperty('vLow')) {
        this.vLow = initObj.vLow
      }
      else {
        this.vLow = 0;
      }
      if (initObj.hasOwnProperty('threshold')) {
        this.threshold = initObj.threshold
      }
      else {
        this.threshold = 0;
      }
      if (initObj.hasOwnProperty('centroid')) {
        this.centroid = initObj.centroid
      }
      else {
        this.centroid = new geometry_msgs.msg.PoseWithCovarianceStamped();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BlobFeatureMsg
    // Serialize message field [hHigh]
    bufferOffset = _serializer.uint8(obj.hHigh, buffer, bufferOffset);
    // Serialize message field [sHigh]
    bufferOffset = _serializer.uint8(obj.sHigh, buffer, bufferOffset);
    // Serialize message field [vHigh]
    bufferOffset = _serializer.uint8(obj.vHigh, buffer, bufferOffset);
    // Serialize message field [hLow]
    bufferOffset = _serializer.uint8(obj.hLow, buffer, bufferOffset);
    // Serialize message field [sLow]
    bufferOffset = _serializer.uint8(obj.sLow, buffer, bufferOffset);
    // Serialize message field [vLow]
    bufferOffset = _serializer.uint8(obj.vLow, buffer, bufferOffset);
    // Serialize message field [threshold]
    bufferOffset = _serializer.uint8(obj.threshold, buffer, bufferOffset);
    // Serialize message field [centroid]
    bufferOffset = geometry_msgs.msg.PoseWithCovarianceStamped.serialize(obj.centroid, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BlobFeatureMsg
    let len;
    let data = new BlobFeatureMsg(null);
    // Deserialize message field [hHigh]
    data.hHigh = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sHigh]
    data.sHigh = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [vHigh]
    data.vHigh = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hLow]
    data.hLow = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sLow]
    data.sLow = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [vLow]
    data.vLow = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [threshold]
    data.threshold = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [centroid]
    data.centroid = geometry_msgs.msg.PoseWithCovarianceStamped.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.PoseWithCovarianceStamped.getMessageSize(object.centroid);
    return length + 7;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visual_feature_server/BlobFeatureMsg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c25be8f3f0fd93ffc579284ad0e9abf8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BlobFeatureMsg(null);
    if (msg.hHigh !== undefined) {
      resolved.hHigh = msg.hHigh;
    }
    else {
      resolved.hHigh = 0
    }

    if (msg.sHigh !== undefined) {
      resolved.sHigh = msg.sHigh;
    }
    else {
      resolved.sHigh = 0
    }

    if (msg.vHigh !== undefined) {
      resolved.vHigh = msg.vHigh;
    }
    else {
      resolved.vHigh = 0
    }

    if (msg.hLow !== undefined) {
      resolved.hLow = msg.hLow;
    }
    else {
      resolved.hLow = 0
    }

    if (msg.sLow !== undefined) {
      resolved.sLow = msg.sLow;
    }
    else {
      resolved.sLow = 0
    }

    if (msg.vLow !== undefined) {
      resolved.vLow = msg.vLow;
    }
    else {
      resolved.vLow = 0
    }

    if (msg.threshold !== undefined) {
      resolved.threshold = msg.threshold;
    }
    else {
      resolved.threshold = 0
    }

    if (msg.centroid !== undefined) {
      resolved.centroid = geometry_msgs.msg.PoseWithCovarianceStamped.Resolve(msg.centroid)
    }
    else {
      resolved.centroid = new geometry_msgs.msg.PoseWithCovarianceStamped()
    }

    return resolved;
    }
};

module.exports = BlobFeatureMsg;

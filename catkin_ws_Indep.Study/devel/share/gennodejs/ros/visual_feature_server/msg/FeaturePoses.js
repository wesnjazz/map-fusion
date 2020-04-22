// Auto-generated. Do not edit!

// (in-package visual_feature_server.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let FeatureMsg = require('./FeatureMsg.js');

//-----------------------------------------------------------

class FeaturePoses {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.features = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('features')) {
        this.features = initObj.features
      }
      else {
        this.features = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FeaturePoses
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [features]
    // Serialize the length for message field [features]
    bufferOffset = _serializer.uint32(obj.features.length, buffer, bufferOffset);
    obj.features.forEach((val) => {
      bufferOffset = FeatureMsg.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FeaturePoses
    let len;
    let data = new FeaturePoses(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [features]
    // Deserialize array length for message field [features]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.features = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.features[i] = FeatureMsg.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.features.forEach((val) => {
      length += FeatureMsg.getMessageSize(val);
    });
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visual_feature_server/FeaturePoses';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8329d4cd40eb21004182798fbd3b3cb5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    
    FeatureMsg[] features
    
    ================================================================================
    MSG: visual_feature_server/FeatureMsg
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
    const resolved = new FeaturePoses(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.features !== undefined) {
      resolved.features = new Array(msg.features.length);
      for (let i = 0; i < resolved.features.length; ++i) {
        resolved.features[i] = FeatureMsg.Resolve(msg.features[i]);
      }
    }
    else {
      resolved.features = []
    }

    return resolved;
    }
};

module.exports = FeaturePoses;

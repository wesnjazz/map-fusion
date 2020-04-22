// Auto-generated. Do not edit!

// (in-package visual_feature_server.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class Convert2DPointRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.x = null;
      this.y = null;
      this.source_frame = null;
      this.destination_frame = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = [];
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = [];
      }
      if (initObj.hasOwnProperty('source_frame')) {
        this.source_frame = initObj.source_frame
      }
      else {
        this.source_frame = '';
      }
      if (initObj.hasOwnProperty('destination_frame')) {
        this.destination_frame = initObj.destination_frame
      }
      else {
        this.destination_frame = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Convert2DPointRequest
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _arraySerializer.float64(obj.x, buffer, bufferOffset, null);
    // Serialize message field [y]
    bufferOffset = _arraySerializer.float64(obj.y, buffer, bufferOffset, null);
    // Serialize message field [source_frame]
    bufferOffset = _serializer.string(obj.source_frame, buffer, bufferOffset);
    // Serialize message field [destination_frame]
    bufferOffset = _serializer.string(obj.destination_frame, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Convert2DPointRequest
    let len;
    let data = new Convert2DPointRequest(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [y]
    data.y = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [source_frame]
    data.source_frame = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [destination_frame]
    data.destination_frame = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.x.length;
    length += 8 * object.y.length;
    length += object.source_frame.length;
    length += object.destination_frame.length;
    return length + 24;
  }

  static datatype() {
    // Returns string type for a service object
    return 'visual_feature_server/Convert2DPointRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2a1f2197011561a384f51fa793dee78b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64[] x
    float64[] y
    string source_frame
    string destination_frame
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Convert2DPointRequest(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = []
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = []
    }

    if (msg.source_frame !== undefined) {
      resolved.source_frame = msg.source_frame;
    }
    else {
      resolved.source_frame = ''
    }

    if (msg.destination_frame !== undefined) {
      resolved.destination_frame = msg.destination_frame;
    }
    else {
      resolved.destination_frame = ''
    }

    return resolved;
    }
};

class Convert2DPointResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x_source = null;
      this.y_source = null;
      this.z_source = null;
      this.x_dest = null;
      this.y_dest = null;
      this.z_dest = null;
    }
    else {
      if (initObj.hasOwnProperty('x_source')) {
        this.x_source = initObj.x_source
      }
      else {
        this.x_source = [];
      }
      if (initObj.hasOwnProperty('y_source')) {
        this.y_source = initObj.y_source
      }
      else {
        this.y_source = [];
      }
      if (initObj.hasOwnProperty('z_source')) {
        this.z_source = initObj.z_source
      }
      else {
        this.z_source = [];
      }
      if (initObj.hasOwnProperty('x_dest')) {
        this.x_dest = initObj.x_dest
      }
      else {
        this.x_dest = [];
      }
      if (initObj.hasOwnProperty('y_dest')) {
        this.y_dest = initObj.y_dest
      }
      else {
        this.y_dest = [];
      }
      if (initObj.hasOwnProperty('z_dest')) {
        this.z_dest = initObj.z_dest
      }
      else {
        this.z_dest = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Convert2DPointResponse
    // Serialize message field [x_source]
    bufferOffset = _arraySerializer.float64(obj.x_source, buffer, bufferOffset, null);
    // Serialize message field [y_source]
    bufferOffset = _arraySerializer.float64(obj.y_source, buffer, bufferOffset, null);
    // Serialize message field [z_source]
    bufferOffset = _arraySerializer.float64(obj.z_source, buffer, bufferOffset, null);
    // Serialize message field [x_dest]
    bufferOffset = _arraySerializer.float64(obj.x_dest, buffer, bufferOffset, null);
    // Serialize message field [y_dest]
    bufferOffset = _arraySerializer.float64(obj.y_dest, buffer, bufferOffset, null);
    // Serialize message field [z_dest]
    bufferOffset = _arraySerializer.float64(obj.z_dest, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Convert2DPointResponse
    let len;
    let data = new Convert2DPointResponse(null);
    // Deserialize message field [x_source]
    data.x_source = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [y_source]
    data.y_source = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [z_source]
    data.z_source = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [x_dest]
    data.x_dest = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [y_dest]
    data.y_dest = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [z_dest]
    data.z_dest = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.x_source.length;
    length += 8 * object.y_source.length;
    length += 8 * object.z_source.length;
    length += 8 * object.x_dest.length;
    length += 8 * object.y_dest.length;
    length += 8 * object.z_dest.length;
    return length + 24;
  }

  static datatype() {
    // Returns string type for a service object
    return 'visual_feature_server/Convert2DPointResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ab4d89ce84f35328de2f5124bef6a8d2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    float64[] x_source
    float64[] y_source
    float64[] z_source
    
    float64[] x_dest
    float64[] y_dest
    float64[] z_dest
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Convert2DPointResponse(null);
    if (msg.x_source !== undefined) {
      resolved.x_source = msg.x_source;
    }
    else {
      resolved.x_source = []
    }

    if (msg.y_source !== undefined) {
      resolved.y_source = msg.y_source;
    }
    else {
      resolved.y_source = []
    }

    if (msg.z_source !== undefined) {
      resolved.z_source = msg.z_source;
    }
    else {
      resolved.z_source = []
    }

    if (msg.x_dest !== undefined) {
      resolved.x_dest = msg.x_dest;
    }
    else {
      resolved.x_dest = []
    }

    if (msg.y_dest !== undefined) {
      resolved.y_dest = msg.y_dest;
    }
    else {
      resolved.y_dest = []
    }

    if (msg.z_dest !== undefined) {
      resolved.z_dest = msg.z_dest;
    }
    else {
      resolved.z_dest = []
    }

    return resolved;
    }
};

module.exports = {
  Request: Convert2DPointRequest,
  Response: Convert2DPointResponse,
  md5sum() { return 'da24dbed0bfc78862b40c7bfe16c141e'; },
  datatype() { return 'visual_feature_server/Convert2DPoint'; }
};

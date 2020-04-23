// Generated by gencpp from file visual_feature_server/PickleSrv.msg
// DO NOT EDIT!


#ifndef VISUAL_FEATURE_SERVER_MESSAGE_PICKLESRV_H
#define VISUAL_FEATURE_SERVER_MESSAGE_PICKLESRV_H

#include <ros/service_traits.h>


#include <visual_feature_server/PickleSrvRequest.h>
#include <visual_feature_server/PickleSrvResponse.h>


namespace visual_feature_server
{

struct PickleSrv
{

typedef PickleSrvRequest Request;
typedef PickleSrvResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct PickleSrv
} // namespace visual_feature_server


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::visual_feature_server::PickleSrv > {
  static const char* value()
  {
    return "eb297acc7accecca58502296783fbde0";
  }

  static const char* value(const ::visual_feature_server::PickleSrv&) { return value(); }
};

template<>
struct DataType< ::visual_feature_server::PickleSrv > {
  static const char* value()
  {
    return "visual_feature_server/PickleSrv";
  }

  static const char* value(const ::visual_feature_server::PickleSrv&) { return value(); }
};


// service_traits::MD5Sum< ::visual_feature_server::PickleSrvRequest> should match
// service_traits::MD5Sum< ::visual_feature_server::PickleSrv >
template<>
struct MD5Sum< ::visual_feature_server::PickleSrvRequest>
{
  static const char* value()
  {
    return MD5Sum< ::visual_feature_server::PickleSrv >::value();
  }
  static const char* value(const ::visual_feature_server::PickleSrvRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::visual_feature_server::PickleSrvRequest> should match
// service_traits::DataType< ::visual_feature_server::PickleSrv >
template<>
struct DataType< ::visual_feature_server::PickleSrvRequest>
{
  static const char* value()
  {
    return DataType< ::visual_feature_server::PickleSrv >::value();
  }
  static const char* value(const ::visual_feature_server::PickleSrvRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::visual_feature_server::PickleSrvResponse> should match
// service_traits::MD5Sum< ::visual_feature_server::PickleSrv >
template<>
struct MD5Sum< ::visual_feature_server::PickleSrvResponse>
{
  static const char* value()
  {
    return MD5Sum< ::visual_feature_server::PickleSrv >::value();
  }
  static const char* value(const ::visual_feature_server::PickleSrvResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::visual_feature_server::PickleSrvResponse> should match
// service_traits::DataType< ::visual_feature_server::PickleSrv >
template<>
struct DataType< ::visual_feature_server::PickleSrvResponse>
{
  static const char* value()
  {
    return DataType< ::visual_feature_server::PickleSrv >::value();
  }
  static const char* value(const ::visual_feature_server::PickleSrvResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // VISUAL_FEATURE_SERVER_MESSAGE_PICKLESRV_H
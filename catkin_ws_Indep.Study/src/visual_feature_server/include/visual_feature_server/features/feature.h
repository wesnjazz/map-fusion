#ifndef FEATURE_H_
#define FEATURE_H_
#include <ros/ros.h>
#include <visual_feature_server/Convert2DPoint.h>
#include <visual_feature_server/FeatureMsg.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>
//#include <umass_math/KalmanFilter.h>
//#include <ecl/statistics.hpp>
#include <kdl/frames_io.hpp>
// #include <perception_msgs/FeaturePoses.h>
// #include <perception_msgs/Artag.h>
#include <visual_feature_server/FeaturePoses.h>
#include <visual_feature_server/FeatureMsg.h>
#include <std_msgs/Float64.h>

#define SIGMA_PROCESS   1
#define SIGMA_OBS       0.1

class Feature;
typedef std::shared_ptr<Feature> FeaturePtr;
class Feature {
public:
  Feature(ros::NodeHandle node_handle):n_(node_handle){
    pointcloud_client = n_.serviceClient<visual_feature_server::Convert2DPoint>(
                          "/visual_feature_detector/convert_2d_point");
    // rviz_marker_pub = n_.advertise< visualization_msgs::Marker > (
    //                       "/visual_feature_detector/corners", 0);
    feature_tag_pub_ = n_.advertise <visual_feature_server::FeaturePoses> (
                          "/visual_feature_detector/obs_features", 1);
  };
  ~Feature(){};
  double scale;
  ros::ServiceClient pointcloud_client;
  ros::NodeHandle n_;
  // ros::Publisher rviz_marker_pub;
  ros::Publisher feature_tag_pub_;
  bool convert(std::vector<cv::Point> centers, ros::Time convertTime, visual_feature_server::Convert2DPoint::Response& points)
  {
    visual_feature_server::Convert2DPoint srv;
    srv.request.stamp = convertTime;
    srv.request.x.resize(centers.size());
    srv.request.y.resize(centers.size());
    for(int i =0; i < centers.size(); i++)
    {
      srv.request.x.at(i) = centers.at(i).x;
      srv.request.y.at(i) = centers.at(i).y;

    }
    srv.request.source_frame = "kinect_openni_frame";
    srv.request.destination_frame = "world";
    if(!pointcloud_client.call(srv))
    {
      ROS_WARN("Failed to call service /convert_2d_point");
      return false;
    }
    else
    {
      points = srv.response;
      return true;
    }
  }

  void populateCovariance(geometry_msgs::PoseWithCovariance::_covariance_type &covariance)
  {
    covariance[0] = 0.000459;
    covariance[1] = -0.000002;
    covariance[2] = 0.000030;
    covariance[3] = 0.0;
    covariance[4] = 0.0;
    covariance[5] = 0.0;

    covariance[6] = -0.000002;
    covariance[7] = 0.000065;
    covariance[8] = -0.000172;
    covariance[9] = 0.0;
    covariance[10] = 0.0;
    covariance[11] = 0.0;


    covariance[12] = 0.000030;
    covariance[13] = -0.000172;
    covariance[14] = 0.001437;
    covariance[15] = 0.0;
    covariance[16] = 0.0;
    covariance[17] = 0.0;

    covariance[18] = 0.0;
    covariance[19] = 0.0;
    covariance[20] = 0.0;
    covariance[21] = 0.0;
    covariance[22] = 0.0;
    covariance[23] = 0.0;

    covariance[24] = 0.0;
    covariance[25] = 0.0;
    covariance[26] = 0.0;
    covariance[27] = 0.0;
    covariance[28] = 0.0;
    covariance[29] = 0.0;

    covariance[30] = 0.0;
    covariance[31] = 0.0;
    covariance[32] = 0.0;
    covariance[33] = 0.0;
    covariance[34] = 0.0;
    covariance[35] = 0.0;

  }


  std::string type2str(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch ( depth ) {
      case CV_8U:  r = "8U"; break;
      case CV_8S:  r = "8S"; break;
      case CV_16U: r = "16U"; break;
      case CV_16S: r = "16S"; break;
      case CV_32S: r = "32S"; break;
      case CV_32F: r = "32F"; break;
      case CV_64F: r = "64F"; break;
      default:     r = "User"; break;
    }

    r += "C";
    r += (chans+'0');

    return r;
  }
};

#endif // FEATURE_H_

#ifndef POINTCLOUD_SERVICE_H_
#define POINTCLOUD_SERVICE_H_


#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <geometry_msgs/Point.h>
#include <tf/transform_listener.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/common/eigen.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <sensor_msgs/JointState.h>
#include <visual_feature_server/Convert2DPoint.h>
#include <math.h>

class PointCloudService{
public:
  PointCloudService(ros::NodeHandle node_handle);
  ~PointCloudService();
  pcl::PointXYZ transformPoint(pcl::PointXYZ, ros::Time convertTime, std::string, std::string);
  bool pointcloudService(visual_feature_server::Convert2DPoint::Request &request, visual_feature_server::Convert2DPoint::Response &response );
private:
  pcl::PointCloud<pcl::PointXYZ> point_cloud;
  ros::Subscriber points_sub;
  ros::NodeHandle n_;
  void pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg);
  tf::TransformListener tf_listener;
};

#endif // POINTCLOUD_SERVICE_H_

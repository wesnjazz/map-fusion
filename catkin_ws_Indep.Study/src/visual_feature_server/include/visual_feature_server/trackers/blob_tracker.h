#ifndef BLOB_TRACKERS_H_
#define BLOB_TRACKERS_H_
#include "tracker.h"
#include <visual_feature_server/features/blob_feature.h>
#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <pcl/point_types.h>
#include <pcl/features/feature.h>
// #include <pcl/ros/conversions.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/common/common.h>

typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudRGB;
class BlobTracker: public Tracker
{
public:
  BlobTracker(BlobFeature f, std::vector<double> s);
  ~BlobTracker();
  std::vector<SearchGoal> Search(cv::Mat input_image);
  cv::Mat Visualize(cv::Mat input_image, std::vector<SearchGoal> s);
  cv::Mat maxResponseScales_;  // scale corresponding to max image response
  std::vector<cv::Point> max_pixels;
private:
  int min_response_, max_response_;
  int largest_responses_percent;
  BlobFeature f_;
  std::vector<BlobFeature> blobFeatures;
  void getGausDerX(int size, double sigma, Eigen::MatrixXf &result);
  void getGausDerY(int size, double sigma, Eigen::MatrixXf &result);
  cv::Mat binary_image_;	      // input image -> cluster + blob space
  void getBlobResponse(cv::Mat gray_image_);
  std::vector<cv::Mat> filters;
};
#endif // BLOB_TRACKERS_H_

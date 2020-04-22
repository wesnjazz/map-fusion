#ifndef CORNER_TRACKERS_H_
#define CORNER_TRACKERS_H_
#include "tracker.h"
#include <visual_feature_server/features/corner_feature.h>
#include <ros/ros.h>
class CornerTracker: public Tracker
{
public:
  CornerTracker(CornerFeature f, std::vector<double> s);
  ~CornerTracker();
  std::vector<SearchGoal> Search(cv::Mat input_image);
  cv::Mat Visualize(cv::Mat input_image, std::vector<SearchGoal> s);

private:
  CornerFeature f_;
  std::vector<CornerFeature> cornerFeatures;
  void getGausDerX(int size, double sigma, Eigen::MatrixXf &result);
  void getGausDerY(int size, double sigma, Eigen::MatrixXf &result);
  cv::Mat threshold_image_;        // thresholded blob image
  cv::Mat max_response_image_;     // max response blob image
  cv::Mat gray_image_;	      // input image -> hue space
  cv::Mat rgb_image_;	      // input image -> rgb space
  cv::Mat binary_image_;	      // input image -> cluster + blob space
  cv::Mat cluster_image_;	      // input image -> cluster + blob space

};
#endif // CORNER_TRACKERS_H_

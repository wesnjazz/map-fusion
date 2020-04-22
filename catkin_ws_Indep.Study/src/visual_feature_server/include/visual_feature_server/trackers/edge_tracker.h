#ifndef EDGE_TRACKERS_H_
#define EDGE_TRACKERS_H_
#include "tracker.h"
#include <visual_feature_server/features/edge_feature.h>
#include <ros/ros.h>
class EdgeTracker: public Tracker
{
#define MAX_FEATURES 50

public:
  EdgeTracker(EdgeFeature f, std::vector<double> s, int number_of_orientations=4);
  ~EdgeTracker();
  std::vector<SearchGoal> Search(cv::Mat input_image);
  cv::Mat Visualize(cv::Mat input_image, std::vector<SearchGoal> s);
private:
  EdgeFeature f_;
  std::vector<EdgeFeature> edgeFeatures;
  bool start;
  void getGausDerX(int size, double sigma, Eigen::MatrixXf &result);
  void getGausDerY(int size, double sigma, Eigen::MatrixXf &result);
  cv::Mat hedge, vedge, temp_blurred_image, blurred_image;
  cv::Mat edge;
  cv::Mat cc_image;
  cv::Mat cedge, gray, copy_image;
  int ccMeans[MAX_FEATURES][2];
  int ccPointsLen[MAX_FEATURES];
  int marked;
  int unmarked;
  int blurKernel;
  int min_point_thresh;
  int mincc_thresh;
  int edge_thresh;
  int numFeatures;
  std::vector<visual_feature_server::FeatureMsg> lines;
  std::vector<SearchGoal> r;

  void getEdgeResponse(cv::Mat gray_image);
  void getConnectedComponents(cv::Mat &back_img, int k);
  int getThresholdConnectedComponents(std::vector<std::vector<cv::Point> > contours, int k);

  void normalize(cv::Mat &edgeResponse, cv::Mat &response, int lowestResponse, int highestResponse);
};
#endif // EDGE_TRACKERS_H_

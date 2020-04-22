#ifndef TRACKERS_H_
#define TRACKERS_H_
#include "visual_feature_server/features/feature.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <math.h>

#define IMAGE_HEIGHT 480
#define IMAGE_WIDTH 640

// Focal length = 570.34224 (pixel?) = 0.1509 (?METER)
#define FOCAL_LENGTH 570.34224

struct SearchGoal {
  double image_scale;
  double world_scale;

  double upper_tilt;
  double pan;
  double lower_tilt;
  double x_i;
  double y_i;
  double x_w;
  double y_w;
  double z_w;
  double x_i1;
  double y_i1;
  double x_i2;
  double y_i2;

  double x_w1;
  double y_w1;
  double z_w1;
  double x_w2;
  double y_w2;
  double z_w2;

};

class Tracker
{
public:
  Tracker(Feature f, std::vector<double> scales);
  ~Tracker();
  void init();
  virtual std::vector<SearchGoal> Search(cv::Mat input_image)= 0;
  virtual cv::Mat Visualize(cv::Mat input_image, std::vector<SearchGoal> s)= 0;
  virtual void getGausDerX(int size, double sigma, Eigen::MatrixXf &result) = 0;
  virtual void getGausDerY(int size, double sigma, Eigen::MatrixXf &result) = 0;

  void blurImage(cv::Mat& input_image);
  cv::Mat blurredImage;
  void RunKalman();
  std::vector<double> minOrientations;
  std::vector<double> maxOrientations;
  std::vector<cv::Mat> maxResponses;
  std::vector<double> scales;
  std::vector<double> sigmas;
  std::vector<double> sizes;
  std::vector<double> weights;
  std::vector<cv::Mat> filterX;
  std::vector<cv::Mat> filterY;
  std::vector<cv::Mat> imgConvLx;
  std::vector<cv::Mat> imgConvLy;
  std::vector<cv::Mat> responses;

  void initializeFilter(int size, Eigen::MatrixXf& x, Eigen::MatrixXf& y );
  std::vector<cv::Vec3b> color;
  int getFilterSize(double sigma);
  ros::Time convertTime;
  void convolve(cv::Mat input, cv::Mat filter, cv::Mat &output);
private:

  Feature ftracker_;
  // int number_of_scales;
  int number_of_orientations;
  void getGxFilter(cv::Mat& filter, double sigma);
  void getGyFilter(cv::Mat& filter, double sigma);

  // double weight_scale_factor;
};
#endif // TRACKERS_H_

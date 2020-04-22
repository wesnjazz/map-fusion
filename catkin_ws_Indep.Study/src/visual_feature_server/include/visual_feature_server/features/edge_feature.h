#ifndef EDGE_FEATURE_H_
#define EDGE_FEATURE_H_
#include "visual_feature_server/features/feature.h"
struct EdgeFeature: public Feature{
  EdgeFeature(ros::NodeHandle node_handle);
  int threshold;
  double x1_;
  double y1_;
  double z1_;
  double x2_;
  double y2_;
  double z2_;
  void updateEstimates(bool seen);
  //KalmanFilter *kf1_;
  //KalmanFilter *kf2_;
  //Estimate e1;
  //Estimate e2;
  EdgeFeature& operator=(const visual_feature_server::FeatureMsg& msg);

};
#endif // EDGE_FEATURE_H_

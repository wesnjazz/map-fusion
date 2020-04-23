#ifndef CORNER_FEATURE_H_
#define CORNER_FEATURE_H_
#include "visual_feature_server/features/feature.h"
struct CornerFeature: public Feature{
  CornerFeature(ros::NodeHandle node_handle); //FIX KF
  int threshold;
  void updateEstimates(bool seen);
  void initalizeEstimate();

  //KalmanFilter *kf_;
  //Estimate e;
  double x_, y_, z_;
  CornerFeature& operator=(const visual_feature_server::FeatureMsg& msg);

};
#endif //CORNER_FEATURE_H_

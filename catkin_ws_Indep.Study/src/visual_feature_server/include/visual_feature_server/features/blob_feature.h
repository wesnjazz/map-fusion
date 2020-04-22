#ifndef BLOB_FEATURE_H_
#define BLOB_FEATURE_H_
#include "visual_feature_server/features/feature.h"
struct BlobFeature: public Feature{
public:
  BlobFeature(ros::NodeHandle node_handle); //FIX KF
  int hHigh;
  int sHigh;
  int vHigh;
  int hLow;
  int sLow;
  int vLow;
  void updateEstimates(bool seen);
  //KalmanFilter *kf1_;
  //KalmanFilter *kf2_;
  //Estimate e1;
  //Estimate e2;
  BlobFeature& operator=(const visual_feature_server::FeatureMsg& msg);
};
#endif // BLOB_FEATURE_H_

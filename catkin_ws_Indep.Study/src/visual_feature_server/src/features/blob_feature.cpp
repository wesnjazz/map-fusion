#include <visual_feature_server/features/blob_feature.h>

BlobFeature::BlobFeature(ros::NodeHandle node_handle):Feature(node_handle) {
  ROS_ERROR("MAKING BLOB FEATU");
  //kf1_ = new KalmanFilter(SIGMA_PROCESS, SIGMA_OBS, 1, 6);
  ROS_ERROR("MADE BLOB FEATU K1");
  // kf2_ = new KalmanFilter(SIGMA_PROCESS, SIGMA_OBS, 1, 2);
  // ROS_ERROR("MAKING BLOB FEATU K2");
}


void BlobFeature::updateEstimates(bool seen)
{
  /*
  Observation obs;
  e1 = kf1_->kf(seen, e1, obs, 6);
  // TODO: Set obs2
  e2 =  kf2_->kf(seen, e2, obs, 2);
  */
}

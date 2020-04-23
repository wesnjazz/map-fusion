#include <visual_feature_server/features/edge_feature.h>

EdgeFeature::EdgeFeature(ros::NodeHandle node_handle):Feature(node_handle){
  //kf1_ = new KalmanFilter(SIGMA_PROCESS, SIGMA_OBS, 1.0/30.0, 6);
  //kf2_ = new KalmanFilter(SIGMA_PROCESS, SIGMA_OBS, 1, 6);
}

void EdgeFeature::updateEstimates(bool seen)
{
  /*
  Observation obs;
  e1 = kf1_->kf(seen, e1, obs, 6);
  // TODO: Set obs2
  e2 =  kf2_->kf(seen, e2, obs, 6)
  */
}

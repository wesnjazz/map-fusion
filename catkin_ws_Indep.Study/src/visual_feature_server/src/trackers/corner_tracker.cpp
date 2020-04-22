#include <visual_feature_server/trackers/corner_tracker.h>

CornerTracker::CornerTracker(CornerFeature f, std::vector<double> s):
  Tracker(f, s), f_(f){
  ROS_WARN("Scale: %lf", f_.scale);
  init();
  for(int i = 0; i < scales.size(); i++)
  {
    weights.at(i) = pow(scales.at(i), 4)/4;
  }
  cv::namedWindow("CornerTracker", cv::WINDOW_NORMAL);
}

CornerTracker::~CornerTracker()
{}

std::vector<SearchGoal> CornerTracker::Search(cv::Mat input_image)
{
  convertTime = ros::Time(0);
  std::vector<SearchGoal> r;
  ROS_WARN("BLURRING CORNER");
  cv::Mat grayImage;
  cv::cvtColor(input_image, grayImage, CV_BGR2GRAY );
  blurImage(grayImage);
  cv::Mat dst, dst_norm, dst_norm_scaled;
  cv::cornerHarris(blurredImage, dst, 15, 19, 0.04);
  // cv::cornerHarris(blurredImage, dst, 3, 5, 0.04);

  cv::normalize( dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat() );
  cv::convertScaleAbs( dst_norm, dst_norm_scaled );
  int seen = 0;
  std::vector<cv::Point> centers;
  for( int i = 0; i < dst_norm.rows ; i++ )
  {
    for( int j = 0; j < dst_norm.cols; j++ )
    {
      if( (int) dst_norm.at<float>(i,j) > f_.threshold )
      {
        seen++;
        centers.push_back(cv::Point(i, j));
      }
    }
  }

  visual_feature_server::Convert2DPoint::Response res;
  if(f_.convert(centers, convertTime, res))
  {
    visual_feature_server::FeaturePoses features;
    for(int i = 0; i < centers.size(); i++)
    {
      visual_feature_server::FeatureMsg msg;
      msg.name = visual_feature_server::FeatureMsg::CORNER_STR;
      msg.type = visual_feature_server::FeatureMsg::CORNER;
      msg.image_scale = f_.scale;

      double d = sqrt((res.x_source.at(i)*res.x_source.at(i))
            + (res.y_source.at(i)*res.y_source.at(i))
            + (res.z_source.at(i)*res.z_source.at(i)));
      double world_scale = sqrt(2*f_.scale)*d/FOCAL_LENGTH;
      msg.world_scale = world_scale;

      msg.cornerFeature.threshold = f_.threshold;
      msg.cornerFeature.centroid.header.stamp = convertTime;
      msg.cornerFeature.centroid.header.frame_id = "/world";
      msg.cornerFeature.centroid.pose.pose.position.x = res.x_dest.at(i);
      msg.cornerFeature.centroid.pose.pose.position.y = res.y_dest.at(i);
      msg.cornerFeature.centroid.pose.pose.position.z = res.z_dest.at(i);

      msg.cornerFeature.centroid.pose.pose.orientation.x = 0;
      msg.cornerFeature.centroid.pose.pose.orientation.y = 0;
      msg.cornerFeature.centroid.pose.pose.orientation.z = 0;
      msg.cornerFeature.centroid.pose.pose.orientation.w = 1;
      geometry_msgs::PoseWithCovariance::_covariance_type cov;
      f_.populateCovariance(cov);
      msg.cornerFeature.centroid.pose.covariance = cov;
      features.features.push_back(msg);
      SearchGoal s;
      s.image_scale = f_.scale;
      s.world_scale = world_scale;
      s.x_i = centers.at(i).x;
      s.y_i = centers.at(i).y;
      s.x_w = res.x_dest.at(i);
      s.y_w = res.y_dest.at(i);
      s.z_w = res.z_dest.at(i);
      r.push_back(s);
      cv::circle( dst_norm_scaled, centers.at(i), 5,  cv::Scalar(255, 0, 255), 2, 8, 0 );
    }
    f_.feature_tag_pub_.publish(features);
  }
  // ROS_ERROR_STREAM("SEEN " << seen << " corners");
  // cv::imshow("CornerTracker", dst_norm_scaled);
  // cv::waitKey(10);
  // ROS_WARN_STREAM("RETURNING CORNER");
  return r;

}

cv::Mat CornerTracker::Visualize(cv::Mat input_image, std::vector<SearchGoal> s)
{
  cv::Mat annotated = input_image.clone();
  for(int i =0; i < s.size(); i++)
  {
    cv::circle( annotated, cv::Point(s.at(i).x_i, s.at(i).y_i), 5,  cv::Scalar(0, 0, 255), 2, 8, 0 );
  }
  return annotated;
}


void CornerTracker::getGausDerX(int size, double sigma, Eigen::MatrixXf &result)
{
  Eigen::MatrixXf x, y;
  initializeFilter(size, x, y);

  Eigen::MatrixXf temp1(size, size);
  Eigen::MatrixXf temp2(size, size);
  Eigen::MatrixXf temp3(size, size);

  temp1 = x.cwiseProduct(x);
  temp1 = temp1 * (-1 / (2 * pow(sigma, 2)));
  temp1 = temp1.unaryExpr<float(*)(float)>(&std::exp);

  temp2 = y.cwiseProduct(y);
  temp2 = temp2 * (-1 / (2 * pow(sigma, 2)));
  temp2 = temp2.unaryExpr<float(*)(float)>(&std::exp);

  temp3 = temp1.cwiseProduct(temp2);
  result = x.cwiseProduct(temp3);
  result = result * (1 / (2 * CV_PI * pow(sigma, 4)));
}

void CornerTracker::getGausDerY(int size, double sigma, Eigen::MatrixXf &result)
{
  Eigen::MatrixXf x, y;
  initializeFilter(size, x, y);


  Eigen::MatrixXf temp1(size, size);
  Eigen::MatrixXf temp2(size, size);
  Eigen::MatrixXf temp3(size, size);

  temp1 = x.cwiseProduct(x);
  temp1 = temp1 * (-1 / (2 * pow(sigma, 2)));
  temp1 = temp1.unaryExpr<float(*)(float)>(&std::exp);

  temp2 = y.cwiseProduct(y);
  temp2 = temp2 * (-1 / (2 * pow(sigma, 2)));
  temp2 = temp2.unaryExpr<float(*)(float)>(&std::exp);

  temp3 = temp1.cwiseProduct(temp2);
  result = y.cwiseProduct(temp3);
  result = result * (1 / (2 * CV_PI * pow(sigma, 4)));
}

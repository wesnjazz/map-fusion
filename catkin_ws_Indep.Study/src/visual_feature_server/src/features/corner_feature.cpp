#include <visual_feature_server/features/corner_feature.h>

CornerFeature::CornerFeature(ros::NodeHandle node_handle):Feature(node_handle){
  //kf_ = new KalmanFilter(SIGMA_PROCESS, SIGMA_OBS, 1, 6);
}

void CornerFeature::initalizeEstimate()
{
  /*
  Eigen::MatrixXf est_cov(6, 6);
  est_cov << 0.000459,-0.000002,0.000030, 0,0,0,
            -0.000002,0.000065,-0.000172,0,0,0,
            0.000030,-0.000172,0.001437,0,0,0,
            0,0,0,0,0,0,
            0,0,0,0,0,0,
            0,0,0,0,0,0;

    Eigen::VectorXf x_plus(6);
    x_plus(0) = x_;
    x_plus(1) = y_;
    x_plus(2) = z_;
    x_plus(3) = 0;
    x_plus(4) = 0;
    x_plus(5) = 0;
    e = Estimate (x_plus, est_cov, 6);
    */
}

void CornerFeature::updateEstimates(bool seen)
{
  /*
  Eigen::VectorXf pos(3);
  pos << x_, y_, z_;
  Eigen::MatrixXf sensor_cov(3, 3);
  sensor_cov << 0.000459,-0.000002,0.000030,-0.000002,0.000065,-0.000172,0.000030,-0.000172,0.001437;
  Observation obs(pos, sensor_cov, 3);
  e = kf_->kf(seen, e, obs, 6);



  Eigen::MatrixXf cov = e.getPositionCovariance();
  Eigen::Matrix3d P;
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 3; k++) {
      P(j,k) = cov(j,k);
    }
  }

  ecl::CovarianceEllipsoid3d ellipse(P);
  const Eigen::Vector3d& lengths = ellipse.lengths();
  double eigenval_x = lengths[0]*lengths[0];
  double eigenval_y = lengths[1]*lengths[1];
  double eigenval_z = lengths[2]*lengths[2];

  const Eigen::Matrix3d& axes = ellipse.axes();

  Eigen::VectorXf eigenvec_x(3);
  eigenvec_x(0) = axes(0,0);
  eigenvec_x(1) = axes(0,1);
  eigenvec_x(2) = axes(0,2);
  Eigen::VectorXf eigenvec_y(3);
  eigenvec_y(0) = axes(1,0);
  eigenvec_y(1) = axes(1,1);
  eigenvec_y(2) = axes(1,2);
  Eigen::VectorXf eigenvec_z(3);
  eigenvec_z(0) = axes(2,0);
  eigenvec_z(1) = axes(2,1);
  eigenvec_z(2) = axes(2,2);

  KDL::Rotation r(eigenvec_x(0), eigenvec_x(1), eigenvec_x(2), eigenvec_y(0), eigenvec_y(1), eigenvec_y(2), eigenvec_z(0), eigenvec_z(1), eigenvec_z(2));
  double x,y,z,w;
  r.GetQuaternion(x, y, z, w);


  double quat_sum = sqrt((x*x) + (y*y) + (z*z) + (w*w));
  ROS_INFO_STREAM("Length " << lengths[0] << ", " << lengths[1] << "," << lengths[2] );

  ROS_INFO_STREAM("Eigenval " << eigenval_x << ", " << eigenval_y << "," << eigenval_z );
  visualization_msgs::Marker rviz_marker;
  rviz_marker.header.stamp = ros::Time(0);
  rviz_marker.header.frame_id = "world";
  rviz_marker.ns = "corner_covariance";
  rviz_marker.id = 1;
  rviz_marker.type = visualization_msgs::Marker::SPHERE;
  rviz_marker.action = visualization_msgs::Marker::ADD;
  rviz_marker.pose.position.x = x_;
  rviz_marker.pose.position.y = y_;
  rviz_marker.pose.position.z = z_;
  rviz_marker.pose.orientation.x = x/(quat_sum);
  rviz_marker.pose.orientation.y = y/(quat_sum);
  rviz_marker.pose.orientation.z = z/(quat_sum);
  rviz_marker.pose.orientation.w = w/(quat_sum);
  rviz_marker.scale.x = sqrt(eigenval_x)*15;
  rviz_marker.scale.y = sqrt(eigenval_y)*15;
  rviz_marker.scale.z = sqrt(eigenval_z)*15;
  rviz_marker.color.r = 1.0f;
  rviz_marker.color.g = 0.0f;
  rviz_marker.color.b = 1.0f;
  rviz_marker.color.a = 0.5;
  rviz_marker.lifetime = ros::Duration(0);

  ROS_WARN_STREAM("GPONG TOP PUBLISH WITH (" << rviz_marker.pose.position.x << ","
        << rviz_marker.pose.position.y << "," <<rviz_marker.pose.position.z << ") orientation ("
        << rviz_marker.pose.orientation.x << "," << rviz_marker.pose.orientation.y
        << "," << rviz_marker.pose.orientation.y << "," << rviz_marker.pose.orientation.z
        << ") and scale( " << rviz_marker.scale.x << ", " << rviz_marker.scale.y << ", "
        << rviz_marker.scale.z << ") ");
  if(std::isnan(rviz_marker.pose.position.x) || std::isnan(rviz_marker.pose.position.y) ||
      std::isnan(rviz_marker.pose.position.z) || std::isnan(rviz_marker.pose.orientation.x) ||
      std::isnan(rviz_marker.pose.orientation.y) || std::isnan(rviz_marker.pose.orientation.z) ||
      std::isnan(rviz_marker.pose.orientation.w) || std::isnan(rviz_marker.scale.x) <<
      std::isnan(rviz_marker.scale.y) || std::isnan(rviz_marker.scale.z))
      {
        return;
      }


  // rviz_marker_pub.publish(rviz_marker);

  */

}

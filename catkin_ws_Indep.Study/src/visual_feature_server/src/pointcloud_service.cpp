#include "visual_feature_server/pointcloud_service.h"

PointCloudService::PointCloudService(ros::NodeHandle node_handle):n_(node_handle), point_cloud(640, 480, pcl::PointXYZ())
{
  points_sub = n_.subscribe("/asus/depth_registered/points", 1,
                      &PointCloudService::pointsCallback, this);
  ros::ServiceServer service = n_.advertiseService("/visual_feature_detector/convert_2d_point",
                      &PointCloudService::pointcloudService, this);
  ros::spin();
}

PointCloudService::~PointCloudService()
{}


bool PointCloudService::pointcloudService(visual_feature_server::Convert2DPoint::Request &request,
  visual_feature_server::Convert2DPoint::Response &response )
{
  response.x_source.resize(request.x.size());
  response.y_source.resize(request.x.size());
  response.z_source.resize(request.x.size());

  response.x_dest.resize(request.x.size());
  response.y_dest.resize(request.x.size());
  response.z_dest.resize(request.x.size());


  for(int i = 0 ; i < request.x.size(); i++)
  {
    pcl::PointXYZ p = point_cloud.at(request.x.at(i), request.y.at(i));
    response.x_source.at(i) = p.x;
    response.y_source.at(i) = p.y;
    response.z_source.at(i) = p.z;
    p = transformPoint(p, request.stamp, std::string(request.source_frame), std::string(request.destination_frame));
    response.x_dest.at(i) = p.x;
    response.y_dest.at(i) = p.y;
    response.z_dest.at(i) = p.z;
    // if(isnan(response.x_dest.at(i)) || isnan(response.y_dest.at(i)) || isnan(response.z_dest.at(i))
    // || isnan(response.x_source.at(i)) || isnan(response.y_source.at(i)) || isnan(response.z_source.at(i)))
    // {
    //   return false;
    // }
  }
  return true;
}
pcl::PointXYZ PointCloudService::transformPoint(pcl::PointXYZ source, ros::Time convertTime,
  std::string source_frame, std::string destination_frame)
{
  try
  {
    geometry_msgs::PointStamped point_src;
    point_src.header.frame_id = source_frame;

    //we'll just use the most recent transform available for our simple example
    point_src.header.stamp = convertTime;

    //just an arbitrary point in space
    point_src.point.x = source.x;
    point_src.point.y = source.y;
    point_src.point.z = source.z;
    geometry_msgs::PointStamped point_des;
    tf_listener.waitForTransform(point_src.header.frame_id,
       destination_frame,
       point_src.header.stamp,
       ros::Duration(3.0));
    tf_listener.transformPoint(destination_frame, point_src, point_des);
    pcl::PointXYZ destination(point_des.point.x, point_des.point.y, point_des.point.z);
    return destination;
  }
  catch(tf::TransformException& ex){
    ROS_ERROR("Received an exception trying to transform a point from \"kinect_openni_frame\" to \"head_base_link\": %s", ex.what());
  }
}

void PointCloudService::pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
   pcl::fromROSMsg(*msg, point_cloud);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pointcloud_service");
  ros::NodeHandle n("~");
  PointCloudService p(n);
  ros::Rate rate(500);
  while(ros::ok())
  {
    ros::spinOnce();
  }
}

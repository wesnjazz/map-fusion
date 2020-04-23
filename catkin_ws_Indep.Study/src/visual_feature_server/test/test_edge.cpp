#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>
// #include "opencv2/legacy/legacy.hpp"
#include "visual_feature_server/trackers/blob_tracker.h"
#include "visual_feature_server/trackers/edge_tracker.h"
#include "visual_feature_server/trackers/corner_tracker.h"
#include <stdlib.h>
#include <sys/stat.h>

cv::Mat input_image;
image_transport::Subscriber image_sub;
void cameraCallback(const sensor_msgs::ImageConstPtr& msg)
{
  ROS_INFO("CAMERA CALLBACK IN ");
   cv_bridge::CvImagePtr cam_image;

   try
   {
      cam_image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
   }
   catch (cv_bridge::Exception& e)
   {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
   }

   // if (cam_image)
   {
     input_image = cam_image->image.clone();
   }
   ROS_INFO("CAMERA CALLBACK OUT ");
   return;
}

int main(int argc, char** argv)

{

  ros::init(argc, argv, "visual_features");
  ros::NodeHandle n_("~");
  cv::Mat image = cv::imread("/home/dpark/map-fusion/map_data/guitar01.jpg", CV_LOAD_IMAGE_COLOR);
  // cv::Mat image = cv::imread("/home/dpark/map-fusion/map_data/img01_nonoise.jpg", CV_LOAD_IMAGE_COLOR);
  // cv::Mat image = cv::imread("/home/khoshrav/Desktop/lina.png", CV_LOAD_IMAGE_COLOR);
  if(! image.data )                              // Check for invalid input
   {
       std::cout <<  "Could not open or find the image" << std::endl ;
       return -1;
   }
   cv::namedWindow("INPUT", CV_WINDOW_NORMAL);
   cv::namedWindow("keypoints-Visualize", CV_WINDOW_NORMAL);
   cv::namedWindow("keypoints-Top", CV_WINDOW_NORMAL);
   cv::namedWindow("TestImage", CV_WINDOW_NORMAL);



   ROS_WARN_STREAM("hei " << image.size().height << " w" << image.size().width);
   cv::imshow("INPUT", image);
   cv::waitKey(10);
   EdgeFeature edgeFeature(n_);
   //
   // blobFeature.hLow = 110;
   // blobFeature.sLow = 120;
   // blobFeature.vLow = 120;
   //
   // blobFeature.hHigh = 130;
   // blobFeature.sHigh = 255;
   // blobFeature.vHigh = 255;
   // blobFeature.scale = 15;

   // blobFeature.hLow = 0;
   // blobFeature.sLow = 160;
   // blobFeature.vLow = 100;
   //
   // blobFeature.hHigh = 40;
   // blobFeature.sHigh = 255;
   // blobFeature.vHigh = 255;

   // ROS_WARN_STREAM("MADE BLOB FEATURE");
   std::vector<double> edge_s;
   // edge_s.push_back(1);
   // edge_s.push_back(4);
   // edge_s.push_back(16);
   // edge_s.push_back(64);
   // edge_s.push_back(128);
   // edge_s.push_back(512);
   // edge_s.push_back(1024);
   // edge_s.push_back(2048);
   // edge_s.push_back(4096);
   // edge_s.push_back(8192);
   for(int i =1; i < 52; i+=10)
   {
       edge_s.push_back(i);
   }
   std::shared_ptr<EdgeTracker> edgeTracker = std::make_shared<EdgeTracker>(edgeFeature, edge_s);

  while(ros::ok())
  {
    ros::spinOnce();
    std::vector<SearchGoal> goals = edgeTracker->Search(image);
    cv::Mat im_visualize = edgeTracker->Visualize(image.clone(), goals);
    cv::imshow("keypoints-Visualize", im_visualize );
    cv::waitKey(10);







    // Show blobs
    cv::imwrite( "/home/khoshrav/Desktop/ATG/test_edge_annotates.jpg", im_visualize );

  }
  return 0;
}

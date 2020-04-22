#include <ros/ros.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <image_transport/image_transport.h>
#include <std_msgs/Bool.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv/highgui.h>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>

#include "visual_feature_server/trackers/blob_tracker.h"
cv::Mat input_image;
bool isMoving = false;
void cameraCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cam_image;
  try
  {
    cam_image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    input_image = cam_image->image.clone();
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  }
  return;
}

void isMovingCallback(const std_msgs::Bool& msg)
{
  isMoving = msg.data;
  ROS_INFO_STREAM("In callback Data " << msg.data << " flag " << isMoving);
}

int main(int argc, char** argv)

{

  ros::init(argc, argv, "scale_features");
  int count  =0;
  ros::NodeHandle n("~");
  image_transport::ImageTransport it_(n);


  BlobFeature blobFeature(n);

  // ROS_WARN_STREAM("MADE BLOB FEATURE");
  std::vector<double> blob_s;
  // blob_s.push_back(1);
  // blob_s.push_back(4);
  // blob_s.push_back(8);
  // blob_s.push_back(16);
  // blob_s.push_back(24);
  // blob_s.push_back(32);
  for(double i =1; i < 20; i++)
  {
    blob_s.push_back(i);
  }
  blob_s.push_back(40);
  blob_s.push_back(48);
  blob_s.push_back(56);
  blob_s.push_back(60);
  blob_s.push_back(64);
  blob_s.push_back(72);
  blob_s.push_back(128);
  blob_s.push_back(254);
  blob_s.push_back(512);
  // blob_s.push_back(762);
  // blob_s.push_back(1024);
  // blob_s.push_back(2048);
  // blob_s.push_back(3072);
  // blob_s.push_back(4096);
  // blob_s.push_back(6400);
  // blob_s.push_back(8192);
  // blob_s.push_back(10000);
  // blob_s.push_back(12996);
  // blob_s.push_back(16384);
  std::shared_ptr<BlobTracker> blobTracker = std::make_shared<BlobTracker>(blobFeature, blob_s);
  cv::namedWindow("BlobTrackerOutput", cv::WINDOW_NORMAL);
  cv::namedWindow("ScaleFeatures", cv::WINDOW_NORMAL);
  ros::Subscriber isMovingSub = n.subscribe("/uBot_head/isMoving", 1,&isMovingCallback);

  image_transport::Subscriber image_sub = it_.subscribe("/asus/rgb/image_rect_color", 1,
  &cameraCallback);
  ros::Rate rate(1);

  while(ros::ok())
  {
    ros::spinOnce();
    if(input_image.empty())
    {
      // ROS_WARN("Image is empty");
      continue;
    }
    if(isMoving == true)
    {
      ROS_WARN("Is moving");
      continue;
    }
    cv::imshow("ScaleFeatures",input_image);
    // cv::waitKey(10);
    cv::waitKey(10);
    std::vector<SearchGoal> r = blobTracker->Search( input_image);
    cv::Mat annotated = blobTracker->Visualize(input_image, r);
    cv::imshow("BlobTrackerOutput", annotated);
    cv::imwrite( "/home/khoshrav/Desktop/ATG/scale_space_blob_annotated.jpg", annotated );

    cv::waitKey(10);


    rate.sleep();
  }
  return 0;
}

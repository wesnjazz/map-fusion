#include <visual_feature_server/trackers/blob_tracker.h>

BlobTracker::BlobTracker(BlobFeature f, std::vector <double> s):
Tracker(f, s), f_(f){
  init();
  filters.clear();

  for(int i = 0; i < scales.size(); i++)
  {
    weights.at(i) = pow(scales.at(i), 1);
    filters.push_back(filterX.at(i) + filterY.at(i));
  }

  binary_image_ = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);
  maxResponseScales_ = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32F);

  min_response_ = 125;
  max_response_ = 255;
  largest_responses_percent = 2;
  cv::namedWindow("BlobTracker", CV_WINDOW_NORMAL || CV_WINDOW_KEEPRATIO);
  cv::namedWindow("Log", CV_WINDOW_NORMAL || CV_WINDOW_KEEPRATIO);

  cv::createTrackbar("Minimum Response", "BlobTracker", &min_response_, 255, NULL);
  cv::createTrackbar("Number of max responses", "BlobTracker", &largest_responses_percent, 100, NULL);
  cv::namedWindow("MaxBlobResponse", CV_WINDOW_NORMAL || CV_WINDOW_KEEPRATIO);
  //necessary to have time to initialize display window correctly
  cv::waitKey(50);
  ROS_ERROR("LEFT");
}

BlobTracker::~BlobTracker()
{}

void BlobTracker::getBlobResponse(cv::Mat gray_image)
{
  //  Console.WriteLine("Min Orient : {0}, Max Orient : {1}", minOrientation, maxOrientation);
  // do the convolution
  for (int i = 0; i < scales.size(); i++)
  {
    responses.at(i) = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH,CV_32FC1);
    cv::filter2D(gray_image,responses.at(i), -1, filters.at(i), cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
    responses.at(i).convertTo(responses.at(i), CV_32FC1);
    responses.at(i) = responses.at(i)/2.00;
    responses.at(i) = cv::abs(responses.at(i));
    responses.at(i) = responses.at(i) *  weights.at(i);
  }


  cv::Mat maxResponse_ = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32F);
  double scaledVal, scaledValPositive, scaledValNegative;
  // compute max response at each scale
  for (int i = 0; i < gray_image.size().height; i++)
  {
    for (int j = 0; j < gray_image.size().width; j++)
    {
      for (int k = 0; k < scales.size(); k++)
      {
        scaledVal = responses.at(k).at<float>(i,j);// * weights.at(k);
        if ((float)scaledVal > (maxResponse_.at<float>(i,j))) // actually clip out negative vals
        {
          maxResponse_.at<float>(i, j) = ((float)scaledVal);
          maxResponseScales_.at<float>(i, j) = scales.at(k);
        }
      }
    }
  }

  //normalize values from maxResponse and place them in binary_img
  double minval = 0;
  double maxval = 0;
  cv::minMaxLoc(maxResponse_, &minval, &maxval);
  ROS_ERROR_STREAM("MaxResponse_ max" << maxval << " min " << minval);
  minval = std::abs(minval);
  maxval = std::abs(maxval);
  float old_range = maxval - minval;
  float new_range = 255-0;
  cv::Mat max_response_image_ = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32FC1);

  if (maxval > 0)
  {
    for (int i = 0; i < max_response_image_.size().height; i++)
    {
      for (int j = 0; j < max_response_image_.size().width; j++)
      {
        max_response_image_.at <float> (i,j) = ((maxResponse_.at<float>(i,j) - minval) * new_range / old_range);
      }
    }
    max_response_image_.convertTo(max_response_image_, CV_32FC1);

    max_pixels.clear();
    cv::Mat maxResponseCopy = max_response_image_.clone();
    int number_pixels = largest_responses_percent*max_response_image_.size().height*
                      max_response_image_.size().width/100;
    for(int i = 0; i < number_pixels; i++)
    {
      double minVal;
      double maxVal;
      cv::Point minLoc;
      cv::Point maxLoc;
      cv::minMaxLoc( maxResponseCopy, &minVal, &maxVal, &minLoc, &maxLoc );
      max_pixels.push_back(maxLoc);
      maxResponseCopy.at <float>(maxLoc) = -10;
    }

    // int counter = 0;
    // while(max_pixels.size() <= 5)// number_pixels) //for(int i = 0; i < number_pixels; i++)
    // {
    //   ROS_INFO_STREAM("MAX pixels/number pixels " << max_pixels.size() << "/" << number_pixels);
    //   ROS_INFO_STREAM("counter/all pixels " << counter++ << "/" << max_response_image_.size().height*
    //                     max_response_image_.size().width);
    //
    //   double minVal = 0;
    //   double maxVal = 0;
    //   cv::Point minLoc;
    //   cv::Point maxLoc;
    //   cv::minMaxLoc( maxResponseCopy, &minVal, &maxVal, &minLoc, &maxLoc );
    //   if(maxVal <= 0)
    //   {
    //     ROS_ERROR_STREAM("ALL PIXELS < 0");
    //     break;
    //   }
    //   double scale = maxResponseScales_.at<float>(maxLoc);
    //   double filter_size = getFilterSize(sqrt(scale));
    //   double range = (filter_size - 1.00)/2.00;
    //   bool overlapping = false;
    //   ROS_ERROR_STREAM("MAX found at maxLoc x " << maxLoc.x << " y " << maxLoc.y <<  " is " << maxVal << " at scale " << scale << " filter size " << filter_size << " range " << range );
    //   double start_x = std::max(0, static_cast<int>(maxLoc.x - range));
    //   double stop_x = std::min(static_cast<int>(maxLoc.x + range), maxResponseCopy.size().width);
    //   double start_y = std::max(0, static_cast<int>(maxLoc.y - range));
    //   double stop_y = std::min(static_cast<int>(maxLoc.y + range), maxResponseCopy.size().height);
    //   ROS_ERROR_STREAM("Min X " << start_x << " max x" << stop_x << " min y " << start_y << " max y" << stop_y);
    //
    //   for(int relx = start_x; relx <= stop_x; relx ++)
    //   {
    //     for(int rely = start_y; rely <= stop_y; rely ++)
    //       {
    //         if(maxResponseCopy.at<float>(rely, relx) < 0)
    //         {
    //           overlapping = true;
    //           ROS_ERROR_STREAM("QUITTTING COS NEIGHBOR");
    //           break;
    //         }
    //     }
    //     if(overlapping == true)
    //     {
    //       ROS_WARN_STREAM("Quitting relx");
    //       break;
    //     }
    //   }
    //
    //   if(overlapping == false)
    //   {
    //     for(int relx = start_x; relx <= stop_x; relx ++)
    //     {
    //       for(int rely = start_y; rely <= stop_y; rely ++)
    //       {
    //         ROS_INFO_STREAM("\t relx" << relx << " rely " << rely << " was " << maxResponseCopy.at<float>(rely, relx));
    //         maxResponseCopy.at<float>(rely, relx) = -10;
    //         ROS_INFO_STREAM("\t\t Now is " << maxResponseCopy.at<float>(rely, relx));
    //       }
    //     }
    //     max_pixels.push_back(maxLoc);
    //   }
    // }

    cv::inRange(max_response_image_, cv::Scalar(min_response_),cv::Scalar(max_response_), binary_image_);
    cv::Mat temp = max_response_image_/255.00;
    cv::imshow("Log", temp);
  }
}

std::vector<SearchGoal> BlobTracker::Search(cv::Mat input_image)
{
  convertTime = ros::Time(0);
  cv::Mat gray_image = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32FC1);
  cvtColor(input_image, gray_image, CV_BGR2GRAY);
  gray_image.convertTo(gray_image, CV_32FC1);


  std::vector<SearchGoal> r;
  r.clear();

  maxResponseScales_.setTo(cv::Scalar(-1));

  binary_image_.setTo(cv::Scalar(0));

  getBlobResponse(gray_image);


  cv::Mat threshold_image_ = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32FC3);
  //get a copy of the color image with only the blobs visible
  input_image.copyTo(threshold_image_, binary_image_);
  cv::imshow( "BlobTracker", threshold_image_ );
  cv::waitKey(10);


  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours( binary_image_, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
  // ROS_WARN_STREAM("LOOPING-Visualize" << contours.size());
  // for( int j = 0; j< std::min(4, (int)contours.size()); j++ )
  std::vector<cv::Point> centers;
  for( int j = 0; j< contours.size(); j++ )

  {
    cv::Moments moment = cv::moments(contours.at(j), true);
    if(moment.m00 == 0)
    {
      continue;
    }

    cv::Point center(int(moment.m10/moment.m00), int(moment.m01/moment.m00));
    centers.push_back(center);
  }
  visual_feature_server::Convert2DPoint::Response res;
  if(f_.convert(centers, convertTime, res))
  {
    visual_feature_server::FeaturePoses features;
    for(int j = 0; j < centers.size(); j++ )
    {
      if(::isnan(res.x_dest.at(j)) || ::isnan(res.y_dest.at(j)) || ::isnan(res.z_dest.at(j))
      || ::isnan(res.x_source.at(j)) || ::isnan(res.y_source.at(j)) || ::isnan(res.z_source.at(j)))
      {
        ROS_WARN_STREAM("Skipping blob at " << j);
        // continue;
      }
      float scale = maxResponseScales_.at<float>(centers.at(j));

      if(scale == -1)
      {
        ROS_ERROR_STREAM("NO response at "<< centers.at(j));
        continue;
      }
      visual_feature_server::FeatureMsg msg;
      msg.name = visual_feature_server::FeatureMsg::BLOB_STR;
      msg.type = visual_feature_server::FeatureMsg::BLOB;
      msg.image_scale = scale;

      double d = sqrt((res.x_source.at(j)*res.x_source.at(j)) + (res.y_source.at(j)*res.y_source.at(j)) + (res.z_source.at(j)*res.z_source.at(j)));
      double world_scale = (sqrt(2*scale)*d)/(FOCAL_LENGTH);
      // world_scale = round(world_scale);
      // int round_value = 50;
      // int temp_round = (world_scale + (round_value - 1))/round_value;
      // world_scale =  temp_round * round_value;
      world_scale = -1;
      msg.world_scale = world_scale;

      msg.x_pixel = centers.at(j).x;
      msg.y_pixel = centers.at(j).y;
      msg.blobFeature.hHigh = f_.hHigh;
      msg.blobFeature.hLow = f_.hLow;
      msg.blobFeature.sHigh = f_.sHigh;
      msg.blobFeature.sLow = f_.sLow;
      msg.blobFeature.vHigh = f_.vHigh;
      msg.blobFeature.vLow = f_.vLow;
      msg.blobFeature.threshold = min_response_;

      msg.blobFeature.centroid.header.stamp = convertTime;
      msg.blobFeature.centroid.header.frame_id = "/world";
      msg.blobFeature.centroid.pose.pose.position.x = res.x_dest.at(j);
      msg.blobFeature.centroid.pose.pose.position.y = res.y_dest.at(j);
      msg.blobFeature.centroid.pose.pose.position.z = res.z_dest.at(j);

      msg.blobFeature.centroid.pose.pose.orientation.x = 0;
      msg.blobFeature.centroid.pose.pose.orientation.y = 0;
      msg.blobFeature.centroid.pose.pose.orientation.z = 0;
      msg.blobFeature.centroid.pose.pose.orientation.w = 1;

      geometry_msgs::PoseWithCovariance::_covariance_type cov;
      f_.populateCovariance(cov);
      msg.blobFeature.centroid.pose.covariance = cov;


      features.features.push_back(msg);

      SearchGoal sg;
      sg.image_scale = scale;
      sg.world_scale = world_scale;

      sg.x_i = centers.at(j).x;
      sg.y_i = centers.at(j).y;
      sg.x_w = res.x_dest.at(j);
      sg.y_w = res.y_dest.at(j);
      sg.z_w = res.z_dest.at(j);
      // ROS_INFO_STREAM("xi " << sg.x_i << " yi " << sg.y_i << " x_w " << sg.x_w << " y_w " << sg.y_w << " z_w " << sg.z_w);
      // ROS_WARN_STREAM("Image scale " << sg.image_scale << " world scale " << sg.world_scale);
      r.push_back(sg);
      // if(r.size() == 3)
      //   break;
    }
    // ROS_WARN_STREAM("Publishing filtered_features " << features.features.size() << " observations");
    // if(r.size() > 3)
    // {
    //   ROS_ERROR_STREAM("Too many features! Size: " << r.size());
    //   for(int i= 0; i < r.size(); i++)
    //   {
    //     SearchGoal sg = r.at(i);
    //     ROS_INFO_STREAM("xi " << sg.x_i << " yi " << sg.y_i << " x_w " << sg.x_w << " y_w " << sg.y_w << " z_w " << sg.z_w);
    //     ROS_WARN_STREAM("Image scale " << sg.image_scale << " world scale " << sg.world_scale);
    //
    //   }
    //   cv::waitKey(0);
    // }
    f_.feature_tag_pub_.publish(features);
  }

  return r;

}

cv::Mat BlobTracker::Visualize(cv::Mat input_image, std::vector<SearchGoal> s)
{
  cv::Mat annotated_image = input_image.clone();
  for(int i = 0; i < s.size(); i++)
  {
    cv::Point center(s.at(i).x_i, s.at(i).y_i);
    double radius = sqrt(2*s.at(i).image_scale);
    if(radius > IMAGE_WIDTH/2)
    {
      radius = IMAGE_WIDTH/2;
    }
    if(radius > IMAGE_HEIGHT/2)
    {
      radius = IMAGE_HEIGHT/2;
    }
    cv::circle(annotated_image, center, radius, cv::Scalar(255, 0,0));
    // cv::putText(annotated_image, std::to_string(i), center, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0,143,143), 2);
    // cv::circle(annotated_image, center, getFilterSize(s.at(i).scale), cv::Scalar(0, 0,255));
  }

  cv::Mat top_responses = input_image.clone();
  for(int i = 0; i < max_pixels.size(); i++)
  {
    cv::Point pixel = max_pixels.at(i);
    float scale = maxResponseScales_.at<float>(pixel);
    if(scale > 0 )
    {
      cv::circle(top_responses, pixel, ((sqrt(scale/2)*5)+1)/2, cv::Scalar(0, 0, 255));
      cv::circle(top_responses, pixel,1, cv::Scalar(255,0,0),CV_FILLED);
      // ROS_WARN_STREAM("Plot center scale" <<  scale);
    }
  }
  cv::imshow("MaxBlobResponse", top_responses);
  cv::waitKey(10);

  return annotated_image;
}

//Second Derivative
void BlobTracker::getGausDerX(int size, double sigma, Eigen::MatrixXf &result)
{
  Eigen::MatrixXf x, y;
  initializeFilter(size, x, y);
  Eigen::MatrixXf temp1(size, size);
  Eigen::MatrixXf temp2(size, size);
  Eigen::MatrixXf temp3(size, size);

  temp1 = x.cwiseProduct(x);
  temp1 = temp1.array() - std::pow(sigma, 2.0);
  temp1 = temp1 * (1.0 / (2.0 * CV_PI * std::pow(sigma, 6.0)));

  temp2 = x.cwiseProduct(x);
  temp2 = temp2 * (-1.0 / (2.0 * std::pow(sigma, 2.0)));
  temp2 = temp2.array().exp();

  temp3 = y.cwiseProduct(y);
  temp3 = temp3 * (-1.0 / (2.0 * std::pow(sigma, 2.0)));
  temp3 = temp3.array().exp();

  result = temp3.cwiseProduct(temp2);
  result = result.cwiseProduct(temp1);

}

void BlobTracker::getGausDerY(int size, double sigma, Eigen::MatrixXf &result)
{
  Eigen::MatrixXf x, y;
  initializeFilter(size, x, y);


  Eigen::MatrixXf temp1(size, size);
  Eigen::MatrixXf temp2(size, size);
  Eigen::MatrixXf temp3(size, size);

  temp1 = y.cwiseProduct(y);
  temp1 = temp1.array() - std::pow(sigma, 2.0);
  temp1 = temp1 * (1.0 / (2.0 * CV_PI * std::pow(sigma, 6.0)));

  temp2 = y.cwiseProduct(y);
  temp2 = temp2 * (-1.0 / (2.0 * std::pow(sigma, 2.0)));
  temp2 = temp2.array().exp();

  temp3 = x.cwiseProduct(x);
  temp3 = temp3 * (-1.0 / (2.0 * std::pow(sigma, 2.0)));
  temp3 = temp3.array().exp();

  result = temp3.cwiseProduct(temp2);
  result = result.cwiseProduct(temp1);
}

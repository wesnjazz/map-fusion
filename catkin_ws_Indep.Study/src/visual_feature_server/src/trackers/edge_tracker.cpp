#include <visual_feature_server/trackers/edge_tracker.h>

EdgeTracker::EdgeTracker(EdgeFeature f, std::vector<double> s,
  int number_of_orientations):Tracker(f, s), f_(f){
  ROS_WARN("Scale: %lf", f_.scale);
  init();
  for(int i = 0; i < scales.size(); i++)
  {
    weights.at(i) = pow(scales.at(i), 0.5)/pow(2, 0.25);
    cv::namedWindow("EdgeTrackerScale"+std::to_string(i), CV_WINDOW_NORMAL);
  }
  minOrientations.resize(number_of_orientations);
  maxOrientations.resize(number_of_orientations);
  maxResponses.resize(number_of_orientations);
  for(int i = 0; i < number_of_orientations; i++)
  {
    minOrientations.at(i) = ((CV_PI/number_of_orientations) * i);// - (CV_PI/2.00);
    maxOrientations.at(i) = (CV_PI/number_of_orientations) + minOrientations.at(i);
    maxResponses.at(i) = cvCreateMat(IMAGE_WIDTH, IMAGE_HEIGHT, CV_32FC1);
    cv::namedWindow("EdgeTracker"+std::to_string(i), CV_WINDOW_NORMAL);
    cv::namedWindow("TestImage"+std::to_string(i), CV_WINDOW_NORMAL);

    ROS_WARN_STREAM("Orientation " << i << " Min = " << minOrientations.at(i) << " max " << maxOrientations.at(i));
  }
  cv::namedWindow("EdgeTracker", cv::WINDOW_NORMAL);
  cv::namedWindow("EdgeTrackerBlur", cv::WINDOW_NORMAL);

  hedge = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);
  vedge = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);
  edge = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3);
  temp_blurred_image = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);
  blurred_image = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);
  cc_image = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3);
  // Create the output image
  cedge = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);
  copy_image = cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3);
  marked = 255;// marked.val[1] = 255; marked.val[2] = 255;
  unmarked = 0;
  color.resize(MAX_FEATURES);
  color.at(0)[0] = 255; color.at(0)[1] = 0;   color.at(0)[2] = 0;
  color.at(1)[0] = 0;   color.at(1)[1] = 255; color.at(1)[2] = 0;
  color.at(2)[0] = 255; color.at(2)[1] = 0;   color.at(2)[2] = 255;
  color.at(3)[0] = 255; color.at(3)[1] = 255; color.at(3)[2] = 0;
  color.at(4)[0] = 0;   color.at(4)[1] = 255; color.at(4)[2] = 255;

  for (int i = 5; i < MAX_FEATURES; i++)
  {
    color.at(i)[0] = (rand()%20) * 10;
    color.at(i)[1] = (rand()%20) * 10;
    color.at(i)[2] = (rand()%20) * 10;
  }
  blurKernel = 5;
  min_point_thresh = 200;
  mincc_thresh = 200;
  edge_thresh = 50;
  cv::createTrackbar("Threshold", "EdgeTracker", &edge_thresh, 255, NULL);

  start = true;
}

EdgeTracker::~EdgeTracker()
{}

void EdgeTracker::getEdgeResponse(cv::Mat gray_image)
{
  hedge = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC1);
  vedge = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC1);
  edge = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC3);
  temp_blurred_image = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC1);
  blurred_image = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC1);
  cc_image = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC3);
  // Create the output image
  cedge = cv::Mat(gray_image.rows, gray_image.cols, CV_32FC1);
  copy_image = cv::Mat(gray_image.rows, gray_image.cols, CV_8UC3);
  ROS_INFO_STREAM("Set things up");
  // do the convolution
  for (int i = 0; i < scales.size(); i++)
  {
    // (Lx^2 + Ly^2)^.5
    // ROS_INFO("Filtering");
    //Console.WriteLine("Doing Lx, Lx Convolution, scale={0}",i);
    cv::filter2D(gray_image, imgConvLx.at(i), -1, filterX.at(i));
    cv::filter2D(gray_image, imgConvLy.at(i), -1, filterY.at(i));
    responses.at(i).convertTo(responses.at(i), CV_32FC1);
    //Console.WriteLine("Squaring, scale={0}",i);
    // ROS_INFO("Squaring");
    cv::Mat sqx, sqy;
    cv::pow(imgConvLx.at(i), 2, sqx);
    cv::pow(imgConvLy.at(i), 2, sqy);
    //Console.WriteLine("Combining, scale={0}", i);
    // ROS_INFO("Adding");

    cv::add(sqx, sqy, responses.at(i));
    responses.at(i).convertTo(responses.at(i), CV_32FC1);
    // ROS_INFO("Squaring again");

    cv::pow(responses.at(i), 0.5, responses.at(i));

    // imgConvLx.at(i).convertTo(imgConvLx.at(i), CV_32FC1);
    // imgConvLy.at(i).convertTo(imgConvLy.at(i), CV_32FC1);
    //
    // cv::pow(imgConvLx.at(i), 0.5, imgConvLx.at(i));
    // cv::pow(imgConvLy.at(i), 0.5, imgConvLy.at(i));



    double max, min;
    cv::Mat scaled = responses.at(i);
    cv::minMaxLoc(responses.at(i), &min, &max);
    ROS_ERROR_STREAM("i " << i << " MaxResponse_" << max << " min " << min);
    float old_range = max - min;
    float new_range = 255-0;
    // if (max > 0)
    {
      for (int h = 0; h < responses.at(i).size().height; h++)
      {
        for (int w = 0; w < responses.at(i).size().width; w++)
        {
          scaled.at <float> (h,w) = ((responses.at(i).at<float>(h,w) - min) * new_range / old_range);
        }
      }
      // scaled.convertTo(scaled, CV_32FC1);
    }
    cv::imshow("EdgeTrackerScale"+std::to_string(i), scaled);
    cv::waitKey(10);
    cv::minMaxLoc(scaled, &min, &max);
    ROS_ERROR_STREAM(" \tMaxResponse_" << max << " min " << min);

  }
  cv::waitKey(0);
  ROS_WARN("DONE1");
  // zero max response matrix
  for(int i=0; i<minOrientations.size(); i++)
  {
    maxResponses.at(i) = cv::Mat::zeros(gray_image.rows, gray_image.cols, CV_32FC1);
  }

  double scaledVal;
  double orientation;
  ROS_WARN_STREAM("DONE2" <<  "w 2 " << responses.at(0).cols << "h 1 " << responses.at(0).rows);

  // compute max response at each scale
  for (int w = 0; w < responses.at(0).cols; w++)
  {
    for (int h = 0; h < responses.at(0).rows; h++)
    {
      for (int i = 0; i < scales.size(); i++)
      {
        scaledVal = weights.at(i) * (responses.at(i).at<float>(h, w));
        orientation = atan2(imgConvLy.at(i).at<float>(h, w), imgConvLx.at(i).at<float>(h, w));
        // orientation = atan(imgConvLy.at(i).at<float>(h, w)/imgConvLx.at(i).at<float>(h, w));

        for(int j=0; j<minOrientations.size(); j++)
        {
          // ROS_WARN_STREAM("Updating scale " << i << " h "<< h << " w " << w << " val " << scaledVal << " orientation is " << orientation);
          //if ((fabs(scaledVal) > fabs(cvmGet(maxResponse[j], h, w))) && (fabs(orientation) >= minOrientation[j]) && (fabs(orientation) < maxOrientation[j]))
          if (fabs(scaledVal) > fabs(maxResponses.at(j).at<float>(h, w)))
          {
            if(fabs(orientation) >= fabs(minOrientations.at(j)) && fabs(orientation) < fabs(maxOrientations.at(j)))
            {
              maxResponses.at(j).at<float>(h, w) = scaledVal;
            }
            else
            {
              // ROS_ERROR_STREAM("!!! orientation doesnt fit " << orientation << " min " << minOrientations.at(j) << " max " << maxOrientations.at(j));
            }
          }
        }
      }
    }
  }
  ROS_WARN("DONE3");

  for (int i = 0; i < MAX_FEATURES; i++)
  {
    // edgeTracker_->rawBlobs_[i].Reset();
    // edgeTracker_->filters_[i].measured_.Reset();
  }
  ROS_WARN_STREAM("Done4-1");
  for(int i = 0; i < minOrientations.size(); i++)
  {
    cv::imshow("EdgeTracker"+std::to_string(i), maxResponses.at(i));
    cv::waitKey(10);
  }
  cv::waitKey(0);

  cc_image.setTo(cv::Scalar::all(0));
  copy_image.setTo(cv::Scalar::all(0));
  ROS_WARN_STREAM("Done4-2");

  normalize(edge, cedge, edge_thresh, 255);

  // ROS_WARN_STREAM("Length" << len);


  // f_.feature_tag_pub_.publish(features);

  // ROS_WARN_STREAM("RETURNING EDGE");
}

std::vector<SearchGoal> EdgeTracker::Search(cv::Mat input_image)
{
  convertTime = ros::Time(0);
  cv::Mat gray_image = cv::Mat::zeros(input_image.rows, input_image.cols, CV_32FC1);
  cvtColor(input_image, gray_image, CV_BGR2GRAY);
  gray_image.convertTo(gray_image, CV_32FC1);


  std::vector<SearchGoal> r;
  r.clear();
  ROS_WARN_STREAM("CALLING EDGE RESPONSE");
  getEdgeResponse(gray_image);


  return r;

 }

 cv::Mat EdgeTracker::Visualize(cv::Mat input_image, std::vector<SearchGoal> s)
 {
   cv::Mat annotated = input_image.clone();
   for(int i =0; i < s.size(); i++)
   {
     line( annotated, cv::Point(s.at(i).x_i1, s.at(i).y_i1),
     cv::Point(s.at(i).x_i2, s.at(i).y_i2), cv::Scalar(0,0,255),  1, 8 );
     // cv::circle( annotated, cv::Point(s.at(i).x_i, s.at(i).y_i), 5,  cv::Scalar(0, 0, 255), 2, 8, 0 );

   }
   return annotated;
 }

// First Derivative
void EdgeTracker::getGausDerX(int size, double sigma, Eigen::MatrixXf &result)
{
  Eigen::MatrixXf x, y;
  initializeFilter(size, x, y);

 Eigen::MatrixXf temp1(size, size);
 Eigen::MatrixXf temp2(size, size);
 Eigen::MatrixXf temp3(size, size);

 temp1 = x.cwiseProduct(x);
 temp1 = temp1 * (-1.0 / (2.0 * pow(sigma, 2.0)));
 temp1 = temp1.unaryExpr<float(*)(float)>(&std::exp);

 temp2 = y.cwiseProduct(y);
 temp2 = temp2 * (-1.0 / (2.0 * pow(sigma, 2.0)));
 temp2 = temp2.unaryExpr<float(*)(float)>(&std::exp);

 temp3 = temp1.cwiseProduct(temp2);
 result = x.cwiseProduct(temp3);
 result = result * (-1.0 / (2.0 * CV_PI * pow(sigma, 4.0)));
}

void EdgeTracker::getGausDerY(int size, double sigma, Eigen::MatrixXf &result)
{
  Eigen::MatrixXf x, y;
  initializeFilter(size, x, y);


  Eigen::MatrixXf temp1(size, size);
  Eigen::MatrixXf temp2(size, size);
  Eigen::MatrixXf temp3(size, size);

  temp1 = x.cwiseProduct(x);
  temp1 = temp1 * (-1.0 / (2.0 * pow(sigma, 2.0)));
  temp1 = temp1.unaryExpr<float(*)(float)>(&std::exp);

  temp2 = y.cwiseProduct(y);
  temp2 = temp2 * (-1.0 / (2.0 * pow(sigma, 2.0)));
  temp2 = temp2.unaryExpr<float(*)(float)>(&std::exp);

  temp3 = temp1.cwiseProduct(temp2);
  result = y.cwiseProduct(temp3);
  result = result * (-1.0 / (2.0 * CV_PI * pow(sigma, 4.0)));
}

void EdgeTracker::normalize(cv::Mat &edgeResponse, cv::Mat &response, int lowestResponse, int highestResponse)
{
  std::vector<double> minval, maxval;
  minval.resize(minOrientations.size());
  maxval.resize(minOrientations.size());

  double min_, max_;
  int val;
  double absmax;
  double cov[4];

  // features.num = 0;
  numFeatures = 0;
  ROS_WARN_STREAM("Done4-5");
  edgeResponse.setTo(cv::Scalar::all(0));
  ROS_WARN_STREAM("Done4");
  for (int i = 0; i < MAX_FEATURES; i++) {
    ccMeans[i][0] = 0;
    ccMeans[i][1] = 0;
    ccPointsLen[i] = 0;

  }
  // for (int i = 0; i < MAX_FEATURES; i++)
  // {
  //   edgeTracker_->rawBlobs_[i].Reset();
  //   edgeTracker_->filters_[i].measured_.Reset();
  // }

  for(int i=0; i<minOrientations.size(); i++)
  {
    cv::minMaxLoc(maxResponses.at(i), &min_, &max_);
    minval.at(i) = min_;
    maxval.at(i) = max_;
    ROS_INFO_STREAM("Minmax for i " << i);
    ROS_INFO_STREAM("\tMin " << minval.at(i));
    ROS_INFO_STREAM("\tMax " << maxval.at(i));

    ROS_ERROR_STREAM("MaxResponse_ max" << maxval.at(i) << " min " << minval.at(i));
    // minval.at(i) = std::abs(minval.at(i));
    // maxval.at(i) = std::abs(maxval.at(i));
    // float old_range = maxval.at(i) - minval.at(i);
    // float new_range = 255-0;
    // if (maxval.at(i) > 0)
    // {
    //   for (int h = 0; h < maxResponses.at(i).size().height; h++)
    //   {
    //     for (int w = 0; w < maxResponses.at(i).size().width; w++)
    //     {
    //       maxResponses.at(i).at <float> (h,w) = ((maxResponses.at(i).at<float>(h,w) - minval.at(i)) * new_range / old_range);
    //     }
    //   }
    //   maxResponses.at(i).convertTo(maxResponses.at(i), CV_32FC1);
    // }
    // cv::imshow("EdgeTracker"+std::to_string(i), maxResponses.at(i));
    // cv::waitKey(10);
    // cv::minMaxLoc(maxResponses.at(i), &minval.at(i), &maxval.at(i));
    // ROS_ERROR_STREAM("MaxResponse_2 max" << maxval.at(i) << " min " << minval.at(i));
  }


  // cv::waitKey(0);
  int numPoints;
  ROS_WARN_STREAM("Done5");

  for(int k=0; k<minOrientations.size(); k++)
  {
    int numPoints = 0;
    response.setTo(cv::Scalar::all(0));;
    numPoints = 0;
    ROS_WARN_STREAM("Done5-" <<k);
    if(minval.at(k) > maxval.at(k)) {
      absmax = minval.at(k);
    } else {
      absmax = maxval.at(k);
    }
    if(absmax == 0)
      continue;
    // cv::inRange(maxResponses.at(k), cv::Scalar(lowestResponse),cv::Scalar(highestResponse), response);
    ROS_WARN_STREAM("Done6");
    for(int i = 0; i < maxResponses.at(k).rows; i++)
    for (int j = 0; j < maxResponses.at(k).cols; j++)
    {
      val = (int)(minval.at(k) + abs(maxResponses.at(k).at<float> (i, j)) * (maxval.at(k) - minval.at(k)) / absmax);
      // ROS_WARN_STREAM("i " << i << " j " << j << " response " <<maxResponses.at(k).at<float>(i, j)  << " val " << val << " highestResponse " << highestResponse << " lowestResponse" << lowestResponse);

      if (val <= highestResponse && val >= lowestResponse)
      {
        response.at<float>(i, j) = marked;
        edgeResponse.at<cv::Vec3b>(cv::Point(i, j)) = color.at(k);
        numPoints++;
      }
      else
      {
        response.at<float>(i, j) = unmarked;
      }
    }
    ROS_WARN("LEAVING");
    cv::imshow("TestImage"+std::to_string(k), response);
    cv::waitKey(0);
    ROS_WARN_STREAM("Done7");
    //	printf("Number of points : %d\n", numPoints);
    // double kernelSize = 2.0 * blurKernel + 1.0;
    // double sigma = 0.3 * ((kernelSize/2.0) - 1.0) + 0.8;
    // cv::GaussianBlur(response, blurred_image, cv::Size(kernelSize, kernelSize), sigma);
    // // cvSmooth(&response, &blurred_image, CV_GAUSSIAN, 2 * blurKernel + 1, 0, 0);
    // ROS_WARN_STREAM("Done7-1");
    // cv::imshow("EdgeTrackerBlur", blurred_image);
    // cv::waitKey(0);
    // // cvThreshold(&blurred_image, &temp_blurred_image, 50, 255,
    // //   CV_THRESH_BINARY);
    // cv::threshold(blurred_image, temp_blurred_image, 50, 255, CV_THRESH_BINARY);
    // ROS_WARN_STREAM("Done7-2");
    // temp_blurred_image.convertTo(response, CV_32FC1);
    // cv::imshow("TestImage"+std::to_string(k), response);
    // cv::waitKey(0);
    ROS_WARN_STREAM("Done8");
    // continue;
    if(false)//numPoints > min_point_thresh)
    {
      //Find Connected Components
      getConnectedComponents(response,k);
      //   printf("Number of connected components----> : %d \n", numCC);
      // for (int i = 0; i < numCC; i++) {
        // CvScalar colors = CV_RGB((int) COLOR_LEGENDS[i][0],
        //			       (int) COLOR_LEGENDS[i][1], (int) COLOR_LEGENDS[i][2]);
        // cvDrawContours(cc_image, ccs[i].contour, colors, colors, 0, -1, 0);//2,1,8
        //cvDrawContours(copy_image, ccs[i].contour, color[k], color[k], 0, -1, 0);
        //color.Dispose();
      // }
    }
  }
  ROS_WARN_STREAM("Done9");

  char name[100];
  sprintf(name, "NO_FEATURE");
  for (int k = numFeatures; k < MAX_FEATURES; k++)
  {
    cov[0] = 1; cov[1] = 0; cov[2] = 0; cov[3] = 1;
    //set the other features invalid
    // edgeTracker_->AddNewMeasurement(-1, -1, cov, k, name, -1);
  }
    //printf("==========================\n");
    // edgeTracker_->MatchRawDataToEstimates(false, numFeatures);

    //GetCVNormalize(maxResponse[index].mat, min, max, minval, maxval, highestResponse, lowestResponse, response);
}

void EdgeTracker::getConnectedComponents(cv::Mat &back_img, int k) {
  std::vector<std::vector<cv::Point> > contours;
  std::vector<std::vector<cv::Point> > contours_poly;
  std::vector<cv::Vec4i> hierarchy;
  ROS_WARN_STREAM("DONE8-1");
  ROS_WARN_STREAM("DONE8-2");
  cv::findContours(back_img, contours, hierarchy,
      CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);
    ROS_WARN_STREAM("DONE8-3");

  if (contours.size()>0) {
    ROS_WARN_STREAM("DONE8-3-1");
    contours_poly.resize(contours.size());
    for(int i=0; i < contours.size(); i++)
    {
        cv::approxPolyDP(contours.at(i), contours_poly.at(i), 3, 0);
    }

    ROS_WARN_STREAM("DONE8-4");

    int numCC = getThresholdConnectedComponents(contours_poly, k);
    ROS_WARN_STREAM("DONE8-5 " << numCC);

    //Limit in blobs
    numCC = numCC < MAX_FEATURES ? numCC : MAX_FEATURES;
    ROS_WARN_STREAM("DONE8-6 " << numCC);

  }
  ROS_WARN_STREAM("DONE8-7");

  //  printf("Number of connected components : %d \n", numCC);
  //delete contours;
}


int EdgeTracker::getThresholdConnectedComponents(std::vector<std::vector<cv::Point> > contours, int k)
{

  int count = 0;
  double area;
  double perimeter;
  CvBox2D box;
  // int i=-1;
  int numPoints;
  double  cov[4];
  double a, b;
  CvPoint means;
  double length;

  // CvPoint* r;
  std::vector<cv::Point> startPoints, endPoints;
  //    while (contours != NULL && count < numComponents) {
  for(int i = 0; i < contours.size(); i++ )
  {
    length = cv::arcLength(contours.at(i), 0);
    //	printf("Contour length : %f \n", length);
    //  printf("Number of contours : %d \n", contours->total-1);
    //for ( int m = 0; m<=contours->total-1; m++ )
    //{
    //printf("Number of contours ---> : %d , %d\n", contours->total-1,m);
    //	i++;
    numPoints=0;
    means.x=0; means.y=0;
    cov[0] = 0;	cov[1] = 0;	cov[2] = 0;	cov[3] = 0;
    area =  fabs(cv::contourArea(contours.at(i)));
    //	perimeter = cvContourPerimeter(contours);
    //	printf("area : %f perimeter : %f\n",area,perimeter);
    if (length > mincc_thresh)
    {
      // ccs[count].area = area;
      //  ccs[count].contour = contours;
      count++;
      //	  printf("In here\n");

      //CvSeq* r = *(CvSeq**)cvGetSeqElem( contours,0);
      //	  printf("Hello : -----> %d\n",c->total);
      for ( int j = 0; j < contours.at(i).size(); j++ )
      {

        //   printf("Hello : %d\n",j);
        cv::Point pt = contours.at(i).at(j);
        //   printf(" (%d,%d)\n", pt->x, pt->y );

        means.x += pt.x; means.y += pt.y;
        numPoints++;
        //j++;
      }
      // printf("Num of points : %d\n",numPoints);
      if(numPoints != 0)
      {
        means.x /= numPoints; means.y /= numPoints;
        //	box = cvFitEllipse2(r);

        for ( int j = 0; j < contours.at(i).size(); j++ )
        {
          cv::Point pt = contours.at(i).at(j);
          a = pt.x - means.x;
          b = pt.y - means.y;

          cov[0] = cov[0] + (a * a);
          cov[1] = cov[1] + (a * b);
          cov[2] = cov[2] + (b * a);
          cov[3] = cov[3] + (b * b);
        }
        for (int j = 0; j < 4; j++)
        {
          cov[j] = cov[j] / (double) (numPoints);
        }

        /*  if(saveData == true)
        {
          fprintf(fp,"%d ",k);
          fprintf(fp,"%d %d ",means.x, means.y);
          fprintf(fp,"%f %f %f %f\n",cov[0],cov[1],cov[2],cov[3]);
        }*/

        char name[100];
        sprintf(name, "ORIENTED_EDGES_%d",k);
        // edgeTracker_->AddNewMeasurement(means.x, means.y, cov, numFeatures,name, k);
        numFeatures++;
        startPoints.push_back(contours.at(i).at(0));
        endPoints.push_back(contours.at(i).at(contours.at(i).size() - 1));
      }
    }
    visual_feature_server::Convert2DPoint::Response res1;
    visual_feature_server::Convert2DPoint::Response res2;
    if(f_.convert(startPoints, convertTime, res1) &&
                    f_.convert(endPoints, convertTime, res2))
    {
      visual_feature_server::FeaturePoses features;
      for(int i = 0; i < startPoints.size(); i++)
      {

        visual_feature_server::FeatureMsg msg;
        msg.name = visual_feature_server::FeatureMsg::EDGE_STR;
        msg.type = visual_feature_server::FeatureMsg::EDGE;
        msg.image_scale = f_.scale;

        double d = sqrt((((res1.x_dest.at(i) + res2.x_dest.at(i))/2)*((res1.x_dest.at(i) + res2.x_dest.at(i))/2))
                      + (((res1.y_dest.at(i) + res2.y_dest.at(i))/2)*((res1.y_dest.at(i) + res2.y_dest.at(i))/2))
                      + (((res1.z_dest.at(i) + res2.z_dest.at(i))/2)*((res1.z_dest.at(i) + res2.z_dest.at(i))/2)));
        double world_scale = sqrt(2*f_.scale)*d/FOCAL_LENGTH;
        msg.world_scale = world_scale;

        msg.edgeFeature.threshold = f_.threshold;
        msg.edgeFeature.centroid.header.stamp = convertTime;
        msg.edgeFeature.centroid.header.frame_id = "/world";
        msg.edgeFeature.centroid.pose.pose.position.x = (res1.x_dest.at(i) + res2.x_dest.at(i))/2;
        msg.edgeFeature.centroid.pose.pose.position.y = (res1.y_dest.at(i) + res2.y_dest.at(i))/2;
        msg.edgeFeature.centroid.pose.pose.position.z = (res1.z_dest.at(i) + res2.z_dest.at(i))/2;
        geometry_msgs::PoseWithCovariance::_covariance_type cov;
        f_.populateCovariance(cov);
        msg.edgeFeature.centroid.pose.covariance = cov;

        features.features.push_back(msg);
        f_.feature_tag_pub_.publish(features);
        SearchGoal s;
        s.image_scale = f_.scale;
        s.world_scale = world_scale;
        s.x_i = (startPoints.at(i).x + endPoints.at(i).x)/2;
        s.y_i = (startPoints.at(i).y + endPoints.at(i).y)/2;
        s.x_w = (res1.x_dest.at(i) + res2.x_dest.at(i))/2;
        s.y_w = (res1.y_dest.at(i) + res2.y_dest.at(i))/2;
        s.z_w = (res1.z_dest.at(i) + res2.z_dest.at(i))/2;

        s.x_i1 = startPoints.at(i).x;
        s.y_i1 = startPoints.at(i).y;
        s.x_i2 = endPoints.at(i).x;
        s.y_i2 = endPoints.at(i).y;

        s.x_w1 = res1.x_dest.at(i);
        s.y_w1 = res1.y_dest.at(i);
        s.z_w1 = res1.z_dest.at(i);

        s.x_w2 = res2.x_dest.at(i);
        s.y_w2 = res2.y_dest.at(i);
        s.z_w2 = res2.z_dest.at(i);

        r.push_back(s);
      }
    }
  //	contours = contours->h_next; //next contour
  }
  return count;
}

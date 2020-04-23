#include <visual_feature_server/trackers/tracker.h>

Tracker::Tracker(Feature f, std::vector<double> s):ftracker_(f)
{
  scales = s;
  // number_of_scales = num_scales;
  // number_of_orientations = num_orientations;
  ROS_WARN_STREAM("Tracker constructor done");

}

Tracker::~Tracker(){}

void Tracker::init()
{
  blurredImage = cv::Mat::zeros( cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT), CV_32FC3 );

  ROS_WARN_STREAM("Tracker constructor orientation done");

  // scales.resize(number_of_scales);
  sigmas.resize(scales.size());
  sizes.resize(scales.size());
  weights.resize(scales.size());
  filterX.resize(scales.size());
  filterY.resize(scales.size());
  imgConvLx.resize(scales.size());
  imgConvLy.resize(scales.size());
  responses.resize(scales.size());
  for(int i = 0; i < scales.size(); i++)
  {
    sigmas.at(i) = sqrt(scales.at(i));
    sizes.at(i) = getFilterSize(sigmas.at(i));
    // weights.at(i) = pow(scales.at(i), weight_scale_factor);
    filterX.at(i) = cv::Mat::zeros(sizes.at(i), sizes.at(i), CV_32FC1);
    filterY.at(i) = cv::Mat::zeros(sizes.at(i), sizes.at(i), CV_32FC1);
    getGxFilter(filterX.at(i), sigmas.at(i));
    getGyFilter(filterY.at(i), sigmas.at(i));
    double minval, maxval;
    cv::minMaxLoc(filterX.at(i), &minval, &maxval);
    double sumX = cv::sum(filterX.at(i))[0];
    ROS_ERROR_STREAM("For filterX i=" << i << " min " << minval<< " max " << maxval << "total " << sumX);

    cv::minMaxLoc(filterY.at(i), &minval, &maxval);
    double sumY = cv::sum(filterY.at(i))[0];
    ROS_ERROR_STREAM("For filterY i=" << i << " min " << minval<< " max " << maxval<< "total " << sumY);

    imgConvLx.at(i) = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH,CV_32FC1);
    imgConvLy.at(i) = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH,CV_32FC1);
    responses.at(i) = cv::Mat::zeros(IMAGE_HEIGHT, IMAGE_WIDTH,CV_32FC1);
  }
  ROS_WARN_STREAM("Tracker constructor scale done");

}
void Tracker::blurImage(cv::Mat& input_image)
{
  if(input_image.rows <= 0 || input_image.cols <=0)
    return;
  ROS_WARN_STREAM("ftracker_.scale " << ftracker_.scale);
  cv::GaussianBlur(input_image,blurredImage,
    cv::Size(ftracker_.scale,ftracker_.scale), ftracker_.scale/3.0);
}

void Tracker::getGxFilter(cv::Mat& filter, double sigma)
{
  int size = getFilterSize(sigma);

  Eigen::MatrixXf Mresult(size, size);
  ROS_WARN_STREAM("CALLING filterX");
  getGausDerX(size, sigma, Mresult);
  ROS_WARN_STREAM("CALLED filterX");

  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      filter.at<float>(i, j) = Mresult(i,j);
    }
  }
}

void Tracker::getGyFilter(cv::Mat& filter, double sigma)
{
  int size = getFilterSize(sigma);

  Eigen::MatrixXf Mresult(size, size);

  getGausDerY(size, sigma, Mresult);

  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      filter.at<float>(i, j) = Mresult(i,j);
    }
  }
}


int Tracker::getFilterSize(double sigma)
{
  int tempSize = ceil(5.0 * sigma);
  if(tempSize %2 == 0)
  {
    tempSize +=1;
  }

  return tempSize;
}

void Tracker::initializeFilter(int size, Eigen::MatrixXf& x, Eigen::MatrixXf& y )
{
  x = Eigen::MatrixXf(size,size);
  y = Eigen::MatrixXf(size,size);

  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      x(i,j) = (j-((size-1.0)/2.0));
      y(i,j) = (i-((size-1.0)/2.0));
    }
  }
}


void Tracker::convolve(cv::Mat input, cv::Mat filter, cv::Mat &output)
{
  for (int i = 0-(filter.rows/2); i < input.rows - (filter.rows/2); i++)
  {
      for (int j = 0-(filter.cols/2); j < input.cols - (filter.cols/2); j++)
      {  //adding k and l to i and j will make up the difference and allow us to process the whole image
          float filtertotal = 0;
          for (int k = 0; k < filter.rows; k++)
          {
              for (int l = 0; l < filter.rows; l++)
              {
                  if(i+k >= 0 && i+k < input.rows && j+l >= 0 && j+l < input.cols)
                  {  //don't try to process pixels off the endge of the map
                      float a = input.at<float>(i+k,j+l);
                      float b = filter.at<float>(k,l);
                      float product = a * b;
                      filtertotal += product;
                      // ROS_INFO_STREAM("\ta " << a << " b " << b << " Product " << product << " filter total" << filtertotal);
                  }
              }
          }
          //filter all proccessed for this pixel, write it to dst
          output.at<float>(i+(filter.rows/2),j+(filter.cols/2)) = fabs(filtertotal);

      }
  }
}

#ifndef MAP_ALIGN_H
#define MAP_ALIGN_H

#include <opencv4/opencv2/opencv.hpp>
// #include <opencv4/opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void SIFT(string im1_str, string im2_str)
{
    Mat im1 = imread("/home/dpark/map-fusion/map_data/img01_nonoise.jpg");
    namedWindow("Image Window", WINDOW_AUTOSIZE);
    imshow("Image Window", im1);
    // waitKey();
    // cv::Mat im1 = cv::imread(im1_str.c_str(), cv::IMREAD_GRAYSCALE);
    // cv::Mat im2 = cv::imread(im2_str.c_str(), cv::IMREAD_GRAYSCALE);
}


#endif
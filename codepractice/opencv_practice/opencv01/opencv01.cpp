#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/rapid.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    cv::String im1_name("/home/dpark/map-fusion/codepractice/opencv_practice/img01_nonoise.jpg");
    cv::String im2_name("/home/dpark/map-fusion/codepractice/opencv_practice/img02_nonoise.jpg");

    cv::Mat im1, im2, im3;
    im1 = imread( samples::findFile(im1_name), IMREAD_COLOR);
    im2 = imread( samples::findFile(im2_name), IMREAD_COLOR);


    cv::rapid::findCorrespondencies(im1, im2, im3);


    cv::namedWindow("Display Window", WINDOW_NORMAL);
    cv::resizeWindow("Display Window", 2560, 1440);
    cv::imshow("Display Window", im1);


    cv::waitKey(0);
    return 0;
}
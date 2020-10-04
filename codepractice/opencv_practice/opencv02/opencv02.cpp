#include <iostream>
#include <core.hpp>
#include <imgcodecs.hpp>
#include <highgui.hpp>
#include <rapid.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    cv::String dir = "/home/dpark/map-fusion/codepractice/opencv_practice/mapping_result_data/";
    cv::String im1_name(dir + "robot_frame_0_0_0.txt.jpg");
    cv::String im2_name(dir + "robot_frame_0_0_15.txt.jpg");
    // cv::String im1_name("/home/dpark/map-fusion/codepractice/opencv_practice/img01_nonoise.jpg");
    // cv::String im2_name("/home/dpark/map-fusion/codepractice/opencv_practice/img02_nonoise.jpg");

    cv::Mat im1, im2, im3;
    im1 = imread( samples::findFile(im1_name), IMREAD_COLOR);
    im2 = imread( samples::findFile(im2_name), IMREAD_COLOR);


    // cv::rapid::findCorrespondencies(im1, im2, im3);


    cv::namedWindow("Display Window", WINDOW_NORMAL);
    cv::resizeWindow("Display Window", 2560, 1440);
    cv::imshow("Display Window", im1);
    cv::waitKey(0);
    cv::imshow("Display Window", im2);
    cv::waitKey(0);

    return 0;
}
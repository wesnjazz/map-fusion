#ifndef MAP_ALIGN_H
#define MAP_ALIGN_H

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
// #include <opencv4/opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


Mat concatenate_two_images_adjacent_horizontal(Mat &im1, Mat&im2)
{
    int im1_w = im1.size().width;
    int im1_h = im1.size().height;
    int im2_w = im2.size().width;
    int im2_h = im2.size().height;
    Mat im_matches;
    // Mat left(im_matches, Rect(0, 0, im1_w, im1_h)); // Copy constructor
    // im1.copyTo(left);
    // Mat right(im_matches, Rect(im1_w, 0, im2_w, im2_h)); // Copy constructor
    // im2.copyTo(right);

    hconcat(im1, im2, im_matches);

    return im_matches;
}


void display_im(string window_name, Mat &im)
{
    namedWindow(window_name, WINDOW_NORMAL);
    resizeWindow(window_name, 2560, 1440);
    imshow(window_name, im);
    waitKey();
    destroyWindow(window_name);
}


void SIFT(cv::Mat &im1, cv::Mat im2)
{
    Mat im1_gray;
    cvtColor(im1, im1_gray, cv::COLOR_BGR2GRAY);
    
    namedWindow("Image Window", WINDOW_AUTOSIZE);
    imshow("Image Window", im1);
    // waitKey();
    // cv::Mat im1 = cv::imread(im1_str.c_str(), cv::IMREAD_GRAYSCALE);
    // cv::Mat im2 = cv::imread(im2_str.c_str(), cv::IMREAD_GRAYSCALE);
}


void CannyEdge(Mat &im1, Mat im2)
{
    Mat im1_gray;
    cvtColor(im1, im1_gray, cv::COLOR_BGR2GRAY);

    int min_val, max_val, aperture_size;
    cout
        << "Canny Edge" << endl
        << "min_val: ";
    cin >> min_val;
    cout
        << "Canny Edge" << endl
        << "max_val: ";
    cin >> max_val;
    cout
        << "Canny Edge" << endl
        << "aperture_size(3-7): ";
    cin >> aperture_size;

    Mat im_result;
    Canny(im1_gray, im_result, min_val, max_val, aperture_size, false);

    Mat concat_im;
    concat_im = concatenate_two_images_adjacent_horizontal(im1_gray, im_result);
    display_im("im_result_window", concat_im);
}



#endif
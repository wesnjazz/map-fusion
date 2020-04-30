#ifndef MAP_ALIGN_H
#define MAP_ALIGN_H

#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv::xfeatures2d;

cv::Mat concatenate_two_images_adjacent_horizontal(cv::Mat &im1, cv::Mat&im2)
{
    int im1_w = im1.size().width;
    int im1_h = im1.size().height;
    int im2_w = im2.size().width;
    int im2_h = im2.size().height;
    cv::Mat im_matches;
    hconcat(im1, im2, im_matches);
    return im_matches;
}


void display(string window_name, cv::Mat &im)
{
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::resizeWindow(window_name, 2560, 1440);
    cv::imshow(window_name, im);
    cv::waitKey();
    cv::destroyWindow(window_name);
}


void display_imorigin_imconvoluted_adj_horizontal(cv::Mat &im_original, cv::Mat &im_convoluted)
{
    cv::Mat concat_im;
    concat_im = concatenate_two_images_adjacent_horizontal(im_original, im_convoluted);
    display("im_result_window", concat_im);
}


void mySIFT(cv::Mat &im)
{
    cv::Mat im_gray;
    cvtColor(im, im_gray, cv::COLOR_BGR2GRAY);

    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
    vector<cv::KeyPoint> kp;
    sift->detect(im_gray, kp);

    cv::Mat im_result;
    drawKeypoints(im_gray, kp, im_result);

    display_imorigin_imconvoluted_adj_horizontal(im, im_result);
}


void CannyEdge(cv::Mat &im)
{
    cv::Mat im_gray;
    cvtColor(im, im_gray, cv::COLOR_BGR2GRAY);

    int min_val, max_val, aperture_size;
    cout
        << "Canny Edge" << endl
        << "min_val(default=200): ";
    cin >> min_val;
    cout
        << "Canny Edge" << endl
        << "max_val(default=300): ";
    cin >> max_val;
    cout
        << "Canny Edge" << endl
        << "aperture_size(3-7): ";
    cin >> aperture_size;

    cv::Mat im_result;
    Canny(im_gray, im_result, min_val, max_val, aperture_size, false);

    display_imorigin_imconvoluted_adj_horizontal(im_gray, im_result);
}


void SimpleBlob(cv::Mat &im)
{
    cv::Mat im_gray;
    cvtColor(im, im_gray, cv::COLOR_BGR2GRAY);

    cv::SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 0.001;
    params.maxArea = 10000;
    params.filterByCircularity = true;

	params.minThreshold = 10;
	params.maxThreshold = 200;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 1500;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1;

	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;

    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

    // Ptr<SimpleBlobDetector> blob = SimpleBlobDetector::create(params);
    // vector<KeyPoint> kp;
    // blob->detect(im_gray, kp);

    // Mat img_keypoints;
    // drawKeypoints(im_gray, kp, img_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //-- Step 1: Detect the keypoints using SURF Detector
    // int minHessian = 400;
    // Ptr<SURF> detector = SURF::create( minHessian );
    std::vector<cv::KeyPoint> keypoints;
    detector->detect( im_gray, keypoints );
    //-- Draw keypoints
    cv::Mat img_keypoints;
    drawKeypoints( im_gray, keypoints, img_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );



    
    // imshow("keypoints", img_keypoints);
    // waitKey(0);
    display_imorigin_imconvoluted_adj_horizontal(im, img_keypoints);
}



#endif
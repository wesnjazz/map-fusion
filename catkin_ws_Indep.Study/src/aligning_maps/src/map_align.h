#ifndef MAP_ALIGN_H
#define MAP_ALIGN_H

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include <opencv4/opencv2/xfeatures2d.hpp>
// #include <opencv4/opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

Mat concatenate_two_images_adjacent_horizontal(Mat &im1, Mat&im2)
{
    int im1_w = im1.size().width;
    int im1_h = im1.size().height;
    int im2_w = im2.size().width;
    int im2_h = im2.size().height;
    Mat im_matches;
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


void display_imorigin_imconvoluted_adj_horizontal(Mat &im_original, Mat &im_convoluted)
{
    Mat concat_im;
    concat_im = concatenate_two_images_adjacent_horizontal(im_original, im_convoluted);
    display_im("im_result_window", concat_im);
}


void SIFT(cv::Mat &im)
{
    Mat im_gray;
    cvtColor(im, im_gray, cv::COLOR_BGR2GRAY);

    Ptr<xfeatures2d::SIFT> sift = xfeatures2d::SIFT::create();
    vector<KeyPoint> kp;
    sift->detect(im_gray, kp);

    Mat im_result;
    drawKeypoints(im_gray, kp, im_result);

    display_imorigin_imconvoluted_adj_horizontal(im, im_result);
}


void CannyEdge(Mat &im)
{
    Mat im_gray;
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

    Mat im_result;
    Canny(im_gray, im_result, min_val, max_val, aperture_size, false);

    display_imorigin_imconvoluted_adj_horizontal(im_gray, im_result);
}


void SimpleBlob(cv::Mat &im)
{
    Mat im_gray;
    cvtColor(im, im_gray, cv::COLOR_BGR2GRAY);

    SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 1;
    params.maxArea = 10000;
    params.filterByCircularity = true;
    // params.filterByConvexity = true;
    // params.filterByInertia = true;
    // params.filterByColor = true;
    // params.blobColor = 255;

    // // Change thresholds
    // params.minThreshold = 10;
    // params.maxThreshold = 200;

    // // Filter by Area.
    // params.filterByArea = true;
    // params.minArea = 1500;

    // // Filter by Circularity
    // params.filterByCircularity = true;
    // params.minCircularity = 0.1;

    // // Filter by Convexity
    // params.filterByConvexity = true;
    // params.minConvexity = 0.87;

    // // Filter by Inertia
    // params.filterByInertia = true;
    // params.minInertiaRatio = 0.01;

    // Ptr<SimpleBlobDetector> blob = SimpleBlobDetector::create(params);
    // vector<KeyPoint> kp;
    // blob->detect(im_gray, kp);

    // Mat img_keypoints;
    // drawKeypoints(im_gray, kp, img_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create( minHessian );
    std::vector<KeyPoint> keypoints;
    detector->detect( im_gray, keypoints );
    //-- Draw keypoints
    Mat img_keypoints;
    drawKeypoints( im_gray, keypoints, img_keypoints );


    // imshow("keypoints", img_keypoints);
    // waitKey(0);
    display_imorigin_imconvoluted_adj_horizontal(im, img_keypoints);
}



#endif
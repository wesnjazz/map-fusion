#include <iostream>
#include <core.hpp>
#include <imgcodecs.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
// #include <rapid.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{


    // cv::String dir = "/home/dpark/map-fusion/imgs/examples/";
    cv::String dir = "/home/dpark/map-fusion/imgs/mapping_result_data/";
    // cv::String im1_name(dir + "robot01.jpg");
    // cv::String im1_name(dir + "robot_frame_0_0_0.txt.jpg");
    cv::String im1_name(dir + "robot_frame_0_0_0.txt_left.jpg");
    cv::String im2_name(dir + "robot_frame_0_0_0.txt_right.jpg");
    Mat src1 = imread( samples::findFile(im1_name), IMREAD_GRAYSCALE );
    Mat src2 = imread( samples::findFile(im2_name), IMREAD_GRAYSCALE );
    Mat dst1, dst2;

    int win_width = 2560 * 0.5;
    int win_height = 1440 * 0.5;
    namedWindow("disp", WINDOW_NORMAL);
    resizeWindow("disp", win_width, win_height);
    imshow("disp", src1);
    waitKey();
    imshow("disp", src2);
    waitKey();

    // Copy edges to the images that will display the results in BGR
    cvtColor(src1, dst1, COLOR_GRAY2BGR);
    cvtColor(src2, dst2, COLOR_GRAY2BGR);
    // Probabilistic Line Transform
    vector<Vec4i> linesP1, linesP2; // will hold the results of the detection
    HoughLinesP(src1, linesP1, 1, CV_PI/180, 10, 50, 50 ); // runs the actual detection
    HoughLinesP(src2, linesP2, 1, CV_PI/180, 10, 50, 50 ); // runs the actual detection
    // for(vector<Vec4i>::iterator it = linesP1.begin(); it != linesP1.end(); ++it) {
    //     cout << *it << endl;
    // }
    cout << "img 1's line vector<Vec4i> size: " << linesP1.size() << endl;
    cout << "img 2's line vector<Vec4i> size: " << linesP2.size() << endl;
    // Draw the lines
    for( size_t i = 0; i < linesP1.size(); i++ )
    {
        Vec4i l = linesP1[i];
        line( dst1, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
    }
    for( size_t i = 0; i < linesP2.size(); i++ )
    {
        Vec4i l = linesP2[i];
        line( dst2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
    }
    // Show results
    cv::namedWindow("src1", WINDOW_NORMAL);
    cv::namedWindow("src2", WINDOW_NORMAL);
    cv::namedWindow("Detected Lines (in red) - Probabilistic Line Transform dst1", WINDOW_NORMAL);
    cv::namedWindow("Detected Lines (in red) - Probabilistic Line Transform dst2", WINDOW_NORMAL);
    cv::resizeWindow("src1", win_width, win_height);
    cv::resizeWindow("src2", win_width, win_height);
    cv::resizeWindow("Detected Lines (in red) - Probabilistic Line Transform dst1", win_width, win_height);
    cv::resizeWindow("Detected Lines (in red) - Probabilistic Line Transform dst2", win_width, win_height);
    imshow("src1", src1);
    imshow("src2", src2);
    imshow("Detected Lines (in red) - Probabilistic Line Transform dst1", dst1);
    imshow("Detected Lines (in red) - Probabilistic Line Transform dst2", dst2);
    waitKey();
    return 0;
}
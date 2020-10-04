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
    cv::String dir = "/home/dpark/map-fusion/mapping_result_data/";
    // cv::String im1_name(dir + "robot01.jpg");
    // cv::String im1_name(dir + "robot_frame_0_0_0.txt.jpg");
    cv::String im1_name(dir + "robot_frame_0_0_15.txt.jpg");
    Mat src = imread( samples::findFile(im1_name), IMREAD_GRAYSCALE );
    Mat dst, cdst, cdstP;

    // Edge detection
    Canny(src, dst, 50, 200, 3);

    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    // Standard Hough Line Transform
    vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }
    // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI/180, 10, 5, 50 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }
    // Show results
    int win_width = 2560 * 0.9;
    int win_height = 1440 * 0.9;
    cv::namedWindow("Source", WINDOW_NORMAL);
    cv::namedWindow("Detected Lines (in red) - Standard Hough Line Transform", WINDOW_NORMAL);
    cv::namedWindow("Detected Lines (in red) - Probabilistic Line Transform", WINDOW_NORMAL);
    cv::resizeWindow("Source", win_width, win_height);
    cv::resizeWindow("Detected Lines (in red) - Standard Hough Line Transform", win_width, win_height);
    cv::resizeWindow("Detected Lines (in red) - Probabilistic Line Transform", win_width, win_height);
    imshow("Source", src);
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
    // Wait and Exit
    waitKey();
    return 0;
}
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
    Mat dst;

    // Copy edges to the images that will display the results in BGR
    cvtColor(src, dst, COLOR_GRAY2BGR);
    // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(src, linesP, 1, CV_PI/180, 10, 50, 50 ); // runs the actual detection
    for(vector<Vec4i>::iterator it = linesP.begin(); it != linesP.end(); ++it) {
        cout << *it << endl;
    }
    cout << "size: " << linesP.size() << endl;
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
    }
    // Show results
    int win_width = 2560 * 0.9;
    int win_height = 1440 * 0.9;
    cv::namedWindow("Source", WINDOW_NORMAL);
    cv::namedWindow("Detected Lines (in red) - Probabilistic Line Transform", WINDOW_NORMAL);
    cv::resizeWindow("Source", win_width, win_height);
    cv::resizeWindow("Detected Lines (in red) - Probabilistic Line Transform", win_width, win_height);
    imshow("Source", src);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", dst);
    waitKey();
    return 0;
}
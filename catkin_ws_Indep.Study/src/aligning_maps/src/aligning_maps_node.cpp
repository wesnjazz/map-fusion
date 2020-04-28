#include <iostream>
#include <fstream>
#include <ros/ros.h>
#include "map_align.h"
#include "ransac.h"
// #include "CImg.h"

using namespace std;
// using namespace cimg_library;

int main(int argc, char **argv) 
{
    /** ROS initialization **/
    ros::init(argc, argv, "Mapping_Simulator");
    ros::NodeHandle n;
    ros::Rate loop_rate(20);

    cout << "OpenCV version : " << CV_VERSION << endl;
    cout << "Major version : " << CV_MAJOR_VERSION << endl;
    cout << "Minor version : " << CV_MINOR_VERSION << endl;
    cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

    while(ros::ok())
    {
        // cv::Mat im1 = imread("/home/dpark/map-fusion/imgs/examples/butterfly01.jpg");
        // cv::Mat im1 = imread("/home/dpark/map-fusion/imgs/examples/guitar04.jpg");
        // cv::Mat im1 = imread("/home/dpark/map-fusion/imgs/examples/mountain01.jpeg");
        // cv::Mat im1 = imread("/home/dpark/map-fusion/imgs/examples/robot01.jpg");
        // cv::Mat im1 = imread("/home/dpark/map-fusion/imgs/examples/shaq01.jpg");
        // cv::Mat im1 = imread("/home/dpark/map-fusion/imgs/mapping_output/img01_nonoise.jpg");
        // cv::Mat im2 = imread("/home/dpark/map-fusion/imgs/mapping_output/img02_nonoise.jpg");
        cv::Mat im1 = cv::imread("/home/dpark/map-fusion/imgs/lsd_output/test_clean_0_0_0_a45.png");
        cv::Mat im2 = cv::imread("/home/dpark/map-fusion/imgs/lsd_output/test_clean_0_0_15_a45.png");
        ifstream lsd_txt_01 = ifstream("/home/dpark/map-fusion/imgs/lsd_output2/test_clean_0_0_0_a45.txt");
        ifstream lsd_txt_02 = ifstream("/home/dpark/map-fusion/imgs/lsd_output2/test_clean_0_0_15_a45.txt");

        cv::Mat im1_gray;
        cvtColor(im1, im1_gray, cv::COLOR_BGR2GRAY);
        cv::Mat im2_gray;
        cvtColor(im2, im2_gray, cv::COLOR_BGR2GRAY);

        int cols = 8000;
        int rows = 5000;
        cv::Mat img = cv::Mat::zeros(cols, rows, CV_8UC3);
        // CannyEdge(im1);
        // mySIFT(im1);
        // SimpleBlob(im1);
        // myGRANSAC();
        myAlign(img, lsd_txt_01, lsd_txt_02);


        cout << "Press any key to continue...";
        getchar();
        cin.clear();
        fflush(stdin);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
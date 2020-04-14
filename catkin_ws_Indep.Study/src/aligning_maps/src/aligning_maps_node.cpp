#include <iostream>
#include <fstream>
#include <ros/ros.h>
#include "map_align.h"
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
        Mat im1 = imread("/home/dpark/map-fusion/map_data/guitar04.jpg");
        // Mat im1 = imread("/home/dpark/map-fusion/map_data/mountain01.jpeg");
        // Mat im1 = imread("/home/dpark/map-fusion/map_data/robot01.jpg");
        // Mat im1 = imread("/home/dpark/map-fusion/map_data/shaq01.jpg");
        // Mat im1 = imread("/home/dpark/map-fusion/map_data/img01_nonoise.jpg");
        Mat im2 = imread("/home/dpark/map-fusion/map_data/img02_nonoise.jpg");

        Mat im1_gray;
        cvtColor(im1, im1_gray, cv::COLOR_BGR2GRAY);
        Mat im2_gray;
        cvtColor(im2, im2_gray, cv::COLOR_BGR2GRAY);


        CannyEdge(im1);
        // SIFT(im1);


        cout << "Press any key to continue...";
        getchar();
        cin.clear();
        fflush(stdin);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
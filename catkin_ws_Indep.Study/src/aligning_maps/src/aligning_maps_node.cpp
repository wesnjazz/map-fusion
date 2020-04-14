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

    ifstream image_1;
    ifstream image_2;

    while(ros::ok())
    {
        int i = 0;
        string s_img1 = "img01_nonoise.jpg";
        string s_img2 = "img02_nonoise.jpg";
        // string s_img1;
        // string s_img2;
        // cout
        //     << "Type image file names." << endl
        //     << "image [" << ++i << "]: ";
        // getline(cin, s_img1);
        // cout
        //     << "image [" << ++i << "]: ";
        // getline(cin, s_img2);



        SIFT(s_img1, s_img2);


        // CImg<unsigned char> im1(s_img1.c_str()), im2(s_img2.c_str());
        // CImgDisplay im1_disp(im1, "image 1"), im2_disp(im2, "image 2");
        // int scale = 3;
        // im1_disp.resize(im1.width() / scale, im1.height() / scale);
        // im2_disp.resize(im2.width() / scale, im2.height() / scale);

        // while(!im1_disp.is_closed() && !im2_disp.is_closed())
        // {
        //     im1_disp.wait();
        //     im2_disp.wait();
        // }





        cout << "Press any key to continue...";
        getchar();
        cin.clear();
        fflush(stdin);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
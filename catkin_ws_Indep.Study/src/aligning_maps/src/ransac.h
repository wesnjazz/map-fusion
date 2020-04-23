#ifndef RANSAC_H_
#define RANSAC_H_

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "segment.h"
#include "GRANSAC.hpp"
#include "AbstractModel.hpp"
#include "LineModel.hpp"

using namespace std;


void read_lsd(ifstream &seg_file, vector<Segment> &segments)
{
    // x1, y1, x2, y2, width, p, -log_nfa
    Vec2f p1 = Vec2f(0,0);
    Vec2f p2 = Vec2f(0,0);
    Segment seg = Segment(p1, p2);

    float x, y;
    int count = 0;
    string line;
    // cv::Point2f Pt_1;
    // cv::Point2f Pt_2;
    // std::shared_ptr<GRANSAC::AbstractParameter> CandPt = NULL;

    while(getline(seg_file, line)) {
        stringstream ss(line);
        while(getline(ss, line, ' ')) {
            count++;
            switch (count)
            {
            case 1: x = stof(line); break;
            case 2: y = stof(line); p1 = Vec2f(x, y); break;
            case 3: x = stof(line); break;
            case 4: 
                y = stof(line);
                p2 = Vec2f(x, y);
                count = 0;
                seg = Segment(p1, p2);
                segments.push_back(seg);
                break;
            default: break;
            }
            // switch (count)
            // {
            // case 1: x = stof(line); Pt_1.x = x; break;
            // case 2: y = stof(line); Pt_1.y = y;
            //     CandPt = std::make_shared<Point2D>(Pt_1.x, Pt_1.y);
            //     CandPoints.push_back(CandPt);
            //     break;
            // case 3: x = stof(line); Pt_2.x = x; break;
            // case 4: y = stof(line); Pt_2.y = y;
            //     CandPt = std::make_shared<Point2D>(Pt_2.x, Pt_2.y);
            //     CandPoints.push_back(CandPt);
            //     break;
            // case 5: break;
            // case 6: break;
            // case 7: count = 0; break;
            // default: break;
            // }
        }
        cout << "size: " << segments.size() << endl;
    }
}


// void myGRANSAC()
void myGRANSAC(ifstream &file_01, ifstream &file_02)
{
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints_01;
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints_02;
    vector<Segment> &segments_01;
    vector<Segment> &segments_02;
    read_lsd(file_01, segments_01);
    read_lsd(file_02, segments_02);
    // std::shared_ptr<GRANSAC::AbstractParameter> CandPt = std::make_shared<Point2D>
    // GRANSAC::RANSAC<Line2DModel, 2> Estimator;
}


#endif
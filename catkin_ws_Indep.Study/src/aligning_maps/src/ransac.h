#ifndef RANSAC_H_
#define RANSAC_H_

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "transformation.h"
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


vector<int> compute_matches(cv::Mat &img, vector<Segment> &seg_01, vector<Segment> &seg_02)
{
    vector<int> matches;
    for(vector<Segment>::iterator it_01 = seg_01.begin(); it_01 != seg_01.end(); ++it_01)
    {
        int index_min = 0;
        float diff = 0.0f;
        float min_diff = 9999999999.0f;

        for(vector<Segment>::iterator it_02 = seg_02.begin(); it_02 != seg_02.end(); ++it_02)
        {
            diff = fabs(it_01->length - it_02->length);
            // cout << "min_diff: " << min_diff << "\t" << "diff: " << diff << endl;
            if (diff < min_diff)
            {
                min_diff = diff; 
                index_min = it_02 - seg_02.begin();
            }
        }
        // cout << "\t\t\tmin_diff: " << min_diff << endl;
        matches.push_back(index_min);

        // cv::Mat im = cv::Mat::zeros(6000, 8500, CV_8UC3);
        // cv::Point2f p1 = cv::Point2f(it_01->start.x(), it_01->start.y());
        // cv::Point2f p2 = cv::Point2f(it_01->end.x(), it_01->end.y());
        // cv::line(im, p1, p2, cv::Scalar(0, 100, 255), 50, 8);
        // int ee = it_01 - seg_01.begin();
        // p1 = cv::Point2f(seg_02.at(ee).start.x(), seg_02.at(ee).start.y());
        // p2 = cv::Point2f(seg_02.at(ee).end.x(), seg_02.at(ee).end.y());
        // cv::line(im, p1, p2, cv::Scalar(100, 255, 0), 50, 8);
        // display_im("Result", im);
        // cout 
        //     << *it_01 << endl
        //     << seg_02.at(ee) << endl
            ;
        // getchar();
    }
    return matches;
}


            // cout 
            //         << it_01->start.x() << "/t" << it_01->start.y() << endl
            //         << it_01->end.x() << "/t" << it_01->end.y() << endl
            //         << it_02->start.x() << "/t" << it_02->start.y() << endl
            //         << it_02->end.x() << "/t" << it_02->end.y() << endl
            //         ;
            // cv::Mat im = cv::Mat::zeros(10000, 8000, CV_8UC3);
            // cv::Point2f p1 = cv::Point2f(it_01->start.x(), it_01->start.y());
            // cv::Point2f p2 = cv::Point2f(it_01->end.x(), it_01->end.y());
            // cv::line(im, p1, p2, cv::Scalar(0, 100, 255), 10, 8);
            // p1 = cv::Point2f(it_02->start.x(), it_02->start.y());
            // p2 = cv::Point2f(it_02->end.x(), it_02->end.y());
            // cv::line(im, p1, p2, cv::Scalar(100, 255, 0), 10, 8);
            // display_im("Result", im);




void myAlign(cv::Mat &img, ifstream &file_01, ifstream &file_02)
{
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints_01;
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints_02;
    vector<Segment> segments_01;
    vector<Segment> segments_02;
    read_lsd(file_01, segments_01);
    read_lsd(file_02, segments_02);

    vector<int> matches = compute_matches(img, segments_01, segments_02);
    for(vector<int>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        int idx_i = it - matches.begin();
        float seg_01_x = segments_01.at(idx_i).start.x();
        float seg_01_y = segments_01.at(idx_i).start.y();
        float seg_01_theta = segments_01.at(idx_i).angle_degree;
        float seg_02_x = segments_02.at(*it).start.x();
        float seg_02_y = segments_02.at(*it).start.y();
        float seg_02_theta = segments_02.at(*it).angle_degree;
        Vec3f seg_01_pos = Vec3f(seg_01_x, seg_01_y, seg_01_theta);
        Vec3f seg_02_pos = Vec3f(seg_02_x, seg_02_y, seg_02_theta);
        Mat3f HT = get_HT_Aframe_to_Bframe(seg_01_pos, seg_02_pos);
        cout << seg_01_pos << endl;
        cout << seg_02_pos << endl;
        cout << HT << endl;


        int x_move = 1500;
        int y_move = 1500;
        for(vector<Segment>::iterator it_seg = segments_02.begin(); it_seg != segments_02.end(); ++it_seg)
        {
            Vec2f start = it_seg->start;
            Vec3f new_start_with_dummy_1 = HT * (start.homogeneous());
            Vec2f new_start_2f = Vec2f(new_start_with_dummy_1.x(), new_start_with_dummy_1.y());
            Vec2f end = it_seg->end;
            Vec3f new_end_with_dummy_1 = HT * (end.homogeneous());
            Vec2f new_end_2f = Vec2f(new_end_with_dummy_1.x(), new_end_with_dummy_1.y());
            Segment seg_transformed = Segment(new_start_2f, new_end_2f);

        cv::Mat im = cv::Mat::zeros(6000, 8500, CV_8UC3);
        cv::Point2f seg_01_p1 = cv::Point2f(segments_01.at(idx_i).start.x() + x_move, segments_01.at(idx_i).start.y() + y_move);
        cv::Point2f seg_01_p2 = cv::Point2f(segments_01.at(idx_i).end.x()   + x_move, segments_01.at(idx_i).end.y()   + y_move);
        cv::line(im, seg_01_p1, seg_01_p2, cv::Scalar(0, 100, 255), 50, 8);
        display_im("Result", im);
        cv::Point2f seg_01_pair_p1 = cv::Point2f(segments_02.at(*it).start.x() + x_move, segments_02.at(*it).start.y() + y_move);
        cv::Point2f seg_01_pair_p2 = cv::Point2f(segments_02.at(*it).end.x()   + x_move, segments_02.at(*it).end.y()   + y_move);
        cv::line(im, seg_01_pair_p1, seg_01_pair_p2, cv::Scalar(0, 50, 255), 50, 8);
        display_im("Result", im);
        cv::Point2f seg_02_p1 = cv::Point2f(it_seg->start.x() + x_move, it_seg->start.y() + y_move);
        cv::Point2f seg_02_p2 = cv::Point2f(it_seg->end.x()   + x_move, it_seg->end.y()   + y_move);
        cv::line(im, seg_02_p1, seg_02_p2, cv::Scalar(255, 0, 100), 50, 7);
        display_im("Result", im);
        cv::Point2f seg_transformed_p1 = cv::Point2f(seg_transformed.start.x() + x_move, seg_transformed.start.y() + y_move);
        cv::Point2f seg_transformed_p2 = cv::Point2f(seg_transformed.end.x()   + x_move, seg_transformed.end.y()   + y_move);
        cv::line(im, seg_transformed_p1, seg_transformed_p2, cv::Scalar(0, 255, 10), 50, 7);
        display_im("Result", im);
        //     cv::Point2f seg_02_p1 = cv::Point2f(it_seg->start.x(), it_seg->start.y());
        //     cv::Point2f seg_02_p2 = cv::Point2f(it_seg->end.x(), it_seg->end.y());
        //     cv::line(im, seg_02_p1, seg_02_p2, cv::Scalar(0, 255, 100), 50, 8);
        //     display_im("Result", im);

        }

    }
    
    
    // compute HT between two line segment
    // HT all line segments
    // compute difference (dot product)
    // choose least difference
    // align

    // std::shared_ptr<GRANSAC::AbstractParameter> CandPt = std::make_shared<Point2D>
    // GRANSAC::RANSAC<Line2DModel, 2> Estimator;
}


#endif
#ifndef RANSAC_H_
#define RANSAC_H_

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "simulator.h"
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
                seg = Segment(p1, p2);
                segments.push_back(seg);
                break;
            case 5: break;
            case 6: break;
            case 7: count = 0; break;
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
        // display("Result", im);
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
            // display("Result", im);



void ransac_affine(cv::Mat &im, Segment &depart, Segment &arrival, cv::Mat &affine_M, cv::Mat &translate_M)
{
    float x1 = depart.start.x();
    float x1p = arrival.start.x();
    float y1 = depart.start.y();
    float y1p = arrival.start.y();
    float x3 = depart.end.x();
    float x3p = arrival.end.x();
    float y3 = depart.end.y();
    float y3p = arrival.end.y();
    float x2 = (x1 + x3) / 2.0f;
    float x2p = (x1p + x3p) / 2.0f;
    float y2 = (y1 + y3) / 2.0f;
    float y2p = (y1p + y3p) / 2.0f;

        int x_move = 0;
        int y_move = 0;
        cv::Point2f seg_A_p1 = cv::Point2f(x1 + x_move, y1 + y_move);
        cv::Point2f seg_A_prp1 = cv::Point2f(x1p + x_move, y1p + y_move);
        cv::Point2f seg_A_p2 = cv::Point2f(x2 + x_move, y2 + y_move);
        cv::Point2f seg_A_prp2 = cv::Point2f(x2p + x_move, y2p + y_move);
        cv::Point2f seg_A_p3 = cv::Point2f(x3 + x_move, y3 + y_move);
        cv::Point2f seg_A_prp3 = cv::Point2f(x3p + x_move, y3p + y_move);
        cv::line(im, seg_A_p1, seg_A_prp1, cv::Scalar(100, 255, 255), 2, 8);
        cv::line(im, seg_A_p2, seg_A_prp2, cv::Scalar(50, 205, 205), 2, 8);
        cv::line(im, seg_A_p3, seg_A_prp3, cv::Scalar(0, 155, 155), 2, 8);
        cv::circle(im, cv::Point2f(x1 + x_move, y1 + y_move), 50, cv::Scalar(255, 0, 255), 10);
        cv::circle(im, cv::Point2f(x2 + x_move, y2 + y_move), 50, cv::Scalar(155, 0, 155), 10);
        cv::circle(im, cv::Point2f(x3 + x_move, y3 + y_move), 50, cv::Scalar(55, 0, 55), 10);
        cv::circle(im, cv::Point2f(x1p + x_move, y1p + y_move), 50, cv::Scalar(50, 200, 255), 10);
        cv::circle(im, cv::Point2f(x2p + x_move, y2p + y_move), 50, cv::Scalar(20, 100, 155), 10);
        cv::circle(im, cv::Point2f(x3p + x_move, y3p + y_move), 50, cv::Scalar(0, 50, 55), 10);
        display("Result", im);

    float data[36] = { 
                        x1, y1,  0,  0,  1,  0,
                         0,  0, x1, y1,  0,  1,
                        x2, y2,  0,  0,  1,  0,
                         0,  0, x2, y2,  0,  1,
                        x3, y3,  0,  0,  1,  0,
                         0,  0, x3, y3,  0,  1
                     };
    float data2[6] = { x1p, y1p, x2p, y2p, x3p, y3p };
    cv::Mat before_M = cv::Mat(6, 6, CV_32FC1, &data);
    cv::Mat before_M_inv = before_M.inv();
    cv::Mat transformed_M = cv::Mat(6, 1, CV_32FC1, &data2);
    // trans = np.dot(np.linalg.inv(p),p_prime)
    // p   # original data
    // p_prime  # transformed data

    cv::Point2f src[3];
    cv::Point2f dst[3];
    cv::Mat rot_mat( 2, 3, CV_32FC1 );
    cv::Mat warp_mat( 2, 3, CV_32FC1 );
    cv::Mat warp_dst, warp_rotate_dst;
    warp_dst = cv::Mat::zeros(im.rows, im.cols, im.type());

    src[0] = cv::Point2f( x1, y1 );
    src[1] = cv::Point2f( x2, y2 );
    src[2] = cv::Point2f( x3, y3 );

    dst[0] = cv::Point2f( x1p, y1p );
    dst[1] = cv::Point2f( x2p, y2p );
    dst[2] = cv::Point2f( x3p, y3p );

    warp_mat = cv::getAffineTransform(src, dst);


    // cv::warpAffine(im, warp_dst, warp_mat, warp_dst.size());
    cout << "warp_mat:" << endl << warp_mat << endl << endl;
    getchar();
    // display("Result", warp_dst);





    cv::Mat parameter_M = before_M.inv() * transformed_M;
    cout << "before_M:" << endl << before_M << endl << endl;
    cout << "before_M_inv():" << endl << before_M_inv << endl << endl;
    cout << "det: " << endl << cv::determinant(before_M) << endl << endl;
    cout << "transformed_M:" << endl << transformed_M << endl << endl;
    cout << "parameter_M:" << endl << parameter_M << endl << endl;
        // cv::circle(im, cv::Point2f(transformed_M.at<float>(0,0) + x_move, transformed_M.at<float>(1,0) + y_move), 120, cv::Scalar(0, 200, 55), 10);
        // cv::circle(im, cv::Point2f(transformed_M.at<float>(2,0) + x_move, transformed_M.at<float>(3,0) + y_move), 120, cv::Scalar(0, 200, 55), 10);
        // cv::circle(im, cv::Point2f(transformed_M.at<float>(4,0) + x_move, transformed_M.at<float>(5,0) + y_move), 120, cv::Scalar(0, 200, 55), 10);
        // display("Result", im);


    float affine[4] = {
                        parameter_M.at<float>(0, 0), parameter_M.at<float>(1, 0),
                        parameter_M.at<float>(2, 0), parameter_M.at<float>(3, 0)
                      };
    cv::Mat a_M = cv::Mat(2, 2, CV_32FC1, &affine);
    float translate[2] = {
                            parameter_M.at<float>(4, 0), parameter_M.at<float>(5, 0)
                         };
    cv::Mat t_M = cv::Mat(2, 1, CV_32FC1, &translate);
    cout << "affine_M: " << endl << affine_M << endl << endl;
    cout << "translate_M: " << endl << translate_M << endl << endl;
    affine_M = a_M;
    translate_M = t_M;
}

void draw_lsd_map(cv::Mat &im, vector<Segment> &segments, cv::Scalar &color, int thickness, int type)
{
    int x_move = 0;
    int y_move = 0;
    for(vector<Segment>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        cv::Point2f p1 = cv::Point2f(it->start.x() + x_move, it->start.y() + y_move);
        cv::Point2f p2 = cv::Point2f(it->end.x()   + x_move, it->end.y()   + y_move);
        cv::line(im, p1, p2, color, thickness, type);
    }
        display("Result", im);
}

void myAlign(cv::Mat &img, ifstream &file_01, ifstream &file_02)
{
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints_01;
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints_02;

    /** Read LSD file (vector representation .esp file) 
     *  Convert vectors into Segments **/
    vector<Segment> segments_01;
    vector<Segment> segments_02;
    read_lsd(file_01, segments_01);
    read_lsd(file_02, segments_02);

    cv::Mat im_base = cv::Mat::zeros(3000, 5000, CV_8UC3);
    cv::Scalar color_r = cv::Scalar(0, 0, 255);
    cv::Scalar color_r1 = cv::Scalar(100, 100, 255);
    cv::Scalar color_r2 = cv::Scalar(200, 200, 255);
    cv::Scalar color_g = cv::Scalar(0, 255, 0);
    cv::Scalar color_b = cv::Scalar(255, 0, 0);
    cv::Scalar color_b1 = cv::Scalar(255, 100, 100);
    cv::Scalar color_b2 = cv::Scalar(255, 200, 200);
    cv::Scalar color_purple = cv::Scalar(255, 0, 255);
    cv::Scalar color_yellow = cv::Scalar(0, 255, 255);
    cv::Scalar color_orange = cv::Scalar(0, 150, 255);
    cv::Scalar color_white = cv::Scalar(255, 255, 255);
    draw_lsd_map(im_base, segments_01, color_r, 2, 1);
    draw_lsd_map(im_base, segments_02, color_b, 2, 2);

    /** Compute matches **/
    vector<int> matches = compute_matches(img, segments_01, segments_02);
    
    for(vector<int>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        // cv::Mat im_board = cv::Mat::zeros(im_base.rows, im_base.cols, im_base.type);
        cv::Mat im_board = cv::Mat::zeros(3000, 5000, CV_8UC3);
        cv::Mat im_affine = cv::Mat::zeros(3000, 5000, CV_8UC3);
        im_board += im_base;
        im_affine += im_base;
        int x_move = 0;
        int y_move = 0;
        int idx_i = it - matches.begin();
        /** seg_A : a segment
         *  seg_B : seg_A's matching segment **/
        Segment seg_A = segments_01.at(idx_i);
        Segment seg_B = segments_02.at(*it);

        // cv::Mat im = cv::Mat::zeros(6000, 8500, CV_8UC3);
        cv::Point2f seg_A_p1 = cv::Point2f(seg_A.start.x() + x_move, seg_A.start.y() + y_move);
        cv::Point2f seg_A_p2 = cv::Point2f(seg_A.end.x()   + x_move, seg_A.end.y()   + y_move);
        cv::line(im_board, seg_A_p1, seg_A_p2, color_g, 10, 3);
        cv::circle(im_board, seg_A_p1, 50, color_white, 10);
        display("Board", im_board);

        cv::Point2f seg_B_p1 = cv::Point2f(seg_B.start.x() + x_move, seg_B.start.y() + y_move);
        cv::Point2f seg_B_p2 = cv::Point2f(seg_B.end.x()   + x_move, seg_B.end.y()   + y_move);
        cv::line(im_board, seg_B_p1, seg_B_p2, color_purple, 10, 4);
        cv::circle(im_board, seg_B_p1, 50, color_white, 10);
        display("Board", im_board);


        cv::Mat affine_M = cv::Mat::zeros(2, 2, CV_32FC1);
        cv::Mat translate_M = cv::Mat::zeros(2, 1, CV_32FC1);

        ransac_affine(im_board, seg_A, seg_B, affine_M, translate_M);

        // cout << "affine_M: " << endl << affine_M << endl << endl;
        // cout << "translate_M: " << endl << translate_M << endl << endl;

        // float seg_A_x = seg_A.start.x();
        // float seg_A_y = seg_A.start.y();
        // float seg_A_theta = seg_A.angle_degree;
        // float seg_B_x = seg_B.start.x();
        // float seg_B_y = seg_B.start.y();
        // float seg_B_theta = seg_B.angle_degree;
        // Vec3f seg_A_pos = Vec3f(seg_A_x, seg_A_y, seg_A_theta);
        // Vec3f seg_B_pos = Vec3f(seg_B_x, seg_B_y, seg_B_theta);
        // Mat3f HT = get_HT_Aframe_to_Bframe(seg_A_pos, seg_B_pos);


        // cv::Point2f tf_p1 = cv::Point2f(seg_A_x + x_move, seg_A_y + y_move);
        // cv::Point2f tf_p2 = cv::Point2f(seg_B_x + x_move, seg_B_y + y_move);
        // cv::line(im, tf_p1, tf_p2, cv::Scalar(0, 200, 0), 50, 8);
        // cv::circle(im, tf_p1, 100, cv::Scalar(255, 255, 255), 10);
        // display("Result", im);


        // cout << seg_A_pos << endl;
        // cout << seg_B_pos << endl;
        // cout << HT << endl;


        //     Vec2f start = seg_A.start;
        //     Vec3f new_start_with_dummy_1 = HT * (start.homogeneous());
        //     Vec2f new_start_2f = Vec2f(new_start_with_dummy_1.x(), new_start_with_dummy_1.y());
        //     Vec2f end = seg_A.end;
        //     Vec3f new_end_with_dummy_1 = HT * (end.homogeneous());
        //     Vec2f new_end_2f = Vec2f(new_end_with_dummy_1.x(), new_end_with_dummy_1.y());
        //     Segment seg_transformed = Segment(new_start_2f, new_end_2f);
        // cv::Point2f seg_tf_start = cv::Point2f(seg_transformed.start.x() + x_move, seg_transformed.start.y() + y_move);
        // cv::Point2f seg_tf_end = cv::Point2f(seg_transformed.end.x()   + x_move, seg_transformed.end.y()   + y_move);
        // cv::line(im, seg_tf_start, seg_tf_end, cv::Scalar(255, 0, 0), 30, 8);
        // cv::circle(im, seg_tf_start, 100, cv::Scalar(255, 255, 255), 10);
        // display("Result", im);


        // float x1 = 


        // for(vector<Segment>::iterator it_seg = segments_02.begin(); it_seg != segments_02.end(); ++it_seg)
        // {
        //     Vec2f start = it_seg->start;
        //     Vec3f new_start_with_dummy_1 = HT * (start.homogeneous());
        //     Vec2f new_start_2f = Vec2f(new_start_with_dummy_1.x(), new_start_with_dummy_1.y());
        //     Vec2f end = it_seg->end;
        //     Vec3f new_end_with_dummy_1 = HT * (end.homogeneous());
        //     Vec2f new_end_2f = Vec2f(new_end_with_dummy_1.x(), new_end_with_dummy_1.y());
        //     Segment seg_transformed = Segment(new_start_2f, new_end_2f);

        //     float theta_diff = fabs(seg_transformed.angle_degree - seg_01.angle_degree);
        //     float dot = fabs(seg_transformed.segment.dot(seg_01.segment));
        //     float theta_diff_dot = dot * degree_to_radian(theta_diff);
        //     float similarity = theta_diff_dot / dot;
        //     if (theta_diff_dot > dot) {
        //         similarity = dot / theta_diff_dot;
        //     }
        //     cout << "theta_diff: " << theta_diff << endl
        //         << "dot: " << dot << endl
        //         << "theta_diff_dot: " << theta_diff_dot << endl
        //         << "similarity: " << similarity << endl
        //         ;

            // cout << segments_01.at(*it) << endl;
            // cout << seg_transformed << endl << endl;
            // cout << segments_01.at(*it).segment.dot(seg_transformed.segment) << endl;
            // Vec2f a = Vec2f(10, 0);
            // Vec2f b = Vec2f(0, 10);
            // cout << a.unitOrthogonal() << endl;
            // cout << b.unitOrthogonal() << endl;
            // cout << a.unitOrthogonal().dot(b.unitOrthogonal()) << endl;

        // cv::Mat im = cv::Mat::zeros(6000, 8500, CV_8UC3);
        // cv::Point2f seg_01_p1 = cv::Point2f(segments_01.at(idx_i).start.x() + x_move, segments_01.at(idx_i).start.y() + y_move);
        // cv::Point2f seg_01_p2 = cv::Point2f(segments_01.at(idx_i).end.x()   + x_move, segments_01.at(idx_i).end.y()   + y_move);
        // cv::line(im, seg_01_p1, seg_01_p2, cv::Scalar(0, 100, 255), 50, 8);
        // cv::circle(im, seg_01_p1, 100, cv::Scalar(255, 255, 255), 10);
        // display("Result", im);
        // cv::Point2f seg_02_p1 = cv::Point2f(seg_transformed.start.x() + x_move, seg_transformed.start.y() + y_move);
        // cv::Point2f seg_02_p2 = cv::Point2f(seg_transformed.end.x()   + x_move, seg_transformed.end.y()   + y_move);
        // cv::line(im, seg_02_p1, seg_02_p2, cv::Scalar(255, 0, 100), 50, 7);
        // cv::circle(im, seg_02_p1, 100, cv::Scalar(255, 255, 255), 10);
        // display("Result", im);

        // cv::Point2f seg_01_pair_p1 = cv::Point2f(segments_02.at(*it).start.x() + x_move, segments_02.at(*it).start.y() + y_move);
        // cv::Point2f seg_01_pair_p2 = cv::Point2f(segments_02.at(*it).end.x()   + x_move, segments_02.at(*it).end.y()   + y_move);
        // cv::line(im, seg_01_pair_p1, seg_01_pair_p2, cv::Scalar(0, 50, 255), 50, 8);
        // display("Result", im);
        // cv::Point2f seg_transformed_p1 = cv::Point2f(seg_transformed.start.x() + x_move, seg_transformed.start.y() + y_move);
        // cv::Point2f seg_transformed_p2 = cv::Point2f(seg_transformed.end.x()   + x_move, seg_transformed.end.y()   + y_move);
        // cv::line(im, seg_transformed_p1, seg_transformed_p2, cv::Scalar(0, 255, 10), 50, 7);
        // display("Result", im);
        //     cv::Point2f seg_02_p1 = cv::Point2f(it_seg->start.x(), it_seg->start.y());
        //     cv::Point2f seg_02_p2 = cv::Point2f(it_seg->end.x(), it_seg->end.y());
        //     cv::line(im, seg_02_p1, seg_02_p2, cv::Scalar(0, 255, 100), 50, 8);
        //     display("Result", im);

        // }

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
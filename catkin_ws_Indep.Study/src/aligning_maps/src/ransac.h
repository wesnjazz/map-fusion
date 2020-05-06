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
        }
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
        matches.push_back(index_min);
    }
    return matches;
}


void find_affine_translate(cv::Mat &im,  cv::Point2f src[], cv::Point2f dst[], cv::Mat &affine_M, cv::Mat &translate_M)
{
    int x_move = 0;
    int y_move = 0;
    cv::Point2f seg_A_p1    = cv::Point2f(src[0].x + x_move, src[0].y + y_move);
    cv::Point2f seg_A_prp1  = cv::Point2f(dst[0].x + x_move, dst[0].y + y_move);
    cv::Point2f seg_A_p2    = cv::Point2f(src[1].x + x_move, src[1].y + y_move);
    cv::Point2f seg_A_prp2  = cv::Point2f(dst[1].x + x_move, dst[1].y + y_move);
    cv::Point2f seg_A_p3    = cv::Point2f(src[2].x + x_move, src[2].y + y_move);
    cv::Point2f seg_A_prp3  = cv::Point2f(dst[2].x + x_move, dst[2].y + y_move);
    cv::line(im, seg_A_p1, seg_A_prp1, cv::Scalar(100, 255, 255), 2, 8);
    cv::line(im, seg_A_p2, seg_A_prp2, cv::Scalar(50, 205, 205), 2, 8);
    cv::line(im, seg_A_p3, seg_A_prp3, cv::Scalar(0, 155, 155), 2, 8);
    cv::circle(im, cv::Point2f(src[0].x + x_move, src[0].y + y_move), 50, cv::Scalar(255, 0, 255), 10);
    cv::circle(im, cv::Point2f(src[1].x + x_move, src[1].y + y_move), 50, cv::Scalar(155, 0, 155), 10);
    cv::circle(im, cv::Point2f(src[2].x + x_move, src[2].y + y_move), 50, cv::Scalar(55, 0, 55), 10);
    cv::circle(im, cv::Point2f(dst[0].x + x_move, dst[0].y + y_move), 50, cv::Scalar(50, 200, 255), 10);
    cv::circle(im, cv::Point2f(dst[1].x + x_move, dst[1].y + y_move), 50, cv::Scalar(20, 100, 155), 10);
    cv::circle(im, cv::Point2f(dst[2].x + x_move, dst[2].y + y_move), 50, cv::Scalar(0, 50, 55), 10);
    display("Result", im);

    // float data[36] = { 
    //                     x1, y1,  0,  0,  1,  0,
    //                      0,  0, x1, y1,  0,  1,
    //                     x2, y2,  0,  0,  1,  0,
    //                      0,  0, x2, y2,  0,  1,
    //                     x3, y3,  0,  0,  1,  0,
    //                      0,  0, x3, y3,  0,  1
    //                  };
    // float data2[6] = { dst[0], dst[0], dst[1].x, y2p, x3p, y3p };
    // cv::Mat before_M = cv::Mat(6, 6, CV_32FC1, &data);
    // cv::Mat before_M_inv = before_M.inv();
    // cv::Mat transformed_M = cv::Mat(6, 1, CV_32FC1, &data2);
    // trans = np.dot(np.linalg.inv(p),p_prime)
    // p   # original data
    // p_prime  # transformed data

    // cv::Mat rot_mat( 2, 3, CV_32FC1 );
    // cv::Mat warp_mat( 2, 3, CV_32FC1 );
    // cv::Mat warp_dst, warp_rotate_dst;
    // warp_dst = cv::Mat::zeros(im.rows, im.cols, im.type());

    cout 
        << "src:" << endl << src[0] << "\t" << src[1] << "\t" << src[2] << endl
        << "dst:" << endl << dst[0] << "\t" << dst[1] << "\t" << dst[2] << endl
        << endl;


    Vec2f A_head = Vec2f(src[0].x, src[0].y);
    Vec2f A_tail = Vec2f(src[2].x, src[2].y);
    Vec2f B_head = Vec2f(dst[0].x, dst[0].y);
    Vec2f B_tail = Vec2f(dst[2].x, dst[2].y);
    Segment Seg_A = Segment(A_head, A_tail);
    Segment Seg_B = Segment(B_head, B_tail);
    Vec3f A_frame = Vec3f(A_head.x(), A_head.y(), Seg_A.angle_degree);
    Vec3f B_frame = Vec3f(B_head.x(), B_head.y(), Seg_B.angle_degree);

    cout << "A_frame:" << endl << A_frame << endl;
    cout << "B_frame:" << endl << B_frame << endl;

    cv::Point2f p1_head = cv::Point2f(A_head.x(), A_head.y());
    cv::Point2f p1_tail = cv::Point2f(A_tail.x(), A_tail.y());
    cv::Point2f p2_head = cv::Point2f(B_head.x(), B_head.y());
    cv::Point2f p2_tail = cv::Point2f(B_tail.x(), B_tail.y());
    cv::line(im, p1_head, p1_tail, cv::Scalar(0,0,255), 30, 8);
    cv::line(im, p2_head, p2_tail, cv::Scalar(0,0,255), 30, 8);
    display("Result", im);

    Mat3f HT = get_HT_Aframe_to_Bframe(A_frame, B_frame);

    float a = HT(0, 0);
    float b = HT(0, 1);
    float c = HT(0, 2);
    float e = HT(1, 0);
    float f = HT(1, 1);
    float g = HT(1, 2);
    cout << a << "\t" << b << "\t" << c << endl;
    cout << e << "\t" << f << "\t" << g << endl;


    affine_M.at<float>(0, 0) = a;
    affine_M.at<float>(0, 1) = b;
    affine_M.at<float>(1, 0) = e;
    affine_M.at<float>(1, 1) = f;
    translate_M.at<float>(0, 0) = c;
    translate_M.at<float>(1, 0) = g;

    // cv::Mat warp_mat = cv::getAffineTransform(src, dst);
    // affine_M = warp_mat(cv::Range::all(), cv::Range(0,2));
    // affine_M.convertTo(affine_M, CV_32FC1);
    // translate_M = warp_mat(cv::Range::all(), cv::Range(2, 3));
    // translate_M.convertTo(translate_M, CV_32FC1);

    // cv::warpAffine(im, warp_dst, warp_mat, warp_dst.size());
    // cout << "warp_mat:" << endl << warp_mat << endl << endl;
    cout << "affine_M:" << endl << affine_M << endl << endl;
    cout << "translate_M:" << endl << translate_M << endl << endl;
    // display("Result", warp_dst);

}


void get_three_pairs_of_line(Segment &depart, Segment &arrival, cv::Point2f src[], cv::Point2f dst[])
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
    src[0] = cv::Point2f( x1, y1 );
    src[1] = cv::Point2f( x2, y2 );
    src[2] = cv::Point2f( x3, y3 );
    dst[0] = cv::Point2f( x1p, y1p );
    dst[1] = cv::Point2f( x2p, y2p );
    dst[2] = cv::Point2f( x3p, y3p );
}

void draw_affine_transforms(cv::Mat &im_board, vector<Segment> &segments, cv::Mat &affine_M, cv::Mat &translate_M)
{
    for(vector<Segment>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        float head[2] = { it->start.x(), it->start.y() };
        float tail[2] = { it->end.x(), it->end.y() };
        cv::Mat head_M = cv::Mat(2, 1, CV_32FC1, head);
        cv::Mat tail_M = cv::Mat(2, 1, CV_32FC1, tail);
        cv::Mat head_prime = affine_M * head_M + translate_M;
        cv::Mat tail_prime = affine_M * tail_M + translate_M;

        int x_move = 0;
        int y_move = 0;
        cv::Point2f p1 = cv::Point2f(head_prime.at<float>(0, 0) + x_move, head_prime.at<float>(0, 1) + y_move);
        cv::Point2f p2 = cv::Point2f(tail_prime.at<float>(0, 0) + x_move, tail_prime.at<float>(0, 1) + y_move);
        cv::line(im_board, p1, p2, cv::Scalar(200,200,255), 10, 8);
        cout 
            << "head_M:" << endl << head_M << endl
            << "tail_M: " << endl << tail_M << endl
            << "head_prime:" << endl << head_prime << endl
            << "tail_prime: " << endl << tail_prime << endl << endl;
        // display("Result", im_board);
    }
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


void test(cv::Mat src)
{
    using namespace cv;
    Point2f srcTri[3];
    srcTri[0] = Point2f( 0.f, 0.f );
    srcTri[1] = Point2f( src.cols - 1.f, 0.f );
    srcTri[2] = Point2f( 0.f, src.rows - 1.f );
    Point2f dstTri[3];
    dstTri[0] = Point2f( 0.f, src.rows*0.13f );
    dstTri[1] = Point2f( src.cols*0.25f, src.rows*0.25f );
    dstTri[2] = Point2f( src.cols*0.05f, src.rows*0.07f );
    Mat warp_mat = getAffineTransform( srcTri, dstTri );
    cout << "warp_mat:" << endl << warp_mat << endl << endl;
    getchar();
    Mat warp_dst = Mat::zeros( src.rows/3, src.cols/3, src.type() );
    warpAffine( src, warp_dst, warp_mat, warp_dst.size() );
    Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
    double angle = -50.0;
    double scale = 0.6;
    Mat rot_mat = getRotationMatrix2D( center, angle, scale );
    Mat warp_rotate_dst;
    warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );
    imshow( "Source image", src );
    imshow( "Warp", warp_dst );
    imshow( "Warp + Rotate", warp_rotate_dst );
    waitKey();
}



void lsd_txt_to_cv_mat(ifstream &file, cv::Mat &cv_mat)
{
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

    vector<Segment> segments;
    read_lsd(file, segments);
    draw_lsd_map(cv_mat, segments, color_g, 5, 5);

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

    cv::Mat im_base = cv::Mat::zeros(3000, 5000, CV_32FC3);
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

    // test(im_base);

    /** Compute matches **/
    vector<int> matches = compute_matches(img, segments_01, segments_02);
    
    for(vector<int>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        // cv::Mat im_board = cv::Mat::zeros(im_base.rows, im_base.cols, im_base.type);
        cv::Mat im_board = cv::Mat::zeros(3000, 5000, CV_32FC3);
        cv::Mat im_affine = cv::Mat::zeros(3000, 5000, CV_32FC3);
        im_board += im_base;
        im_affine += im_base;
        int x_move = 0;
        int y_move = 0;
        int idx_i = it - matches.begin();
        /** seg_A : a segment
         *  seg_B : seg_A's matching segment **/
        Segment seg_A = segments_01.at(idx_i);
        Segment seg_B = segments_02.at(*it);

        // cv::Mat im = cv::Mat::zeros(6000, 8500, CV_32FC3);
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


        cv::Point2f src[3];
        cv::Point2f dst[3];
        get_three_pairs_of_line(seg_A, seg_B, src, dst);
        find_affine_translate(im_board, src, dst, affine_M, translate_M);

        cout << "*****************" << endl;
        cout << "affine_M: " << endl << affine_M << endl << endl;
        cout << "translate_M: " << endl << translate_M << endl << endl;

        draw_affine_transforms(im_board, segments_02, affine_M, translate_M);
        display("Result", im_board);

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

        // cv::Mat im = cv::Mat::zeros(6000, 8500, CV_32FC3);
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
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


vector<int> compute_matches(cv::Mat &img, vector<Segment> &segs_pivot, vector<Segment> &segs_target)
{

    int segs_pivot_size = segs_pivot.size();
    int segs_target_size = segs_target.size();
    std::random_device rd_pivot;
    std::mt19937 gen_pivot( rd_pivot());
    std::uniform_int_distribution<> dis_pivot( 0, segs_pivot_size-1);
    std::random_device rd_target;
    std::mt19937 gen_target( rd_target());
    std::uniform_int_distribution<> dis_target( 0, segs_target_size-1);

    // // random indices
    // int num_sets = 50;
    // float sum_diff = 999999999.0f;
    // float threshold_sum = 1.0f;
    // float threshold_dist = 100.0;
    // int num_trials = 300;
    // float minimum_sum_diff = 999999999.0f;

    // indices of segments
    vector<int> idxs_pivot;
    vector<int> idxs_target;
    
    int num_trials = 300;
    int num_matches = 30;
    int num_sets = 50;
    float threshold_sum = 1.0f;
    float threshold_dist = 100.0;
    float sum_diff = 999999999.0f;
    float minimum_sum_diff = 999999999.0f;

    cv::Mat im_compute_matches_base = cv::Mat::zeros(3000, 5000, CV_32FC3);
    cv::Mat im_compute_matches_pivot = cv::Mat::zeros(3000, 5000, CV_32FC3);
    cv::Mat im_compute_matches_target = cv::Mat::zeros(3000, 5000, CV_32FC3);
    cv::Mat im_compute_matches_final = cv::Mat::zeros(3000, 5000, CV_32FC3);
    while(true)
    {
        // random indices

        num_trials--;
        cout << "\n\n\t\t\t\t\t\ttrial: " << num_trials << endl;

        int segs_pivot_idx = 0;
        int segs_pivot_min_idx = 0;
        int segs_target_min_idx = 0;
        vector<int> closest_idx_min_pivot;
        vector<int> closest_idx_min_target;

        for(vector<Segment>::iterator it_seg_pivot = segs_pivot.begin(); it_seg_pivot != segs_pivot.end(); it_seg_pivot++)
        {
            im_compute_matches_pivot = img.clone();

            Segment segment_pivot = *it_seg_pivot;
            // Segment segment_pivot = segs_pivot.at(rand_segs_pivot_idx);
            // copy vectors of segs_pivot, segs_target
            vector<Segment> segs_pivot_copy;
            for (int i=0; i<segs_pivot.size(); i++) 
                segs_pivot_copy.push_back(segs_pivot[i]); 
            // get a random segment
            // int rand_segs_pivot_idx = dis_pivot(gen_pivot);
            // indices of closest segments from pivot
            vector<int> closest_idx_pivot;
            vector<Segment *> closes_seg_address_pivot;
            // distances from pivot
            vector<float> distances_from_pivot;
            // cout << "segment_pivot:mid:" << segment_pivot.mid << endl;
            for(vector<Segment>::iterator it = segs_pivot.begin(); it != segs_pivot.end(); ++it)
            {
                float distance_tmp = segment_pivot.distance_between_segments(*it);
                distances_from_pivot.push_back(distance_tmp);
                // cout << distance_tmp << "\t";
            }
            // get closest segments
            int num_closest_segs_pivot = num_matches;
            while(num_closest_segs_pivot > 0)
            {
                // get the minimum distance segment
                float min_distance_pivot = 999999999.0f;
                int min_pivot_idx = 0;
                for(int i=0; i<segs_pivot_copy.size(); ++i)
                {
                    float distance_tmp = segment_pivot.distance_between_segments(segs_pivot_copy.at(i));
                    if(distance_tmp < min_distance_pivot)
                    {   
                        // cout << "i:" << i << endl;
                        // cout << "closest_idx_pivot:\t";
                        // for(int j=0; j<closest_idx_pivot.size(); j++)
                        // {
                        //     cout << closest_idx_pivot[j] << "\t";
                        // }
                        // cout << endl;
                        if(find(closest_idx_pivot.begin(), closest_idx_pivot.end(), i) == closest_idx_pivot.end())
                        {
                            min_distance_pivot = distance_tmp;
                            min_pivot_idx = i;
                        }
                        else {
                            continue;
                        }
                    }
                    // getchar();
                }
                // cout << "closes:idx:size:" << closest_idx_pivot.size() << endl;
                // cout << "mid_idx: " << min_pivot_idx << endl;
                // cout << "distance: " << min_distance_pivot << endl;
                // segs_pivot_copy.erase(segs_pivot_copy.begin() + min_pivot_idx);
                // distances_from_pivot.erase(distances_from_pivot.begin() + min_pivot_idx);
                closest_idx_pivot.push_back(min_pivot_idx);
                // cout << "size of closest segs: " << num_closest_segs_pivot << endl;
                num_closest_segs_pivot--;
            }
            // get sum of distances
            float sum_closest_distance_pivot = 0.0f;
            for(vector<int>::iterator it = closest_idx_pivot.begin(); it != closest_idx_pivot.end(); ++it)
            {
                sum_closest_distance_pivot += segment_pivot.distance_between_segments(segs_pivot.at(*it));
                // cout << segment_pivot.distance_between_segments(segs_pivot.at(*it)) << endl;
                // cv::Point2f head = cv::Point2f(segs_pivot.at(*it).start.x(), segs_pivot.at(*it).start.y());
                // cv::Point2f tail = cv::Point2f(segs_pivot.at(*it).end.x(), segs_pivot.at(*it).end.y());
                // cv::line(im_compute_matches_pivot, head, tail, cv::Scalar(200, 200, 0), 15, 1);
            }
            // cout << "sum_closest_distance_pivot: " << sum_closest_distance_pivot << endl;


            int segs_target_idx = 0;
            for(vector<Segment>::iterator it_seg_target = segs_target.begin(); it_seg_target != segs_target.end(); it_seg_target++)
            {
                im_compute_matches_target = im_compute_matches_pivot.clone();

                Segment segment_target = *it_seg_target;
                // Segment segment_target = segs_target.at(rand_segs_target_idx);
                // copy vectors of segs_pivot, segs_target
                vector<Segment> segs_target_copy;
                for (int i=0; i<segs_target.size(); i++) 
                    segs_target_copy.push_back(segs_target[i]); 
                // get a random segment
                // int rand_segs_target_idx = dis_target(gen_target);
                // indices of closest segments from target
                vector<int> closest_idx_target;
                vector<Segment *> closes_seg_address_target;
                // distances from target
                vector<float> distances_from_target;
                // cout << "segment_target:mid:" << segment_target.mid << endl;
                for(vector<Segment>::iterator it = segs_target.begin(); it != segs_target.end(); ++it)
                {
                    float distance_tmp = segment_target.distance_between_segments(*it);
                    distances_from_target.push_back(distance_tmp);
                    // cout << distance_tmp << "\t";
                }
                // get closest segments
                int num_closest_segs_target = num_matches;
                while(num_closest_segs_target > 0)
                {
                    // get the minimum distance segment
                    float min_distance_target = 999999999.0f;
                    int min_target_idx = 0;
                    for(int i=0; i<segs_target_copy.size(); ++i)
                    {
                        float distance_tmp = segment_target.distance_between_segments(segs_target_copy.at(i));
                        if(distance_tmp < min_distance_target)
                        {   
                            // cout << "i:" << i << endl;
                            // cout << "closest_idx_target:\t";
                            // for(int j=0; j<closest_idx_target.size(); j++)
                            // {
                            //     cout << closest_idx_target[j] << "\t";
                            // }
                            // cout << endl;
                            if(find(closest_idx_target.begin(), closest_idx_target.end(), i) == closest_idx_target.end())
                            {
                                min_distance_target = distance_tmp;
                                min_target_idx = i;
                            }
                            else {
                                continue;
                            }
                        }
                        // getchar();
                    }
                    // cout << "closes:idx:size:" << closest_idx_target.size() << endl;
                    // cout << "mid_idx: " << min_target_idx << endl;
                    // cout << "distance: " << min_distance_target << endl;
                    // segs_target_copy.erase(segs_target_copy.begin() + min_target_idx);
                    // distances_from_target.erase(distances_from_target.begin() + min_target_idx);
                    closest_idx_target.push_back(min_target_idx);
                    // cout << "size of closest segs: " << num_closest_segs_target << endl;
                    num_closest_segs_target--;
                }

                // get sum of distances
                int x_move = 0;
                int y_move = 0;
                float sum_closest_distance_target = 0.0f;
                for(vector<int>::iterator it = closest_idx_target.begin(); it != closest_idx_target.end(); ++it)
                {
                    sum_closest_distance_target += segment_target.distance_between_segments(segs_target.at(*it));
                    // cout << segment_target.distance_between_segments(segs_target.at(*it)) << endl;
                    // cv::Point2f head = cv::Point2f(segs_target.at(*it).start.x() + x_move, segs_target.at(*it).start.y() + y_move);
                    // cv::Point2f tail = cv::Point2f(segs_target.at(*it).end.x()   + x_move, segs_target.at(*it).end.y()   + y_move);
                    // cv::line(im_compute_matches_target, head, tail, cv::Scalar(0, 200, 200), 15, 1);
                }
                // cout 
                //     << "seg_pivot[" << segs_pivot_idx << "]: (" << segment_pivot.mid.x() << "," << segment_pivot.mid.y() << ")"
                //     << "\t"
                //     << "seg_target[" << segs_target_idx << "]: (" << segment_target.mid.x() << "," << segment_target.mid.y() << ")"
                //     << endl
                //     << "sum_closest_distance_target: " << sum_closest_distance_target 
                //     << "\tsegs_target_size: " << segs_target.size()
                //     << "\tsegs_target_idx: " << segs_target_idx
                //     << endl;

                float sum_total_diff = fabs(sum_closest_distance_pivot - sum_closest_distance_target);
                // cout << "sum_diff: " << sum_total_diff << endl;
                if (sum_total_diff < minimum_sum_diff)
                {
                    minimum_sum_diff = sum_total_diff;
                    segs_pivot_min_idx = segs_pivot_idx;
                    segs_target_min_idx = segs_target_idx;
                    closest_idx_min_pivot.clear();
                    for (int i=0; i<closest_idx_pivot.size(); i++) 
                        closest_idx_min_pivot.push_back(closest_idx_pivot[i]); 
                    closest_idx_min_target.clear();
                    for (int i=0; i<closest_idx_target.size(); i++) 
                        closest_idx_min_target.push_back(closest_idx_target[i]); 
                }
                // getchar();
                // cout 
                //     << "the minimum sum_diff:" << minimum_sum_diff 
                //     << endl
                //     << "min_seg_pivot[" << segs_pivot_min_idx << "]: (" << segs_target[segs_pivot_min_idx].mid.x() << "," << segs_target[segs_pivot_min_idx].mid.y() << ")"
                //     << "\t"
                //     << "min_seg_target[" << segs_target_min_idx << "]: (" << segs_target[segs_target_min_idx].mid.x() << "," << segs_target[segs_target_min_idx].mid.y() << ")"
                //     << endl << endl
                //     << endl;
                // getchar();
                // display("Results", im_compute_matches_target);
                segs_target_idx++;
            }

            cout 
                << "seg_pivot_idx: " << segs_pivot_idx
                << "\t"
                << "seg_pivot[" << segs_pivot_idx << "]: (" << segs_pivot[segs_pivot_idx].mid.x() << "," << segs_pivot[segs_pivot_idx].mid.y() << ")"
                << endl;

                cout 
                    << "the minimum sum_diff:" << minimum_sum_diff 
                    << endl
                    << "seg_pivot[" << segs_pivot_min_idx << "]: (" << segs_pivot[segs_pivot_min_idx].mid.x() << "," << segs_pivot[segs_pivot_min_idx].mid.y() << ")"
                    << "\t"
                    << "seg_target[" << segs_target_min_idx << "]: (" << segs_target[segs_target_min_idx].mid.x() << "," << segs_target[segs_target_min_idx].mid.y() << ")"
                    << endl << endl
                    << endl;
            // getchar();

            // display("Results", im_compute_matches_board);
            // if (sum_total_diff < threshold_sum)
            // {
            //     display("Results", im_compute_matches_board);
            //     break;
            // }




        // int rand_segs_target_idx = dis_target(gen_target);
        // Segment segs_target = segs_pivot.at(rand_segs_target_idx);

        // vector<int> closest_idx_target;
        // vector<Segment *> closes_seg_address_target;

        // // copy vectors of segs_pivot, segs_target
        // vector<Segment> segs_pivot_copy;
        // for (int i=0; i<segs_pivot.size(); i++) 
        // segs_pivot_copy.push_back(segs_pivot[i]); 
        // vector<Segment> segs_target_copy;
        // for (int i=0; i<segs_target.size(); i++) 
        // segs_target_copy.push_back(segs_target[i]); 

        // // distances from pivot
        // vector<float> distances_from_target;




        // for(int i=0; i<num_sets; ++i)
        // {
        //     Segment seg_tmp_pivot = segs_pivot.at()
        //     float dst = segs_pivot.distance_between_segments(seg_)
        //     idxs_pivot.push_back(dis_pivot(gen_pivot));
        //     cout << idxs_pivot.at(idxs_pivot.size()-1) << "\t";
        // }

        


        // idxs_pivot.clear();
        // idxs_target.clear();
        // for(int i=0; i<num_sets; ++i)
        // {
        //     idxs_pivot.push_back(dis_pivot(gen_pivot));
        //     cout << idxs_pivot.at(idxs_pivot.size()-1) << "\t";
        // }
        // for(int i=0; i<num_sets; ++i)
        // {
        //     idxs_target.push_back(dis_target(gen_target));
        //     cout << idxs_target.at(idxs_target.size()-1) << "\t";
        // }

        // // sum of pivot
        // float sum_pivot = 0.0;
        // for(vector<int>::iterator it = idxs_pivot.begin(); it != idxs_pivot.end(); ++it)
        // {
        //     sum_pivot += segs_pivot.at(*it).length;
        //     cout << "pivot at:" << *it << "\tvalue:" << segs_pivot.at(*it).length << endl;
        // }
        // cout << "sum_pivot: " << sum_pivot << endl;

        // // sum of target
        // float sum_target = 0.0;
        // for(vector<int>::iterator it = idxs_target.begin(); it != idxs_target.end(); ++it)
        // {
        //     sum_target += segs_target.at(*it).length;
        //     cout << "target at:" << *it << "\tvalue:" << segs_target.at(*it).length << endl;
        // }
        // cout << "sum_target: " << sum_target << endl;

        // sum_diff = fabs(sum_pivot - sum_target);
        // cout << endl << "sum_diff: " << sum_diff << endl;
        // // getchar();
        // if(sum_diff <= threshold_sum) {
        //     cout << "found good matches!" << endl;
        //     break;
        // }
        // // getchar();
            segs_pivot_idx++;
        }
        cout << "\nfinished!!\nready to draw?" << endl;
        getchar();

        im_compute_matches_final = img.clone();

        for(vector<int>::iterator it = closest_idx_min_pivot.begin(); it != closest_idx_min_pivot.end(); ++it)
        {
            cv::Point2f head = cv::Point2f(segs_pivot.at(*it).start.x(), segs_pivot.at(*it).start.y() );
            cv::Point2f tail = cv::Point2f(segs_pivot.at(*it).end.x()  , segs_pivot.at(*it).end.y()   );
            cv::line(im_compute_matches_final, head, tail, cv::Scalar(0, 200, 200), 15, 1);
        }
        for(vector<int>::iterator it = closest_idx_min_target.begin(); it != closest_idx_min_target.end(); ++it)
        {
            cv::Point2f head = cv::Point2f(segs_target.at(*it).start.x(), segs_target.at(*it).start.y() );
            cv::Point2f tail = cv::Point2f(segs_target.at(*it).end.x()  , segs_target.at(*it).end.y()   );
            cv::line(im_compute_matches_final, head, tail, cv::Scalar(0, 200, 200), 15, 1);
        }
        display("Final", im_compute_matches_final);
        display("Final", im_compute_matches_final);
        display("Final", im_compute_matches_final);


        if (num_trials < 0)
        {
            break;
        }
    }


    // for(vector<int>::iterator it = idxs_pivot.begin(); it != idxs_pivot.end(); ++it)
    // {
    //     cv::Point2f head = cv::Point2f(segs_pivot.at(*it).start.x(), segs_pivot.at(*it).start.y());
    //     cv::Point2f tail = cv::Point2f(segs_pivot.at(*it).end.x(), segs_pivot.at(*it).end.y());
    //     cv::line(img, head, tail, cv::Scalar(0, 0, 200), 2, 1);
    // }
    // display("Result", img);
    // for(vector<int>::iterator it = idxs_target.begin(); it != idxs_target.end(); ++it)
    // {
    //     cv::Point2f head = cv::Point2f(segs_target.at(*it).start.x(), segs_target.at(*it).start.y());
    //     cv::Point2f tail = cv::Point2f(segs_target.at(*it).end.x(), segs_target.at(*it).end.y());
    //     cv::line(img, head, tail, cv::Scalar(200, 0, 0), 2, 1);
    // }
    // display("Result", img);


    vector<int> matches;
    // for(vector<Segment>::iterator it_01 = segs_pivot.begin(); it_01 != segs_pivot.end(); ++it_01)
    // {
    //     int index_min = 0;
    //     float diff = 0.0f;
    //     float min_diff = 9999999999.0f;

    //     for(vector<Segment>::iterator it_02 = segs_target.begin(); it_02 != segs_target.end(); ++it_02)
    //     {
    //         diff = fabs(it_01->length - it_02->length);
    //         // cout << "min_diff: " << min_diff << "\t" << "diff: " << diff << endl;
    //         if (diff < min_diff)
    //         {
    //             min_diff = diff; 
    //             index_min = it_02 - segs_target.begin();
    //         }
    //     }
    //     matches.push_back(index_min);
    // }
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
    cv::line(im, seg_A_p1, seg_A_prp1, cv::Scalar(0, 0, 255), 4, 8);
    cv::line(im, seg_A_p2, seg_A_prp2, cv::Scalar(100, 100, 100), 2, 8);
    cv::line(im, seg_A_p3, seg_A_prp3, cv::Scalar(255, 255, 255), 2, 8);
    cv::circle(im, cv::Point2f(src[0].x + x_move, src[0].y + y_move), 50, cv::Scalar(255, 255, 255), 9);
    cv::circle(im, cv::Point2f(src[1].x + x_move, src[1].y + y_move), 50, cv::Scalar(0, 100, 100), 8);
    cv::circle(im, cv::Point2f(src[2].x + x_move, src[2].y + y_move), 50, cv::Scalar(0, 100, 100), 8);
    cv::circle(im, cv::Point2f(dst[0].x + x_move, dst[0].y + y_move), 50, cv::Scalar(255, 255, 255), 9);
    cv::circle(im, cv::Point2f(dst[1].x + x_move, dst[1].y + y_move), 50, cv::Scalar(0, 100, 100), 8);
    cv::circle(im, cv::Point2f(dst[2].x + x_move, dst[2].y + y_move), 50, cv::Scalar(0, 100, 100), 8);
    // display("Result", im);

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
    cv::line(im, p1_head, p1_tail, cv::Scalar(0,0,255), 40, 8);
    cv::line(im, p2_head, p2_tail, cv::Scalar(255,0,0), 40, 8);
    display("Result", im);

    Mat3f HT = get_HT_Aframe_to_Bframe(B_frame, A_frame);

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

void draw_affine_transforms(cv::Mat &im_board, vector<Segment> &segments, cv::Mat &affine_M, cv::Mat &translate_M, cv::Scalar &color)
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
        cv::line(im_board, p1, p2, color, 10, 1);
        // cv::line(im_board, p1, p2, cv::Scalar(200,200,255), 10, 8);
        cout 
            << "head_M:" << endl << head_M << endl
            << "tail_M: " << endl << tail_M << endl
            << "head_prime:" << endl << head_prime << endl
            << "tail_prime: " << endl << tail_prime << endl << endl;
        // display("Result", im_board);
    }
}



void draw_lsd_map(cv::Mat &im, vector<Segment> &segments, cv::Scalar &color, int thickness, int type, int x_move, int y_move)
{
    // int x_move = 0;
    // int y_move = 0;
    for(vector<Segment>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        cv::Point2f p1 = cv::Point2f(it->start.x() + x_move, it->start.y() + y_move);
        cv::Point2f p2 = cv::Point2f(it->end.x()   + x_move, it->end.y()   + y_move);
        cv::line(im, p1, p2, color, thickness, type);
    }
    // display("Result", im);
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
    draw_lsd_map(cv_mat, segments, color_g, 5, 5, 0, 0);

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
    draw_lsd_map(im_base, segments_01, color_r, 2, 1, 0, 0);
    draw_lsd_map(im_base, segments_02, color_b, 2, 2, 0, 0);
    display("Result", im_base);

    // test(im_base);

    /** Compute matches **/
    vector<int> matches = compute_matches(im_base, segments_01, segments_02);
    
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
        // cv::Point2f seg_A_p1 = cv::Point2f(seg_A.start.x() + x_move, seg_A.start.y() + y_move);
        // cv::Point2f seg_A_p2 = cv::Point2f(seg_A.end.x()   + x_move, seg_A.end.y()   + y_move);
        // cv::line(im_board, seg_A_p1, seg_A_p2, color_g, 10, 3);
        // cv::circle(im_board, seg_A_p1, 50, color_white, 10);
        // display("Board", im_board);

        // cv::Point2f seg_B_p1 = cv::Point2f(seg_B.start.x() + x_move, seg_B.start.y() + y_move);
        // cv::Point2f seg_B_p2 = cv::Point2f(seg_B.end.x()   + x_move, seg_B.end.y()   + y_move);
        // cv::line(im_board, seg_B_p1, seg_B_p2, color_purple, 10, 4);
        // cv::circle(im_board, seg_B_p1, 50, color_white, 10);
        // display("Board", im_board);


        cv::Mat affine_M_target = cv::Mat::zeros(2, 2, CV_32FC1);
        cv::Mat translate_M_target = cv::Mat::zeros(2, 1, CV_32FC1);
        cv::Mat affine_M_pivot = cv::Mat::zeros(2, 2, CV_32FC1);
        cv::Mat translate_M_pivot = cv::Mat::zeros(2, 1, CV_32FC1);
        affine_M_pivot.at<float>(0, 0) = 1;
        affine_M_pivot.at<float>(0, 1) = 0;
        affine_M_pivot.at<float>(1, 0) = 0;
        affine_M_pivot.at<float>(1, 1) = 1;
        translate_M_pivot.at<float>(0, 0) = 0;
        translate_M_pivot.at<float>(1, 0) = 0;
        affine_M_pivot.convertTo(affine_M_pivot, CV_32FC3);
        translate_M_pivot.convertTo(translate_M_pivot, CV_32FC3);

        cv::Point2f src[3];
        cv::Point2f dst[3];
        get_three_pairs_of_line(seg_A, seg_B, src, dst);
        find_affine_translate(im_board, src, dst, affine_M_target, translate_M_target);

        cout << "*****************" << endl;
        cout << "affine_M_target: " << endl << affine_M_target << endl << endl;
        cout << "translate_M_target: " << endl << translate_M_target << endl << endl;

        cv::Scalar color_pivot  = cv::Scalar(255, 255, 0);
        cv::Scalar color_target = cv::Scalar(0, 255, 0);

        draw_affine_transforms(im_board, segments_01, affine_M_pivot, translate_M_pivot, color_pivot);
        draw_affine_transforms(im_board, segments_02, affine_M_target, translate_M_target, color_target);
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
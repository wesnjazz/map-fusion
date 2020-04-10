#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <deque>
#include <fstream>
#include "segment.h"
#include "robot.h"
#include "laser.h"
#include "noise.h"
#include "wheelencoder.h"
#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <vector_slam_msgs/LidarDisplayMsg.h>


void simulate_scan_with_vision(vector<Vec2f> &point_cloud, vector<Vec2f> &collison_candidates, Robot &robot, vector<Segment> &wall_segments,
                            Laser &laser_sensor, Noise &length_noise, Noise &angle_noise, float dx_ns_accumulated, float dy_ns_accumulated);
void simulate_scan(vector<Vec2f> &point_cloud, Robot &robot, vector<Segment> &wall_segments,
                            Laser &laser_sensor, Noise &length_noise, Noise &angle_noise);
void collision_avoidance(vector<Vec2f> &point_cloud, Robot &robot, vector<Mat3f> &aHTb);

deque<Vec2f> interpolate_curve_points(deque<Eigen::Matrix3f> &homos, float delta_t,
                                      Robot &robot, Vec2f &depart, Vec2f &arrive, bool noisy = false, Noise *noise = NULL);

void draw_robot_vector(Robot &robot_ideal, vector_slam_msgs::LidarDisplayMsg &lidar_msg, uint32_t color = 0xFF000000);
void draw_grids(vector_slam_msgs::LidarDisplayMsg &lidar_msg, uint32_t color = 0x10000000);
void draw_grid_line_of_robot_frame(Robot &robot_ideal, Mat3f &new_HT, Vec3f &arrival_R, vector_slam_msgs::LidarDisplayMsg &lidar_msg, bool erase=false);

int usage(char *app_name);
void read_segments(ifstream &seg_file, vector<Segment> &segments, 
                    bool origin_transformed = false, Vec3f *TF_origin = NULL);
void read_waypoints(ifstream &pos_file, deque<Vec3f> &positions, 
                    bool origin_transformed = false, Vec3f *TF_origin = NULL);
Vec3f read_TF_origin(ifstream &TF_origin_file);

float cut_redundant_epsilon(float x, float threshold = 0.000001);
float degree_to_radian(float theta);
float radian_to_degree(float theta);
float get_delta_t(Laser &laser);
float get_vector_length(Vec2f &v);

bool if_arrived_at_a_point_frameW(Robot &robot, Vec3f &goal, float threshold_distance = 0.01, float threshold_heading_degree = 1);
bool if_arrived_at_xy_frameW(Robot &robot, float x, float y, float threshold_distance = 0.05);
bool if_arrived_at_theta_degree_frameW(Robot &robot, float theta_degree, float threshold_theta = 1);
bool if_collides(vector<Vec2f> &point_cloud, Robot &robot, vector_slam_msgs::LidarDisplayMsg &lidar_msg, ros::Publisher &lidar_msg_pub);
void check_safety(Robot &robot___actual, float distance_to_arrival_R, bool safely_arrived);


#endif
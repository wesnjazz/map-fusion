#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <deque>
#include <fstream>
#include "segment.h"
#include "robot.h"
#include "laser.h"
#include "noise.h"
#include <geometry_msgs/Vector3.h>
#include <vector_slam_msgs/LidarDisplayMsg.h>


void simulate_scan(vector<Vec2f> &point_cloud, Robot &robot, vector<Segment> &wall_segments,
                            Laser &laser_sensor, Noise &length_noise, Noise &angle_noise);
float get_vector_length(Vec2f &v);
deque<Vec2f> interpolate_curve_points(deque<Eigen::Matrix3f> &homos, float delta_t,
                                      Robot &robot, Vec2f &depart, Vec2f &arrive, bool noisy = false, Noise *noise = NULL);
void draw_robot_vector(Robot &robot_ideal, vector_slam_msgs::LidarDisplayMsg &lidar_msg);

int usage(char *app_name);
void read_segments(ifstream &seg_file, vector<Segment> &segments);
void read_waypoints(ifstream &pos_file, deque<Vec3f> &positions, deque<float>robot_headings, vector_slam_msgs::LidarDisplayMsg &msg);
float cut_redundant_epsilon(float x, float threshold = 0.000001);
float degree_to_radian(float theta);
float radian_to_degree(float theta);
float get_delta_t(Laser &laser);
bool if_arrived_at_a_point_frameW(Robot &robot, Vec3f &goal, float threshold_distance = 0.01, float threshold_heading_degree = 1);
void draw_grid_line_of_robot_frame(Robot &robot_ideal, Mat3f &new_HT, Vec3f &arrival_R, vector_slam_msgs::LidarDisplayMsg &lidar_msg, bool erase=false);

#endif
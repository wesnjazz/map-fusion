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
deque<Vec2f> interpolate_curve_points(Robot &robot, Vec2f &depart, Vec2f &arrive, bool noisy = false, Noise *noise = NULL);
void draw_robot_vector(Robot &robot_ideal, vector_slam_msgs::LidarDisplayMsg &lidar_msg);

int usage(char *app_name);
void read_segments(ifstream &seg_file, vector<Segment> &segments);
void read_waypoints(ifstream &pos_file, deque<Vec2f> &positions);
float cut_redundant_epsilon(float x, float threshold = 0.000001);
float degree_to_radian(float theta);
float radian_to_degree(float theta);
float get_delta_t(Laser &laser);


#endif
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


void simulate_scan(vector<Vec2f> &point_cloud, Robot &robot, vector<Segment> &wall_segments,
                            Laser &laser_sensor, Noise &length_noise, Noise &angle_noise);
float get_vector_length(Vec2f &v);
deque<Vec2f> interpolate_curve_points(Robot &robot, Vec2f &goal);

int usage(char *app_name);
void read_segments(ifstream &seg_file, vector<Segment> &segs);
// void read_positions(ifstream &pos_file, vector<Position> &positions);
float cut_redundant_epsilon(float x, float threshold = 0.000001);

#endif
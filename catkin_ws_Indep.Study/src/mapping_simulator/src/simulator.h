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


void simulate_scan(vector<Vec2f> *point_cloud, Robot *robot, vector<Segment> *wall_segments,
                            Laser *laser_sensor, Noise *length_noise, Noise *angle_noise);
double get_vector_length(Vec2f &v);
deque<Position> interpolate_curve_points(Robot &robot, Position &goal);

int usage(char *app_name);
void read_segments(ifstream &seg_file, vector<Segment> *segs);
void read_positions(ifstream &pos_file, vector<Position> *positions);

#endif
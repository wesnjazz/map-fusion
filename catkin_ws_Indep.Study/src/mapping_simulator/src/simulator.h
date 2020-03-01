#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <fstream>
#include "segment.h"
#include "robot.h"
#include "laser.h"
#include "noise.h"


void simulate_scan(vector<Vec2f> *point_cloud, Robot *robot, vector<Segment> *wall_segments,
                            Laser *laser_sensor, Noise *length_noise, Noise *angle_noise);
int usage(char *app_name);
void read_segments(ifstream &seg_file, vector<Segment> *segs);
void read_positions(ifstream &pos_file, vector<Position> *positions);

#endif
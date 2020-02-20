#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "laser.h"
#include "trajectory.h"
#include "position.h"

struct Robot
{
    Robot(Position pos);
    vector<Laser> lasers;
    vector<Trajectory> trajectories;
    vector<Segment> closest_segments;
    Position position;

    void laser_scan(Position pos);
    void wheel_encode();
};

#endif
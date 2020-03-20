#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include "segment.h"


struct Trajectory
{
    Trajectory();

    std::vector<Vec2f> trajectories;
};

#endif
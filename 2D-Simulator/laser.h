#ifndef LASER_H
#define LASER_H

#include "math.h"
#include "segment.h"
#include "position.h"
#include "noise.h"

struct Laser
{
    Laser();
    const float FOV_degree = 180;
    const float FOV_radian = FOV_degree * (M_PI / 180.0);
    const float range_min = 0.2;
    const float range_max = 10;
    const float ray_length = range_max - range_min;
    const int num_total_rays = 18;
    const float angular_resolution_radian = FOV_radian / num_total_rays;
    const float angular_resolution_degree = FOV_degree / num_total_rays;

    Segment create_a_ray(Position pos, float angle, Noise &length_noise, Noise &angle_noise);
};

#endif
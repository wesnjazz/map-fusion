#ifndef LASER_H
#define LASER_H

#include "segment.h"
#include "position.h"
#include "noise.h"


struct Laser
{
    Laser();
    const float FOV_degree = 270;
    const float FOV_radian = FOV_degree * (M_PI / 180.0);
    const float range_min = 0.2;
    const float range_max = 1;
    const float ray_length = range_max - range_min;
    const int num_total_rays = 1080;
    const int frequency = 5;
    const float angular_resolution_radian = FOV_radian / num_total_rays;
    const float angular_resolution_degree = FOV_degree / num_total_rays;

    Segment create_a_ray(Vec2f &start, float angle, Noise &length_noise, Noise &angle_noise);
};

#endif
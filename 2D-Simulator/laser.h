#ifndef LASER_H
#define LASER_H

#include "segment.h"


struct Laser
{
    Laser();
    float FOV;
    float range_min;
    float range_max;
    int num_total_rays;
    float angular_resolution;
    float noise_mean;
    float noise_sigma;

    vector<Segment> rays;

    int add_ray(Segment ray);
};

#endif
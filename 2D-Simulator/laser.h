#ifndef LASER_H
#define LASER_H

#include <vector>
#include "segment.h"
#include "position.h"


struct Laser
{
    Laser(Position pos);
    float FOV;
    float FOV_degree;
    float range_min;
    float range_max;
    float ray_length;
    int num_total_rays;
    float angular_resolution;
    float noise_mean;
    float noise_sigma;
    Position position;

    vector<Segment> rays;

    void create_rays();
    int add_ray(Segment ray);
    void print_rays();
};

#endif
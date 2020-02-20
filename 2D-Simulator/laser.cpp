#include "laser.h"


Laser::Laser()
{
    FOV = 270;
    range_min = 0.2;
    range_max = 10.0;
    num_total_rays = 1080;
    angular_resolution = num_total_rays / FOV;
    noise_mean = 0.0;
    noise_sigma = 0.02;
}


int Laser::add_ray(Segment ray)
{
    rays.push_back(ray);
    if (rays.size() > num_total_rays) {
        rays.erase(rays.begin(), rays.begin()+1);
    }
    return rays.size();
}
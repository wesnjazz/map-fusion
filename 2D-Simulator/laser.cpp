#include "laser.h"

Laser::Laser(Position pos)
{
    FOV_degree = 30;
    // FOV = 270;
    FOV = FOV_degree * (M_PI/180.0);
    range_min = 0.2;
    range_max = 10.0;
    ray_length = range_max - range_min;
    num_total_rays = 30;
    angular_resolution = FOV / num_total_rays;
    noise_mean = 0.0;
    noise_sigma = 0.02;
    position = pos;
}

void Laser::create_rays()
{
    float angle = position.theta - (FOV / 2.0);
    for(int i = 1; i <= num_total_rays; ++i) {
        Segment *seg = new Segment(position.pos_vec2f, ray_length, angle);
        cout << angle << "\n";
        cout << *seg << "\n";
        add_ray(*seg);
        angle += angular_resolution;
        cout << angle << "\n\n";
    }
}

int Laser::add_ray(Segment ray)
{
    rays.push_back(ray);
    if (rays.size() > num_total_rays) {
        rays.erase(rays.begin(), rays.begin()+1);
    }
    return rays.size();
}

void Laser::print_rays()
{
    int count = 1;
    for(vector<Segment>::iterator it = rays.begin(); it != rays.end(); it++) {
        cout << "ray[" << count++ << "]:" << *it << "\n";
    }
}
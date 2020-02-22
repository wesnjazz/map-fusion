#include "laser.h"

// Laser::Laser(Position pos)
// {
//     position = pos;
// }

// void Laser::create_rays()
// {
//     float angle = position.theta - (LaserParameter::FOV / 2.0);
//     for(int i = 1; i <= num_total_rays; ++i) {
//         Segment *seg = new Segment(position.pos_vec2f, ray_length, angle);
//         cout << angle << "\n";
//         cout << *seg << "\n";
//         add_ray(*seg);
//         angle += angular_resolution;
//         cout << angle << "\n\n";
//     }
// }

// int Laser::add_ray(Segment ray)
// {
//     rays.push_back(ray);
//     if (rays.size() > num_total_rays) {
//         rays.erase(rays.begin(), rays.begin()+1);
//     }
//     return rays.size();
// }

// void Laser::print_rays()
// {
//     int count = 1;
//     for(vector<Segment>::iterator it = rays.begin(); it != rays.end(); it++) {
//         cout << "ray[" << count++ << "]:" << *it << "\n";
//     }
// }
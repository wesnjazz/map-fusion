#include "laser.h"

Laser::Laser()
{
    // noise = Noise(0.0, 0.0);
    ;
}

Segment Laser::create_a_ray(Position pos, float angle, Noise &length_noise, Noise &angle_noise)
{
    double ln = length_noise.gaussian();
    double noisy_length = this->ray_length + ln;
    // double noisy_length = this->ray_length + length_noise.gaussian();
    cout << "noisy_length: " << noisy_length << "\tnoise: " << ln << "\t\t(mean, std): (" << length_noise.mean << ", " << length_noise.std << ")" << endl;
    double an = angle_noise.gaussian();
    double noisy_angle_degree = pos.theta_degree + angle + an;
    // double noisy_angle_degree = pos.theta_degree + angle + angle_noise.gaussian();
    cout << "noisy_angle: " << noisy_angle_degree << "\tnoise: " << an << "\t\t(mean, std): (" << angle_noise.mean << ", " << angle_noise.std << ")" << endl;
    Segment ray = Segment(pos.position_vector, noisy_length, noisy_angle_degree);
    // Segment ray = Segment(pos.position_vector, this->ray_length, pos.theta_degree + angle);
    return ray;
}

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
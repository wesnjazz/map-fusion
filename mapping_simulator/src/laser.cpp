#include <iostream>
#include "segment.h"
#include "noise.h"
#include "laser.h"


Laser::Laser()
{
    ;
}


Segment Laser::create_a_ray(Vec2f &start, float angle, Noise &length_noise, Noise &angle_noise)
{
    float ln = length_noise.gaussian();
    float noisy_length = this->ray_length + ln;
    // cout << "noisy_length: " << noisy_length << "\tnoise: " << ln << "\t\t(mean, std): (" << length_noise.mean << ", " << length_noise.std << ")" << endl;
    float an = angle_noise.gaussian();
    float noisy_angle_degree = angle + an;
    // cout << "noisy_angle: " << noisy_angle_degree << "\tnoise: " << an << "\t\t(mean, std): (" << angle_noise.mean << ", " << angle_noise.std << ")" << endl;
    Segment ray = Segment(start, noisy_length, noisy_angle_degree);
    return ray;
}
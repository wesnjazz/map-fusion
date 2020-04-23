#ifndef WHEELENCODER_H
#define WHEELENCODER_H

#include <iostream>
#include "noise.h"


struct WheelEncoder 
{
    WheelEncoder();

    float dx;
    float dy;
    float dtheta_degree;
    float dtheta_radian;

    void simulate_odometry(float speed, float time, float dx_noise, float dy_noise);
};


#endif
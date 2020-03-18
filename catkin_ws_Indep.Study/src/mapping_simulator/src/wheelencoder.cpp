#include "wheelencoder.h"
#include "simulator.h"


WheelEncoder::WheelEncoder()
{
    this->dx = 0.0;
    this->dy = 0.0;
    this->dtheta_radian = 0.0;
    this->dtheta_degree = 0.0;
}


void WheelEncoder::simulate_odometry(float speed, float time, float dx_noise, float dy_noise)
{
    dx_noise = cut_redundant_epsilon( fabs(dx_noise) );
    this->dx = cut_redundant_epsilon( speed * time + dx_noise );
    this->dy = dy_noise;
    cout << "dx, dy: " << this->dx << ", " << this->dy << endl;
    // this->dy = cut_redundant_epsilon( speed * time + dy_noise );
    this->dtheta_radian = cut_redundant_epsilon( atan2( this->dy, this->dx ) );
    this->dtheta_degree = cut_redundant_epsilon( radian_to_degree(this->dtheta_radian) );
    cout << "dtheta: " << this->dtheta_radian << ", " << this->dtheta_degree << endl;
}

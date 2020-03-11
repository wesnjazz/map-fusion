#include "noise.h"
#include <chrono>
#include <random>
using namespace std;


Noise::Noise()
{
    mean = 0.0;
    std = 0.0;
}

Noise::Noise(float mean, float std)
{
    this->mean = mean;
    this->std = std;
}

void Noise::change_mean_std(float mean, float std)
{
    this->mean = mean;
    this->std = std;
}

float Noise::gaussian()
{
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<float> distribution(mean, std);
    return distribution(generator);
}
#include "noise.h"
#include <chrono>
#include <random>
using namespace std;


Noise::Noise()
{
    mean = 0.0;
    std = 0.0;
}

Noise::Noise(double mean, double std)
{
    this->mean = mean;
    this->std = std;
}

void Noise::change_mean_std(double mean, double std)
{
    this->mean = mean;
    this->std = std;
}

double Noise::gaussian()
{
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean, std);
    return distribution(generator);
}
#ifndef NOISE_H
#define NOISE_H


struct Noise
{
    Noise();
    Noise(double mean, double std);
    double mean;
    double std;
    unsigned seed;

    void change_mean_std(double mean, double std);
    double gaussian();
};

#endif
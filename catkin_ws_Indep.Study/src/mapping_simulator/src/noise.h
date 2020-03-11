#ifndef NOISE_H
#define NOISE_H


struct Noise
{
    Noise();
    Noise(float mean, float std);
    float mean;
    float std;
    unsigned seed;

    void change_mean_std(float mean, float std);
    float gaussian();
};

#endif
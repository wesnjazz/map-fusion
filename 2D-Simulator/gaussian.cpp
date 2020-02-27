#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int main(int argc, char **argv)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    double mean = 5.0;
    double sigma = 2.0;
    normal_distribution<double> distribution(mean, sigma);
    cout << generator << "\n";
    cout << distribution << "\n";
    cout << distribution(generator) << "\n";
    
    int nrolls = 10000;
    int nstars = 100;
    
    int p[10] = {};
    for (int i=0; i<nrolls; ++i) {
        double number = distribution(generator);
        if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
    }

    cout << "normal_distribution (" << mean << ", " << sigma << "): " << endl;

    for (int i=0; i<10; ++i) {
        cout << i << "-" << (i+1) << ": ";
        cout << string(p[i]*nstars/nrolls, '*') << endl;
    }

    return 0;
}
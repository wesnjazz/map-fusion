#include <iostream>
#include <string>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv)
{
    CImg<unsigned char> img(1024,768,1,3,0);
    for (int i=0; i<100; ++i)
    {
        for (int j=0; j<100; ++j)
        {
            img(i,j,0) = 255;
            img(i,j,1) = 255;
            img(i,j,2) = 255;
        }
    }
    string s = "test.jpg";
    img.save_jpeg(s.c_str());

    return 0;
}
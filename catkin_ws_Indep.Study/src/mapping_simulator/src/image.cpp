#include <string>
#include "image.h"
#include "CImg.h"

// save_map
using namespace cimg_library;

void save_map(vector<vector<Vec2f>> &point_clouds, string img_filename)
{
    float x_max = -987654321;
    float x_min =  987654321;
    float y_max = -987654321;
    float y_min =  987654321;
    for(vector<vector<Vec2f>>::iterator its = point_clouds.begin(); its != point_clouds.end(); ++its)
    {
        for(vector<Vec2f>::iterator it = its->begin(); it != its->end(); ++it)
        {
            float x = it->x();
            float y = it->y();
            if (x > x_max) { x_max = x; }
            if (x < x_min) { x_min = x; }
            if (y > y_max) { y_max = y; }
            if (y < y_min) { y_min = y; }
        }
    }
    cout
        << "x_max: " << x_max << endl
        << "x_min: " << x_min << endl
        << "y_max: " << y_max << endl
        << "y_min: " << y_min << endl;

    int margin = 10;
    int img_width = (int)(fabs(x_max - x_min));
    int img_height = (int)(fabs(y_max - y_min));
    int color_channel = 3;
    int default_color = 0;
    CImg<unsigned char> img(img_width + margin, img_height + margin, 1, color_channel, default_color);

    for(vector<vector<Vec2f>>::iterator its = point_clouds.begin(); its != point_clouds.end(); ++its)
    {
        for(vector<Vec2f>::iterator it = its->begin(); it != its->end(); ++it)
        {
            int x_grid = (int)it->x() - x_min + margin/2;
            int y_grid = (int)it->y() - y_min + margin/2;
            img(x_grid, y_grid, 0) = 255;
            img(x_grid, y_grid, 1) = 255;
            img(x_grid, y_grid, 2) = 255;
        }
    }
    img.save_jpeg(img_filename.c_str());
}
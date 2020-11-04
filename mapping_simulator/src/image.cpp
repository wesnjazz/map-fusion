#include <string>
#include "image.h"
#include "CImg.h"
#include "segment.h"

// save_map
using namespace cimg_library;

void save_map(vector<vector<Vec2f>> &point_clouds,  Mat3f &HT_World_frame_to_Robot_frame, string img_filename, int img_scale)
{
    float x_max = -987654321;
    float x_min =  987654321;
    float y_max = -987654321;
    float y_min =  987654321;
    for(vector<vector<Vec2f>>::iterator its = point_clouds.begin(); its != point_clouds.end(); ++its)
    {
        for(vector<Vec2f>::iterator it = its->begin(); it != its->end(); ++it)
        {
            Vec3f transformed_point = HT_World_frame_to_Robot_frame * it->homogeneous();
            float x = transformed_point.x();
            float y = transformed_point.y();
            if (x > x_max) { x_max = x; }
            if (x < x_min) { x_min = x; }
            if (y > y_max) { y_max = y; }
            if (y < y_min) { y_min = y; }
        }
    }
    int margin = 10;
//    int img_scale = 50;
//    int margin = 0;
//    int img_scale = 1;
    int pixel_size = 1;
    int img_width =  (int)(fabs(x_max - x_min)*img_scale);
    int img_height = (int)(fabs(y_max - y_min)*img_scale);
    int color_channel = 3;
    int default_color = 0;
    cout
        << "\nMap output saving into an image." << endl
        << "Filename: [" << img_filename << "]" << endl
        << "img_scale: " << img_scale << "\t"
        << "img_width: " << img_width << "\t"
        << "img_height: " << img_height << endl
        << "x_max: " << x_max << "\t"
        << "x_min: " << x_min << "\t"
        << "y_max: " << y_max << "\t"
        << "y_min: " << y_min << endl;

    CImg<unsigned char> img(img_width + margin, img_height + margin, 1, color_channel, default_color);

    for(vector<vector<Vec2f>>::iterator its = point_clouds.begin(); its != point_clouds.end(); ++its)
    {
        for(vector<Vec2f>::iterator it = its->begin(); it != its->end(); ++it)
        {
            Vec3f transformed_point = HT_World_frame_to_Robot_frame * it->homogeneous();
            /** Scaled **/
            int y_grid = ((int)((transformed_point.y())*img_scale)) - (int)(y_min*img_scale) + (margin/2);
            int x_grid = ((int)((transformed_point.x())*img_scale)) - (int)(x_min*img_scale) + (margin/2);
            /** Not scaled - 1:1 **/
//             int x_grid = ((int)((transformed_point.x()))) - (int)(x_min);
//             int y_grid = ((int)((transformed_point.y()))) - (int)(y_min);

//             img(x_grid, y_grid, 0) = 255;
//             img(x_grid, y_grid, 1) = 255;
//             img(x_grid, y_grid, 2) = 255;
            for(int i = 0; i < pixel_size; ++i)
            {
                for(int j = 0; j < pixel_size; ++j)
                {
                    img(x_grid + i, y_grid + j, 0) = 255;
                    img(x_grid + i, y_grid + j, 1) = 255;
                    img(x_grid + i, y_grid + j, 2) = 255;
                }
            }
        }
    }
    img.mirror('y').save_jpeg(img_filename.c_str());
}
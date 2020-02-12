#ifndef SEGMENT_H
#define SEGMENT_H

#include <iostream>
#include <math.h>
#include <Eigen/Dense>
using namespace std;

typedef Eigen::Vector2f Vec2f;
typedef Eigen::Hyperplane<float, 2> Line;

// For accurate comparison between floats
// bool cmpf(float A, float B, float epsilon = 0.005f)
// {
//     return (fabs(A - B) < epsilon);
// }

struct Segment
{
    Segment(Vec2f start, Vec2f end)
    {
        p1 = start;
        p2 = end;
        calculate_members();
    }
    Vec2f p1;
    Vec2f p2;
    float x_difference;
    float y_difference;
    Line segment;
    float angle_radian;
    float angle_degree;
    Eigen::Rotation2D<float> rotation;
    
    double length;
    int orientation;

    void calculate_members()
    {
        x_difference = p2.x()-p1.x();
        y_difference = p2.y()-p1.y();
        length = abs(sqrt((pow(x_difference,2.0) + pow(y_difference,2.0))));
        angle_radian = atan2(y_difference, x_difference);
        angle_degree = angle_radian * (180.0/M_PI);
        segment = Line::Through(p1, p2);
    }

    Vec2f intersect(const Segment &seg2)
    {
        Vec2f intersect = segment.intersection(seg2.segment);
        float x = intersect.x();
        float y = intersect.y();
        cout << intersect.x() << " " << intersect.y() << "\n";

        float seg1_min_x = min(p1.x(), p2.x());
        float seg1_max_x = max(p1.x(), p2.x());
        float seg1_min_y = min(p1.y(), p2.y());
        float seg1_max_y = max(p1.y(), p2.y());
        float seg2_min_x = min(seg2.p1.x(), seg2.p2.x());
        float seg2_max_x = max(seg2.p1.x(), seg2.p2.x());
        float seg2_min_y = min(seg2.p1.y(), seg2.p2.y());
        float seg2_max_y = max(seg2.p1.y(), seg2.p2.y());
        bool inter = seg1_min_x <= x && x <= seg1_max_x 
                    && seg1_min_y <= y && y <= seg1_max_y
                    && seg2_min_x <= x && x <= seg2_max_x 
                    && seg2_min_y <= y && y <= seg2_max_y;

        cout << "intersect?: ";
        string result = inter==true ? "Yes" : "No";
        cout << result << "\n";
        return intersect;
    }

    friend std::ostream& operator<<(std::ostream& os, const Segment &sg)
    {
        double x = sg.p2.x()-sg.p1.x();
        double x2 = pow(x,2.0);
        double y = sg.p2.y()-sg.p1.y();
        double y2 = pow(y,2.0);
        double z = sqrt(x2+y2);
        os << "[" << to_string(sg.p1.x()) << "," << to_string(sg.p1.y()) << "]";
        os << "->";
        os << "[" << to_string(sg.p2.x()) << "," << to_string(sg.p2.y()) << "]";
        os << "\nlength:" << sg.length << "\tangle_radian:" << sg.angle_radian << "\tangle_degree:" << sg.angle_degree;
        // os << "\n" << sg.p1.se;
        // os << "\n" << sg.segment;
        // os << "\n" << sg.p2.x() << "-" << sg.p1.x() << "=" << x << "\t" << x2;
        // os << "\n" << sg.p2.y() << "-" << sg.p1.y() << "=" << x << "\t" << y2;
        // os << "\t" << z << "\t" << abs(z);
        return os;
    }
};

#endif
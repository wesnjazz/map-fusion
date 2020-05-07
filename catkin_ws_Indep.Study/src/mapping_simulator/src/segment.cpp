#include <iostream>
#include "segment.h"
#include "simulator.h"
using namespace std;


Segment::Segment(Vec2f p1, Vec2f p2)
{
    start = p1;
    end = p2;
    calculate_members();
}


Segment::Segment(Vec2f start, float length, float angle_degree)
{
    this->start = start;
    this->angle_radian = angle_degree * (M_PI / 180.0);
    float length_x = cut_redundant_epsilon(cos(angle_radian));
    float length_y = cut_redundant_epsilon(sin(angle_radian));
    float end_x = start.x() + length * length_x;
    float end_y = start.y() + length * length_y;
    this->end = Vec2f(end_x, end_y);
    calculate_members();
}


void Segment::calculate_members()
{
    segment = end - start;  // Get a vector of the line
    segment_unit = segment.normalized();    // Unit vector
    segment_norm_unit = segment.unitOrthogonal();   // Normal Unit vector
    remove_small_error_values(segment_unit);    // Replace very small number with zero
    remove_small_error_values(segment_norm_unit);

    x_diff = end.x()-start.x();     // Difference of x coordinate
    y_diff = end.y()-start.y();     // Difference of y coordinate
    angle_radian = atan2(y_diff, x_diff);  // Angle (Direction) of the line vector
    angle_degree = angle_radian * (180.0/M_PI);
    length = abs(sqrt((pow(x_diff,2.0) + pow(y_diff,2.0))));    // Length of the line

    float x1 = this->start.x();
    float y1 = this->start.y();
    float x3 = this->end.x();
    float y3 = this->end.y();
    float x2 = (x1 + x3) / 2.0f;
    float y2 = (y1 + y3) / 2.0f;
    this->mid = Vec2f(x2, y2);
}


bool Segment::isParallel(const Segment &seg2)
{
    float dot_product = (segment_unit).dot(seg2.segment_norm_unit);     // Parallel if dot product is zero
    return (dot_product == 0.0) ? true : false;
}


bool Segment::ifIntersect(const Segment &seg2)
{
    // t: The distance on the segment line 1 to the intersecting point with segment 2
    // u: The distance on the segment line 2 to the intersecting point with segment 1
    // If t and u both are less or equal to itselves, then two line segments intersect!
    // if ((0.0 < t && t <= length)) {
    //     cout << "\t\tIntersect! at\n";
    // }
    // return (0.0 < t && t <= length);

    // if ((0.0 < t && t <= length) && (0.0 < seg2.t && seg2.t <= seg2.length)) {
    //     cout << "\t\tIntersect! at\n";
    // }
    return (0.0 < t && t <= length) &&
            (0.0 < seg2.t && seg2.t <= seg2.length);
}


Vec2f Segment::intersection_point(Segment &seg2)
{
    t = (seg2.start - start).dot(seg2.segment_norm_unit) / (segment_unit).dot(seg2.segment_norm_unit);
    seg2.t = (start - seg2.start).dot(segment_norm_unit) / (seg2.segment_unit).dot(segment_norm_unit);
    Vec2f intersect_vector = start + t*(segment_unit);
    // cout << "\nt:" << t << "\tu:" << seg2.t << "\n";
    remove_small_error_values(intersect_vector);
    return intersect_vector;
}


void Segment::remove_small_error_values(Vec2f &vec)     // Replace very small number with zero
{
    vec = Vec2f(cut_redundant_epsilon(vec.x()), vec.y());
    vec = Vec2f(vec.x(), cut_redundant_epsilon(vec.y()));
    // if (fabs(vec.x()) < 0.00001) { vec = Vec2f(0, vec.y()); }    
    // if (fabs(vec.y()) < 0.00001) { vec = Vec2f(vec.x(), 0); }
}



float Segment::distance_between_segments(Segment &seg2)
{
    float mid_point_seg_01_x = this->mid.x();
    float mid_point_seg_01_y = this->mid.y();
    float mid_point_seg_02_x = seg2.mid.x();
    float mid_point_seg_02_y = seg2.mid.y();
    float x_diff_pow2 = pow(fabs(mid_point_seg_01_x - mid_point_seg_02_x), 2.0);
    float y_diff_pow2 = pow(fabs(mid_point_seg_01_y - mid_point_seg_02_y) ,2.0);
    float distance =sqrt(x_diff_pow2 + y_diff_pow2);
    return distance;
    // float x1_pivot = this->start.x();
    // float y1_pivot = this->start.y();
    // float x3_pivot = this->end.x();
    // float y3_pivot = this->end.y();
    // float x2_pivot = (x1_pivot + x3_pivot) / 2.0f;
    // float y2_pivot = (y1_pivot + y3_pivot) / 2.0f;
    // float x1_target = seg2.start.x();
    // float y1_target = seg2.start.y();
    // float x3_target = seg2.end.x();
    // float y3_target = seg2.end.y();
    // float x2_target = (x1_target + x3_target) / 2.0f;
    // float y2_target = (y1_target + y3_target) / 2.0f;

}
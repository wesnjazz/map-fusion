#include "segment.h"


Segment::Segment(Vec2f p1, Vec2f p2)
{
    start = p1;
    end = p2;
    calculate_members();
}

Segment::Segment(Vec2f st, float length, float angle_degree)
{
    start = st;
    float angle_radian = angle_degree * (M_PI / 180.0);
    float end_x = st.x() + length * cos(angle_radian);
    float end_y = st.y() + length * sin(angle_radian);
    end = Vec2f(end_x, end_y);
    calculate_members();
}

void Segment::calculate_members()
{
    segment = end - start;
    segment_unit = segment.normalized();
    segment_norm_unit = segment.unitOrthogonal();
    x_diff = end.x()-start.x();
    y_diff = end.y()-start.y();
    angle = atan2(y_diff, x_diff);
    angle_degree = angle * (180.0/M_PI);
    length = abs(sqrt((pow(x_diff,2.0) + pow(y_diff,2.0))));
}


bool Segment::isParallel(const Segment &seg2)
{
    float dot_product = (segment_unit).dot(seg2.segment_norm_unit);
    cout << "isParallel(dot_product):" << dot_product << "\n";
    if (fabs(dot_product) < 0.0000001) { cout << "Parallel!\n"; }
    return (dot_product == 0.0) ? true : false;
}


bool Segment::ifIntersect(const Segment &seg2)
{
    if ((0.0 < t && t <= length) && (0.0 < seg2.t && seg2.t <= seg2.length)) {
        cout << "\t\tIntersect!\n";
    }
    return (0.0 < t && t <= length) &&
            (0.0 < seg2.t && seg2.t <= seg2.length);
}


Vec2f Segment::intersection_point(Segment &seg2)
{
    t = (seg2.start - start).dot(seg2.segment_norm_unit) / (segment_unit).dot(seg2.segment_norm_unit);
    seg2.t = (start - seg2.start).dot(segment_norm_unit) / (seg2.segment_unit).dot(segment_norm_unit);
    Vec2f intersect_vector = start + t*(segment_unit);

    cout << "t:" << t << "\n";
    cout << "u:" << seg2.t << "\n";
    // cout << "acrossb:\n" << acrossb << "\n";

    return intersect_vector;
}
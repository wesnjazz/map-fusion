#include "segment.h"

Segment::Segment(Vec2f p1, Vec2f p2)
{
    start = p1;
    end = p2;
    calculate_members();
}

void Segment::calculate_members()
{
    segment = end - start;
    segment_unit = segment.normalized();
    segment_unit_norm = segment.unitOrthogonal();

    // segment = Line::Through(p1, p2);
    x_diff = end.x()-start.x();
    y_diff = end.y()-start.y();
    angle = atan2(y_diff, x_diff);
    angle_degree = angle * (180.0/M_PI);
    length = abs(sqrt((pow(x_diff,2.0) + pow(y_diff,2.0))));
}

// Vec2f Segment::intersect2(const Segment &seg2)
// {
//     // Intersecting point of two segments(hyperplanes) between this(seg1) & seg2
//     Vec2f intersect = Vec2f(0,0,0);
//     // Vec2f intersect = segment.intersection(seg2.segment);

//     float seg1_min_x = min(start.x(), end.x());
//     float seg1_max_x = max(start.x(), end.x());
//     float seg1_min_y = min(start.y(), end.y());
//     float seg1_max_y = max(start.y(), end.y());
//     float seg2_min_x = min(seg2.start.x(), seg2.end.x());
//     float seg2_max_x = max(seg2.start.x(), seg2.end.x());
//     float seg2_min_y = min(seg2.start.y(), seg2.end.y());
//     float seg2_max_y = max(seg2.start.y(), seg2.end.y());
//     bool inter = seg1_min_x <= intersect.x() && intersect.x() <= seg1_max_x 
//     && seg1_min_y <= intersect.y() && intersect.y() <= seg1_max_y
//     && seg2_min_x <= intersect.x() && intersect.x() <= seg2_max_x 
//     && seg2_min_y <= intersect.y() && intersect.y() <= seg2_max_y;

//     cout << "intersect?: ";
//     string result = inter==true ? "Yes" : "No";
//     cout << result << "\n";
//     return intersect;
// }

Vec2f Segment::intersection_point(Segment &seg2)
{
    this->t = (seg2.start - this->start).dot(seg2.segment_unit_norm) / (this->segment_unit).dot(seg2.segment_unit_norm);
    seg2.t = (this->start - seg2.start).dot(this->segment_unit_norm) / (seg2.segment_unit).dot(this->segment_unit_norm);
    Vec2f intersect_vector = this->start + t*(this->segment_unit);

    cout << "t:" << t << "\n";
    cout << "u:" << seg2.t << "\n";
    // cout << "acrossb:\n" << acrossb << "\n";

    return intersect_vector;
}

bool Segment::ifIntersect(const Segment &seg2)
{
    float a = (this->segment_unit).dot(seg2.segment_unit_norm);
    cout << "ifIntersect:" << a << "\n";
    return a;
}

// bool Segment::intersetcion_check(const Segment &seg2)
// {
//     cout << "t:" << t << "\n";
//     cout << "u:" << u << "\n";
//     cout << "acrossb:\n" << acrossb << "\n";

// }
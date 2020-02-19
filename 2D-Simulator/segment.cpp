#include "segment.h"

Segment::Segment(Vec2f start, Vec2f end)
{
    p1 = start;
    p2 = end;
    calculate_members();
}

void Segment::calculate_members()
{
    segment = Line::Through(p1, p2);
    x_difference = p2.x()-p1.x();
    y_difference = p2.y()-p1.y();
    angle = atan2(y_difference, x_difference);
    angle_degree = angle * (180.0/M_PI);
    length = abs(sqrt((pow(x_difference,2.0) + pow(y_difference,2.0))));
}

Vec2f Segment::intersect(const Segment &seg2)
{
    // Intersecting point of two segments(hyperplanes) between this(seg1) & seg2
    Vec2f intersect = segment.intersection(seg2.segment);

    float seg1_min_x = min(p1.x(), p2.x());
    float seg1_max_x = max(p1.x(), p2.x());
    float seg1_min_y = min(p1.y(), p2.y());
    float seg1_max_y = max(p1.y(), p2.y());
    float seg2_min_x = min(seg2.p1.x(), seg2.p2.x());
    float seg2_max_x = max(seg2.p1.x(), seg2.p2.x());
    float seg2_min_y = min(seg2.p1.y(), seg2.p2.y());
    float seg2_max_y = max(seg2.p1.y(), seg2.p2.y());
    bool inter = seg1_min_x <= intersect.x() && intersect.x() <= seg1_max_x 
    && seg1_min_y <= intersect.y() && intersect.y() <= seg1_max_y
    && seg2_min_x <= intersect.x() && intersect.x() <= seg2_max_x 
    && seg2_min_y <= intersect.y() && intersect.y() <= seg2_max_y;

    cout << "intersect?: ";
    string result = inter==true ? "Yes" : "No";
    cout << result << "\n";
    return intersect;
}

Vec2f Segment::intersect2(const Segment &seg2)
{
    ;
}
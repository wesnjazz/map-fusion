#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <Eigen/Core>
using namespace std;

struct Line
{
    Line(Eigen::Vector2f start, Eigen::Vector2f end)
    {
        p1 = start;
        p2 = end;
    }
    Eigen::Vector2f p1;
    Eigen::Vector2f p2;
    double length;
    int orientation;

    // std::ostream& operator<<(std::ostream& os)
    // std::string operator<<(const Line &l)
    // {
    //     // os << p1.x();
    //     std::string temp_str;
    //     temp_str = "(" + std::to_string(p1.x()) + "," + std::to_string(p1.y()) + ")";
    //     return temp_str;
    //     // return os;
    // }

    friend std::ostream& operator<<(std::ostream& os, const Line &l)
    {
        string temp_str1;
        string temp_str2;
        string temp_str3;
        temp_str1 = "[" + to_string(l.p1.x()) + "," + to_string(l.p1.y()) + "]";
        temp_str2 = "[" + to_string(l.p2.x()) + "," + to_string(l.p2.y()) + "]";
        temp_str3 = temp_str1 + " -> " + temp_str2;
        os << temp_str3;
        return os;
    }
};

#endif
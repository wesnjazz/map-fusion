#include <iostream>
#include "segment.h"
#include <Eigen/Dense>
using namespace std;

typedef Eigen::Vector2f Vec2f;

int main(int argv, char **args)
{
    Vec2f a = Vec2f(3, 6);
    Segment wall1 = Segment(Vec2f(0.0, 0.0), Vec2f(10.0, 0.0));
    Segment wall2 = Segment(Vec2f(10.0, 0.0), Vec2f(10.0, 5.0));
    Segment wall3 = Segment(Vec2f(10.0, 5.0), Vec2f(20.0, 5.0));
    Segment wall4 = Segment(Vec2f(20.0, 5.0), Vec2f(20.0, 10.0));
    Segment wall5 = Segment(Vec2f(0.0, 0.0), Vec2f(0.0, 20.0));
    Segment wall6 = Segment(Vec2f(0.0, 10.0), Vec2f(20.0, 10.0));
    Segment seg5 = Segment(Vec2f(5.0, 5.0), Vec2f(20.0, 10.0));
    Segment seg6 = Segment(Vec2f(0.0, 0.0), Vec2f(3.0, 4.0));
    // cout << seg5 << "\n";
    // cout << seg6 << "\n";

    // Segment ray1 = Segment(Vec2f(-10.0, 0.0), Vec2f(2.0, 0.0));
    // cout << wall2 << "\n";
    // cout << ray1 << "\n";
    // cout << ray1.intersect(wall2) << "\n";

    // 10.0 && 9.9999995 == false
    // 10.0 && 9.9999996 == true
    Segment ray2 = Segment(Vec2f(0.0, 0.0), Vec2f(1.23567, 9.9999995));
    cout << wall6 << "\n";
    cout << ray2 << "\n";
    cout << ray2.intersect(wall6) << "\n";
}
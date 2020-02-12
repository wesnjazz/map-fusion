#include <iostream>
#include "line.h"
using namespace std;

typedef Eigen::Vector2f Vec2f;

int main(int argv, char **args)
{
    Vec2f a = Vec2f(3, 6);
    Line seg1 = Line(Vec2f(0.0, 0.0), Vec2f(10.0, 0.0));
    Line seg2 = Line(Vec2f(10.0, 0.0), Vec2f(10.0, 5.0));
    Line seg3 = Line(Vec2f(10.0, 5.0), Vec2f(20.0, 5.0));
    Line seg4 = Line(Vec2f(20.0, 5.0), Vec2f(20.0, 10.0));
    Line seg5 = Line(Vec2f(5.0, 5.0), Vec2f(20.0, 10.0));
    Line seg6 = Line(Vec2f(0.0, 0.0), Vec2f(3.0, 4.0));
    // cout << a.y();
    cout << seg5 << "\n";
    cout << seg6 << "\n";
}
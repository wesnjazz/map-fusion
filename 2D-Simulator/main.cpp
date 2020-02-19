#include <iostream>
#include <fstream>
#include <vector>
#include "segment.h"
#include <Eigen/Dense>

using namespace std;
typedef Eigen::Vector2f Vec2f;
void test();
void test2();

/** Todo 
 * Read map data
 * Read rays data
 * Robot Poses (x, y, theta)
 * Segment operator<< into cpp file
 * 
 * **/

int usage(char *app_name) {
    cout << "Usage: " << app_name << " [text file]\n";
    cout << "Options:\n";
    cout << "  -p\t\t\tpause on every line\n\n";
    exit(0);
}

void read_segments(ifstream &seg_file, vector<Segment> *segs)
{
    Vec2f p1 = Vec2f(0,0);
    Vec2f p2 = Vec2f(0,0);
    Segment seg = Segment(p1, p2);
    int x, y;
    int count = 0;
    string line;
    while(getline(seg_file, line)) {
        stringstream ss(line);
        while(getline(ss, line, ',')) {
            count++;
            switch (count)
            {
            case 1: x = stoi(line); break;
            case 2: y = stoi(line); p1 = Vec2f(x, y); break;
            case 3: x = stoi(line); break;
            case 4: 
                y = stoi(line);
                p2 = Vec2f(x, y);
                count = 0;
                // Segment seg = Segment(p1, p2);
                seg = Segment(p1, p2);
                segs->push_back(seg);
                break;
            default: break;
            }
        }
    }
}

int main(int argc, char **argv)
{
    vector<Segment> map;
    vector<Segment> rays;
    ifstream map_file;
    ifstream rays_file;

    // Check number of arguments
    if (argc <= 1 || 4 <= argc) {
        usage(argv[0]);
    }
    if (argc >= 2) { map_file = ifstream(argv[1]); }
    if (argc >= 3) { rays_file = ifstream(argv[2]); }
    if (!map_file && !rays_file) {
        cout << "The file [";
        if (!map_file) { cout << argv[1]; }
        if (!rays_file) { cout << ", " << argv[2]; }
        cout << "] doesn't exists.\n\n";
        exit(0);
    }

    read_segments(map_file, &map);
    read_segments(rays_file, &rays);
    // for (vector<Segment>::iterator it = map.begin(); it != map.end(); ++it) {
    //     cout << *it << "\n";
    // }
    // for (vector<Segment>::iterator it = rays.begin(); it != rays.end(); ++it) {
    //     cout << *it << "\n";
    // }

    test2();

    // Print text file line by line
    // string line;
    // flush();
    // while(getline(infile, line)) {
    //     cout << line << endl;
    // }

    // infile.close();
    return 0;
}

void test2()
{
    Segment va = Segment(Vec2f(1,5), Vec2f(6,6));
    Segment vb = Segment(Vec2f(4,8), Vec2f(10,4));

    /**
     * as: a vector of va's starting point
     * ad: a unit, direction vector of vector va
     * 
     * parametrinc representation
     * va = as + t(ad)
     * vb = bs + u(bd)
     * 
     * va = [as_x as_y]^T + t[ad_x ad_y]^T
     * vb = [bs_x bs_y]^T + u[bd_x bd_y]^T
     * 
     * p: intersection point
     * as + t(ad) = bs + u(bd)
     * =>
     * as_x + t(ad_x) = bs_x + u(bd_x)   - 1)
     * as_y + t(ad_y) = bs_y + u(bd_y)   - 2)
     * => from 1) t:
     * t(ad_x) = bs_x + u(bd_x) - as_x
     * t = [bs_x + u(bd_x) - as_x] / ad_x
     * => from 2) u:
     * u(bd_y) = as_y + t(ad_y) - bs_y
     * u = (as_y + t(ad_y) - bs_y) / bd_y
     * => substitute
     * 
     * as_y + ([bs_x + u(bd_x) - as_x] / ad_x)(ad_y) = bs_y + u(bd_y)
     * (as_y)(ad_y) + ([bs_x + u(bd_x) - as_x] / ad_x) = (bs_y)(ad_y) + u(bd_y)(ad_y)
     * (as_y)(ad_y)(ad_x) + [bs_x + u(bd_x) - as_x] = (bs_y)(ad_y)(ad_x) + u(bd_y)(ad_y)(ad_x)
     * u(bd_y)(ad_y)(ad_x) - u(bd_x) = (as_y)(ad_y)(ad_x) + bs_x - as_x - (bs_y)(ad_y)(ad_x)
     * 
     * 
     * 
     * 
     * u(bd_y) = as_y + t(ad_y) - bs_y
     * u = (as_y + t(ad_y) - bs_y) / bd_y
     * u = (as_y + [(bs_x + u(bd_x) - as_x) / ad_x] * ad_y - bs_y) / bd_y
     * u = 
     * 
     **/

    // Vec2f n1 = (va.p2 - va.p1).normalized(); 
    // Vec2f n2 = (vb.p2 - vb.p1).normalized(); 
    // float t = (vb.p1 - va.p1).dot(n2) / (va.p2-va.p1).dot(n2);

    cout << "va:" << va << "\n";
    cout << "vb:" << vb << "\n";
    // cout << "n1:" << n1 << "\n";
    // cout << "n2:" << n2 << "\n";
    // cout << "t:" << t << "\n";
}

void test()
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
    // cout << wall6 << "\n";
    // cout << ray2 << "\n";
    // cout << ray2.intersect(wall6) << "\n";

    Segment seg7 = Segment(Vec2f(4.0, 8.0), Vec2f(7.0, 5.0));
    Segment ray3 = Segment(Vec2f(4.5, 2.0), Vec2f(6.5, 9.0));
    cout << seg7 << "\n";
    cout << ray3 << "\n";
    cout << ray3.intersect(seg7) << "\n";
    cout << ray3.intersect(wall5) << "\n";
    cout << wall5.intersect(ray3) << "\n";

}
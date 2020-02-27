#include <iostream>
#include <fstream>
#include <vector>
#include "segment.h"
#include "laser.h"
#include "robot.h"
#include <Eigen/Dense>

using namespace std;
typedef Eigen::Vector2f Vec2f;
void test();
void test2();
void test3();
void test4(Robot &robot);
void test5(Robot &robot);

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
    float x, y;
    int count = 0;
    string line;
    while(getline(seg_file, line)) {
        stringstream ss(line);
        while(getline(ss, line, ',')) {
            count++;
            switch (count)
            {
            case 1: x = stof(line); break;
            case 2: y = stof(line); p1 = Vec2f(x, y); break;
            case 3: x = stof(line); break;
            case 4: 
                y = stof(line);
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

void read_positions(ifstream &pos_file, vector<Position> *positions)
{
    Position pos = Position(0, 0);
    float x, y;
    int count = 0;
    string line;
    while(getline(pos_file, line)) {
        stringstream ss(line);
        while(getline(ss, line, ',')) {
            count++;
            switch (count)
            {
            case 1: x = stof(line); break;
            case 2: 
                y = stof(line); 
                pos.move_to(x, y); 
                count = 0;
                positions->push_back(pos);
                break;
            default: break;
            }
        }
    }
}

void print_segments(vector<Segment> &segs)
{
    for (vector<Segment>::iterator it = segs.begin(); it != segs.end(); ++it) {
        cout << *it << "\n";
    }
}


vector<Segment*> simulate_scan(Robot *robot, vector<Segment> *wall_segments, Laser *laser_sensor)
{
    vector<Segment*> closest_segs;
    Position pos;

    float angle = robot->position.theta_degree - (laser_sensor->FOV_degree / 2.0);
    for(int i = 0; i <= laser_sensor->num_total_rays; i++) {
        cout << "------walls----------\n";
        Segment ray = laser_sensor->create_a_ray(robot->position, angle);
        cout << ray << "\n";
        angle += laser_sensor->angular_resolution_degree;
        for(vector<Segment>::iterator it = wall_segments->begin(); it != wall_segments->end(); it++) {
            // cout << *it << "\n";
            if (!ray.isParallel(*it)) {
                Vec2f intersect = ray.intersection_point(*it);
                if (ray.ifIntersect(*it)) {
                    cout << intersect << "\nwith" << *it << "\n";
                    closest_segs.push_back(&(*it));
                }
            }
        }
        cout << "--------------\n\n";
    }

    return closest_segs;
}

    // while (trajectories->size() != 0) {
    //     pos = trajectories->at(0);
    //     cout << "at " << pos << "\n";
    //     for(int i = 0; i <= laser_sensor->num_total_rays; i++) {

    //     }
    //     // copy(trajectories->begin(), trajectories->begin(), pos);
    //     trajectories->erase(trajectories->begin());
    // }
    // return closest_segs;



int main(int argc, char **argv)
{
    vector<Segment> wall_segments;
    vector<Position> trajectories;
    ifstream wall_segments_file;
    ifstream trajectories_file;
    Laser laser_sensor = Laser();

    // Check number of arguments
    if (argc <= 1 || 4 <= argc) {
        usage(argv[0]);
    }
    if (argc >= 2) { wall_segments_file = ifstream(argv[1]); }
    if (argc >= 3) { trajectories_file = ifstream(argv[2]); }
    if (!wall_segments_file && !trajectories_file) {
        cout << "The file [";
        if (!wall_segments_file) { cout << argv[1]; }
        if (!trajectories_file) { cout << ", " << argv[2]; }
        cout << "] doesn't exists.\n\n";
        exit(0);
    }

    read_segments(wall_segments_file, &wall_segments);
    read_positions(trajectories_file, &trajectories);

    Robot robot = Robot(Position(4,3,0));
    // test4(robot);
    // test5(robot);

    vector<Segment*> closest_walls = simulate_scan(&robot, &wall_segments, &laser_sensor);

    wall_segments_file.close();
    trajectories_file.close();
    return 0;
}







void test5(Robot &robot)
{
    Segment a = Segment(Vec2f(0, 0), Vec2f(20, 0));
    Segment b = Segment(Vec2f(20, 0), Vec2f(20, 10));
    Segment d = Segment(Vec2f(20, 0), Vec2f(20, -10));
    Segment r = Segment(Vec2f(4, 3), Vec2f(4, -6));

    Vec2f a_unit = a.segment_unit;
    Vec2f a_norm = a.segment_norm_unit;
    cout << a_unit << "\n";
    cout << a_norm << "\n";
    Vec2f b_unit = b.segment_unit;
    Vec2f b_norm = b.segment_norm_unit;
    cout << b_unit << "\n";
    cout << b_norm << "\n";
    Vec2f d_unit = d.segment_unit;
    Vec2f d_norm = d.segment_norm_unit;
    cout << d_unit << "\n";
    cout << d_norm << "\n\nr:\n";
    Vec2f r_unit = r.segment_unit;
    Vec2f r_norm = r.segment_norm_unit;
    cout << r_unit << "\n";
    cout << r_norm << "\n";

    cout << "\n\ndot product\n";
    float r_dot_a_unit = r.segment_unit.dot(d_norm);
    cout << r_unit << "\ndot\n" << d_norm << " : " << r_dot_a_unit << "\n";

    cout << r.intersection_point(d) << "\n";
}




void test4(Robot &robot)
{
    cout << "Robot(" << robot.position.x << "," << robot.position.y << "," << robot.position.theta_degree << ", [" << robot.position.position_vector << "])" << "\n";
    // robot.laser_scan(robot.position);
}

void test3()
{
    Segment va = Segment(Vec2f(0,0), Vec2f(5,0));
    Segment vb = Segment(Vec2f(5.1,-5), Vec2f(15.1,-5));
    // Segment vb = Segment(Vec2f(5.1,-5), Vec2f(5.1,5));

    cout << "va:" << va << "\n";
    cout << "vb:" << vb << "\n";
    cout << va.ifIntersect(vb);
    cout << "intersect point:\n" << va.intersection_point(vb) << "\n";

}

void test2()
{

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

    Segment va = Segment(Vec2f(0,0), Vec2f(3,3));
    Segment vb = Segment(Vec2f(2,1), Vec2f(5,5));
    // Segment vb = Segment(Vec2f(1,6), Vec2f(5,2));
    Vec2f btoa = vb.start - va.start;
    Vec2f bnom = vb.segment_norm_unit;
    Vec2f ad = va.segment_unit;
    float t = btoa.dot(bnom) / ad.dot(bnom);
    Vec2f atob = va.start - vb.start;
    Vec2f anom = va.segment_norm_unit;
    Vec2f bd = vb.segment_unit;
    float u = atob.dot(anom) / bd.dot(anom);
    Vec2f interab = va.start + t*(va.segment_unit);
    float acrossb = va.segment.x() * vb.segment.y() - (vb.segment.x() * va.segment.y());
    // Vec2f acrossb = va.segment.x * vb.segment.y - (vb.segment.x * va.segment.y);
    // Vec2f acrossb = va.segment.transpose().cross(vb.segment.transpose());
    // Vec2f acrossb = va.segment.

    cout << "va:" << va << "\n";
    cout << "vb:" << vb << "\n";
    // cout << "va cross vb:" <<  << "\n";
    // cout << va.segment << "\n";
    Vec2f bortho = vb.segment.unitOrthogonal();
    Vec2f bunit = vb.segment.normalized();
    // cout << bortho << "\n";
    // cout << bunit << "\n";
    // cout << vb.segment.dot(vb.segment_norm_unit) << "\n";
    cout << "interab:\n" << interab << "\n";
    cout << "t:" << t << "\n";
    cout << "u:" << u << "\n";
    cout << "acrossb:\n" << acrossb << "\n";
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
    cout << seg7.segment << "\n";
    // cout << ray3.intersect(seg7) << "\n";
    // cout << ray3.intersect(wall5) << "\n";
    // cout << wall5.intersect(ray3) << "\n";

}
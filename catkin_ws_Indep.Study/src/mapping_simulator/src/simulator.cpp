#include <iostream>
#include <string>
#include "simulator.h"
#include "segment.h"
#include "robot.h"
#include "laser.h"
#include "noise.h"
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>
using namespace std;


void simulate_scan(vector<Vec2f> &point_cloud, Robot &robot, vector<Segment> &wall_segments,
                            Laser &laser_sensor, Noise &length_noise, Noise &angle_noise)
{
    float angle = robot.angle_degree 
                - (laser_sensor.FOV_degree / 2.0);                     // Calculate starting angle from current Position(x, y, theta)

    for(int i = 1; i <= laser_sensor.num_total_rays; i++) {            // For all each laser ray
        // cout << "------ rays ----------\n";
        Segment ray = 
            laser_sensor.create_a_ray(robot.position, angle, length_noise, angle_noise); // Create a ray
        // cout << ray << "\n-------------------------\n";
        angle += laser_sensor.angular_resolution_degree;               // Get the next ray's angle

        float min_t = 99999;                                            // Temp value for min
        bool point_exists = false;
        Vec2f min_point;                                                // Pointer of the closest segment at the moment

        for(vector<Segment>::iterator wall_it = wall_segments.begin(); wall_it != wall_segments.end(); wall_it++) {  // For all each wall segment
            if (!ray.isParallel(*wall_it)) {                                 // If two segments(Laser ray & Wall segment) is not Parallel
                Vec2f new_point = ray.intersection_point(*wall_it);                // Get the intersection point as a Vec2f
                // cout << "(" << new_point.x() << "," << new_point.y() << ")" << endl;
                    // cout << ray.t << " ** " << min_t << endl;                       // In two intersects on its length (not on a extended line)
                if (ray.ifIntersect(*wall_it)) {      
                    if (fabs(ray.t) < fabs(min_t)) {                    // Takes as closest wall segment at the moment
                        point_exists = true;
                        min_t = ray.t;                                  // Remember the min t (length)
                        min_point = new_point;
                        // cout << "(" << min_point.x() << "," << min_point.y() << ") with a wall " << *wall_it << "\n";
                    }
                }
            }
        }

        if (point_exists) {                                             // If there existed any closest wall segment
            // cout << "adding min!" << endl;
            // cout << min_point << endl;
            if (min_t < laser_sensor.range_min) {                      // Too close point (closer than min_range of laser)
                ;
                // cout << "Too close to detect... pass by this ray. t: " << min_t << "\trange_min: " << laser_sensor.range_min << endl;
            } else {
                // geometry_msgs::Vector3 vec;
                // vec.x = min_point.x();
                // vec.y = min_point.y();
                // vec.z = 0;
                point_cloud.push_back(min_point);                      // Push back into a vector of Segment* pointers
            }
        } else {
            ;
            // cout << "nothing to add!" << endl;
        }
        // cout << "\n\n";
    }
}


float get_vector_length(Vec2f &v)
{
    return sqrt((pow(v.x(), 2.0) + pow(v.y(), 2.0)));
}


deque<Vec2f> interpolate_curve_points(Robot &robot, Vec2f &depart, Vec2f &arrive, bool noisy, Noise *noise)
{
    // L0: depart ~ interpoint
    // L1: interpoint ~ arrive
    Vec2f L0 = robot.velocity;
    Vec2f L1 = arrive - L0;
    cout << "L0: " << L0 << endl;
    cout << "L1: " << L1 << endl;

    float L0_length = get_vector_length(L0);
    float L1_length = get_vector_length(L1);
    cout << "L0 len: " << L0_length << endl;
    cout << "L1 len: " << L1_length << endl;

    if (L0_length <= 5.0) { L0_length = 5.0; }
    if (L1_length <= 5.0) { L1_length = 5.0; }
    float delta = 1 / (L0_length * L1_length * 2);
    float t = 0.0;
    cout << "L0 len * L1 len = " << (L0_length * L1_length) << endl;
    cout << "delta:" << delta << endl;
    
    deque<Vec2f> curves;
    Vec2f p_before = L0;
    for(float curve_point = 0.0; curve_point <= 1.0; curve_point += delta) {
        cout << "curve_point: " << curve_point << endl;
        // Position p = (P0 * pow((1 - curve_point), 2.0)) +
        //             (P1 * 2 * (1 - curve_point) * curve_point) +
        //             (arrive * pow(curve_point, 2.0));
        float x = (depart.x() * pow((1 - curve_point), 2.0)) +
                    (L0.x() * 2 * (1 - curve_point) * curve_point) +
                    (arrive.x() * pow(curve_point, 2.0));
        float y = (depart.y() * pow((1 - curve_point), 2.0)) +
                    (L0.y() * 2 * (1 - curve_point) * curve_point) +
                    (arrive.y() * pow(curve_point, 2.0));
        // if (noisy) {
        //     float x_n = noise->gaussian();
        //     float y_n = x_n;
        //     // float y_n = noise->gaussian();
        //     x += x_n;
        //     y += y_n;
        //     depart.x() += x_n;
        //     depart.y() += y_n;
        // }                    
        Vec2f p_next = Vec2f(x, y);
        // p_before = Vec2f()
        // Vec2f q = robot.position;
        // robot.move_to(p);
        // robot.angle_degree += atan2((p_before.y()-q.y()), (p_before.x()-q.x()));
        // robot.set_velocity();
        cout << "new pos: " << p_next << "\t\tRobot pos:" << "(" << robot.position.x() << "," << robot.position.y() << ")" << endl;
        cout << "Robot pos:" << "(" << robot.position.x() << "," << robot.position.y() << ")  angle:" << robot.angle_degree << endl;
        curves.push_back(p_next);
        // getchar();
    }

    if (noisy) {
        deque<Vec2f> noised_curves;
        Vec2f last_p = curves.front();
        float x_accm = 0.0;
        float y_accm = 0.0;
        for (deque<Vec2f>::iterator it = curves.begin(); it != curves.end(); ++it) {
            x_accm += noise->gaussian();
            y_accm += noise->gaussian();
            float noised_x = it->x() + x_accm;
            float noised_y = it->y() + y_accm;
            last_p = Vec2f(noised_x, noised_y);
            noised_curves.push_back(last_p);
        }
        return noised_curves;
    }

    return curves;
}


int usage(char *app_name) {
    cout << "Usage: " << app_name << " [text file]\n";
    cout << "Options:\n";
    cout << "  -p\t\t\tpause on every line\n\n";
    exit(0);
}


void read_segments(ifstream &seg_file, vector<Segment> &segments)
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
                segments.push_back(seg);
                break;
            default: break;
            }
        }
    }
}


float cut_redundant_epsilon(float x, float threshold)
{
    return (fabs(x) < threshold) ? 0.0 : x;
}


void read_waypoints(ifstream &pos_file, deque<Vec2f> &positions)
{
    float x, y;
    int count = 0;
    string line;
    while(getline(pos_file, line)) {
        stringstream ss(line);
        while(getline(ss, line, ',')) {
            cout << line << endl;
            count++;
            switch (count)
            {
            case 1: x = stof(line); break;
            case 2: 
                y = stof(line); 
                positions.push_back(Vec2f(x, y));
                count = 0;
                break;
            default: break;
            }
        }
    }
}
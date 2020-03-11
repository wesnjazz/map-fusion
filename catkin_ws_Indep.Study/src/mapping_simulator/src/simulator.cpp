#include <iostream>
#include <string>
#include "simulator.h"
#include "segment.h"
#include "robot.h"
#include "laser.h"
#include "noise.h"
#include "transformation.h"
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>
using namespace std;


float get_delta_t(Laser &laser)
{
    float delta_t = 1.0f / laser.frequency;
    return delta_t;
}


void simulate_scan(vector<Vec2f> &point_cloud, Robot &robot, vector<Segment> &wall_segments,
                            Laser &laser_sensor, Noise &length_noise, Noise &angle_noise)
{
    float angle = robot.heading_degree 
                - (laser_sensor.FOV_degree / 2.0);                     // Calculate starting angle from current Position(x, y, theta)

    for(int i = 1; i <= laser_sensor.num_total_rays; i++) {            // For all each laser ray
        // cout << "------ rays ----------\n";
        Segment ray = 
            laser_sensor.create_a_ray(robot.position_W, angle, length_noise, angle_noise); // Create a ray
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


deque<Vec2f> interpolate_curve_points(deque<Eigen::Matrix3f> &homos, float delta_t, Robot &robot, Vec2f &depart, Vec2f &arrive, bool noisy, Noise *noise)
{
    float move = delta_t * robot.speed;
    float num_points = (int)(get_vector_length(arrive) / move);
    cout << "depart:" << depart << "\tarrive:" << arrive << "\tlength:" << get_vector_length(arrive) << endl;
    cout << "move:" << move << "\tdelta_t:"<<delta_t<<"\tspeed:"<<robot.speed<< "\tnum_points:" << num_points << endl;
    /** Calculate the interpoint based on robot's velocity **/
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


    /** Calculate delta(division step of a single curve line) **/
    if (L0_length <= 5.0) { L0_length = 5.0; }
    if (L1_length <= 5.0) { L1_length = 5.0; }
    float delta = 1.0 / num_points;
    // float delta = 1 / (L0_length * L1_length * 2);
    float t = 0.0;
    cout << "L0 len * L1 len = " << (L0_length * L1_length) << endl;
    cout << "delta:" << delta << endl;
    

    /** Getting curve points (Vec2f) **/
    deque<Vec2f> curves;
    Vec2f p_before = L0;
    for(float curve_point = 0.0; curve_point <= 1.0; curve_point += delta) {
        cout << "curve_point: " << curve_point << endl;
        float x = (depart.x() * pow((1 - curve_point), 2.0)) +
                    (L0.x() * 2 * (1 - curve_point) * curve_point) +
                    (arrive.x() * pow(curve_point, 2.0));
        float y = (depart.y() * pow((1 - curve_point), 2.0)) +
                    (L0.y() * 2 * (1 - curve_point) * curve_point) +
                    (arrive.y() * pow(curve_point, 2.0));
        Vec2f p_next = Vec2f(x, y);
        float angle_radian = get_angle_radian_between_two_vectors(p_before, p_next);
        // Eigen::Matrix2f rot = get_rotation_matrix2f(angle_radian);
        // Vec2f trans = get_translation_vec2f(p_before, p_next);
        Eigen::Matrix3f homo = get_homogeneous_transform(p_before, p_next);
        homos.push_back(homo);
        cout << homo << endl;
        cout << "new pos: " << p_next << "\t\tRobot pos:" << "(" << robot.position_W.x() << "," << robot.position_W.y() << ")" << endl;
        cout << "Robot pos:" << "(" << robot.position_W.x() << "," << robot.position_W.y() << ")  angle:" << robot.heading_degree << endl;
        // getchar();
        curves.push_back(p_next);
        p_before = Vec2f(p_next);
        /** Todo
         * - Get a pure translation
         * - Get a pure rotation
         * - Combine those into a homogeneous transformation
         **/
        
    }

    /** Apply Noise (Odometry simulation) **/
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


    /** return ideal curve points (no Noises) **/
    return curves;
}


void draw_robot_vector(Robot &robot_ideal, vector_slam_msgs::LidarDisplayMsg &lidar_msg)
{
    float robot_length = 0.1;
    // float robot_length = get_vector_length(robot_ideal.position_W) * 10;
    float heading_x = robot_ideal.position_W.x() + (robot_length * cos(robot_ideal.heading_radian));
    float heading_y = robot_ideal.position_W.y() + (robot_length * sin(robot_ideal.heading_radian));
    cout << "robot_x:" << robot_ideal.position_W.x() << " y:" << robot_ideal.position_W.y() << " angle:" << robot_ideal.heading_degree
        << " length:" << robot_length << " heading_x:" << heading_x << " y:" << heading_y << endl;
    lidar_msg.lines_p1x.push_back(robot_ideal.position_W.x());
    lidar_msg.lines_p1y.push_back(robot_ideal.position_W.y());
    lidar_msg.lines_p2x.push_back(heading_x);
    lidar_msg.lines_p2y.push_back(heading_y);
    lidar_msg.lines_col.push_back(0xFF000000);

    float arrow_length = robot_length / 2.0;
    float left_head_x = robot_ideal.position_W.x() + (arrow_length * cos(robot_ideal.heading_radian - degree_to_radian(45)));
    float left_head_y = robot_ideal.position_W.y() + (arrow_length * sin(robot_ideal.heading_radian - degree_to_radian(45)));
    float right_head_x = robot_ideal.position_W.x() + (arrow_length * cos(robot_ideal.heading_radian + degree_to_radian(45)));
    float right_head_y = robot_ideal.position_W.y() + (arrow_length * sin(robot_ideal.heading_radian + degree_to_radian(45)));
    lidar_msg.lines_p1x.push_back(left_head_x);
    lidar_msg.lines_p1y.push_back(left_head_y);
    lidar_msg.lines_p2x.push_back(heading_x);
    lidar_msg.lines_p2y.push_back(heading_y);
    lidar_msg.lines_col.push_back(0xFF000000);
    lidar_msg.lines_p1x.push_back(right_head_x);
    lidar_msg.lines_p1y.push_back(right_head_y);
    lidar_msg.lines_p2x.push_back(heading_x);
    lidar_msg.lines_p2y.push_back(heading_y);
    lidar_msg.lines_col.push_back(0xFF000000);

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


void read_waypoints(ifstream &pos_file, deque<Vec2f> &positions, deque<float>robot_headings)
{
    float x, y, theta;
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
            case 2: y = stof(line); break;
            case 3: 
                theta = stof(line); 
                positions.push_back(Vec2f(x, y));
                robot_headings.push_back(theta);
                count = 0;
                break;
            default: break;
            }
        }
    }
}


float degree_to_radian(float theta)
{
    return theta * (M_PI / 180.0);
}


float radian_to_degree(float theta)
{
    return theta * (180.0 / M_PI);
}

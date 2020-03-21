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
    float angle = robot.heading_degree_in_Wframe 
                - (laser_sensor.FOV_degree / 2.0);                     // Calculate starting angle from current Position(x, y, theta)

    for(int i = 1; i <= laser_sensor.num_total_rays; i++) {            // For all each laser ray
        Segment ray = 
            laser_sensor.create_a_ray(robot.position_in_Wframe, angle, length_noise, angle_noise); // Create a ray
        angle += laser_sensor.angular_resolution_degree;               // Get the next ray's angle

        float min_t = 99999;                                            // Temp value for min
        bool point_exists = false;
        Vec2f min_point;                                                // Pointer of the closest segment at the moment

        for(vector<Segment>::iterator wall_it = wall_segments.begin(); wall_it != wall_segments.end(); wall_it++) {  // For all each wall segment
            if (!ray.isParallel(*wall_it)) {                                 // If two segments(Laser ray & Wall segment) is not Parallel
                Vec2f new_point = ray.intersection_point(*wall_it);                // Get the intersection point as a Vec2f
                if (ray.ifIntersect(*wall_it)) {      
                    if (fabs(ray.t) < fabs(min_t)) {                    // Takes as closest wall segment at the moment
                        point_exists = true;
                        min_t = ray.t;                                  // Remember the min t (length)
                        min_point = new_point;
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
                min_point = Vec2f(min_point.x() + length_noise.gaussian(), min_point.y() + angle_noise.gaussian());
                point_cloud.push_back(min_point);                      // Push back into a vector of Segment* pointers
            }
        } 
    }
}


// void collision_avoidance(vector<Vec2f> &point_cloud, Robot &robot, vector<Mat3f> &aHTb)
// {
//     for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it)    
//     {

//     }
// }


// void adjust_heading(Robot &robot, Vec2f &goal, float threshold)
// {
//     float angle_diff_degree = get_angle_degree_between_two_vectors(robot.position_in_Wframe, goal);


// }


float get_vector_length(Vec2f &v)
{
    return sqrt((pow(v.x(), 2.0) + pow(v.y(), 2.0)));
}


bool if_arrived_at_a_point_frameW(Robot &robot, Vec3f &goal, float threshold_distance, float threshold_heading_degree)
{
    bool within_x = fabs(robot.position_in_Wframe.x() - goal.x()) < threshold_distance;
    bool within_y = fabs(robot.position_in_Wframe.y() - goal.y()) < threshold_distance;
    bool within_heading_degree = fabs(robot.heading_degree_in_Wframe - goal.z()) < threshold_heading_degree;
    cout
        << "difference: "
        << "x:" << fabs(robot.position_in_Wframe.x() - goal.x())
        << "y:" << fabs(robot.position_in_Wframe.y() - goal.y())
        << "th:" << fabs(robot.heading_degree_in_Wframe - goal.z())
        << endl;

    return (within_x && within_y && within_heading_degree) ? true : false;
}


bool if_arrived_at_xy_frameW(Robot &robot, float x, float y, float threshold_distance)
{
    float x_diff = fabs(robot.position_in_Wframe.x() - x);
    float y_diff = fabs(robot.position_in_Wframe.y() - y);
    bool within_x = x_diff < threshold_distance;
    bool within_y = y_diff < threshold_distance;
    // cout
    //     << "\ndifference: "
    //     << "  x:" << within_x
    //     << "  y:" << within_y
    //     << endl;

    return (within_x && within_y) ? true : false;
}


bool if_arrived_at_theta_degree_frameW(Robot &robot, float theta_degree, float threshold_theta)
{
    float theta_diff = fabs(robot.heading_degree_in_Wframe - theta_degree);
    bool within_theta = theta_diff < threshold_theta;
    cout
        << "\ndifference: "
        << "  theta:" << within_theta
        << endl;

    return (within_theta) ? true : false;
}


deque<Vec2f> interpolate_curve_points(deque<Eigen::Matrix3f> &homos, float delta_t, Robot &robot, Vec2f &depart, Vec2f &arrive, bool noisy, Noise *noise)
{
    float move = delta_t * robot.speed;
    float num_points = (int)(get_vector_length(arrive) / move);
    // cout << "depart:" << depart << "\tarrive:" << arrive << "\tlength:" << get_vector_length(arrive) << endl;
    // cout << "move:" << move << "\tdelta_t:"<<delta_t<<"\tspeed:"<<robot.speed<< "\tnum_points:" << num_points << endl;
    /** Calculate the interpoint based on robot's velocity **/
    // L0: depart ~ interpoint
    // L1: interpoint ~ arrive
    Vec2f L0 = robot.position_in_Wframe;
    // Vec2f L0 = robot.velocity_in_Wframe;
    Vec2f L1 = arrive - L0;
    // cout << "L0: " << L0 << endl;
    // cout << "L1: " << L1 << endl;

    float L0_length = get_vector_length(L0);
    float L1_length = get_vector_length(L1);
    // cout << "L0 len: " << L0_length << endl;
    // cout << "L1 len: " << L1_length << endl;


    /** Calculate delta(division step of a single curve line) **/
    if (L0_length <= 5.0) { L0_length = 5.0; }
    if (L1_length <= 5.0) { L1_length = 5.0; }
    float delta = 1.0 / num_points;
    // float delta = 1 / (L0_length * L1_length * 2);
    float t = 0.0;
    // cout << "L0 len * L1 len = " << (L0_length * L1_length) << endl;
    // cout << "delta:" << delta << endl;
    

    /** Getting curve points (Vec2f) **/
    deque<Vec2f> curves;
    Vec2f p_before = L0;
    for(float curve_point = 0.0; curve_point <= 1.0; curve_point += delta) {
        // cout << "curve_point: " << curve_point << endl;
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
        // cout << "new pos: " << p_next << "\t\tRobot pos:" << "(" << robot.position_in_Wframe.x() << "," << robot.position_in_Wframe.y() << ")" << endl;
        // cout << "Robot pos:" << "(" << robot.position_in_Wframe.x() << "," << robot.position_in_Wframe.y() << ")  angle:" << robot.heading_degree_in_Wframe << endl;
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


void draw_robot_vector(Robot &robot_ideal, vector_slam_msgs::LidarDisplayMsg &lidar_msg, uint32_t color)
{
    float vector_length = robot_ideal.speed / 5.0;
    // float vector_length = get_vector_length(robot_ideal.position_in_Wframe) * 10;
    float heading_x = robot_ideal.position_in_Wframe.x() + (vector_length * cos(robot_ideal.heading_radian_in_Wframe));
    float heading_y = robot_ideal.position_in_Wframe.y() + (vector_length * sin(robot_ideal.heading_radian_in_Wframe));
    // cout << "robot_x:" << robot_ideal.position_in_Wframe.x() << " y:" << robot_ideal.position_in_Wframe.y() << " angle:" << robot_ideal.heading_degree_in_Wframe
    //     << " length:" << vector_length << " heading_x:" << heading_x << " y:" << heading_y << endl;
    lidar_msg.lines_p1x.push_back(robot_ideal.position_in_Wframe.x());
    lidar_msg.lines_p1y.push_back(robot_ideal.position_in_Wframe.y());
    lidar_msg.lines_p2x.push_back(heading_x);
    lidar_msg.lines_p2y.push_back(heading_y);
    lidar_msg.lines_col.push_back(color);

    float arrow_length = vector_length / 2.0;
    float left_head_x = robot_ideal.position_in_Wframe.x() + (arrow_length * cos(robot_ideal.heading_radian_in_Wframe - degree_to_radian(45)));
    float left_head_y = robot_ideal.position_in_Wframe.y() + (arrow_length * sin(robot_ideal.heading_radian_in_Wframe - degree_to_radian(45)));
    float right_head_x = robot_ideal.position_in_Wframe.x() + (arrow_length * cos(robot_ideal.heading_radian_in_Wframe + degree_to_radian(45)));
    float right_head_y = robot_ideal.position_in_Wframe.y() + (arrow_length * sin(robot_ideal.heading_radian_in_Wframe + degree_to_radian(45)));
    lidar_msg.lines_p1x.push_back(left_head_x);
    lidar_msg.lines_p1y.push_back(left_head_y);
    lidar_msg.lines_p2x.push_back(heading_x);
    lidar_msg.lines_p2y.push_back(heading_y);
    lidar_msg.lines_col.push_back(color);
    lidar_msg.lines_p1x.push_back(right_head_x);
    lidar_msg.lines_p1y.push_back(right_head_y);
    lidar_msg.lines_p2x.push_back(heading_x);
    lidar_msg.lines_p2y.push_back(heading_y);
    lidar_msg.lines_col.push_back(color);

}


void draw_grids(vector_slam_msgs::LidarDisplayMsg &lidar_msg, uint32_t color)
{
    for (int i = -30; i <= 30; ++i)
    {
        lidar_msg.lines_p1x.push_back(i);
        lidar_msg.lines_p1y.push_back(-30);
        lidar_msg.lines_p2x.push_back(i);
        lidar_msg.lines_p2y.push_back(30);
        lidar_msg.lines_col.push_back(color);

        lidar_msg.lines_p1x.push_back(-30);
        lidar_msg.lines_p1y.push_back(i);
        lidar_msg.lines_p2x.push_back(30);
        lidar_msg.lines_p2y.push_back(i);
        lidar_msg.lines_col.push_back(color);
    }
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


void read_waypoints(ifstream &pos_file, deque<Vec3f> &positions, vector_slam_msgs::LidarDisplayMsg &msg)
{
    float x, y, theta_degree;
    int count = 0;
    string line;
    while(getline(pos_file, line)) {
        stringstream ss(line);
        while(getline(ss, line, ',')) {
            // cout << line << endl;
            count++;
            switch (count)
            {
            case 1: x = stof(line); break;
            case 2: y = stof(line); break;
            case 3: 
                theta_degree = stof(line); 
                // msg.points_x.push_back(x);
                // msg.points_y.push_back(y);
                // msg.points_col.push_back(0xFF00FF00);

                positions.push_back(Vec3f(x, y, theta_degree));
                // robot_headings.push_back(theta_degree);
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


void draw_grid_line_of_robot_frame(Robot &robot_ideal, Mat3f &new_HT, Vec3f &arrival_R, vector_slam_msgs::LidarDisplayMsg &lidar_msg, bool erase)
{
        /** Grid lines of the robot frame **/
    Vec3f arrival_of_R_in_W = new_HT * arrival_R;

    uint32_t color_draw_grid = 0x442266AA;
    uint32_t color_draw_axis = 0x99DD6633;
    uint32_t color_erase = 0xFFFFFFFF;

    int l = 10; // length
    int n = 10; // number of lines
    if (!erase)
    {
        for(int i = -n; i <= n; ++i)    // Draw
        {
            Vec3f R_gridx1u = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(i, l, 0);
            Vec3f R_gridx1d = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(i, -l, 0);
            lidar_msg.lines_p1x.push_back(R_gridx1u.x());
            lidar_msg.lines_p1y.push_back(R_gridx1u.y());
            lidar_msg.lines_p2x.push_back(R_gridx1d.x());
            lidar_msg.lines_p2y.push_back(R_gridx1d.y());
            if (i == 0) {
                lidar_msg.lines_col.push_back(color_draw_axis);
            } else {
                lidar_msg.lines_col.push_back(color_draw_grid);
            }
            Vec3f R_gridy1u = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(l, i, 0);
            Vec3f R_gridy1d = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(-l, i, 0);
            lidar_msg.lines_p1x.push_back(R_gridy1u.x());
            lidar_msg.lines_p1y.push_back(R_gridy1u.y());
            lidar_msg.lines_p2x.push_back(R_gridy1d.x());
            lidar_msg.lines_p2y.push_back(R_gridy1d.y());
            if (i == 0) {
                lidar_msg.lines_col.push_back(color_draw_axis);
            } else {
                lidar_msg.lines_col.push_back(color_draw_grid);
            }
        }
    } else
    {
        for(int i = -n; i <= n; ++i)    // Erase
        {
            Vec3f R_gridx1u = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(i, l, 0);
            Vec3f R_gridx1d = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(i, -l, 0);
            lidar_msg.lines_p1x.push_back(R_gridx1u.x());
            lidar_msg.lines_p1y.push_back(R_gridx1u.y());
            lidar_msg.lines_p2x.push_back(R_gridx1d.x());
            lidar_msg.lines_p2y.push_back(R_gridx1d.y());
            lidar_msg.lines_col.push_back(color_erase);
            Vec3f R_gridy1u = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(l, i, 0);
            Vec3f R_gridy1d = (robot_ideal.position_in_Wframe).homogeneous() + new_HT * Vec3f(-l, i, 0);
            lidar_msg.lines_p1x.push_back(R_gridy1u.x());
            lidar_msg.lines_p1y.push_back(R_gridy1u.y());
            lidar_msg.lines_p2x.push_back(R_gridy1d.x());
            lidar_msg.lines_p2y.push_back(R_gridy1d.y());
            lidar_msg.lines_col.push_back(color_erase);
        }
    }
}
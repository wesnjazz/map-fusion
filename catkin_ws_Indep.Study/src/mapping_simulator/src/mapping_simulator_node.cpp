#include "simulator.h"
#include "segment.h"
#include "transformation.h"
#include "wheelencoder.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <ros/ros.h>
#include <std_msgs/ColorRGBA.h>
#include <geometry_msgs/Vector3.h>
#include <vector_slam_msgs/LidarDisplayMsg.h>
#include <gui_publisher_helper.h>
#include <sensor_msgs/LaserScan.h>

using namespace std;


int main(int argc, char **argv) 
{
    /** ROS initialization **/
    ros::init(argc, argv, "Mapping_Simulator");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);
    ros::Publisher lidar_msg_pub = n.advertise<vector_slam_msgs::LidarDisplayMsg>("/VectorSLAM/VectorLocalization/Gui", 1000);


    /** Map and Points **/
    vector<Segment> wall_segments;  // vector of wall segments
    ifstream wall_segments_file;    // file stream of wall segments
    deque<Vec2f> waypoints;         // vector of waypoints
    ifstream waypoints_file;        // file stream of waypoints
    deque<float> robot_headings;     // deque of robot headings


    /** File loading **/
    if (argc <= 1 || 4 <= argc) {
        usage(argv[0]);
    }
    if (argc >= 2) { wall_segments_file = ifstream(argv[1]); }
    if (argc >= 3) { waypoints_file = ifstream(argv[2]); }
    if (!wall_segments_file) { // && !waypoints_file) {
        cout << "The file [";
        if (!wall_segments_file) { cout << argv[1]; }
        if (!waypoints_file) { cout << ", " << argv[2]; }
        cout << "] doesn't exists.\n\n";
        exit(0);
    }
    read_segments(wall_segments_file, wall_segments);
    read_waypoints(waypoints_file, waypoints, robot_headings);
    deque<Vec2f> *waypoints_backup = new deque<Vec2f>(waypoints);   // Deep copy


    /** Create objects **/
    
    /** Sets robot's init position **/
    Vec2f robot_init_position = (waypoints.empty() ? Vec2f(0, 0) : waypoints.front());
    float heading = (robot_headings.empty() ? 0.0 : robot_headings.front());
    float speed = 0.5;

    Robot robot_actual = Robot(robot_init_position, heading, speed);
    Robot robot_ideal = Robot(robot_init_position, heading, speed);

    Laser laser_sensor = Laser();
    Noise length_noise = Noise(0.0, 0.8);
    Noise angle_noise = Noise(0.0, 0.2);
    Noise wheel_encoder_dx_noise = Noise(0.0, 0.02);
    Noise wheel_encoder_dy_noise = Noise(0.0, 0.02);
    WheelEncoder wheel_encoder = WheelEncoder();

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_stamp = 0.0;


    /** LaserScan msg **/
    sensor_msgs::LaserScan laserscan;
    laserscan.range_max = laser_sensor.range_max;
    laserscan.range_min = laser_sensor.range_min;
    laserscan.angle_max = laser_sensor.FOV_radian;
    laserscan.angle_min = 0.0;


    /** ROS node loop **/
    while (ros::ok())
    {   
        /** Draw Wall segments **/
        vector_slam_msgs::LidarDisplayMsg lidar_msg;
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(cobot_gui::kColorBlack);
        }

        /** Initial position **/
        Vec2f depart = waypoints.front();
        waypoints.pop_front();

        /** Loop until visit all waypoints **/
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            /** Extract the next waypoint **/
            Vec2f arrive = waypoints.front();
            waypoints.pop_front();
            cout << "depart:" << depart << endl;
            cout << "arrive:" << arrive << endl;
            // getchar();


            deque<Eigen::Matrix3f> homos;
            /** Calculate curve points(trajectories) from current waypoint to the next waypoint **/
            Noise trajectories_noise = Noise(0.0, 0.01);        // For simulating noises on Odometry
            /** Separate curve points.  Ideal: Where robot think it is.  Actual: Actual position of the robot **/
            deque<Vec2f> trajectories_ideal = interpolate_curve_points(homos, delta_t, robot_ideal, depart, arrive);
            deque<Vec2f> trajectories_actual = interpolate_curve_points(homos, delta_t, robot_actual, depart, arrive, true, &trajectories_noise);


            Eigen::Matrix3f final_homo = homos.front();
            homos.pop_front();
            for (deque<Eigen::Matrix3f>::iterator it = homos.begin(); it != homos.end(); ++it) {
                Eigen::Matrix3f h = homos.front();
                homos.pop_front();
                final_homo = final_homo * h;
            }

            Eigen::Vector3f first;
            first.row(0) = robot_init_position.row(0);
            first.row(1) = robot_init_position.row(1);
            first.row(2) << 1;
            // Eigen::Vector3f first = final_homo.block<1, 3>(0, 0);
            // Eigen::Vector3f first;
            // first.setIdentity();
            // Eigen::Vector3f last = robot_init_position.transpose() * final_homo;
            cout << "first:\n"<< first << endl;
            Eigen::Vector3f last = first.transpose() * final_homo;
            cout << "last:\n"<< last << endl;
            cout << "final_homo:\n" << final_homo << endl;
            // getchar();


            /** Traverse all curve points between point P0 and P1 **/
            while (!trajectories_ideal.empty())
            {
                /** Extract the next curve point **/
                Vec2f p_ideal = trajectories_ideal.front();
                Vec2f p_actual = trajectories_actual.front();
                trajectories_ideal.pop_front();
                trajectories_actual.pop_front();

                /** Move robot **/
                // robot_ideal.move_to(p_ideal);
                // draw_robot_vector(robot_ideal, lidar_msg);
                // robot_actual.move_to(p_actual);

                /** Draw Robot's velocity **/
                lidar_msg.points_x.push_back(p_ideal.x());
                lidar_msg.points_y.push_back(p_ideal.y());
                lidar_msg.points_col.push_back(0xFFFF0000);
                lidar_msg.points_x.push_back(p_actual.x());
                lidar_msg.points_y.push_back(p_actual.y());
                lidar_msg.points_col.push_back(0xFF0000FF);

                lidar_msg.robotLocX = robot_actual.position_W.x();
                lidar_msg.robotLocY = robot_actual.position_W.y();
                lidar_msg.timestamp = time_stamp;
                lidar_msg.robotAngle = robot_actual.heading_radian;

                /** Simulate scan **/
                vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
                // simulate_scan(point_cloud, robot_actual, wall_segments, laser_sensor, length_noise, angle_noise);
                // sort(point_cloud.begin(), point_cloud.end(), compare_xy_Vec2f());
                // point_cloud.erase( unique(point_cloud.begin(), point_cloud.end()), point_cloud.end());
                // cout << "point cloud size:" << point_cloud.size() << endl;

                /** Update time delta t after one laser scan **/
                time_stamp += delta_t;

                /** Draw laser scan points **/
                for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    lidar_msg.points_x.push_back(it->x());
                    lidar_msg.points_y.push_back(it->y());
                    lidar_msg.points_col.push_back(0xFFA500FF); // Orange
                }

                /** Successfull Tests **/
                Vec2f F1 = Vec2f(0, 0);
                Vec2f F2 = Vec2f(4, 0);
                // Vec2f F1_frameF2 = Vec2f(-4, -3);
                Vec2f F3 = Vec2f(2, 4);
                // Vec2f F3_frameF2 = Vec2f(0, 2);
                Vec2f P9 = Vec2f(5, 1);
                Mat3f A12 = get_homogeneous_transform_between_two_frames(F1.x(), F1.y(), 0, F2.x(), F2.y(), 45);
                Mat3f A21 = get_homogeneous_transform_between_two_frames(F2.x(), F2.y(), 45, F1.x(), F1.y(), 0);
                Mat3f A23 = get_homogeneous_transform_between_two_frames(F2.x(), F2.y(), 45, F3.x(), F3.y(), 90);
                Mat3f A13 = get_homogeneous_transform_between_two_frames(F1.x(), F1.y(), 0, F3.x(), F3.y(), 90);
                // Eigen::Matrix3f A31 = get_homogeneous_transform(F3, F1);
                cout << A12 << endl;
                cout << A23 << endl;
                cout << A13 << endl;
                // cout << A31 << endl;
                Vec3f F1toF2 = A12 * F1.homogeneous();
                Vec3f P9inF2 = A21 * P9.homogeneous();
                // Vec3f F2toF3 = A23 * A12 * F1.homogeneous();
                // Vec3f F1toF3 = A13 * F1.homogeneous();
                // Vec3f F1toF3p = A12 * A23 * F1.homogeneous();
                // Vec3f F3_in_W_frame = A12 * F3_frameF2.homogeneous();
                cout << "-----------------------------------" << endl;
                cout << F1 << endl << P9 << endl;
                cout << F1toF2 << endl;
                cout << P9inF2 << endl;
                cout << "-----------------------------------" << endl;
                // cout << F2 << endl;
                // cout << F2toF3 << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F3 << endl;
                // cout << F1toF3 << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F3 << endl;
                // cout << F1toF3p << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F3 << endl;
                // cout << F3_in_W_frame << endl;
                cout << "-----------------------------------" << endl;
                // F1toF2 = A12 * F1;
                // Eigen::Vector3f F1toF2 = Eigen::Vector3f(A12 * F1);
                // Eigen::Vector3f F2toF3 = Eigen::Vector3f(A23 * F2);
                // Eigen::Vector3f F1toF3 = Eigen::Vector3f(A23 * A12 * F1);
                lidar_msg.points_x.push_back(F1.x());
                lidar_msg.points_y.push_back(F1.y());
                lidar_msg.points_col.push_back(0xFF00FF00);
                lidar_msg.points_x.push_back(F2.x());
                lidar_msg.points_y.push_back(F2.y());
                lidar_msg.points_col.push_back(0xFF00FF00);
                lidar_msg.points_x.push_back(F3.x());
                lidar_msg.points_y.push_back(F3.y());
                lidar_msg.points_col.push_back(0xFF00FF00);


                /** Odometry Test **/
                Vec2f O1 = Vec2f(0, 0);
                Vec2f O2 = Vec2f(2, 0);
                Vec2f O3 = Vec2f(4, 2);
                Vec2f O4 = Vec2f(4, 4);
                float speed_wheel = 0.1;
                float del_t = 0.1;

                float x_pos = 0;
                float y_pos = 0;
                // float dx_ns = wheel_encoder_dx_noise.gaussian();
                // float dy_ns = wheel_encoder_dy_noise.gaussian();
                for (int i = 0; i <= 100000; ++i) {
                    wheel_encoder.simulate_odometry( speed_wheel, del_t, 
                                    fabs(wheel_encoder_dx_noise.gaussian()), fabs(wheel_encoder_dy_noise.gaussian()) );
                                    Vec2f pp = Vec2f(robot_ideal.position_W.x()+wheel_encoder.dx, robot_ideal.position_W.y()+wheel_encoder.dy);
                                    robot_ideal.move_to(pp);
                    lidar_msg.points_x.push_back( robot_ideal.position_W.x() );
                    lidar_msg.points_y.push_back( robot_ideal.position_W.y() );
                    lidar_msg.points_col.push_back(0xFF55A3B0);
                lidar_msg_pub.publish(lidar_msg);
                getchar();
                }

                /** Publishing msgs **/

                // getchar();
                // return 0;
                cout << "time_stamp: " << time_stamp << endl;
                cout << "delta_t: " << delta_t << endl;
                ros::spinOnce();
                loop_rate.sleep();
                // getchar();
            }
            depart = Vec2f(arrive);
            cout << "angle:" << robot_actual.heading_degree << "\tcurrent:(" << robot_actual.position_W.x() 
                << "," << robot_actual.position_W.y() << ")" << "\tarrive:(" << arrive.x() << "," << arrive.y() << ")" << endl;
            cout << "robot's velocity:" << robot_actual.velocity << endl;
            cout << "waypoints.front():" << waypoints.front() << endl;


            // getchar();
        }

        // robot.move_to(robot_init_position);
        for(deque<Vec2f>::iterator it = waypoints_backup->begin(); it != waypoints_backup->end(); ++it) {
            waypoints.push_back(*it);
        }
        cout << "arrived at:(" << robot_ideal.position_W.x() << ", " << robot_ideal.position_W.y() << ")" << endl;
        cout << "Travel finished!" << endl;
        // getchar();

        heading = (robot_headings.empty() ? 0.0 : robot_headings.front());
        speed = 0.5;
        robot_ideal.move_to(robot_init_position);
        robot_ideal.set_heading(heading);
        robot_ideal.set_speed(speed);
        robot_actual.move_to(robot_init_position);
        robot_actual.set_heading(heading);
        robot_actual.set_speed(speed);
        // robot_actual = Robot(robot_init_position, heading, speed);
        // robot_ideal = Robot(robot_init_position, heading, speed);

    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
#include "simulator.h"
#include "segment.h"
#include "transformation.h"
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


    /** Variables **/
    vector<Segment> wall_segments;  // vector of wall segments
    ifstream wall_segments_file;    // file stream of wall segments
    deque<Vec2f> waypoints;         // vector of waypoints
    ifstream waypoints_file;        // file stream of waypoints


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
    read_waypoints(waypoints_file, waypoints);
    deque<Vec2f> *waypoints_backup = new deque<Vec2f>(waypoints);   // Deep copy


    /** Create objects **/
    
    /** Sets robot's init position **/
    Vec2f robot_init_position;
    if (waypoints.empty()) { robot_init_position = Vec2f(0, 0); }
    else { Vec2f robot_init_position = waypoints.at(0); }

    float heading = 0.0;
    float speed = 0.5;
    Robot robot = Robot(robot_init_position, heading, speed);
    Robot robot_ideal = Robot(robot_init_position, heading, speed);
    Laser laser_sensor = Laser();
    Noise length_noise = Noise(0.0, 0.8);
    Noise angle_noise = Noise(0.0, 0.2);
    Vec2f goal = Vec2f (0,5);

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_stamp = 0.0;

    /** LaserScan msg **/
    sensor_msgs::LaserScan laserscan;
    laserscan.range_max = laser_sensor.range_max;
    laserscan.range_min = laser_sensor.range_min;
    laserscan.angle_max = laser_sensor.FOV_radian;
    laserscan.angle_min = 0.0;


    int time = -1;
    int robot_x = 1;
    int robot_y = 1;
    float x = 0.0;
    float y = 0.0;

    /** ROS node loop **/
    while (ros::ok())
    {   
        /** Initial position **/
        Vec2f depart = waypoints.front();
        waypoints.pop_front();

        /** Draw Wall segments **/
        vector_slam_msgs::LidarDisplayMsg lidar_msg;
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(cobot_gui::kColorBlack);
        }

        /** Loop until visit all waypoints **/
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            /** Extract the next waypoint **/
            Vec2f arrive = waypoints.front();
            waypoints.pop_front();

            /** Calculate curve points(trajectories) from current waypoint to the next waypoint **/
            Noise trajectories_noise = Noise(0.0, 0.01);        // For simulating noises on Odometry
            /** Separate curve points.  Ideal: Where robot think it is.  Actual: Actual position of the robot **/
            deque<Vec2f> trajectories_ideal = interpolate_curve_points(delta_t, robot_ideal, depart, arrive);
            deque<Vec2f> trajectories_actual = interpolate_curve_points(delta_t, robot, depart, arrive, true, &trajectories_noise);

            /** Traverse all curve points between point P0 and P1 **/
            while (!trajectories_ideal.empty())
            {
                /** Extract the next curve point **/
                Vec2f p_ideal = trajectories_ideal.front();
                Vec2f p_actual = trajectories_actual.front();
                trajectories_ideal.pop_front();
                trajectories_actual.pop_front();

                /** Move robot **/
                robot_ideal.move_to(p_ideal);
                // draw_robot_vector(robot_ideal, lidar_msg);
                robot.move_to(p_actual);

                /** Draw Robot's velocity **/
                lidar_msg.points_x.push_back(p_ideal.x());
                lidar_msg.points_y.push_back(p_ideal.y());
                lidar_msg.points_col.push_back(0xFFFF0000);

                lidar_msg.points_x.push_back(p_actual.x());
                lidar_msg.points_y.push_back(p_actual.y());
                lidar_msg.points_col.push_back(0xFF0000FF);

                /** Simulate scan **/
                vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
                simulate_scan(point_cloud, robot, wall_segments, laser_sensor, length_noise, angle_noise);
                sort(point_cloud.begin(), point_cloud.end(), compare_xy_Vec2f());
                point_cloud.erase( unique(point_cloud.begin(), point_cloud.end()), point_cloud.end());
                cout << "point cloud size:" << point_cloud.size() << endl;

                /** Update time delta t after one laser scan **/
                time_stamp += delta_t;

                /** Draw laser scan points **/
                for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    lidar_msg.points_x.push_back(it->x());
                    lidar_msg.points_y.push_back(it->y());
                    lidar_msg.points_col.push_back(0xFFA500FF); // Orange
                }


                /** Draft **/
                time++;
                cout << "time: " << time << endl;
                x += 0.1;
                y += 0.1;
                float l = x*x + y;
                float line_x = x + 10;
                float line_y = y + 10;
                lidar_msg.robotLocX = robot.position.x();
                lidar_msg.robotLocY = robot.position.y();
                // lidar_msg.timestamp = x;
                // lidar_msg.robotAngle = x * 10;
                // lidar_msg.windowSize = x;


                /** Publishing msgs **/
                lidar_msg_pub.publish(lidar_msg);

                auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
                cout << ctime(&timenow) << endl; 



                /** Successfull Tests **/
                // Vec2f P1 = Vec2f(0, 0);
                // Vec2f P2 = Vec2f(2, 2);
                // Vec2f P3 = Vec2f(3, 4);
                // Eigen::Matrix3f P1TP2 = get_homogeneous_transform(P1, P2);
                // Eigen::Matrix3f P2TP3 = get_homogeneous_transform(P2, P3);
                // Eigen::Matrix3f P1TP3 = get_homogeneous_transform(P1, P3);
                // Eigen::Matrix3f P3TP1 = get_homogeneous_transform(P3, P1);
                // cout << P1TP2 << endl;
                // cout << P2TP3 << endl;
                // cout << P1TP3 << endl;
                // cout << P3TP1 << endl;

                // getchar();
                // return 0;
                cout << "time_stamp: " << time_stamp << endl;
                cout << "delta_t: " << delta_t << endl;
                ros::spinOnce();
                loop_rate.sleep();
                // getchar();
            }
            depart = Vec2f(arrive);
        }

        robot.move_to(robot_init_position);
        for(deque<Vec2f>::iterator it = waypoints_backup->begin(); it != waypoints_backup->end(); ++it) {
            waypoints.push_back(*it);
        }
        cout << "arrived at:(" << robot_ideal.position.x() << ", " << robot_ideal.position.y() << ")" << endl;
        cout << "Travel finished!" << endl;
        getchar();
    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
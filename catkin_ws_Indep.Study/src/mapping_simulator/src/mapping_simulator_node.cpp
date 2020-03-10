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
    float speed = 0.1;
    Robot robot = Robot(robot_init_position, heading, speed);
    Robot robot_ideal = Robot(robot_init_position, heading, speed);
    Laser laser_sensor = Laser();
    Noise length_noise = Noise(0.0, 0.8);
    Noise angle_noise = Noise(0.0, 0.2);
    Vec2f goal = Vec2f (0,5);


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
            deque<Vec2f> trajectories_ideal = interpolate_curve_points(robot_ideal, depart, arrive);
            deque<Vec2f> trajectories_actual = interpolate_curve_points(robot, depart, arrive, true, &trajectories_noise);

            /** Loop until visit all curve points **/
            while (!trajectories_ideal.empty())
            {
                /** Extract the next curve point **/
                Vec2f p_ideal = trajectories_ideal.front();
                Vec2f p_actual = trajectories_actual.front();
                trajectories_ideal.pop_front();
                trajectories_actual.pop_front();

                /** Move robot **/
                robot_ideal.move_to(p_ideal);
                draw_robot_vector(robot_ideal, lidar_msg);
                robot.move_to(p_actual);

                /** Simulate scan **/
                vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
                simulate_scan(point_cloud, robot, wall_segments, laser_sensor, length_noise, angle_noise);
                sort(point_cloud.begin(), point_cloud.end(), compare_xy_Vec2f());
                point_cloud.erase( unique(point_cloud.begin(), point_cloud.end()), point_cloud.end());
                cout << "point cloud size:" << point_cloud.size() << endl;

                /** Draw laser scan points **/
                for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    lidar_msg.points_x.push_back(it->x());
                    lidar_msg.points_y.push_back(it->y());
                    lidar_msg.points_col.push_back(0xFFA500FF); // Orange
                }

                /** Convert Eigen::Vector2f to geometry_msg::Vector3 **/
                vector<geometry_msgs::Vector3> points;
                for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    geometry_msgs::Vector3 vec;
                    vec.x = (*it).x();
                    vec.y = (*it).y();
                    vec.z = 0;
                    points.push_back(vec);
                }
                cout << "geometry Vector3 points size:" << points.size() << endl;

                /** Draft **/
                time++;
                cout << "time: " << time << endl;
                x += 0.1;
                y += 0.1;
                float l = x*x + y;
                float line_x = x + 10;
                float line_y = y + 10;
                lidar_msg.robotLocX = robot_x++;
                lidar_msg.robotLocY = robot_y + l;
                lidar_msg.timestamp = x;
                lidar_msg.robotAngle = x * 10;
                lidar_msg.windowSize = x;


                /** Publishing msgs **/
                lidar_msg_pub.publish(lidar_msg);

                auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
                cout << ctime(&timenow) << endl; 

            }
            depart = Vec2f(arrive);
        }

        cout << "Travel finished!" << endl;
        robot.move_to(robot_init_position);
        for(deque<Vec2f>::iterator it = waypoints_backup->begin(); it != waypoints_backup->end(); ++it) {
            waypoints.push_back(*it);
        }
        ros::spinOnce();
        loop_rate.sleep();
        cout << "time: " << time << endl;

        Vec2f p1 = Vec2f(3, 3);
        Vec2f p2 = Vec2f(6, 0);
        Vec2f p3 = get_translation_vec2f(p1, p2);
        // Eigen::Matrix2f r1;
        // r1 << 2, 3, 4, 5;
        Eigen::Matrix2f r1 = get_rotation_matrix2f(degree_to_radian(45));
        Vec2f p4 = r1 * p2;
        Vec2f p5 = r1 * p4;

        cout <<"p1:" << p1 << endl;
        cout <<"p2:" << p2 << endl;
        cout <<"p3:" << p3 << endl;
        cout <<"R(45):" << r1 << endl;
        cout <<"p4:" << p4 << endl;
        cout <<"p5:" << p5 << endl;

        cout << get_homogeneous_transform(r1, p2) << endl;

        // Eigen::Matrix3f homo;
        // homo.setIdentity();
        // cout << homo << endl;
        // homo.block<2, 2>(0, 0) = r1;
        // cout << homo << endl;
        // homo.block<2, 1>(0, 2) = p1;
        // cout << homo << endl;

        // Eigen::Matrix3f homo;
        // homo.setZero();
        // // Eigen::MatrixXf append(3);
        // cout << homo << endl;
        // homo.block(0, 0, 2, 2) = r1;
        // cout << homo << endl;
        // // homo.col(2) = p1.transpose();
        // // Eigen::Vector3f trans = Eigen::Vector3f::Constant(1);
        // Eigen::Vector2f trans = Eigen::Vector2f(p1);
        // cout << trans << endl;
        // cout << trans.homogeneous() << endl;
        // trans.block(0, 0, 2, 0) = p1;
        

        // Eigen::Matrix3f m = Eigen::Matrix3f::setZero();
        // Eigen::Matrix3f m;
        // m.setZero();
        // Eigen::Matrix3f A = Eigen::Matrix3f::Constant(0.1);
        // Eigen::Vector4f b = Eigen::Vector4f::Constant(0.2), c = Eigen::Vector4f::Constant(0.3);
        // Eigen::Matrix2f homo;
        // homo << r1;
        // // homo << 1, 1, 1, 
        // //         2, 2, 2, 
        // //         3, 3, 3;
        // // homo << r1.row(1), p3.x(), r1.row(2), p3.y();
        // homo.conservativeResize(3, 5);
        // cout << "homo:" << homo << endl;

        // Eigen::Matrix4f m = Eigen::Matrix4f::Random();
        // Eigen::Matrix3f A = Eigen::Matrix3f::Constant(0.1);
        // Eigen::Vector4f b = Eigen::Vector4f::Constant(0.2), c = Eigen::Vector4f::Constant(0.3);
        // cout << m << endl << endl;
        // cout << A << endl << endl;
        // cout << b << endl << endl;
        // cout << c << endl << endl;

        // m.block(0, 0, 3, 3) = A;
        // m.col(3) = b;
        // m.row(3) = c;

        // cout << m << endl << endl;


        getchar();
    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
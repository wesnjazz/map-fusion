#include "simulator.h"
#include "segment.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>
#include <vector_slam_msgs/LidarDisplayMsg.h>
#include <vector_slam_msgs/CobotStatusMsg.h>
#include <vector_slam_msgs/LocalizationMsg.h>
#include <gui_publisher_helper.h>
#include <sensor_msgs/LaserScan.h>

int main(int argc, char **argv) 
{
    /** ROS initialization **/
    ros::init(argc, argv, "Mapping_Simulator");
    ros::NodeHandle n;
    ros::Rate loop_rate(4);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Publisher lidar_msg_pub = n.advertise<vector_slam_msgs::LidarDisplayMsg>("/VectorSLAM/VectorLocalization/Gui", 1000);
    ros::Publisher cobot_msg_pub = n.advertise<vector_slam_msgs::CobotStatusMsg>("/Cobot/Status", 1000);
    // ros::Publisher cobot_msg_pub = n.advertise<vector_slam_msgs::LocalizationMsg>("/Cobot/Status", 1000);
    ros::Publisher sensor_msgs_laserscan_pub = n.advertise<sensor_msgs::LaserScan>("sensor_msgs/LaserScan", 1);


    /** Variables **/
    vector<Segment> wall_segments;
    ifstream wall_segments_file;
    // vector<Position> trajectories;
    // ifstream trajectories_file;


    /** File loading **/
    if (argc <= 1 || 4 <= argc) {
        usage(argv[0]);
    }
    if (argc >= 2) { wall_segments_file = ifstream(argv[1]); }
    // if (argc >= 3) { trajectories_file = ifstream(argv[2]); }
    if (!wall_segments_file) { // && !trajectories_file) {
        cout << "The file [";
        if (!wall_segments_file) { cout << argv[1]; }
        // if (!trajectories_file) { cout << ", " << argv[2]; }
        cout << "] doesn't exists.\n\n";
        exit(0);
    }
    read_segments(wall_segments_file, wall_segments);
    // read_positions(trajectories_file, &trajectories);


    /** Create objects **/
    float pos_x = 0;
    float pos_y = 0;
    float angle = 0;

    Vec2f robot_init_position = Vec2f(pos_x, pos_y);
    Robot robot = Robot(robot_init_position, angle, 0.5);
    Laser laser_sensor = Laser();
    Noise length_noise = Noise(0.0, 0.8);
    Noise angle_noise = Noise(0.0, 0.2);
    // Position goal = Position (0,5);
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
        deque<Vec2f> trajectories = interpolate_curve_points(robot, goal);
        cout << "tracj size:" << trajectories.size() << endl;
        // pos_x += 0.1;
        // position.new_position(pos_x, pos_y, angle);
        // robot.move_to(position);

        while (!trajectories.empty())
        {
            time++;
            cout << "time: " << time << endl;
            vector_slam_msgs::CobotStatusMsg cobot_msg;
            cobot_msg.timestamp = x;
            cobot_msg.loc_x = robot_x;
            cobot_msg.loc_y = robot_y;
            cobot_msg.orientation = x;
            cobot_msg_pub.publish(cobot_msg);
            x += 0.1;
            cobot_msg.orientation = 
            y += 0.1;
            float l = x*x + y;
            float line_x = x + 10;
            float line_y = y + 10;
            vector_slam_msgs::LidarDisplayMsg lidar_msg;
            lidar_msg.robotLocX = robot_x++;
            lidar_msg.robotLocY = robot_y + l;
            lidar_msg.timestamp = x;
            lidar_msg.robotAngle = x * 10;
            lidar_msg.windowSize = x;
            // lidar_msg.text_x.push_back(x);
            // lidar_msg.text_y.push_back(y);
            // lidar_msg.text.push_back(to_string(x));
            // lidar_msg.lines_p1x.push_back(x+5);
            // lidar_msg.lines_p1y.push_back(y-5);
            // lidar_msg.lines_p2x.push_back(line_x);
            // lidar_msg.lines_p2y.push_back(line_y);
            // lidar_msg.circles_x.push_back(x);
            // lidar_msg.circles_y.push_back(y);
            // lidar_msg.lines_col.push_back(line_col++);
            // lidar_msg.points_x.push_back(x);
            // lidar_msg.points_y.push_back(y);

            cout << "traj size: " << trajectories.size() << endl;
            Vec2f new_pos = trajectories.front();
            trajectories.pop_front();
            robot.move_to(new_pos);
            // lidar_msg.robotLocX = robot.position.x;
            // lidar_msg.robotLocY = robot.position.y;
            // lidar_msg.robotAngle = robot.position.theta_degree;
            // while (new_pos != goal) 
            // {


            /** Draw Wall segments **/
            for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
                lidar_msg.lines_p1x.push_back(it->start.x());
                lidar_msg.lines_p1y.push_back(it->start.y());
                lidar_msg.lines_p2x.push_back(it->end.x());
                lidar_msg.lines_p2y.push_back(it->end.y());
                lidar_msg.lines_col.push_back(cobot_gui::kColorBlack);
            }


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
                // lidar_msg.points_col.push_back(0xFFFF00FF);
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


            /** Marker for rviz **/
            visualization_msgs::Marker marker;
            marker.header.frame_id = "/my_frame";
            marker.header.stamp = ros::Time::now();
            marker.ns = "basic_shapes";
            marker.id = 0;
            marker.type = visualization_msgs::Marker::POINTS;
            marker.action = visualization_msgs::Marker::ADD;
            marker.pose.orientation.w = 1.0;
            marker.lifetime = ros::Duration();
        //     // marker.pose.position.x = (*it).x;
        //     // marker.pose.position.y = (*it).y;
        //     // marker.pose.position.z = 0;
            marker.scale.x = 0.1;
            marker.scale.y = 0.1;
            // marker.scale.z = 0.1;
            marker.color.r = 0.0f;
            marker.color.g = 1.0f;
            marker.color.b = 0.0f;
            marker.color.a = 1.0f;


            /** Points for wall segments **/
            for(vector<geometry_msgs::Vector3>::iterator it=points.begin(); it !=points.end(); ++it) {
                geometry_msgs::Point p;
                p.x = (*it).x;
                p.y = (*it).y;
                p.z = (*it).z;
                marker.points.push_back(p);
            }


            /** Point for a Robot **/
            geometry_msgs::Point r;
            r.x = robot.position.x();
            r.y = robot.position.y();
            r.z = 0;
            marker.points.push_back(r);


            /** Publishing marker **/
            marker_pub.publish(marker);
            lidar_msg_pub.publish(lidar_msg);


            auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
            cout << ctime(&timenow) << endl; 

            ros::spinOnce();
            loop_rate.sleep();
        }
        cout << "Travel finished!" << endl;
        // robot.move_to(robot_init_position);
        getchar();
    }

    wall_segments_file.close();
    // trajectories_file.close();
    return 0;
}
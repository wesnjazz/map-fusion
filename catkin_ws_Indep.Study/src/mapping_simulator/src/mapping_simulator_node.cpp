#include "simulator.h"
#include "segment.h"
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
    ros::Publisher gui_laser_pub = n.advertise<vector_slam_msgs::LidarDisplayMsg>("/VectorSLAM/VectorLocalization/Gui", 100);
    ros::Publisher gui_wall_pub = n.advertise<vector_slam_msgs::LidarDisplayMsg>("/VectorSLAM/VectorLocalization/Gui", 100);


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
        vector_slam_msgs::LidarDisplayMsg gui_wall;
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            gui_wall.lines_p1x.push_back(5 + it->start.x());
            gui_wall.lines_p1y.push_back(5 + it->start.y());
            gui_wall.lines_p2x.push_back(5 + it->end.x());
            gui_wall.lines_p2y.push_back(5 + it->end.y());
            gui_wall.lines_col.push_back(cobot_gui::kColorBlack);
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
                robot.move_to(p_actual);

                /** Simulate scan **/
                vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
                simulate_scan(point_cloud, robot, wall_segments, laser_sensor, length_noise, angle_noise);
                sort(point_cloud.begin(), point_cloud.end(), compare_xy_Vec2f());
                point_cloud.erase( unique(point_cloud.begin(), point_cloud.end()), point_cloud.end());
                cout << "point cloud size:" << point_cloud.size() << endl;

                /** Draw laser scan points **/
                vector_slam_msgs::LidarDisplayMsg gui_laser;
                for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    gui_laser.points_x.push_back(it->x());
                    gui_laser.points_y.push_back(it->y());
                    gui_laser.points_col.push_back(0xFFA500FF); // Orange
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
                gui_laser.robotLocX = robot_x++;
                gui_laser.robotLocY = robot_y + l;
                gui_laser.timestamp = x;
                gui_laser.robotAngle = x * 10;
                gui_laser.windowSize = x;


                /** Publishing msgs **/
                gui_laser_pub.publish(gui_laser);
                gui_wall_pub.publish(gui_wall);

                auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
                cout << ctime(&timenow) << endl; 

            }
            depart = Vec2f(arrive);
        }

        cout << "Travel finished!" << endl;
        robot.move_to(robot_init_position);
        getchar();
        for(deque<Vec2f>::iterator it = waypoints_backup->begin(); it != waypoints_backup->end(); ++it) {
            waypoints.push_back(*it);
        }
        ros::spinOnce();
        loop_rate.sleep();
        cout << "time: " << time << endl;
    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
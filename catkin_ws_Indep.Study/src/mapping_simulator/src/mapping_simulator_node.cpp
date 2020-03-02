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

using namespace std;


int main(int argc, char **argv) 
{
    /** ROS initialization **/
    ros::init(argc, argv, "Mapping_Simulator");
    ros::NodeHandle n;
    ros::Rate loop_rate(4);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    // ifstream point_cloud_file = ifstream(argv[1]);
    // ros::Publisher cloud_pub = n.advertise<geometry_msgs::Vector3>("cloud", 1000);


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
    read_segments(wall_segments_file, &wall_segments);
    // read_positions(trajectories_file, &trajectories);


    /** Create objects **/
    double pos_x = 0;
    double pos_y = 0;
    double angle = 0;
    Position position(pos_x, pos_y, angle);

    Robot robot = Robot(position, 2);
    cout << "Robot pos:" << robot.position << endl;
    // getchar();
    Laser laser_sensor = Laser();
    Noise length_noise = Noise(0.0, 0.5);
    Noise angle_noise = Noise(0.0, 0.02);

    Position goal = Position (0,6);
    cout << "Goal:" << goal << endl;
    // getchar();
    // getchar();
    while (ros::ok())
    {   
    deque<Position> trajectories = interpolate_curve_points(robot, goal);
    cout << "tracj size:" << trajectories.size() << endl;
        // pos_x += 0.1;
        // position.new_position(pos_x, pos_y, angle);
        // robot.move_to(position);
        while (!trajectories.empty())
        {
            cout << "traj size: " << trajectories.size() << endl;
            Position new_pos = trajectories.front();
            trajectories.pop_front();
            robot.move_to(new_pos);
            // while (new_pos != goal) 
            // {
                /** Simulate scan **/
                vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
                simulate_scan(&point_cloud, &robot, &wall_segments, &laser_sensor, &length_noise, &angle_noise);
                sort(point_cloud.begin(), point_cloud.end(), compare_xy_Vec2f());
                point_cloud.erase( unique(point_cloud.begin(), point_cloud.end()), point_cloud.end());
                cout << "point cloud size:" << point_cloud.size() << endl;


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
                r.x = robot.position.x;
                r.y = robot.position.y;
                r.z = 0;
                marker.points.push_back(r);


                /** Publishing marker **/
                marker_pub.publish(marker);


                auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
                cout << ctime(&timenow) << endl; 


            // }   
        loop_rate.sleep();
        }
        cout << "Travel finished!" << endl;
        getchar();
    }

    wall_segments_file.close();
    // trajectories_file.close();
    return 0;
}
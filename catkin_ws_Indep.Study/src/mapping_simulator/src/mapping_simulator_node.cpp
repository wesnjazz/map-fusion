#include "simulator.h"
#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>

using namespace std;


int main(int argc, char **argv) 
{
    /** ROS initialization **/
    ros::init(argc, argv, "Mapping_Simulator");
    ros::NodeHandle n;
    ros::Publisher cloud_pub = n.advertise<geometry_msgs::Vector3>("cloud", 1000);
    ros::Rate loop_rate(20);
    ifstream point_cloud_file = ifstream(argv[1]);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    /** Variables **/
    vector<Segment> wall_segments;
    ifstream wall_segments_file;
    vector<Position> trajectories;
    ifstream trajectories_file;
    // vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
    // ofstream point_cloud_file;
    // Laser laser_sensor = Laser();

    /** File loading **/
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



    // int count = 0;
    // string line;
    vector<geometry_msgs::Vector3> points;
    // vector<visualization_msgs::Marker> markers;
    // while(getline(point_cloud_file, line)) {
    //     geometry_msgs::Vector3 vec;
    //     stringstream ss(line);
    //     while(getline(ss, line, ',')) {
    //         count++;
    //         switch (count)
    //         {
    //         case 1: vec.x = stof(line); break;
    //         case 2: 
    //             vec.y = stof(line); 
    //             vec.z = 0;
    //             points.push_back(vec);
    //             count = 0;
    //             break;
    //         default: break;
    //         }
    //     }
    //     cout << vec << endl;
    // }

    // vector<geometry_msgs::Vector3>::iterator it=points.begin();
    // vector<visualization_msgs::Marker>::iterator it=markers.begin();
    while (ros::ok())
    {
    //     // cout << *it << endl;
    //     // if (it == points.end()) {
    //     //     it = points.begin();
    //     // }
    //     // cloud_pub.publish(*it);
        visualization_msgs::Marker marker;
    //     uint32_t shape = visualization_msgs::Marker::CUBE;

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
        marker.scale.z = 0.1;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;

        for(vector<geometry_msgs::Vector3>::iterator it=points.begin(); it !=points.end(); ++it) {
            geometry_msgs::Point p;
            p.x = (*it).x;
            p.y = (*it).y;
            p.z = (*it).z;
            marker.points.push_back(p);
        }


        marker_pub.publish(marker);
    //     // ++it;
    //     // ros::spinOnce();
        loop_rate.sleep();
    }

    wall_segments_file.close();
    trajectories_file.close();
    // point_cloud_file.close();
    return 0;
}
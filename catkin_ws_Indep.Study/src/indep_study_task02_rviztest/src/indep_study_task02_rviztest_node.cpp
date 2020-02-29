#include <iostream>
#include <fstream>
#include <vector>
#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>

using namespace std;

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "Simulator");
    ros::NodeHandle n;
    ros::Publisher cloud_pub = n.advertise<geometry_msgs::Vector3>("cloud", 1000);
    ros::Rate loop_rate(20);
    ifstream point_cloud_file = ifstream(argv[1]);

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 100);

    int count = 0;
    string line;
    vector<geometry_msgs::Vector3> points;
    while(getline(point_cloud_file, line)) {
        geometry_msgs::Vector3 vec;
        stringstream ss(line);
        while(getline(ss, line, ',')) {
            count++;
            switch (count)
            {
            case 1: vec.x = stof(line); break;
            case 2: 
                vec.y = stof(line); 
                vec.z = 0;
                points.push_back(vec);
                count = 0;
                break;
            default: break;
            }
        }
        cout << vec << endl;
    }

    // vector<geometry_msgs::Vector3>::iterator it=points.begin();
    // vector<visualization_msgs::Marker>::iterator it=markers.begin();
    while (ros::ok())
    {
        // cout << *it << endl;
        // if (it == points.end()) {
        //     it = points.begin();
        // }
        // cloud_pub.publish(*it);
        visualization_msgs::Marker marker;
        uint32_t shape = visualization_msgs::Marker::CUBE;

        marker.header.frame_id = "/my_frame";
        marker.header.stamp = ros::Time::now();
        marker.ns = "basic_shapes";
        marker.id = 0;
        marker.type = visualization_msgs::Marker::POINTS;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.orientation.w = 1.0;
        marker.lifetime = ros::Duration();
        // marker.pose.position.x = (*it).x;
        // marker.pose.position.y = (*it).y;
        // marker.pose.position.z = 0;
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
        // ++it;
        // ros::spinOnce();
        loop_rate.sleep();
    }

    point_cloud_file.close();
    return 0;
}
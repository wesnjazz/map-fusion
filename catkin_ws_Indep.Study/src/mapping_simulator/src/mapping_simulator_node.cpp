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

// using namespace std;


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
    deque<Vec3f> waypoints;         // vector of waypoints
    ifstream waypoints_file;        // file stream of waypoints
    deque<float> robot_headings;     // deque of robot headings


    /** Create objects **/
    
    /** Sets robot's init position **/
    Vec3f robot_init_frame = waypoints.empty() ? Vec3f(0, 0, 0) : waypoints.front();
    Vec2f robot_init_position = robot_init_frame.block<2, 1>(0, 0);
    float robot_init_heading = robot_init_frame.z();
    float speed = 0.4;

    /** Sensors and Noises **/
    Laser laser_sensor = Laser();
    Noise laser_length_noise = Noise(0.0, 0.8);
    Noise laser_angle_noise = Noise(0.0, 0.2);
    Noise wheel_encoder_dx_noise = Noise(0.0, 0.001);
    Noise wheel_encoder_dy_noise = Noise(0.0, 0.002);
    WheelEncoder wheel_encoder = WheelEncoder();
    Vec3f World_frame = Vec3f(0, 0, 0);

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_stamp = 0.0;


    /** File loading **/
    if (argc <= 1 || 6 <= argc) {
        usage(argv[0]);
    }
    if (argc >= 2) { wall_segments_file = ifstream(argv[1]); }
    if (argc >= 3) { waypoints_file = ifstream(argv[2]); }
    if (argc >= 4) { speed = atof(argv[3]); }
    if (argc >= 5) { delta_t = atof(argv[4]); }
    if (!wall_segments_file) { // && !waypoints_file) {
        cout << "The file [";
        if (!wall_segments_file) { cout << argv[1]; }
        if (!waypoints_file) { cout << ", " << argv[2]; }
        cout << "] doesn't exists.\n\n";
        exit(0);
    }
    vector_slam_msgs::LidarDisplayMsg lidar_msg;
    read_segments(wall_segments_file, wall_segments);
    read_waypoints(waypoints_file, waypoints, robot_headings, lidar_msg);
    deque<Vec3f> *waypoints_backup = new deque<Vec3f>(waypoints);   // Deep copy


    Robot robot_actual = Robot(robot_init_position, robot_init_heading, speed);
    Robot robot_ideal = Robot(robot_init_position, robot_init_heading, speed);
    cout << "robot_frame:\n" << robot_ideal.robot_frame_in_Wframe << endl;

    /** LaserScan msg **/
    sensor_msgs::LaserScan laserscan;
    laserscan.range_max = laser_sensor.range_max;
    laserscan.range_min = laser_sensor.range_min;
    laserscan.angle_max = laser_sensor.FOV_radian;
    laserscan.angle_min = 0.0;

    vector<Vec2f> point_cloud;


    /** ROS node loop **/
    while (ros::ok())
    {   
        /** Initial position **/
        Vec3f departure_W = waypoints.front();
        waypoints.pop_front();

        /** Initial Transformation **/
        Mat3f initial_frame;
        Mat2f initial_rot;
        Vec2f initial_trans = Vec2f(0, 0);
        initial_rot << 1, 0, 0, 1;
        initial_frame.setIdentity();
        initial_frame.block<2, 2>(0, 0) = initial_rot;
        initial_frame.block<2, 1>(0, 2) = initial_trans;

        /** History of transformations, odometries, frames **/
        vector<Mat3f> HTs;
        vector<Vec2f> odometries;
        vector<Vec3f> frames;
        HTs.push_back(initial_frame);
        odometries.push_back(Vec2f(0, 0));
        frames.push_back(Vec3f(0, 0, 0));

        /** Draw Wall segments **/
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(0xFF99ff33);
        }

        /** Drawing Grid **/
        draw_grids(lidar_msg);
        draw_robot_vector(robot_ideal, lidar_msg);

        int round = 0;
        /** Loop untround visit all waypoints **/
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            /** Get the next waypoint **/
            Vec3f arrival_W = waypoints.front();
            waypoints.pop_front();

            while (true)
            {
                cout 
                    << "Departure:" << endl << departure_W << endl
                    << "Arrival:" << endl << arrival_W << endl
                    << "theta_robot:" << robot_ideal.heading_degree_in_Wframe << endl
                    << "theta_waypoint:" << arrival_W.z() << endl
                    ;

                /** If arrived at the waypoint, get the next waypoint **/
                if (if_arrived_at_xy_frameW(robot_ideal, arrival_W.x(), arrival_W.y(), 0.1)) {
                    cout 
                        << "\t\tArrived at point:(" << arrival_W.x() << ", " << arrival_W.y() << ")" << endl
                        << "\t\tDeparture was: (" << departure_W.x() << ", " << departure_W.y() << ")" << endl
                        << endl;
                    break;
                }

                cout << "round: " << ++round << endl;

                /** Laser Scan **/
                simulate_scan(point_cloud, robot_ideal, wall_segments, robot_ideal.sensor_laser, laser_length_noise, laser_angle_noise);
                for(vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    lidar_msg.points_x.push_back(it->x());
                    lidar_msg.points_y.push_back(it->y());
                    lidar_msg.points_col.push_back(0xFFFF5500);
                }

                /** Odometry simulation in robot frame **/
                float dx_ns = wheel_encoder_dx_noise.gaussian();
                float dy_ns = wheel_encoder_dy_noise.gaussian();
                wheel_encoder.simulate_odometry( robot_ideal.speed, delta_t, dx_ns, dy_ns );
                float dtheta_radian = cut_redundant_epsilon( ( atan2(wheel_encoder.dy, wheel_encoder.dx) ) );
                float dtheta_degree = radian_to_degree( dtheta_radian );
                float cos_dtheta = cut_redundant_epsilon( cos(dtheta_radian) );
                float sin_dtheta = cut_redundant_epsilon( sin(dtheta_radian) );


                /** New HT(homogeneous transformation matrix) in robot frame **/
                Mat2f sROTt;
                sROTt << cos_dtheta, -sin_dtheta, sin_dtheta, cos_dtheta;
                Vec2f sTRANSt = Vec2f(wheel_encoder.dx, wheel_encoder.dy);
                Mat3f current_R_HT_new_R = current_R_HT_new_R.setIdentity();
                current_R_HT_new_R.block<2, 2>(0, 0) = sROTt;
                current_R_HT_new_R.block<2, 1>(0, 2) = sTRANSt;

                /** New HT in world frame
                 *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                 *  **/
                Mat3f W_HT_R = HTs.back() * current_R_HT_new_R;
                HTs.push_back(W_HT_R);
                // cout 
                //         << "current_R_HT_new_R:" << endl << current_R_HT_new_R << endl
                //         << "W_HT_R:" << endl << W_HT_R << endl
                //         << "HTs.back:" << endl << HTs.back() << endl
                //         << endl;
                Vec3f pivot_R = Vec3f(0, 0, 1);   /** current position in the current frame **/
                Vec3f new_frame_W = W_HT_R * pivot_R;
                Vec2f new_position_W = Vec2f(new_frame_W.x(), new_frame_W.y());

                /** Move the robot **/
                robot_ideal.move_to(new_position_W);

                /** Calculate arrival_R: arrival_W in robot frame **/
                Mat3f new_HT_inverse = new_HT_inverse.setIdentity();
                Mat2f new_HT_ROT = W_HT_R.block<2, 2>(0, 0);
                Vec2f new_HT_TRANS = W_HT_R.block<2, 1>(0, 2);
                Mat2f new_HT_ROT_neg = -new_HT_ROT;
                Vec2f TRANS_in_inverse = new_HT_ROT_neg.transpose() * new_HT_TRANS;
                new_HT_inverse.block<2, 2>(0, 0) = new_HT_ROT.transpose();
                new_HT_inverse.block<2, 1>(0, 2) = TRANS_in_inverse;
                Vec2f arrival_W_only_xy = arrival_W.block<2, 1>(0, 0);
                Vec3f arrival_R = new_HT_inverse * arrival_W_only_xy.homogeneous();

                /** Get angle of goal point in robot frame **/
                float angle_goal_robot_frame_degree = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R.y(), arrival_R.x()) ));

                cout 
                    << "Departure: (" << departure_W.x() << ", " << departure_W.y() << ", " << departure_W.z() << ")" << endl
                    << "Arrival_W: (" << arrival_W.x() << ", " << arrival_W.y() << ", " << arrival_W.z() << ")" << endl
                    << "Arrival_R: (" << arrival_R.x() << ", " << arrival_R.y() << ", " << arrival_R.z() << ")" << endl
                    << "  Current: (" << robot_ideal.position_in_Wframe.x() << ", " << robot_ideal.position_in_Wframe.y() << ")" << endl
                    << " Robot's heading in W: " << robot_ideal.heading_degree_in_Wframe << endl
                    << "   Angle to goal in R: " << angle_goal_robot_frame_degree << endl
                    ;


                /** New HT(homogeneous transformation matrix) in robot frame **/
                float angle_goal_robot_frame_radian = degree_to_radian(angle_goal_robot_frame_degree / 4.0);
                float cos_adjust_heading = cut_redundant_epsilon( cos(angle_goal_robot_frame_radian) );
                float sin_adjust_heading = cut_redundant_epsilon( sin(angle_goal_robot_frame_radian) );
                Mat2f aROTb;
                aROTb << cos_adjust_heading, -sin_adjust_heading, sin_adjust_heading, cos_adjust_heading;
                Vec2f aTRANSb = Vec2f(0, 0);
                Mat3f current_HT_adjust_heading = current_HT_adjust_heading.setIdentity();
                current_HT_adjust_heading.block<2, 2>(0, 0) = aROTb;
                current_HT_adjust_heading.block<2, 1>(0, 2) = aTRANSb;

                // /** New HT in world frame
                //  *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                //  *  **/
                Mat3f new_HT_adjust_heading = HTs.back() * current_HT_adjust_heading;
                HTs.push_back(new_HT_adjust_heading);

                float new_ang_degree = cut_redundant_epsilon( radian_to_degree( acos( new_HT_adjust_heading(0,0) ) ));
                cout
                    << "new_ang:" << new_ang_degree << endl;
                    
                /** Draw robot's position and its velocity vector **/
                draw_robot_vector(robot_ideal, lidar_msg);
                lidar_msg.points_x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFF00FFFF);

                /** For debugging **/                
                // draw_grid_line_of_robot_frame(robot_ideal, W_HT_R, arrival_R, lidar_msg);

                lidar_msg.circles_x.push_back(arrival_W.x());
                lidar_msg.circles_y.push_back(arrival_W.y());
                lidar_msg.circles_col.push_back(0xFFFF00FF);

                lidar_msg.points_x.push_back(new_frame_W.x());
                lidar_msg.points_y.push_back(new_frame_W.y());
                lidar_msg.points_col.push_back(0xFFFF0000);

                lidar_msg.lines_p1x.push_back(arrival_W_only_xy.x());
                lidar_msg.lines_p1y.push_back(arrival_W_only_xy.y());
                lidar_msg.lines_p2x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.lines_p2y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.lines_col.push_back(0x229999FF);

                /** Publish lidar msg **/
                lidar_msg_pub.publish(lidar_msg);

                // draw_grid_line_of_robot_frame(robot_ideal, W_HT_R, arrival_R, lidar_msg, true);

                cout
                    << "robot heading:" << robot_ideal.heading_degree_in_Wframe << endl
                    ;

                /** timestep increasing **/
                time_stamp += delta_t;
                cout 
                    << "robot is at:(" << robot_ideal.position_in_Wframe.x() << ", " << robot_ideal.position_in_Wframe.y() << ")" << endl;
                getchar();
            }

            /** Update the next departure waypoint to the current position **/
            departure_W = arrival_W;

            ros::spinOnce();
            loop_rate.sleep();
        }

        cout << "arrived at:(" << robot_ideal.position_in_Wframe.x() << ", " << robot_ideal.position_in_Wframe.y() << ")" << endl;
        cout << "Travel finished!" << endl;
    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
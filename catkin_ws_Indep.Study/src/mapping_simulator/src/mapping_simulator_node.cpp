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
    ros::Rate loop_rate(4);
    ros::Publisher lidar_msg_pub = n.advertise<vector_slam_msgs::LidarDisplayMsg>("/VectorSLAM/VectorLocalization/Gui", 1);


    /** Map and Points **/
    vector<Segment> wall_segments;  // vector of wall segments
    ifstream wall_segments_file;    // file stream of wall segments
    deque<Vec3f> waypoints;         // vector of waypoints
    ifstream waypoints_file;        // file stream of waypoints


    /** Create objects **/
    
    /** Sets robot's init position **/
    Vec3f robot_init_frame = waypoints.empty() ? Vec3f(0, 0, 0) : waypoints.front();
    Vec2f robot_init_position = robot_init_frame.block<2, 1>(0, 0);
    float robot_init_heading = robot_init_frame.z();
    float speed = 0.4;

    /** Sensors and Noises **/
    Laser laser_sensor = Laser();
    Noise laser_length_noise = Noise(0.0, 0.8);
    Noise laser_angle_noise = Noise(0.0, 0.8);
    Noise wheel_encoder_actual_dx_noise = Noise(0.0, 0.002);
    Noise wheel_encoder_actual_dy_noise = Noise(0.0, 0.01);
    WheelEncoder wheel_encoder_actual = WheelEncoder();
    WheelEncoder wheel_encoder_ideal = WheelEncoder();
    Vec3f World_frame = Vec3f(0, 0, 0);

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_step = 0.0;


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
    read_waypoints(waypoints_file, waypoints, lidar_msg);

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
        vector<Mat3f> HTs_actual;
        vector<Mat3f> HTs_ideal;
        HTs_actual.push_back(initial_frame);
        HTs_ideal.push_back(initial_frame);

        /** Draw Wall segments **/
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(0x22555555);
        }

        /** Drawing Grid **/
        // draw_grids(lidar_msg);
        draw_robot_vector(robot_ideal, lidar_msg);
        draw_robot_vector(robot_actual, lidar_msg, 0xFFFF5555);

        int round = 0;
        /** Loop untround visit all waypoints **/
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            /** Get the next waypoint **/
            Vec3f arrival_W = waypoints.front();
            waypoints.pop_front();
            bool arrival_circle_drew = false;

            while (true)
            {
                /** If arrived at the waypoint, get the next waypoint **/
                if (if_arrived_at_xy_frameW(robot_actual, arrival_W.x(), arrival_W.y(), 0.1)) {
                    cout 
                        << "\t\tDeparture was: (" << departure_W.x() << ", " << departure_W.y() << ")" << endl
                        << "\t\t   Arrived at: (" << arrival_W.x() << ", " << arrival_W.y() << ")" << endl
                        << "\t\t  Robot speeddddd: " << robot_actual.speed << "\t delta_t: " << delta_t << endl
                        << endl;
                    break;
                }

                round++;
                

                /** Laser Scan **/
                simulate_scan(point_cloud, robot_actual, wall_segments, robot_actual.sensor_laser, laser_length_noise, laser_angle_noise);
                for(vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    lidar_msg.points_x.push_back(it->x());
                    lidar_msg.points_y.push_back(it->y());
                    lidar_msg.points_col.push_back(0xFFFF5500);
                }


                /** Odometry simulation in robot frame **/
                float dx_ns = wheel_encoder_actual_dx_noise.gaussian();
                float dy_ns = wheel_encoder_actual_dy_noise.gaussian();
                wheel_encoder_actual.simulate_odometry( robot_actual.speed, delta_t, dx_ns, dy_ns );
                float dtheta_radian_actual = cut_redundant_epsilon( ( atan2(wheel_encoder_actual.dy, wheel_encoder_actual.dx) ) );
                float cos_dtheta_actual = cut_redundant_epsilon( cos(dtheta_radian_actual) );
                float sin_dtheta_actual = cut_redundant_epsilon( sin(dtheta_radian_actual) );
                wheel_encoder_ideal.simulate_odometry( robot_ideal.speed, delta_t, 0, 0);
                float dtheta_radian_ideal = cut_redundant_epsilon( ( atan2(wheel_encoder_ideal.dy, wheel_encoder_ideal.dx) ) );
                float cos_dtheta_ideal = cut_redundant_epsilon( cos(dtheta_radian_ideal) );
                float sin_dtheta_ideal = cut_redundant_epsilon( sin(dtheta_radian_ideal) );


                /** New HT(homogeneous transformation matrix) in robot frame **/
                Mat2f sROTt_actual;
                sROTt_actual << cos_dtheta_actual, -sin_dtheta_actual, sin_dtheta_actual, cos_dtheta_actual;
                Vec2f sTRANSt_actual = Vec2f(wheel_encoder_actual.dx, wheel_encoder_actual.dy);
                Mat3f current_R_HT_new_R_actual = current_R_HT_new_R_actual.setIdentity();
                current_R_HT_new_R_actual.block<2, 2>(0, 0) = sROTt_actual;
                current_R_HT_new_R_actual.block<2, 1>(0, 2) = sTRANSt_actual;

                Mat2f sROTt_ideal;
                sROTt_ideal << cos_dtheta_ideal, -sin_dtheta_ideal, sin_dtheta_ideal, cos_dtheta_ideal;
                Vec2f sTRANSt_ideal = Vec2f(wheel_encoder_ideal.dx, wheel_encoder_ideal.dy);
                Mat3f current_R_HT_new_R_ideal = current_R_HT_new_R_ideal.setIdentity();
                current_R_HT_new_R_ideal.block<2, 2>(0, 0) = sROTt_ideal;
                current_R_HT_new_R_ideal.block<2, 1>(0, 2) = sTRANSt_ideal;


                /** New HT in world frame
                 *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                 *  **/
                Mat3f W_HT_R_actual = HTs_actual.back() * current_R_HT_new_R_actual;
                HTs_actual.pop_back();
                HTs_actual.push_back(W_HT_R_actual);
                Vec3f pivot_R_actual = Vec3f(0, 0, 1);   /** current position in the current frame **/
                Vec3f new_frame_W_actual = W_HT_R_actual * pivot_R_actual;
                Vec2f new_position_W_actual = Vec2f(new_frame_W_actual.x(), new_frame_W_actual.y());

                Mat3f W_HT_R_ideal = HTs_ideal.back() * current_R_HT_new_R_ideal;
                HTs_ideal.pop_back();
                HTs_ideal.push_back(W_HT_R_ideal);
                Vec3f pivot_R_ideal = Vec3f(0, 0, 1);   /** current position in the current frame **/
                Vec3f new_frame_W_ideal = W_HT_R_ideal * pivot_R_ideal;
                Vec2f new_position_W_ideal = Vec2f(new_frame_W_ideal.x(), new_frame_W_ideal.y());


                /** Move the robot **/
                robot_actual.move_to(new_position_W_actual);
                robot_ideal.move_to(new_position_W_ideal);


                /** Calculate arrival_R: arrival_W in robot frame **/
                Mat3f new_HT_inverse_actual = new_HT_inverse_actual.setIdentity();
                Mat2f new_HT_ROT_actual = W_HT_R_actual.block<2, 2>(0, 0);
                Vec2f new_HT_TRANS_actual = W_HT_R_actual.block<2, 1>(0, 2);
                Mat2f new_HT_ROT_actual_neg_actual = -new_HT_ROT_actual;
                Vec2f TRANS_in_inverse_actual = new_HT_ROT_actual_neg_actual.transpose() * new_HT_TRANS_actual;
                new_HT_inverse_actual.block<2, 2>(0, 0) = new_HT_ROT_actual.transpose();
                new_HT_inverse_actual.block<2, 1>(0, 2) = TRANS_in_inverse_actual;
                Vec2f arrival_W_only_xy_actual = arrival_W.block<2, 1>(0, 0);
                Vec3f arrival_R_actual = new_HT_inverse_actual * arrival_W_only_xy_actual.homogeneous();

                Mat3f new_HT_inverse_ideal = new_HT_inverse_ideal.setIdentity();
                Mat2f new_HT_ROT_ideal = W_HT_R_ideal.block<2, 2>(0, 0);
                Vec2f new_HT_TRANS_ideal = W_HT_R_ideal.block<2, 1>(0, 2);
                Mat2f new_HT_ROT_ideal_neg_ideal = -new_HT_ROT_ideal;
                Vec2f TRANS_in_inverse_ideal = new_HT_ROT_ideal_neg_ideal.transpose() * new_HT_TRANS_ideal;
                new_HT_inverse_ideal.block<2, 2>(0, 0) = new_HT_ROT_ideal.transpose();
                new_HT_inverse_ideal.block<2, 1>(0, 2) = TRANS_in_inverse_ideal;
                Vec2f arrival_W_only_xy_ideal = arrival_W.block<2, 1>(0, 0);
                Vec3f arrival_R_ideal = new_HT_inverse_ideal * arrival_W_only_xy_ideal.homogeneous();


                /** Get angle of goal point in robot frame **/
                float angle_goal_robot_frame_degree_actual = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R_actual.y(), arrival_R_actual.x()) ));
                float angle_goal_robot_frame_degree_ideal = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R_ideal.y(), arrival_R_ideal.x()) ));


                /** New HT(homogeneous transformation matrix) in robot frame **/
                float angle_goal_robot_frame_radian_actual = degree_to_radian(angle_goal_robot_frame_degree_actual / 4.0);
                float cos_adjust_heading_actual = cut_redundant_epsilon( cos(angle_goal_robot_frame_radian_actual) );
                float sin_adjust_heading_actual = cut_redundant_epsilon( sin(angle_goal_robot_frame_radian_actual) );
                Mat2f aROTb_actual;
                aROTb_actual << cos_adjust_heading_actual, -sin_adjust_heading_actual, sin_adjust_heading_actual, cos_adjust_heading_actual;
                Vec2f aTRANSb_actual = Vec2f(0, 0);
                Mat3f current_HT_adjust_heading_actual = current_HT_adjust_heading_actual.setIdentity();
                current_HT_adjust_heading_actual.block<2, 2>(0, 0) = aROTb_actual;
                current_HT_adjust_heading_actual.block<2, 1>(0, 2) = aTRANSb_actual;

                float angle_goal_robot_frame_radian_ideal = degree_to_radian(angle_goal_robot_frame_degree_ideal / 4.0);
                float cos_adjust_heading_ideal = cut_redundant_epsilon( cos(angle_goal_robot_frame_radian_ideal) );
                float sin_adjust_heading_ideal = cut_redundant_epsilon( sin(angle_goal_robot_frame_radian_ideal) );
                Mat2f aROTb_ideal;
                aROTb_ideal << cos_adjust_heading_ideal, -sin_adjust_heading_ideal, sin_adjust_heading_ideal, cos_adjust_heading_ideal;
                Vec2f aTRANSb_ideal = Vec2f(0, 0);
                Mat3f current_HT_adjust_heading_ideal = current_HT_adjust_heading_ideal.setIdentity();
                current_HT_adjust_heading_ideal.block<2, 2>(0, 0) = aROTb_ideal;
                current_HT_adjust_heading_ideal.block<2, 1>(0, 2) = aTRANSb_ideal;


                // /** New HT in world frame
                //  *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                //  *  **/
                Mat3f new_HT_adjust_heading_actual = HTs_actual.back() * current_HT_adjust_heading_actual;
                HTs_actual.pop_back();
                HTs_actual.push_back(new_HT_adjust_heading_actual);

                Mat3f new_HT_adjust_heading_ideal = HTs_ideal.back() * current_HT_adjust_heading_ideal;
                HTs_ideal.pop_back();
                HTs_ideal.push_back(new_HT_adjust_heading_ideal);

                    
                /** Draw robot's position and its velocity vector **/
                draw_robot_vector(robot_actual, lidar_msg, 0xFF5555FF);
                lidar_msg.points_x.push_back(robot_actual.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_actual.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFF5555FF);
                draw_robot_vector(robot_ideal, lidar_msg, 0xFFFF5555);
                lidar_msg.points_x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFFFF5555);
                if (!arrival_circle_drew) {
                    lidar_msg.circles_x.push_back(arrival_W.x());
                    lidar_msg.circles_y.push_back(arrival_W.y());
                    lidar_msg.circles_col.push_back(0xFFFF00FF);
                    arrival_circle_drew = true;
                }

                /** For debugging **/                
                // draw_grid_line_of_robot_frame(robot_actual, W_HT_R_actual, arrival_R, lidar_msg);


                /** Publish lidar msg **/
                lidar_msg_pub.publish(lidar_msg);

                /** Deletes drawing **/
                // Deletes robot points
                // lidar_msg.points_x.pop_back();
                // lidar_msg.points_y.pop_back();
                // lidar_msg.points_col.pop_back();
                // Deletes robot velocity
                lidar_msg.lines_p1x.pop_back();
                lidar_msg.lines_p1y.pop_back();
                lidar_msg.lines_p2x.pop_back();
                lidar_msg.lines_p2y.pop_back();
                lidar_msg.lines_col.pop_back();
                lidar_msg.lines_p1x.pop_back();
                lidar_msg.lines_p1y.pop_back();
                lidar_msg.lines_p2x.pop_back();
                lidar_msg.lines_p2y.pop_back();
                lidar_msg.lines_col.pop_back();
                lidar_msg.lines_p1x.pop_back();
                lidar_msg.lines_p1y.pop_back();
                lidar_msg.lines_p2x.pop_back();
                lidar_msg.lines_p2y.pop_back();
                lidar_msg.lines_col.pop_back();

                lidar_msg.lines_p1x.pop_back();
                lidar_msg.lines_p1y.pop_back();
                lidar_msg.lines_p2x.pop_back();
                lidar_msg.lines_p2y.pop_back();
                lidar_msg.lines_col.pop_back();
                lidar_msg.lines_p1x.pop_back();
                lidar_msg.lines_p1y.pop_back();
                lidar_msg.lines_p2x.pop_back();
                lidar_msg.lines_p2y.pop_back();
                lidar_msg.lines_col.pop_back();
                lidar_msg.lines_p1x.pop_back();
                lidar_msg.lines_p1y.pop_back();
                lidar_msg.lines_p2x.pop_back();
                lidar_msg.lines_p2y.pop_back();
                lidar_msg.lines_col.pop_back();


                /** timestep increasing **/
                time_step += delta_t;
                ros::spinOnce();
                loop_rate.sleep();
            }

            /** Update the next departure waypoint to the current position **/
            departure_W = arrival_W;

        }

        cout 
            << "arrived at:(" << robot_actual.position_in_Wframe.x() << ", " << robot_actual.position_in_Wframe.y() << ")" << endl;
        cout << "Travel finished!" << endl;
        cout << "Press to continue...";
        getchar();
    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
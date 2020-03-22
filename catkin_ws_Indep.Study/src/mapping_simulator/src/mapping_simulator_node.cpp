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
    ros::Rate loop_rate(40);
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
    Noise laser_length_noise = Noise(0.0, 0.05);
    Noise laser_angle_noise = Noise(0.0, 0.005);
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
    // cout << "robot_frame:\n" << robot_ideal.robot_frame_in_Wframe << endl;

    /** LaserScan msg **/
    sensor_msgs::LaserScan laserscan;
    laserscan.range_max = laser_sensor.range_max;
    laserscan.range_min = laser_sensor.range_min;
    laserscan.angle_max = laser_sensor.FOV_radian;
    laserscan.angle_min = 0.0;

    // vector<Vec2f> point_cloud;
    // point_cloud.reserve(9990000);

    /** ROS node loop **/
    while (ros::ok())
    {   
        /** Initial position **/
        Vec3f departure_W = waypoints.front();
        waypoints.pop_front();


        // float init_angle_degree = departure_W.z();
        // float cos_init_angle_degree = cut_redundant_epsilon(degree_to_radian( cos(init_angle_degree) ));
        // float sin_init_angle_degree = cut_redundant_epsilon(degree_to_radian( sin(init_angle_degree) ));
        // Mat2f init_ROT;  // pure ROT in Rframe
        // init_ROT << cos_init_angle_degree, -sin_init_angle_degree, sin_init_angle_degree, cos_init_angle_degree;
        // Vec2f init_position = Vec2f(departure_W.x(), departure_W.y()); 
        // Mat3f init_HT = init_HT.setIdentity();
        // init_HT.block<2, 2>(0, 0) = init_ROT;
        // init_HT.block<3, 1>(0, 2) = init_position.homogeneous();
        // cout << "departure_W:\n" << departure_W << endl;
        // robot_actual.move_to(init_position);
        // robot_ideal.move_to(init_position);

        /** Initial Transformation **/
        Mat3f initial_frame;
        Mat2f initial_rot;
        Vec2f initial_trans = Vec2f(0, 0);
        initial_rot << 1, 0, 0, 1;
        initial_frame.setIdentity();
        initial_frame.block<2, 2>(0, 0) = initial_rot;
        initial_frame.block<2, 1>(0, 2) = initial_trans;

        /** History of homogeneous transformations HT **/
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
        // draw_robot_vector(robot_ideal, lidar_msg);
        // draw_robot_vector(robot_actual, lidar_msg, 0xFFFF5555);

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
                /** Draw robot's position and its velocity vector **/
                draw_robot_vector(robot_actual, lidar_msg, 0xFF5555FF);
                lidar_msg.points_x.push_back(robot_actual.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_actual.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFFFF5555);
                draw_robot_vector(robot_ideal, lidar_msg, 0xFFFF5555);
                lidar_msg.points_x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFF5555FF);
                if (!arrival_circle_drew) {
                    lidar_msg.circles_x.push_back(arrival_W.x());
                    lidar_msg.circles_y.push_back(arrival_W.y());
                    lidar_msg.circles_col.push_back(0xFFFF00FF);
                    arrival_circle_drew = true;
                }

                /** If arrived at the waypoint, get the next waypoint **/
                if (if_arrived_at_xy_frameW(robot_actual, arrival_W.x(), arrival_W.y(), 0.2)) {
                    cout 
                        << "\t Departure was: (" << departure_W.x() << ", " << departure_W.y() << ")" << endl
                        << "\t    Arrived at: (" << arrival_W.x() << ", " << arrival_W.y() << ")"
                        << "\t\tActual position:(" << robot_actual.position_in_Wframe.x() << ", " << robot_actual.position_in_Wframe.y() << ")" << endl
                        << "\t Robot speed: " << robot_actual.speed 
                        << " delta_t: " << delta_t << endl
                        << endl;
                    break;
                }

                round++;

                vector<Vec2f> point_cloud;
                point_cloud.reserve(90000);


                /** Laser Scan **/
                simulate_scan(point_cloud, robot_actual, wall_segments, robot_actual.sensor_laser, laser_length_noise, laser_angle_noise);
                for(vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    lidar_msg.points_x.push_back(it->x());
                    lidar_msg.points_y.push_back(it->y());
                    lidar_msg.points_col.push_back(0xFFFF5500);
                }
                // lidar_msg_pub.publish(lidar_msg);
                // getchar();
                

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


                /** Check collison **/
                // point_cloud, robot, HTs
                int num_collides = 0;
                int if_collides = false;
                float angle = robot_actual.heading_degree_in_Wframe;
            do {
                for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it)
                {
                    float x_diff = it->x() - robot_actual.position_in_Wframe.x();
                    float y_diff = it->y() - robot_actual.position_in_Wframe.y();
                    float angle_degree_between_laser_scan_and_velocity 
                        = cut_redundant_epsilon( 
                          radian_to_degree( atan2( y_diff, x_diff ) ));
                    float squared_length_robot_to_laserscanpoint
                        = cut_redundant_epsilon( y_diff * y_diff + x_diff * x_diff );
                    float squared_velocity_length 
                        = get_vector_length(robot_actual.velocity_in_Wframe) * get_vector_length(robot_actual.velocity_in_Wframe);
                    if (squared_length_robot_to_laserscanpoint < squared_velocity_length)
                    {
                        num_collides += 1;
                        if (num_collides > 50) {
                            if_collides = true;
                            angle += 15;
                            // robot_actual.set_heading(robot_actual.heading_degree_in_Wframe + 15);
                            // draw_robot_vector(robot_actual, lidar_msg, 0xFF987654);
                            // robot_ideal.set_heading(robot_ideal.heading_degree_in_Wframe + 15);
                            // draw_robot_vector(robot_ideal, lidar_msg, 0xFF456789);
                            // lidar_msg_pub.publish(lidar_msg);
                            // it = point_cloud.begin();
                            break;
                            // continue;
                        }
                        // if_collides = false;
                        // break;
                    } else {
                        if_collides = false;
                    }
                }
                break;
            } while (if_collides);

                angle = robot_actual.heading_degree_in_Wframe;

                //         // angle += 45; 
                //         // float adjust_heading_radian = 0.0f;
                //         // float abs_angle = fabs( angle_degree_between_laser_scan_and_velocity );
                //         // if (0.0f <= angle && angle <= 90.0f ||
                //         //     -90.0f <= angle && angle <= 0.0f)
                //         // {
                //         //     angle = robot_actual.heading_radian_in_Wframe + 90.0f;
                //         // }
                //         // else
                //         // {
                //         //     angle = robot_actual.heading_radian_in_Wframe - 90.0f;
                //         // }
                //         // else if (0.0f > angle_degree_between_laser_scan_and_velocity 
                //         //               && angle_degree_between_laser_scan_and_velocity >= -90.0f)
                //         // {
                //         //     adjust_heading_radian = degree_to_radian( -45.0f );
                //         // }
                //         // else if (-90.0f > angle_degree_between_laser_scan_and_velocity 
                //         //               && angle_degree_between_laser_scan_and_velocity >= -180.0f)
                //         // {
                //         //     adjust_heading_radian = degree_to_radian( -45.0f );
                //         // }
                //         // float cos_adjust_heading = cut_redundant_epsilon( cos( degree_to_radian( angle)) );
                //         // float sin_adjust_heading = cut_redundant_epsilon( sin( degree_to_radian( angle)) );
                //         // Mat2f pure_rotation;
                //         // pure_rotation << cos_adjust_heading, -sin_adjust_heading, sin_adjust_heading, cos_adjust_heading;
                //         // Mat3f rotation_HT = rotation_HT.setIdentity();
                //         // rotation_HT.block<2, 2>(0, 0) = pure_rotation;
                //         // rotation_HT.block<2, 1>(0, 2) = Vec2f(0, 0);
                //         // // // cout << HTs_actual.back() << endl;
                //         // // // cout << rotation_HT << endl;
                //         // cut_redundant_epsilon_Mat3f(rotation_HT);
                //         // Mat3f accumulated_frame_HT_rotated_frame = HTs_actual.back() * rotation_HT;
                //         // HTs_actual.pop_back();
                //         // HTs_actual.push_back(accumulated_frame_HT_rotated_frame);
                //         // HTs_ideal.pop_back();
                //         // HTs_ideal.push_back(accumulated_frame_HT_rotated_frame);
                //         // // robot_actual.set_heading(angle);
                //         // // robot_actual.set_velocity();
                //         // draw_robot_vector(robot_actual, lidar_msg, 0xFF99CCAA);
                //         // draw_robot_vector(robot_ideal, lidar_msg, 0xFFAA99CC);
                //         // lidar_msg_pub.publish(lidar_msg);
                //         // break;
                //     // }
                //     // getchar();
                // }

                if (if_collides) {
                    // if (0.0f <= angle && angle <= 90.0f ||
                    //     -90.0f <= angle && angle <= 0.0f)
                    // {
                    //     angle = robot_actual.heading_radian_in_Wframe + 180.0f;
                    // }
                    // else
                    // {
                    //     angle = robot_actual.heading_radian_in_Wframe - 180.0f;
                    // }

                    angle += 45;
                    float cos_adjust_heading = cut_redundant_epsilon( cos( degree_to_radian( angle)) );
                    float sin_adjust_heading = cut_redundant_epsilon( sin( degree_to_radian( angle)) );
                    Mat2f pure_rotation;
                    pure_rotation << cos_adjust_heading, -sin_adjust_heading, sin_adjust_heading, cos_adjust_heading;
                    Mat3f rotation_HT = rotation_HT.setIdentity();
                    rotation_HT.block<2, 2>(0, 0) = pure_rotation;
                    rotation_HT.block<2, 1>(0, 2) = Vec2f(0, 0);
                    // // cout << HTs_actual.back() << endl;
                    // // cout << rotation_HT << endl;
                    cut_redundant_epsilon_Mat3f(rotation_HT);
                    Mat3f accumulated_frame_HT_rotated_frame = HTs_actual.back() * rotation_HT;
                    HTs_actual.pop_back();
                    HTs_actual.push_back(accumulated_frame_HT_rotated_frame);
                    HTs_ideal.pop_back();
                    HTs_ideal.push_back(accumulated_frame_HT_rotated_frame);
                    // robot_actual.set_heading(angle);
                    // robot_actual.set_velocity();
                    // draw_robot_vector(robot_actual, lidar_msg, 0xFF99CCAA);
                    // draw_robot_vector(robot_ideal, lidar_msg, 0xFFAA99CC);
                    // lidar_msg_pub.publish(lidar_msg);
                    // simulate_scan(point_cloud, robot_actual, wall_segments, robot_actual.sensor_laser, laser_length_noise, laser_angle_noise);
                    
                    // if_collides = false;
                    // break;
                }

                /** HT(homogeneous transformation matrix) from Current frame to Next frame written in Robot frame **/
                /** HT: pure ROT in Rframe + pure TRANS in Rframe **/
                /** Robot_actual **/
                /** Pure rotation in Rframe: from current -> next **/
                Mat2f current_frame_ROT_next_frame_inRframe_actual;
                current_frame_ROT_next_frame_inRframe_actual << cos_dtheta_actual, -sin_dtheta_actual, sin_dtheta_actual, cos_dtheta_actual;
                /** Pure translation in Rframe: from current -> next **/
                Vec2f current_frame_TRANS_next_frame_in_Rframe_actual = Vec2f(wheel_encoder_actual.dx, wheel_encoder_actual.dy);
                /** HT: current -> next **/
                Mat3f current_frame_HT_next_frame_in_Rframe_actual = current_frame_HT_next_frame_in_Rframe_actual.setIdentity();
                current_frame_HT_next_frame_in_Rframe_actual.block<2, 2>(0, 0) = current_frame_ROT_next_frame_inRframe_actual;
                current_frame_HT_next_frame_in_Rframe_actual.block<2, 1>(0, 2) = current_frame_TRANS_next_frame_in_Rframe_actual;

                /** Robot_ideal **/
                /** Pure rotation in Rframe: from current -> next **/
                Mat2f current_frame_ROT_next_frame_inRframe_ideal;
                current_frame_ROT_next_frame_inRframe_ideal << cos_dtheta_ideal, -sin_dtheta_ideal, sin_dtheta_ideal, cos_dtheta_ideal;
                /** Pure translation in Rframe: from current -> next **/
                Vec2f current_frame_TRANS_next_frame_in_Rframe_ideal = Vec2f(wheel_encoder_ideal.dx, wheel_encoder_ideal.dy);
                Mat3f current_frame_HT_next_frame_in_Rframe_ideal = current_frame_HT_next_frame_in_Rframe_ideal.setIdentity();
                current_frame_HT_next_frame_in_Rframe_ideal.block<2, 2>(0, 0) = current_frame_ROT_next_frame_inRframe_ideal;
                current_frame_HT_next_frame_in_Rframe_ideal.block<2, 1>(0, 2) = current_frame_TRANS_next_frame_in_Rframe_ideal;


                /** New HT in World frame
                 *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                 *  **/
                /** Robot_actual **/
                /** Accumulated HT: last HT * current HT in World frame **/
                Mat3f accumulated_frames_HT_next_frame_in_Wframe_actual = HTs_actual.back() * current_frame_HT_next_frame_in_Rframe_actual;
                /** Replace old HT to new HT **/
                HTs_actual.pop_back();
                HTs_actual.push_back(accumulated_frames_HT_next_frame_in_Wframe_actual);
                Vec3f next_position_with_extra_1_in_Wframe_actual = accumulated_frames_HT_next_frame_in_Wframe_actual * Vec3f(0, 0, 1);  // Pure Translation // current position in Rframe is always (0, 0)
                Vec2f next_position_in_Wframe_actual = Vec2f(next_position_with_extra_1_in_Wframe_actual.x(), next_position_with_extra_1_in_Wframe_actual.y());    // cut unnecessary third element

                /** Robot_ideal **/
                Mat3f accumulated_frames_HT_next_frame_in_Wframe_ideal = HTs_ideal.back() * current_frame_HT_next_frame_in_Rframe_ideal;
                HTs_ideal.pop_back();
                HTs_ideal.push_back(accumulated_frames_HT_next_frame_in_Wframe_ideal);
                Vec3f next_position_with_extra_1_in_Wframe_ideal = accumulated_frames_HT_next_frame_in_Wframe_ideal * Vec3f(0, 0, 1);
                Vec2f next_position_in_Wframe_ideal = Vec2f(next_position_with_extra_1_in_Wframe_ideal.x(), next_position_with_extra_1_in_Wframe_ideal.y());


                /** Move the robot **/
                robot_actual.move_to(next_position_in_Wframe_actual);
                robot_ideal.move_to(next_position_in_Wframe_ideal);


                /** Robot moved to the new frame, but needs to adjust its heading too by another HT(contains only ROT) **/
                /** To get the Pure Rotation, robot needs to know next location in its R frame **/
                /** HT inverse: To transform arrival_W to Robot frame **/
                /** HT_inverse: [R_transpose | -R_transpose * p ] p: translation **/
                /**             [      0     |                1 ] **/
                /** Robot_actual **/
                Mat3f new_HT_inverse_actual = new_HT_inverse_actual.setIdentity();
                /** Extract rotation R and translation T for the independent calculation **/
                Mat2f new_HT_ROT_actual = accumulated_frames_HT_next_frame_in_Wframe_actual.block<2, 2>(0, 0);  // R
                Vec2f new_HT_TRANS_actual = accumulated_frames_HT_next_frame_in_Wframe_actual.block<2, 1>(0, 2);    // p
                Mat2f new_HT_ROT_actual_neg_actual = -new_HT_ROT_actual;    // -R
                /** Pure Translation in the R_inverse: -R_transpose * p **/
                Vec2f TRANS_in_inverse_actual = new_HT_ROT_actual_neg_actual.transpose() * new_HT_TRANS_actual;
                /** Assign rotation and translation of the inverse **/
                new_HT_inverse_actual.block<2, 2>(0, 0) = new_HT_ROT_actual.transpose();
                new_HT_inverse_actual.block<2, 1>(0, 2) = TRANS_in_inverse_actual;
                /** To avoid miscalculating by the third element(it's the angle in waypoint data) in Vec3f, make Vec2f first and then use Vec2f.homogenous() **/
                Vec2f arrival_W_only_xy_actual = arrival_W.block<2, 1>(0, 0);
                /** Result: (x in R frame, y in R frame, 1) **/
                /** pure TRANS in Rframe **/
                Vec3f arrival_R_actual = new_HT_inverse_actual * arrival_W_only_xy_actual.homogeneous();

                /** Robot_ideal **/
                Mat3f new_HT_inverse_ideal = new_HT_inverse_ideal.setIdentity();
                Mat2f new_HT_ROT_ideal = accumulated_frames_HT_next_frame_in_Wframe_ideal.block<2, 2>(0, 0);
                Vec2f new_HT_TRANS_ideal = accumulated_frames_HT_next_frame_in_Wframe_ideal.block<2, 1>(0, 2);
                Mat2f new_HT_ROT_ideal_neg_ideal = -new_HT_ROT_ideal;
                Vec2f TRANS_in_inverse_ideal = new_HT_ROT_ideal_neg_ideal.transpose() * new_HT_TRANS_ideal;
                new_HT_inverse_ideal.block<2, 2>(0, 0) = new_HT_ROT_ideal.transpose();
                new_HT_inverse_ideal.block<2, 1>(0, 2) = TRANS_in_inverse_ideal;
                Vec2f arrival_W_only_xy_ideal = arrival_W.block<2, 1>(0, 0);
                Vec3f arrival_R_ideal = new_HT_inverse_ideal * arrival_W_only_xy_ideal.homogeneous();


                /** Get angle between robot's heading(always 0 in R frame) and next location in Robot frame **/
                float angle_degree_to_next_point_in_Robot_frame_actual = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R_actual.y(), arrival_R_actual.x()) ));
                float angle_degree_to_next_point_in_Robot_frame_ideal = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R_ideal.y(), arrival_R_ideal.x()) ));


                /** New HT(homogeneous transformation matrix) in robot frame **/
                /** Pure Rotation: adjusted heading rather than rotating towards the next point directly **/
                /** Robot_actual **/
                float adjust_angle_radian_to_next_point_in_Robot_frame_actual = degree_to_radian(angle_degree_to_next_point_in_Robot_frame_actual / 4.0);
                float cos_adjusted_heading_actual = cut_redundant_epsilon( cos(adjust_angle_radian_to_next_point_in_Robot_frame_actual) );
                float sin_adjusted_heading_actual = cut_redundant_epsilon( sin(adjust_angle_radian_to_next_point_in_Robot_frame_actual) );
                Mat2f current_heading_ROT_adjusted_heading_actual;  // pure ROT in Rframe
                current_heading_ROT_adjusted_heading_actual << cos_adjusted_heading_actual, -sin_adjusted_heading_actual, sin_adjusted_heading_actual, cos_adjusted_heading_actual;
                /** Robot_ideal **/
                float adjust_angle_radian_to_next_point_in_Robot_frame_ideal = degree_to_radian(angle_degree_to_next_point_in_Robot_frame_ideal / 4.0);
                float cos_adjusted_heading_ideal = cut_redundant_epsilon( cos(adjust_angle_radian_to_next_point_in_Robot_frame_ideal) );
                float sin_adjusted_heading_ideal = cut_redundant_epsilon( sin(adjust_angle_radian_to_next_point_in_Robot_frame_ideal) );
                Mat2f current_heading_ROT_adjusted_heading_ideal;
                current_heading_ROT_adjusted_heading_ideal << cos_adjusted_heading_ideal, -sin_adjusted_heading_ideal, sin_adjusted_heading_ideal, cos_adjusted_heading_ideal;


                /** HT: Homogeneous Transformation from current frame to the next frame **/
                /** Robot_actual **/
                Mat3f current_frame_HT_only_ROT_next_frame_in_Rframe_actual = current_frame_HT_only_ROT_next_frame_in_Rframe_actual.setIdentity();
                current_frame_HT_only_ROT_next_frame_in_Rframe_actual.block<2, 2>(0, 0) = current_heading_ROT_adjusted_heading_actual;
                current_frame_HT_only_ROT_next_frame_in_Rframe_actual.block<3, 1>(0, 2) = Vec3f(0, 0, 1);
                /** Robot_ideal **/
                Mat3f current_frame_HT_only_ROT_next_frame_in_Rframe_ideal = current_frame_HT_only_ROT_next_frame_in_Rframe_ideal.setIdentity();
                current_frame_HT_only_ROT_next_frame_in_Rframe_ideal.block<2, 2>(0, 0) = current_heading_ROT_adjusted_heading_ideal;
                current_frame_HT_only_ROT_next_frame_in_Rframe_ideal.block<3, 1>(0, 2) = Vec3f(0, 0, 1);


                // /** New HT in world frame
                //  *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                //  *  **/
                accumulated_frames_HT_next_frame_in_Wframe_actual = HTs_actual.back() * current_frame_HT_only_ROT_next_frame_in_Rframe_actual;
                HTs_actual.pop_back();
                HTs_actual.push_back(accumulated_frames_HT_next_frame_in_Wframe_actual);

                accumulated_frames_HT_next_frame_in_Wframe_ideal = HTs_ideal.back() * current_frame_HT_only_ROT_next_frame_in_Rframe_ideal;
                HTs_ideal.pop_back();
                HTs_ideal.push_back(accumulated_frames_HT_next_frame_in_Wframe_ideal);


                /** For debugging **/                
                // draw_grid_line_of_robot_frame(robot_actual, accumulated_frames_HT_next_frame_in_Wframe_actual, arrival_R, lidar_msg);


                /** Publish lidar msg **/
                lidar_msg_pub.publish(lidar_msg);

                /** Clear robot points **/
                // lidar_msg.points_x.pop_back();
                // lidar_msg.points_y.pop_back();
                // lidar_msg.points_col.pop_back();

                /** Clear robot velocity **/
                // lidar_msg.lines_p1x.pop_back();
                // lidar_msg.lines_p1y.pop_back();
                // lidar_msg.lines_p2x.pop_back();
                // lidar_msg.lines_p2y.pop_back();
                // lidar_msg.lines_col.pop_back();
                // lidar_msg.lines_p1x.pop_back();
                // lidar_msg.lines_p1y.pop_back();
                // lidar_msg.lines_p2x.pop_back();
                // lidar_msg.lines_p2y.pop_back();
                // lidar_msg.lines_col.pop_back();
                // lidar_msg.lines_p1x.pop_back();
                // lidar_msg.lines_p1y.pop_back();
                // lidar_msg.lines_p2x.pop_back();
                // lidar_msg.lines_p2y.pop_back();
                // lidar_msg.lines_col.pop_back();

                // lidar_msg.lines_p1x.pop_back();
                // lidar_msg.lines_p1y.pop_back();
                // lidar_msg.lines_p2x.pop_back();
                // lidar_msg.lines_p2y.pop_back();
                // lidar_msg.lines_col.pop_back();
                // lidar_msg.lines_p1x.pop_back();
                // lidar_msg.lines_p1y.pop_back();
                // lidar_msg.lines_p2x.pop_back();
                // lidar_msg.lines_p2y.pop_back();
                // lidar_msg.lines_col.pop_back();
                // lidar_msg.lines_p1x.pop_back();
                // lidar_msg.lines_p1y.pop_back();
                // lidar_msg.lines_p2x.pop_back();
                // lidar_msg.lines_p2y.pop_back();
                // lidar_msg.lines_col.pop_back();

                // getchar();
                /** timestep increasing **/
                time_step += delta_t;
                ros::spinOnce();
                loop_rate.sleep();
            }
            // cout 
                // << "point_cloud size: " << point_cloud.size() << endl;
            // if (collide) { continue; }

            /** Update the next departure waypoint to the current position **/
            departure_W = arrival_W;


            /** Clear trajectories **/
            // lidar_msg.points_x.clear();
            // lidar_msg.points_y.clear();
            // lidar_msg.points_col.clear();
            /** Clear circles **/
            lidar_msg.circles_x.clear();
            lidar_msg.circles_y.clear();
            lidar_msg.circles_col.clear();

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
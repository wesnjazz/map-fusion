#include "simulator.h"
#include "segment.h"
#include "transformation.h"
#include "wheelencoder.h"
#include "image.h"
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
#include "CImg.h"

// using namespace std;
using namespace cimg_library;


int main(int argc, char **argv) 
{
    /** ROS initialization **/
    ros::init(argc, argv, "Mapping_Simulator");
    ros::NodeHandle n;
    ros::Rate loop_rate(20);
    ros::Publisher lidar_msg_pub = n.advertise<vector_slam_msgs::LidarDisplayMsg>("/VectorSLAM/VectorLocalization/Gui", 1);
    vector_slam_msgs::LidarDisplayMsg lidar_msg;


    /** Containers for Map and Way Points **/
    vector<Segment> wall_segments;  // vector of wall segments
    ifstream wall_segments_file;    // file stream of wall segments
    deque<Vec3f> waypoints;         // vector of waypoints  // dequeue for FIFO
    ifstream waypoints_file;        // file stream of waypoints
    ifstream Robot_frame_file;

    /** Sensors **/ 
    Laser laser_sensor = Laser();
    WheelEncoder wheel_encoder___actual = WheelEncoder();
    WheelEncoder wheel_encoder___ideal = WheelEncoder();
    /** Noises **/
    Noise laser_length_noise = Noise(0.0, 0.01);
    Noise laser_angle_noise = Noise(0.0, 0.005);
    Noise wheel_encoder___actual_dx_noise = Noise(-0.001, 0.004);
    Noise wheel_encoder___actual_dy_noise = Noise(-0.002, 0.2);
    /** No Noises **/
    // Noise laser_length_noise = Noise(0.0, 0.0);
    // Noise laser_angle_noise = Noise(0.0, 0.0);
    // Noise wheel_encoder___actual_dx_noise = Noise(0.0, 0.0);
    // Noise wheel_encoder___actual_dy_noise = Noise(0.0, 0.0);

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_step = 0.0;
    float speed = 0.4;

    /** File loading **/
    if (argc <= 1 || 7 <= argc) {
        usage(argv[0]);
    }
    bool origin_transformed = false;
    if (argc >= 2) { wall_segments_file = ifstream(argv[1]); }
    if (argc >= 3) { waypoints_file = ifstream(argv[2]); }
    if (argc >= 4) { speed = atof(argv[3]); }
    if (argc >= 5) { delta_t = atof(argv[4]); }
    if (argc >= 6) { Robot_frame_file = ifstream(argv[5]); origin_transformed = true; }
    if (!wall_segments_file) { // && !waypoints_file) {
        cout << "The file [";
        if (!wall_segments_file) { cout << argv[1]; }
        if (!waypoints_file) { cout << ", " << argv[2]; }
        cout << "] doesn't exists.\n\n";
        exit(0);
    }


    /** World frame and Transformed World frame(Robot_frame) **/
    Vec3f World_frame = Vec3f(0, 0, 0);
    Vec3f Robot_frame = read_Robot_frame(Robot_frame_file);
    Mat3f HT_World_frame_to_Robot_frame = get_HT_Aframe_to_Bframe(World_frame, Robot_frame);


    /** Read Map (Wall Segments) and Way Points **/
    read_segments(wall_segments_file, wall_segments, origin_transformed, &Robot_frame);
    read_waypoints(waypoints_file, waypoints, origin_transformed, &Robot_frame);
    wall_segments_file.close();
    waypoints_file.close();
    Robot_frame_file.close();


    /** History of homogeneous transformations HT **/
    const int HTs_size = 99000;
    vector<Mat3f> HTs___actual;
    vector<Mat3f> HTs___ideal;
    HTs___actual.reserve(HTs_size);
    HTs___ideal.reserve(HTs_size);


    /** Initial position **/
    Vec3f departure_W = waypoints.front();
    waypoints.pop_front();
    Mat3f initial_frame = get_HT_Aframe_to_Bframe(World_frame, departure_W);
    Vec2f init_pos = Vec2f(departure_W.x(), departure_W.y());
    HTs___actual.push_back(initial_frame);
    HTs___ideal.push_back(initial_frame);
   

    /** Robot objects **/
    Robot robot___actual = Robot(init_pos, departure_W.z(), speed);
    robot___actual.move_to(init_pos);
    robot___actual.set_heading(departure_W.z());
    robot___actual.speed_normal = speed;
    robot___actual.speed_low = speed / 2.0f;
    Robot robot___ideal = Robot(init_pos, departure_W.z(), speed);
    robot___ideal.move_to(init_pos);
    robot___ideal.set_heading(departure_W.z());
    robot___ideal.speed_normal = speed;
    robot___ideal.speed_low = speed / 2.0f;


    /** Draw Wall segments **/
    for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
        if (origin_transformed) {
            Vec3f transformed_point_start = HT_World_frame_to_Robot_frame * it->start.homogeneous();
            Vec3f transformed_point_end = HT_World_frame_to_Robot_frame * it->end.homogeneous();
            lidar_msg.lines_p1x.push_back(transformed_point_start.x());
            lidar_msg.lines_p1y.push_back(transformed_point_start.y());
            lidar_msg.lines_p2x.push_back(transformed_point_end.x());
            lidar_msg.lines_p2y.push_back(transformed_point_end.y());
            lidar_msg.lines_col.push_back(0x22555555);
        } else {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(0x22555555);
        }
    }

    /** Drawing Grid **/
    // draw_grids(lidar_msg);

    /** vector of point_cloud vector: Store all laserscan points **/
    vector<vector<Vec2f>> point_clouds;

    /** ROS node loop **/
    while (ros::ok())
    {   
        int num_total_laserscan_points = 0;
        int num_total_HTs = 0;
        int safety_steps_departure = 0;
        bool safely_arrived = false;

        float dx_ns_accumulated = 0.0f;
        float dy_ns_accumulated = 0.0f;

        /** Loop untround visit all waypoints **/
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            /** Get the next waypoint **/
            Vec3f arrival_W = waypoints.front();
            Vec2f arrival_W_2f = Vec2f(arrival_W.x(), arrival_W.y());
            arrival_W = Vec3f(arrival_W.x() + dx_ns_accumulated, arrival_W.y() + dy_ns_accumulated, arrival_W.z());
            waypoints.pop_front();
            bool arrival_circle_drew = false;

            while (true)
            {
                if (origin_transformed) {
                    Vec3f transformed_point = HT_World_frame_to_Robot_frame * robot___actual.position_in_Wframe.homogeneous();

                    /** Draw robot's position and its velocity vector **/
                    // draw_robot_vector(robot___actual, lidar_msg, 0xFF5555FF);
                    lidar_msg.points_x.push_back(transformed_point.x());
                    lidar_msg.points_y.push_back(transformed_point.y());
                    lidar_msg.points_col.push_back(0xFF2200fc);
                    // draw_robot_vector(robot___ideal, lidar_msg, 0xFF2200fc);
                    // lidar_msg.points_x.push_back(robot___ideal.position_in_Wframe.x());
                    // lidar_msg.points_y.push_back(robot___ideal.position_in_Wframe.y());
                    // lidar_msg.points_col.push_back(0xFF5555FF);
                } else {
                    /** Draw robot's position and its velocity vector **/
                    // draw_robot_vector(robot___actual, lidar_msg, 0xFF5555FF);
                    lidar_msg.points_x.push_back(robot___actual.position_in_Wframe.x());
                    lidar_msg.points_y.push_back(robot___actual.position_in_Wframe.y());
                    lidar_msg.points_col.push_back(0xFF2200fc);
                    // draw_robot_vector(robot___ideal, lidar_msg, 0xFF2200fc);
                    // lidar_msg.points_x.push_back(robot___ideal.position_in_Wframe.x());
                    // lidar_msg.points_y.push_back(robot___ideal.position_in_Wframe.y());
                    // lidar_msg.points_col.push_back(0xFF5555FF);
                }

                /** Draw a circle for each way point **/
                if (!arrival_circle_drew) {
                    if (origin_transformed) {
                        Vec3f transformed_point = HT_World_frame_to_Robot_frame * arrival_W_2f.homogeneous();
                        lidar_msg.circles_x.push_back(transformed_point.x());
                        lidar_msg.circles_y.push_back(transformed_point.y());
                        lidar_msg.circles_col.push_back(0xFFFF00FF);
                    } else {
                        lidar_msg.circles_x.push_back(arrival_W.x());
                        lidar_msg.circles_y.push_back(arrival_W.y());
                        lidar_msg.circles_col.push_back(0xFFFF00FF);
                    }
                    arrival_circle_drew = true;
                }


                /** TODO:
                 * - Slow if store all points
                 * */
                vector<Vec2f> point_cloud;
                point_cloud.reserve(laser_sensor.num_total_rays);
                vector<Vec2f> collison_candidates;
                collison_candidates.reserve(laser_sensor.num_total_rays);


                /** Odometry simulation in robot frame **/
                float dx_ns = wheel_encoder___actual_dx_noise.gaussian();   // Get a noise from wheel encoder noise object
                float dy_ns = wheel_encoder___actual_dy_noise.gaussian();
                dx_ns_accumulated += dx_ns; // Accumulated noise
                dy_ns_accumulated += dy_ns;
                wheel_encoder___actual.simulate_odometry( robot___actual.speed, delta_t, dx_ns, dy_ns );
                float dtheta_radian___actual = cut_redundant_epsilon( ( atan2(wheel_encoder___actual.dy, wheel_encoder___actual.dx) ) );
                float cos_dtheta___actual = cut_redundant_epsilon( cos(dtheta_radian___actual) );
                float sin_dtheta___actual = cut_redundant_epsilon( sin(dtheta_radian___actual) );
                wheel_encoder___ideal.simulate_odometry( robot___ideal.speed, delta_t, 0, 0);
                float dtheta_radian___ideal = cut_redundant_epsilon( ( atan2(wheel_encoder___ideal.dy, wheel_encoder___ideal.dx) ) );
                float cos_dtheta___ideal = cut_redundant_epsilon( cos(dtheta_radian___ideal) );
                float sin_dtheta___ideal = cut_redundant_epsilon( sin(dtheta_radian___ideal) );


                /** Laser Scan **/
                // simulate_scan(point_cloud, robot___actual, wall_segments, robot___actual.sensor_laser, laser_length_noise, laser_angle_noise);
                simulate_scan_with_vision(point_cloud, collison_candidates, robot___ideal, wall_segments, robot___ideal.sensor_laser, laser_length_noise, laser_angle_noise, dx_ns_accumulated, dy_ns_accumulated);
                for(vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                    if (origin_transformed) {
                        Vec3f transformed_point = HT_World_frame_to_Robot_frame * it->homogeneous();
                        lidar_msg.points_x.push_back(transformed_point.x());
                        lidar_msg.points_y.push_back(transformed_point.y());
                        lidar_msg.points_col.push_back(0xFFFF5500);
                    } else {
                        lidar_msg.points_x.push_back(it->x());
                        lidar_msg.points_y.push_back(it->y());
                        lidar_msg.points_col.push_back(0xFFFF5500);
                    }
                }
                // bool if_collide = if_collides(collison_candidates, robot___actual, lidar_msg, lidar_msg_pub);
                point_clouds.push_back(point_cloud);
                num_total_laserscan_points += point_cloud.size();


                /** Check collison **/
                // point_cloud, robot, HTs
                // int does_collide = false;
                // float angle = robot___actual.heading_degree_in_Wframe;
                // Noise random_angle = Noise(0, 90);
                // angle = robot___actual.heading_degree_in_Wframe + random_angle.gaussian();


                // if (does_collide) {
                //     cout << "\t\t\tCOLLIDES!!!" << endl;

                //     float cos_adjust_heading = cut_redundant_epsilon( cos( degree_to_radian( angle)) );
                //     float sin_adjust_heading = cut_redundant_epsilon( sin( degree_to_radian( angle)) );
                //     Mat2f pure_rotation;
                //     pure_rotation << cos_adjust_heading, -sin_adjust_heading, sin_adjust_heading, cos_adjust_heading;
                //     Mat3f rotation_HT = rotation_HT.setIdentity();
                //     rotation_HT.block<2, 2>(0, 0) = pure_rotation;
                //     rotation_HT.block<2, 1>(0, 2) = Vec2f(0, 0);
                //     // // cout << HTs___actual.back() << endl;
                //     // // cout << rotation_HT << endl;
                //     cut_redundant_epsilon_Mat3f(rotation_HT);
                //     Mat3f accumulated_frame_HT_rotated_frame = HTs___actual.back() * rotation_HT;
                //     HTs___actual.pop_back();
                //     HTs___actual.push_back(accumulated_frame_HT_rotated_frame);
                //     HTs___ideal.pop_back();
                //     HTs___ideal.push_back(accumulated_frame_HT_rotated_frame);
                //     robot___actual.set_heading(angle);
                //     robot___actual.set_velocity();
                //     draw_robot_vector(robot___actual, lidar_msg, 0xFFFF33CC);
                //     // draw_robot_vector(robot___ideal, lidar_msg, 0xFFCC6600);
                //     lidar_msg_pub.publish(lidar_msg);
                //     // getchar();
                //     // simulate_scan(point_cloud, robot___actual, wall_segments, robot___actual.sensor_laser, laser_length_noise, laser_angle_noise);
                    
                //     // does_collide = false;
                //     continue;
                // }
                // Vec3f Aframe = Vec3f(departure_W.x(), departure_W.y(), departure_W.z());
                // Vec3f Bframe = Vec3f(departure_W.x() + wheel_encoder___actual.dx, 
                //                      departure_W.y() + wheel_encoder___actual.dy, 
                //                      departure_W.z() + wheel_encoder___actual.dtheta_degree);



                /** Robot__actual **/
                /** Robot moves to the new frame (TRANSlate and then ROTate) **/
                Vec3f Aframe___actual = Vec3f(0, 0, 0);                                               // Current frame in Rframe(Robot) is always (0, 0, 0)
                Vec3f Bframe___actual = Vec3f(wheel_encoder___actual.dx,           
                                     wheel_encoder___actual.dy, 
                                     wheel_encoder___actual.dtheta_degree);                    // Next frame is the position of simulated odometry
                Mat3f HT_Aframe_to_Bframe___actual = get_HT_Aframe_to_Bframe(Aframe___actual, Bframe___actual);
                Mat3f HT_accumulated___actual = HTs___actual.back() * HT_Aframe_to_Bframe___actual;      // Transfer to Wframe
                HTs___actual.pop_back();
                HTs___actual.push_back(HT_accumulated___actual);
                num_total_HTs++;
                Vec3f new_position_added_dummy1___actual = HT_accumulated___actual * Vec3f(0, 0, 1);
                Vec2f new_position_in_Wframe___actual = Vec2f(new_position_added_dummy1___actual.x(), new_position_added_dummy1___actual.y());
                robot___actual.move_to(new_position_in_Wframe___actual);

                /** No ROTation here for the theta in Vec3f, (Waypoints's data: (x, y, theta))
                 * because robot just needs to move to the next waypoint rather than parking at the desired angle **/

                /** Get the next arrival point in Robot frame(Rframe) **/
                /** Arrival_R: Arrival_W in Robot frame **/
                Mat3f HT_inverse___actual = get_HT_inverse_Aframe_to_Wframe(HT_accumulated___actual);
                Vec2f arrival_W_only_xy___actual = arrival_W.block<2, 1>(0, 0);  // Excluding theta in Vec3f(x, y, theta)
                Vec3f arrival_R___actual = HT_inverse___actual * arrival_W_only_xy___actual.homogeneous();

                // float distance_to_arrival_R = sqrt( arrival_R___actual.x() * arrival_R___actual.x() + arrival_R___actual.y() * arrival_R___actual.x() );
                // check_safety(robot___actual, distance_to_arrival_R, safely_arrived);

                /** Get HT for the next arrival point **/
                /** Get angle between robot's heading(always 0 in R frame) and next location in Robot frame **/
                float angle_degree_to_next_point_in_Robot_frame___actual = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R___actual.y(), arrival_R___actual.x()) ));
                /** New HT(homogeneous transformation matrix) in robot frame **/
                /** Pure Rotation: adjusted heading rather than rotating towards the next point directly **/
                Mat3f HT_ROT_only___actual = get_HT_ROT_only(angle_degree_to_next_point_in_Robot_frame___actual / 4.0f);
                HT_accumulated___actual = HTs___actual.back() * HT_ROT_only___actual;
                HTs___actual.pop_back();
                HTs___actual.push_back(HT_accumulated___actual);
                num_total_HTs++;



                /** Robot__ideal **/
                /** Robot moves to the new frame (TRANSlate and then ROTate) **/
                Vec3f Aframe___ideal = Vec3f(0, 0, 0);                                               // Current frame in Rframe(Robot) is always (0, 0, 0)
                Vec3f Bframe___ideal = Vec3f(wheel_encoder___ideal.dx,           
                                     wheel_encoder___ideal.dy, 
                                     wheel_encoder___ideal.dtheta_degree);                    // Next frame is the position of simulated odometry
                Mat3f HT_Aframe_to_Bframe___ideal = get_HT_Aframe_to_Bframe(Aframe___ideal, Bframe___ideal);
                Mat3f HT_accumulated___ideal = HTs___ideal.back() * HT_Aframe_to_Bframe___ideal;      // Transfer to Wframe
                HTs___ideal.pop_back();
                HTs___ideal.push_back(HT_accumulated___ideal);
                Vec3f new_position_added_dummy1___ideal = HT_accumulated___ideal * Vec3f(0, 0, 1);
                Vec2f new_position_in_Wframe___ideal = Vec2f(new_position_added_dummy1___ideal.x(), new_position_added_dummy1___ideal.y());
                robot___ideal.move_to(new_position_in_Wframe___ideal);

                /** No ROTation here for the theta in Vec3f, (Waypoints's data: (x, y, theta))
                 * because robot just needs to move to the next waypoint rather than parking at the desired angle **/

                /** Get the next arrival point in Robot frame(Rframe) **/
                /** Arrival_R: Arrival_W in Robot frame **/
                Mat3f HT_inverse___ideal = get_HT_inverse_Aframe_to_Wframe(HT_accumulated___ideal);
                Vec2f arrival_W_only_xy___ideal = arrival_W.block<2, 1>(0, 0);  // Excluding theta in Vec3f(x, y, theta)
                Vec3f arrival_R___ideal = HT_inverse___ideal * arrival_W_only_xy___ideal.homogeneous();

                /** Get HT for the next arrival point **/
                /** Get angle between robot's heading(always 0 in R frame) and next location in Robot frame **/
                float angle_degree_to_next_point_in_Robot_frame___ideal = cut_redundant_epsilon( radian_to_degree( atan2(arrival_R___ideal.y(), arrival_R___ideal.x()) ));
                /** New HT(homogeneous transformation matrix) in robot frame **/
                /** Pure Rotation: adjusted heading rather than rotating towards the next point directly **/
                Mat3f HT_ROT_only___ideal = get_HT_ROT_only(angle_degree_to_next_point_in_Robot_frame___ideal / 4.0f);
                HT_accumulated___ideal = HTs___ideal.back() * HT_ROT_only___ideal;
                HTs___ideal.pop_back();
                HTs___ideal.push_back(HT_accumulated___ideal);



                /** For debugging **/                
                // draw_grid_line_of_robot_frame(robot_actual, HT_accumulated, arrival_R, lidar_msg);
                // draw_robot_vector(robot_actual, lidar_msg, 0xFF5555FF);


                /** Publish lidar msg **/
                lidar_msg_pub.publish(lidar_msg);
                // getchar();
                // draw_grid_line_of_robot_frame(robot_actual, HT_accumulated, arrival_R, lidar_msg, true);

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


                /** If arrived at the waypoint, get the next waypoint **/
                if (if_arrived_at_xy_frameW(robot___actual, arrival_W.x(), arrival_W.y(), robot___actual.speed / 2.0f)) {
                    cout 
                        << "\t Departure was: (" << departure_W.x() << ", " << departure_W.y() << ")" << endl
                        << "\t    Arrived at: (" << arrival_W.x() << ", " << arrival_W.y() << ")"
                        << "\t\tActual position:(" << robot___actual.position_in_Wframe.x() << ", " << robot___actual.position_in_Wframe.y() << ")" << endl
                        << "\t Robot speed: " << robot___actual.speed 
                        << " delta_t: " << delta_t << endl
                        << endl;
                        // safely_arrived = true;
                    break;
                }
                // if (safely_arrived) { safety_steps_departure++; }
                // if (safety_steps_departure > 7) { safely_arrived = false; safety_steps_departure = 0; }


            }

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
            << "\narrived at:(" << robot___actual.position_in_Wframe.x() << ", " << robot___actual.position_in_Wframe.y() << ")"
            << "\tTravel finished!" << endl
            << "total num of scans: " << point_clouds.size() << endl
            << "p[0]: " << point_clouds[0].size()
            << "\tp[1]: " << point_clouds[1].size()
            << "\t..." << endl
            << "total num of points: " << num_total_laserscan_points
            << "\tAvg.num of points per scan: " << num_total_laserscan_points / point_clouds.size() << endl
            << "total num of HTs: " << num_total_HTs << endl
            << "Press to continue..." << endl
            ;
        getchar();


        string img_filename = "test.jpg";
        save_map(point_clouds, HT_World_frame_to_Robot_frame, img_filename);


        /** Plot point cloud on the map in two different colors **/
        // vector<uint32_t> colors;
        // uint32_t color_1 = 0xFFff00ff;
        // uint32_t color_2 = 0xFF3366ff;
        // colors.push_back(color_1);
        // colors.push_back(color_2);
        // int round = 0;
        
        // while (true)
        // {
        //     uint32_t color = colors[round++];
        //     if (round >= 2) { round = 0; }
        //     vector_slam_msgs::LidarDisplayMsg lidar_msg_after_all_scans;
        //     for(vector<vector<Vec2f>>::iterator it = point_clouds.begin(); it != point_clouds.end(); ++it)
        //     {
        //         for(vector<Vec2f>::iterator jt = it->begin(); jt != it->end(); ++jt)
        //         {
        //             lidar_msg_after_all_scans.points_x.push_back(jt->x());
        //             lidar_msg_after_all_scans.points_y.push_back(jt->y());
        //             lidar_msg_after_all_scans.points_col.push_back(color);
        //         }
        //     }
        //     cout
        //         << "Press anykey to plot point coulds..." << endl
        //         ;
        //         lidar_msg_pub.publish(lidar_msg_after_all_scans);
        //     getchar();
        // }
    }

    return 0;
}

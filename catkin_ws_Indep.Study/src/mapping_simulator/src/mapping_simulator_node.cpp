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
    vector_slam_msgs::LidarDisplayMsg lidar_msg;
    read_segments(wall_segments_file, wall_segments);
    read_waypoints(waypoints_file, waypoints, robot_headings, lidar_msg);
    deque<Vec3f> *waypoints_backup = new deque<Vec3f>(waypoints);   // Deep copy


    /** Create objects **/
    
    /** Sets robot's init position **/
    Vec3f robot_init_frame = waypoints.empty() ? Vec3f(0, 0, 0) : waypoints.front();
    Vec2f robot_init_position = robot_init_frame.block<2, 1>(0, 0);
    float robot_init_heading = robot_init_frame.z();
    cout << "robot_init_frame:\n" << robot_init_frame << endl;
    cout << "robot_init_position:\n" << robot_init_position << endl;
    float speed = 0.2;

    Robot robot_actual = Robot(robot_init_position, robot_init_heading, speed);
    Robot robot_ideal = Robot(robot_init_position, robot_init_heading, speed);
    cout << "robot_frame:\n" << robot_ideal.robot_frame_in_Wframe << endl;

    /** Sensors and Noises **/
    Laser laser_sensor = Laser();
    Noise laser_length_noise = Noise(0.0, 0.8);
    Noise laser_angle_noise = Noise(0.0, 0.2);
    Noise wheel_encoder_dx_noise = Noise(0.0, 0.001);
    Noise wheel_encoder_dy_noise = Noise(0.0, 0.001);
    WheelEncoder wheel_encoder = WheelEncoder();
    Vec3f World_frame = Vec3f(0, 0, 0);

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_stamp = 0.0;

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
        /** Draw Wall segments **/
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(0xFF99ff33);
        }

        /** Initial position **/
        Vec3f departure_W = waypoints.front();
        waypoints.pop_front();

            /** Drawing Grid **/
            for (int i = -30; i <= 30; ++i) {
                lidar_msg.lines_p1x.push_back(i);
                lidar_msg.lines_p1y.push_back(-30);
                lidar_msg.lines_p2x.push_back(i);
                lidar_msg.lines_p2y.push_back(30);
                lidar_msg.lines_col.push_back(0x10000000);

                lidar_msg.lines_p1x.push_back(-30);
                lidar_msg.lines_p1y.push_back(i);
                lidar_msg.lines_p2x.push_back(30);
                lidar_msg.lines_p2y.push_back(i);
                lidar_msg.lines_col.push_back(0x10000000);
            }

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

        int i = 0;
        /** Loop until visit all waypoints **/
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            /** Get the next waypoint **/
            Vec3f arrival_W = waypoints.front();
            waypoints.pop_front();

            while (true)
            {
                /** If arrived at the waypoint, get the next waypoint **/
                if (if_arrived_at_a_point_frameW(robot_ideal, arrival_W)) {
                    cout 
                        << "Arrived at point:(" << arrival_W.x() << ", " << arrival_W.y() << ")" << endl
                        << "Departure was: (" << departure_W.x() << ", " << departure_W.y() << ")" << endl
                        ;
                    break;
                }

                /** Draw robot's position and its velocity vector **/
                draw_robot_vector(robot_ideal, lidar_msg);
                lidar_msg.points_x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFF00FFFF);
                lidar_msg_pub.publish(lidar_msg);
                cout << "round: " << ++i << endl;

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


                // cout 
                //     << "Departure:" << endl << departure_W << endl
                //     << "Arrival:" << endl << arrival_W << endl
                //     << "theta_waypoint:" << arrival_W << endl
                //     << "theta_goal:" << robot_ideal.heading_degree_in_Wframe << endl
                //     ;

                /** New HT(homogeneous transformation matrix) in robot frame **/
                Mat2f sROTt;
                sROTt << cos_dtheta, -sin_dtheta, sin_dtheta, cos_dtheta;
                Vec2f sTRANSt = Vec2f(wheel_encoder.dx, wheel_encoder.dy);
                Mat3f current_HT = current_HT.setIdentity();
                current_HT.block<2, 2>(0, 0) = sROTt;
                current_HT.block<2, 1>(0, 2) = sTRANSt;

                /** New HT in world frame
                 *  sHTt = sHT1 * 1HT2 * ... * (k-1)HTk * kHTt
                 *  **/
                Mat3f new_HT = HTs.back() * current_HT;
                HTs.push_back(new_HT);
                // cout 
                //         << "current_HT:" << endl << current_HT << endl
                //         << "new_HT:" << endl << new_HT << endl
                //         << "HTs.back:" << endl << HTs.back() << endl
                //         << endl;
                Vec3f pivot = Vec3f(0, 0, 1);   /** current position in the current frame **/
                Vec3f new_frame = new_HT * pivot;
                Vec2f new_position = Vec2f(new_frame.x(), new_frame.y());

                /** Move the robot **/
                robot_ideal.move_to(new_position);

                Mat3f new_HT_inverse = new_HT_inverse.setIdentity();
                Mat2f new_HT_ROT = new_HT.block<2, 2>(0, 0);
                Vec2f new_HT_TRANS = new_HT.block<2, 1>(0, 2);
                Mat2f new_HT_ROT_neg = -new_HT_ROT;
                Vec2f TRANS_in_inverse = new_HT_ROT_neg.transpose() * new_HT_TRANS;
                new_HT_inverse.block<2, 2>(0, 0) = new_HT_ROT.transpose();
                new_HT_inverse.block<2, 1>(0, 2) = TRANS_in_inverse;
                Vec2f arrival_W2f = arrival_W.block<2, 1>(0, 0);
                Vec3f arrival_R = new_HT_inverse * arrival_W2f.homogeneous();
                // float angle_difference = 
                lidar_msg.points_x.push_back(arrival_R.x());
                lidar_msg.points_y.push_back(arrival_R.y());
                lidar_msg.points_col.push_back(0xFF3388AA);

                cout 
                    << "Departure: (" << departure_W.x() << ", " << departure_W.y() << ")" << endl
                    << "Arrival_W: (" << arrival_W.x() << ", " << arrival_W.y() << ")" << endl
                    << "Arrival_R: (" << arrival_R.x() << ", " << arrival_R.y() << ")" << endl
                    << "  Current: (" << robot_ideal.position_in_Wframe.x() << ", " << robot_ideal.position_in_Wframe.y() << ")" << endl
                    << " Robot's heading: " << robot_ideal.heading_degree_in_Wframe << endl
                    << "Angle difference: " << robot_ideal.heading_degree_in_Wframe << endl
                    ;



                lidar_msg.points_x.push_back(new_frame.x());
                lidar_msg.points_y.push_back(new_frame.y());
                lidar_msg.points_col.push_back(0xFFFF0000);





                /** timestep increasing **/
                time_stamp += delta_t;
                getchar();
            }

            departure_W = arrival_W;





            // deque<Eigen::Matrix3f> homos;
            /** Calculate curve points(trajectories) from current waypoint to the next waypoint **/
            // Noise trajectories_noise = Noise(0.0, 0.01);        // For simulating noises on Odometry
            /** Separate curve points.  Ideal: Where robot think it is.  Actual: Actual position of the robot **/
            // deque<Vec2f> trajectories_ideal = interpolate_curve_points(homos, delta_t, robot_ideal, departure_W, arrive);
            // deque<Vec2f> trajectories_actual = interpolate_curve_points(homos, delta_t, robot_actual, departure_W, arrive, true, &trajectories_noise);


            /** Traverse all curve points between point P0 and P1 **/
            // while (!trajectories_ideal.empty())
            // {
                
                /** Extract the next curve point **/
                // Vec2f p_ideal = trajectories_ideal.front();
                // Vec2f p_actual = trajectories_actual.front();
                // trajectories_ideal.pop_front();
                // trajectories_actual.pop_front();



                // cout << "homo:" << endl << homo_WR << endl;
                // cout << ( radian_to_degree(acos(homo_WR(0, 0)))  ) << endl << endl;

                // Vec3f pose_W = homo_WR * Vec2f(0, 0).homogeneous();
                // cout << "pose_W: (" << pose_W.x() << ", " << pose_W.y() << ")" << endl;

                /** Move robot **/
                // robot_ideal.move_to(p_ideal);
                // draw_robot_vector(robot_ideal, lidar_msg);
                // robot_actual.move_to(p_actual);



                /** Draw Robot's velocity **/
                // lidar_msg.points_x.push_back(p_ideal.x());
                // lidar_msg.points_y.push_back(p_ideal.y());
                // lidar_msg.points_col.push_back(0xFFFF0000);
                // lidar_msg.points_x.push_back(p_actual.x());
                // lidar_msg.points_y.push_back(p_actual.y());
                // lidar_msg.points_col.push_back(0xFF0000FF);

                // lidar_msg.robotLocX = robot_actual.position_in_Wframe.x();
                // lidar_msg.robotLocY = robot_actual.position_in_Wframe.y();
                // lidar_msg.timestamp = time_stamp;
                // lidar_msg.robotAngle = robot_actual.heading_radian;

                /** Simulate scan **/
                // vector<Vec2f> point_cloud;                      // Vector: intersection points cloud
                // simulate_scan(point_cloud, robot_actual, wall_segments, laser_sensor, laser_length_noise, laser_angle_noise);
                // sort(point_cloud.begin(), point_cloud.end(), compare_xy_Vec2f());
                // point_cloud.erase( unique(point_cloud.begin(), point_cloud.end()), point_cloud.end());
                // cout << "point cloud size:" << point_cloud.size() << endl;

                /** Update time delta t after one laser scan **/

                /** Draw laser scan points **/
                // for (vector<Vec2f>::iterator it = point_cloud.begin(); it != point_cloud.end(); ++it) {
                //     lidar_msg.points_x.push_back(it->x());
                //     lidar_msg.points_y.push_back(it->y());
                //     lidar_msg.points_col.push_back(0xFFA500FF); // Orange
                // }

                /** Successfull Tests **/
                // Vec2f F1 = Vec2f(0, 0);
                // Vec2f F2 = Vec2f(4, 0);
                // Vec2f F1_frameF2 = Vec2f(-4, -3);
                // Vec2f F3 = Vec2f(2, 4);
                // Vec2f F3_frameF2 = Vec2f(0, 2);
                // Vec2f P9 = Vec2f(5, 1);
                // Mat3f A12 = get_homogeneous_transform_between_two_frames(F1.x(), F1.y(), 0, F2.x(), F2.y(), 45);
                // Mat3f A21 = get_homogeneous_transform_between_two_frames(F2.x(), F2.y(), 45, F1.x(), F1.y(), 0);
                // Mat3f A23 = get_homogeneous_transform_between_two_frames(F2.x(), F2.y(), 45, F3.x(), F3.y(), 90);
                // Mat3f A13 = get_homogeneous_transform_between_two_frames(F1.x(), F1.y(), 0, F3.x(), F3.y(), 90);
                // Eigen::Matrix3f A31 = get_homogeneous_transform(F3, F1);
                // cout << A12 << endl;
                // cout << A23 << endl;
                // cout << A13 << endl;
                // cout << A31 << endl;
                // Vec3f F1toF2 = A12 * F1.homogeneous();
                // Vec3f P9inF2 = A21 * P9.homogeneous();
                // Vec3f F2toF3 = A23 * A12 * F1.homogeneous();
                // Vec3f F1toF3 = A13 * F1.homogeneous();
                // Vec3f F1toF3p = A12 * A23 * F1.homogeneous();
                // Vec3f F3_in_W_frame = A12 * F3_frameF2.homogeneous();
                // cout << "-----------------------------------" << endl;
                // cout << F1 << endl << P9 << endl;
                // cout << F1toF2 << endl;
                // cout << P9inF2 << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F2 << endl;
                // cout << F2toF3 << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F3 << endl;
                // cout << F1toF3 << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F3 << endl;
                // cout << F1toF3p << endl;
                // cout << "-----------------------------------" << endl;
                // cout << F3 << endl;
                // cout << F3_in_W_frame << endl;
                // cout << "-----------------------------------" << endl;
                // F1toF2 = A12 * F1;
                // Eigen::Vector3f F1toF2 = Eigen::Vector3f(A12 * F1);
                // Eigen::Vector3f F2toF3 = Eigen::Vector3f(A23 * F2);
                // Eigen::Vector3f F1toF3 = Eigen::Vector3f(A23 * A12 * F1);
                // lidar_msg.points_x.push_back(F1.x());
                // lidar_msg.points_y.push_back(F1.y());
                // lidar_msg.points_col.push_back(0xFF00FF00);
                // lidar_msg.points_x.push_back(F2.x());
                // lidar_msg.points_y.push_back(F2.y());
                // lidar_msg.points_col.push_back(0xFF00FF00);
                // lidar_msg.points_x.push_back(F3.x());
                // lidar_msg.points_y.push_back(F3.y());
                // lidar_msg.points_col.push_back(0xFF00FF00);


                /** Odometry Test **/
                // Vec2f O1 = Vec2f(0, 0);
                // Vec2f O2 = Vec2f(2, 0);
                // Vec2f O3 = Vec2f(4, 2);
                // Vec2f O4 = Vec2f(4, 4);
                // float speed_wheel = 0.1;
                // float del_t = 0.1;

                // float x_pos = 0;
                // float y_pos = 0;
                // float dx_ns = wheel_encoder_dx_noise.gaussian();
                // float dy_ns = wheel_encoder_dy_noise.gaussian();
                // for (int i = 0; i <= 100000; ++i) {
                //     float dx_ns = 0;
                //     float dy_ns = 0;
                //     if (i % 3 == 0) {
                        // dx_ns = fabs(wheel_encoder_dx_noise.gaussian());
                        // dy_ns = wheel_encoder_dy_noise.gaussian();
                    // }
                //     wheel_encoder.simulate_odometry( speed_wheel, del_t, 
                //                     dx_ns, dy_ns );
                //                     Vec2f pp = Vec2f(robot_ideal.position_in_Wframe.x()+wheel_encoder.dx, robot_ideal.position_in_Wframe.y()+wheel_encoder.dy);
                //                     robot_ideal.move_to(pp);
                //     lidar_msg.points_x.push_back( robot_ideal.position_in_Wframe.x() );
                //     lidar_msg.points_y.push_back( robot_ideal.position_in_Wframe.y() );
                //     lidar_msg.points_col.push_back(0xFF55A3B0);
                // cout << "dtheta:" << wheel_encoder.dtheta_degree << endl;
                // }


                ros::spinOnce();
                loop_rate.sleep();
            // }
            // departure_W = Vec3f(arrive_W);
            // cout << "angle:" << robot_actual.heading_degree << "\tcurrent:(" << robot_actual.position_in_Wframe.x() 
            //     << "," << robot_actual.position_in_Wframe.y() << ")" << "\tarrive:(" << arrive.x() << "," << arrive.y() << ")" << endl;
            // cout << "robot's velocity:" << robot_actual.velocity << endl;
            // cout << "waypoints.front():" << waypoints.front() << endl;
        }

        cout << "arrived at:(" << robot_ideal.position_in_Wframe.x() << ", " << robot_ideal.position_in_Wframe.y() << ")" << endl;
        cout << "Travel finished!" << endl;
    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
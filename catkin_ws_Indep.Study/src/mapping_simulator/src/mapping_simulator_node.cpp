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
    cout << "robot_init_frame:\n" << robot_init_frame << endl;
    cout << "robot_init_position:\n" << robot_init_position << endl;
    float speed = 1;

    Robot robot_actual = Robot(robot_init_position, robot_init_frame.z(), speed);
    Robot robot_ideal = Robot(robot_init_position, robot_init_frame.z(), speed);
    cout << "robot_frame:\n" << robot_ideal.robot_frame_in_Wframe << endl;

    /** Sensors and Noises **/
    Laser laser_sensor = Laser();
    Noise laser_length_noise = Noise(0.0, 0.8);
    Noise laser_angle_noise = Noise(0.0, 0.2);
    Noise wheel_encoder_dx_noise = Noise(0.0, 0.0);
    Noise wheel_encoder_dy_noise = Noise(0.05, 0.0);
    // Noise wheel_encoder_dx_noise = Noise(0.0, speed / 100);
    // Noise wheel_encoder_dy_noise = Noise(0.0, speed / 50);
    WheelEncoder wheel_encoder = WheelEncoder();
    Vec3f World_frame = Vec3f(0, 0, 0);

    /** Variables for the simulator **/
    float delta_t = get_delta_t(laser_sensor);
    float time_stamp = 0.0;

    deque<Mat3f> transforms;
    Mat3f init_transform = get_homogeneous_transform_frame_A_to_B(
        World_frame.x(), World_frame.y(), World_frame.z(),
        waypoints.front().x(), waypoints.front().y(), waypoints.front().z());
    cout << "init_transform:\n" << init_transform << endl;
    transforms.push_back(init_transform);
    getchar();

    /** LaserScan msg **/
    sensor_msgs::LaserScan laserscan;
    laserscan.range_max = laser_sensor.range_max;
    laserscan.range_min = laser_sensor.range_min;
    laserscan.angle_max = laser_sensor.FOV_radian;
    laserscan.angle_min = 0.0;


    /** ROS node loop **/
    while (ros::ok())
    {   
        /** Draw Wall segments **/
        for (vector<Segment>::iterator it = wall_segments.begin(); it != wall_segments.end(); ++it) {
            lidar_msg.lines_p1x.push_back(it->start.x());
            lidar_msg.lines_p1y.push_back(it->start.y());
            lidar_msg.lines_p2x.push_back(it->end.x());
            lidar_msg.lines_p2y.push_back(it->end.y());
            lidar_msg.lines_col.push_back(cobot_gui::kColorBlack);
        }

        /** Initial position **/
        Vec3f depart_W = waypoints.front();
        waypoints.pop_front();

            /** Drawing Grid **/
            lidar_msg.lines_p1x.push_back(0);
            lidar_msg.lines_p1y.push_back(0);
            lidar_msg.lines_p2x.push_back(200);
            lidar_msg.lines_p2y.push_back(0);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(1);
            lidar_msg.lines_p1y.push_back(10);
            lidar_msg.lines_p2x.push_back(1);
            lidar_msg.lines_p2y.push_back(-10);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(2);
            lidar_msg.lines_p1y.push_back(10);
            lidar_msg.lines_p2x.push_back(2);
            lidar_msg.lines_p2y.push_back(-10);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(3);
            lidar_msg.lines_p1y.push_back(10);
            lidar_msg.lines_p2x.push_back(3);
            lidar_msg.lines_p2y.push_back(-10);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(4);
            lidar_msg.lines_p1y.push_back(10);
            lidar_msg.lines_p2x.push_back(4);
            lidar_msg.lines_p2y.push_back(-10);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(5);
            lidar_msg.lines_p1y.push_back(10);
            lidar_msg.lines_p2x.push_back(5);
            lidar_msg.lines_p2y.push_back(-10);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(-10);
            lidar_msg.lines_p1y.push_back(0);
            lidar_msg.lines_p2x.push_back(10);
            lidar_msg.lines_p2y.push_back(0);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(-10);
            lidar_msg.lines_p1y.push_back(1);
            lidar_msg.lines_p2x.push_back(10);
            lidar_msg.lines_p2y.push_back(1);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(-10);
            lidar_msg.lines_p1y.push_back(2);
            lidar_msg.lines_p2x.push_back(10);
            lidar_msg.lines_p2y.push_back(2);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(-10);
            lidar_msg.lines_p1y.push_back(3);
            lidar_msg.lines_p2x.push_back(10);
            lidar_msg.lines_p2y.push_back(3);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(-10);
            lidar_msg.lines_p1y.push_back(4);
            lidar_msg.lines_p2x.push_back(10);
            lidar_msg.lines_p2y.push_back(4);
            lidar_msg.lines_col.push_back(0xFF00DD00);

            lidar_msg.lines_p1x.push_back(-10);
            lidar_msg.lines_p1y.push_back(5);
            lidar_msg.lines_p2x.push_back(10);
            lidar_msg.lines_p2y.push_back(5);
            lidar_msg.lines_col.push_back(0xFF00DD00);


            Mat3f Init_frame;
            Mat2f Init_rot;
            Vec2f Init_trans = Vec2f(0, 0);
            Init_rot << 1, 0, 0, 1;
            Init_frame.setIdentity();
            Init_frame.block<2, 2>(0, 0) = Init_rot;
            Init_frame.block<2, 1>(0, 2) = Init_trans;


        vector<Mat3f> TFs;
        // TFs.push_back(Init_frame);
        vector<Vec2f> odometries;
        // odometries.push_back(Vec2f(0, 0));
        vector<Vec3f>frames;
        // frames.push_back(Vec3f(0, 0, 0));

        int i = 0;
        // int i = waypoints.size();
        /** Loop until visit all waypoints **/
        // while (true)  // While there's a waypoint to visit
        Mat3f new_point_ht;
        float headings_degree = 0.0;
        while (!waypoints.empty())  // While there's a waypoint to visit
        {
            cout << "---------  i: " << i << "  --------------------------------------------------------------\n";
            if (i >= 10) exit(0);

            new_point_ht.setIdentity();

            /** Extract the next waypoint **/
            Vec3f arrive_W = waypoints.front();
            waypoints.pop_front();
            cout 
                << "depart:(" << depart_W.x() << "," << depart_W.y() << "," << depart_W.z() << ")\t" 
                << "arrive:(" << arrive_W.x() << "," << arrive_W.y() << "," << arrive_W.z() << ")\t"  
                << "angle:" << arrive_W.z() - depart_W.z()
                << endl;

            lidar_msg.lines_p1x.push_back(depart_W.x());
            lidar_msg.lines_p1y.push_back(depart_W.y());
            lidar_msg.lines_p2x.push_back(arrive_W.x());
            lidar_msg.lines_p2y.push_back(arrive_W.y());
            lidar_msg.lines_col.push_back(0xFF6666EE);

            // while (!if_arrived_at_a_point_frameW(robot_ideal, arrive_W)) {
                // Vec3f W_frame = Vec3f(0, 0, 0);
                // Vec3f A_frame = Vec3f(0, 0, 30);
                // Vec3f B_frame = Vec3f(2, 1, 45);
                // Vec3f C_frame = Vec3f(3, 3, 90);

                Vec3f W_frame = depart_W;
                Vec3f A_frame = arrive_W;

                /** Get the next location N_R in robot frame **/
                float dx_ns = wheel_encoder_dx_noise.gaussian();
                float dy_ns = wheel_encoder_dy_noise.gaussian();
                wheel_encoder.simulate_odometry( robot_ideal.speed, delta_t, dx_ns, dy_ns );
                wheel_encoder.dx = 1;
                wheel_encoder.dy = 1;

                float WthetaA_radian = cut_redundant_epsilon( ( atan2(wheel_encoder.dy, wheel_encoder.dx) ) );
                // float WthetaA_degree = radian_to_degree( WthetaA_radian );
                // float WthetaA_radian = cut_redundant_epsilon( degree_to_radian( A_frame.z() - W_frame.z() ));
                float WthetaA_degree = radian_to_degree( WthetaA_radian );
                // float WthetaA_radian = cut_redundant_epsilon( degree_to_radian( A_frame.z() - W_frame.z() ) );
                cout << "\nANGLE: " << WthetaA_radian << "\t" << WthetaA_degree << endl;
                // cout << "\nANGLE: " << ( A_frame.z() - W_frame.z() ) << endl;
                float cos_WthetaA = cut_redundant_epsilon( cos(WthetaA_radian) );
                float sin_WthetaA = cut_redundant_epsilon( sin(WthetaA_radian) );
                Mat2f WrotA;
                WrotA << cos_WthetaA, -sin_WthetaA, sin_WthetaA, cos_WthetaA;

                headings_degree += WthetaA_degree;
                cout
                    << "headings_degree:" << headings_degree << endl;

                int j = TFs.size();
                // for (vector<Mat3f>::iterator it = TFs.begin(); it != TFs.end(); ++it) {
                for (int k = 0; k < j; ++k) {
                    // new_point_ht = (*it) * new_point_ht;
                    new_point_ht = TFs.at(k) * new_point_ht;
                }


                // Vec2f WtransA = Vec2f(wheel_encoder.dx, wheel_encoder.dy);
                Vec2f WtransA_in_world_frame = Vec2f(A_frame.x() - W_frame.x(), A_frame.y() - W_frame.y());
                Vec3f WtransA3f = new_point_ht * Vec2f(wheel_encoder.dx, wheel_encoder.dy).homogeneous();
                // Vec3f WtransA3f = new_point_ht * Vec2f(A_frame.x() - W_frame.x(), A_frame.y() - W_frame.y()).homogeneous();
                Vec2f WtransA = Vec2f(A_frame.x() - W_frame.x(), A_frame.y() - W_frame.y());
                // Vec2f WtransA = Vec2f(A_frame.x() - W_frame.x(), A_frame.y() - W_frame.y());
                Vec3f point_frame = Vec3f(0, 0, 1);

                Mat3f WtfA;
                WtfA.setIdentity();
                WtfA.block<2, 2>(0, 0) = WrotA;
                WtfA.block<3, 1>(0, 2) = WtransA.homogeneous();

                Mat3f last_transform;
                last_transform = last_transform.setZero();
                cout << "size:" << TFs.size() << endl;
                if (TFs.empty()) { last_transform = Init_frame; }
                else { last_transform = TFs.at(TFs.size()-1); }
                // Mat3f last_transform = TFs.at(TFs.size()-1);
                Vec3f new_frame = last_transform * point_frame;
                new_frame.z() = headings_degree;

                TFs.push_back(WtfA);
                odometries.push_back(WtransA);
                frames.push_back(new_frame);

                Mat3f cur_TF = TFs.at(i);
                Vec2f cur_odo = odometries.at(i);
                Vec3f cur_frame = frames.at(i);
                i++;

                // Vec2f new_point = Vec2f(new_frame.x(), new_frame.y());

                Vec3f new_point_3 = new_point_ht * WtransA.homogeneous();
                // Vec3f new_point_3 = new_point_ht * odometries.at(j-1).homogeneous();
                Vec2f new_point = Vec2f(new_point_3.x(), new_point_3.y());
                Vec2f new_frame_point = Vec2f(new_frame.x(), new_frame.y());
                float new_heading = radian_to_degree( acos(cos_WthetaA) );
                robot_ideal.move_to(new_frame_point);
                robot_ideal.set_heading(new_frame.z());
                // robot_ideal.set_heading(WthetaA_degree);
                // robot_ideal.set_heading(A_frame.z());
                // draw_robot_vector(robot_ideal, lidar_msg);
                // robot_ideal.set_heading(frames.at(frames.size()-1).z());

                cout
                        << "W_frame:" << endl << "(" << W_frame.x() << "," << W_frame.y() << "," << W_frame.z() << ")" << endl
                        << "A_frame:" << endl << "(" << A_frame.x() << "," << A_frame.y() << "," << A_frame.z() << ")" << endl
                        << "WthetaA_degree:" << endl << "(" << radian_to_degree( WthetaA_radian ) << endl
                        // << "cos_WthetaA:" << endl << cos_WthetaA << endl
                        // << "sin_WthetaA:" << endl << sin_WthetaA << endl
                        << "WrotA:" << endl << WrotA << endl
                        << "WtransA:" << endl << WtransA << endl
                        << "WtfA:" << endl << WtfA << endl
                        << "last_transform:" << endl << last_transform << endl
                        << "new_frame:" << endl << new_frame
                        << "cur_TF:" << endl << cur_TF << endl
                        << "cur_odo: (" << cur_odo.x() << "," << cur_odo.y() << ")" << endl
                        << "cur_frame: (" << cur_frame.x() << "," << cur_frame.y() << "," << cur_frame.z() << ")" << endl
                        << "ROBOT x,y,theta: " << robot_ideal.position_in_Wframe.x() << "," 
                                               << robot_ideal.position_in_Wframe.y() << ","
                                               << robot_ideal.heading_degree_in_Wframe << endl
                        << "ROBOT position_Vector:" << endl << robot_ideal.velocity_in_Wframe
                        << endl;


                lidar_msg.points_x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFFFF0000);
                

                // Vec2f dx_dy_1 = Vec2f(1,0);
                // lidar_msg.points_x.push_back(dx_dy_1.x());
                // lidar_msg.points_y.push_back(dx_dy_1.y());
                // lidar_msg.points_col.push_back(0xFF0000FF);
                // Vec2f WtA = Vec2f(A_frame.x(), A_frame.y());
                // Vec2f WtA = Vec2f(A_frame.x() - W_frame.x(), A_frame.y() - W_frame.y());
                


                // Mat3f CCTF = WtfA * LastTF;
                // LastTF = CCTF;

                // Mat3f NewTF = WtfA * TFs.front();
                // TFs.push_front(NewTF);

                // Vec3f dx_dy_1_A = NewTF * dx_dy_1.homogeneous();
                // lidar_msg.points_x.push_back(dx_dy_1_A.x());
                // lidar_msg.points_y.push_back(dx_dy_1_A.y());
                // lidar_msg.points_col.push_back(0xFFDD3377);

                        // << "dx_dy_1:" << endl << dx_dy_1 << endl
                        // << "dx_dy_1_A:" << endl << dx_dy_1_A << endl
                        // << "WtA:" << endl << WtA << endl
                        // << "WtfA:" << endl << WtfA << endl;



                // Mat3f AtfW;
                // AtfW.setIdentity();
                // AtfW.block<2, 2>(0, 0) = 
                // AtfW.block<2, 1>(0, 2) = 
        

                // Vec2f next_odometry_W = Vec2f(wheel_encoder.dx, wheel_encoder.dy);


                // Mat3f wTa = get_homogeneous_transform_frame_A_to_B(
                //     W_frame.x(), W_frame.y(), W_frame.z(), A_frame.x(), A_frame.y(), A_frame.z() );
                // Mat3f aTb = get_homogeneous_transform_frame_A_to_B(
                //     A_frame.x(), A_frame.y(), A_frame.z(), B_frame.x(), B_frame.y(), B_frame.z() );
                // Mat3f bTc = get_homogeneous_transform_frame_A_to_B(
                //     B_frame.x(), B_frame.y(), B_frame.z(), C_frame.x(), C_frame.y(), C_frame.z() );
                // Mat3f wTc = wTa * aTb * bTc;
                // cut_redundant_epsilon_Mat3f(wTc);


                // Mat3f wwTaa = get_homogeneous_transform_dx_dy(wheel_encoder.dx, wheel_encoder.dy,
                //     W_frame.x(), W_frame.y(), W_frame.z(), A_frame.x(), A_frame.y(), A_frame.z() );

                // cout
                //         << "wTa:" << endl << wTa << endl
                //         << "wwTaa:" << endl << wwTaa << endl
                //         << "aTb:" << endl << aTb << endl
                //         << "bTc:" << endl << bTc << endl
                //         << "wTc:" << endl << wTc << endl;

                // Vec3f dxdy_homo = Vec3f(next_odometry_W.x(), next_odometry_W.y(), 1);
                // Vec3f dxdy_bTc = bTc * dxdy_homo;
                // cout 
                //         << "dxdy_homo:" << endl << dxdy_homo << endl
                //         << "dxdy_bTc:" << endl << dxdy_bTc << endl;

                // cout << "depart_W:\n" << depart_W << endl;
                // cout << "arrive_W:\n" << arrive_W << endl;

                /**
                 * To move a robot from frame b to c:
                 * 1) take a previous homo transform
                 *       wTa * aTb = wTb
                 * 2) simulate odometry
                 *       (dx, dy)b
                 * *) new point arrive_W:
                 *       bTc * (0, 0, heading_b)
                 * 
                 * new point arrive_W: bTc * (dx, dy)b
                 * (dx, dy)b = wTb * (dx, dy)w
                 *       
                 * 3) get new homo transform
                 *       bTc = [ bRc | btc ]
                 *             bRc = c_heading_W - b_heading_W
                 *             btc = 
                 * 
                 *    bTc * P0b
                 *    
                 * New location to frame c:
                 * wTc * init_loc_w
                 * 
                 * 
                 * bTc = bRc + btc
                 * bRc = c_heading_w - b_heading_w
                 * btc = P1b
                 * P1b = (dx, dy)b
                 *     = (dx, dy)w
                 * 
                 * bTc = [c_heading_w - b_heading_w | (dx, dy)w ]
                 * 
                 * wTc = wTa * aTb * bTc
                 * 
                 * 
                 *     = P0b + bTw * (dx, dy)w
                 *     = bTw * (dx, dy)w
                 * btc = wTb * (dx, dy)w.homo - P0b(0, 0, 0)
                 * wTb = wTa * aTb
                 * 
                 * bTw = bTa * aTw
                 * 
                 * Thus,
                 * bTc * P1b = [c_heading_w - b_heading_w | bTw * (dx, dy)w ]
                 * 
                 * */



                /** Get the next heading **/



                /** Transform N_R into worlf frame N_W **/



                // Mat3f previous_homo_WR = transforms.front();
                // Vec3f previous_frame = get_frame_from_homogeneous_transform(previous_homo_WR);
                // cout << "\nprevious_homo_WR:\n" << previous_homo_WR << endl;
                // cout << "\nprevious_frame:\n" << previous_frame << endl;
                // Mat3f homo_WR = get_homogeneous_transform_frame_A_to_B(
                //                 previous_frame.x(), previous_frame.y(), previous_frame.z(), 
                //                 robot_ideal.robot_frame_in_Wframe.x(), robot_ideal.robot_frame_in_Wframe.y(), arrive_W.z() - World_frame.z());
                // cout << "\nhomo_WR:\n" << homo_WR << endl;
                // transforms.push_back(homo_WR);
                // getchar();
                // Vec3f next_odometry_W_include_extra_1 = homo_WR * next_odometry_R.homogeneous();
                // Vec2f next_odometry_W = Vec2f(next_odometry_W_include_extra_1.x(), next_odometry_W_include_extra_1.y());

                // /** Move to N_W **/
                // robot_ideal.move_to(next_odometry_W);
                // bool arrived_at_a_point_frameW = if_arrived_at_a_point_frameW(robot_ideal, arrive_W);
                // cout << "\nnext_odometry_R:\n" << next_odometry_R 
                //     // << "\nhomo_WR:\n"<<homo_WR 
                //     // << "\nnext_odometry_W_include_extra_1:\n" << next_odometry_W_include_extra_1
                //     << "\nnext_odometry_W:\n" << next_odometry_W
                //     << "\nrobot pos:\n" << robot_ideal.position_in_Wframe << endl;

                // /** Calculate arrive point(frame) in robot frame **/
                // Mat3f homo_RW = get_homogeneous_transform_frame_A_to_B(
                //     robot_ideal.position_in_Wframe.x(), robot_ideal.position_in_Wframe.y(), robot_ideal.heading_degree_in_Wframe,
                //     World_frame.x(), World_frame.y(), 0 - World_frame.z() );
                // cout 
                //     << "robot_ideal.position_W:" << robot_ideal.position_in_Wframe.x()
                //     << ", " << robot_ideal.position_in_Wframe.y()
                //     << ", " << robot_ideal.heading_degree_in_Wframe
                //     << endl << "World_frame:" << World_frame.x()
                //     << ", " << World_frame.y()
                //     << ", " << World_frame.z();

                // Vec2f arrive_W_only_positions = Vec2f(arrive_W.x(), arrive_W.y());
                // Vec3f arrive_R = homo_RW * arrive_W_only_positions.homogeneous();
                // float heading_diff_R = arrive_R.z() - 0.0f;         // Robot's heading is always zero in robot frame
                // cout 
                //     << "\narrive_W:\n" << arrive_W 
                //     // << "\nhomo_RW:\n" << homo_RW 
                //     << "\narrive_R:\n" << arrive_R 
                //     << "\nheading_diff_R:\n" << heading_diff_R << endl;


                // /** Adjust heading **/
                // float new_heading_R = ( atan2(arrive_R.y(), arrive_R.x() )) / 2.0f;
                // robot_ideal.set_heading(new_heading_R);
                // cout 
                //     << "\narrive_W heading:\n" << arrive_W.z()
                //     << "\narrive_R.z:" << arrive_R.z()
                //     << "\trobot_heading:\n" << robot_ideal.heading_degree_in_Wframe << endl;

                /** Draw robot **/
                draw_robot_vector(robot_ideal, lidar_msg);
                lidar_msg.points_x.push_back(robot_ideal.position_in_Wframe.x());
                lidar_msg.points_y.push_back(robot_ideal.position_in_Wframe.y());
                lidar_msg.points_col.push_back(0xFFFF0000);
                time_stamp += delta_t;
                lidar_msg_pub.publish(lidar_msg);
                cout << "-----------------------------------------------------------------------";

            // }
            cout << "Arrived at point:(" << arrive_W.x() << ", " << arrive_W.y() << ")" << endl;
                getchar();
                // cout << "prev_W: (" << previous_frame_W.x() << ", " << previous_frame_W.y() << ")" << endl;

                // cout << "next_R: (" << next_R.x() << ", " << next_R.y() << ")" << endl;

                // cout << "next_W: (" << next_W.x() << ", " << next_W.y() << ")" << endl << endl;

                // cout << "W.x:" << World_frame.x() << "\tW.y:" << World_frame.y() << "\tW.th:" << World_frame.z() << endl;
                // cout << "R.x:" << robot_ideal.robot_frame_in_Wframe.x() << "\tR.y:" << robot_ideal.robot_frame_in_Wframe.y() << "\tR.th:" << robot_ideal.robot_frame_in_Wframe.z() << endl;



            // deque<Eigen::Matrix3f> homos;
            /** Calculate curve points(trajectories) from current waypoint to the next waypoint **/
            // Noise trajectories_noise = Noise(0.0, 0.01);        // For simulating noises on Odometry
            /** Separate curve points.  Ideal: Where robot think it is.  Actual: Actual position of the robot **/
            // deque<Vec2f> trajectories_ideal = interpolate_curve_points(homos, delta_t, robot_ideal, depart_W, arrive);
            // deque<Vec2f> trajectories_actual = interpolate_curve_points(homos, delta_t, robot_actual, depart_W, arrive, true, &trajectories_noise);


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

                /** Publishing msgs **/

                // getchar();
                // return 0;
                // cout << "time_stamp: " << time_stamp << endl;
                // cout << "delta_t: " << delta_t << endl;
                ros::spinOnce();
                loop_rate.sleep();
                // getchar();
            // }
            depart_W = Vec3f(arrive_W);
            // cout << "angle:" << robot_actual.heading_degree << "\tcurrent:(" << robot_actual.position_in_Wframe.x() 
            //     << "," << robot_actual.position_in_Wframe.y() << ")" << "\tarrive:(" << arrive.x() << "," << arrive.y() << ")" << endl;
            // cout << "robot's velocity:" << robot_actual.velocity << endl;
            // cout << "waypoints.front():" << waypoints.front() << endl;


            // getchar();
        }

        // robot.move_to(robot_init_position);
        // for(deque<Vec2f>::iterator it = waypoints_backup->begin(); it != waypoints_backup->end(); ++it) {
        //     waypoints.push_back(*it);
        // }
        cout << "arrived at:(" << robot_ideal.position_in_Wframe.x() << ", " << robot_ideal.position_in_Wframe.y() << ")" << endl;
        cout << "Travel finished!" << endl;
        // getchar();

        // heading = (robot_headings.empty() ? 0.0 : robot_headings.front());
        // speed = 0.5;
        // robot_ideal.move_to(robot_init_position);
        // robot_ideal.set_heading(heading);
        // robot_ideal.set_speed(speed);
        // robot_actual.move_to(robot_init_position);
        // robot_actual.set_heading(heading);
        // robot_actual.set_speed(speed);
        // robot_actual = Robot(robot_init_position, heading, speed);
        // robot_ideal = Robot(robot_init_position, heading, speed);

    }

    wall_segments_file.close();
    waypoints_file.close();
    return 0;
}
#include "transformation.h"
#include "segment.h"
#include "simulator.h"
#include <Eigen/Dense>


Mat2f get_rotation_matrix2f(float theta_degree)
{
    Mat2f rot;
    float theta_radian = cut_redundant_epsilon( degree_to_radian(theta_degree) );
    float cos_theta = cut_redundant_epsilon(cos(theta_radian));
    float sin_theta = cut_redundant_epsilon(sin(theta_radian));
    rot << cos_theta, -sin_theta, sin_theta, cos_theta;
    return rot;
}


Vec2f get_translation_vec2f(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree)
{
    cout 
        << "from (" << A_x << "," << A_y << "," << A_theta_degree 
        << ") to (" << B_x << "," << B_y << "," << B_theta_degree << ")" << endl;
    float x_diff_W = cut_redundant_epsilon( B_x - A_x );
    float y_diff_W = cut_redundant_epsilon( B_y - A_y );
    float length = cut_redundant_epsilon( sqrt( pow(x_diff_W, 2.0) + pow(y_diff_W, 2.0) ) );
    float total_theta_degree = cut_redundant_epsilon( B_theta_degree - A_theta_degree );
    float total_theta_radian = cut_redundant_epsilon( degree_to_radian(total_theta_degree) );
    float cos_theta = cut_redundant_epsilon(cos(total_theta_radian));
    float sin_theta = cut_redundant_epsilon(sin(total_theta_radian));
    float x_diff_A = cut_redundant_epsilon( length * cos_theta );
    float y_diff_A = cut_redundant_epsilon( length * sin_theta );
    cout
        << "length: " << length << "\ttotal_theta: " << total_theta_degree << "\tcos_th: " << cos_theta << "\tsin_th: " << sin_theta << endl;
    Vec2f A_t_B = Vec2f(x_diff_A, y_diff_A);
    cout << "trans:" << endl << A_t_B << endl;
    return A_t_B;
}


Mat3f get_homogeneous_transform_dx_dy(float dx, float dy, float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree)
{
    cout 
        << "from (" << A_x << "," << A_y << "," << A_theta_degree 
        << ") to (" << B_x << "," << B_y << "," << B_theta_degree << ")" << endl;
    float x_diff_W = cut_redundant_epsilon( B_x - A_x );
    float y_diff_W = cut_redundant_epsilon( B_y - A_y );
    float length = cut_redundant_epsilon( sqrt( pow(x_diff_W, 2.0) + pow(y_diff_W, 2.0) ) );
    float theta_of_dx_dy = cut_redundant_epsilon( atan2( dy, dx ) );
    float total_theta_degree = cut_redundant_epsilon( A_theta_degree - 90 + theta_of_dx_dy );
    float total_theta_radian = cut_redundant_epsilon( degree_to_radian(total_theta_degree) );
    float cos_theta = cut_redundant_epsilon(cos(total_theta_radian));
    float sin_theta = cut_redundant_epsilon(sin(total_theta_radian));
    float x_diff_A = cut_redundant_epsilon( length * cos_theta );
    float y_diff_A = cut_redundant_epsilon( length * sin_theta );
    cout
        << "length: " << length << "\ttotal_theta: " << total_theta_degree << "\tcos_th: " << cos_theta << "\tsin_th: " << sin_theta << endl;
    Vec2f A_t_B = Vec2f(x_diff_A, y_diff_A);
    cout << "trans:" << endl << A_t_B << endl;

    Mat2f rot = get_rotation_matrix2f(total_theta_radian);
    Vec2f trans = A_t_B;
    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    homo.block<2, 1>(0, 2) = trans;
    return homo;
}


// Mat3f get_homogeneous_transform(Mat2f &rotation, Vec2f translation)
Mat3f get_homogeneous_transform(Vec2f &P0, Vec2f &P1)
{
    // cout << "P0:" << endl << P0 << endl;
    // cout << "P1:" << endl << P1 << endl;
    float theta_radian = get_angle_radian_between_two_vectors(P0, P1);
    theta_radian = cut_redundant_epsilon( theta_radian );
    // cout << "angle between two vectors:" << radian_to_degree(theta_radian) << endl;
    Mat2f rot = get_rotation_matrix2f(theta_radian);
    // cout << "rotation matrix:" << endl << rot << endl;
    // Vec2f trans = get_translation_vec2f(P0, P1);
    // cout << "trans:" << endl << trans << endl;

    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    // homo.block<2, 1>(0, 2) = trans;
    return homo;
}


Mat3f get_homogeneous_transform_frame_A_to_B(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree)
{
    Vec2f A = Vec2f(A_x, A_y);
    Vec2f B = Vec2f(B_x, B_y);
    Vec2f trans = get_translation_vec2f(A_x, A_y, A_theta_degree, B_x, B_y, B_theta_degree);
    // cout << "trans:" << endl << trans << endl;
    float angle_degree = B_theta_degree - A_theta_degree;
    angle_degree = cut_redundant_epsilon( angle_degree );
    Mat2f rot = get_rotation_matrix2f(angle_degree);
    // cout << "trans:\n" << trans << "\trot:\n" << rot << endl;
    cout << "angleA,B,diff:" << A_theta_degree << ", " << B_theta_degree << ", " << angle_degree << endl;
    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    homo.block<2, 1>(0, 2) = trans;
    // cout << "homo:\n" << homo << endl;
    // getchar();
    return homo;
}


Vec3f get_frame_from_homogeneous_transform(Mat3f &homo_transform)
{
    float x = homo_transform(0, 2);
    float y = homo_transform(1, 2);
    float theta_radian = acos(homo_transform(0, 0));
    float theta_degree = radian_to_degree(theta_radian);
    Vec3f frame = Vec3f(x, y, theta_degree);
    return frame;
}


void cut_redundant_epsilon_Mat3f(Mat3f &m)
{
    m(0 ,0) = cut_redundant_epsilon(m(0, 0));
    m(0 ,1) = cut_redundant_epsilon(m(0, 1));
    m(0 ,2) = cut_redundant_epsilon(m(0, 2));
    m(1 ,0) = cut_redundant_epsilon(m(1, 0));
    m(1 ,1) = cut_redundant_epsilon(m(1, 1));
    m(1 ,2) = cut_redundant_epsilon(m(1, 2));
}


float get_angle_degree_between_two_vectors(Vec2f &P0, Vec2f &P1)
{
    float x_diff = cut_redundant_epsilon( P1.x() - P0.x() );
    float y_diff = cut_redundant_epsilon( P1.y() - P0.y() );
    float angle_degree = cut_redundant_epsilon( radian_to_degree(atan2(y_diff, x_diff)) );
    // cout << "robot_ideal.position_W"<<P0<<"\tP1:"<<P1<<endl;
    return angle_degree;
}


float get_angle_radian_between_two_vectors(Vec2f &P0, Vec2f &P1)
{
    float x_diff = cut_redundant_epsilon( P1.x() - P0.x() );
    float y_diff = cut_redundant_epsilon( P1.y() - P0.y() );
    float angle_radian = cut_redundant_epsilon( atan2(y_diff, x_diff) );
    return angle_radian;
}
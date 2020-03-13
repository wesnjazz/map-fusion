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


Vec2f get_translation_vec2f(Vec2f &vec_a, Vec2f &vec_b)
{
    return vec_b - vec_a;
}


// Mat3f get_homogeneous_transform(Mat2f &rotation, Vec2f translation)
Mat3f get_homogeneous_transform(Vec2f &P0, Vec2f &P1)
{
    cout << "P0:" << endl << P0 << endl;
    cout << "P1:" << endl << P1 << endl;
    float theta_radian = get_angle_radian_between_two_vectors(P0, P1);
    theta_radian = cut_redundant_epsilon( theta_radian );
    cout << "angle between two vectors:" << radian_to_degree(theta_radian) << endl;
    Mat2f rot = get_rotation_matrix2f(theta_radian);
    cout << "rotation matrix:" << endl << rot << endl;
    Vec2f trans = get_translation_vec2f(P0, P1);
    cout << "trans:" << endl << trans << endl;

    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    homo.block<2, 1>(0, 2) = trans;
    return homo;
}


Mat3f get_homogeneous_transform_between_two_frames(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree)
{
    Vec2f A = Vec2f(A_x, A_y);
    Vec2f B = Vec2f(B_x, B_y);
    Vec2f trans = get_translation_vec2f(A, B);
    float angle_degree = B_theta_degree - A_theta_degree;
    angle_degree = cut_redundant_epsilon( angle_degree );
    Mat2f rot = get_rotation_matrix2f(angle_degree);
    cout << "trans:\n" << trans << "\trot:\n" << rot << endl;
    cout << "angleA,B,diff:" << A_theta_degree << ", " << B_theta_degree << ", " << angle_degree << endl;
    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    homo.block<2, 1>(0, 2) = trans;
    cout << "homo:\n" << homo << endl;
    getchar();
    return homo;
}


float get_angle_degree_between_two_vectors(Vec2f &P0, Vec2f &P1)
{
    float x_diff = cut_redundant_epsilon( P1.x() - P0.x() );
    float y_diff = cut_redundant_epsilon( P1.y() - P0.y() );
    float angle_degree = cut_redundant_epsilon( radian_to_degree(atan2(y_diff, x_diff)) );
    cout << "P0:"<<P0<<"\tP1:"<<P1<<endl;
    return angle_degree;
}


float get_angle_radian_between_two_vectors(Vec2f &P0, Vec2f &P1)
{
    float x_diff = cut_redundant_epsilon( P1.x() - P0.x() );
    float y_diff = cut_redundant_epsilon( P1.y() - P0.y() );
    float angle_radian = cut_redundant_epsilon( atan2(y_diff, x_diff) );
    return angle_radian;
}
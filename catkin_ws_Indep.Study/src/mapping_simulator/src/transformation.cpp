#include "transformation.h"
#include "segment.h"
#include "simulator.h"
#include <Eigen/Dense>


Eigen::Matrix2f get_rotation_matrix2f(float theta_radian)
{
    Eigen::Matrix2f rot;
    rot << cos(theta_radian), -sin(theta_radian), sin(theta_radian), cos(theta_radian);
    return rot;
}


Vec2f get_translation_vec2f(Vec2f &vec_a, Vec2f &vec_b)
{
    return vec_b - vec_a;
}


// Eigen::Matrix3f get_homogeneous_transform(Eigen::Matrix2f &rotation, Vec2f translation)
Eigen::Matrix3f get_homogeneous_transform(Vec2f &P0, Vec2f &P1)
{
    float theta_radian = get_angle_radian_between_two_vectors(P0, P1);
    Eigen::Matrix2f rot = get_rotation_matrix2f(theta_radian);
    Vec2f trans = get_translation_vec2f(P0, P1);

    Eigen::Matrix3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    homo.block<2, 1>(0, 2) = trans;
    return homo;
}


float get_angle_degree_between_two_vectors(Vec2f &P0, Vec2f &P1)
{
    float x_diff = P1.x() - P0.x();
    float y_diff = P1.y() - P0.y();
    float angle_degree = radian_to_degree(atan2(y_diff, x_diff));
    return angle_degree;
}


float get_angle_radian_between_two_vectors(Vec2f &P0, Vec2f &P1)
{
    float x_diff = P1.x() - P0.x();
    float y_diff = P1.y() - P0.y();
    float angle_radian = atan2(y_diff, x_diff);
    return angle_radian;
}
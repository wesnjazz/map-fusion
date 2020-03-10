#include "transformation.h"
#include "segment.h"
#include <Eigen/Dense>


Eigen::Matrix2f get_rotation_matrix2f(float theta)
{
    Eigen::Matrix2f rot;
    rot << cos(theta), -sin(theta), sin(theta), cos(theta);
    return rot;
}


Vec2f get_translation_vec2f(Vec2f &vec_a, Vec2f &vec_b)
{
    return vec_b - vec_a;
}


Eigen::Matrix3f get_homogeneous_transform(Eigen::Matrix2f &rotation, Vec2f translation)
{
    Eigen::Matrix3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rotation;
    homo.block<2, 1>(0, 2) = translation;
    return homo;
}
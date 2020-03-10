#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Eigen/Dense>
#include "segment.h"


Eigen::Matrix2f get_rotation_matrix2f(float theta_radian);
Vec2f get_translation_vec2f(Vec2f &vec_a, Vec2f &vec_b);
Eigen::Matrix3f get_homogeneous_transform(Eigen::Matrix2f &rotation, Vec2f translation);


#endif
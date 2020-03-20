#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Eigen/Dense>
#include "segment.h"


Mat2f get_rotation_matrix2f(float theta_radian);
Vec2f get_translation_vec2f(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree);
Mat3f get_homogeneous_transform(Vec2f &P0, Vec2f &P1);
Mat3f get_homogeneous_transform_frame_A_to_B(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree);
Mat3f get_homogeneous_transform_dx_dy(float dx, float dy, float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree);

Vec3f get_frame_from_homogeneous_transform(Mat3f &frame);
void cut_redundant_epsilon_Mat3f(Mat3f &m);
// Eigen::Matrix3f get_homogeneous_transform(Eigen::Matrix2f &rotation, Vec2f translation);
float get_angle_degree_between_two_vectors(Vec2f &P0, Vec2f &P1);
float get_angle_radian_between_two_vectors(Vec2f &P0, Vec2f &P1);

#endif
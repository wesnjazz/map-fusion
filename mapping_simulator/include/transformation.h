#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Eigen/Dense>
#include "segment.h"


Mat2f get_pure_ROT(float cos_theta, float sin_theta);
Vec2f get_pure_TRANS(float x, float y);
Mat3f get_HT_from_ROT_and_TRANS(Mat2f &pure_ROT, Vec2f &pure_TRANS);
Mat3f get_HT_Aframe_to_Bframe(Vec3f &departure, Vec3f &arrival);
Mat3f get_HT_inverse_Aframe_to_Wframe(Mat3f &Aframe);
Mat3f get_HT_ROT_only(float theta_degree);

Vec3f get_frame_from_homogeneous_transform(Mat3f &frame);
void cut_redundant_epsilon_Mat3f(Mat3f &m);
float get_angle_degree_between_two_vectors(Vec2f &P0, Vec2f &P1);
float get_angle_radian_between_two_vectors(Vec2f &P0, Vec2f &P1);

/** Depricates **/
Mat2f get_rotation_matrix2f(float theta_radian);
Vec2f get_translation_vec2f(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree);
Mat3f get_homogeneous_transform(Vec2f &P0, Vec2f &P1);
Mat3f get_homogeneous_transform_frame_A_to_B(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree);
Mat3f get_homogeneous_transform_dx_dy(float dx, float dy, float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree);

#endif
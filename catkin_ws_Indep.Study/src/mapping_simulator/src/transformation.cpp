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


Mat3f get_homogeneous_transform(Vec2f &P0, Vec2f &P1)
{
    float theta_radian = get_angle_radian_between_two_vectors(P0, P1);
    theta_radian = cut_redundant_epsilon( theta_radian );
    Mat2f rot = get_rotation_matrix2f(theta_radian);
    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    return homo;
}


Mat3f get_homogeneous_transform_frame_A_to_B(float A_x, float A_y, float A_theta_degree, float B_x, float B_y, float B_theta_degree)
{
    Vec2f A = Vec2f(A_x, A_y);
    Vec2f B = Vec2f(B_x, B_y);
    Vec2f trans = get_translation_vec2f(A_x, A_y, A_theta_degree, B_x, B_y, B_theta_degree);
    float angle_degree = B_theta_degree - A_theta_degree;
    angle_degree = cut_redundant_epsilon( angle_degree );
    Mat2f rot = get_rotation_matrix2f(angle_degree);
    cout << "angleA,B,diff:" << A_theta_degree << ", " << B_theta_degree << ", " << angle_degree << endl;
    Mat3f homo;
    homo.setIdentity();
    homo.block<2, 2>(0, 0) = rot;
    homo.block<2, 1>(0, 2) = trans;
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




Mat2f get_pure_ROT(float cos_theta, float sin_theta)
{
    Mat2f current_frame_ROT_next_frame_inRframe_actual;
    current_frame_ROT_next_frame_inRframe_actual << cos_theta, -sin_theta, sin_theta, cos_theta;
    return current_frame_ROT_next_frame_inRframe_actual;
}


Vec2f get_pure_TRANS(float x, float y)
{
    return Vec2f(x, y);
}


Mat3f get_HT_from_ROT_and_TRANS(Mat2f &pure_ROT, Vec2f &pure_TRANS)
{
    Mat3f HT = HT.setIdentity();
    HT.block<2, 2>(0, 0) = pure_ROT;
    HT.block<2, 1>(0, 2) = pure_TRANS;
    return HT;
}


Mat3f get_HT_Aframe_to_Bframe(Vec3f &departure, Vec3f &arrival)
{
    float x_diff = arrival.x() - departure.x();
    float y_diff = arrival.y() - departure.y();
    float theta_diff_radian = degree_to_radian( arrival.z() - departure.z() );
    float cos_theta = cut_redundant_epsilon( cos(theta_diff_radian) );
    float sin_theta = cut_redundant_epsilon( sin(theta_diff_radian) );


    /** HT(homogeneous transformation matrix) from Current frame to Next frame written in Robot frame **/
    /** HT: pure ROT in Rframe + pure TRANS in Rframe **/
    /** Robot_actual **/
    /** Pure rotation in Rframe: from current -> next **/
    Mat2f Aframe_ROT_Bframe = get_pure_ROT(cos_theta, sin_theta);
    /** Pure translation in Rframe: from current -> next **/
    Vec2f Aframe_TRANS_Bframe = get_pure_TRANS(x_diff, y_diff);
    /** HT: current -> next **/
    Mat3f Aframe_HT_Bframe = get_HT_from_ROT_and_TRANS(Aframe_ROT_Bframe, Aframe_TRANS_Bframe);
    return Aframe_HT_Bframe;
}


Mat3f get_HT_inverse_Aframe_to_Wframe(Mat3f &Aframe)
{
    /** HT inverse: To transform arrival_W to Robot frame **/
    /** HT_inverse: [R_transpose | -R_transpose * p ] p: translation **/
    /**             [      0     |                1 ] **/
    Mat3f HT_inverse = HT_inverse.setIdentity();
    /** Extract rotation R and translation T for the independent calculation **/
    Mat2f HT_ROT_only = Aframe.block<2, 2>(0, 0);  // R
    Vec2f HT_TRANS_only = Aframe.block<2, 1>(0, 2);    // p
    Mat2f HT_ROT_neg = -HT_ROT_only;    // -R
    /** Pure Translation in the R_inverse: -R_transpose * p **/
    Vec2f TRANS_in_inverse = HT_ROT_neg.transpose() * HT_TRANS_only;
    /** Assign rotation and translation of the inverse **/
    HT_inverse.block<2, 2>(0, 0) = HT_ROT_only.transpose();
    HT_inverse.block<2, 1>(0, 2) = TRANS_in_inverse;
    return HT_inverse;
}


Mat3f get_HT_ROT_only(float theta_degree)
{
    float theta_radian = degree_to_radian(theta_degree);
    float cos_theta = cut_redundant_epsilon( cos(theta_radian) );
    float sin_theta = cut_redundant_epsilon( sin(theta_radian) );

    Mat2f ROT = get_pure_ROT(cos_theta, sin_theta);
    Vec2f TRANS = Vec2f(0, 0);
    Mat3f HT_ROT_only = get_HT_from_ROT_and_TRANS(ROT, TRANS);
    return HT_ROT_only;
}



// Mat3f get_homogeneous_transform_pureROT(float cos_theta, float sin_theta)
// {
//         /** HT(homogeneous transformation matrix) from Current frame to Next frame written in Robot frame **/
//     /** HT: pure ROT in Rframe + pure TRANS in Rframe **/
//     /** Robot_actual **/
//     /** Pure rotation in Rframe: from current -> next **/
//     Mat2f current_frame_ROT_next_frame_inRframe_actual;
//     current_frame_ROT_next_frame_inRframe_actual << cos_dtheta_actual, -sin_dtheta_actual, sin_dtheta_actual, cos_dtheta_actual;
//     /** Pure translation in Rframe: from current -> next **/
//     Vec2f current_frame_TRANS_next_frame_in_Rframe_actual = Vec2f(wheel_encoder_actual.dx, wheel_encoder_actual.dy);
//     /** HT: current -> next **/
//     Mat3f current_frame_HT_next_frame_in_Rframe_actual = current_frame_HT_next_frame_in_Rframe_actual.setIdentity();
//     current_frame_HT_next_frame_in_Rframe_actual.block<2, 2>(0, 0) = current_frame_ROT_next_frame_inRframe_actual;
//     current_frame_HT_next_frame_in_Rframe_actual.block<2, 1>(0, 2) = current_frame_TRANS_next_frame_in_Rframe_actual;

//     /** Robot_ideal **/
//     /** Pure rotation in Rframe: from current -> next **/
//     Mat2f current_frame_ROT_next_frame_inRframe_ideal;
//     current_frame_ROT_next_frame_inRframe_ideal << cos_dtheta_ideal, -sin_dtheta_ideal, sin_dtheta_ideal, cos_dtheta_ideal;
//     /** Pure translation in Rframe: from current -> next **/
//     Vec2f current_frame_TRANS_next_frame_in_Rframe_ideal = Vec2f(wheel_encoder_ideal.dx, wheel_encoder_ideal.dy);
//     Mat3f current_frame_HT_next_frame_in_Rframe_ideal = current_frame_HT_next_frame_in_Rframe_ideal.setIdentity();
//     current_frame_HT_next_frame_in_Rframe_ideal.block<2, 2>(0, 0) = current_frame_ROT_next_frame_inRframe_ideal;
//     current_frame_HT_next_frame_in_Rframe_ideal.block<2, 1>(0, 2) = current_frame_TRANS_next_frame_in_Rframe_ideal;

// }



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
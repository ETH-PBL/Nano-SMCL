/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Nicky Zimmerman
 */

#ifndef __MCL_CONFIG_H__
#define __MCL_CONFIG_H__



#define FREQU_FC 370*1000*1000
#define FREQU_CL 370*1000*1000

#define NUM_SEEDS 6

// #define PARALLEL 
#define NUM_CORES 8

#define PARTICLE_NUM 4096 //4096 , 8192 //be careful if here or in cmdline
#define PARTICLES_IN_L2
#define MATH_PI 3.141592654f
#define RESOLUTION 0.05f
//#define DUMP_PARTICLES
#define DUMP_PREDICTIONS

#define MAPQUANT
#define MAX_X 371
#define MAX_Y 302
#define MCL_origin_x -9.94f
#define MCL_origin_y -7.688f
#define MCL_origin_yaw 0.0f

#define TRACE_TH 180
#define TRUNC_DIST 40
#define MAX_SCAN_RANGE 4.0f
#define MIN_SCAN_RANGE 0.01f
#define OBS_SIGMA 8
#define FUSE_SIGMA 10.0f
#define LIKELIHOOD_PRECOMPUTE 0.14104739587f //0.282094792f//1.0f / fastrsqrt(2.0f * MATH_PI * OBS_SIGMA)
#define TRIGGER_DIST 0.1f
#define TRIGGER_ANG 0.1f
#define ODOM_SIGMA 0.5f
#define MAX_HEIGHT 1.3f
#define MIN_HEIGHT 0.5f
#define MASK_TH 12
#define EFF_COEFF 100000000000.0f//100000000000.0f
#define PAST_WEIGHT 0
#define TRACKING 0

#define STEP_PERIOD 50

#define DUMP_BUFFER_SIZE PARTICLE_NUM*33
#define RESULT_BUFFER_SIZE 200
#define SCAN_BUFFER_SIZE 4 * 8 * 50


#define HEADER_LENGTH 3
#define PAYLOAD_LENGTH 24
#define CHECKSUM_LENGTH 2
#define BUFFER_LENGTH (HEADER_LENGTH + PAYLOAD_LENGTH + CHECKSUM_LENGTH)


#define PACKET_HEADER 0xFE
#define PACKET_TYPE_ODOM 0x01
#define PACKET_TYPE_TOF 0x02

#define ORIGIN_F_X 0.015f
#define ORIGIN_F_Y 0.0f
#define ORIGIN_F_THETA 0.0f
#define ORIGIN_B_X -0.015f
#define ORIGIN_B_Y 0.0f
#define ORIGIN_B_THETA 3.141592f

#define ORIGIN_R_X 0.0f
#define ORIGIN_R_Y -0.015f
#define ORIGIN_R_THETA -1.570796f
#define ORIGIN_L_X 0.0f
#define ORIGIN_L_Y 0.015f
#define ORIGIN_L_THETA 1.570796f


#define TOF_NUM 2 // can be 1 or 2, also change MCL_types.h accordingly
#define TOF_NUM_MAX 4

// 640 x 480 
// k = [587.30490585,  0.0, 303.93472197,  0.0, 588.72041029, 219.94374821, 0.0, 0.0, 1.0]
// k_inv = [ 0.00170269,  0. , -0.51750755,  0. ,  0.0016986 ,  -0.37359627,  0. ,  0. ,  1.]
#define k_inv2 0.0f
#define k_inv4 0.0f
#define k_inv7 0.0f
#define k_inv8 0.0f
#define k_inv9 1.0f

// #define k_inv1 0.00170269f
// #define k_inv3 -0.51750755f
// #define k_inv5 0.0016986f
// #define k_inv6 -0.37359627f

// #define t_mat3 1.0f
// #define t_mat4 -1.0f
// #define t_mat8 -1.0f

// #define LUT_OFFSET 52
// #define LUT_BLOCK 67

// 256x192
// k = [587.30490585,  0.0, 121.573888788,  0.0, 588.72041029, 87.977499284, 0.0, 0.0, 1.0]
// k_inv = [ 0.00170269,  0.        , -0.20700302,  0.        ,  0.0016986 ,  -0.14943851,  0.        ,  0.        ,  1.        ])

#define k_inv1 0.00170269f
#define k_inv3 -0.20700302f
#define k_inv5 0.0016986f
#define k_inv6 -0.14943851f

#define LUT_OFFSET 20
#define LUT_BLOCK 27






//np.array([[0, 0, 1], [-1, 0, 0], [0, -1, 0]])

#endif

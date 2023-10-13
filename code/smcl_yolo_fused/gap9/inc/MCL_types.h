/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Nicky Zimmerman
 */

#ifndef __MCL_TYPES_H__
#define __MCL_TYPES_H__

#define SCAN_SIZE 8
#define LINE_SCAN_SIZE 32
#define GRID_SCAN_SIZE 64
#define FULL_SCAN_SIZE 88
#define SEMANTIC_DATA_SIZE 6
#define MAX_DETECT_NUM 10

typedef struct vec4f {
    float v1;    
    float v2;
    float v3;
    float v4;
} vec4f;

typedef struct vec3f {
    float v1;    
    float v2;
    float v3;
} vec3f;

typedef struct vec2f {
    float v1;    
    float v2;
} vec2f;

typedef struct particle {
    vec3f pose;
    float w;
} particle;

typedef vec3f MCL_scan[SCAN_SIZE]; // one ToF line 
typedef vec3f MCL_line_scan[LINE_SCAN_SIZE]; // one line of 4 ToF (f, r, b, l)
typedef vec3f MCL_grid_scan[GRID_SCAN_SIZE]; //8x8 ToF
typedef vec3f MCL_full_scan[FULL_SCAN_SIZE]; // 8x8 ToF front, 8 r, 8 b, 8 l

typedef float SemanticData[SEMANTIC_DATA_SIZE * MAX_DETECT_NUM + 1];
//typedef float MCL_semantic_detection[SEMANTIC_SCAN_SIZE];

typedef struct correct_task_args {
    particle* particles;
    MCL_full_scan scan;  
    uint8_t *mask;
} correct_task_args;

// struct odometry {
//     float x;    
//     float y;        
//     float z;        
//     float yaw;
// };


#endif
/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Nicky Zimmerman
 */

#ifndef __MCL_UTILS_H__
#define __MCL_UTILS_H__

#include "MCL_types.h"
#include "MCL_config.h"
#include "stdint.h"
#include "math.h"
#include "gaplib/fs_switch.h"

#define FAST_MATH_TABLE_SIZE 512

vec3f world2map(vec3f pos);
vec3f map2world(vec3f pos);
vec3f top_left();
vec3f bottom_right();
float Wrap2Pi(float angle);

// return random number between -1 and 1
float generate_random_float();
float sample_gaussian(float sigma);
vec3f backward(vec3f p1, vec3f p2);
vec3f forward(vec3f p_prev, vec3f cmd);
vec3f sample_motion(vec3f p_prev, vec3f cmd);
uint8_t is_valid(vec3f pose);
int init_uniform(particle *particles, int num_particles);
int init_gaussian(particle *particles, int num_particles, vec3f init_guess);
int predict(particle *particles, vec3f odom, uint8_t debug);


int scan2XY(float *ranges, MCL_scan scan, uint8_t *mask);
vec3f centerLidarPoints(vec3f origin, vec3f scan);
int mergeScans(float *ranges, MCL_line_scan line_scan, uint8_t *line_mask);
vec3f points2drone(vec3f pose, vec3f scan, float c, float s);
float get_likelihood(float dist);
float compute_weights(particle part, MCL_line_scan scan, uint8_t *mask);
int correct(particle *particles, MCL_line_scan scan,  uint8_t *mask);

int scan2XYZ(float *ranges, MCL_grid_scan scan);
uint8_t is_valid2D(vec2f uv);
float compute_average_range(vec4f bb, MCL_grid_scan ranges);
float trace_detection(float u_, float v_, float dx, float dy, uint16_t clsVal );
// int fuse(particle *particles, MCL_grid_scan scan, SemanticData detections);
// float compute_weights_semantic(particle part, MCL_grid_scan scan, SemanticData detections);
int fuse(particle *particles, MCL_grid_scan scan, float* detections);
float compute_weights_semantic(particle part, MCL_grid_scan scan, float* detections, float *avg_ranges, int *labels, float *confidences, vec4f *boudingBoxes);


// int correct(particle *particles, MCL_full_scan scan, uint8_t *mask);
float sum_weights(particle *particles);
float sum_weights_square(particle *particles);
int resample(particle *current, particle *next);



// // TODO: consider only take best xx% (e.g. 80%)
// int get_prediction(particle *particles, vec3f *pred);
 int WriteDataToFile(char *FileName, unsigned int size, char *OutBuffer);
int dump_particles(particle *particles, char *filename, char *OutBuffer);
// int packet_parser(uint8_t *buffer, float *ranges, vec3f *odom, float *height);
float plp_sin_f32s_xpulpv2(float x);
float plp_cos_f32s_xpulpv2(float x);
vec3f uv2camera(vec3f uv);
// int correct_semantic(particle *particles, SemanticData* data, uint8_t detectNum);
// uint8_t isTraced(uint32_t u_, uint32_t v_, float dx, float dy, uint8_t clsVal );
// float compute_weights_semantic(particle part, SemanticData* data, uint8_t detectNum);

// int mergeScans(float *f_ranges, float *r_ranges, float *b_ranges, float *l_ranges, MCL_full_scan fullscan, uint8_t *full_mask);
 int dump_result(float t, vec3f pred, char *OutBuffer);
 int WriteRowToFile(void *File, unsigned int size, char *OutBuffer);
 int dump_scan(MCL_line_scan scan, char *filename, char *OutBuffer);

/**
  @par
  Example code for the generation of the floating-point sine table:
  <pre>
  tableSize = 512;
  for (n = 0; n < (tableSize + 1); n++)
  {
  sinTable[n] = sin(2*PI*n/tableSize);
  }</pre>
 @par
  where PI value is  3.14159265358979
 */


#endif
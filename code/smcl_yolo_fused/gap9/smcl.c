/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Nicky Zimmerman
 */

#include "pmsis.h"
#include <stdlib.h>
#include <time.h>
#include "MCL_utils.h"
#include "MCL_config.h"
#include "SPI_config.h"
#include "MCL_types.h"
#include "stdint.h"
#include "math.h"
#include "gaplib/fs_switch.h"
#include "best_float32.h"
#include "gpio_config.h"
#include "spi_driver.h"
#include "spi_config.h"
#include "spi_cmds_decode.h"
#include "best_float32.h"
#include "best_float32Kernels.h"

#define PARALLEL
// #define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT(...) /**/  
#endif

PI_L2 unsigned char *buff[2];

#ifdef CONFIG_APP_LOG
#define APP_LOG_TAG "App"
#define APP_LOG_TRC(fmt, ...) PI_LOG_TRC(APP_LOG_TAG, fmt, ##__VA_ARGS__)
#define APP_LOG_DBG(fmt, ...) PI_LOG_DBG(APP_LOG_TAG, fmt, ##__VA_ARGS__)
#define APP_LOG_ERR(fmt, ...) PI_LOG_ERR(APP_LOG_TAG, fmt, ##__VA_ARGS__)
#else
#define APP_LOG_TRC(fmt, ...)
#define APP_LOG_DBG(fmt, ...)
#define APP_LOG_ERR(fmt, ...)
#endif

#if defined(CONFIG_DRIVER_OV5647_FORMAT_QVGA) || defined(CONFIG_DRIVER_OV5647_FORMAT_VGA)
// Peripheral clock must be a multiple of 20 MHz ~ 2-3%
#define CLOCK_PERIPH 360000000
#elif defined(CONFIG_DRIVER_OV5647_FORMAT_5MP)
// Peripheral clock must be a multiple of 42 MHz
#define CLOCK_PERIPH 336000000
#else
#error <OV5647 driver: No valid format specified>
#endif

#define WIDTH CONFIG_DRIVER_OV5647_FORMAT_WIDTH

#ifdef CONFIG_DRIVER_OV5647_FORMAT_5MP
#define HEIGHT 160
#else
#define HEIGHT CONFIG_DRIVER_OV5647_FORMAT_HEIGHT
#endif

#define ISP_ADJUST_DELAY_US 1500000
PI_L2 uint8_t *buffer[2];

pi_device_t *ov5647_device;
pi_evt_t end_of_capture_evt;

// For now only 10 bits config works
#define BUFFER_SIZE_IMAGE (WIDTH * HEIGHT * 2)

#ifndef STACK_SIZE
#define STACK_SIZE 1024
#endif

struct pi_cluster_task cl_task;
pi_evt_t task_block_illegal;

static uint8_t *spi_buf_rx;
static uint8_t *spi_buf_tx;

#ifdef RUN_FROM_FILE
#include "odom.h"
#include "scan.h"
#include "sem_q.h"
#endif // RUN_FROM_FILE

PI_L2 float perf_values[NUM_CORES] = {0.0f};
PI_L2 float perf_values_pred[NUM_CORES] = {0.0f};
uint32_t time_sum_fuse = 0;
uint32_t time_sum_counter_fuse = 0;
uint32_t time_sum_correct = 0;
uint32_t time_sum_counter_correct = 0;
uint32_t time_sum_resample = 0;
uint32_t time_sum_counter_resample = 0;
uint32_t time_sum_predict = 0;
uint32_t time_sum_counter_predict = 0;

struct pi_device cluster_dev;
struct pi_cluster_conf cl_conf;
struct pi_cluster_task cl_task;
pi_evt_t task_block_illegal;

// S4 seems to work with 13, 5
// S9 seems to work with 1, 13
// S6 kinda works with 2, 6 but stuck
uint32_t random_int = 13;

uint32_t camera_frame_id = 0;

vec3f p_prev = {0.0f, 0.0f, 0.0f};
vec3f p_curr = {0.0f, 0.0f, 0.0f};
vec3f pred;
vec3f cmd;
uint8_t init_odom = 1;
volatile uint8_t step = 0;
volatile uint16_t fusion = 0;

uint8_t dump = 0;
char *ScanBuffer;
char *OutBuffer;
char *ResultsBuffer;
particle *particles_current;
particle *particles_next;

uint8_t swapped = 0;

#ifdef PARALLEL
PI_CL_L1 float sum;
PI_CL_L1 float sum_part[NUM_CORES];
PI_CL_L1 float sum_square;
PI_CL_L1 float sum_square_part[NUM_CORES];

PI_CL_L1 float r;

PI_CL_L1 MCL_line_scan line_scan;
PI_CL_L1 MCL_grid_scan grid_scan;
PI_CL_L1 uint8_t line_mask[LINE_SCAN_SIZE];

PI_CL_L1 float *detections;
PI_CL_L1 uint8_t detNum;
PI_CL_L1 float avg_ranges[MAX_DETECT_NUM];
PI_CL_L1 int labels[MAX_DETECT_NUM];
PI_CL_L1 float confidences[MAX_DETECT_NUM];
PI_CL_L1 vec4f boudingBoxes[MAX_DETECT_NUM];

PI_CL_L1 float *detection_data;
#else
PI_L2 float sum;
PI_L2 float sum_part[NUM_CORES];
PI_L2 float sum_square;
PI_L2 float sum_square_part[NUM_CORES];

PI_L2 float r;

PI_L2 MCL_line_scan line_scan;
PI_L2 MCL_grid_scan grid_scan;
PI_L2 uint8_t line_mask[LINE_SCAN_SIZE];

PI_L2 float *detections;
PI_L2 uint8_t detNum;
PI_L2 float avg_ranges[MAX_DETECT_NUM];
PI_L2 int labels[MAX_DETECT_NUM];
PI_L2 float confidences[MAX_DETECT_NUM];
PI_L2 vec4f boudingBoxes[MAX_DETECT_NUM];

PI_L2 float *detection_data;
#endif

float input_scan_live[89];
float input_odom_live[7];
float detection_input_live[61];

uint32_t timestamp;

#define ROWS 1344
#define CLASSES 13
#define THRESHOLD 153      // equals 0.2 with the current quantization of the last layer
#define THRESHOLD_IOU 0.5f 
#define MAX_BOXES 5        // having more than 5 overlapping boxes is unrealistic
#define RESULTS_ELEMENTS 6        // confidence, class and x,y,w,h

signed char final_results[MAX_BOXES][RESULTS_ELEMENTS] = {0}; // x, y, w, h, conf, class

AT_DEFAULTFLASH_EXT_ADDR_TYPE best_float32_L3_Flash = 0;

char ImageName[] = "../005525.ppm";

unsigned char selected_results[ROWS][2] = {0}; // do we really need ROWS dimension here? theoretically yes, but practically maybe not
int selected_results_indices[ROWS] = {0};

/* Inputs */
// L2_MEM
/* Outputs */
L2_MEM unsigned char Output_2[17472];
L2_MEM signed char Output_1[5376];

void cluster_demosaick(void *args)
{
    uint32_t core_id = pi_core_id();
    int start = (int)((core_id) * 256 / NUM_CORES);
    int end = (int)((core_id + 1) * 256 / NUM_CORES);

    unsigned char *Out = (unsigned char *)best_float32_L2_Memory_Dyn;
    ;
    unsigned char *In = buff[0];
    int W = 256;
    int W2 = 640;
    for (int j = start; j < end; j += 1)
    {
        for (int i = 0; i < 256; i += 1)
        {
            // R
            Out[0 + 3 * (j * W + i)] = In[(2 * j * W2 + 2 * i + W2 + 1) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i + W2 + 1) * 2] >> 2); // buff[0][(i * WIDTH + j) *2 +1] << 6 | (buff[0][(i * WIDTH + j) *2] >> 2);
            // Out[3*(j*W+i+1)]    = In[j*W+i+W+1];
            // Out[3*(j*W+i+W)]    = In[j*W+i+W+1];
            // Out[3*(j*W+i+W+1)]  = In[j*W+i+W+1];
            // G
            Out[1 + 3 * (j * W + i)] = ((In[(2 * j * W2 + 2 * i + W2) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i + W2) * 2] >> 2)) + (In[(2 * j * W2 + 2 * i + 1) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i + 1) * 2] >> 2))) >> 1;
            // Out[1+3*(j*W+i+1)]    = ((In[j*W+i+W])+(In[j*W+i+1]))>>1 ;
            // Out[1+3*(j*W+i+W)]    = ((In[j*W+i+W])+(In[j*W+i+1]))>>1 ;
            // Out[1+3*(j*W+i+W+1)]  = ((In[j*W+i+W])+(In[j*W+i+1]))>>1 ;
            // B
            Out[2 + 3 * (j * W + i)] = In[(2 * j * W2 + 2 * i) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i) * 2] >> 2);
            // Out[2+3*(j*W+i+1)]    = In[2*j*W+2*i];
            // Out[2+3*(j*W+i+W)]    = In[2*j*W+2*i];
            // Out[2+3*(j*W+i+W+1)]  = In[2*j*W+2*i];
        }
    }
}

/* Cluster main entry, executed by core 0. */
void cluster_delegate_demosaick(void *arg)
{
    /* Task dispatch to cluster cores. */
    pi_cl_team_fork(NUM_CORES, cluster_demosaick, arg);
}

void get_max_score(unsigned char *scores, unsigned char *max, unsigned char *argmax)
{
    *max = 0;
    *argmax = 0;
    for (short int i = 0; i < CLASSES; i++)
    {
        // printf("%d %d\n", i, scores[i]);

        if (scores[i] > *max)
        {
            *max = scores[i];
            *argmax = i;
        }
    }
}

float get_overlap(signed char *box_1, signed char *box_2)
{
    // printf("%d %d %d %d\n", box_1[0], box_1[1], box_1[2], box_1[3]);
    // printf("%d %d %d %d\n", box_2[0], box_2[1], box_2[2], box_2[3]);

    int A_x1 = box_1[0 * ROWS];
    int A_x2 = (int)box_1[0 * ROWS] + (int)box_1[2 * ROWS];
    int B_x1 = box_2[0];
    int B_x2 = (int)box_2[0] + (int)box_2[2];
    int A_y1 = box_1[1 * ROWS];
    int A_y2 = (int)box_1[1 * ROWS] + (int)box_1[3 * ROWS];
    int B_y1 = box_2[1];
    int B_y2 = (int)box_2[1] + (int)box_2[3];
    int interArea = (int)Max(0, Min(A_x2, B_x2) - Max(A_x1, B_x1)) * (int)Max(0, Min(A_y2, B_y2) - Max(A_y1, B_y1));
    int uinionArea = box_1[2 * ROWS] * box_1[3 * ROWS] + box_2[2 * ROWS] * box_2[3 * ROWS] - interArea;
    // printf("inter area: %d\n", interArea);
    // printf("union area: %d\n", uinionArea);
    float iou = (float)interArea / (float)uinionArea;
    // printf("%f\n", iou);
    return iou;
}

void postprocess(signed char *output_buffer_1, unsigned char *output_buffer_2)
{
    // printf("postprocess\n");

    int counter = 0;

    for (int i = 0; i < ROWS; i++)
    {
        unsigned char *scores = &(output_buffer_2[i * CLASSES]);
        unsigned char max;
        unsigned char argmax;
        get_max_score(scores, &max, &argmax);
        // printf("%d %d\n", i, max);
        if (max > THRESHOLD)
        {
            selected_results[counter][0] = max;
            selected_results[counter][1] = argmax;
            selected_results_indices[counter] = i;
            // printf("%d %d %d\n", max, argmax, selected_results_indices[counter]);
            counter++;
        }
    }

    int counter2 = 0;
    for (int i = 0; i < counter; i++)
    {
        unsigned char temp_max = 0;
        int temp_index = 0;
        // if we have our max boxes without overlap we can stop
        if (counter2 >= MAX_BOXES)
        {
            break;
        }
        // look for the highest confidence score
        for (int j = 0; j < counter; j++)
        {
            if (selected_results[j][0] > temp_max)
            {
                temp_max = selected_results[j][0];
                temp_index = j;
            }
        }
        // check if we already have a box with a too high overlap
        bool new_box = true;
        for (int j = 0; j < counter2; j++)
        {
            // printf("%d\n",j);
            if (get_overlap(&(output_buffer_1[0 * ROWS + selected_results_indices[temp_index]]), &(final_results[j][0])) > THRESHOLD_IOU)
            {
                new_box = false;
                //    printf("Too big overlap!\n");
                break;
            }
        }
        if (new_box)
        {
            final_results[counter2][0] = output_buffer_1[0 * ROWS + selected_results_indices[temp_index]];
            final_results[counter2][1] = output_buffer_1[1 * ROWS + selected_results_indices[temp_index]];
            final_results[counter2][2] = output_buffer_1[2 * ROWS + selected_results_indices[temp_index]];
            final_results[counter2][3] = output_buffer_1[3 * ROWS + selected_results_indices[temp_index]];
            final_results[counter2][4] = (signed char)(temp_max - 128);
            final_results[counter2][5] = (signed char)selected_results[temp_index][1];

            float x = 4.14939484f*(float)(output_buffer_1[0*ROWS + selected_results_indices[temp_index]]);
            float y = 4.14939484f*(float)(output_buffer_1[1*ROWS + selected_results_indices[temp_index]]);
            float w = 4.14939484f*(float)(output_buffer_1[2*ROWS + selected_results_indices[temp_index]]);
            float h = 4.14939484f*(float)(output_buffer_1[3*ROWS + selected_results_indices[temp_index]]);

            detection_input_live[counter2*6 + 1] = (float)selected_results[temp_index][1];
            detection_input_live[counter2*6 + 2] = (x - w / 2);
            detection_input_live[counter2*6 + 3] = (y - w / 2);
            detection_input_live[counter2*6 + 4] = w;
            detection_input_live[counter2*6 + 5] = h;
            detection_input_live[counter2*6 + 6] = 0.00787402f*(float)(temp_max - 128);

            // printf("%d ", selected_results_indices[temp_index]);
            // printf("%f ", 0.00787402f*(float)(selected_results[temp_index][0]-128));
            // printf("%f ", 4.14939484f*(float)(output_buffer_1[0*ROWS + selected_results_indices[temp_index]]));
            // printf("%f ", 4.14939484f*(float)(output_buffer_1[1*ROWS + selected_results_indices[temp_index]]));
            // printf("%f ", 4.14939484f*(float)(output_buffer_1[2*ROWS + selected_results_indices[temp_index]]));
            // printf("%f\n", 4.14939484f*(float)(output_buffer_1[3*ROWS + selected_results_indices[temp_index]]));
            DEBUG_PRINT("confidence: %f \n", 0.00787402f*(float)(final_results[counter2][4]));
            DEBUG_PRINT("class: %d \n", (final_results[counter2][5]));
            DEBUG_PRINT("box x: %f \n", 4.14939484f*(float)(final_results[counter2][0]));
            DEBUG_PRINT("box y: %f \n", 4.14939484f*(float)(final_results[counter2][1]));
            DEBUG_PRINT("box w: %f \n", 4.14939484f*(float)(final_results[counter2][2]));
            DEBUG_PRINT("box h: %f \n", 4.14939484f*(float)(final_results[counter2][3]));
            // printf("\n");
            counter2++;
        }
        // overwrite max with 0
        selected_results[temp_index][0] = 0;
        detection_input_live[0] = counter2;
        spi_buf_tx[0] = 'S';
        spi_buf_tx[1] = RESULTS_CMD;
        memcpy(&spi_buf_tx[2], final_results, sizeof(char)*MAX_BOXES*RESULTS_ELEMENTS);

    }
}

int get_spi_command(uint8_t *spi_cmd, uint8_t len)
{
    if (spi_cmd[0] == 'S' && spi_cmd[len - 1] == 'E')
        return spi_cmd[1];
    else
        return -1;
}

void cluster_resample1(void *args)
{
    uint32_t core_id = pi_core_id();
    sum_part[core_id] = 0.0f;
    int start = (int)((core_id)*PARTICLE_NUM / NUM_CORES);
    int end = (int)((core_id + 1) * PARTICLE_NUM / NUM_CORES);
    if (end > PARTICLE_NUM)
    {
        end = PARTICLE_NUM;
    }
    for (int i = start; i < end; ++i)
    {
        sum_part[core_id] += (float)(particles_current[i].w);
    }
}
void cluster_resample2(void *args)
{
    uint32_t core_id = pi_core_id();
    int start = (int)((core_id)*PARTICLE_NUM / NUM_CORES);
    int end = (int)((core_id + 1) * PARTICLE_NUM / NUM_CORES);
    // printf("%d %d \n", start, end);
    if (end > PARTICLE_NUM)
    {
        end = PARTICLE_NUM;
    }
    for (int i = start; i < end; ++i)
    {
#ifdef PARTICLES_F16
        particles_current[i].w = (f16)(((float)(particles_current[i].w) / sum));
#else
        particles_current[i].w = (float)(((float)(particles_current[i].w) / sum));
#endif
    }
}
void cluster_resample3(void *args)
{
    uint32_t core_id = pi_core_id();
    sum_square_part[core_id] = 0.0f;
    int start = (int)((core_id)*PARTICLE_NUM / NUM_CORES);
    int end = (int)((core_id + 1) * PARTICLE_NUM / NUM_CORES);
    if (end > PARTICLE_NUM)
    {
        end = PARTICLE_NUM;
    }
    for (int i = start; i < end; ++i)
    {
        sum_square_part[core_id] += (float)(particles_current[i].w) * (float)(particles_current[i].w);
    }
}

void cluster_resample(void *args)
{

    int core_id = pi_core_id();

    int offset_i = (int)(core_id * (PARTICLE_NUM / NUM_CORES));
    float offset_j = 0.0f;
    for (int i = 0; i < core_id; ++i)
    {
        offset_j += sum_part[i];
    }
    offset_j *= (float)(PARTICLE_NUM) / sum;
    r += (offset_j - (int)offset_j) / PARTICLE_NUM;
    float acc = (float)(particles_current[0 + offset_i].w);
    volatile int i = 0;
    float frac = 1.0f / (float)PARTICLE_NUM;
    // printf("%d %f %f \n", offset_i, offset_j, sum_part[core_id]/sum*PARTICLE_NUM );
    for (int j = 0; j < (int)(sum_part[core_id] / sum * (float)PARTICLE_NUM + 0.5f); ++j)
    {
        while (r > acc && i < ((PARTICLE_NUM - 1) / NUM_CORES))
        {
            ++i;
            acc += (float)(particles_current[i + offset_i].w);
            // printf("i: %d acc: %f\n",i, acc);
        }
        // printf("%d %d\n", core_id, i + offset_i);
        // printf("j: %d i: %d\n",j + (int)offset_j, i + offset_i);
        particles_next[j + (int)offset_j].pose = particles_current[i + offset_i].pose;
        particles_next[j + (int)offset_j].w = (float)1.0f;
        r += frac;
    }
}
/* Cluster main entry, executed by core 0. */
void cluster_delegate_resample(void *arg)
{
    sum = 0.0f;
    // printf("Cluster master core entry\n");
    pi_cl_team_fork(NUM_CORES, cluster_resample1, arg);
    // printf("First fork\n");
    for (int i = 0; i < NUM_CORES; ++i)
    {
        sum += sum_part[i];
        // printf("%f\n", sum);
    }
    if (sum == 0.0f)
    {
        // printf("sum zero\n");
        swapped = 0;
        return;
    }
    pi_cl_team_fork(NUM_CORES, cluster_resample2, arg);
    pi_cl_team_fork(NUM_CORES, cluster_resample3, arg);

    sum_square = 0.0f;
    for (int i = 0; i < NUM_CORES; ++i)
    {
        sum_square += sum_square_part[i];
    }

    float eff = 1.0f / sum_square;
    // printf("eff: %f\n", eff);
    if (eff < EFF_COEFF * PARTICLE_NUM)
    {
        /* Task dispatch to cluster cores. */
        r = (float)(generate_random_float() / PARTICLE_NUM);
        pi_cl_team_fork(NUM_CORES, cluster_resample, arg);
        // printf("Fourth fork\n");

        swapped = 1;
    }
    else
    {
        swapped = 0;
    }
}

void cluster_predict(void *args)
{
    uint32_t core_id = pi_core_id();
    int start = (int)((core_id)*PARTICLE_NUM / NUM_CORES);
    int end = (int)((core_id + 1) * PARTICLE_NUM / NUM_CORES);
    if (end > PARTICLE_NUM)
    {
        end = PARTICLE_NUM;
    }

    for (int i = start; i < end; ++i)
    {
        particles_current[i].pose = sample_motion(particles_current[i].pose, cmd);
        if (!is_valid(particles_current[i].pose))
        {
            // printf("%d not valid\n", core_id);
            init_uniform(&(particles_current[i]), 1);
        }
        // printf("%d %d valid\n",i, core_id);
    }
}

void cluster_fuse(void *args)
{
    uint32_t core_id = pi_core_id();
    // printf("%d\n", core_id);
    if (core_id == 0)
    {
        // detection part, only parallelized by number of detections
#ifdef RUN_FROM_FILE
        detections = detection_input[camera_frame_id] + 1;
#else  // RUN_FROM_FILE
        detections = detection_input_live;
#endif // RUN_FROM_FILE
        detNum = (int)detections[0];

        detection_data = detections + 1; // ignore the detNum first element
    }
    pi_cl_team_barrier();
    int start = (int)((core_id)*PARTICLE_NUM / detNum);
    int end = (int)((core_id + 1) * PARTICLE_NUM / detNum);
    if (end > detNum)
    {
        end = detNum;
    }
    for (int i = start; i < end; ++i)
    {
        float l = detection_data[i * SEMANTIC_DATA_SIZE];
        labels[i] = (int)l;
        float conf = detection_data[i * SEMANTIC_DATA_SIZE + 5];
        confidences[i] = conf;
        float *bb = detection_data + (i * SEMANTIC_DATA_SIZE + 1);
        vec4f box = {bb[0], bb[1], bb[2], bb[3]};
        boudingBoxes[i] = box;
        avg_ranges[i] = compute_average_range(boudingBoxes[i], grid_scan) / RESOLUTION;
    }
    pi_cl_team_barrier();
    // weight update, parallelized by particles

    start = (int)((core_id)*PARTICLE_NUM / NUM_CORES);
    end = (int)((core_id + 1) * PARTICLE_NUM / NUM_CORES);
    if (end > PARTICLE_NUM)
    {
        end = PARTICLE_NUM;
    }

    for (int i = start; i < end; ++i)
    {
        particles_current[i].w *= compute_weights_semantic(particles_current[i], grid_scan, detections, avg_ranges, labels, confidences, boudingBoxes);
    }
}

void cluster_correct(void *args)
{
    uint32_t core_id = pi_core_id();
    int start = (int)((core_id)*PARTICLE_NUM / NUM_CORES);
    int end = (int)((core_id + 1) * PARTICLE_NUM / NUM_CORES);
    if (end > PARTICLE_NUM)
    {
        end = PARTICLE_NUM;
    }

    for (int i = start; i < end; ++i)
    {
        particles_current[i].w = compute_weights(particles_current[i], line_scan, line_mask);
    }
}

/* Cluster main entry, executed by core 0. */
void cluster_delegate_predict(void *arg)
{
    /* Task dispatch to cluster cores. */
    pi_cl_team_fork(NUM_CORES, cluster_predict, arg);
}

/* Cluster main entry, executed by core 0. */
void cluster_delegate_fuse(void *arg)
{
    /* Task dispatch to cluster cores. */
    pi_cl_team_fork(NUM_CORES, cluster_fuse, arg);
}

/* Cluster main entry, executed by core 0. */
void cluster_delegate_correct(void *arg)
{
    /* Task dispatch to cluster cores. */
    pi_cl_team_fork(NUM_CORES, cluster_correct, arg);
}

int get_prediction(particle *particles, vec3f *pred)
{
    vec3f pose = {0.0f, 0.0f, 0.0f};
    float sum = sum_weights(particles);
    float sum_sine = 0;
    float sum_cosine = 0;

    // while(particles[i].pose.v3 < (-MATH_PI))
    //         particles[i].pose.v3 += 2*MATH_PI;
    // while(particles[i].pose.v3 > (MATH_PI))
    //         particles[i].pose.v3 -= 2*MATH_PI;

    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        float w = particles[i].w;
        vec3f weighted_pose = {particles[i].pose.v1 * w, particles[i].pose.v2 * w, 0.0f};
        // printf("particle %d = (%f, %f, %f) \n", i, particles[i].pose.v1, particles[i].pose.v2, particles[i].pose.v3);
        pose.v1 += weighted_pose.v1;
        pose.v2 += weighted_pose.v2;
        sum_sine += sinf(particles[i].pose.v3) * w;
        sum_cosine += cosf(particles[i].pose.v3) * w;
    }

    float yaw = atan2f(sum_sine, sum_cosine);
    // printf("pose: %f %f %f \n", pose.v1, pose.v2, pose.v3);

    pred->v1 = pose.v1 / sum;
    pred->v2 = pose.v2 / sum;
    pred->v3 = yaw;
    // printf("prediction: %f %f %f \n", pred->v1, pred->v2, pred->v3);

    return 1;
}


int init_system(void)
{
    printf("Entering main controller\n");

    uint32_t errors = 0;

    /* Init cluster configuration structure. */
    pi_cluster_conf_init(&cl_conf);
    cl_conf.id = 0; /* Set cluster ID. */
    /* Configure & open cluster. */
    pi_open_from_conf(&cluster_dev, &cl_conf);
    if (pi_cluster_open(&cluster_dev))
    {
        DEBUG_PRINT("Cluster open failed !\n");
        pmsis_exit(-1);
    }

    /* Frequency Settings: defined in the Makefile */
    int cur_fc_freq = pi_freq_set(PI_FREQ_DOMAIN_FC, FREQ_FC * 1000 * 1000);
    int cur_cl_freq = pi_freq_set(PI_FREQ_DOMAIN_CL, FREQ_CL * 1000 * 1000);
    int cur_pe_freq = pi_freq_set(PI_FREQ_DOMAIN_PERIPH, FREQ_PE * 1000 * 1000);
    if (cur_fc_freq == -1 || cur_cl_freq == -1 || cur_pe_freq == -1)
    {
        DEBUG_PRINT("Error changing frequency !\nTest failed...\n");
        pmsis_exit(-4);
    }
    DEBUG_PRINT("FC Frequency = %d Hz CL Frequency = %d Hz PERIPH Frequency = %d Hz\n",
           pi_freq_get(PI_FREQ_DOMAIN_FC), pi_freq_get(PI_FREQ_DOMAIN_CL), pi_freq_get(PI_FREQ_DOMAIN_PERIPH));

#ifdef VOLTAGE
    pi_pmu_voltage_set(PI_PMU_VOLTAGE_DOMAIN_CHIP, VOLTAGE);
    pi_pmu_voltage_set(PI_PMU_VOLTAGE_DOMAIN_CHIP, VOLTAGE);
#endif
    DEBUG_PRINT("Voltage: %dmV\n", pi_pmu_voltage_get(PI_PMU_VOLTAGE_DOMAIN_CHIP));

    // alloc memory for particles
#ifdef PARTICLES_IN_L2
    particles_current = (particle *)pi_l2_malloc(PARTICLE_NUM * sizeof(particle));
    particles_next = (particle *)pi_l2_malloc(PARTICLE_NUM * sizeof(particle));
#else
    particles_current = (particle *)pi_l1_malloc(&cluster_dev, PARTICLE_NUM * sizeof(particle));
    particles_next = (particle *)pi_l1_malloc(&cluster_dev, PARTICLE_NUM * sizeof(particle));
#endif

    if (TRACKING)
    {
        vec3f init_guess = {-4.5f, -4.5f, 0.07f};
        init_gaussian(particles_current, PARTICLE_NUM, init_guess);
        DEBUG_PRINT("Tracking\n");
    }
    else
    {
        init_uniform(particles_current, PARTICLE_NUM);
        DEBUG_PRINT("Global localization\n");
    }

    // IMPORTANT - MUST BE CALLED AFTER THE CLUSTER IS SWITCHED ON!!!!
    int ConstructorErr = best_float32CNN_Construct();
    if (ConstructorErr)
    {
        DEBUG_PRINT("Graph constructor exited with error: (%s)\n", GetAtErrorName(ConstructorErr));
        pmsis_exit(-6);
    }

    gpio_init();
    spi_buf_rx = pi_l2_malloc(SPIBUF_SIZE);
    spi_buf_tx = pi_l2_malloc(SPIBUF_SIZE);
    memset(spi_buf_tx,0, SPIBUF_SIZE);
    spi_slave_driver_init();

    DEBUG_PRINT("Finished system init\n");
    return 0;
}

void update_tof_async(void)
{
    vec3f odom;
    odom.v1 = input_odom_live[1];
    odom.v2 = input_odom_live[2];
    odom.v3 = input_odom_live[6];

    float height = input_odom_live[3];

    // printf("Predict\n");
    if ((height >= MIN_HEIGHT) && (height <= MAX_HEIGHT))
    {
        if (init_odom)
        {
            p_prev.v1 = odom.v1;
            p_prev.v2 = odom.v2;
            p_prev.v3 = odom.v3;
            init_odom = 0;
        }
        else
        {
            p_curr.v1 = odom.v1;
            p_curr.v2 = odom.v2;
            p_curr.v3 = odom.v3;

            float dx = p_prev.v1 - p_curr.v1;
            float dy = p_prev.v2 - p_curr.v2;
            float dtheta = p_prev.v3 - p_curr.v3;
            // printf("Predict t: %f, dxdy: %f\n", input_odom_live[0], sqrt(dx * dx + dy * dy));
            if (sqrt(dx * dx + dy * dy) > TRIGGER_DIST || fabs(dtheta) > TRIGGER_ANG)
            {
                // printf("Inside predict, step \n");
                cmd = backward(p_prev, p_curr);
                int start = pi_time_get_us(); // gap_fc_readhwtimer();
#ifdef PARALLEL
                /* Prepare cluster task and send it to cluster. */
                pi_evt_sig_init(&task_block_illegal);
                pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_predict, NULL), &task_block_illegal);
                pi_evt_wait(&task_block_illegal);
#else
                predict(particles_current, cmd, 0);
#endif
                int time_predict = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
                time_sum_predict += time_predict;
                ++time_sum_counter_predict;
                // printf("time predict: %d\n", time_predict);
                p_prev = p_curr;
                step = 1;
                // printf("Finished predict\n");
                start = pi_time_get_us(); // gap_fc_readhwtimer();
                get_prediction(particles_current, &pred);
                int time_get_prediction = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
                // printf("time get prediction: %d\n", time_get_prediction);
                // printf("Predict t: %f, pred: %f, %f, %f \n",input_odom[i][0], pred.v1, pred.v2, pred.v3);
            }
        }
    }
    if ((step == 1) && (fusion > 2))
    {
        DEBUG_PRINT("Correct\n");
        mergeScans(input_scan_live + 1, line_scan, line_mask);
        uint8_t masked = 0;
        for (int i = 0; i < LINE_SCAN_SIZE; ++i)
        {
            masked += line_mask[i];
        }
        if (masked < MASK_TH)
        {
#ifdef PARALLEL
            /* Prepare cluster task and send it to cluster. */
            pi_evt_sig_init(&task_block_illegal);
            pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_correct, NULL), &task_block_illegal);
            pi_evt_wait(&task_block_illegal);
#else
            correct(particles_current, line_scan, line_mask);
#endif

#ifdef PARALLEL
            /* Prepare cluster task and send it to cluster. */
            pi_evt_sig_init(&task_block_illegal);
            pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_resample, NULL), &task_block_illegal);
            pi_evt_wait(&task_block_illegal);
#else
            swapped = resample(particles_current, particles_next);
#endif

            if (swapped)
            {
                particle *temp = particles_current;
                particles_current = particles_next;
                particles_next = temp;
            }
            step = 0;
            get_prediction(particles_current, &pred);
        }
    }
}

void update_camera_async(void)
{
    DEBUG_PRINT("camera update\n");
    scan2XYZ(input_scan_live + 1, grid_scan);

#ifdef PARALLEL
    /* Prepare cluster task and send it to cluster. */
    pi_evt_sig_init(&task_block_illegal);
    pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_fuse, NULL), &task_block_illegal);
    pi_evt_wait(&task_block_illegal);
#else

    fuse(particles_current, grid_scan, detection_input_live); // we don't want the time stamp which is the first element

#endif

    int swapped = resample(particles_current, particles_next);
    if (swapped)
    {
        particle *temp = particles_current;
        particles_current = particles_next;
        particles_next = temp;
        // printf("swapped\n");
    }
    get_prediction(particles_current, &pred);
    spi_buf_tx[0] = 'S';
    spi_buf_tx[1] = RESULTS_CMD;
    memcpy(&spi_buf_tx[2 + MAX_BOXES*RESULTS_ELEMENTS], &pred, sizeof(vec3f));
    // printf("Fuse, pred: %f, %f, %f \n", pred.v1, pred.v2, pred.v3);
    // printf("Fuse t: %f, pred: %f, %f, %f \n",detection_input[camera_frame_id][0], pred.v1, pred.v2, pred.v3);
}

static void cluster()
{

    best_float32CNN(buff[0], Output_1, Output_2);
    // printf("Runner completed\n");
}

int run_yolo(void)
{
    unsigned char *In = buff[0]; //(unsigned char*)best_float32_L2_Memory_Dyn;//buff[0] + 480*640;

    DEBUG_PRINT("start preprocess\n");

    // #ifdef PARALLEL
    //         /* Prepare cluster task and send it to cluster. */
    //         pi_evt_sig_init(&task_block_illegal);
    //         pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_demosaick, NULL), &task_block_illegal);
    //         pi_evt_wait(&task_block_illegal);
    //         memcpy(best_float32_L2_Memory_Dyn,buff[0], 256*256*3);
    // #else
    unsigned char *Out = buff[0];
    int W = 256;
    int W2 = 640;
    for (int j = 0; j < 256; j += 1)
    {
        for (int i = 0; i < 256; i += 1)
        {
            // R
            Out[3 * (j * W + i)] = In[(2 * j * W2 + 2 * i + W2 + 1) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i + W2 + 1) * 2] >> 2); // buff[0][(i * WIDTH + j) *2 +1] << 6 | (buff[0][(i * WIDTH + j) *2] >> 2);
            // Out[3*(j*W+i+1)]    = In[j*W+i+W+1];
            // Out[3*(j*W+i+W)]    = In[j*W+i+W+1];
            // Out[3*(j*W+i+W+1)]  = In[j*W+i+W+1];
            // G
            Out[1 + 3 * (j * W + i)] = ((In[(2 * j * W2 + 2 * i + W2) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i + W2) * 2] >> 2)) + (In[(2 * j * W2 + 2 * i + 1) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i + 1) * 2] >> 2))) >> 1;
            // Out[1+3*(j*W+i+1)]    = ((In[j*W+i+W])+(In[j*W+i+1]))>>1 ;
            // Out[1+3*(j*W+i+W)]    = ((In[j*W+i+W])+(In[j*W+i+1]))>>1 ;
            // Out[1+3*(j*W+i+W+1)]  = ((In[j*W+i+W])+(In[j*W+i+1]))>>1 ;
            // B
            Out[2 + 3 * (j * W + i)] = In[(2 * j * W2 + 2 * i) * 2 + 1] << 6 | (In[(2 * j * W2 + 2 * i) * 2] >> 2);
            // Out[2+3*(j*W+i+1)]    = In[2*j*W+2*i];
            // Out[2+3*(j*W+i+W)]    = In[2*j*W+2*i];
            // Out[2+3*(j*W+i+W+1)]  = In[2*j*W+2*i];
        }
    }
    // WriteImageToFile(filename, 3*256, 256, sizeof(uint8_t), buff[0], BYPASS_IO);

    best_float32_L2_Memory_Dyn = (AT_L2_POINTER)(buff[0] + 3 * 256 * 256); // we use the now free memory for the dynamic memory for the NN


    struct pi_cluster_task task;
    pi_cluster_task(&task, (void (*)(void *))cluster, NULL);
    pi_cluster_task_stacks(&task, NULL, SLAVE_STACK_SIZE);

    pi_cluster_send_task_to_cl(&cluster_dev, &task);

    postprocess(Output_1, Output_2);
    return 0;
}

int run_from_sensors(void)
{
    pi_l2_free(best_float32_L2_Memory_Dyn, 206504);
    buff[0] = pi_l2_malloc(BUFFER_SIZE_IMAGE);

    pi_err_t err = PI_OK;
    APP_LOG_DBG("Format : %d\n", CONFIG_DRIVER_OV5647_FORMAT);
    APP_LOG_DBG("Width  : %d\n", WIDTH);
    APP_LOG_DBG("Height : %d\n", HEIGHT);

    err = pi_open(PI_CAMERA_OV5647, &ov5647_device);
    if (err)
    {
        APP_LOG_ERR("Failed to open OV5647 device\n");
        goto error_handler;
    }
    APP_LOG_TRC("OV5647 device opened\n");

    APP_LOG_TRC("Buffer allocated\n");

    pi_camera_control(ov5647_device, PI_CAMERA_CMD_ON, 0);
    APP_LOG_TRC("Camera powered on\n");

    pi_time_wait_us(ISP_ADJUST_DELAY_US);
    pi_camera_control(ov5647_device, PI_CAMERA_CMD_START, 0);

    while (1)
    {
        DEBUG_PRINT("trigger camera\n");

        if (NULL == buff[0])
        {
            APP_LOG_ERR("Failed to allocate buffer in L2 memory\n");
            goto error_handler;
        }
        pi_camera_capture_async(ov5647_device, buff[0], BUFFER_SIZE_IMAGE, pi_evt_sig_init(&end_of_capture_evt));

        // the tof packet arrives at 15Hz and we want to do the camera update at 5Hz - so while we acquire the camera image we execute the tof update 3x
        for (uint8_t i = 0; i < 3; i++)
        {
            spi_exchange_blocking(spi_buf_tx, spi_buf_rx, SPI_PKT_SIZE);
            memset(spi_buf_tx,0, SPIBUF_SIZE);
            DEBUG_PRINT("received SPI\n");
            int cmd = get_spi_command(spi_buf_rx, SPI_PKT_SIZE);
            switch (cmd)
            {
            case TIMESTAMP_CMD:
                spi_decode_timestamp(spi_buf_rx, &timestamp);
                DEBUG_PRINT("THIS PACKET IS NOT SUPPOSED TO EXIST IN MCL: timestamp received %d\n", timestamp);
                break;
            case TOF_MEASUREMENT_CMD:
                spi_decode_tof_measurement(spi_buf_rx, &timestamp, input_odom_live, input_scan_live);
                update_tof_async();
                DEBUG_PRINT("measurement received at %d\n", timestamp);
                break;
            }
        }
        // we shouldn't have to wait anymore - but just to be sure
        pi_evt_wait(&end_of_capture_evt);
        DEBUG_PRINT("received frame\n");

        run_yolo();
        DEBUG_PRINT("ran yolo\n");
        update_camera_async();
        DEBUG_PRINT("updated camera\n");
    }
    return 0;
error_handler:
    printf("Test failed\n");
    return err;
}

#ifdef LOAD_TESTS
void test_sem_load()
{
    float time = detection_input[1][0];

    float *detections = detection_input[1] + 1;
    int detNum = (int)detections[0];

    float *detection_data = detections + 1;
    // vec3f pose = {2.73f, -2.15f, 1.57f};
    vec3f pose = {0.3f, 0.1f, 0.07f};
    // vec3f pose = {-0.03f, -0.10f, 0.43f};
    scan2XYZ(input_scan[19] + 1, grid_scan);

    particle part;
    part.pose = pose;
    part.w = 0.000244;

    vec3f mp = world2map(pose);
    float c = cosf(pose.v3);
    float s = sinf(pose.v3);

    // for (int i = 0; i < GRID_SCAN_SIZE; ++i)
    // {
    //     printf("Eigen::Vector3f(%f, %f, %f),\n", grid_scan[i].v1, grid_scan[i].v2, grid_scan[i].v3);
    // }
    float conf_th[13] = {0.5, 0.4, 0.8, 0.7, 0.7, 0.8, 0.8, 0.5, 0.7, 0.6, 0.8, 0.4, 0.8};
    int loc_classes[13] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0};

    printf("mp: %f, %f\n", mp.v1, mp.v2);

    for (int i = 0; i < detNum; ++i)
    {

        float label = detection_data[i * SEMANTIC_DATA_SIZE];
        int l = (int)label;
        float conf = detection_data[i * SEMANTIC_DATA_SIZE + 5];
        if (loc_classes[l] == 0)
            continue;
        if (conf < conf_th[l])
        {
            continue;
        }

        float *bb = detection_data + (i * SEMANTIC_DATA_SIZE + 1);
        vec4f box = {bb[0], bb[1], bb[2], bb[3]};
        printf("detection %d: (%d, %f, %f, %f, %f, %f)\n", i, (int)l, bb[0], bb[1], bb[2], bb[3], conf);

        // uint16_t sval = toy_map[(uint32_t)roundf(mp.v2)][(uint32_t)roundf(mp.v1)];
        int clsVal = powf(2, l + 1); // LSB is the occupancy map, and then we have class map, so add one
        // printf("map value: %d, class value: %f\n", sval, clsVal);

        vec3f center = {0.5f * (box.v1 + box.v3), 0.5f * (box.v2 + box.v4), 0.0f};
        printf("center: %f, %f\n", center.v1, center.v2);

        vec3f dir = uv2camera(center);
        printf("dir: %f, %f\n", dir.v1, dir.v2);

        vec3f uv = points2drone(pose, dir, c, s);

        float dx = uv.v1 - mp.v1;
        float dy = uv.v2 - mp.v2;
        // printf("%f %f %f %f\n", uv.v1, uv.v2, mp.v1, mp.v2);
        float norm = sqrtf(dx * dx + dy * dy);
        dx = dx / norm;
        dy = dy / norm;

        printf("uv: %f, %f\n", dx, dy);

        float rayDist = trace_detection(mp.v1, mp.v2, dx, dy, clsVal);
        printf("rayDist: %f\n", rayDist);

        float avgRange = compute_average_range(box, grid_scan) / RESOLUTION;

        printf("avgRange: %f\n", avgRange);
    }
    // float w = compute_weights_semantic(part, grid_scan, detections);
    // printf("w: %f\n", w );
}
#endif // LOAD_TESTS

#ifdef RUN_FROM_FILE
void test_sequential_from_file(void)
{
    printf("Entering main controller\n");
    pi_freq_set(PI_FREQ_DOMAIN_FC, FREQU_FC);
    pi_freq_set(PI_FREQ_DOMAIN_CL, FREQU_CL);
    int32_t cur_fc_freq = pi_freq_get(PI_FREQ_DOMAIN_FC);
    int32_t cur_cl_freq = pi_freq_get(PI_FREQ_DOMAIN_CL);

    printf("FC frequency : %ld\nCL frequency : %ld\n", cur_fc_freq, cur_cl_freq);

    uint32_t errors = 0;

    /* Init cluster configuration structure. */
    pi_cluster_conf_init(&cl_conf);
    cl_conf.id = 0; /* Set cluster ID. */
    /* Configure & open cluster. */
    pi_open_from_conf(&cluster_dev, &cl_conf);
    if (pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open failed !\n");
        pmsis_exit(-1);
    }

    ScanBuffer = (char *)pi_l2_malloc(SCAN_BUFFER_SIZE);
    OutBuffer = (char *)pi_l2_malloc(DUMP_BUFFER_SIZE);
    ResultsBuffer = (char *)pi_l2_malloc(RESULT_BUFFER_SIZE);

    // alloc memory for particles
#ifdef PARTICLES_IN_L2
    particles_current = (particle *)pi_l2_malloc(PARTICLE_NUM * sizeof(particle));
    particles_next = (particle *)pi_l2_malloc(PARTICLE_NUM * sizeof(particle));
#else
    particles_current = (particle *)pi_l1_malloc(&cluster_dev, PARTICLE_NUM * sizeof(particle));
    particles_next = (particle *)pi_l1_malloc(&cluster_dev, PARTICLE_NUM * sizeof(particle));
#endif

    int num_steps = sizeof(input_odom) / (7 * sizeof(float));

    if (TRACKING)
    {
        vec3f init_guess = {-4.5f, -4.5f, 0.07f};
        init_gaussian(particles_current, PARTICLE_NUM, init_guess);
        printf("Tracking\n");
    }
    else
    {
        init_uniform(particles_current, PARTICLE_NUM);
        printf("Global localization\n");
    }

    step = 1;
    fusion = 2;

    get_prediction(particles_current, &pred);
    printf("Init t: %f, pred: %f, %f, %f \n", 0.0f, pred.v1, pred.v2, pred.v3);

    float camera_time = detection_input[camera_frame_id][0];
    int start_frame = 0;
    while ((camera_time - input_scan[start_frame][0]) < 0.0f)
    {
        ++camera_frame_id;
        camera_time = detection_input[camera_frame_id][0];
    }

    char ResultsFile[40] = {'\0'};
    sprintf(ResultsFile, "predictions_%d_%d.txt", PARTICLE_NUM, 0);
    switch_fs_t fs;
    __FS_INIT(fs);
    void *File = __OPEN_WRITE(fs, ResultsFile);
    memset(ResultsBuffer, 0, RESULT_BUFFER_SIZE);

#ifdef DUMP_PARTICLES
    char filename[30] = {'\0'};
    sprintf(filename, "%f_particles.txt", 0.0);
    memset(OutBuffer, 0, DUMP_BUFFER_SIZE);
    dump_particles(particles_current, filename, OutBuffer);
#endif
    int num_frames_to_run = 1600; // S4

    // //test from file
    for (int i = start_frame; i < num_steps; ++i)
    {
        vec3f odom;
        odom.v1 = input_odom[i][1];
        odom.v2 = input_odom[i][2];
        odom.v3 = input_odom[i][6];

        float height = input_odom[i][3];
       //  printf("Predict\n");
        if ((height >= MIN_HEIGHT) && (height <= MAX_HEIGHT))
        {
            if (init_odom)
            {
                p_prev.v1 = odom.v1;
                p_prev.v2 = odom.v2;
                p_prev.v3 = odom.v3;
                init_odom = 0;
            }
            else
            {
                p_curr.v1 = odom.v1;
                p_curr.v2 = odom.v2;
                p_curr.v3 = odom.v3;

                float dx = p_prev.v1 - p_curr.v1;
                float dy = p_prev.v2 - p_curr.v2;
                float dtheta = p_prev.v3 - p_curr.v3;
                // printf("Predict t: %f, dxdy: %f\n",input_odom[i][0], sqrt(dx*dx + dy*dy));
                if (sqrt(dx * dx + dy * dy) > TRIGGER_DIST || fabs(dtheta) > TRIGGER_ANG)
                {
                    // printf("Inside predict, step %d / %d\n", i, num_steps);
                    cmd = backward(p_prev, p_curr);
                    // printf("cmd %f %f %f\n", cmd.v1, cmd.v2, cmd.v3);
                    //  if (i == 281) predict(particles_current, cmd, 1);
                    //  else predict(particles_current, cmd, 0);
                    //  gap_fc_starttimer();
                    //  gap_fc_resethwtimer();
                    int start = pi_time_get_us(); // gap_fc_readhwtimer();
#ifdef PARALLEL
                    /* Prepare cluster task and send it to cluster. */
                    pi_evt_sig_init(&task_block_illegal);
                    pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_predict, NULL), &task_block_illegal);
                    pi_evt_wait(&task_block_illegal);
#else
                    predict(particles_current, cmd, 0);
#endif
                    int time_predict = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
                    time_sum_predict += time_predict;
                    ++time_sum_counter_predict;
                    // printf("time predict: %d\n", time_predict);
                    p_prev = p_curr;
                    step = 1;
                    // printf("Finished predict\n");
                    start = pi_time_get_us(); // gap_fc_readhwtimer();
                    get_prediction(particles_current, &pred);
                    int time_get_prediction = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
                    // printf("time get prediction: %d\n", time_get_prediction);
                    // printf("Predict t: %f, pred: %f, %f, %f \n",input_odom[i][0], pred.v1, pred.v2, pred.v3);
                    memset(ResultsBuffer, 0, RESULT_BUFFER_SIZE);
                    int len = dump_result(input_odom[i][0], pred, ResultsBuffer);
                    WriteRowToFile(File, len, ResultsBuffer);
                }
            }
        }
        // printf("Correct\n");
        if ((step == 1) && (fusion > 2))
        {
            // printf("Correct t: %f\n",input_scan[i][0]);
            mergeScans(input_scan[i] + 1, line_scan, line_mask);
            uint8_t masked = 0;
            for (int i = 0; i < LINE_SCAN_SIZE; ++i)
            {
                masked += line_mask[i];
                // printf("Eigen::Vector4f(%f, %f, %f, %d),\n", line_scan[i].v1, line_scan[i].v2, line_scan[i].v3, line_mask[i]);
                // printf("(%f, %f, %f, %d),\n", line_scan[i].v1, line_scan[i].v2, line_scan[i].v3, line_mask[i]);
            }
            // printf("\n");
            if (masked < MASK_TH)
            {
                // printf("Correct Step %d / %d \n", i, num_steps);
                int start = pi_time_get_us(); // gap_fc_readhwtimer();
#ifdef PARALLEL
                /* Prepare cluster task and send it to cluster. */
                pi_evt_sig_init(&task_block_illegal);
                pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_correct, NULL), &task_block_illegal);
                pi_evt_wait(&task_block_illegal);
#else
                correct(particles_current, line_scan, line_mask);
#endif
                int time_correct = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
                time_sum_correct += time_correct;
                ++time_sum_counter_correct;
                // printf("time correct: %d\n", time_correct);
#ifdef DUMP_PARTICLES
                char filename[30] = {'\0'};
                sprintf(filename, "%f_particles.txt", input_scan[i][0]);
                memset(OutBuffer, 0, DUMP_BUFFER_SIZE);
                dump_particles(particles_current, filename, OutBuffer);

                char filename2[30] = {'\0'};
                sprintf(filename2, "%f_scan.txt", input_scan[i][0]);
                memset(ScanBuffer, 0, SCAN_BUFFER_SIZE);
                dump_scan(line_scan, filename2, ScanBuffer);
#endif
                start = pi_time_get_us(); // gap_fc_readhwtimer();
#ifdef PARALLEL
                /* Prepare cluster task and send it to cluster. */
                pi_evt_sig_init(&task_block_illegal);
                pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_resample, NULL), &task_block_illegal);
                pi_evt_wait(&task_block_illegal);
#else
                swapped = resample(particles_current, particles_next);
#endif
                int time_resample = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
                time_sum_resample += time_resample;
                ++time_sum_counter_resample;
                // printf("time resample: %d\n", time_resample);
                if (swapped)
                {
                    particle *temp = particles_current;
                    particles_current = particles_next;
                    particles_next = temp;
                }
                step = 0;
                get_prediction(particles_current, &pred);
                // printf("Correct t: %f, pred: %f, %f, %f \n",input_scan[i][0], pred.v1, pred.v2, pred.v3);
                memset(ResultsBuffer, 0, RESULT_BUFFER_SIZE);
                int len = dump_result(input_scan[i][0], pred, ResultsBuffer);
                WriteRowToFile(File, len, ResultsBuffer);
            }
        }
        if (fabs(camera_time - input_scan[i][0]) < 66.0f)
        {
            // printf("Fuse Step %d / %d \n", i, num_steps);
            scan2XYZ(input_scan[i] + 1, grid_scan);
       //  printf("going to fuse\n");
            int start = pi_time_get_us(); // gap_fc_readhwtimer();
#ifdef PARALLEL
            /* Prepare cluster task and send it to cluster. */
            pi_evt_sig_init(&task_block_illegal);
            pi_cluster_send_task_to_cl_async(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate_fuse, NULL), &task_block_illegal);
            pi_evt_wait(&task_block_illegal);
#else
            fuse(particles_current, grid_scan, detection_input[camera_frame_id] + 1); // we don't want the time stamp which is the first element
#endif
            int time_fuse = pi_time_get_us() - start; // gap_fc_readhwtimer() - start;
            time_sum_fuse += time_fuse;
            ++time_sum_counter_fuse;
            // printf("time fuse: %d\n", time_fuse);
            // printf("finished fuse\n");

#ifdef DUMP_PARTICLES

            char filename[30] = {'\0'};
            sprintf(filename, "%f_particles.txt", detection_input[camera_frame_id][0]);
            memset(OutBuffer, 0, DUMP_BUFFER_SIZE);
            dump_particles(particles_current, filename, OutBuffer);
#endif
            int swapped = resample(particles_current, particles_next);
            if (swapped)
            {
                particle *temp = particles_current;
                particles_current = particles_next;
                particles_next = temp;
                // printf("swapped\n");
            }
            get_prediction(particles_current, &pred);
            // printf("Fuse t: %f, pred: %f, %f, %f \n",detection_input[camera_frame_id][0], pred.v1, pred.v2, pred.v3);
            memset(ResultsBuffer, 0, RESULT_BUFFER_SIZE);
            int len = dump_result(detection_input[camera_frame_id][0], pred, ResultsBuffer);
            WriteRowToFile(File, len, ResultsBuffer);
            ++fusion;
            ++camera_frame_id;
            camera_time = detection_input[camera_frame_id][0];
        }
        // printf("After fuse\n");
    }

    printf("time correct: %f over %d executions\n", (float)time_sum_correct / (float)time_sum_counter_correct, time_sum_counter_correct);
    printf("time fuse: %f over %d executions\n", (float)time_sum_fuse / (float)time_sum_counter_fuse, time_sum_counter_fuse);
    printf("time resample: %f over %d executions\n", (float)time_sum_resample / (float)time_sum_counter_resample, time_sum_counter_resample);
    printf("time predict: %f over %d executions\n", (float)time_sum_predict / (float)time_sum_counter_predict, time_sum_counter_predict);

    __CLOSE(File);
    __FS_DEINIT(fs);


    pmsis_exit(errors);
}
#endif // RUN_FROM_FILE

/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** SMCL ***\n\n");
    // test_sem_load();
    //  test_sequential_from_file();
    //  test_best_float32();
    init_system();
    run_from_sensors();
}

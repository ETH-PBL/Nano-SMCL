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
#include "MCL_utils.h"
#include "MCL_config.h"
#include "math.h"
#include "stdint.h"
#include "../DSP_Libraries/FastFloatApprox.h"

#include "map.h"
#include "edt.h"

extern PI_L2 float perf_values[NUM_CORES];

extern uint32_t random_int;
static float angles[8] = {0.39269908, 0.28049934, 0.16829961, 0.05609987, -0.05609987, -0.16829961,
 -0.28049934, -0.39269908}; 

#ifdef PARALLEL
PI_CL_L1 vec3f tl = {0.0f, 0.0f, 0.0f};
PI_CL_L1 vec3f br = {MAX_X - 1, MAX_Y -1, 0.0f};
// PI_CL_L1 vec3f tl_w = {MCL_origin_x, MAX_Y*RESOLUTION + MCL_origin_y, 0.0f};
// PI_CL_L1 vec3f br_w = {(MAX_X - 1)*RESOLUTION + MCL_origin_x, RESOLUTION + MCL_origin_y, 0.0f};
PI_CL_L1 float conf_th[13] = {0.5, 0.6, 0.5, 0.6, 0.6, 1.0, 0.6, 0.5, 0.7, 0.6, 1.0, 0.4, 1.0};
#else
PI_L2 vec3f tl = {0.0f, 0.0f, 0.0f};
PI_L2 vec3f br = {MAX_X - 1, MAX_Y -1, 0.0f};
// PI_L2 vec3f tl_w = {MCL_origin_x, MAX_Y*RESOLUTION + MCL_origin_y, 0.0f};
// PI_L2 vec3f br_w = {(MAX_X - 1)*RESOLUTION + MCL_origin_x, RESOLUTION + MCL_origin_y, 0.0f};
PI_L2 float conf_th[13] = {0.5, 0.6, 0.5, 0.6, 0.6, 1.0, 0.6, 0.5, 0.7, 0.6, 1.0, 0.4, 1.0};
#endif


vec3f world2map(vec3f pos)
{
    float u = roundf((pos.v1 - MCL_origin_x)/RESOLUTION);
    float v = MAX_Y - roundf((pos.v2 - MCL_origin_y)/RESOLUTION);
    vec3f pos_2d;
    pos_2d.v1 = u;
    pos_2d.v2 = v;
    pos_2d.v3 = 0.0f;
    return pos_2d;
}

vec3f map2world(vec3f pos)
{
    float x = pos.v1*RESOLUTION + MCL_origin_x;
    float y = (MAX_Y - pos.v2)*RESOLUTION + MCL_origin_y;
    vec3f pos_3d;
    pos_3d.v1 = x;
    pos_3d.v2 = y;
    pos_3d.v3 = 0.0f;
    return pos_3d;
}

vec3f top_left()
{
    return tl;
}

vec3f bottom_right()
{
    return br;   
}

float Wrap2Pi(float angle)
{
    float wAngle = angle;

    while (wAngle < -MATH_PI) wAngle += 2 * MATH_PI;

    while (wAngle > MATH_PI) wAngle -= 2 * MATH_PI;

    return wAngle;
}


// return random number between 0 and 1
float generate_random_float()
{
    random_int = (random_int * 1103515245 + 12345);
    float random_float = (float)((uint32_t)(random_int/65536) % 32768)/32768.0f;
    return random_float;
}

//
float sample_gaussian(float sigma)
{
    float sample = 0.0f;
    for (int i = 0; i < 12; ++i)
    {
        sample += 2.0f*sigma*generate_random_float() - sigma;
    }
    return sample*0.5f;
}

vec3f backward(vec3f p1, vec3f p2)
{
    float dx = p2.v1 - p1.v1;
    float dy = p2.v2 - p1.v2;
    float dtheta = p2.v3 - p1.v3;

    float a =  cosf(p1.v3);
    float b =  sinf(p1.v3);
    float f = (dx * a + dy * b) / (a * a + b * b);
    float s = (dy - f * b) / a;
    float r = dtheta;
    vec3f diff_pose = {f, s, r};


    return diff_pose;
}

vec3f forward(vec3f p_prev, vec3f cmd)
{
  
    float f = cmd.v1;
    float s = cmd.v2;
    float r = cmd.v3;

    float a =  cosf(p_prev.v3);
    float b =  sinf(p_prev.v3);

    float x = p_prev.v1 + f * a - s * b;
    float y = p_prev.v2 + f * b + s * a;
    float theta = Wrap2Pi(r + p_prev.v3); //Wrap2Pi?

    vec3f pose_new = {x,y, theta};

    return pose_new;
}



vec3f sample_motion(vec3f p_prev, vec3f cmd)
{
    float u1 = cmd.v1 - sample_gaussian(ODOM_SIGMA*fabs(cmd.v1));
    float u2 = cmd.v2 - sample_gaussian(ODOM_SIGMA*fabs(cmd.v2));
    float u3 = cmd.v3 - sample_gaussian(ODOM_SIGMA*fabs(cmd.v3));
    vec3f u = {u1, u2, u3};
    vec3f pose_new = forward(p_prev, u);
    return pose_new;
}

uint8_t is_valid(vec3f pose)
{
    vec3f uv = world2map(pose);
    vec3f tl = top_left();
    vec3f br = bottom_right();
   
    if(uv.v1 > br.v1 || uv.v1 < tl.v1 || uv.v2 > br.v2 || uv.v2 < tl.v2)
    {
        return 0;
    }
    uint8_t val = toy_map[(uint32_t)roundf(uv.v2)][(uint32_t)roundf(uv.v1)];
    if(val & 1) // 0 on least significant bit means occupied or unknown in the occ map, 1 on least significant bit means free. 
    {
        return 1;
    }
    return 0; //TODO fix this to do something!!!
}


uint8_t is_valid2D(vec2f uv)
{
    vec3f tl = top_left();
    vec3f br = bottom_right();
   
    if(uv.v1 > br.v1 || uv.v1 < tl.v1 || uv.v2 > br.v2 || uv.v2 < tl.v2)
    {
        return 0;
    }
    uint8_t val = toy_map[(uint32_t)roundf(uv.v2)][(uint32_t)roundf(uv.v1)];
    if(val & 1) // 0 on least significant bit means occupied or unknown in the occ map, 1 on least significant bit means free. 
    {
        return 1;
    }
    return 0; //TODO fix this to do something!!!
}

int init_uniform(particle *particles, int num_particles)
{
    vec3f tl_w = map2world(tl);
    vec3f br_w = map2world(br);

    int counter = 0;
    while(counter < num_particles)
    {
        float x = generate_random_float()*(br_w.v1 - tl_w.v1) +tl_w.v1;
        float y = generate_random_float()*(br_w.v2 - tl_w.v2) +tl_w.v2;
        vec3f pose = {x,y,0.0f};
        if(is_valid(pose))
        {
            // printf("valid\n");
            float theta = generate_random_float()*2*MATH_PI - MATH_PI;
            particles[counter].pose.v1 = x;
            particles[counter].pose.v2 = y;
            particles[counter].pose.v3 = theta;
            particles[counter].w = 1.0f; 
            ++counter;   
        } // if not valid we just try again (not increase the counter)   
    }
    return 1;
}

int init_gaussian(particle *particles, int num_particles, vec3f init_guess)
{

    int counter = 0;
    float cov = 0.1f;
    //float cov = 5.0f;
    while(counter < num_particles)
    {
        float dx = (generate_random_float() - 0.5f)*cov;
        float dy = (generate_random_float() - 0.5f)*cov;
        float dtheta = (generate_random_float() - 0.5f)*cov;
        vec3f pose = {init_guess.v1 + dx, init_guess.v2 + dy, init_guess.v3 + dtheta};
        if(is_valid(pose))
        {
            particles[counter].pose = pose;
            particles[counter].w = 1.0f; 
            ++counter;   
        } // if not valid we just try again (not increase the counter)   
    }
    return 1;
}



int predict(particle *particles, vec3f odom, uint8_t debug)
{
    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        if (fabs(particles[i].pose.v3) > 4.0)
        {
            printf("before %d %f\n", i, particles[i].pose.v3);
        }
        particles[i].pose = sample_motion(particles[i].pose, odom);
        if (fabs(particles[i].pose.v3) > 4.0)
        {
            printf("after %f\n", particles[i].pose.v3);
        }
        if(!is_valid(particles[i].pose))
        {
           // printf("not valid\n");
           init_uniform(&(particles[i]), 1);
           if (debug)
           {
            printf("p %d, %f %f %f\n", i, particles[i].pose.v1, particles[i].pose.v2, particles[i].pose.v3);
           }
        }
    }
    return 1;
}


int scan2XY(float *ranges, MCL_scan scan, uint8_t *mask)
{
    for (int i = 0; i < SCAN_SIZE; ++i)
    {
        float x = ranges[i];
        float y = tanf(angles[i]) * x;
        vec3f xy = {x,y,1.0f};
        if(ranges[i] <= MIN_SCAN_RANGE || ranges[i] > MAX_SCAN_RANGE)
        {
            mask[i] = 1; //invalid point
        }
        else
        {
            mask[i] = 0;
        }
        scan[i] = xy;
        //printf("%f, %f, %d\n", scan[i].v1, scan[i].v2, mask[i]);
    }
    return 1;
}


int scan2XYZ(float *ranges, MCL_grid_scan scan)
{
    for (int v = 0; v < SCAN_SIZE; ++v)
    {
        for (int h = 0; h < SCAN_SIZE; ++h)
        {
            uint index = v * SCAN_SIZE + h;
            float x = ranges[index];
            float y = tanf(angles[h]) * x;
            float z = tanf(angles[SCAN_SIZE - v - 1]) * x;
            vec3f xy = {x,y,z};
            scan[index] = xy;
        //printf("%f, %f, %d\n", scan[i].v1, scan[i].v2, mask[i]);
        }
    }
    return 1;
}

vec3f centerLidarPoints(vec3f origin, vec3f scan)
{
    float c = cosf(origin.v3);
    float s = sinf(origin.v3);
    float x = c * scan.v1 - s * scan.v2 + origin.v1;
    float y = s * scan.v1 + c * scan.v2 + origin.v2;
    float theta = 1.0f;
    vec3f pose_new = {x,y,theta};
    return pose_new;
}


int mergeScans(float *ranges, MCL_line_scan line_scan, uint8_t *line_mask)
{
    MCL_scan f_scan;
    scan2XY(ranges + 32, f_scan, line_mask);

    MCL_scan r_scan;
    scan2XY(ranges + 64, r_scan, line_mask + 8);

    MCL_scan b_scan;
    scan2XY(ranges + 72, b_scan, line_mask + 16);

    MCL_scan l_scan;
    scan2XY(ranges + 80, l_scan, line_mask + 24);

    vec3f f_origin = {ORIGIN_F_X, ORIGIN_F_Y, ORIGIN_F_THETA};
    vec3f r_origin = {ORIGIN_R_X, ORIGIN_R_Y, ORIGIN_R_THETA};
    vec3f b_origin = {ORIGIN_B_X, ORIGIN_B_Y, ORIGIN_B_THETA};
    vec3f l_origin = {ORIGIN_L_X, ORIGIN_L_Y, ORIGIN_L_THETA};

    for (int i = 0; i < SCAN_SIZE; ++i)
    {
        line_scan[i] = centerLidarPoints(f_origin, f_scan[i]);
        line_scan[i + SCAN_SIZE] = centerLidarPoints(r_origin, r_scan[i]);
        line_scan[i + 2 * SCAN_SIZE] = centerLidarPoints(b_origin, b_scan[i]);
        line_scan[i + 3 * SCAN_SIZE] = centerLidarPoints(l_origin, l_scan[i]);
    }

    return 1;

}

vec3f points2drone(vec3f pose, vec3f scan, float c, float s)
{
    float x = c * scan.v1 - s * scan.v2 + pose.v1;
    float y = s * scan.v1 + c * scan.v2 + pose.v2;
    float theta = 1.0f;
    vec3f pose_new = {x,y,theta};
    
    vec3f uv = world2map(pose_new);    
    //printf("uv: %f %f %f %f %f %f\n", scan.v1, scan.v2, pose_new.v1, pose_new.v2, uv.v1, uv.v2);  
    return world2map(pose_new);
}

float get_likelihood(float dist)
{
    return LIKELIHOOD_PRECOMPUTE * expf(-0.5f * ((dist*dist)/(OBS_SIGMA*OBS_SIGMA)));
}

float compute_weights(particle part, MCL_line_scan scan, uint8_t *mask)
{

    //float margin_x = (br.v1 - tl.v1)*margin_factor;
    //float margin_y = (br.v2 - tl.v2)*margin_factor;
    // float margin_x = 0;
    // float margin_y = 0;
    vec3f tl = top_left();
    vec3f br = bottom_right();

    uint8_t non_valid = 0;
    uint8_t valid = 0;

    uint32_t total_dist = 0;
    float total_dist_f = 0.0f;

    // float c = cosf(-part.pose.v3);
    float c = cosf(part.pose.v3);
    // float c = plp_cos_f32s_xpulpv2(part.pose.v3); // saves some cycles, but not really relevant
    // float c = fastercosfull(-part.pose.v3);
    // float s = sinf(-part.pose.v3);
    float s = sinf(part.pose.v3);
    // float s = plp_sin_f32s_xpulpv2(part.pose.v3); // saves some cycles, but not really relevant
    // float s = fastersinfull(-part.pose.v3);
    for (int i = 0; i < LINE_SCAN_SIZE; ++i)
    {
        if (mask[i] != 1)
        {
            vec3f uv = points2drone(part.pose, scan[i], c, s); 
            //printf("uv %f %f \n", uv.v1, uv.v2);  

            
            //check if point is in the reachable part of the map and afterwards (shouldn't happen if margin of the map is big enough) check if it is in the map (prevent seg fault)
            // if ((uv.v1 < br.v1 + margin_x && uv.v1 > tl.v1 - margin_x && uv.v2 < br.v2 + margin_y && uv.v2 > tl.v2 - margin_y) && (uv.v1 >= 0 && uv.v1 < MAX_X && uv.v2 >= 0 && uv.v2 < MAX_Y))
            if ((uv.v1 < br.v1 && uv.v1 > tl.v1 && uv.v2 < br.v2 && uv.v2 > tl.v2))// && (uv.v1 >= 0 && uv.v1 < MAX_X && uv.v2 >= 0 && uv.v2 < MAX_Y))
            {
                uint32_t dist = toy_edt[(uint32_t)roundf(uv.v2)][(uint32_t)roundf(uv.v1)]; // Hope it really is switched
                // float tmp = (float)dist*TRUNC_DIST/255.0f;
                // total_dist_f += (tmp/OBS_SIGMA) * (tmp/OBS_SIGMA);
                total_dist += dist*dist;
                ++valid;
            }
            else
            {
                ++non_valid;
            }
        }    
        // else{
        //      //++non_valid; //TODO check if we should count them
        //     //printf("uv: %f %f %f %f \n", 0.0f, 0.0f, scan[i].v1, scan[i].v2);  
        // }
    }
    total_dist_f = (float)total_dist*TRUNC_DIST*TRUNC_DIST/(255*255*OBS_SIGMA*OBS_SIGMA);
    // printf("total dist from int %f total dist float %f\n", total_dist_from_int, total_dist_f);
    total_dist_f +=  (float) non_valid * (TRUNC_DIST/OBS_SIGMA) * (TRUNC_DIST/OBS_SIGMA);

    float likelihood = LIKELIHOOD_PRECOMPUTE * expf(-0.5f *total_dist_f / (valid + non_valid));


    return likelihood;
}


int correct(particle *particles, MCL_line_scan scan,  uint8_t *mask)
{
   

    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        particles[i].w *= compute_weights(particles[i], scan, mask);       
    }
   
   
    return 1;
}

float compute_average_range(vec4f bb, MCL_grid_scan scan )
{

    float ranges[GRID_SCAN_SIZE];

    for (int i = 0; i < GRID_SCAN_SIZE; ++i)
    {
        vec3f pnt = scan[i];
        ranges[i] = sqrtf((scan[i].v1 * scan[i].v1) + (scan[i].v2 * scan[i].v2));
        //printf("ranges %d: %f %f %f\n", i, pnt.v1, pnt.v2, r);
    }



    // find the corresponding distances for the bounding box using the LUT
    int min_u = (int)((bb.v1 - (float)LUT_OFFSET) / (float)LUT_BLOCK);
    int min_v = (int)(bb.v2 / (float)LUT_BLOCK);
    int max_u = (int)((bb.v3 - (float)LUT_OFFSET) / (float)LUT_BLOCK);
    int max_v = (int)(bb.v4 / (float)LUT_BLOCK);

    float avgDist = -1.0f;

    if (min_u < 0.0f) min_u = 0.0f;
    if (min_v < 0.0f) min_v = 0.0f;
    if (max_u < 0.0f) max_u = 0.0f;
    if (max_v < 0.0f) max_v = 0.0f;

    int beamNum = (max_u - min_u + 1) * (max_v - min_v + 1);

    // if we have enough matches (e.g. more than 3 beams), compute an average if the distances 
    if (beamNum > 1)
    {
        avgDist = 0.0;

        for(int u = min_u; u < max_u + 1; ++u)
        {
            for(int v = min_v; v < max_v + 1; ++v)
            {
                float d = ranges[v * 8 + u];
               // printf("d: %f\n", d);
                if (d <= 0.0001f)
                {
                    --beamNum;
                }
                else avgDist += d;
            }
        }
        if (beamNum > 0) avgDist /= beamNum;
        else avgDist = -1.0;
    }

    return avgDist;
}

float trace_detection(float u_, float v_, float dx, float dy, uint16_t clsVal )
{
    float u = (float)u_ + dx;
    float v = (float)v_ + dy;
    int count = 0;
    vec2f uv = {u, v};

    while(is_valid2D(uv))
    {
        count++;
        if (count > TRACE_TH) return -1.0f;
        uint16_t val = toy_map[(uint32_t)roundf(v)][(uint32_t)roundf(u)];
        //printf("u: %f v: %f, map val: %d\n", u, v, val);
        if (val & clsVal)
        {
            //printf("traced!\n");
            return count;
        }
        u += dx;
        v += dy;
        uv.v1 = u;
        uv.v2 = v;
        
    }
   // printf("not traced!\n");

    return -1.0f;
}

float compute_weights_semantic(particle part, MCL_grid_scan scan, float* detections, float *avg_ranges, int *labels, float *confidences, vec4f *boudingBoxes)
//float compute_weights_semantic(particle part, MCL_grid_scan scan, SemanticData detections)
{
    uint8_t detNum = (int)detections[0];

    float w = 1.0f;
    float penalty = 0.01f;
    float dist = 0.0f;
    int num_valid_det = 0;

    vec3f pose = part.pose;
    vec3f mp = world2map(pose);
    float c = cosf(pose.v3);
    float s = sinf(pose.v3);
    int loc_classes[13] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0};

    for (int i = 0; i < detNum; ++i)
    {

        int l = labels[i];
        if (loc_classes[l] == 0) continue;
        if (confidences[i] < conf_th[l])
        {
            continue;
        } 

        uint16_t sval = toy_map[(uint32_t)roundf(mp.v2)][(uint32_t)roundf(mp.v1)];
        int clsVal = powf(2, l + 1); // LSB is the occupancy map, and then we have class map, so add one
        if (sval & clsVal)
        {
            if (l != 1) continue;
        } 


        vec4f bb = boudingBoxes[i];
        vec3f center = {0.5f *(bb.v1 + bb.v3), 0.5f *(bb.v2 + bb.v4), 0.0f};
        vec3f dir = uv2camera(center);

        vec3f uv = points2drone(pose, dir, c, s);  

        float dx = uv.v1 - mp.v1;
        float dy = uv.v2 - mp.v2;
        //printf("%f %f %f %f\n", uv.v1, uv.v2, mp.v1, mp.v2);
        float norm = sqrtf(dx * dx + dy * dy);

        if (norm == 0)
        {
            continue;
        }
        dx = dx / norm;
        dy = dy / norm;
        ++num_valid_det;

        float rayDist = trace_detection(mp.v1, mp.v2, dx, dy, clsVal);
        if(rayDist > 0.0f)
        {
            // ++found;
            //printf("found \n");
            //printf("%f \n", avg_ranges[i]);
            if((avg_ranges[i] < 50.0f) && (avg_ranges[i] > 0.0))
            {
                //w *= expf(-0.5f * ((rayDist - avg_ranges[i]) / FUSE_SIGMA) * ((rayDist - avg_ranges[i]) / FUSE_SIGMA));
                dist += ((rayDist - avg_ranges[i]) / FUSE_SIGMA) * ((rayDist - avg_ranges[i]) / FUSE_SIGMA);
            }
        }
        else
        {
            //w *= penalty;
            dist += 9.1;
        }
    }

    //w *= expf(-0.5f * dist * num_valid_det);
    w *= expf(-0.5f * dist);

    return w;
}

int fuse(particle *particles, MCL_grid_scan scan, float* detections)
//int fuse(particle *particles, MCL_grid_scan scan, SemanticData detections)
{
    uint8_t detNum = (int)detections[0];
    float avg_ranges[MAX_DETECT_NUM];
    int labels[MAX_DETECT_NUM];
    float confidences[MAX_DETECT_NUM];
    vec4f boudingBoxes[MAX_DETECT_NUM];

    float* detection_data = detections + 1; //ignore the detNum first element

    for (int i = 0; i < detNum; ++i)
    {
        float l = detection_data[i * SEMANTIC_DATA_SIZE];
        labels[i] = (int)l;
        float conf = detection_data[i * SEMANTIC_DATA_SIZE + 5];
        confidences[i] = conf;
        float* bb = detection_data + (i * SEMANTIC_DATA_SIZE + 1);
        vec4f box = {bb[0], bb[1], bb[2], bb[3]};
        boudingBoxes[i] = box;
        avg_ranges[i] = compute_average_range(boudingBoxes[i], scan) / RESOLUTION;
    }

    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        particles[i].w *= compute_weights_semantic(particles[i], scan, detections, avg_ranges, labels, confidences, boudingBoxes);
    }

    return 1;
}



float sum_weights(particle *particles)
{
    float sum = 0.0f;
    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        sum += particles[i].w;
    }
    return sum;
}

float sum_weights_square(particle *particles)
{
    float sum = 0.0f;
    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        sum += particles[i].w*particles[i].w;
    }
    return sum;
}

void normalize_weights(particle* particles)
{
    float max_w = 0.0f;

    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        if (particles[i].w > max_w)
        {
            max_w = particles[i].w;
        }
    }
    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        particles[i].w /= max_w;
    }
}

int resample(particle *current, particle *next)
{
    int swapped = 0;
    float sum = sum_weights(current);
    //printf("sum %f\n", sum);
    for (int i = 0; i < PARTICLE_NUM; ++i)
    {
        current[i].w /= sum;
    }

    float eff = 1.0f/sum_weights_square(current);
    //printf("eff: %f\n", eff);
    if(eff < EFF_COEFF * PARTICLE_NUM)
    {
        float r = generate_random_float()/PARTICLE_NUM;
        // printf("r %f\n", r);
        // float r = 0.0001773437095496799f;
        float acc = current[0].w;
        int i = 0;
        float frac = 1.0f / PARTICLE_NUM;
        for (int j = 0; j < PARTICLE_NUM; ++j)
        {
            float u = r + j * frac;
            while(u > acc && i < (PARTICLE_NUM - 1))
            {
                ++i;
                acc += current[i].w;
                // printf("i: %d acc: %f\n",i, acc);                
            }
            //printf("j: %d i: %d\n",j, i);
            next[j] = current[i];
            next[j].w = 1.0f;
        }
        swapped = 1;
    }
    else
    {
        normalize_weights(current);
    }
    return swapped;
}



vec3f uv2camera(vec3f uv)
{

    // multiply by K inverse
    float x = uv.v1 * k_inv1 + uv.v2 * k_inv2 + k_inv3;
    float y = uv.v1 * k_inv4 + uv.v2 * k_inv5 + k_inv6;
    float z = uv.v1 * k_inv7 + uv.v2 * k_inv8 + k_inv9;

    // normalize 
    x = x / z;
    y = y / z;

    //multiply by T

    float x_ = 1.0f;
    float y_ = -1.0f * x;
    vec3f xyzCam;
    xyzCam.v1 = x_;
    xyzCam.v2 = y_;
    xyzCam.v3 = 1.0f;

    return xyzCam;
}

int WriteDataToFile(char *FileName, unsigned int size, char *OutBuffer)
{

    switch_fs_t fs;
    __FS_INIT(fs);

    void *File = __OPEN_WRITE(fs, FileName);

    int ret = 0;


    ret+=__WRITE(File, OutBuffer, size);

    __CLOSE(File);
    __FS_DEINIT(fs);

    return ret;
}


int dump_particles(particle *particles, char *filename, char *OutBuffer)
{
    int len = 0;
    for(int i = 0; i < PARTICLE_NUM; ++i)
    {
        len += sprintf(OutBuffer + len,"%.2f, %.2f, %.2f, %f\n", particles[i].pose.v1, particles[i].pose.v2, particles[i].pose.v3, particles[i].w);
        //printf("p %d w %f\n", i, particles[i].w);
        //printf("%s\n", OutBuffer);
    }
    WriteDataToFile(filename, len, OutBuffer);

    return len;
}

int dump_scan(MCL_line_scan scan, char *filename, char *OutBuffer)
{
    int len = 0;
    for(int i = 0; i < LINE_SCAN_SIZE - 1; ++i)
    {
        len += sprintf(OutBuffer + len,"%f, %f, %f,", scan[i].v1, scan[i].v2, scan[i].v3);
        
        // printf("%s\n", OutBuffer);
    }
    len += sprintf(OutBuffer + len,"%f, %f, %f\n", scan[LINE_SCAN_SIZE - 1].v1, scan[LINE_SCAN_SIZE - 1].v2, scan[LINE_SCAN_SIZE - 1].v3);

    WriteDataToFile(filename, len, OutBuffer);
    return len;
}

int dump_result(float t, vec3f pred, char *OutBuffer)
{
    int len = sprintf(OutBuffer,"%f, %f, %f, %f\n", t, pred.v1, pred.v2, pred.v3);
  
    return len;
}
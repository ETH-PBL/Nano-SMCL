/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "app.h"

#include "FreeRTOS.h"
#include "task.h"
#include "log.h"
#include "deck.h"
#include "spi_comm.h"

#include "debug.h"
#include "crtp.h"
#include "vl53l5cx_api.h"
#include "I2C_expander.h"


#define DEBUG_MODULE "TOFMATRIX"
#define NR_OF_SENSORS 4
#define NR_OF_PIXELS 64

static VL53L5CX_Configuration tof_dev[NR_OF_SENSORS];
static VL53L5CX_ResultsData tof_data;
static uint16_t ranging_results_forward[NR_OF_PIXELS];
static uint16_t ranging_results_backward[NR_OF_PIXELS];
static uint16_t ranging_results_left[NR_OF_PIXELS];
static uint16_t ranging_results_right[NR_OF_PIXELS];

void send_command(uint8_t command, uint8_t arg);
void send_data_packet(uint8_t *data, uint16_t data_len);
void send_data_packet_28b(uint8_t *data, uint8_t size, uint8_t index);

uint8_t config_sensors(VL53L5CX_Configuration *p_dev, uint16_t new_i2c_address);

#define TOF_I2C_ADDR 0x56
uint8_t tof_i2c_addresses[NR_OF_SENSORS];

void appMain() {
   pinMode(DECK_GPIO_IO1, OUTPUT);  // Init CS pin
   pinMode(DECK_GPIO_IO2, INPUT);  // Init Busy pin
   digitalWrite(DECK_GPIO_IO1, 1);
   spiBegin();

   DEBUG_PRINT("Size of configuration %d \n", sizeof(VL53L5CX_Configuration));

   DEBUG_PRINT("Configured for %d ToF sensor(s) \n", NR_OF_SENSORS);
   // Configure GPIO expander pins modes
   I2C_expander_initialize();

   // Define the address of each ToF matrix sensor
   for(uint8_t i=0; i<NR_OF_SENSORS; i++)
      tof_i2c_addresses[i] = TOF_I2C_ADDR + 2 + 2*i;

   // Configure the ToF sensor(s)
   for(uint8_t i=0; i<NR_OF_SENSORS; i++) {
      I2C_expander_set_pin(i, 1); 

      // Configure the current sensor
      uint8_t status = config_sensors(&tof_dev[i], tof_i2c_addresses[i]);
      DEBUG_PRINT("Sensor %d conf. status: %d  (0 means ok) \n", i, status);

      // Start ranging
      status = vl53l5cx_start_ranging(&tof_dev[i]);
      DEBUG_PRINT("Sensor %d ranging status: %d  (0 means ok) \n", i, status);

      if (status == 0)
         I2C_expander_set_pin(LED0, 1);
   }

   uint8_t reg_value;
   i2cdevReadByte(I2C1_DEV, I2C_EXPANDER_I2C_ADDRESS, OUTPUT_REG_ADDRESS, &reg_value);
   DEBUG_PRINT("Sensor %d \n", reg_value);

   uint8_t ranging_ready = 255;
   uint8_t get_data_success = 255;
   uint8_t to_send_buffer[4*NR_OF_PIXELS];
 
   while(1) {
      vTaskDelay(M2T(70));
      // spi_send_timestamp();
      vl53l5cx_check_data_ready(&tof_dev[0], &ranging_ready);  // poll for data-ready

      if (ranging_ready == 1) {
         get_data_success = vl53l5cx_get_ranging_data(&tof_dev[0], &tof_data);
         if (get_data_success == VL53L5CX_STATUS_OK) {
            for(uint8_t i=0; i<NR_OF_PIXELS; i++)
            {
               if(tof_data.target_status[i] == 5 || tof_data.target_status[i] == 9)
               {
                  ranging_results_forward[i] = tof_data.distance_mm[i];
               } else
               {
                  ranging_results_forward[i] = 0;
               }
            }
               // DEBUG_PRINT(" %ld \n", (int32_t)tof_data.distance_mm[i]);
            // memcpy(&to_send_buffer[0], (uint8_t *)(&tof_data.distance_mm[0]), 2*NR_OF_PIXELS);
            // memcpy(&to_send_buffer[2*NR_OF_PIXELS], (uint8_t *)(&tof_data.nb_target_detected[0]), NR_OF_PIXELS);
            // memcpy(&to_send_buffer[3*NR_OF_PIXELS], (uint8_t *)(&tof_data.target_status[0]), NR_OF_PIXELS);

            // send_command(1, (4*NR_OF_PIXELS)/28 + 1);
            // send_data_packet(&to_send_buffer[0], 4*NR_OF_PIXELS);
         }
      }
      ranging_ready = 2;
      vl53l5cx_check_data_ready(&tof_dev[1], &ranging_ready);  // poll for data-ready

      if (ranging_ready == 1) {
         get_data_success = vl53l5cx_get_ranging_data(&tof_dev[1], &tof_data);
         if (get_data_success == VL53L5CX_STATUS_OK) {
            for(uint8_t i=0; i<NR_OF_PIXELS; i++)
            {
               if(tof_data.target_status[i] == 5 || tof_data.target_status[i] == 9)
               {
                  ranging_results_backward[i] = tof_data.distance_mm[i];
               } else
               {
                  ranging_results_backward[i] = 0;
               }
            }
         }
      }
      ranging_ready = 2;
      vl53l5cx_check_data_ready(&tof_dev[2], &ranging_ready);  // poll for data-ready

      if (ranging_ready == 1) {
         get_data_success = vl53l5cx_get_ranging_data(&tof_dev[2], &tof_data);
         if (get_data_success == VL53L5CX_STATUS_OK) {
            for(uint8_t i=0; i<NR_OF_PIXELS; i++)
            {
               if(tof_data.target_status[i] == 5 || tof_data.target_status[i] == 9)
               {
                  ranging_results_left[i] = tof_data.distance_mm[i];
               } else
               {
                  ranging_results_left[i] = 0;
               }
            }
         }
      }
      ranging_ready = 2;
      vl53l5cx_check_data_ready(&tof_dev[3], &ranging_ready);  // poll for data-ready

      if (ranging_ready == 1) {
         get_data_success = vl53l5cx_get_ranging_data(&tof_dev[3], &tof_data);
         if (get_data_success == VL53L5CX_STATUS_OK) {
            for(uint8_t i=0; i<NR_OF_PIXELS; i++)
            {
               if(tof_data.target_status[i] == 5 || tof_data.target_status[i] == 9)
               {
                  ranging_results_right[i] = tof_data.distance_mm[i];
               } else
               {
                  ranging_results_right[i] = 0;
               }
            }
         }
      }
      ranging_ready = 2;
      // theoretically we should check that we got all data
      spi_send_data(ranging_results_forward, ranging_results_right + 32, ranging_results_backward + 32, ranging_results_left + 32);
   }
}


void send_data_packet(uint8_t *data, uint16_t data_len) {
   uint8_t packets_nr = 0;
   if (data_len%28 > 0)
      packets_nr = data_len/28 + 1;
   else
      packets_nr = data_len/28;

   for (uint8_t idx=0; idx<packets_nr; idx++)
      if(data_len - 28*idx >= 28)
         send_data_packet_28b(&data[28*idx], 28, idx);
      else
         send_data_packet_28b(&data[28*idx], data_len - 28*idx, idx);
}


void send_data_packet_28b(uint8_t *data, uint8_t size, uint8_t index) {
   CRTPPacket pk;
   pk.header = CRTP_HEADER(1, 0); // first arg is the port number
   pk.size = size + 2;
   pk.data[0] = 'D';
   pk.data[1] = index;
   memcpy(&(pk.data[2]), data, size);
   crtpSendPacketBlock(&pk);
}

void send_command(uint8_t command, uint8_t arg) {
   CRTPPacket pk;
   pk.header = CRTP_HEADER(1, 0); // first arg is the port number
   pk.size = 5;
   pk.data[0] = 'C';
   pk.data[1] = command;
   pk.data[2] = arg;
   crtpSendPacketBlock(&pk);
}


uint8_t config_sensors(VL53L5CX_Configuration *p_dev, uint16_t new_i2c_address) {
   p_dev->platform = VL53L5CX_DEFAULT_I2C_ADDRESS; // use default adress for first use

   uint8_t status = 0;
   // Initialize the sensor
   status += vl53l5cx_init(p_dev); 

   // Change I2C address
   status += vl53l5cx_set_i2c_address(p_dev, new_i2c_address);
   status += vl53l5cx_set_resolution(p_dev, VL53L5CX_RESOLUTION_8X8);

   // 15Hz frame rate
   status += vl53l5cx_set_ranging_frequency_hz(p_dev, 15);
   status += vl53l5cx_set_target_order(p_dev, VL53L5CX_TARGET_ORDER_CLOSEST);
   status += vl53l5cx_set_ranging_mode(p_dev, VL53L5CX_RANGING_MODE_CONTINUOUS);

   return status;
}

// LOG_GROUP_START(MCL)
// LOG_ADD(LOG_FLOAT, pred_x, &pred_x)
// LOG_ADD(LOG_FLOAT, pred_y, &pred_y)
// LOG_ADD(LOG_FLOAT, pred_yaw, &pred_yaw)
// LOG_GROUP_STOP(MCL)

LOG_GROUP_START(ToF_f_Data)
LOG_ADD(LOG_UINT16, ToF_0, &ranging_results_forward[0])
LOG_ADD(LOG_UINT16, ToF_1, &ranging_results_forward[1])
LOG_ADD(LOG_UINT16, ToF_2, &ranging_results_forward[2])
LOG_ADD(LOG_UINT16, ToF_3, &ranging_results_forward[3])
LOG_ADD(LOG_UINT16, ToF_4, &ranging_results_forward[4])
LOG_ADD(LOG_UINT16, ToF_5, &ranging_results_forward[5])
LOG_ADD(LOG_UINT16, ToF_6, &ranging_results_forward[6])
LOG_ADD(LOG_UINT16, ToF_7, &ranging_results_forward[7])
LOG_ADD(LOG_UINT16, ToF_8, &ranging_results_forward[8])
LOG_ADD(LOG_UINT16, ToF_9, &ranging_results_forward[9])
LOG_ADD(LOG_UINT16, ToF_10, &ranging_results_forward[10])
LOG_ADD(LOG_UINT16, ToF_11, &ranging_results_forward[11])
LOG_ADD(LOG_UINT16, ToF_12, &ranging_results_forward[12])
LOG_ADD(LOG_UINT16, ToF_13, &ranging_results_forward[13])
LOG_ADD(LOG_UINT16, ToF_14, &ranging_results_forward[14])
LOG_ADD(LOG_UINT16, ToF_15, &ranging_results_forward[15])
LOG_ADD(LOG_UINT16, ToF_16, &ranging_results_forward[16])
LOG_ADD(LOG_UINT16, ToF_17, &ranging_results_forward[17])
LOG_ADD(LOG_UINT16, ToF_18, &ranging_results_forward[18])
LOG_ADD(LOG_UINT16, ToF_19, &ranging_results_forward[19])
LOG_ADD(LOG_UINT16, ToF_20, &ranging_results_forward[20])
LOG_ADD(LOG_UINT16, ToF_21, &ranging_results_forward[21])
LOG_ADD(LOG_UINT16, ToF_22, &ranging_results_forward[22])
LOG_ADD(LOG_UINT16, ToF_23, &ranging_results_forward[23])
LOG_ADD(LOG_UINT16, ToF_24, &ranging_results_forward[24])
LOG_ADD(LOG_UINT16, ToF_25, &ranging_results_forward[25])
LOG_ADD(LOG_UINT16, ToF_26, &ranging_results_forward[26])
LOG_ADD(LOG_UINT16, ToF_27, &ranging_results_forward[27])
LOG_ADD(LOG_UINT16, ToF_28, &ranging_results_forward[28])
LOG_ADD(LOG_UINT16, ToF_29, &ranging_results_forward[29])
LOG_ADD(LOG_UINT16, ToF_30, &ranging_results_forward[30])
LOG_ADD(LOG_UINT16, ToF_31, &ranging_results_forward[31])
LOG_ADD(LOG_UINT16, ToF_32, &ranging_results_forward[32])
LOG_ADD(LOG_UINT16, ToF_33, &ranging_results_forward[33])
LOG_ADD(LOG_UINT16, ToF_34, &ranging_results_forward[34])
LOG_ADD(LOG_UINT16, ToF_35, &ranging_results_forward[35])
LOG_ADD(LOG_UINT16, ToF_36, &ranging_results_forward[36])
LOG_ADD(LOG_UINT16, ToF_37, &ranging_results_forward[37])
LOG_ADD(LOG_UINT16, ToF_38, &ranging_results_forward[38])
LOG_ADD(LOG_UINT16, ToF_39, &ranging_results_forward[39])
LOG_ADD(LOG_UINT16, ToF_40, &ranging_results_forward[40])
LOG_ADD(LOG_UINT16, ToF_41, &ranging_results_forward[41])
LOG_ADD(LOG_UINT16, ToF_42, &ranging_results_forward[42])
LOG_ADD(LOG_UINT16, ToF_43, &ranging_results_forward[43])
LOG_ADD(LOG_UINT16, ToF_44, &ranging_results_forward[44])
LOG_ADD(LOG_UINT16, ToF_45, &ranging_results_forward[45])
LOG_ADD(LOG_UINT16, ToF_46, &ranging_results_forward[46])
LOG_ADD(LOG_UINT16, ToF_47, &ranging_results_forward[47])
LOG_ADD(LOG_UINT16, ToF_48, &ranging_results_forward[48])
LOG_ADD(LOG_UINT16, ToF_49, &ranging_results_forward[49])
LOG_ADD(LOG_UINT16, ToF_50, &ranging_results_forward[50])
LOG_ADD(LOG_UINT16, ToF_51, &ranging_results_forward[51])
LOG_ADD(LOG_UINT16, ToF_52, &ranging_results_forward[52])
LOG_ADD(LOG_UINT16, ToF_53, &ranging_results_forward[53])
LOG_ADD(LOG_UINT16, ToF_54, &ranging_results_forward[54])
LOG_ADD(LOG_UINT16, ToF_55, &ranging_results_forward[55])
LOG_ADD(LOG_UINT16, ToF_56, &ranging_results_forward[56])
LOG_ADD(LOG_UINT16, ToF_57, &ranging_results_forward[57])
LOG_ADD(LOG_UINT16, ToF_58, &ranging_results_forward[58])
LOG_ADD(LOG_UINT16, ToF_59, &ranging_results_forward[59])
LOG_ADD(LOG_UINT16, ToF_60, &ranging_results_forward[60])
LOG_ADD(LOG_UINT16, ToF_61, &ranging_results_forward[61])
LOG_ADD(LOG_UINT16, ToF_62, &ranging_results_forward[62])
LOG_ADD(LOG_UINT16, ToF_63, &ranging_results_forward[63])
LOG_GROUP_STOP(ToF_f_Data)

LOG_GROUP_START(ToF_b_Data)
LOG_ADD(LOG_UINT16, ToF_0, &ranging_results_backward[0])
LOG_ADD(LOG_UINT16, ToF_1, &ranging_results_backward[1])
LOG_ADD(LOG_UINT16, ToF_2, &ranging_results_backward[2])
LOG_ADD(LOG_UINT16, ToF_3, &ranging_results_backward[3])
LOG_ADD(LOG_UINT16, ToF_4, &ranging_results_backward[4])
LOG_ADD(LOG_UINT16, ToF_5, &ranging_results_backward[5])
LOG_ADD(LOG_UINT16, ToF_6, &ranging_results_backward[6])
LOG_ADD(LOG_UINT16, ToF_7, &ranging_results_backward[7])
LOG_ADD(LOG_UINT16, ToF_8, &ranging_results_backward[8])
LOG_ADD(LOG_UINT16, ToF_9, &ranging_results_backward[9])
LOG_ADD(LOG_UINT16, ToF_10, &ranging_results_backward[10])
LOG_ADD(LOG_UINT16, ToF_11, &ranging_results_backward[11])
LOG_ADD(LOG_UINT16, ToF_12, &ranging_results_backward[12])
LOG_ADD(LOG_UINT16, ToF_13, &ranging_results_backward[13])
LOG_ADD(LOG_UINT16, ToF_14, &ranging_results_backward[14])
LOG_ADD(LOG_UINT16, ToF_15, &ranging_results_backward[15])
LOG_ADD(LOG_UINT16, ToF_16, &ranging_results_backward[16])
LOG_ADD(LOG_UINT16, ToF_17, &ranging_results_backward[17])
LOG_ADD(LOG_UINT16, ToF_18, &ranging_results_backward[18])
LOG_ADD(LOG_UINT16, ToF_19, &ranging_results_backward[19])
LOG_ADD(LOG_UINT16, ToF_20, &ranging_results_backward[20])
LOG_ADD(LOG_UINT16, ToF_21, &ranging_results_backward[21])
LOG_ADD(LOG_UINT16, ToF_22, &ranging_results_backward[22])
LOG_ADD(LOG_UINT16, ToF_23, &ranging_results_backward[23])
LOG_ADD(LOG_UINT16, ToF_24, &ranging_results_backward[24])
LOG_ADD(LOG_UINT16, ToF_25, &ranging_results_backward[25])
LOG_ADD(LOG_UINT16, ToF_26, &ranging_results_backward[26])
LOG_ADD(LOG_UINT16, ToF_27, &ranging_results_backward[27])
LOG_ADD(LOG_UINT16, ToF_28, &ranging_results_backward[28])
LOG_ADD(LOG_UINT16, ToF_29, &ranging_results_backward[29])
LOG_ADD(LOG_UINT16, ToF_30, &ranging_results_backward[30])
LOG_ADD(LOG_UINT16, ToF_31, &ranging_results_backward[31])
LOG_ADD(LOG_UINT16, ToF_32, &ranging_results_backward[32])
LOG_ADD(LOG_UINT16, ToF_33, &ranging_results_backward[33])
LOG_ADD(LOG_UINT16, ToF_34, &ranging_results_backward[34])
LOG_ADD(LOG_UINT16, ToF_35, &ranging_results_backward[35])
LOG_ADD(LOG_UINT16, ToF_36, &ranging_results_backward[36])
LOG_ADD(LOG_UINT16, ToF_37, &ranging_results_backward[37])
LOG_ADD(LOG_UINT16, ToF_38, &ranging_results_backward[38])
LOG_ADD(LOG_UINT16, ToF_39, &ranging_results_backward[39])
LOG_ADD(LOG_UINT16, ToF_40, &ranging_results_backward[40])
LOG_ADD(LOG_UINT16, ToF_41, &ranging_results_backward[41])
LOG_ADD(LOG_UINT16, ToF_42, &ranging_results_backward[42])
LOG_ADD(LOG_UINT16, ToF_43, &ranging_results_backward[43])
LOG_ADD(LOG_UINT16, ToF_44, &ranging_results_backward[44])
LOG_ADD(LOG_UINT16, ToF_45, &ranging_results_backward[45])
LOG_ADD(LOG_UINT16, ToF_46, &ranging_results_backward[46])
LOG_ADD(LOG_UINT16, ToF_47, &ranging_results_backward[47])
LOG_ADD(LOG_UINT16, ToF_48, &ranging_results_backward[48])
LOG_ADD(LOG_UINT16, ToF_49, &ranging_results_backward[49])
LOG_ADD(LOG_UINT16, ToF_50, &ranging_results_backward[50])
LOG_ADD(LOG_UINT16, ToF_51, &ranging_results_backward[51])
LOG_ADD(LOG_UINT16, ToF_52, &ranging_results_backward[52])
LOG_ADD(LOG_UINT16, ToF_53, &ranging_results_backward[53])
LOG_ADD(LOG_UINT16, ToF_54, &ranging_results_backward[54])
LOG_ADD(LOG_UINT16, ToF_55, &ranging_results_backward[55])
LOG_ADD(LOG_UINT16, ToF_56, &ranging_results_backward[56])
LOG_ADD(LOG_UINT16, ToF_57, &ranging_results_backward[57])
LOG_ADD(LOG_UINT16, ToF_58, &ranging_results_backward[58])
LOG_ADD(LOG_UINT16, ToF_59, &ranging_results_backward[59])
LOG_ADD(LOG_UINT16, ToF_60, &ranging_results_backward[60])
LOG_ADD(LOG_UINT16, ToF_61, &ranging_results_backward[61])
LOG_ADD(LOG_UINT16, ToF_62, &ranging_results_backward[62])
LOG_ADD(LOG_UINT16, ToF_63, &ranging_results_backward[63])
LOG_GROUP_STOP(ToF_b_Data)

LOG_GROUP_START(ToF_l_Data)
LOG_ADD(LOG_UINT16, ToF_0, &ranging_results_left[0])
LOG_ADD(LOG_UINT16, ToF_1, &ranging_results_left[1])
LOG_ADD(LOG_UINT16, ToF_2, &ranging_results_left[2])
LOG_ADD(LOG_UINT16, ToF_3, &ranging_results_left[3])
LOG_ADD(LOG_UINT16, ToF_4, &ranging_results_left[4])
LOG_ADD(LOG_UINT16, ToF_5, &ranging_results_left[5])
LOG_ADD(LOG_UINT16, ToF_6, &ranging_results_left[6])
LOG_ADD(LOG_UINT16, ToF_7, &ranging_results_left[7])
LOG_ADD(LOG_UINT16, ToF_8, &ranging_results_left[8])
LOG_ADD(LOG_UINT16, ToF_9, &ranging_results_left[9])
LOG_ADD(LOG_UINT16, ToF_10, &ranging_results_left[10])
LOG_ADD(LOG_UINT16, ToF_11, &ranging_results_left[11])
LOG_ADD(LOG_UINT16, ToF_12, &ranging_results_left[12])
LOG_ADD(LOG_UINT16, ToF_13, &ranging_results_left[13])
LOG_ADD(LOG_UINT16, ToF_14, &ranging_results_left[14])
LOG_ADD(LOG_UINT16, ToF_15, &ranging_results_left[15])
LOG_ADD(LOG_UINT16, ToF_16, &ranging_results_left[16])
LOG_ADD(LOG_UINT16, ToF_17, &ranging_results_left[17])
LOG_ADD(LOG_UINT16, ToF_18, &ranging_results_left[18])
LOG_ADD(LOG_UINT16, ToF_19, &ranging_results_left[19])
LOG_ADD(LOG_UINT16, ToF_20, &ranging_results_left[20])
LOG_ADD(LOG_UINT16, ToF_21, &ranging_results_left[21])
LOG_ADD(LOG_UINT16, ToF_22, &ranging_results_left[22])
LOG_ADD(LOG_UINT16, ToF_23, &ranging_results_left[23])
LOG_ADD(LOG_UINT16, ToF_24, &ranging_results_left[24])
LOG_ADD(LOG_UINT16, ToF_25, &ranging_results_left[25])
LOG_ADD(LOG_UINT16, ToF_26, &ranging_results_left[26])
LOG_ADD(LOG_UINT16, ToF_27, &ranging_results_left[27])
LOG_ADD(LOG_UINT16, ToF_28, &ranging_results_left[28])
LOG_ADD(LOG_UINT16, ToF_29, &ranging_results_left[29])
LOG_ADD(LOG_UINT16, ToF_30, &ranging_results_left[30])
LOG_ADD(LOG_UINT16, ToF_31, &ranging_results_left[31])
LOG_ADD(LOG_UINT16, ToF_32, &ranging_results_left[32])
LOG_ADD(LOG_UINT16, ToF_33, &ranging_results_left[33])
LOG_ADD(LOG_UINT16, ToF_34, &ranging_results_left[34])
LOG_ADD(LOG_UINT16, ToF_35, &ranging_results_left[35])
LOG_ADD(LOG_UINT16, ToF_36, &ranging_results_left[36])
LOG_ADD(LOG_UINT16, ToF_37, &ranging_results_left[37])
LOG_ADD(LOG_UINT16, ToF_38, &ranging_results_left[38])
LOG_ADD(LOG_UINT16, ToF_39, &ranging_results_left[39])
LOG_ADD(LOG_UINT16, ToF_40, &ranging_results_left[40])
LOG_ADD(LOG_UINT16, ToF_41, &ranging_results_left[41])
LOG_ADD(LOG_UINT16, ToF_42, &ranging_results_left[42])
LOG_ADD(LOG_UINT16, ToF_43, &ranging_results_left[43])
LOG_ADD(LOG_UINT16, ToF_44, &ranging_results_left[44])
LOG_ADD(LOG_UINT16, ToF_45, &ranging_results_left[45])
LOG_ADD(LOG_UINT16, ToF_46, &ranging_results_left[46])
LOG_ADD(LOG_UINT16, ToF_47, &ranging_results_left[47])
LOG_ADD(LOG_UINT16, ToF_48, &ranging_results_left[48])
LOG_ADD(LOG_UINT16, ToF_49, &ranging_results_left[49])
LOG_ADD(LOG_UINT16, ToF_50, &ranging_results_left[50])
LOG_ADD(LOG_UINT16, ToF_51, &ranging_results_left[51])
LOG_ADD(LOG_UINT16, ToF_52, &ranging_results_left[52])
LOG_ADD(LOG_UINT16, ToF_53, &ranging_results_left[53])
LOG_ADD(LOG_UINT16, ToF_54, &ranging_results_left[54])
LOG_ADD(LOG_UINT16, ToF_55, &ranging_results_left[55])
LOG_ADD(LOG_UINT16, ToF_56, &ranging_results_left[56])
LOG_ADD(LOG_UINT16, ToF_57, &ranging_results_left[57])
LOG_ADD(LOG_UINT16, ToF_58, &ranging_results_left[58])
LOG_ADD(LOG_UINT16, ToF_59, &ranging_results_left[59])
LOG_ADD(LOG_UINT16, ToF_60, &ranging_results_left[60])
LOG_ADD(LOG_UINT16, ToF_61, &ranging_results_left[61])
LOG_ADD(LOG_UINT16, ToF_62, &ranging_results_left[62])
LOG_ADD(LOG_UINT16, ToF_63, &ranging_results_left[63])
LOG_GROUP_STOP(ToF_l_Data)

LOG_GROUP_START(ToF_r_Data)
LOG_ADD(LOG_UINT16, ToF_0, &ranging_results_right[0])
LOG_ADD(LOG_UINT16, ToF_1, &ranging_results_right[1])
LOG_ADD(LOG_UINT16, ToF_2, &ranging_results_right[2])
LOG_ADD(LOG_UINT16, ToF_3, &ranging_results_right[3])
LOG_ADD(LOG_UINT16, ToF_4, &ranging_results_right[4])
LOG_ADD(LOG_UINT16, ToF_5, &ranging_results_right[5])
LOG_ADD(LOG_UINT16, ToF_6, &ranging_results_right[6])
LOG_ADD(LOG_UINT16, ToF_7, &ranging_results_right[7])
LOG_ADD(LOG_UINT16, ToF_8, &ranging_results_right[8])
LOG_ADD(LOG_UINT16, ToF_9, &ranging_results_right[9])
LOG_ADD(LOG_UINT16, ToF_10, &ranging_results_right[10])
LOG_ADD(LOG_UINT16, ToF_11, &ranging_results_right[11])
LOG_ADD(LOG_UINT16, ToF_12, &ranging_results_right[12])
LOG_ADD(LOG_UINT16, ToF_13, &ranging_results_right[13])
LOG_ADD(LOG_UINT16, ToF_14, &ranging_results_right[14])
LOG_ADD(LOG_UINT16, ToF_15, &ranging_results_right[15])
LOG_ADD(LOG_UINT16, ToF_16, &ranging_results_right[16])
LOG_ADD(LOG_UINT16, ToF_17, &ranging_results_right[17])
LOG_ADD(LOG_UINT16, ToF_18, &ranging_results_right[18])
LOG_ADD(LOG_UINT16, ToF_19, &ranging_results_right[19])
LOG_ADD(LOG_UINT16, ToF_20, &ranging_results_right[20])
LOG_ADD(LOG_UINT16, ToF_21, &ranging_results_right[21])
LOG_ADD(LOG_UINT16, ToF_22, &ranging_results_right[22])
LOG_ADD(LOG_UINT16, ToF_23, &ranging_results_right[23])
LOG_ADD(LOG_UINT16, ToF_24, &ranging_results_right[24])
LOG_ADD(LOG_UINT16, ToF_25, &ranging_results_right[25])
LOG_ADD(LOG_UINT16, ToF_26, &ranging_results_right[26])
LOG_ADD(LOG_UINT16, ToF_27, &ranging_results_right[27])
LOG_ADD(LOG_UINT16, ToF_28, &ranging_results_right[28])
LOG_ADD(LOG_UINT16, ToF_29, &ranging_results_right[29])
LOG_ADD(LOG_UINT16, ToF_30, &ranging_results_right[30])
LOG_ADD(LOG_UINT16, ToF_31, &ranging_results_right[31])
LOG_ADD(LOG_UINT16, ToF_32, &ranging_results_right[32])
LOG_ADD(LOG_UINT16, ToF_33, &ranging_results_right[33])
LOG_ADD(LOG_UINT16, ToF_34, &ranging_results_right[34])
LOG_ADD(LOG_UINT16, ToF_35, &ranging_results_right[35])
LOG_ADD(LOG_UINT16, ToF_36, &ranging_results_right[36])
LOG_ADD(LOG_UINT16, ToF_37, &ranging_results_right[37])
LOG_ADD(LOG_UINT16, ToF_38, &ranging_results_right[38])
LOG_ADD(LOG_UINT16, ToF_39, &ranging_results_right[39])
LOG_ADD(LOG_UINT16, ToF_40, &ranging_results_right[40])
LOG_ADD(LOG_UINT16, ToF_41, &ranging_results_right[41])
LOG_ADD(LOG_UINT16, ToF_42, &ranging_results_right[42])
LOG_ADD(LOG_UINT16, ToF_43, &ranging_results_right[43])
LOG_ADD(LOG_UINT16, ToF_44, &ranging_results_right[44])
LOG_ADD(LOG_UINT16, ToF_45, &ranging_results_right[45])
LOG_ADD(LOG_UINT16, ToF_46, &ranging_results_right[46])
LOG_ADD(LOG_UINT16, ToF_47, &ranging_results_right[47])
LOG_ADD(LOG_UINT16, ToF_48, &ranging_results_right[48])
LOG_ADD(LOG_UINT16, ToF_49, &ranging_results_right[49])
LOG_ADD(LOG_UINT16, ToF_50, &ranging_results_right[50])
LOG_ADD(LOG_UINT16, ToF_51, &ranging_results_right[51])
LOG_ADD(LOG_UINT16, ToF_52, &ranging_results_right[52])
LOG_ADD(LOG_UINT16, ToF_53, &ranging_results_right[53])
LOG_ADD(LOG_UINT16, ToF_54, &ranging_results_right[54])
LOG_ADD(LOG_UINT16, ToF_55, &ranging_results_right[55])
LOG_ADD(LOG_UINT16, ToF_56, &ranging_results_right[56])
LOG_ADD(LOG_UINT16, ToF_57, &ranging_results_right[57])
LOG_ADD(LOG_UINT16, ToF_58, &ranging_results_right[58])
LOG_ADD(LOG_UINT16, ToF_59, &ranging_results_right[59])
LOG_ADD(LOG_UINT16, ToF_60, &ranging_results_right[60])
LOG_ADD(LOG_UINT16, ToF_61, &ranging_results_right[61])
LOG_ADD(LOG_UINT16, ToF_62, &ranging_results_right[62])
LOG_ADD(LOG_UINT16, ToF_63, &ranging_results_right[63])
LOG_GROUP_STOP(ToF_r_Data)

// LOG_GROUP_START(ToF_b_Data)
// LOG_ADD(LOG_UINT16, ToF_32, &tof_data1.distance_mm[32])
// LOG_ADD(LOG_UINT16, ToF_33, &tof_data1.distance_mm[33])
// LOG_ADD(LOG_UINT16, ToF_34, &tof_data1.distance_mm[34])
// LOG_ADD(LOG_UINT16, ToF_35, &tof_data1.distance_mm[35])
// LOG_ADD(LOG_UINT16, ToF_36, &tof_data1.distance_mm[36])
// LOG_ADD(LOG_UINT16, ToF_37, &tof_data1.distance_mm[37])
// LOG_ADD(LOG_UINT16, ToF_38, &tof_data1.distance_mm[38])
// LOG_ADD(LOG_UINT16, ToF_39, &tof_data1.distance_mm[39])
// LOG_GROUP_STOP(ToF_b_Data)
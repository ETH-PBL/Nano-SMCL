/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */

#include "deck.h"
#include "FreeRTOS.h"
#include "task.h"
#include "spi_comm.h"
#include "debug.h"
#include "log.h"

#define MAX_PKT_SIZE (210)
#define RESULTS_SIZE (6)
#define MAX_BOXES (5)

typedef struct vec3f {
    float v1;    
    float v2;
    float v3;
} vec3f;

typedef enum {
    TIMESTAMP_CMD = 0,
    TOF_MEASUREMENT_CMD = 1,
    RESULTS_CMD = 2,
} spi_cmd_t;

static uint8_t to_send[2 * MAX_PKT_SIZE];
static uint8_t to_recv[601];

void spi_dummy_clk_cycles() {
   float spi_dummy_rev, spi_dummy_tr;
   spiBeginTransaction(SPI_BAUDRATE_2MHZ);
   spiExchange(1, &spi_dummy_tr, &spi_dummy_rev);
   spiEndTransaction();
}

void spi_send_timestamp() {
   to_send[0] = 'S';
   to_send[1] = TIMESTAMP_CMD;
   uint32_t timestamp = (uint32_t) xTaskGetTickCount();
   memcpy(&to_send[2], &timestamp, sizeof(uint32_t));
    // DEBUG_PRINT("Timestamp: %d", *(uint32_t*)(&to_send[2]));
   uint32_t checksum = 0;
   for (int16_t i=2; i<6; i++) {
      checksum += to_send[i];
   }
   memcpy(&to_send[6], &checksum, sizeof(uint32_t));

   to_send[MAX_PKT_SIZE-1] = 'E';

   spi_dummy_clk_cycles();
   spiBeginTransaction(SPI_BAUDRATE_2MHZ);
   digitalWrite(DECK_GPIO_IO1, 0);
   spiExchange(MAX_PKT_SIZE, to_send, to_recv);
   digitalWrite(DECK_GPIO_IO1, 1);
   spiEndTransaction();
}

void spi_send_data(uint16_t *f_scan, uint16_t *r_scan, uint16_t *b_scan, uint16_t *l_scan) {
   logVarId_t idX = logGetVarId("stateEstimate", "x");
   float x = 0.0f;
   logVarId_t idY = logGetVarId("stateEstimate", "y");
   float y = 0.0f;
   logVarId_t idZ = logGetVarId("stateEstimate", "z");
   float z = 0.0f;
   logVarId_t idRoll = logGetVarId("stateEstimate", "roll");
   float roll = 0.0f;
   logVarId_t idPitch = logGetVarId("stateEstimate", "pitch");
   float pitch = 0.0f;
   logVarId_t idYaw = logGetVarId("stateEstimate", "yaw");
   float yaw = 0.0f;

   x = logGetFloat(idX);
   y = logGetFloat(idY);
   z = logGetFloat(idZ);
   roll = logGetFloat(idRoll);
   pitch = logGetFloat(idPitch);
   yaw = logGetFloat(idYaw);

   to_send[0] = 'S';
   to_send[1] = TOF_MEASUREMENT_CMD;
   uint32_t timestamp = (uint32_t) xTaskGetTickCount();
   memcpy(&to_send[2], &timestamp, sizeof(uint32_t));
   memcpy(&to_send[6], &x, sizeof(float));
   memcpy(&to_send[10], &y, sizeof(float));
   memcpy(&to_send[14], &z, sizeof(float));
   memcpy(&to_send[18], &roll, sizeof(float));
   memcpy(&to_send[22], &pitch, sizeof(float));
   memcpy(&to_send[26], &yaw, sizeof(float));
   memcpy(&to_send[30], f_scan, 64*sizeof(uint16_t));
   memcpy(&to_send[30 + 64*2], r_scan, 8*sizeof(uint16_t));
   memcpy(&to_send[30 + 72*2], b_scan, 8*sizeof(uint16_t));
   memcpy(&to_send[30 + 80*2], l_scan, 8*sizeof(uint16_t));
    // DEBUG_PRINT("Timestamp: %d", *(uint32_t*)(&to_send[2]));
   uint32_t checksum = 0;
   for (int16_t i=2; i<206; i++) {
      checksum += to_send[i];
   }
   memcpy(&to_send[206], &checksum, sizeof(uint32_t));

   to_send[MAX_PKT_SIZE-1] = 'E';

   spi_dummy_clk_cycles();
   spiBeginTransaction(SPI_BAUDRATE_2MHZ);
   digitalWrite(DECK_GPIO_IO1, 0);
   spiExchange(MAX_PKT_SIZE, to_send, to_recv);
   digitalWrite(DECK_GPIO_IO1, 1);
   spiEndTransaction();
   uint8_t cmd_type = to_recv[1];
	if (cmd_type != RESULTS_CMD)
   {
      if (cmd_type != 0x00)
		DEBUG_PRINT("received wrong packet cmd: %x\n", cmd_type);
   } else
   {
      vec3f *pred = &to_recv[2 + MAX_BOXES*RESULTS_SIZE];
      DEBUG_PRINT("prediction x: %f y: %f yaw: %f\n", pred->v1, pred->v2, pred->v3);
      for (int i = 0; i < MAX_BOXES; i++)
      {
         signed char* final_results = &to_recv[2]; 
         float confidence = 0.00787402f*(float)(final_results[i*RESULTS_SIZE + 4]);
         if(confidence > 0.5f)
         {
            DEBUG_PRINT("confidence: %f \n", confidence);
            char class = final_results[i*RESULTS_SIZE + 5];
            switch (class)
            {
            case 0:
               DEBUG_PRINT("class: sink\n");
               break;
            case 1:
               DEBUG_PRINT("class: door\n");
               break;
            case 2:
               DEBUG_PRINT("class: fridge\n");
               break;
            case 3:
               DEBUG_PRINT("class: board\n");
               break;
            case 4:
               DEBUG_PRINT("class: table\n");
               break;
            case 5:
               DEBUG_PRINT("class: box\n");
               break;
            case 6:
               DEBUG_PRINT("class: plant\n");
               break;
            case 7:
               DEBUG_PRINT("class: drawers\n");
               break;
            case 8:
               DEBUG_PRINT("class: sofa\n");
               break;
            case 9:
               DEBUG_PRINT("class: cabinet\n");
               break;
            case 10:
               DEBUG_PRINT("class: chair\n");
               break;
            case 11:
               DEBUG_PRINT("class: extinguisher\n");
               break;
            case 12:
               DEBUG_PRINT("class: person\n");
               break;
            
            default:
               break;
            }
            // DEBUG_PRINT("class: %d \n", (final_results[i*RESULTS_SIZE + 5]));
            // DEBUG_PRINT("box x: %f \n", 4.14939484f*(float)(final_results[i*RESULTS_SIZE + 0]));
            // DEBUG_PRINT("box y: %f \n", 4.14939484f*(float)(final_results[i*RESULTS_SIZE + 1]));
            // DEBUG_PRINT("box w: %f \n", 4.14939484f*(float)(final_results[i*RESULTS_SIZE + 2]));
            // DEBUG_PRINT("box h: %f \n", 4.14939484f*(float)(final_results[i*RESULTS_SIZE + 3]));
         }
      }
   }
   
   

}


// void spi_sanity_check(int16_t* state) {
//    to_send[0] = 'S';
//    to_send[1] = CHECK_CMD;
//    to_send[MAX_PKT_SIZE-1] = 'E';

//    spi_dummy_clk_cycles();
//    spiBeginTransaction(SPI_BAUDRATE_2MHZ);
//    digitalWrite(DECK_GPIO_IO1, 0);
//    spiExchange(MAX_PKT_SIZE, to_send, to_recv);
//    digitalWrite(DECK_GPIO_IO1, 1);
//    spiEndTransaction();

//    vTaskDelay(M2T(3));

//    spi_dummy_clk_cycles();
//    spiBeginTransaction(SPI_BAUDRATE_2MHZ);
//    digitalWrite(DECK_GPIO_IO1, 0);
//    spiExchange(20, to_send, to_recv);
//    digitalWrite(DECK_GPIO_IO1, 1);
//    spiEndTransaction();

//    memcpy(state, to_recv, 20);
// }
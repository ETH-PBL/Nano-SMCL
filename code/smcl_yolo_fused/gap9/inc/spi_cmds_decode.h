/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */

#ifndef SPI_CMDS_H
#define SPI_CMDS_H

#include "pmsis.h"

#define SPIBUF_SIZE (210)
#define SPI_PKT_SIZE (210)

typedef enum {
    TIMESTAMP_CMD = 0,
    TOF_MEASUREMENT_CMD = 1,
    RESULTS_CMD = 2,
    // SCAN_CMD = 1,
    // OPTIMIZE_CMD = 2,
    // POSE_REQ_CMD = 3,
    // CHECK_CMD = 4,
} spi_cmd_t;

typedef enum spi_transfer {
    SPI_OK = 0, 
    SPI_WRONG_CMD = -1, 
    SPI_ERR = -2,
    SPI_CHECKSUM_ERR = -3
} spi_transfer_t;


// spi_transfer_t spi_decode_pose(uint8_t* buffer, pcl_pose_t* pose);
// spi_transfer_t spi_decode_scan_info(uint8_t* buffer, int16_t* scan_info);
// spi_transfer_t spi_decode_pose_req(uint8_t* buffer, int16_t* pose_request);

spi_transfer_t spi_decode_timestamp(uint8_t* buffer, uint32_t* timestamp);
spi_transfer_t spi_decode_tof_measurement(uint8_t* buffer, uint32_t* timestamp, float* input_odom, float* input_scan);


#endif
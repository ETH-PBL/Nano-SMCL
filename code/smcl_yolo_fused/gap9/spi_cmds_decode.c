/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */


#define CMD_OFFSET 1
#define ID_OFFSET 2
#define TIMESTAMP_OFFSET 6
#define POS_OFFSET 10
#define TOF_OFFSET 22

#include "spi_cmds_decode.h"

spi_transfer_t spi_decode_timestamp(uint8_t* buffer, uint32_t* timestamp) {
	uint8_t cmd_type = buffer[CMD_OFFSET];
	if (cmd_type != TIMESTAMP_CMD)
		return SPI_WRONG_CMD;

	*timestamp = *(uint32_t*)(&buffer[2]);


	int16_t checksum = 0;
	for (int16_t i=2; i<6; i++)
		checksum += buffer[i];

	int16_t checksum_stm32 = *((int16_t*)&buffer[6]);
	if (checksum != checksum_stm32)
		return SPI_CHECKSUM_ERR;

	return SPI_OK;
}

spi_transfer_t spi_decode_tof_measurement(uint8_t* buffer, uint32_t* timestamp, float* input_odom, float* input_scan) {
	uint8_t cmd_type = buffer[CMD_OFFSET];
	if (cmd_type != TOF_MEASUREMENT_CMD)
		return SPI_WRONG_CMD;

	*timestamp = *(uint32_t*)(&buffer[2]);

	memcpy(input_odom, (&buffer[6]), 6*sizeof(float)); 

	for (int i = 0; i < 88; i++)
	{
		uint16_t uint16_dist = *((uint16_t*)(&buffer[30 + 2*i]));
		input_scan[i] = (float)uint16_dist;
	}

	int16_t checksum = 0;
	for (int16_t i=2; i<206; i++)
		checksum += buffer[i];

	int16_t checksum_stm32 = *((int16_t*)&buffer[6]);
	if (checksum != checksum_stm32)
		return SPI_CHECKSUM_ERR;

	return SPI_OK;
}
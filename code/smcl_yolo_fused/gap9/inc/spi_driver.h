/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */

#ifndef SPI_DRV_
#define SPI_DRV_

#include "pmsis.h"

#define PAD_GPIO_3V3_PERIPH (PI_PAD_035)
#define PAD_GPIO_CS_CUSTOM (PI_PAD_034)

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

void spi_slave_driver_init();
void spi_rcv_blocking(void* data, size_t len);
void spi_send_blocking(void* data, size_t len);
void spi_exchange_blocking(void* tx_data, void* rx_data, size_t len);

#endif

typedef enum
{
    CPOL_LOW = 0,
    CPOL_HIGH
} spi_cpol;

typedef enum
{
    CPHA_LOW = 0,
    CPHA_HIGH
} spi_cpha;

uint8_t spi_init(int baudrate, uint8_t polarity, uint8_t phase);
void spi_transfer(uint8_t *tx_buffer_local, uint8_t *rx_buffer_local, int trx_size);
void spi_send(uint8_t *tx_buffer_local, int tx_size);
void spi_receive( uint8_t *rx_buffer_local, int rx_size);

int enable_cs_custom(void);
void spi_cs_high();
void spi_cs_low(); 

void spi_change_baudrate(int baudrate);

#endif
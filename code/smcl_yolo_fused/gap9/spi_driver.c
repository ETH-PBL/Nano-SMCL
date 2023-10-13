/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */

#include "spi_driver.h"
#include "pmsis.h"
#include "spi_config.h"
#include "gpio_config.h"

static pi_device_t spi_slave;
static struct pi_spi_conf spi_slave_conf;
static pi_evt_t send_task, receive_task, end_task;


static void spi_slave_pad_init() {
    pi_pad_function_set(SPI_SLAVE_PAD_SCK, SPI_SLAVE_PAD_FUNC);
    pi_pad_function_set(SPI_SLAVE_PAD_CS0, SPI_SLAVE_PAD_FUNC);
    pi_pad_function_set(SPI_SLAVE_PAD_SDO, SPI_SLAVE_PAD_FUNC);
    pi_pad_function_set(SPI_SLAVE_PAD_SDI, SPI_SLAVE_PAD_FUNC);
}

static void spi_slave_init(pi_device_t* spi_slave, struct pi_spi_conf* spi_slave_conf) {
    pi_assert(spi_slave);
    pi_assert(spi_slave_conf);

    pi_spi_conf_init(spi_slave_conf);
    spi_slave_conf->wordsize = SPI_SLAVE_WORDSIZE;
    spi_slave_conf->big_endian = SPI_SLAVE_ENDIANESS;
    spi_slave_conf->max_baudrate = SPI_SLAVE_BAUDRATE;
    spi_slave_conf->polarity = SPI_SLAVE_POLARITY;
    spi_slave_conf->phase = SPI_SLAVE_PHASE;
    spi_slave_conf->itf = SPI_SLAVE_ITF;
    spi_slave_conf->cs = SPI_SLAVE_CS; 
    spi_slave_conf->dummy_clk_cycle = SPI_MASTER_DUMMY_CYCLE;
    spi_slave_conf->dummy_clk_cycle_mode = SPI_MASTER_DUMMY_CYCLE_MODE;
    spi_slave_conf->is_slave = SPI_SLAVE_IS_SLAVE;
    pi_open_from_conf(spi_slave, spi_slave_conf);
}

void spi_slave_driver_init() {
    spi_slave_pad_init();
    spi_slave_init(&spi_slave, &spi_slave_conf);
    if (pi_spi_open(&spi_slave)) {
        printf("ERROR: Failed to open SPI peripheral\n");
    }
}

void spi_send_blocking(void* data, size_t len) {
    pi_spi_send(&spi_slave, data, 8 * len, SPI_NO_OPTION);
}

void spi_rcv_blocking(void* data, size_t len) {
    pi_spi_receive(&spi_slave, data, 8 * len, SPI_NO_OPTION);
}

void spi_exchange_blocking(void* tx_data, void* rx_data, size_t len) {
    pi_spi_transfer(&spi_slave, tx_data, rx_data, 8 * len, SPI_NO_OPTION);
}


static int enable_3v3_periph(void)
{
    int module_initialized = 0;

    if(!module_initialized)
    {
        /* set pad to gpio mode */
        pi_pad_function_set(PAD_GPIO_3V3_PERIPH, PI_PAD_FUNC1);

        /* configure gpio output */
        pi_gpio_flags_e flags = PI_GPIO_OUTPUT;
        pi_gpio_pin_configure(PAD_GPIO_3V3_PERIPH, flags);

        pi_gpio_pin_write(PAD_GPIO_3V3_PERIPH, 1);

        /* wait some time to let voltage rise */
        pi_time_wait_us(20000);

        module_initialized = 1;
    }
    

    return 0;
}



pi_device_t gpio_cs_periph;


int enable_cs_custom(void)
{
    static int module_initialized = 0;
    if(!module_initialized)
    {
        /* set pad to gpio mode */
        pi_pad_function_set(PAD_GPIO_CS_CUSTOM, PI_PAD_FUNC1);

        /* configure gpio output */
        pi_gpio_flags_e flags = PI_GPIO_OUTPUT;
        pi_gpio_pin_configure(PAD_GPIO_CS_CUSTOM, flags);

        pi_gpio_pin_write(PAD_GPIO_CS_CUSTOM, 1);

        /* wait some time to let voltage rise */
        pi_time_wait_us(20000);

        module_initialized = 1;
    
    }

    return 0;
}

static pi_device_t spi;

uint8_t spi_init(int baudrate, uint8_t polarity, uint8_t phase)
{
    static int module_initialized = 0;

    if(!module_initialized)
    {
        /* set spi pads to function 0 */
        pi_pad_function_set(PI_PAD_034, PI_PAD_FUNC0); // CS
        pi_pad_function_set(PI_PAD_038, PI_PAD_FUNC0); // MOSI
        pi_pad_function_set(PI_PAD_039, PI_PAD_FUNC0); // MISO
        pi_pad_function_set(PI_PAD_033, PI_PAD_FUNC0); // SCK

        /* open SPI interface */
        struct pi_spi_conf conf;

        pi_spi_conf_init(&conf);
        conf.wordsize = PI_SPI_WORDSIZE_8;
        conf.big_endian = 1;
        conf.max_baudrate = baudrate;
        conf.polarity = polarity;
        conf.phase = phase;
        conf.itf = 1;
        conf.cs = 0; /* Mikroe connector SPI is enabled when CS = 0 */

        pi_open_from_conf(&spi, &conf);

        if (pi_spi_open(&spi))
        {
            printf("Failed to open SPI\n");
            return -1;
        }

        /* Enable support for Mikroe */
        enable_3v3_periph();

        module_initialized = 1;
    }
    

    return 0;
}

void spi_transfer(uint8_t *tx_buffer_local, uint8_t *rx_buffer_local, int trx_size)
{
    pi_spi_transfer(&spi, tx_buffer_local, rx_buffer_local, trx_size * 8, 0);
}

void spi_send(uint8_t *tx_buffer_local, int tx_size)
{
    pi_spi_send(&spi, tx_buffer_local, tx_size * 8, 0);
}

void spi_receive( uint8_t *rx_buffer_local, int rx_size)
{
    pi_spi_receive(&spi, rx_buffer_local, rx_size * 8, 0);
}


void spi_cs_high()
{
    pi_gpio_pin_write(PAD_GPIO_CS_CUSTOM, 1);
}

void spi_cs_low()
{
    pi_gpio_pin_write(PAD_GPIO_CS_CUSTOM, 0);
}

void spi_change_baudrate(int baudrate)
{

    pi_spi_ioctl(&spi, PI_SPI_CTRL_SET_MAX_BAUDRATE, &spi_slave_conf);	

}
/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Hanna Müller, Vlad Niculescu
 */

#include "pmsis.h"

static pi_device_t gpio_cf;

void gpio_init() {

    /* set pad to gpio mode */
    pi_pad_function_set(PI_PAD_060, PI_PAD_FUNC1);

    /* configure gpio output */
    pi_gpio_flags_e flags = PI_GPIO_OUTPUT;
    pi_gpio_pin_configure(PI_PAD_060, flags);

    pi_gpio_pin_write(PI_PAD_060, 0);
}

void set_cf_gpio(int8_t value) {
	pi_gpio_pin_write(PI_PAD_060, value);
}
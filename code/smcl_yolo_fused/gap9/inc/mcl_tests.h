/* 
 * Copyright (C) 2023 ETH Zurich
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the GPL-3.0 license.  See the LICENSE file for details.
 *
 * Authors: Nicky Zimmerman
 */

#ifndef __MCL_TESTS_H__
#define __MCL_TESTS_H__

#include "pmsis.h"
#include <stdlib.h>
#include <time.h>
#include "MCL_utils.h"
#include "MCL_config.h"
#include "SPI_config.h"
#include "MCL_types.h"
#include "stdint.h"
#include "math.h"

int test_odom(vec3f odom);


int test_line_scan();

int test_grid_scan();

int test_edt();

//int test_map1();

int test_random();


#endif
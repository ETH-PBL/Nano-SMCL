#ifndef __best_float32_H__
#define __best_float32_H__

#define __PREFIX(x) best_float32 ## x
// Include basic GAP builtins defined in the Autotiler
#include "at_api.h"

#ifdef __EMUL__
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/param.h>
#include <string.h>
#endif

extern AT_DEFAULTFLASH_EXT_ADDR_TYPE best_float32_L3_Flash;

int test_best_float32(void);

#endif
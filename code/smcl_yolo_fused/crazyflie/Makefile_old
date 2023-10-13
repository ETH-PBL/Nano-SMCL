
# enable app support
APP=1
APP_STACKSIZE=3000

VPATH += src/
PROJ_OBJ += test_tof.o
PROJ_OBJ += vl53l5cx_api.o
PROJ_OBJ += ToFplatform.o
PROJ_OBJ += I2C_expander.o

INCLUDES += -Isrc

CRAZYFLIE_BASE=../../tii/crazyflie-firmware
include $(CRAZYFLIE_BASE)/Makefile
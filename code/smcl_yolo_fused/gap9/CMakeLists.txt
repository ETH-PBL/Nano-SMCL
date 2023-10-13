cmake_minimum_required(VERSION 3.16)


###############################################################################
# Application related definitions
###############################################################################

if (CONFIG_MODEL_EMUL)
  set(TARGET_NAME         best_float32_emul)
else()
  set(TARGET_NAME         best_float32)
endif()
set(MAIN                best_float32.c)
set(MODEL_EXPRESSIONS   ${CMAKE_CURRENT_SOURCE_DIR}/./Expression_Kernels.c)
set(AT_MODEL_PATH       ${CMAKE_CURRENT_SOURCE_DIR}/./model.c)
set(AT_TENSORS_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/./weights_tensors)
set(SEQUENCE                S4)

###############################################################################
# CMake pre initialization
###############################################################################

include($ENV{GAP_SDK_HOME}/utils/cmake/setup.cmake)

###############################################################################
# Autotiler Variables
###############################################################################

autotiler_define_gen_names(${TARGET_NAME})
autotiler_setup(${TARGET_NAME})

###############################################################################
# Application dependencies
###############################################################################

list(APPEND TARGET_SRCS 
                        ${CNN_LIB}
                        ${CONFIG_MODEL_BUILDDIR}/${KERNEL_C}
                        ${MODEL_EXPRESSIONS}
                        MCL_utils.c
                        smcl.c
                        gpio_config.c
                        spi_cmds_decode.c
                        spi_driver.c
)

list(APPEND TARGET_INCS -I.
                        -I${TILER_INC}
                        -I${TILER_EMU_INC}
                        -I$ENV{GAP_SDK_HOME}/libs/gap_lib/include
                        -I$ENV{GAP_SDK_HOME}/utils/power_meas_utils
                          ${CNN_LIB_INCLUDE}
                        -I${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_MODEL_BUILDDIR}
                        -I${CMAKE_CURRENT_SOURCE_DIR}
                        -I${CMAKE_CURRENT_SOURCE_DIR}/.
                        -I${CMAKE_CURRENT_SOURCE_DIR}/inc
                        -I${CMAKE_CURRENT_SOURCE_DIR}/data
                        -I${CMAKE_CURRENT_SOURCE_DIR}/data/${SEQUENCE})

if (CONFIG_MODEL_EMUL)
list(REMOVE_ITEM TARGET_CFLAGS
  -mno-memcpy)
list(APPEND TARGET_CFLAGS
  -g
  -m32
  -O0
  -fcommon
  -D__EMUL__)
else()
list(APPEND TARGET_CFLAGS   -O3)
endif()

set(FREQ_CL 370)
set(FREQ_FC 370)
set(FREQ_PE 360)

message(STATUS "Clock speeds - Cluster ${FREQ_CL} FC ${FREQ_FC} Peripheral ${FREQ_PE}")
# math(EXPR FREQ_CL ${CONFIG_FREQUENCY_CLUSTER}/1000000 OUTPUT_FORMAT DECIMAL)
# math(EXPR FREQ_FC ${CONFIG_FREQUENCY_FC}/1000000 OUTPUT_FORMAT DECIMAL)
# math(EXPR FREQ_PE ${CONFIG_FREQUENCY_PERIPH}/1000000 OUTPUT_FORMAT DECIMAL)

list(APPEND TARGET_PREPROCESSOR -DPERF
                                -DAT_MODEL_PREFIX=${MODEL_PREFIX}
                                -DSTACK_SIZE=${CONFIG_CL_MASTER_CORE_STACK_SIZE}
                                -DSLAVE_STACK_SIZE=${CONFIG_CL_SLAVE_CORE_STACK_SIZE}
                                -DFREQ_CL=${FREQ_CL}
                                -DFREQ_FC=${FREQ_FC}
                                -DFREQ_PE=${FREQ_PE}
                                

                                
)

project(${TARGET_NAME} C ASM)

add_executable(${TARGET_NAME} ${TARGET_SRCS})
target_link_libraries(${TARGET_NAME} PUBLIC m)

if (CONFIG_MODEL_EMUL)
find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set(CMAKE_C_COMPILER_LAUNCHER   ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()
set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
if (NOT CONFIG_MODEL_HAS_NO_CONSTANTS)
  add_custom_command(TARGET ${TARGET_NAME}
    COMMENT "Copy tensors to build directory"
    POST_BUILD
    COMMAND cp ${MODEL_TENSORS} ${CMAKE_CURRENT_BINARY_DIR}
  )
endif()
add_custom_target(run ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME})
endif()

target_compile_options(${TARGET_NAME} PUBLIC   ${TARGET_CFLAGS}
                                                ${TARGET_INCS}
                                                ${TARGET_PREPROCESSOR})

###############################################################################
# CMake post initialization
###############################################################################
if (NOT CONFIG_MODEL_EMUL)
  setupos(${TARGET_NAME})
endif ()
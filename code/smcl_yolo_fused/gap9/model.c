#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators_SQ8.h"
#include "CNN_Generators_NE16.h"
#include "ResizeGenerator.h"

#include "CNN_Copy_Generators.h"

void load_expressions_kernels() {
    LibKernelTemplate(
        "s18_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_0_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_0_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_0_out_0")
        )
    );
    
    LibKernel(
        "s18_kernel",
        CALL_PARALLEL,
        0,
        "s18_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s255_kernel_args_t",
        CArgs(7,
            TCArg("unsigned int", "I0"),
            TCArg("signed char *__restrict__ ", "expr_1_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_1_in_1"),
            TCArg("signed char *__restrict__ ", "expr_1_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_1_in_3"),
            TCArg("signed char *__restrict__ ", "expr_1_out_0"),
            TCArg("signed char *__restrict__ ", "expr_1_out_1")
        )
    );
    
    LibKernel(
        "s255_kernel",
        CALL_PARALLEL,
        0,
        "s255_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s37_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_2_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_2_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_2_out_0")
        )
    );
    
    LibKernel(
        "s37_kernel",
        CALL_PARALLEL,
        0,
        "s37_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s56_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_3_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_3_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_3_out_0")
        )
    );
    
    LibKernel(
        "s56_kernel",
        CALL_PARALLEL,
        0,
        "s56_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s75_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_4_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_4_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_4_out_0")
        )
    );
    
    LibKernel(
        "s75_kernel",
        CALL_PARALLEL,
        0,
        "s75_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s257_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("signed char *__restrict__ ", "expr_64_in_0"),
            TCArg("signed char *__restrict__ ", "expr_64_in_1"),
            TCArg("signed char *__restrict__ ", "expr_64_out_0")
        )
    );
    
    LibKernel(
        "s257_kernel",
        CALL_PARALLEL,
        0,
        "s257_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "expr_44_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_44_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_44_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_44",
        CALL_PARALLEL,
        0,
        "expr_44_args_t",
        0
    );
    LibKernelTemplate(
        "expr_55_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_55_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_55_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_55",
        CALL_PARALLEL,
        0,
        "expr_55_args_t",
        0
    );
    LibKernelTemplate(
        "expr_13_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_13_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_13_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_13",
        CALL_PARALLEL,
        0,
        "expr_13_args_t",
        0
    );
    LibKernelTemplate(
        "expr_23_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_23_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_23_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_23",
        CALL_PARALLEL,
        0,
        "expr_23_args_t",
        0
    );
    LibKernelTemplate(
        "expr_42_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_42_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_42_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_42",
        CALL_PARALLEL,
        0,
        "expr_42_args_t",
        0
    );
    LibKernelTemplate(
        "expr_43_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_43_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_43_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_43",
        CALL_PARALLEL,
        0,
        "expr_43_args_t",
        0
    );
    LibKernelTemplate(
        "expr_45_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_45_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_45_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_45",
        CALL_PARALLEL,
        0,
        "expr_45_args_t",
        0
    );
    LibKernelTemplate(
        "expr_46_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_46_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_46_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_46",
        CALL_PARALLEL,
        0,
        "expr_46_args_t",
        0
    );
    LibKernelTemplate(
        "expr_48_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_48_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_48_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_48",
        CALL_PARALLEL,
        0,
        "expr_48_args_t",
        0
    );
    LibKernelTemplate(
        "expr_49_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_49_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_49_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_49",
        CALL_PARALLEL,
        0,
        "expr_49_args_t",
        0
    );
    LibKernelTemplate(
        "expr_50_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_50_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_50_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_50",
        CALL_PARALLEL,
        0,
        "expr_50_args_t",
        0
    );
    LibKernelTemplate(
        "expr_51_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_51_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_51_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_51",
        CALL_PARALLEL,
        0,
        "expr_51_args_t",
        0
    );
    LibKernelTemplate(
        "expr_53_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_53_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_53_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_53",
        CALL_PARALLEL,
        0,
        "expr_53_args_t",
        0
    );
    LibKernelTemplate(
        "expr_54_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_54_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_54_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_54",
        CALL_PARALLEL,
        0,
        "expr_54_args_t",
        0
    );
    LibKernelTemplate(
        "expr_56_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_56_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_56_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_56",
        CALL_PARALLEL,
        0,
        "expr_56_args_t",
        0
    );
    LibKernelTemplate(
        "expr_57_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_57_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_57_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_57",
        CALL_PARALLEL,
        0,
        "expr_57_args_t",
        0
    );
    LibKernelTemplate(
        "expr_59_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_59_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_59_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_59",
        CALL_PARALLEL,
        0,
        "expr_59_args_t",
        0
    );
    LibKernelTemplate(
        "expr_60_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_60_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_60_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_60",
        CALL_PARALLEL,
        0,
        "expr_60_args_t",
        0
    );
    LibKernelTemplate(
        "expr_61_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_61_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_61_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_61",
        CALL_PARALLEL,
        0,
        "expr_61_args_t",
        0
    );
    LibKernelTemplate(
        "expr_62_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_62_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_62_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_62",
        CALL_PARALLEL,
        0,
        "expr_62_args_t",
        0
    );
    LibKernelTemplate(
        "expr_5_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_5_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_5_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_5",
        CALL_PARALLEL,
        0,
        "expr_5_args_t",
        0
    );
    LibKernelTemplate(
        "expr_6_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_6_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_6_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_6",
        CALL_PARALLEL,
        0,
        "expr_6_args_t",
        0
    );
    LibKernelTemplate(
        "expr_7_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_7_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_7_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_7",
        CALL_PARALLEL,
        0,
        "expr_7_args_t",
        0
    );
    LibKernelTemplate(
        "expr_9_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_9_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_9_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_9",
        CALL_PARALLEL,
        0,
        "expr_9_args_t",
        0
    );
    LibKernelTemplate(
        "expr_10_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_10_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_10_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_10",
        CALL_PARALLEL,
        0,
        "expr_10_args_t",
        0
    );
    LibKernelTemplate(
        "expr_11_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_11_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_11_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_11",
        CALL_PARALLEL,
        0,
        "expr_11_args_t",
        0
    );
    LibKernelTemplate(
        "expr_12_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_12_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_12_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_12",
        CALL_PARALLEL,
        0,
        "expr_12_args_t",
        0
    );
    LibKernelTemplate(
        "expr_14_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_14_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_14_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_14",
        CALL_PARALLEL,
        0,
        "expr_14_args_t",
        0
    );
    LibKernelTemplate(
        "expr_16_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_16_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_16_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_16",
        CALL_PARALLEL,
        0,
        "expr_16_args_t",
        0
    );
    LibKernelTemplate(
        "expr_17_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_17_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_17_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_17",
        CALL_PARALLEL,
        0,
        "expr_17_args_t",
        0
    );
    LibKernelTemplate(
        "expr_18_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_18_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_18_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_18",
        CALL_PARALLEL,
        0,
        "expr_18_args_t",
        0
    );
    LibKernelTemplate(
        "expr_19_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_19_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_19_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_19",
        CALL_PARALLEL,
        0,
        "expr_19_args_t",
        0
    );
    LibKernelTemplate(
        "expr_20_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_20_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_20_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_20",
        CALL_PARALLEL,
        0,
        "expr_20_args_t",
        0
    );
    LibKernelTemplate(
        "expr_21_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_21_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_21_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_21",
        CALL_PARALLEL,
        0,
        "expr_21_args_t",
        0
    );
    LibKernelTemplate(
        "expr_22_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_22_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_22_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_22",
        CALL_PARALLEL,
        0,
        "expr_22_args_t",
        0
    );
    LibKernelTemplate(
        "expr_25_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_25_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_25_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_25",
        CALL_PARALLEL,
        0,
        "expr_25_args_t",
        0
    );
    LibKernelTemplate(
        "expr_26_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_26_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_26_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_26",
        CALL_PARALLEL,
        0,
        "expr_26_args_t",
        0
    );
    LibKernelTemplate(
        "expr_27_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_27_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_27_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_27",
        CALL_PARALLEL,
        0,
        "expr_27_args_t",
        0
    );
    LibKernelTemplate(
        "expr_28_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_28_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_28_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_28",
        CALL_PARALLEL,
        0,
        "expr_28_args_t",
        0
    );
    LibKernelTemplate(
        "expr_29_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_29_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_29_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_29",
        CALL_PARALLEL,
        0,
        "expr_29_args_t",
        0
    );
    LibKernelTemplate(
        "expr_30_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_30_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_30_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_30",
        CALL_PARALLEL,
        0,
        "expr_30_args_t",
        0
    );
    LibKernelTemplate(
        "expr_31_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_31_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_31_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_31",
        CALL_PARALLEL,
        0,
        "expr_31_args_t",
        0
    );
    LibKernelTemplate(
        "expr_32_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_32_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_32_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_32",
        CALL_PARALLEL,
        0,
        "expr_32_args_t",
        0
    );
    LibKernelTemplate(
        "expr_33_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_33_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_33_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_33",
        CALL_PARALLEL,
        0,
        "expr_33_args_t",
        0
    );
    LibKernelTemplate(
        "expr_35_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_35_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_35_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_35",
        CALL_PARALLEL,
        0,
        "expr_35_args_t",
        0
    );
    LibKernelTemplate(
        "expr_36_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_36_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_36_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_36",
        CALL_PARALLEL,
        0,
        "expr_36_args_t",
        0
    );
    LibKernelTemplate(
        "expr_37_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_37_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_37_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_37",
        CALL_PARALLEL,
        0,
        "expr_37_args_t",
        0
    );
    LibKernelTemplate(
        "expr_38_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_38_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_38_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_38",
        CALL_PARALLEL,
        0,
        "expr_38_args_t",
        0
    );
    LibKernelTemplate(
        "expr_39_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_39_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_39_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_39",
        CALL_PARALLEL,
        0,
        "expr_39_args_t",
        0
    );
    LibKernelTemplate(
        "expr_40_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_40_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_40_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_40",
        CALL_PARALLEL,
        0,
        "expr_40_args_t",
        0
    );
    LibKernelTemplate(
        "expr_41_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_41_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_41_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_41",
        CALL_PARALLEL,
        0,
        "expr_41_args_t",
        0
    );
}



int s18_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (64, 64, 8) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (32768.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 32768, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_0_in_0"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_0_in_1"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_0_out_0"),
            TCArg(CNN_ArgDataTypeUns(2, 1, 1), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s18_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_0_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_0_in_0", KER_ARG_TILE),
                    K_Arg("expr_0_in_1", KER_ARG_TILE),
                    K_Arg("expr_0_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_0_out_0 axes: (0,)
        // var: expr_0_in_1 axes: (0,)
        // var: expr_0_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_0_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_0_out_0"),
            KerArg("expr_0_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_0_in_1"),
            KerArg("expr_0_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_0_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 98304, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 98560, 0);
        AddKernelArgDim(Name, "SigmoidLUTTable", 2, 256,       2);
        AddKernelArgDim(Name, "expr_0_in_0",     4, 64, 64, 8, 1);
        AddKernelArgDim(Name, "expr_0_in_1",     4, 64, 64, 8, 1);
        AddKernelArgDim(Name, "expr_0_out_0",    4, 64, 64, 8, 1);
    }
    return (Kernel!=0);
}
int s255_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (2, 1, 1344) spaces: ((0, 2),) 
        // parametric_spaces: ((0, 2),) 
        // exterior_shape: (2688.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 2688, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(6,
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_1_in_0"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_1_in_1"),
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_1_in_2"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_1_in_3"),
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_1_out_0"),
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_1_out_1")
        ),
        Calls(1,
            Call("s255_kernel", LOC_D0,
                Bindings(7,
                    K_ArgPar("expr_1_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("expr_1_in_0", KER_ARG_TILE),
                    K_Arg("expr_1_in_1", KER_ARG_TILE),
                    K_Arg("expr_1_in_2", KER_ARG_TILE),
                    K_Arg("expr_1_in_3", KER_ARG_TILE),
                    K_Arg("expr_1_out_0", KER_ARG_TILE),
                    K_Arg("expr_1_out_1", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_1_in_0 axes: (0,)
        // var: expr_1_in_1 axes: (0,)
        // var: expr_1_in_3 axes: (0,)
        // var: expr_1_in_2 axes: (0,)
        // var: expr_1_out_0 axes: (0,)
        // var: expr_1_out_1 axes: (0,)
        KerArgs(6,
            KerArg("expr_1_in_0",  KerArgSpace(1, KER_ITER_D0), O_IN|O_DB,  1, 1, 1, 0, 0, 0, "expr_1_in_0"),
            KerArg("expr_1_in_1",  KerArgSpace(1, KER_ITER_D0), O_IN|O_DB,  1, 1, 1, 0, 0, 0, "expr_1_in_1"),
            KerArg("expr_1_in_3",  KerArgSpace(1, KER_ITER_D0), O_IN|O_DB,  1, 1, 1, 0, 0, 0, "expr_1_in_3"),
            KerArg("expr_1_in_2",  KerArgSpace(1, KER_ITER_D0), O_IN|O_DB,  1, 1, 1, 0, 0, 0, "expr_1_in_2"),
            KerArg("expr_1_out_0", KerArgSpace(1, KER_ITER_D0), O_OUT|O_DB, 1, 1, 1, 0, 0, 0, "expr_1_out_0"),
            KerArg("expr_1_out_1", KerArgSpace(1, KER_ITER_D0), O_OUT|O_DB, 1, 1, 1, 0, 0, 0, "expr_1_out_1")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 26880, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 16128, 0);
        AddKernelArgDim(Name, "expr_1_in_0",  4, 2, 1, 1344, 1);
        AddKernelArgDim(Name, "expr_1_in_1",  4, 2, 1, 1344, 1);
        AddKernelArgDim(Name, "expr_1_in_2",  4, 2, 1, 1344, 1);
        AddKernelArgDim(Name, "expr_1_in_3",  4, 2, 1, 1344, 1);
        AddKernelArgDim(Name, "expr_1_out_0", 4, 2, 1, 1344, 1);
        AddKernelArgDim(Name, "expr_1_out_1", 4, 2, 1, 1344, 1);
    }
    return (Kernel!=0);
}
int s37_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (32, 32, 16) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (16384.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 16384, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_2_in_0"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_2_in_1"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_2_out_0"),
            TCArg(CNN_ArgDataTypeUns(2, 1, 1), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s37_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_2_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_2_in_0", KER_ARG_TILE),
                    K_Arg("expr_2_in_1", KER_ARG_TILE),
                    K_Arg("expr_2_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_2_out_0 axes: (0,)
        // var: expr_2_in_1 axes: (0,)
        // var: expr_2_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_2_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_2_out_0"),
            KerArg("expr_2_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_2_in_1"),
            KerArg("expr_2_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_2_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 49152, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 49408, 0);
        AddKernelArgDim(Name, "SigmoidLUTTable", 2, 256,        2);
        AddKernelArgDim(Name, "expr_2_in_0",     4, 32, 32, 16, 1);
        AddKernelArgDim(Name, "expr_2_in_1",     4, 32, 32, 16, 1);
        AddKernelArgDim(Name, "expr_2_out_0",    4, 32, 32, 16, 1);
    }
    return (Kernel!=0);
}
int s56_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (16, 16, 28) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (7168.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 7168, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_3_in_0"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_3_in_1"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_3_out_0"),
            TCArg(CNN_ArgDataTypeUns(2, 1, 1), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s56_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_3_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_3_in_0", KER_ARG_TILE),
                    K_Arg("expr_3_in_1", KER_ARG_TILE),
                    K_Arg("expr_3_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_3_out_0 axes: (0,)
        // var: expr_3_in_1 axes: (0,)
        // var: expr_3_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_3_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_3_out_0"),
            KerArg("expr_3_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_3_in_1"),
            KerArg("expr_3_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_3_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 21504, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 21760, 0);
        AddKernelArgDim(Name, "SigmoidLUTTable", 2, 256,        2);
        AddKernelArgDim(Name, "expr_3_in_0",     4, 16, 16, 28, 1);
        AddKernelArgDim(Name, "expr_3_in_1",     4, 16, 16, 28, 1);
        AddKernelArgDim(Name, "expr_3_out_0",    4, 16, 16, 28, 1);
    }
    return (Kernel!=0);
}
int s75_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (8, 8, 52) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (3328.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 3328, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_4_in_0"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_4_in_1"),
            TCArg(CNN_ArgDataTypeUns(1, 1, 1), "expr_4_out_0"),
            TCArg(CNN_ArgDataTypeUns(2, 1, 1), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s75_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_4_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_4_in_0", KER_ARG_TILE),
                    K_Arg("expr_4_in_1", KER_ARG_TILE),
                    K_Arg("expr_4_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_4_out_0 axes: (0,)
        // var: expr_4_in_1 axes: (0,)
        // var: expr_4_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_4_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_4_out_0"),
            KerArg("expr_4_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_4_in_1"),
            KerArg("expr_4_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_4_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 9984, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 10240, 0);
        AddKernelArgDim(Name, "SigmoidLUTTable", 2, 256,      2);
        AddKernelArgDim(Name, "expr_4_in_0",     4, 8, 8, 52, 1);
        AddKernelArgDim(Name, "expr_4_in_1",     4, 8, 8, 52, 1);
        AddKernelArgDim(Name, "expr_4_out_0",    4, 8, 8, 52, 1);
    }
    return (Kernel!=0);
}
int s257_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (4, 1, 1344) spaces: ((0,), (2,)) 
        // parametric_spaces: ((0,), (2,)) 
        // exterior_shape: (4, 1344.0) 
        KernelIterSpace(3, IterParSpace(KER_ITER_D0, 4, 1), IterParSpace(KER_ITER_D1, 1344, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(3,
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_64_in_0"),
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_64_in_1"),
            TCArg(CNN_ArgDataType(1, 1, 1), "expr_64_out_0")
        ),
        Calls(1,
            Call("s257_kernel", LOC_D1,
                Bindings(5,
                    K_ArgPar("expr_64_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_64_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_Arg("expr_64_in_0", KER_ARG_TILE),
                    K_Arg("expr_64_in_1", KER_ARG_TILE),
                    K_Arg("expr_64_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_64_out_0 axes: (0, 1)
        // var: expr_64_in_1 axes: (0, 1)
        // var: expr_64_in_0 axes: (1,)
        KerArgs(3,
            KerArg("expr_64_out_0", KerArgSpace(2, KER_ITER_D0, KER_ITER_D1), O_OUT|O_DB, 1, 1, 1, 0, 0, 0, "expr_64_out_0"),
            KerArg("expr_64_in_1",  KerArgSpace(2, KER_ITER_D0, KER_ITER_D1), O_IN|O_DB,  1, 1, 1, 0, 0, 0, "expr_64_in_1"),
            KerArg("expr_64_in_0",  KerArgSpace(1, KER_ITER_D1),              O_IN|O_DB,  1, 1, 1, 0, 0, 0, "expr_64_in_0")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 5376, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 12096, 0);
        AddKernelArgDim(Name, "expr_64_in_0",  2, 1344,       1);
        AddKernelArgDim(Name, "expr_64_in_1",  4, 4, 1, 1344, 1);
        AddKernelArgDim(Name, "expr_64_out_0", 4, 4, 1, 1344, 1);
    }
    return (Kernel!=0);
}

void best_float32Model(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 7, "at_api.h", "best_float32.h", "CNN_BasicKernels_SQ8.h", "CNN_BasicKernels_NE16.h", "ResizeBasicKernels.h", "CNN_BasicKernels_SQ8.h", "Expression_Kernels.h");
    SetGeneratedFilesNames("best_float32Kernels.c", "best_float32Kernels.h");
    AT_SetGraphCtrl(AT_GRAPH_MONITOR_CYCLES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_NODE_NAMES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_OPERINFOS, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_ASYNC_FORK, AT_OPT_ON);

    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "best_float32_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "best_float32_L2_Memory", 0, 1,
        AT_MEM_L3_DEFAULTRAM, L3Memory, "best_float32_L3_Memory", 0, 0,
        AT_MEM_L3_DEFAULTFLASH, L3Flash, "best_float32_L3_Flash", "best_float32_L3_Flash_Const.dat", 0
    );

    LoadCNN_SQ8_Library();
    LoadCNN_NE16_SQ8_Library();
    LoadResizeLibrary();
    LoadCNN_Copy_Library();
    load_expressions_kernels();

    CNN_GenControl_T gen_ctrl_S3_CONV_2D_0_1_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "CUSTOM_ACTIVATION_NAME", "expr_44");
    CNN_ExtraActivationArgs_T gen_ctrl_S3_CONV_2D_0_1_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S3_CONV_2D_0_1_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_1_fusion
    CNN_ConvolutionNE16("S3_CONV_2D_0_1_fusion", &gen_ctrl_S3_CONV_2D_0_1_fusion,
                        -1, -1, 4, 1, 8,
                        3, 8, 256, 256,
                        KOP_CONV, 6, 6, 1, 1, 2, 2, 1, 0,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S6_CONV_2D_0_5_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "CUSTOM_ACTIVATION_NAME", "expr_55");
    CNN_ExtraActivationArgs_T gen_ctrl_S6_CONV_2D_0_5_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S6_CONV_2D_0_5_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_5_fusion
    CNN_ConvolutionNE16("S6_CONV_2D_0_5_fusion", &gen_ctrl_S6_CONV_2D_0_5_fusion,
                        -1, -1, 4, 1, 8,
                        8, 16, 128, 128,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 8,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S9_CONV_2D_0_8_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "CUSTOM_ACTIVATION_NAME", "expr_13");
    CNN_ExtraActivationArgs_T gen_ctrl_S9_CONV_2D_0_8_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S9_CONV_2D_0_8_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_8_fusion
    CNN_ConvolutionNE16("S9_CONV_2D_0_8_fusion", &gen_ctrl_S9_CONV_2D_0_8_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 64, 64,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 7,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_8_split
    CNN_SplitLastAxis_Generator("S10_CONV_2D_0_8_split", 0, -1, 4096, 8, 8, 0, 0, KOP_SPLIT);
    
    
    // generator for CONCAT_0_21_qin1
    CNN_Convert("S11_CONCAT_0_21_qin1", -1, -1, 32768, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S14_CONV_2D_0_14_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "CUSTOM_ACTIVATION_NAME", "expr_23");
    CNN_ExtraActivationArgs_T gen_ctrl_S14_CONV_2D_0_14_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S14_CONV_2D_0_14_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_14_fusion
    CNN_ConvolutionNE16("S14_CONV_2D_0_14_fusion", &gen_ctrl_S14_CONV_2D_0_14_fusion,
                        -1, -1, 4, 1, 8,
                        8, 8, 64, 64,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 6,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S17_CONV_2D_0_17;
    CNN_InitGenCtrl(&gen_ctrl_S17_CONV_2D_0_17);
    CNN_SetGenCtrl(&gen_ctrl_S17_CONV_2D_0_17, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S17_CONV_2D_0_17, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_17
    CNN_ConvolutionNE16("S17_CONV_2D_0_17", &gen_ctrl_S17_CONV_2D_0_17,
                        -1, -1, 4, 1, 8,
                        8, 8, 64, 64,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_0
    s18_kernel_gen("S18_expr_0");
    
    
    // generator for CONCAT_0_21
    CNN_ConcatLastAxis_Generator("S19_CONCAT_0_21", 0, -1, 4096, 8, 8, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S22_CONV_2D_0_22_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "CUSTOM_ACTIVATION_NAME", "expr_42");
    CNN_ExtraActivationArgs_T gen_ctrl_S22_CONV_2D_0_22_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S22_CONV_2D_0_22_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_22_fusion
    CNN_ConvolutionNE16("S22_CONV_2D_0_22_fusion", &gen_ctrl_S22_CONV_2D_0_22_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 64, 64,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S25_CONV_2D_0_26_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "CUSTOM_ACTIVATION_NAME", "expr_43");
    CNN_ExtraActivationArgs_T gen_ctrl_S25_CONV_2D_0_26_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S25_CONV_2D_0_26_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_26_fusion
    CNN_ConvolutionNE16("S25_CONV_2D_0_26_fusion", &gen_ctrl_S25_CONV_2D_0_26_fusion,
                        -1, -1, 4, 1, 8,
                        16, 32, 64, 64,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 8,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S28_CONV_2D_0_29_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "CUSTOM_ACTIVATION_NAME", "expr_45");
    CNN_ExtraActivationArgs_T gen_ctrl_S28_CONV_2D_0_29_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S28_CONV_2D_0_29_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_29_fusion
    CNN_ConvolutionNE16("S28_CONV_2D_0_29_fusion", &gen_ctrl_S28_CONV_2D_0_29_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_29_split
    CNN_SplitLastAxis_Generator("S29_CONV_2D_0_29_split", 0, -1, 1024, 16, 16, 0, 0, KOP_SPLIT);
    
    
    // generator for CONCAT_0_42_qin1
    CNN_Convert("S30_CONCAT_0_42_qin1", -1, -1, 16384, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S33_CONV_2D_0_32_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "CUSTOM_ACTIVATION_NAME", "expr_46");
    CNN_ExtraActivationArgs_T gen_ctrl_S33_CONV_2D_0_32_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S33_CONV_2D_0_32_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_32_fusion
    CNN_ConvolutionNE16("S33_CONV_2D_0_32_fusion", &gen_ctrl_S33_CONV_2D_0_32_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S36_CONV_2D_0_35;
    CNN_InitGenCtrl(&gen_ctrl_S36_CONV_2D_0_35);
    CNN_SetGenCtrl(&gen_ctrl_S36_CONV_2D_0_35, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S36_CONV_2D_0_35, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_35
    CNN_ConvolutionNE16("S36_CONV_2D_0_35", &gen_ctrl_S36_CONV_2D_0_35,
                        -1, -1, 4, 1, 8,
                        16, 16, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_2
    s37_kernel_gen("S37_expr_2");
    
    
    // generator for CONCAT_0_42
    CNN_ConcatLastAxis_Generator("S38_CONCAT_0_42", 0, -1, 1024, 16, 16, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S41_CONV_2D_0_43_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "CUSTOM_ACTIVATION_NAME", "expr_48");
    CNN_ExtraActivationArgs_T gen_ctrl_S41_CONV_2D_0_43_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S41_CONV_2D_0_43_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_43_fusion
    CNN_ConvolutionNE16("S41_CONV_2D_0_43_fusion", &gen_ctrl_S41_CONV_2D_0_43_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 16,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S44_CONV_2D_0_47_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "CUSTOM_ACTIVATION_NAME", "expr_49");
    CNN_ExtraActivationArgs_T gen_ctrl_S44_CONV_2D_0_47_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S44_CONV_2D_0_47_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_47_fusion
    CNN_ConvolutionNE16("S44_CONV_2D_0_47_fusion", &gen_ctrl_S44_CONV_2D_0_47_fusion,
                        -1, -1, 4, 1, 8,
                        32, 56, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S47_CONV_2D_0_50_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "CUSTOM_ACTIVATION_NAME", "expr_50");
    CNN_ExtraActivationArgs_T gen_ctrl_S47_CONV_2D_0_50_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S47_CONV_2D_0_50_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_50_fusion
    CNN_ConvolutionNE16("S47_CONV_2D_0_50_fusion", &gen_ctrl_S47_CONV_2D_0_50_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 15,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_50_split
    CNN_SplitLastAxis_Generator("S48_CONV_2D_0_50_split", 0, -1, 256, 28, 28, 0, 0, KOP_SPLIT);
    
    
    // generator for CONCAT_0_63_qin1
    CNN_Convert("S49_CONCAT_0_63_qin1", -1, -1, 7168, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S52_CONV_2D_0_53_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "CUSTOM_ACTIVATION_NAME", "expr_51");
    CNN_ExtraActivationArgs_T gen_ctrl_S52_CONV_2D_0_53_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S52_CONV_2D_0_53_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_53_fusion
    CNN_ConvolutionNE16("S52_CONV_2D_0_53_fusion", &gen_ctrl_S52_CONV_2D_0_53_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 15,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S55_CONV_2D_0_56;
    CNN_InitGenCtrl(&gen_ctrl_S55_CONV_2D_0_56);
    CNN_SetGenCtrl(&gen_ctrl_S55_CONV_2D_0_56, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S55_CONV_2D_0_56, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_56
    CNN_ConvolutionNE16("S55_CONV_2D_0_56", &gen_ctrl_S55_CONV_2D_0_56,
                        -1, -1, 4, 1, 8,
                        28, 28, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_3
    s56_kernel_gen("S56_expr_3");
    
    
    // generator for CONCAT_0_63
    CNN_ConcatLastAxis_Generator("S57_CONCAT_0_63", 0, -1, 256, 28, 28, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S60_CONV_2D_0_64_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "CUSTOM_ACTIVATION_NAME", "expr_53");
    CNN_ExtraActivationArgs_T gen_ctrl_S60_CONV_2D_0_64_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S60_CONV_2D_0_64_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_64_fusion
    CNN_ConvolutionNE16("S60_CONV_2D_0_64_fusion", &gen_ctrl_S60_CONV_2D_0_64_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 16,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S63_CONV_2D_0_68_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S63_CONV_2D_0_68_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S63_CONV_2D_0_68_fusion, "CUSTOM_ACTIVATION_NAME", "expr_54");
    CNN_ExtraActivationArgs_T gen_ctrl_S63_CONV_2D_0_68_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S63_CONV_2D_0_68_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S63_CONV_2D_0_68_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S63_CONV_2D_0_68_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S63_CONV_2D_0_68_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_68_fusion
    CNN_ConvolutionNE16("S63_CONV_2D_0_68_fusion", &gen_ctrl_S63_CONV_2D_0_68_fusion,
                        -1, -1, 4, 1, 8,
                        56, 104, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S66_CONV_2D_0_71_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S66_CONV_2D_0_71_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S66_CONV_2D_0_71_fusion, "CUSTOM_ACTIVATION_NAME", "expr_56");
    CNN_ExtraActivationArgs_T gen_ctrl_S66_CONV_2D_0_71_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S66_CONV_2D_0_71_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S66_CONV_2D_0_71_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S66_CONV_2D_0_71_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S66_CONV_2D_0_71_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_71_fusion
    CNN_ConvolutionNE16("S66_CONV_2D_0_71_fusion", &gen_ctrl_S66_CONV_2D_0_71_fusion,
                        -1, -1, 4, 1, 8,
                        104, 104, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_71_split
    CNN_SplitLastAxis_Generator("S67_CONV_2D_0_71_split", 0, -1, 64, 52, 52, 0, 0, KOP_SPLIT);
    
    
    // generator for CONCAT_0_84_qin1
    CNN_Convert("S68_CONCAT_0_84_qin1", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S71_CONV_2D_0_74_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S71_CONV_2D_0_74_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S71_CONV_2D_0_74_fusion, "CUSTOM_ACTIVATION_NAME", "expr_57");
    CNN_ExtraActivationArgs_T gen_ctrl_S71_CONV_2D_0_74_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S71_CONV_2D_0_74_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S71_CONV_2D_0_74_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S71_CONV_2D_0_74_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S71_CONV_2D_0_74_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_74_fusion
    CNN_ConvolutionNE16("S71_CONV_2D_0_74_fusion", &gen_ctrl_S71_CONV_2D_0_74_fusion,
                        -1, -1, 4, 1, 8,
                        52, 52, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S74_CONV_2D_0_77;
    CNN_InitGenCtrl(&gen_ctrl_S74_CONV_2D_0_77);
    CNN_SetGenCtrl(&gen_ctrl_S74_CONV_2D_0_77, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S74_CONV_2D_0_77, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_77
    CNN_ConvolutionNE16("S74_CONV_2D_0_77", &gen_ctrl_S74_CONV_2D_0_77,
                        -1, -1, 4, 1, 8,
                        52, 52, 8, 8,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_4
    s75_kernel_gen("S75_expr_4");
    
    
    // generator for CONCAT_0_84
    CNN_ConcatLastAxis_Generator("S76_CONCAT_0_84", 0, -1, 64, 52, 52, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S79_CONV_2D_0_85_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S79_CONV_2D_0_85_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S79_CONV_2D_0_85_fusion, "CUSTOM_ACTIVATION_NAME", "expr_59");
    CNN_ExtraActivationArgs_T gen_ctrl_S79_CONV_2D_0_85_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S79_CONV_2D_0_85_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S79_CONV_2D_0_85_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S79_CONV_2D_0_85_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S79_CONV_2D_0_85_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_85_fusion
    CNN_ConvolutionNE16("S79_CONV_2D_0_85_fusion", &gen_ctrl_S79_CONV_2D_0_85_fusion,
                        -1, -1, 4, 1, 8,
                        104, 104, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 15,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S82_CONV_2D_0_88_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S82_CONV_2D_0_88_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S82_CONV_2D_0_88_fusion, "CUSTOM_ACTIVATION_NAME", "expr_60");
    CNN_ExtraActivationArgs_T gen_ctrl_S82_CONV_2D_0_88_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S82_CONV_2D_0_88_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S82_CONV_2D_0_88_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S82_CONV_2D_0_88_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S82_CONV_2D_0_88_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_88_fusion
    CNN_ConvolutionNE16("S82_CONV_2D_0_88_fusion", &gen_ctrl_S82_CONV_2D_0_88_fusion,
                        -1, -1, 4, 1, 8,
                        104, 52, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S83_MAX_POOL_2D_0_91;
    CNN_InitGenCtrl(&gen_ctrl_S83_MAX_POOL_2D_0_91);
    CNN_SetGenCtrl(&gen_ctrl_S83_MAX_POOL_2D_0_91, "HWC", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S83_MAX_POOL_2D_0_91, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S83_MAX_POOL_2D_0_91, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for MAX_POOL_2D_0_91
    CNN_PoolAct_SQ8("S83_MAX_POOL_2D_0_91", &gen_ctrl_S83_MAX_POOL_2D_0_91,
                    52, 8, 8,
                    KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                    KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S84_MAX_POOL_2D_0_92;
    CNN_InitGenCtrl(&gen_ctrl_S84_MAX_POOL_2D_0_92);
    CNN_SetGenCtrl(&gen_ctrl_S84_MAX_POOL_2D_0_92, "HWC", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S84_MAX_POOL_2D_0_92, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S84_MAX_POOL_2D_0_92, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for MAX_POOL_2D_0_92
    CNN_PoolAct_SQ8("S84_MAX_POOL_2D_0_92", &gen_ctrl_S84_MAX_POOL_2D_0_92,
                    52, 8, 8,
                    KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                    KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S85_MAX_POOL_2D_0_93;
    CNN_InitGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_93);
    CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_93, "HWC", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_93, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_93, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for MAX_POOL_2D_0_93
    CNN_PoolAct_SQ8("S85_MAX_POOL_2D_0_93", &gen_ctrl_S85_MAX_POOL_2D_0_93,
                    52, 8, 8,
                    KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                    KOP_NONE);
    
    
    // generator for CONCAT_0_94
    CNN_ConcatLastAxis_Generator("S86_CONCAT_0_94", 0, -1, 64, 52, 52, 52, 52, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S89_CONV_2D_0_95_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S89_CONV_2D_0_95_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S89_CONV_2D_0_95_fusion, "CUSTOM_ACTIVATION_NAME", "expr_61");
    CNN_ExtraActivationArgs_T gen_ctrl_S89_CONV_2D_0_95_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S89_CONV_2D_0_95_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S89_CONV_2D_0_95_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S89_CONV_2D_0_95_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S89_CONV_2D_0_95_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_95_fusion
    CNN_ConvolutionNE16("S89_CONV_2D_0_95_fusion", &gen_ctrl_S89_CONV_2D_0_95_fusion,
                        -1, -1, 4, 1, 8,
                        208, 104, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 128,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S92_CONV_2D_0_98_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S92_CONV_2D_0_98_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S92_CONV_2D_0_98_fusion, "CUSTOM_ACTIVATION_NAME", "expr_62");
    CNN_ExtraActivationArgs_T gen_ctrl_S92_CONV_2D_0_98_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S92_CONV_2D_0_98_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S92_CONV_2D_0_98_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S92_CONV_2D_0_98_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S92_CONV_2D_0_98_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_98_fusion
    CNN_ConvolutionNE16("S92_CONV_2D_0_98_fusion", &gen_ctrl_S92_CONV_2D_0_98_fusion,
                        -1, -1, 4, 1, 8,
                        104, 56, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for RESIZE_NN_0_101_qin0
    CNN_Convert("S93_RESIZE_NN_0_101_qin0", -1, -1, 3584, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for RESIZE_NN_0_101_trans_0 Transpose 8x8x56 -> 56x8x8 ((1, 0))
    CNN_MatTranspose("S94_RESIZE_NN_0_101_trans_0", 0, -1,
                      1, 56, 64, KOP_MATTRANSP);
    
    // generator for RESIZE_NN_0_101
    GenerateResizeMultiChannel("S95_RESIZE_NN_0_101", 0, 8, 8, 16, 16, 56, UNSIGNED_INOUT, KOP_NEAREST_NEIGHBOR_RESIZE);
    
    
    // generator for RESIZE_NN_0_101_trans Transpose 56x16x16 -> 16x16x56 ((1, 0))
    CNN_MatTranspose("S96_RESIZE_NN_0_101_trans", 0, -1,
                      1, 256, 56, KOP_MATTRANSP);
    
    
    // generator for CONCAT_0_102
    CNN_ConcatLastAxis_Generator("S97_CONCAT_0_102", 0, -1, 256, 56, 56, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S100_CONV_2D_0_103_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S100_CONV_2D_0_103_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S100_CONV_2D_0_103_fusion, "CUSTOM_ACTIVATION_NAME", "expr_5");
    CNN_ExtraActivationArgs_T gen_ctrl_S100_CONV_2D_0_103_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S100_CONV_2D_0_103_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S100_CONV_2D_0_103_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S100_CONV_2D_0_103_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S100_CONV_2D_0_103_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_103_fusion
    CNN_ConvolutionNE16("S100_CONV_2D_0_103_fusion", &gen_ctrl_S100_CONV_2D_0_103_fusion,
                        -1, -1, 4, 1, 8,
                        112, 56, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_103_split
    CNN_SplitLastAxis_Generator("S101_CONV_2D_0_103_split", 0, -1, 256, 28, 28, 0, 0, KOP_SPLIT);
    
    CNN_GenControl_T gen_ctrl_S104_CONV_2D_0_106_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S104_CONV_2D_0_106_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S104_CONV_2D_0_106_fusion, "CUSTOM_ACTIVATION_NAME", "expr_6");
    CNN_ExtraActivationArgs_T gen_ctrl_S104_CONV_2D_0_106_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S104_CONV_2D_0_106_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S104_CONV_2D_0_106_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S104_CONV_2D_0_106_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S104_CONV_2D_0_106_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_106_fusion
    CNN_ConvolutionNE16("S104_CONV_2D_0_106_fusion", &gen_ctrl_S104_CONV_2D_0_106_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S107_CONV_2D_0_109_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S107_CONV_2D_0_109_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_109_fusion, "CUSTOM_ACTIVATION_NAME", "expr_7");
    CNN_ExtraActivationArgs_T gen_ctrl_S107_CONV_2D_0_109_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_109_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S107_CONV_2D_0_109_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_109_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_109_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_109_fusion
    CNN_ConvolutionNE16("S107_CONV_2D_0_109_fusion", &gen_ctrl_S107_CONV_2D_0_109_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONCAT_0_115
    CNN_ConcatLastAxis_Generator("S108_CONCAT_0_115", 0, -1, 256, 28, 28, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S111_CONV_2D_0_116_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S111_CONV_2D_0_116_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S111_CONV_2D_0_116_fusion, "CUSTOM_ACTIVATION_NAME", "expr_9");
    CNN_ExtraActivationArgs_T gen_ctrl_S111_CONV_2D_0_116_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S111_CONV_2D_0_116_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S111_CONV_2D_0_116_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S111_CONV_2D_0_116_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S111_CONV_2D_0_116_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_116_fusion
    CNN_ConvolutionNE16("S111_CONV_2D_0_116_fusion", &gen_ctrl_S111_CONV_2D_0_116_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S114_CONV_2D_0_119_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S114_CONV_2D_0_119_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_119_fusion, "CUSTOM_ACTIVATION_NAME", "expr_10");
    CNN_ExtraActivationArgs_T gen_ctrl_S114_CONV_2D_0_119_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_119_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S114_CONV_2D_0_119_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_119_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_119_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_119_fusion
    CNN_ConvolutionNE16("S114_CONV_2D_0_119_fusion", &gen_ctrl_S114_CONV_2D_0_119_fusion,
                        -1, -1, 4, 1, 8,
                        56, 32, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for RESIZE_NN_0_122_qin0
    CNN_Convert("S115_RESIZE_NN_0_122_qin0", -1, -1, 8192, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for RESIZE_NN_0_122_trans Transpose 16x16x32 -> 32x16x16 ((1, 0))
    CNN_MatTranspose("S116_RESIZE_NN_0_122_trans", 0, -1,
                      1, 32, 256, KOP_MATTRANSP);
    
    // generator for RESIZE_NN_0_122
    GenerateResizeMultiChannel("S117_RESIZE_NN_0_122", 0, 16, 16, 32, 32, 32, UNSIGNED_INOUT, KOP_NEAREST_NEIGHBOR_RESIZE);
    
    
    // generator for RESIZE_NN_0_122_trans_0 Transpose 32x32x32 -> 32x32x32 ((1, 0))
    CNN_MatTranspose("S118_RESIZE_NN_0_122_trans_0", 0, -1,
                      1, 1024, 32, KOP_MATTRANSP);
    
    
    // generator for CONCAT_0_123
    CNN_ConcatLastAxis_Generator("S119_CONCAT_0_123", 0, -1, 1024, 32, 32, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S122_CONV_2D_0_124_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S122_CONV_2D_0_124_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S122_CONV_2D_0_124_fusion, "CUSTOM_ACTIVATION_NAME", "expr_11");
    CNN_ExtraActivationArgs_T gen_ctrl_S122_CONV_2D_0_124_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S122_CONV_2D_0_124_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S122_CONV_2D_0_124_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S122_CONV_2D_0_124_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S122_CONV_2D_0_124_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_124_fusion
    CNN_ConvolutionNE16("S122_CONV_2D_0_124_fusion", &gen_ctrl_S122_CONV_2D_0_124_fusion,
                        -1, -1, 4, 1, 8,
                        64, 32, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_124_split
    CNN_SplitLastAxis_Generator("S123_CONV_2D_0_124_split", 0, -1, 1024, 16, 16, 0, 0, KOP_SPLIT);
    
    
    // generator for CONCAT_0_136_qin1
    CNN_Convert("S124_CONCAT_0_136_qin1", -1, -1, 16384, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S127_CONV_2D_0_127_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S127_CONV_2D_0_127_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S127_CONV_2D_0_127_fusion, "CUSTOM_ACTIVATION_NAME", "expr_12");
    CNN_ExtraActivationArgs_T gen_ctrl_S127_CONV_2D_0_127_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S127_CONV_2D_0_127_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S127_CONV_2D_0_127_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S127_CONV_2D_0_127_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S127_CONV_2D_0_127_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_127_fusion
    CNN_ConvolutionNE16("S127_CONV_2D_0_127_fusion", &gen_ctrl_S127_CONV_2D_0_127_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S130_CONV_2D_0_130_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S130_CONV_2D_0_130_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_130_fusion, "CUSTOM_ACTIVATION_NAME", "expr_14");
    CNN_ExtraActivationArgs_T gen_ctrl_S130_CONV_2D_0_130_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_130_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S130_CONV_2D_0_130_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_130_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_130_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_130_fusion
    CNN_ConvolutionNE16("S130_CONV_2D_0_130_fusion", &gen_ctrl_S130_CONV_2D_0_130_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 14,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONCAT_0_136
    CNN_ConcatLastAxis_Generator("S131_CONCAT_0_136", 0, -1, 1024, 16, 16, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S134_CONV_2D_0_137_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S134_CONV_2D_0_137_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S134_CONV_2D_0_137_fusion, "CUSTOM_ACTIVATION_NAME", "expr_16");
    CNN_ExtraActivationArgs_T gen_ctrl_S134_CONV_2D_0_137_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S134_CONV_2D_0_137_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S134_CONV_2D_0_137_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S134_CONV_2D_0_137_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S134_CONV_2D_0_137_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_137_fusion
    CNN_ConvolutionNE16("S134_CONV_2D_0_137_fusion", &gen_ctrl_S134_CONV_2D_0_137_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S137_CONV_2D_0_141_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S137_CONV_2D_0_141_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_141_fusion, "CUSTOM_ACTIVATION_NAME", "expr_17");
    CNN_ExtraActivationArgs_T gen_ctrl_S137_CONV_2D_0_141_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_141_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S137_CONV_2D_0_141_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_141_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_141_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_141_fusion
    CNN_ConvolutionNE16("S137_CONV_2D_0_141_fusion", &gen_ctrl_S137_CONV_2D_0_141_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONCAT_0_144
    CNN_ConcatLastAxis_Generator("S138_CONCAT_0_144", 0, -1, 256, 32, 32, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S141_CONV_2D_0_145_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S141_CONV_2D_0_145_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S141_CONV_2D_0_145_fusion, "CUSTOM_ACTIVATION_NAME", "expr_18");
    CNN_ExtraActivationArgs_T gen_ctrl_S141_CONV_2D_0_145_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S141_CONV_2D_0_145_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S141_CONV_2D_0_145_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S141_CONV_2D_0_145_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S141_CONV_2D_0_145_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_145_fusion
    CNN_ConvolutionNE16("S141_CONV_2D_0_145_fusion", &gen_ctrl_S141_CONV_2D_0_145_fusion,
                        -1, -1, 4, 1, 8,
                        32, 64, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S144_CONV_2D_0_148_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S144_CONV_2D_0_148_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_148_fusion, "CUSTOM_ACTIVATION_NAME", "expr_19");
    CNN_ExtraActivationArgs_T gen_ctrl_S144_CONV_2D_0_148_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_148_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S144_CONV_2D_0_148_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_148_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_148_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_148_fusion
    CNN_ConvolutionNE16("S144_CONV_2D_0_148_fusion", &gen_ctrl_S144_CONV_2D_0_148_fusion,
                        -1, -1, 4, 1, 8,
                        64, 64, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S147_CONV_2D_0_151_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S147_CONV_2D_0_151_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S147_CONV_2D_0_151_fusion, "CUSTOM_ACTIVATION_NAME", "expr_20");
    CNN_ExtraActivationArgs_T gen_ctrl_S147_CONV_2D_0_151_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S147_CONV_2D_0_151_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S147_CONV_2D_0_151_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S147_CONV_2D_0_151_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S147_CONV_2D_0_151_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_151_fusion
    CNN_ConvolutionNE16("S147_CONV_2D_0_151_fusion", &gen_ctrl_S147_CONV_2D_0_151_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S150_CONV_2D_0_154_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S150_CONV_2D_0_154_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S150_CONV_2D_0_154_fusion, "CUSTOM_ACTIVATION_NAME", "expr_21");
    CNN_ExtraActivationArgs_T gen_ctrl_S150_CONV_2D_0_154_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S150_CONV_2D_0_154_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S150_CONV_2D_0_154_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S150_CONV_2D_0_154_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S150_CONV_2D_0_154_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_154_fusion
    CNN_ConvolutionNE16("S150_CONV_2D_0_154_fusion", &gen_ctrl_S150_CONV_2D_0_154_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 32, 32,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S153_CONV_2D_0_157_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S153_CONV_2D_0_157_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S153_CONV_2D_0_157_fusion, "CUSTOM_ACTIVATION_NAME", "expr_22");
    CNN_ExtraActivationArgs_T gen_ctrl_S153_CONV_2D_0_157_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S153_CONV_2D_0_157_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S153_CONV_2D_0_157_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S153_CONV_2D_0_157_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S153_CONV_2D_0_157_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_157_fusion
    CNN_ConvolutionNE16("S153_CONV_2D_0_157_fusion", &gen_ctrl_S153_CONV_2D_0_157_fusion,
                        -1, -1, 4, 1, 8,
                        64, 56, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_157_split
    CNN_SplitLastAxis_Generator("S154_CONV_2D_0_157_split", 0, -1, 256, 28, 28, 0, 0, KOP_SPLIT);
    
    
    // generator for CONCAT_0_173_qin1
    CNN_Convert("S155_CONCAT_0_173_qin1", -1, -1, 7168, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S158_CONV_2D_0_163;
    CNN_InitGenCtrl(&gen_ctrl_S158_CONV_2D_0_163);
    CNN_SetGenCtrl(&gen_ctrl_S158_CONV_2D_0_163, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S158_CONV_2D_0_163, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_163
    CNN_ConvolutionNE16("S158_CONV_2D_0_163", &gen_ctrl_S158_CONV_2D_0_163,
                        -1, -1, 4, 1, 8,
                        64, 64, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S161_CONV_2D_0_164;
    CNN_InitGenCtrl(&gen_ctrl_S161_CONV_2D_0_164);
    CNN_SetGenCtrl(&gen_ctrl_S161_CONV_2D_0_164, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S161_CONV_2D_0_164, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_164
    CNN_ConvolutionNE16("S161_CONV_2D_0_164", &gen_ctrl_S161_CONV_2D_0_164,
                        -1, -1, 4, 1, 8,
                        32, 13, 32, 32,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 7,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for CONCAT_0_165
    CNN_ConcatLastAxis_Generator("S162_CONCAT_0_165", 0, -1, 1024, 64, 13, 0, 0, KOP_CONCAT);
    
    
    // generator for CONCAT_0_233_qin0
    CNN_Convert("S164_CONCAT_0_233_qin0", -1, -1, 78848, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S167_CONV_2D_0_167_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S167_CONV_2D_0_167_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_167_fusion, "CUSTOM_ACTIVATION_NAME", "expr_25");
    CNN_ExtraActivationArgs_T gen_ctrl_S167_CONV_2D_0_167_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_167_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S167_CONV_2D_0_167_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_167_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_167_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_167_fusion
    CNN_ConvolutionNE16("S167_CONV_2D_0_167_fusion", &gen_ctrl_S167_CONV_2D_0_167_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S170_CONV_2D_0_170_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S170_CONV_2D_0_170_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_170_fusion, "CUSTOM_ACTIVATION_NAME", "expr_26");
    CNN_ExtraActivationArgs_T gen_ctrl_S170_CONV_2D_0_170_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_170_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S170_CONV_2D_0_170_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_170_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_170_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_170_fusion
    CNN_ConvolutionNE16("S170_CONV_2D_0_170_fusion", &gen_ctrl_S170_CONV_2D_0_170_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 13,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONCAT_0_173
    CNN_ConcatLastAxis_Generator("S171_CONCAT_0_173", 0, -1, 256, 28, 28, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S174_CONV_2D_0_174_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S174_CONV_2D_0_174_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_174_fusion, "CUSTOM_ACTIVATION_NAME", "expr_27");
    CNN_ExtraActivationArgs_T gen_ctrl_S174_CONV_2D_0_174_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_174_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S174_CONV_2D_0_174_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_174_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_174_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_174_fusion
    CNN_ConvolutionNE16("S174_CONV_2D_0_174_fusion", &gen_ctrl_S174_CONV_2D_0_174_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S177_CONV_2D_0_178_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S177_CONV_2D_0_178_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S177_CONV_2D_0_178_fusion, "CUSTOM_ACTIVATION_NAME", "expr_28");
    CNN_ExtraActivationArgs_T gen_ctrl_S177_CONV_2D_0_178_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S177_CONV_2D_0_178_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S177_CONV_2D_0_178_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S177_CONV_2D_0_178_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S177_CONV_2D_0_178_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_178_fusion
    CNN_ConvolutionNE16("S177_CONV_2D_0_178_fusion", &gen_ctrl_S177_CONV_2D_0_178_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONCAT_0_181
    CNN_ConcatLastAxis_Generator("S178_CONCAT_0_181", 0, -1, 64, 56, 56, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S181_CONV_2D_0_182_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S181_CONV_2D_0_182_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S181_CONV_2D_0_182_fusion, "CUSTOM_ACTIVATION_NAME", "expr_29");
    CNN_ExtraActivationArgs_T gen_ctrl_S181_CONV_2D_0_182_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S181_CONV_2D_0_182_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S181_CONV_2D_0_182_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S181_CONV_2D_0_182_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S181_CONV_2D_0_182_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_182_fusion
    CNN_ConvolutionNE16("S181_CONV_2D_0_182_fusion", &gen_ctrl_S181_CONV_2D_0_182_fusion,
                        -1, -1, 4, 1, 8,
                        56, 64, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S184_CONV_2D_0_185_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S184_CONV_2D_0_185_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S184_CONV_2D_0_185_fusion, "CUSTOM_ACTIVATION_NAME", "expr_30");
    CNN_ExtraActivationArgs_T gen_ctrl_S184_CONV_2D_0_185_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S184_CONV_2D_0_185_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S184_CONV_2D_0_185_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S184_CONV_2D_0_185_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S184_CONV_2D_0_185_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_185_fusion
    CNN_ConvolutionNE16("S184_CONV_2D_0_185_fusion", &gen_ctrl_S184_CONV_2D_0_185_fusion,
                        -1, -1, 4, 1, 8,
                        56, 32, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S187_CONV_2D_0_188_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S187_CONV_2D_0_188_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S187_CONV_2D_0_188_fusion, "CUSTOM_ACTIVATION_NAME", "expr_31");
    CNN_ExtraActivationArgs_T gen_ctrl_S187_CONV_2D_0_188_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S187_CONV_2D_0_188_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S187_CONV_2D_0_188_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S187_CONV_2D_0_188_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S187_CONV_2D_0_188_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_188_fusion
    CNN_ConvolutionNE16("S187_CONV_2D_0_188_fusion", &gen_ctrl_S187_CONV_2D_0_188_fusion,
                        -1, -1, 4, 1, 8,
                        64, 64, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S190_CONV_2D_0_191_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S190_CONV_2D_0_191_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S190_CONV_2D_0_191_fusion, "CUSTOM_ACTIVATION_NAME", "expr_32");
    CNN_ExtraActivationArgs_T gen_ctrl_S190_CONV_2D_0_191_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S190_CONV_2D_0_191_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S190_CONV_2D_0_191_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S190_CONV_2D_0_191_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S190_CONV_2D_0_191_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_191_fusion
    CNN_ConvolutionNE16("S190_CONV_2D_0_191_fusion", &gen_ctrl_S190_CONV_2D_0_191_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 16, 16,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 10,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S193_CONV_2D_0_194_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S193_CONV_2D_0_194_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S193_CONV_2D_0_194_fusion, "CUSTOM_ACTIVATION_NAME", "expr_33");
    CNN_ExtraActivationArgs_T gen_ctrl_S193_CONV_2D_0_194_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S193_CONV_2D_0_194_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S193_CONV_2D_0_194_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S193_CONV_2D_0_194_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S193_CONV_2D_0_194_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_194_fusion
    CNN_ConvolutionNE16("S193_CONV_2D_0_194_fusion", &gen_ctrl_S193_CONV_2D_0_194_fusion,
                        -1, -1, 4, 1, 8,
                        112, 104, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 15,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_194_split
    CNN_SplitLastAxis_Generator("S194_CONV_2D_0_194_split", 0, -1, 64, 52, 52, 0, 0, KOP_SPLIT);
    
    CNN_GenControl_T gen_ctrl_S197_CONV_2D_0_200;
    CNN_InitGenCtrl(&gen_ctrl_S197_CONV_2D_0_200);
    CNN_SetGenCtrl(&gen_ctrl_S197_CONV_2D_0_200, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S197_CONV_2D_0_200, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_200
    CNN_ConvolutionNE16("S197_CONV_2D_0_200", &gen_ctrl_S197_CONV_2D_0_200,
                        -1, -1, 4, 1, 8,
                        64, 64, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 8,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S200_CONV_2D_0_201;
    CNN_InitGenCtrl(&gen_ctrl_S200_CONV_2D_0_201);
    CNN_SetGenCtrl(&gen_ctrl_S200_CONV_2D_0_201, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S200_CONV_2D_0_201, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_201
    CNN_ConvolutionNE16("S200_CONV_2D_0_201", &gen_ctrl_S200_CONV_2D_0_201,
                        -1, -1, 4, 1, 8,
                        32, 13, 16, 16,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 8,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for CONCAT_0_202
    CNN_ConcatLastAxis_Generator("S201_CONCAT_0_202", 0, -1, 256, 64, 13, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S205_CONV_2D_0_204_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S205_CONV_2D_0_204_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S205_CONV_2D_0_204_fusion, "CUSTOM_ACTIVATION_NAME", "expr_35");
    CNN_ExtraActivationArgs_T gen_ctrl_S205_CONV_2D_0_204_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S205_CONV_2D_0_204_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S205_CONV_2D_0_204_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S205_CONV_2D_0_204_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S205_CONV_2D_0_204_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_204_fusion
    CNN_ConvolutionNE16("S205_CONV_2D_0_204_fusion", &gen_ctrl_S205_CONV_2D_0_204_fusion,
                        -1, -1, 4, 1, 8,
                        52, 52, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 16,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S208_CONV_2D_0_207_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S208_CONV_2D_0_207_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S208_CONV_2D_0_207_fusion, "CUSTOM_ACTIVATION_NAME", "expr_36");
    CNN_ExtraActivationArgs_T gen_ctrl_S208_CONV_2D_0_207_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S208_CONV_2D_0_207_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S208_CONV_2D_0_207_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S208_CONV_2D_0_207_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S208_CONV_2D_0_207_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_207_fusion
    CNN_ConvolutionNE16("S208_CONV_2D_0_207_fusion", &gen_ctrl_S208_CONV_2D_0_207_fusion,
                        -1, -1, 4, 1, 8,
                        52, 52, 8, 8,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 17,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONCAT_0_210
    CNN_ConcatLastAxis_Generator("S209_CONCAT_0_210", 0, -1, 64, 52, 52, 0, 0, KOP_CONCAT);
    
    CNN_GenControl_T gen_ctrl_S212_CONV_2D_0_211_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S212_CONV_2D_0_211_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S212_CONV_2D_0_211_fusion, "CUSTOM_ACTIVATION_NAME", "expr_37");
    CNN_ExtraActivationArgs_T gen_ctrl_S212_CONV_2D_0_211_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S212_CONV_2D_0_211_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S212_CONV_2D_0_211_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S212_CONV_2D_0_211_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S212_CONV_2D_0_211_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_211_fusion
    CNN_ConvolutionNE16("S212_CONV_2D_0_211_fusion", &gen_ctrl_S212_CONV_2D_0_211_fusion,
                        -1, -1, 4, 1, 8,
                        104, 104, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 16,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S215_CONV_2D_0_214_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S215_CONV_2D_0_214_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S215_CONV_2D_0_214_fusion, "CUSTOM_ACTIVATION_NAME", "expr_38");
    CNN_ExtraActivationArgs_T gen_ctrl_S215_CONV_2D_0_214_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S215_CONV_2D_0_214_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S215_CONV_2D_0_214_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S215_CONV_2D_0_214_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S215_CONV_2D_0_214_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_214_fusion
    CNN_ConvolutionNE16("S215_CONV_2D_0_214_fusion", &gen_ctrl_S215_CONV_2D_0_214_fusion,
                        -1, -1, 4, 1, 8,
                        104, 64, 8, 8,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 18,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S218_CONV_2D_0_217_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S218_CONV_2D_0_217_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S218_CONV_2D_0_217_fusion, "CUSTOM_ACTIVATION_NAME", "expr_39");
    CNN_ExtraActivationArgs_T gen_ctrl_S218_CONV_2D_0_217_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S218_CONV_2D_0_217_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S218_CONV_2D_0_217_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S218_CONV_2D_0_217_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S218_CONV_2D_0_217_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_217_fusion
    CNN_ConvolutionNE16("S218_CONV_2D_0_217_fusion", &gen_ctrl_S218_CONV_2D_0_217_fusion,
                        -1, -1, 4, 1, 8,
                        104, 32, 8, 8,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 18,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S221_CONV_2D_0_220_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S221_CONV_2D_0_220_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S221_CONV_2D_0_220_fusion, "CUSTOM_ACTIVATION_NAME", "expr_40");
    CNN_ExtraActivationArgs_T gen_ctrl_S221_CONV_2D_0_220_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S221_CONV_2D_0_220_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S221_CONV_2D_0_220_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S221_CONV_2D_0_220_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S221_CONV_2D_0_220_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_220_fusion
    CNN_ConvolutionNE16("S221_CONV_2D_0_220_fusion", &gen_ctrl_S221_CONV_2D_0_220_fusion,
                        -1, -1, 4, 1, 8,
                        64, 64, 8, 8,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 16,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S224_CONV_2D_0_223_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S224_CONV_2D_0_223_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S224_CONV_2D_0_223_fusion, "CUSTOM_ACTIVATION_NAME", "expr_41");
    CNN_ExtraActivationArgs_T gen_ctrl_S224_CONV_2D_0_223_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S224_CONV_2D_0_223_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S224_CONV_2D_0_223_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S224_CONV_2D_0_223_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S224_CONV_2D_0_223_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_223_fusion
    CNN_ConvolutionNE16("S224_CONV_2D_0_223_fusion", &gen_ctrl_S224_CONV_2D_0_223_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 8, 8,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 24,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S227_CONV_2D_0_226;
    CNN_InitGenCtrl(&gen_ctrl_S227_CONV_2D_0_226);
    CNN_SetGenCtrl(&gen_ctrl_S227_CONV_2D_0_226, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S227_CONV_2D_0_226, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_226
    CNN_ConvolutionNE16("S227_CONV_2D_0_226", &gen_ctrl_S227_CONV_2D_0_226,
                        -1, -1, 4, 1, 8,
                        64, 64, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S230_CONV_2D_0_227;
    CNN_InitGenCtrl(&gen_ctrl_S230_CONV_2D_0_227);
    CNN_SetGenCtrl(&gen_ctrl_S230_CONV_2D_0_227, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S230_CONV_2D_0_227, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_227
    CNN_ConvolutionNE16("S230_CONV_2D_0_227", &gen_ctrl_S230_CONV_2D_0_227,
                        -1, -1, 4, 1, 8,
                        32, 13, 8, 8,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 25,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for CONCAT_0_228
    CNN_ConcatLastAxis_Generator("S231_CONCAT_0_228", 0, -1, 64, 64, 13, 0, 0, KOP_CONCAT);
    
    
    // generator for CONCAT_0_233_qin2
    CNN_Convert("S233_CONCAT_0_233_qin2", -1, -1, 4928, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for STRIDED_SLICE_0_234_split
    CNN_SplitLastAxis_Generator("S235_STRIDED_SLICE_0_234_split", 0, -1, 1344, 64, 13, 0, 0, KOP_SPLIT);
    
    
    // generator for SOFTMAX_0_237_qin0
    CNN_Convert("S237_SOFTMAX_0_237_qin0", -1, 1, 86016, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S238_SOFTMAX_0_237;
    CNN_InitGenCtrl(&gen_ctrl_S238_SOFTMAX_0_237);
    CNN_SetGenCtrl(&gen_ctrl_S238_SOFTMAX_0_237, "INPUT_DATASIZE", AT_OPT_VAL(1));
    // generator for SOFTMAX_0_237
    CNN_SoftMax2D_SQ8("S238_SOFTMAX_0_237", &gen_ctrl_S238_SOFTMAX_0_237, 5376, 16, KOP_SOFTMAX);
    
    
    // generator for CONV_2D_0_240_qin0
    CNN_Convert("S239_CONV_2D_0_240_qin0", 2, -1, 86016, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for CONV_2D_0_240_trans Transpose 1344x4x16 -> 4x1344x16 ((1, 0, 2))
    CNN_3DTensorPermute("S240_CONV_2D_0_240_trans", 0, -1,
                         1344, 16, 4, KOP_MATPERM_CHW2HCW);
    
    
    // generator for LOGISTIC_0_243_qin0
    CNN_Convert("S241_LOGISTIC_0_243_qin0", -1, -1, 17472, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S242_LOGISTIC_0_243;
    CNN_InitGenCtrl(&gen_ctrl_S242_LOGISTIC_0_243);
    CNN_ExtraActivationArgs_T gen_ctrl_S242_LOGISTIC_0_243_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S242_LOGISTIC_0_243, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S242_LOGISTIC_0_243_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S242_LOGISTIC_0_243, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S242_LOGISTIC_0_243, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for LOGISTIC_0_243
    CNN_PoolAct_SQ8("S242_LOGISTIC_0_243", &gen_ctrl_S242_LOGISTIC_0_243,
                    1, 13, 1344,
                    KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                    KOP_SIGMOID);
    
    
    // generator for output_2_qin0
    CNN_Convert("S243_output_2_qin0", -1, -1, 17472, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S247_CONV_2D_0_240;
    CNN_InitGenCtrl(&gen_ctrl_S247_CONV_2D_0_240);
    CNN_SetGenCtrl(&gen_ctrl_S247_CONV_2D_0_240, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S247_CONV_2D_0_240, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_240
    CNN_ConvolutionNE16("S247_CONV_2D_0_240", &gen_ctrl_S247_CONV_2D_0_240,
                        -1, -1, 4, 1, 8,
                        16, 1, 1344, 4,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 0,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_1
    s255_kernel_gen("S255_expr_1");
    
    
    // generator for expr_64
    s257_kernel_gen("S257_expr_64");
    

#define GRAPH
#ifdef GRAPH
    CreateGraph("best_float32CNN",
        /* Arguments either passed or globals */
            CArgs(336,
                TCArgInfo("unsigned char * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_con", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfoExpKerSize("Model_37_tf_nn_convolution_con.tensor", 1, 1, 8, 0, 864)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S3_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S3_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.06207 out: 0.03414  BIASN: 0 PRENORM: 0 NE16_PADVAL: [0] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S3_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_1_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_1_c.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_1_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_1_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S6_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S6_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.09082 out: 0.04266  BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S6_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_2_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_2_c.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_2_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_2_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S9_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S9_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.08408 out: 0.04335  BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S9_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.26<(u8-6.00)*0.04334839<10.79 out_q: -0.56<(u8-12.00)*0.04638396<11.27
                TCArgInfo("signed char * __restrict__", "S11_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S11_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_4_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_4_c.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_4_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_4_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S14_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S14_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.06902 out: 0.03010  BIASN: 0 PRENORM: 0 NE16_PADVAL: [6] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S14_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_5_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_5_c.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_5_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_5_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S17_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S17_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S17_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_6_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_6_c.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_8_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_8_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S22_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S22_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.07176 out: 0.03601  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S22_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_7_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_7_c.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_9_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_9_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S25_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S25_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.06148 out: 0.03098  BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S25_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_10_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_10_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_12_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_12_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S28_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S28_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.05429 out: 0.02950  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S28_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-9.00)*0.02950010<7.26 out_q: -0.55<(u8-16.00)*0.03420605<8.18
                TCArgInfo("signed char * __restrict__", "S30_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S30_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_14_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_14_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_16_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_16_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S33_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S33_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.05814 out: 0.03016  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S33_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_15_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_15_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_17_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_17_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S36_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S36_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S36_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_18_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_18_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_22_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_22_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S41_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S41_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04632 out: 0.02365  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S41_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_26_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_26_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_30_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_30_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S44_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S44_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S44_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S44_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03631 out: 0.01869  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S44_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S44_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_27_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_27_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_31_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_31_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S47_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S47_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S47_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S47_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04097 out: 0.01805  BIASN: 0 PRENORM: 0 NE16_PADVAL: [15] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S47_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S47_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-15.00)*0.01805458<4.33 out_q: -0.55<(u8-16.00)*0.03460563<8.27
                TCArgInfo("signed char * __restrict__", "S49_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S49_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_29_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_29_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_33_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_33_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S52_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S52_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S52_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S52_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04288 out: 0.02112  BIASN: 0 PRENORM: 0 NE16_PADVAL: [15] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S52_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S52_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_30_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_30_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_34_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_34_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S55_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S55_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S55_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S55_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S55_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S55_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_31_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_31_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_37_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_37_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S60_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S60_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S60_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S60_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04399 out: 0.02178  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S60_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S60_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_32_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_32_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_38_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_38_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S63_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S63_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S63_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S63_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04120 out: 0.02274  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S63_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S63_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_33_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_33_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_39_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_39_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S66_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S66_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S66_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S66_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04125 out: 0.02035  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S66_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S66_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-14.00)*0.02034669<4.90 out_q: -0.57<(u8-15.00)*0.03805612<9.13
                TCArgInfo("signed char * __restrict__", "S68_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S68_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_35_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_35_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_41_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_41_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S71_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S71_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S71_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S71_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04616 out: 0.02389  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S71_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S71_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_36_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_36_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_42_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_42_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S74_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S74_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S74_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S74_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S74_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S74_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_37_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_37_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_45_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_45_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S79_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S79_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S79_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S79_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03936 out: 0.02041  BIASN: 0 PRENORM: 0 NE16_PADVAL: [15] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S79_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S79_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_38_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_38_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_46_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_46_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S82_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S82_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S82_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S82_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04140 out: 0.03950  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S82_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S82_Infos.tensor", 1, 1, 8, 0)),
                // no activation ACTSCALE: [1] ACTSCALEN: [0]
                TCArgInfo("signed char * __restrict__", "S83_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Infos.tensor", 1, 1, 8, 0)),
                // no activation ACTSCALE: [1] ACTSCALEN: [0]
                TCArgInfo("signed char * __restrict__", "S84_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S84_Infos.tensor", 1, 1, 8, 0)),
                // no activation ACTSCALE: [1] ACTSCALEN: [0]
                TCArgInfo("signed char * __restrict__", "S85_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S85_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_39_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_39_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_47_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_47_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S89_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S89_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S89_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S89_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03980 out: 0.02307  BIASN: 0 PRENORM: 0 NE16_PADVAL: [128] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S89_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S89_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_40_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_40_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_48_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_48_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S92_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S92_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S92_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S92_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03331 out: 0.01893  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S92_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S92_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-15.00)*0.01893161<4.54 out_q: -0.28<(u8-13.00)*0.02177561<5.27
                TCArgInfo("signed char * __restrict__", "S93_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S93_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_41_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_41_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_49_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_49_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S100_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S100_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S100_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S100_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04190 out: 0.02175  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S100_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S100_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_43_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_43_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_51_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_51_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S104_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S104_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S104_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S104_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03952 out: 0.02065  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S104_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S104_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_44_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_44_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_52_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_52_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S107_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S107_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S107_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S107_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03864 out: 0.02175  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S107_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S107_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_45_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_45_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_53_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_53_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S111_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S111_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S111_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S111_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03777 out: 0.02046  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S111_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S111_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_46_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_46_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_54_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_54_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S114_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S114_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S114_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S114_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03394 out: 0.02256  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S114_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S114_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-12.00)*0.02255585<5.48 out_q: -0.28<(u8-12.00)*0.02365436<5.75
                TCArgInfo("signed char * __restrict__", "S115_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S115_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_47_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_47_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_55_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_55_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S122_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S122_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S122_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S122_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03908 out: 0.01975  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S122_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S122_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-14.00)*0.01975346<4.76 out_q: -0.29<(u8-9.00)*0.03267019<8.04
                TCArgInfo("signed char * __restrict__", "S124_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S124_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_49_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_49_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_57_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_57_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S127_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S127_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S127_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S127_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03705 out: 0.01936  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S127_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S127_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_50_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_50_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_58_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_58_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S130_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S130_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S130_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S130_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04959 out: 0.03267  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S130_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S130_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_53_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_53_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_61_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_61_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S134_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S134_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S134_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S134_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04011 out: 0.02101  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S134_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S134_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_61_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_61_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_69_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_69_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S137_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S137_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S137_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S137_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03916 out: 0.02256  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S137_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S137_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_64_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_64_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_72_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_72_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S141_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S141_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S141_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S141_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04384 out: 0.02239  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S141_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S141_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_68_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_68_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_76_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_76_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S144_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S144_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S144_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S144_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04708 out: 0.03093  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S144_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S144_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_67_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_67_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_75_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_75_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S147_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S147_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S147_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S147_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.05482 out: 0.02991  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S147_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S147_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_71_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_71_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_79_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_79_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S150_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S150_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S150_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S150_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.07766 out: 0.04157  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S150_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S150_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_72_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_72_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_80_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_80_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S153_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S153_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S153_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S153_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03928 out: 0.02084  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S153_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S153_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-13.00)*0.02083624<5.04 out_q: -0.28<(u8-11.00)*0.02538720<6.19
                TCArgInfo("signed char * __restrict__", "S155_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S155_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_74_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_74_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_82_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_82_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S158_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S158_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S158_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S158_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S158_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S158_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_77_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_77_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_85_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_85_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S161_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S161_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S161_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S161_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S161_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S161_Infos.tensor", 1, 1, 8, 0)),
                // in q: -9.81<(u8-124.00)*0.07908482<10.36 out_q: -14.09<(u8-154.00)*0.09148052<9.24
                TCArgInfo("signed char * __restrict__", "S164_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S164_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_78_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_78_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_86_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_86_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S167_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S167_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S167_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S167_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04149 out: 0.02075  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S167_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S167_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_79_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_79_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_87_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_87_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S170_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S170_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S170_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S170_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04322 out: 0.02539  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S170_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S170_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_80_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_80_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_88_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_88_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S174_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S174_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S174_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S174_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04271 out: 0.02270  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S174_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S174_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_81_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_81_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_89_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_89_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S177_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S177_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S177_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S177_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03823 out: 0.01893  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S177_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S177_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_82_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_82_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_90_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_90_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S181_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S181_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S181_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S181_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04336 out: 0.02229  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S181_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S181_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_83_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_83_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_91_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_91_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S184_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S184_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S184_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S184_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.05404 out: 0.02883  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S184_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S184_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_84_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_84_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_92_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_92_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S187_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S187_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S187_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S187_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.05288 out: 0.03601  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S187_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S187_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_85_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_85_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_93_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_93_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S190_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S190_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S190_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S190_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.05978 out: 0.03695  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S190_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S190_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_86_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_86_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_94_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_94_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S193_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S193_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S193_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S193_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03724 out: 0.01727  BIASN: 0 PRENORM: 0 NE16_PADVAL: [15] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S193_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S193_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_88_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_88_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_96_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_96_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S197_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S197_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S197_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S197_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S197_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S197_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_89_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_89_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_97_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_97_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S200_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S200_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S200_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S200_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S200_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S200_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_90_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_90_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_98_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_98_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S205_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S205_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S205_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S205_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03180 out: 0.01596  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S205_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S205_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_91_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_91_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_99_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_99_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S208_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S208_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S208_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S208_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02497 out: 0.01727  BIASN: 0 PRENORM: 0 NE16_PADVAL: [17] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S208_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S208_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_92_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_92_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_100_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_100_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S212_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S212_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S212_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S212_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02916 out: 0.01591  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S212_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S212_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_93_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_93_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_101_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_101_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S215_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S215_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S215_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S215_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03232 out: 0.01785  BIASN: 0 PRENORM: 0 NE16_PADVAL: [18] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S215_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S215_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_94_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_94_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_102_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_102_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S218_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S218_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S218_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S218_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02438 out: 0.01164  BIASN: 0 PRENORM: 0 NE16_PADVAL: [18] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S218_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S218_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_95_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_95_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_103_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_103_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S221_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S221_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S221_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S221_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04393 out: 0.02456  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S221_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S221_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_96_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_96_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_104_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_104_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S224_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S224_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S224_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S224_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02037 out: 0.01099  BIASN: 0 PRENORM: 0 NE16_PADVAL: [24] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S224_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S224_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_97_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_97_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_105_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_105_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S227_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S227_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S227_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S227_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S227_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S227_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_98_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_98_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_106_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_106_add_y.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S230_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S230_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S230_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S230_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [25] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S230_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S230_Infos.tensor", 1, 1, 8, 0)),
                // in q: -12.85<(u8-255.00)*0.05040178<0.00 out_q: -14.09<(u8-154.00)*0.09148052<9.24
                TCArgInfo("signed char * __restrict__", "S233_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S233_Infos.tensor", 1, 1, 8, 0)),
                // in q: -14.09<(u8-154.00)*0.09148052<9.24 out_q: -16.00<(i8-0.00)*0.12500000<15.88 forced
                TCArgInfo("signed char * __restrict__", "S237_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S237_Infos.tensor", 1, 1, 8, 0)),
                // in: 0.12500 out: 0.00003  BIASL_SM: [12]
                TCArgInfo("signed char * __restrict__", "S238_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S238_Infos.tensor", 1, 1, 8, 0)),
                // in q: -1.00<(i16-0.00)*0.00003052<1.00 out_q: 0.00<(u8-0.00)*0.00309831<0.79
                TCArgInfo("signed char * __restrict__", "S239_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S239_Infos.tensor", 1, 1, 8, 0)),
                // in q: -14.09<(u8-154.00)*0.09148052<9.24 out_q: -8.06<(u8-128.00)*0.06299213<8.00 forced
                TCArgInfo("signed char * __restrict__", "S241_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S241_Infos.tensor", 1, 1, 8, 0)),
                // in: 0.06299 out: 0.00392  actscale: [255] actscalen: [15] a0: [0] b0: 0 c0: 0
                TCArgInfo("signed char * __restrict__", "S242_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S242_Infos.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.00392157<1.00 out_q: -1.01<(u8-128.00)*0.00787402<1.00 forced
                TCArgInfo("signed char * __restrict__", "S243_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S243_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_99__15e5e2e5_0", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_99__15e5e2e5_0.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Model_37_tf_nn_convolution_99_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_nn_convolution_99_.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S247_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S247_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S247_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S247_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [0] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S247_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S247_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Model_37_6790", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_6790.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Model_37_tf_math_multiply_201_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_multiply_201_.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Model_37_6790_1", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_6790_1.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned short * __restrict__", "SigmoidLUTTable", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("SigmoidLUTTable.tensor", 1, 1, 16, 0)),
                TCArgInfo("signed char * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("unsigned char * __restrict__", "Output_2", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(124,
            TCArgInfo("unsigned char * __restrict__", "S3_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S6_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S9_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S10_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S10_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S11_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S14_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S17_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S18_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S19_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S22_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S25_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S28_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S29_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S29_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S30_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S33_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S36_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S37_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S38_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S41_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S44_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S47_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S48_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S48_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S49_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S52_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S55_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S56_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S57_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S60_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S63_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S66_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S67_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S67_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S68_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S71_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S74_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S75_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S76_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S79_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S82_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S83_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S84_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S85_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S86_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S89_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S92_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S93_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S94_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S95_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S96_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S97_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S100_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S101_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S101_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S104_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S107_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S108_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S111_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S114_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S115_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S116_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S117_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S118_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S119_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S122_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S123_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S123_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S124_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S127_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S130_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S131_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S134_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S137_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S138_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S141_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S144_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S147_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S150_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S153_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S154_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S154_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S155_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S158_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S161_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S162_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S167_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S170_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S171_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S174_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S177_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S178_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S181_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S184_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S187_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S190_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S193_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S194_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S194_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S197_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S200_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S205_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S208_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S209_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S212_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S215_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S218_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S221_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S224_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S227_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S230_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S231_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S234_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S235_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S235_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S237_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S238_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S239_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S240_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S241_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S242_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S247_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S256_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    // Stacked tensors for concats and splits
    AddStackedTensors(
        "S256_Output",
        2, "S255_Output_1", "S255_Output_0"
    );
    AddStackedTensors(
        "S247_Output",
        2, "S249_Output_0", "S249_Output_1"
    );
    AddStackedTensors(
        "S234_Output",
        3, "S164_Output", "S201_Output", "S233_Output"
    );

    // Node S3_CONV_2D_0_1_fusion inq 0.00<(u8-0.00)*0.00392157<1.00 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-8.00)*0.03414344<8.43 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S3_CONV_2D_0_1_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "Input_1", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_con", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_add_y", 0),
            GNodeArg(GNA_OUT, "S3_Output", 0),
            GNodeArg(GNA_IN, "S3_Mul_scale", 0),
            GNodeArg(GNA_IN, "S3_Mul_shift", 0),
            GNodeArg(GNA_IN, "S3_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S6_CONV_2D_0_5_fusion inq -0.27<(u8-8.00)*0.03414344<8.43 weightsq chan<(u8-128.00)*chan<chan outq -0.30<(u8-7.00)*0.04265840<10.58 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S6_CONV_2D_0_5_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S3_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_1_c", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_1_add_y", 0),
            GNodeArg(GNA_OUT, "S6_Output", 0),
            GNodeArg(GNA_IN, "S6_Mul_scale", 0),
            GNodeArg(GNA_IN, "S6_Mul_shift", 0),
            GNodeArg(GNA_IN, "S6_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S9_CONV_2D_0_8_fusion inq -0.30<(u8-7.00)*0.04265840<10.58 weightsq chan<(u8-128.00)*chan<chan outq -0.26<(u8-6.00)*0.04334839<10.79 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S9_CONV_2D_0_8_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S6_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_2_c", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_2_add_y", 0),
            GNodeArg(GNA_OUT, "S9_Output", 0),
            GNodeArg(GNA_IN, "S9_Mul_scale", 0),
            GNodeArg(GNA_IN, "S9_Mul_shift", 0),
            GNodeArg(GNA_IN, "S9_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_8_split inq ['-0.26<(u8-6.00)*0.04334839<10.79'] outq ['-0.26<(u8-6.00)*0.04334839<10.79', '-0.26<(u8-6.00)*0.04334839<10.79']
    AddNode("S10_CONV_2D_0_8_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S9_Output", 0),
            GNodeArg(GNA_OUT, "S10_Output_0", 0),
            GNodeArg(GNA_OUT, "S10_Output_1", 0)
        )
    );
    // Node CONCAT_0_21_qin1 inq -0.26<(u8-6.00)*0.04334839<10.79 outq -0.56<(u8-12.00)*0.04638396<11.27
    AddNode("S11_CONCAT_0_21_qin1",
        Bindings(3,
            GNodeArg(GNA_IN, "S10_Output_1", 0),
            GNodeArg(GNA_OUT, "S11_Output", 0),
            GNodeArg(GNA_IN, "S11_Infos", 0)
        )
    );
    // Node S14_CONV_2D_0_14_fusion inq -0.26<(u8-6.00)*0.04334839<10.79 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-9.00)*0.03010301<7.41 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S14_CONV_2D_0_14_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S10_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_4_c", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_4_add_y", 0),
            GNodeArg(GNA_OUT, "S14_Output", 0),
            GNodeArg(GNA_IN, "S14_Mul_scale", 0),
            GNodeArg(GNA_IN, "S14_Mul_shift", 0),
            GNodeArg(GNA_IN, "S14_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S17_CONV_2D_0_17 inq -0.27<(u8-9.00)*0.03010301<7.41 weightsq chan<(u8-128.00)*chan<chan outq -11.60<(u8-150.00)*0.07734178<8.12 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S17_CONV_2D_0_17",
        Bindings(7,
            GNodeArg(GNA_IN, "S14_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_5_c", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_5_add_y", 0),
            GNodeArg(GNA_OUT, "S17_Output", 0),
            GNodeArg(GNA_IN, "S17_Mul_scale", 0),
            GNodeArg(GNA_IN, "S17_Mul_shift", 0),
            GNodeArg(GNA_IN, "S17_Infos", 0)
        )
    );
    // Node expr_0 in_qs [-11.60<(u8-150.00)*0.07734178<8.12,-0.26<(u8-6.00)*0.04334839<10.79] out_qs [-0.56<(u8-12.00)*0.04638396<11.27]
    AddNode("S18_expr_0",
        Bindings(4,
            GNodeArg(GNA_IN, "S17_Output", 0),
            GNodeArg(GNA_IN, "S10_Output_0", 0),
            GNodeArg(GNA_OUT, "S18_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_21 inq ['-0.56<(u8-12.00)*0.04638396<11.27', '-0.56<(u8-12.00)*0.04638396<11.27'] outq ['-0.56<(u8-12.00)*0.04638396<11.27']
    AddNode("S19_CONCAT_0_21",
        Bindings(3,
            GNodeArg(GNA_IN, "S18_Output", 0),
            GNodeArg(GNA_IN, "S11_Output", 0),
            GNodeArg(GNA_OUT, "S19_Output", 0)
        )
    );
    // Node S22_CONV_2D_0_22_fusion inq -0.56<(u8-12.00)*0.04638396<11.27 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-8.00)*0.03601303<8.90 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S22_CONV_2D_0_22_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S19_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_6_c", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_8_add_y", 0),
            GNodeArg(GNA_OUT, "S22_Output", 0),
            GNodeArg(GNA_IN, "S22_Mul_scale", 0),
            GNodeArg(GNA_IN, "S22_Mul_shift", 0),
            GNodeArg(GNA_IN, "S22_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S25_CONV_2D_0_26_fusion inq -0.29<(u8-8.00)*0.03601303<8.90 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-9.00)*0.03097624<7.62 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S25_CONV_2D_0_26_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S22_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_7_c", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_9_add_y", 0),
            GNodeArg(GNA_OUT, "S25_Output", 0),
            GNodeArg(GNA_IN, "S25_Mul_scale", 0),
            GNodeArg(GNA_IN, "S25_Mul_shift", 0),
            GNodeArg(GNA_IN, "S25_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S28_CONV_2D_0_29_fusion inq -0.28<(u8-9.00)*0.03097624<7.62 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-9.00)*0.02950010<7.26 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S28_CONV_2D_0_29_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S25_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_10_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_12_add_y", 0),
            GNodeArg(GNA_OUT, "S28_Output", 0),
            GNodeArg(GNA_IN, "S28_Mul_scale", 0),
            GNodeArg(GNA_IN, "S28_Mul_shift", 0),
            GNodeArg(GNA_IN, "S28_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_29_split inq ['-0.27<(u8-9.00)*0.02950010<7.26'] outq ['-0.27<(u8-9.00)*0.02950010<7.26', '-0.27<(u8-9.00)*0.02950010<7.26']
    AddNode("S29_CONV_2D_0_29_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S28_Output", 0),
            GNodeArg(GNA_OUT, "S29_Output_0", 0),
            GNodeArg(GNA_OUT, "S29_Output_1", 0)
        )
    );
    // Node CONCAT_0_42_qin1 inq -0.27<(u8-9.00)*0.02950010<7.26 outq -0.55<(u8-16.00)*0.03420605<8.18
    AddNode("S30_CONCAT_0_42_qin1",
        Bindings(3,
            GNodeArg(GNA_IN, "S29_Output_1", 0),
            GNodeArg(GNA_OUT, "S30_Output", 0),
            GNodeArg(GNA_IN, "S30_Infos", 0)
        )
    );
    // Node S33_CONV_2D_0_32_fusion inq -0.27<(u8-9.00)*0.02950010<7.26 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-9.00)*0.03016425<7.42 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S33_CONV_2D_0_32_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S29_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_14_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_16_add_y", 0),
            GNodeArg(GNA_OUT, "S33_Output", 0),
            GNodeArg(GNA_IN, "S33_Mul_scale", 0),
            GNodeArg(GNA_IN, "S33_Mul_shift", 0),
            GNodeArg(GNA_IN, "S33_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S36_CONV_2D_0_35 inq -0.27<(u8-9.00)*0.03016425<7.42 weightsq chan<(u8-128.00)*chan<chan outq -4.98<(u8-106.00)*0.04698389<7.00 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S36_CONV_2D_0_35",
        Bindings(7,
            GNodeArg(GNA_IN, "S33_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_15_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_17_add_y", 0),
            GNodeArg(GNA_OUT, "S36_Output", 0),
            GNodeArg(GNA_IN, "S36_Mul_scale", 0),
            GNodeArg(GNA_IN, "S36_Mul_shift", 0),
            GNodeArg(GNA_IN, "S36_Infos", 0)
        )
    );
    // Node expr_2 in_qs [-4.98<(u8-106.00)*0.04698389<7.00,-0.27<(u8-9.00)*0.02950010<7.26] out_qs [-0.55<(u8-16.00)*0.03420605<8.18]
    AddNode("S37_expr_2",
        Bindings(4,
            GNodeArg(GNA_IN, "S36_Output", 0),
            GNodeArg(GNA_IN, "S29_Output_0", 0),
            GNodeArg(GNA_OUT, "S37_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_42 inq ['-0.55<(u8-16.00)*0.03420605<8.18', '-0.55<(u8-16.00)*0.03420605<8.18'] outq ['-0.55<(u8-16.00)*0.03420605<8.18']
    AddNode("S38_CONCAT_0_42",
        Bindings(3,
            GNodeArg(GNA_IN, "S37_Output", 0),
            GNodeArg(GNA_IN, "S30_Output", 0),
            GNodeArg(GNA_OUT, "S38_Output", 0)
        )
    );
    // Node S41_CONV_2D_0_43_fusion inq -0.55<(u8-16.00)*0.03420605<8.18 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-12.00)*0.02365436<5.75 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S41_CONV_2D_0_43_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S38_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_18_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_22_add_y", 0),
            GNodeArg(GNA_OUT, "S41_Output", 0),
            GNodeArg(GNA_IN, "S41_Mul_scale", 0),
            GNodeArg(GNA_IN, "S41_Mul_shift", 0),
            GNodeArg(GNA_IN, "S41_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S44_CONV_2D_0_47_fusion inq -0.28<(u8-12.00)*0.02365436<5.75 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-15.00)*0.01868674<4.48 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S44_CONV_2D_0_47_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S41_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_26_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_30_add_y", 0),
            GNodeArg(GNA_OUT, "S44_Output", 0),
            GNodeArg(GNA_IN, "S44_Mul_scale", 0),
            GNodeArg(GNA_IN, "S44_Mul_shift", 0),
            GNodeArg(GNA_IN, "S44_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S47_CONV_2D_0_50_fusion inq -0.28<(u8-15.00)*0.01868674<4.48 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-15.00)*0.01805458<4.33 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S47_CONV_2D_0_50_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S44_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_27_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_31_add_y", 0),
            GNodeArg(GNA_OUT, "S47_Output", 0),
            GNodeArg(GNA_IN, "S47_Mul_scale", 0),
            GNodeArg(GNA_IN, "S47_Mul_shift", 0),
            GNodeArg(GNA_IN, "S47_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_50_split inq ['-0.27<(u8-15.00)*0.01805458<4.33'] outq ['-0.27<(u8-15.00)*0.01805458<4.33', '-0.27<(u8-15.00)*0.01805458<4.33']
    AddNode("S48_CONV_2D_0_50_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S47_Output", 0),
            GNodeArg(GNA_OUT, "S48_Output_0", 0),
            GNodeArg(GNA_OUT, "S48_Output_1", 0)
        )
    );
    // Node CONCAT_0_63_qin1 inq -0.27<(u8-15.00)*0.01805458<4.33 outq -0.55<(u8-16.00)*0.03460563<8.27
    AddNode("S49_CONCAT_0_63_qin1",
        Bindings(3,
            GNodeArg(GNA_IN, "S48_Output_1", 0),
            GNodeArg(GNA_OUT, "S49_Output", 0),
            GNodeArg(GNA_IN, "S49_Infos", 0)
        )
    );
    // Node S52_CONV_2D_0_53_fusion inq -0.27<(u8-15.00)*0.01805458<4.33 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-13.00)*0.02112456<5.11 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S52_CONV_2D_0_53_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S48_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_29_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_33_add_y", 0),
            GNodeArg(GNA_OUT, "S52_Output", 0),
            GNodeArg(GNA_IN, "S52_Mul_scale", 0),
            GNodeArg(GNA_IN, "S52_Mul_shift", 0),
            GNodeArg(GNA_IN, "S52_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S55_CONV_2D_0_56 inq -0.27<(u8-13.00)*0.02112456<5.11 weightsq chan<(u8-128.00)*chan<chan outq -5.00<(u8-121.00)*0.04128413<5.53 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S55_CONV_2D_0_56",
        Bindings(7,
            GNodeArg(GNA_IN, "S52_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_30_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_34_add_y", 0),
            GNodeArg(GNA_OUT, "S55_Output", 0),
            GNodeArg(GNA_IN, "S55_Mul_scale", 0),
            GNodeArg(GNA_IN, "S55_Mul_shift", 0),
            GNodeArg(GNA_IN, "S55_Infos", 0)
        )
    );
    // Node expr_3 in_qs [-5.00<(u8-121.00)*0.04128413<5.53,-0.27<(u8-15.00)*0.01805458<4.33] out_qs [-0.55<(u8-16.00)*0.03460563<8.27]
    AddNode("S56_expr_3",
        Bindings(4,
            GNodeArg(GNA_IN, "S55_Output", 0),
            GNodeArg(GNA_IN, "S48_Output_0", 0),
            GNodeArg(GNA_OUT, "S56_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_63 inq ['-0.55<(u8-16.00)*0.03460563<8.27', '-0.55<(u8-16.00)*0.03460563<8.27'] outq ['-0.55<(u8-16.00)*0.03460563<8.27']
    AddNode("S57_CONCAT_0_63",
        Bindings(3,
            GNodeArg(GNA_IN, "S56_Output", 0),
            GNodeArg(GNA_IN, "S49_Output", 0),
            GNodeArg(GNA_OUT, "S57_Output", 0)
        )
    );
    // Node S60_CONV_2D_0_64_fusion inq -0.55<(u8-16.00)*0.03460563<8.27 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-13.00)*0.02177561<5.27 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S60_CONV_2D_0_64_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S57_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_31_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_37_add_y", 0),
            GNodeArg(GNA_OUT, "S60_Output", 0),
            GNodeArg(GNA_IN, "S60_Mul_scale", 0),
            GNodeArg(GNA_IN, "S60_Mul_shift", 0),
            GNodeArg(GNA_IN, "S60_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S63_CONV_2D_0_68_fusion inq -0.28<(u8-13.00)*0.02177561<5.27 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-12.00)*0.02274227<5.53 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S63_CONV_2D_0_68_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S60_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_32_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_38_add_y", 0),
            GNodeArg(GNA_OUT, "S63_Output", 0),
            GNodeArg(GNA_IN, "S63_Mul_scale", 0),
            GNodeArg(GNA_IN, "S63_Mul_shift", 0),
            GNodeArg(GNA_IN, "S63_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S66_CONV_2D_0_71_fusion inq -0.27<(u8-12.00)*0.02274227<5.53 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-14.00)*0.02034669<4.90 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S66_CONV_2D_0_71_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S63_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_33_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_39_add_y", 0),
            GNodeArg(GNA_OUT, "S66_Output", 0),
            GNodeArg(GNA_IN, "S66_Mul_scale", 0),
            GNodeArg(GNA_IN, "S66_Mul_shift", 0),
            GNodeArg(GNA_IN, "S66_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_71_split inq ['-0.28<(u8-14.00)*0.02034669<4.90'] outq ['-0.28<(u8-14.00)*0.02034669<4.90', '-0.28<(u8-14.00)*0.02034669<4.90']
    AddNode("S67_CONV_2D_0_71_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S66_Output", 0),
            GNodeArg(GNA_OUT, "S67_Output_0", 0),
            GNodeArg(GNA_OUT, "S67_Output_1", 0)
        )
    );
    // Node CONCAT_0_84_qin1 inq -0.28<(u8-14.00)*0.02034669<4.90 outq -0.57<(u8-15.00)*0.03805612<9.13
    AddNode("S68_CONCAT_0_84_qin1",
        Bindings(3,
            GNodeArg(GNA_IN, "S67_Output_1", 0),
            GNodeArg(GNA_OUT, "S68_Output", 0),
            GNodeArg(GNA_IN, "S68_Infos", 0)
        )
    );
    // Node S71_CONV_2D_0_74_fusion inq -0.28<(u8-14.00)*0.02034669<4.90 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-12.00)*0.02388575<5.80 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S71_CONV_2D_0_74_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S67_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_35_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_41_add_y", 0),
            GNodeArg(GNA_OUT, "S71_Output", 0),
            GNodeArg(GNA_IN, "S71_Mul_scale", 0),
            GNodeArg(GNA_IN, "S71_Mul_shift", 0),
            GNodeArg(GNA_IN, "S71_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S74_CONV_2D_0_77 inq -0.29<(u8-12.00)*0.02388575<5.80 weightsq chan<(u8-128.00)*chan<chan outq -5.91<(u8-129.00)*0.04579233<5.77 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S74_CONV_2D_0_77",
        Bindings(7,
            GNodeArg(GNA_IN, "S71_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_36_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_42_add_y", 0),
            GNodeArg(GNA_OUT, "S74_Output", 0),
            GNodeArg(GNA_IN, "S74_Mul_scale", 0),
            GNodeArg(GNA_IN, "S74_Mul_shift", 0),
            GNodeArg(GNA_IN, "S74_Infos", 0)
        )
    );
    // Node expr_4 in_qs [-5.91<(u8-129.00)*0.04579233<5.77,-0.28<(u8-14.00)*0.02034669<4.90] out_qs [-0.57<(u8-15.00)*0.03805612<9.13]
    AddNode("S75_expr_4",
        Bindings(4,
            GNodeArg(GNA_IN, "S74_Output", 0),
            GNodeArg(GNA_IN, "S67_Output_0", 0),
            GNodeArg(GNA_OUT, "S75_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_84 inq ['-0.57<(u8-15.00)*0.03805612<9.13', '-0.57<(u8-15.00)*0.03805612<9.13'] outq ['-0.57<(u8-15.00)*0.03805612<9.13']
    AddNode("S76_CONCAT_0_84",
        Bindings(3,
            GNodeArg(GNA_IN, "S75_Output", 0),
            GNodeArg(GNA_IN, "S68_Output", 0),
            GNodeArg(GNA_OUT, "S76_Output", 0)
        )
    );
    // Node S79_CONV_2D_0_85_fusion inq -0.57<(u8-15.00)*0.03805612<9.13 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-14.00)*0.02041324<4.92 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S79_CONV_2D_0_85_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S76_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_37_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_45_add_y", 0),
            GNodeArg(GNA_OUT, "S79_Output", 0),
            GNodeArg(GNA_IN, "S79_Mul_scale", 0),
            GNodeArg(GNA_IN, "S79_Mul_shift", 0),
            GNodeArg(GNA_IN, "S79_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S82_CONV_2D_0_88_fusion inq -0.29<(u8-14.00)*0.02041324<4.92 weightsq chan<(u8-128.00)*chan<chan outq -5.06<(u8-128.00)*0.03949709<5.02 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S82_CONV_2D_0_88_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S79_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_38_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_46_add_y", 0),
            GNodeArg(GNA_OUT, "S82_Output", 0),
            GNodeArg(GNA_IN, "S82_Mul_scale", 0),
            GNodeArg(GNA_IN, "S82_Mul_shift", 0),
            GNodeArg(GNA_IN, "S82_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node MAX_POOL_2D_0_91 inq -5.06<(u8-128.00)*0.03949709<5.02 forced outq -5.06<(u8-128.00)*0.03949709<5.02 forced
    AddNode("S83_MAX_POOL_2D_0_91",
        Bindings(3,
            GNodeArg(GNA_IN, "S82_Output", 0),
            GNodeArg(GNA_OUT, "S83_Output", 0),
            GNodeArg(GNA_IN, "S83_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_92 inq -5.06<(u8-128.00)*0.03949709<5.02 forced outq -5.06<(u8-128.00)*0.03949709<5.02 forced
    AddNode("S84_MAX_POOL_2D_0_92",
        Bindings(3,
            GNodeArg(GNA_IN, "S83_Output", 0),
            GNodeArg(GNA_OUT, "S84_Output", 0),
            GNodeArg(GNA_IN, "S84_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_93 inq -5.06<(u8-128.00)*0.03949709<5.02 forced outq -5.06<(u8-128.00)*0.03949709<5.02 forced
    AddNode("S85_MAX_POOL_2D_0_93",
        Bindings(3,
            GNodeArg(GNA_IN, "S84_Output", 0),
            GNodeArg(GNA_OUT, "S85_Output", 0),
            GNodeArg(GNA_IN, "S85_Infos", 0)
        )
    );
    // Node CONCAT_0_94 inq ['-5.06<(u8-128.00)*0.03949709<5.02 forced', '-5.06<(u8-128.00)*0.03949709<5.02 forced', '-5.06<(u8-128.00)*0.03949709<5.02 forced', '-5.06<(u8-128.00)*0.03949709<5.02 forced'] outq ['-5.06<(u8-128.00)*0.03949709<5.02 forced']
    AddNode("S86_CONCAT_0_94",
        Bindings(5,
            GNodeArg(GNA_IN, "S82_Output", 0),
            GNodeArg(GNA_IN, "S83_Output", 0),
            GNodeArg(GNA_IN, "S84_Output", 0),
            GNodeArg(GNA_IN, "S85_Output", 0),
            GNodeArg(GNA_OUT, "S86_Output", 0)
        )
    );
    // Node S89_CONV_2D_0_95_fusion inq -5.06<(u8-128.00)*0.03949709<5.02 forced weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-12.00)*0.02307397<5.61 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S89_CONV_2D_0_95_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S86_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_39_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_47_add_y", 0),
            GNodeArg(GNA_OUT, "S89_Output", 0),
            GNodeArg(GNA_IN, "S89_Mul_scale", 0),
            GNodeArg(GNA_IN, "S89_Mul_shift", 0),
            GNodeArg(GNA_IN, "S89_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S92_CONV_2D_0_98_fusion inq -0.28<(u8-12.00)*0.02307397<5.61 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-15.00)*0.01893161<4.54 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S92_CONV_2D_0_98_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S89_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_40_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_48_add_y", 0),
            GNodeArg(GNA_OUT, "S92_Output", 0),
            GNodeArg(GNA_IN, "S92_Mul_scale", 0),
            GNodeArg(GNA_IN, "S92_Mul_shift", 0),
            GNodeArg(GNA_IN, "S92_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node RESIZE_NN_0_101_qin0 inq -0.28<(u8-15.00)*0.01893161<4.54 outq -0.28<(u8-13.00)*0.02177561<5.27
    AddNode("S93_RESIZE_NN_0_101_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S92_Output", 0),
            GNodeArg(GNA_OUT, "S93_Output", 0),
            GNodeArg(GNA_IN, "S93_Infos", 0)
        )
    );
    // Node RESIZE_NN_0_101_trans_0 inq -0.28<(u8-13.00)*0.02177561<5.27 outq -0.28<(u8-13.00)*0.02177561<5.27
    AddNode("S94_RESIZE_NN_0_101_trans_0",
        Bindings(2,
            GNodeArg(GNA_IN, "S93_Output", 0),
            GNodeArg(GNA_OUT, "S94_Output", 0)
        )
    );
    // Node RESIZE_NN_0_101 inq -0.28<(u8-13.00)*0.02177561<5.27 outq -0.28<(u8-13.00)*0.02177561<5.27
    AddNode("S95_RESIZE_NN_0_101",
        Bindings(2,
            GNodeArg(GNA_IN, "S94_Output", 0),
            GNodeArg(GNA_OUT, "S95_Output", 0)
        )
    );
    // Node RESIZE_NN_0_101_trans inq -0.28<(u8-13.00)*0.02177561<5.27 outq -0.28<(u8-13.00)*0.02177561<5.27
    AddNode("S96_RESIZE_NN_0_101_trans",
        Bindings(2,
            GNodeArg(GNA_IN, "S95_Output", 0),
            GNodeArg(GNA_OUT, "S96_Output", 0)
        )
    );
    // Node CONCAT_0_102 inq ['-0.28<(u8-13.00)*0.02177561<5.27', '-0.28<(u8-13.00)*0.02177561<5.27'] outq ['-0.28<(u8-13.00)*0.02177561<5.27']
    AddNode("S97_CONCAT_0_102",
        Bindings(3,
            GNodeArg(GNA_IN, "S96_Output", 0),
            GNodeArg(GNA_IN, "S60_Output", 0),
            GNodeArg(GNA_OUT, "S97_Output", 0)
        )
    );
    // Node S100_CONV_2D_0_103_fusion inq -0.28<(u8-13.00)*0.02177561<5.27 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-13.00)*0.02174521<5.26 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S100_CONV_2D_0_103_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S97_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_41_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_49_add_y", 0),
            GNodeArg(GNA_OUT, "S100_Output", 0),
            GNodeArg(GNA_IN, "S100_Mul_scale", 0),
            GNodeArg(GNA_IN, "S100_Mul_shift", 0),
            GNodeArg(GNA_IN, "S100_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_103_split inq ['-0.28<(u8-13.00)*0.02174521<5.26'] outq ['-0.28<(u8-13.00)*0.02174521<5.26', '-0.28<(u8-13.00)*0.02174521<5.26']
    AddNode("S101_CONV_2D_0_103_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S100_Output", 0),
            GNodeArg(GNA_OUT, "S101_Output_0", 0),
            GNodeArg(GNA_OUT, "S101_Output_1", 0)
        )
    );
    // Node S104_CONV_2D_0_106_fusion inq -0.28<(u8-13.00)*0.02174521<5.26 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-13.00)*0.02064825<5.00 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S104_CONV_2D_0_106_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S101_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_43_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_51_add_y", 0),
            GNodeArg(GNA_OUT, "S104_Output", 0),
            GNodeArg(GNA_IN, "S104_Mul_scale", 0),
            GNodeArg(GNA_IN, "S104_Mul_shift", 0),
            GNodeArg(GNA_IN, "S104_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S107_CONV_2D_0_109_fusion inq -0.27<(u8-13.00)*0.02064825<5.00 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-13.00)*0.02174521<5.26 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S107_CONV_2D_0_109_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S104_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_44_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_52_add_y", 0),
            GNodeArg(GNA_OUT, "S107_Output", 0),
            GNodeArg(GNA_IN, "S107_Mul_scale", 0),
            GNodeArg(GNA_IN, "S107_Mul_shift", 0),
            GNodeArg(GNA_IN, "S107_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_115 inq ['-0.28<(u8-13.00)*0.02174521<5.26', '-0.28<(u8-13.00)*0.02174521<5.26'] outq ['-0.28<(u8-13.00)*0.02174521<5.26']
    AddNode("S108_CONCAT_0_115",
        Bindings(3,
            GNodeArg(GNA_IN, "S107_Output", 0),
            GNodeArg(GNA_IN, "S101_Output_1", 0),
            GNodeArg(GNA_OUT, "S108_Output", 0)
        )
    );
    // Node S111_CONV_2D_0_116_fusion inq -0.28<(u8-13.00)*0.02174521<5.26 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-14.00)*0.02046245<4.93 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S111_CONV_2D_0_116_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S108_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_45_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_53_add_y", 0),
            GNodeArg(GNA_OUT, "S111_Output", 0),
            GNodeArg(GNA_IN, "S111_Mul_scale", 0),
            GNodeArg(GNA_IN, "S111_Mul_shift", 0),
            GNodeArg(GNA_IN, "S111_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S114_CONV_2D_0_119_fusion inq -0.29<(u8-14.00)*0.02046245<4.93 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-12.00)*0.02255585<5.48 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S114_CONV_2D_0_119_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S111_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_46_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_54_add_y", 0),
            GNodeArg(GNA_OUT, "S114_Output", 0),
            GNodeArg(GNA_IN, "S114_Mul_scale", 0),
            GNodeArg(GNA_IN, "S114_Mul_shift", 0),
            GNodeArg(GNA_IN, "S114_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node RESIZE_NN_0_122_qin0 inq -0.27<(u8-12.00)*0.02255585<5.48 outq -0.28<(u8-12.00)*0.02365436<5.75
    AddNode("S115_RESIZE_NN_0_122_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S114_Output", 0),
            GNodeArg(GNA_OUT, "S115_Output", 0),
            GNodeArg(GNA_IN, "S115_Infos", 0)
        )
    );
    // Node RESIZE_NN_0_122_trans inq -0.28<(u8-12.00)*0.02365436<5.75 outq -0.28<(u8-12.00)*0.02365436<5.75
    AddNode("S116_RESIZE_NN_0_122_trans",
        Bindings(2,
            GNodeArg(GNA_IN, "S115_Output", 0),
            GNodeArg(GNA_OUT, "S116_Output", 0)
        )
    );
    // Node RESIZE_NN_0_122 inq -0.28<(u8-12.00)*0.02365436<5.75 outq -0.28<(u8-12.00)*0.02365436<5.75
    AddNode("S117_RESIZE_NN_0_122",
        Bindings(2,
            GNodeArg(GNA_IN, "S116_Output", 0),
            GNodeArg(GNA_OUT, "S117_Output", 0)
        )
    );
    // Node RESIZE_NN_0_122_trans_0 inq -0.28<(u8-12.00)*0.02365436<5.75 outq -0.28<(u8-12.00)*0.02365436<5.75
    AddNode("S118_RESIZE_NN_0_122_trans_0",
        Bindings(2,
            GNodeArg(GNA_IN, "S117_Output", 0),
            GNodeArg(GNA_OUT, "S118_Output", 0)
        )
    );
    // Node CONCAT_0_123 inq ['-0.28<(u8-12.00)*0.02365436<5.75', '-0.28<(u8-12.00)*0.02365436<5.75'] outq ['-0.28<(u8-12.00)*0.02365436<5.75']
    AddNode("S119_CONCAT_0_123",
        Bindings(3,
            GNodeArg(GNA_IN, "S118_Output", 0),
            GNodeArg(GNA_IN, "S41_Output", 0),
            GNodeArg(GNA_OUT, "S119_Output", 0)
        )
    );
    // Node S122_CONV_2D_0_124_fusion inq -0.28<(u8-12.00)*0.02365436<5.75 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-14.00)*0.01975346<4.76 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S122_CONV_2D_0_124_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S119_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_47_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_55_add_y", 0),
            GNodeArg(GNA_OUT, "S122_Output", 0),
            GNodeArg(GNA_IN, "S122_Mul_scale", 0),
            GNodeArg(GNA_IN, "S122_Mul_shift", 0),
            GNodeArg(GNA_IN, "S122_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_124_split inq ['-0.28<(u8-14.00)*0.01975346<4.76'] outq ['-0.28<(u8-14.00)*0.01975346<4.76', '-0.28<(u8-14.00)*0.01975346<4.76']
    AddNode("S123_CONV_2D_0_124_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S122_Output", 0),
            GNodeArg(GNA_OUT, "S123_Output_0", 0),
            GNodeArg(GNA_OUT, "S123_Output_1", 0)
        )
    );
    // Node CONCAT_0_136_qin1 inq -0.28<(u8-14.00)*0.01975346<4.76 outq -0.29<(u8-9.00)*0.03267019<8.04
    AddNode("S124_CONCAT_0_136_qin1",
        Bindings(3,
            GNodeArg(GNA_IN, "S123_Output_1", 0),
            GNodeArg(GNA_OUT, "S124_Output", 0),
            GNodeArg(GNA_IN, "S124_Infos", 0)
        )
    );
    // Node S127_CONV_2D_0_127_fusion inq -0.28<(u8-14.00)*0.01975346<4.76 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-14.00)*0.01936276<4.67 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S127_CONV_2D_0_127_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S123_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_49_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_57_add_y", 0),
            GNodeArg(GNA_OUT, "S127_Output", 0),
            GNodeArg(GNA_IN, "S127_Mul_scale", 0),
            GNodeArg(GNA_IN, "S127_Mul_shift", 0),
            GNodeArg(GNA_IN, "S127_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S130_CONV_2D_0_130_fusion inq -0.27<(u8-14.00)*0.01936276<4.67 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-9.00)*0.03267019<8.04 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S130_CONV_2D_0_130_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S127_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_50_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_58_add_y", 0),
            GNodeArg(GNA_OUT, "S130_Output", 0),
            GNodeArg(GNA_IN, "S130_Mul_scale", 0),
            GNodeArg(GNA_IN, "S130_Mul_shift", 0),
            GNodeArg(GNA_IN, "S130_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_136 inq ['-0.29<(u8-9.00)*0.03267019<8.04', '-0.29<(u8-9.00)*0.03267019<8.04'] outq ['-0.29<(u8-9.00)*0.03267019<8.04']
    AddNode("S131_CONCAT_0_136",
        Bindings(3,
            GNodeArg(GNA_IN, "S130_Output", 0),
            GNodeArg(GNA_IN, "S124_Output", 0),
            GNodeArg(GNA_OUT, "S131_Output", 0)
        )
    );
    // Node S134_CONV_2D_0_137_fusion inq -0.29<(u8-9.00)*0.03267019<8.04 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-13.00)*0.02101343<5.09 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S134_CONV_2D_0_137_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S131_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_53_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_61_add_y", 0),
            GNodeArg(GNA_OUT, "S134_Output", 0),
            GNodeArg(GNA_IN, "S134_Mul_scale", 0),
            GNodeArg(GNA_IN, "S134_Mul_shift", 0),
            GNodeArg(GNA_IN, "S134_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S137_CONV_2D_0_141_fusion inq -0.27<(u8-13.00)*0.02101343<5.09 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-12.00)*0.02255585<5.48 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S137_CONV_2D_0_141_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S134_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_61_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_69_add_y", 0),
            GNodeArg(GNA_OUT, "S137_Output", 0),
            GNodeArg(GNA_IN, "S137_Mul_scale", 0),
            GNodeArg(GNA_IN, "S137_Mul_shift", 0),
            GNodeArg(GNA_IN, "S137_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_144 inq ['-0.27<(u8-12.00)*0.02255585<5.48', '-0.27<(u8-12.00)*0.02255585<5.48'] outq ['-0.27<(u8-12.00)*0.02255585<5.48']
    AddNode("S138_CONCAT_0_144",
        Bindings(3,
            GNodeArg(GNA_IN, "S137_Output", 0),
            GNodeArg(GNA_IN, "S114_Output", 0),
            GNodeArg(GNA_OUT, "S138_Output", 0)
        )
    );
    // Node S141_CONV_2D_0_145_fusion inq -0.27<(u8-13.00)*0.02101343<5.09 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-12.00)*0.02239300<5.44 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S141_CONV_2D_0_145_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S134_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_64_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_72_add_y", 0),
            GNodeArg(GNA_OUT, "S141_Output", 0),
            GNodeArg(GNA_IN, "S141_Mul_scale", 0),
            GNodeArg(GNA_IN, "S141_Mul_shift", 0),
            GNodeArg(GNA_IN, "S141_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S144_CONV_2D_0_148_fusion inq -0.27<(u8-12.00)*0.02239300<5.44 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-9.00)*0.03092699<7.61 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S144_CONV_2D_0_148_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S141_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_68_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_76_add_y", 0),
            GNodeArg(GNA_OUT, "S144_Output", 0),
            GNodeArg(GNA_IN, "S144_Mul_scale", 0),
            GNodeArg(GNA_IN, "S144_Mul_shift", 0),
            GNodeArg(GNA_IN, "S144_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S147_CONV_2D_0_151_fusion inq -0.27<(u8-13.00)*0.02101343<5.09 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-9.00)*0.02990793<7.36 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S147_CONV_2D_0_151_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S134_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_67_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_75_add_y", 0),
            GNodeArg(GNA_OUT, "S147_Output", 0),
            GNodeArg(GNA_IN, "S147_Mul_scale", 0),
            GNodeArg(GNA_IN, "S147_Mul_shift", 0),
            GNodeArg(GNA_IN, "S147_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S150_CONV_2D_0_154_fusion inq -0.27<(u8-9.00)*0.02990793<7.36 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-7.00)*0.04156983<10.31 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S150_CONV_2D_0_154_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S147_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_71_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_79_add_y", 0),
            GNodeArg(GNA_OUT, "S150_Output", 0),
            GNodeArg(GNA_IN, "S150_Mul_scale", 0),
            GNodeArg(GNA_IN, "S150_Mul_shift", 0),
            GNodeArg(GNA_IN, "S150_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S153_CONV_2D_0_157_fusion inq -0.27<(u8-12.00)*0.02255585<5.48 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-13.00)*0.02083624<5.04 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S153_CONV_2D_0_157_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S138_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_72_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_80_add_y", 0),
            GNodeArg(GNA_OUT, "S153_Output", 0),
            GNodeArg(GNA_IN, "S153_Mul_scale", 0),
            GNodeArg(GNA_IN, "S153_Mul_shift", 0),
            GNodeArg(GNA_IN, "S153_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_157_split inq ['-0.27<(u8-13.00)*0.02083624<5.04'] outq ['-0.27<(u8-13.00)*0.02083624<5.04', '-0.27<(u8-13.00)*0.02083624<5.04']
    AddNode("S154_CONV_2D_0_157_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S153_Output", 0),
            GNodeArg(GNA_OUT, "S154_Output_0", 0),
            GNodeArg(GNA_OUT, "S154_Output_1", 0)
        )
    );
    // Node CONCAT_0_173_qin1 inq -0.27<(u8-13.00)*0.02083624<5.04 outq -0.28<(u8-11.00)*0.02538720<6.19
    AddNode("S155_CONCAT_0_173_qin1",
        Bindings(3,
            GNodeArg(GNA_IN, "S154_Output_1", 0),
            GNodeArg(GNA_OUT, "S155_Output", 0),
            GNodeArg(GNA_IN, "S155_Infos", 0)
        )
    );
    // Node S158_CONV_2D_0_163 inq -0.28<(u8-9.00)*0.03092699<7.61 weightsq chan<(u8-128.00)*chan<chan outq -9.81<(u8-124.00)*0.07908482<10.36 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S158_CONV_2D_0_163",
        Bindings(7,
            GNodeArg(GNA_IN, "S144_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_74_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_82_add_y", 0),
            GNodeArg(GNA_OUT, "S158_Output", 0),
            GNodeArg(GNA_IN, "S158_Mul_scale", 0),
            GNodeArg(GNA_IN, "S158_Mul_shift", 0),
            GNodeArg(GNA_IN, "S158_Infos", 0)
        )
    );
    // Node S161_CONV_2D_0_164 inq -0.29<(u8-7.00)*0.04156983<10.31 weightsq chan<(u8-128.00)*chan<chan outq -9.81<(u8-124.00)*0.07908482<10.36 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S161_CONV_2D_0_164",
        Bindings(7,
            GNodeArg(GNA_IN, "S150_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_77_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_85_add_y", 0),
            GNodeArg(GNA_OUT, "S161_Output", 0),
            GNodeArg(GNA_IN, "S161_Mul_scale", 0),
            GNodeArg(GNA_IN, "S161_Mul_shift", 0),
            GNodeArg(GNA_IN, "S161_Infos", 0)
        )
    );
    // Node CONCAT_0_165 inq ['-9.81<(u8-124.00)*0.07908482<10.36', '-9.81<(u8-124.00)*0.07908482<10.36'] outq ['-9.81<(u8-124.00)*0.07908482<10.36']
    AddNode("S162_CONCAT_0_165",
        Bindings(3,
            GNodeArg(GNA_IN, "S158_Output", 0),
            GNodeArg(GNA_IN, "S161_Output", 0),
            GNodeArg(GNA_OUT, "S162_Output", 0)
        )
    );
    // Node CONCAT_0_233_qin0 inq -9.81<(u8-124.00)*0.07908482<10.36 outq -14.09<(u8-154.00)*0.09148052<9.24
    AddNode("S164_CONCAT_0_233_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S162_Output", 0),
            GNodeArg(GNA_OUT, "S164_Output", 0),
            GNodeArg(GNA_IN, "S164_Infos", 0)
        )
    );
    // Node S167_CONV_2D_0_167_fusion inq -0.27<(u8-13.00)*0.02083624<5.04 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-13.00)*0.02074750<5.02 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S167_CONV_2D_0_167_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S154_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_78_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_86_add_y", 0),
            GNodeArg(GNA_OUT, "S167_Output", 0),
            GNodeArg(GNA_IN, "S167_Mul_scale", 0),
            GNodeArg(GNA_IN, "S167_Mul_shift", 0),
            GNodeArg(GNA_IN, "S167_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S170_CONV_2D_0_170_fusion inq -0.27<(u8-13.00)*0.02074750<5.02 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-11.00)*0.02538720<6.19 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S170_CONV_2D_0_170_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S167_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_79_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_87_add_y", 0),
            GNodeArg(GNA_OUT, "S170_Output", 0),
            GNodeArg(GNA_IN, "S170_Mul_scale", 0),
            GNodeArg(GNA_IN, "S170_Mul_shift", 0),
            GNodeArg(GNA_IN, "S170_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_173 inq ['-0.28<(u8-11.00)*0.02538720<6.19', '-0.28<(u8-11.00)*0.02538720<6.19'] outq ['-0.28<(u8-11.00)*0.02538720<6.19']
    AddNode("S171_CONCAT_0_173",
        Bindings(3,
            GNodeArg(GNA_IN, "S170_Output", 0),
            GNodeArg(GNA_IN, "S155_Output", 0),
            GNodeArg(GNA_OUT, "S171_Output", 0)
        )
    );
    // Node S174_CONV_2D_0_174_fusion inq -0.28<(u8-11.00)*0.02538720<6.19 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-12.00)*0.02269554<5.52 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S174_CONV_2D_0_174_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S171_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_80_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_88_add_y", 0),
            GNodeArg(GNA_OUT, "S174_Output", 0),
            GNodeArg(GNA_IN, "S174_Mul_scale", 0),
            GNodeArg(GNA_IN, "S174_Mul_shift", 0),
            GNodeArg(GNA_IN, "S174_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S177_CONV_2D_0_178_fusion inq -0.27<(u8-12.00)*0.02269554<5.52 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-15.00)*0.01893161<4.54 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S177_CONV_2D_0_178_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S174_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_81_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_89_add_y", 0),
            GNodeArg(GNA_OUT, "S177_Output", 0),
            GNodeArg(GNA_IN, "S177_Mul_scale", 0),
            GNodeArg(GNA_IN, "S177_Mul_shift", 0),
            GNodeArg(GNA_IN, "S177_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_181 inq ['-0.28<(u8-15.00)*0.01893161<4.54', '-0.28<(u8-15.00)*0.01893161<4.54'] outq ['-0.28<(u8-15.00)*0.01893161<4.54']
    AddNode("S178_CONCAT_0_181",
        Bindings(3,
            GNodeArg(GNA_IN, "S177_Output", 0),
            GNodeArg(GNA_IN, "S92_Output", 0),
            GNodeArg(GNA_OUT, "S178_Output", 0)
        )
    );
    // Node S181_CONV_2D_0_182_fusion inq -0.27<(u8-12.00)*0.02269554<5.52 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-12.00)*0.02229099<5.42 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S181_CONV_2D_0_182_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S174_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_82_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_90_add_y", 0),
            GNodeArg(GNA_OUT, "S181_Output", 0),
            GNodeArg(GNA_IN, "S181_Mul_scale", 0),
            GNodeArg(GNA_IN, "S181_Mul_shift", 0),
            GNodeArg(GNA_IN, "S181_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S184_CONV_2D_0_185_fusion inq -0.27<(u8-12.00)*0.02269554<5.52 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-10.00)*0.02883490<7.06 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S184_CONV_2D_0_185_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S174_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_83_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_91_add_y", 0),
            GNodeArg(GNA_OUT, "S184_Output", 0),
            GNodeArg(GNA_IN, "S184_Mul_scale", 0),
            GNodeArg(GNA_IN, "S184_Mul_shift", 0),
            GNodeArg(GNA_IN, "S184_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S187_CONV_2D_0_188_fusion inq -0.27<(u8-12.00)*0.02229099<5.42 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-8.00)*0.03600545<8.89 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S187_CONV_2D_0_188_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S181_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_84_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_92_add_y", 0),
            GNodeArg(GNA_OUT, "S187_Output", 0),
            GNodeArg(GNA_IN, "S187_Mul_scale", 0),
            GNodeArg(GNA_IN, "S187_Mul_shift", 0),
            GNodeArg(GNA_IN, "S187_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S190_CONV_2D_0_191_fusion inq -0.29<(u8-10.00)*0.02883490<7.06 weightsq chan<(u8-128.00)*chan<chan outq -0.30<(u8-8.00)*0.03694523<9.13 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S190_CONV_2D_0_191_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S184_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_85_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_93_add_y", 0),
            GNodeArg(GNA_OUT, "S190_Output", 0),
            GNodeArg(GNA_IN, "S190_Mul_scale", 0),
            GNodeArg(GNA_IN, "S190_Mul_shift", 0),
            GNodeArg(GNA_IN, "S190_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S193_CONV_2D_0_194_fusion inq -0.28<(u8-15.00)*0.01893161<4.54 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-16.00)*0.01726941<4.13 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S193_CONV_2D_0_194_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S178_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_86_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_94_add_y", 0),
            GNodeArg(GNA_OUT, "S193_Output", 0),
            GNodeArg(GNA_IN, "S193_Mul_scale", 0),
            GNodeArg(GNA_IN, "S193_Mul_shift", 0),
            GNodeArg(GNA_IN, "S193_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_194_split inq ['-0.28<(u8-16.00)*0.01726941<4.13'] outq ['-0.28<(u8-16.00)*0.01726941<4.13', '-0.28<(u8-16.00)*0.01726941<4.13']
    AddNode("S194_CONV_2D_0_194_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S193_Output", 0),
            GNodeArg(GNA_OUT, "S194_Output_0", 0),
            GNodeArg(GNA_OUT, "S194_Output_1", 0)
        )
    );
    // Node S197_CONV_2D_0_200 inq -0.29<(u8-8.00)*0.03600545<8.89 weightsq chan<(u8-128.00)*chan<chan outq -14.09<(u8-154.00)*0.09148052<9.24 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S197_CONV_2D_0_200",
        Bindings(7,
            GNodeArg(GNA_IN, "S187_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_88_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_96_add_y", 0),
            GNodeArg(GNA_OUT, "S197_Output", 0),
            GNodeArg(GNA_IN, "S197_Mul_scale", 0),
            GNodeArg(GNA_IN, "S197_Mul_shift", 0),
            GNodeArg(GNA_IN, "S197_Infos", 0)
        )
    );
    // Node S200_CONV_2D_0_201 inq -0.30<(u8-8.00)*0.03694523<9.13 weightsq chan<(u8-128.00)*chan<chan outq -14.09<(u8-154.00)*0.09148052<9.24 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S200_CONV_2D_0_201",
        Bindings(7,
            GNodeArg(GNA_IN, "S190_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_89_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_97_add_y", 0),
            GNodeArg(GNA_OUT, "S200_Output", 0),
            GNodeArg(GNA_IN, "S200_Mul_scale", 0),
            GNodeArg(GNA_IN, "S200_Mul_shift", 0),
            GNodeArg(GNA_IN, "S200_Infos", 0)
        )
    );
    // Node CONCAT_0_202 inq ['-14.09<(u8-154.00)*0.09148052<9.24', '-14.09<(u8-154.00)*0.09148052<9.24'] outq ['-14.09<(u8-154.00)*0.09148052<9.24']
    AddNode("S201_CONCAT_0_202",
        Bindings(3,
            GNodeArg(GNA_IN, "S197_Output", 0),
            GNodeArg(GNA_IN, "S200_Output", 0),
            GNodeArg(GNA_OUT, "S201_Output", 0)
        )
    );
    // Node S205_CONV_2D_0_204_fusion inq -0.28<(u8-16.00)*0.01726941<4.13 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-17.00)*0.01595643<3.80 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S205_CONV_2D_0_204_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S194_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_90_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_98_add_y", 0),
            GNodeArg(GNA_OUT, "S205_Output", 0),
            GNodeArg(GNA_IN, "S205_Mul_scale", 0),
            GNodeArg(GNA_IN, "S205_Mul_shift", 0),
            GNodeArg(GNA_IN, "S205_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S208_CONV_2D_0_207_fusion inq -0.27<(u8-17.00)*0.01595643<3.80 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-16.00)*0.01726941<4.13 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S208_CONV_2D_0_207_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S205_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_91_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_99_add_y", 0),
            GNodeArg(GNA_OUT, "S208_Output", 0),
            GNodeArg(GNA_IN, "S208_Mul_scale", 0),
            GNodeArg(GNA_IN, "S208_Mul_shift", 0),
            GNodeArg(GNA_IN, "S208_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_210 inq ['-0.28<(u8-16.00)*0.01726941<4.13', '-0.28<(u8-16.00)*0.01726941<4.13'] outq ['-0.28<(u8-16.00)*0.01726941<4.13']
    AddNode("S209_CONCAT_0_210",
        Bindings(3,
            GNodeArg(GNA_IN, "S208_Output", 0),
            GNodeArg(GNA_IN, "S194_Output_1", 0),
            GNodeArg(GNA_OUT, "S209_Output", 0)
        )
    );
    // Node S212_CONV_2D_0_211_fusion inq -0.28<(u8-16.00)*0.01726941<4.13 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-18.00)*0.01590776<3.77 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S212_CONV_2D_0_211_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S209_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_92_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_100_add_y", 0),
            GNodeArg(GNA_OUT, "S212_Output", 0),
            GNodeArg(GNA_IN, "S212_Mul_scale", 0),
            GNodeArg(GNA_IN, "S212_Mul_shift", 0),
            GNodeArg(GNA_IN, "S212_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S215_CONV_2D_0_214_fusion inq -0.29<(u8-18.00)*0.01590776<3.77 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-16.00)*0.01785398<4.27 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S215_CONV_2D_0_214_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S212_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_93_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_101_add_y", 0),
            GNodeArg(GNA_OUT, "S215_Output", 0),
            GNodeArg(GNA_IN, "S215_Mul_scale", 0),
            GNodeArg(GNA_IN, "S215_Mul_shift", 0),
            GNodeArg(GNA_IN, "S215_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S218_CONV_2D_0_217_fusion inq -0.29<(u8-18.00)*0.01590776<3.77 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-24.00)*0.01164458<2.69 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S218_CONV_2D_0_217_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S212_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_94_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_102_add_y", 0),
            GNodeArg(GNA_OUT, "S218_Output", 0),
            GNodeArg(GNA_IN, "S218_Mul_scale", 0),
            GNodeArg(GNA_IN, "S218_Mul_shift", 0),
            GNodeArg(GNA_IN, "S218_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S221_CONV_2D_0_220_fusion inq -0.29<(u8-16.00)*0.01785398<4.27 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-11.00)*0.02455880<5.99 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S221_CONV_2D_0_220_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S215_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_95_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_103_add_y", 0),
            GNodeArg(GNA_OUT, "S221_Output", 0),
            GNodeArg(GNA_IN, "S221_Mul_scale", 0),
            GNodeArg(GNA_IN, "S221_Mul_shift", 0),
            GNodeArg(GNA_IN, "S221_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S224_CONV_2D_0_223_fusion inq -0.28<(u8-24.00)*0.01164458<2.69 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-25.00)*0.01099040<2.53 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S224_CONV_2D_0_223_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S218_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_96_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_104_add_y", 0),
            GNodeArg(GNA_OUT, "S224_Output", 0),
            GNodeArg(GNA_IN, "S224_Mul_scale", 0),
            GNodeArg(GNA_IN, "S224_Mul_shift", 0),
            GNodeArg(GNA_IN, "S224_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S227_CONV_2D_0_226 inq -0.27<(u8-11.00)*0.02455880<5.99 weightsq chan<(u8-128.00)*chan<chan outq -12.85<(u8-255.00)*0.05040178<0.00 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S227_CONV_2D_0_226",
        Bindings(7,
            GNodeArg(GNA_IN, "S221_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_97_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_105_add_y", 0),
            GNodeArg(GNA_OUT, "S227_Output", 0),
            GNodeArg(GNA_IN, "S227_Mul_scale", 0),
            GNodeArg(GNA_IN, "S227_Mul_shift", 0),
            GNodeArg(GNA_IN, "S227_Infos", 0)
        )
    );
    // Node S230_CONV_2D_0_227 inq -0.27<(u8-25.00)*0.01099040<2.53 weightsq chan<(u8-128.00)*chan<chan outq -12.85<(u8-255.00)*0.05040178<0.00 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S230_CONV_2D_0_227",
        Bindings(7,
            GNodeArg(GNA_IN, "S224_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_98_", 0),
            GNodeArg(GNA_IN, "Model_37_tf_math_add_106_add_y", 0),
            GNodeArg(GNA_OUT, "S230_Output", 0),
            GNodeArg(GNA_IN, "S230_Mul_scale", 0),
            GNodeArg(GNA_IN, "S230_Mul_shift", 0),
            GNodeArg(GNA_IN, "S230_Infos", 0)
        )
    );
    // Node CONCAT_0_228 inq ['-12.85<(u8-255.00)*0.05040178<0.00', '-12.85<(u8-255.00)*0.05040178<0.00'] outq ['-12.85<(u8-255.00)*0.05040178<0.00']
    AddNode("S231_CONCAT_0_228",
        Bindings(3,
            GNodeArg(GNA_IN, "S227_Output", 0),
            GNodeArg(GNA_IN, "S230_Output", 0),
            GNodeArg(GNA_OUT, "S231_Output", 0)
        )
    );
    // Node CONCAT_0_233_qin2 inq -12.85<(u8-255.00)*0.05040178<0.00 outq -14.09<(u8-154.00)*0.09148052<9.24
    AddNode("S233_CONCAT_0_233_qin2",
        Bindings(3,
            GNodeArg(GNA_IN, "S231_Output", 0),
            GNodeArg(GNA_OUT, "S233_Output", 0),
            GNodeArg(GNA_IN, "S233_Infos", 0)
        )
    );
    // Node STRIDED_SLICE_0_234_split inq ['-14.09<(u8-154.00)*0.09148052<9.24'] outq ['-14.09<(u8-154.00)*0.09148052<9.24', '-14.09<(u8-154.00)*0.09148052<9.24']
    AddNode("S235_STRIDED_SLICE_0_234_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S234_Output", 0),
            GNodeArg(GNA_OUT, "S235_Output_0", 0),
            GNodeArg(GNA_OUT, "S235_Output_1", 0)
        )
    );
    // Node SOFTMAX_0_237_qin0 inq -14.09<(u8-154.00)*0.09148052<9.24 outq -16.00<(i8-0.00)*0.12500000<15.88 forced
    AddNode("S237_SOFTMAX_0_237_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S235_Output_0", 0),
            GNodeArg(GNA_OUT, "S237_Output", 0),
            GNodeArg(GNA_IN, "S237_Infos", 0)
        )
    );
    // Node SOFTMAX_0_237 inq -16.00<(i8-0.00)*0.12500000<15.88 forced outq -1.00<(i16-0.00)*0.00003052<1.00
    AddNode("S238_SOFTMAX_0_237",
        Bindings(3,
            GNodeArg(GNA_IN, "S237_Output", 0),
            GNodeArg(GNA_OUT, "S238_Output", 0),
            GNodeArg(GNA_IN, "S238_Infos", 0)
        )
    );
    // Node CONV_2D_0_240_qin0 inq -1.00<(i16-0.00)*0.00003052<1.00 outq 0.00<(u8-0.00)*0.00309831<0.79
    AddNode("S239_CONV_2D_0_240_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S238_Output", 0),
            GNodeArg(GNA_OUT, "S239_Output", 0),
            GNodeArg(GNA_IN, "S239_Infos", 0)
        )
    );
    // Node CONV_2D_0_240_trans inq 0.00<(u8-0.00)*0.00309831<0.79 outq 0.00<(u8-0.00)*0.00309831<0.79
    AddNode("S240_CONV_2D_0_240_trans",
        Bindings(2,
            GNodeArg(GNA_IN, "S239_Output", 0),
            GNodeArg(GNA_OUT, "S240_Output", 0)
        )
    );
    // Node LOGISTIC_0_243_qin0 inq -14.09<(u8-154.00)*0.09148052<9.24 outq -8.06<(u8-128.00)*0.06299213<8.00 forced
    AddNode("S241_LOGISTIC_0_243_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S235_Output_1", 0),
            GNodeArg(GNA_OUT, "S241_Output", 0),
            GNodeArg(GNA_IN, "S241_Infos", 0)
        )
    );
    // Node LOGISTIC_0_243 inq -8.06<(u8-128.00)*0.06299213<8.00 forced outq 0.00<(u8-0.00)*0.00392157<1.00
    AddNode("S242_LOGISTIC_0_243",
        Bindings(4,
            GNodeArg(GNA_IN, "S241_Output", 0),
            GNodeArg(GNA_OUT, "S242_Output", 0),
            GNodeArg(GNA_IN, "S242_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node output_2_qin0 inq 0.00<(u8-0.00)*0.00392157<1.00 outq -1.01<(u8-128.00)*0.00787402<1.00 forced
    AddNode("S243_output_2_qin0",
        Bindings(3,
            GNodeArg(GNA_IN, "S242_Output", 0),
            GNodeArg(GNA_OUT, "Output_2", 0),
            GNodeArg(GNA_IN, "S243_Infos", 0)
        )
    );
    // Node S247_CONV_2D_0_240 inq 0.00<(u8-0.00)*0.00309831<0.79 weightsq -15.00<(u8-128.00)*0.11811024<15.00 outq 0.00<(u8-0.00)*0.04870597<12.42 biasesq -785854.00<(i32-0.00)*0.00036594<785854.00
    AddNode("S247_CONV_2D_0_240",
        Bindings(7,
            GNodeArg(GNA_IN, "S240_Output", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_99__15e5e2e5_0", 0),
            GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_99_", 0),
            GNodeArg(GNA_OUT, "S247_Output", 0),
            GNodeArg(GNA_IN, "S247_Mul_scale", 0),
            GNodeArg(GNA_IN, "S247_Mul_shift", 0),
            GNodeArg(GNA_IN, "S247_Infos", 0)
        )
    );
    // Node expr_1 in_qs [-31.75<(i8-0.00)*0.24803150<31.50,0.00<(u8-0.00)*0.04870597<12.42,-31.75<(i8-0.00)*0.24803150<31.50,0.00<(u8-0.00)*0.04870597<12.42] out_qs [-0.50<(i8--124.00)*0.12624632<31.69,-0.50<(i8--124.00)*0.12624632<31.69]
    AddNode("S255_expr_1",
        Bindings(6,
            GNodeArg(GNA_IN, "Model_37_6790", 0),
            GNodeArg(GNA_IN, "S249_Output_0", 0),
            GNodeArg(GNA_IN, "Model_37_6790_1", 0),
            GNodeArg(GNA_IN, "S249_Output_1", 0),
            GNodeArg(GNA_OUT, "S255_Output_0", 0),
            GNodeArg(GNA_OUT, "S255_Output_1", 0)
        )
    );
    // Node expr_64 in_qs [-32.25<(i8-0.00)*0.25196850<32.00,-0.50<(i8--124.00)*0.12624632<31.69] out_qs [-531.12<(i8-0.00)*4.14939484<526.97 forced]
    AddNode("S257_expr_64",
        Bindings(3,
            GNodeArg(GNA_IN, "Model_37_tf_math_multiply_201_", 0),
            GNodeArg(GNA_IN, "S256_Output", 0),
            GNodeArg(GNA_OUT, "Output_1", 0)
        )
    );
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    best_float32Model(128000, 300000, 8000000, 64*1024*1024);
    GenerateTilingCode();
    return 0;
}

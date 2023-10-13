#ifndef BEST_FLOAT32_BASIC_KERNELS_H
#define BEST_FLOAT32_BASIC_KERNELS_H
#include "at_api.h"
#include "math_funcs.h"
#include "at_api.h"
#include "CNN_BasicKernels_SQ8.h"

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_0_in_0;
    unsigned char *__restrict__  expr_0_in_1;
    unsigned char *__restrict__  expr_0_out_0;
} s18_kernel_args_t;

typedef struct {
    unsigned int I0;
    signed char *__restrict__  expr_1_in_0;
    unsigned char *__restrict__  expr_1_in_1;
    signed char *__restrict__  expr_1_in_2;
    unsigned char *__restrict__  expr_1_in_3;
    signed char *__restrict__  expr_1_out_0;
    signed char *__restrict__  expr_1_out_1;
} s255_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_2_in_0;
    unsigned char *__restrict__  expr_2_in_1;
    unsigned char *__restrict__  expr_2_out_0;
} s37_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_3_in_0;
    unsigned char *__restrict__  expr_3_in_1;
    unsigned char *__restrict__  expr_3_out_0;
} s56_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_4_in_0;
    unsigned char *__restrict__  expr_4_in_1;
    unsigned char *__restrict__  expr_4_out_0;
} s75_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    signed char *__restrict__  expr_64_in_0;
    signed char *__restrict__  expr_64_in_1;
    signed char *__restrict__  expr_64_out_0;
} s257_kernel_args_t;

typedef struct {
    unsigned char *__restrict__  expr_44_in_0;
    unsigned char *__restrict__  expr_44_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_44_args_t;

typedef struct {
    unsigned char *__restrict__  expr_55_in_0;
    unsigned char *__restrict__  expr_55_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_55_args_t;

typedef struct {
    unsigned char *__restrict__  expr_13_in_0;
    unsigned char *__restrict__  expr_13_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_13_args_t;

typedef struct {
    unsigned char *__restrict__  expr_23_in_0;
    unsigned char *__restrict__  expr_23_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_23_args_t;

typedef struct {
    unsigned char *__restrict__  expr_42_in_0;
    unsigned char *__restrict__  expr_42_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_42_args_t;

typedef struct {
    unsigned char *__restrict__  expr_43_in_0;
    unsigned char *__restrict__  expr_43_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_43_args_t;

typedef struct {
    unsigned char *__restrict__  expr_45_in_0;
    unsigned char *__restrict__  expr_45_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_45_args_t;

typedef struct {
    unsigned char *__restrict__  expr_46_in_0;
    unsigned char *__restrict__  expr_46_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_46_args_t;

typedef struct {
    unsigned char *__restrict__  expr_48_in_0;
    unsigned char *__restrict__  expr_48_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_48_args_t;

typedef struct {
    unsigned char *__restrict__  expr_49_in_0;
    unsigned char *__restrict__  expr_49_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_49_args_t;

typedef struct {
    unsigned char *__restrict__  expr_50_in_0;
    unsigned char *__restrict__  expr_50_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_50_args_t;

typedef struct {
    unsigned char *__restrict__  expr_51_in_0;
    unsigned char *__restrict__  expr_51_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_51_args_t;

typedef struct {
    unsigned char *__restrict__  expr_53_in_0;
    unsigned char *__restrict__  expr_53_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_53_args_t;

typedef struct {
    unsigned char *__restrict__  expr_54_in_0;
    unsigned char *__restrict__  expr_54_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_54_args_t;

typedef struct {
    unsigned char *__restrict__  expr_56_in_0;
    unsigned char *__restrict__  expr_56_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_56_args_t;

typedef struct {
    unsigned char *__restrict__  expr_57_in_0;
    unsigned char *__restrict__  expr_57_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_57_args_t;

typedef struct {
    unsigned char *__restrict__  expr_59_in_0;
    unsigned char *__restrict__  expr_59_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_59_args_t;

typedef struct {
    unsigned char *__restrict__  expr_60_in_0;
    unsigned char *__restrict__  expr_60_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_60_args_t;

typedef struct {
    unsigned char *__restrict__  expr_61_in_0;
    unsigned char *__restrict__  expr_61_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_61_args_t;

typedef struct {
    unsigned char *__restrict__  expr_62_in_0;
    unsigned char *__restrict__  expr_62_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_62_args_t;

typedef struct {
    unsigned char *__restrict__  expr_5_in_0;
    unsigned char *__restrict__  expr_5_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_5_args_t;

typedef struct {
    unsigned char *__restrict__  expr_6_in_0;
    unsigned char *__restrict__  expr_6_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_6_args_t;

typedef struct {
    unsigned char *__restrict__  expr_7_in_0;
    unsigned char *__restrict__  expr_7_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_7_args_t;

typedef struct {
    unsigned char *__restrict__  expr_9_in_0;
    unsigned char *__restrict__  expr_9_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_9_args_t;

typedef struct {
    unsigned char *__restrict__  expr_10_in_0;
    unsigned char *__restrict__  expr_10_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_10_args_t;

typedef struct {
    unsigned char *__restrict__  expr_11_in_0;
    unsigned char *__restrict__  expr_11_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_11_args_t;

typedef struct {
    unsigned char *__restrict__  expr_12_in_0;
    unsigned char *__restrict__  expr_12_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_12_args_t;

typedef struct {
    unsigned char *__restrict__  expr_14_in_0;
    unsigned char *__restrict__  expr_14_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_14_args_t;

typedef struct {
    unsigned char *__restrict__  expr_16_in_0;
    unsigned char *__restrict__  expr_16_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_16_args_t;

typedef struct {
    unsigned char *__restrict__  expr_17_in_0;
    unsigned char *__restrict__  expr_17_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_17_args_t;

typedef struct {
    unsigned char *__restrict__  expr_18_in_0;
    unsigned char *__restrict__  expr_18_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_18_args_t;

typedef struct {
    unsigned char *__restrict__  expr_19_in_0;
    unsigned char *__restrict__  expr_19_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_19_args_t;

typedef struct {
    unsigned char *__restrict__  expr_20_in_0;
    unsigned char *__restrict__  expr_20_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_20_args_t;

typedef struct {
    unsigned char *__restrict__  expr_21_in_0;
    unsigned char *__restrict__  expr_21_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_21_args_t;

typedef struct {
    unsigned char *__restrict__  expr_22_in_0;
    unsigned char *__restrict__  expr_22_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_22_args_t;

typedef struct {
    unsigned char *__restrict__  expr_25_in_0;
    unsigned char *__restrict__  expr_25_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_25_args_t;

typedef struct {
    unsigned char *__restrict__  expr_26_in_0;
    unsigned char *__restrict__  expr_26_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_26_args_t;

typedef struct {
    unsigned char *__restrict__  expr_27_in_0;
    unsigned char *__restrict__  expr_27_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_27_args_t;

typedef struct {
    unsigned char *__restrict__  expr_28_in_0;
    unsigned char *__restrict__  expr_28_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_28_args_t;

typedef struct {
    unsigned char *__restrict__  expr_29_in_0;
    unsigned char *__restrict__  expr_29_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_29_args_t;

typedef struct {
    unsigned char *__restrict__  expr_30_in_0;
    unsigned char *__restrict__  expr_30_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_30_args_t;

typedef struct {
    unsigned char *__restrict__  expr_31_in_0;
    unsigned char *__restrict__  expr_31_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_31_args_t;

typedef struct {
    unsigned char *__restrict__  expr_32_in_0;
    unsigned char *__restrict__  expr_32_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_32_args_t;

typedef struct {
    unsigned char *__restrict__  expr_33_in_0;
    unsigned char *__restrict__  expr_33_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_33_args_t;

typedef struct {
    unsigned char *__restrict__  expr_35_in_0;
    unsigned char *__restrict__  expr_35_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_35_args_t;

typedef struct {
    unsigned char *__restrict__  expr_36_in_0;
    unsigned char *__restrict__  expr_36_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_36_args_t;

typedef struct {
    unsigned char *__restrict__  expr_37_in_0;
    unsigned char *__restrict__  expr_37_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_37_args_t;

typedef struct {
    unsigned char *__restrict__  expr_38_in_0;
    unsigned char *__restrict__  expr_38_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_38_args_t;

typedef struct {
    unsigned char *__restrict__  expr_39_in_0;
    unsigned char *__restrict__  expr_39_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_39_args_t;

typedef struct {
    unsigned char *__restrict__  expr_40_in_0;
    unsigned char *__restrict__  expr_40_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_40_args_t;

typedef struct {
    unsigned char *__restrict__  expr_41_in_0;
    unsigned char *__restrict__  expr_41_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_41_args_t;


void s18_kernel(s18_kernel_args_t *Args);

void s255_kernel(s255_kernel_args_t *Args);

void s37_kernel(s37_kernel_args_t *Args);

void s56_kernel(s56_kernel_args_t *Args);

void s75_kernel(s75_kernel_args_t *Args);

void s257_kernel(s257_kernel_args_t *Args);

void expr_44(expr_44_args_t *Args);

void expr_55(expr_55_args_t *Args);

void expr_13(expr_13_args_t *Args);

void expr_23(expr_23_args_t *Args);

void expr_42(expr_42_args_t *Args);

void expr_43(expr_43_args_t *Args);

void expr_45(expr_45_args_t *Args);

void expr_46(expr_46_args_t *Args);

void expr_48(expr_48_args_t *Args);

void expr_49(expr_49_args_t *Args);

void expr_50(expr_50_args_t *Args);

void expr_51(expr_51_args_t *Args);

void expr_53(expr_53_args_t *Args);

void expr_54(expr_54_args_t *Args);

void expr_56(expr_56_args_t *Args);

void expr_57(expr_57_args_t *Args);

void expr_59(expr_59_args_t *Args);

void expr_60(expr_60_args_t *Args);

void expr_61(expr_61_args_t *Args);

void expr_62(expr_62_args_t *Args);

void expr_5(expr_5_args_t *Args);

void expr_6(expr_6_args_t *Args);

void expr_7(expr_7_args_t *Args);

void expr_9(expr_9_args_t *Args);

void expr_10(expr_10_args_t *Args);

void expr_11(expr_11_args_t *Args);

void expr_12(expr_12_args_t *Args);

void expr_14(expr_14_args_t *Args);

void expr_16(expr_16_args_t *Args);

void expr_17(expr_17_args_t *Args);

void expr_18(expr_18_args_t *Args);

void expr_19(expr_19_args_t *Args);

void expr_20(expr_20_args_t *Args);

void expr_21(expr_21_args_t *Args);

void expr_22(expr_22_args_t *Args);

void expr_25(expr_25_args_t *Args);

void expr_26(expr_26_args_t *Args);

void expr_27(expr_27_args_t *Args);

void expr_28(expr_28_args_t *Args);

void expr_29(expr_29_args_t *Args);

void expr_30(expr_30_args_t *Args);

void expr_31(expr_31_args_t *Args);

void expr_32(expr_32_args_t *Args);

void expr_33(expr_33_args_t *Args);

void expr_35(expr_35_args_t *Args);

void expr_36(expr_36_args_t *Args);

void expr_37(expr_37_args_t *Args);

void expr_38(expr_38_args_t *Args);

void expr_39(expr_39_args_t *Args);

void expr_40(expr_40_args_t *Args);

void expr_41(expr_41_args_t *Args);


#endif // BEST_FLOAT32_BASIC_KERNELS_H
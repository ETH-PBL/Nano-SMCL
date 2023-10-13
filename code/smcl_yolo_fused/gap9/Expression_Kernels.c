#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wpointer-sign"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "Expression_Kernels.h"

static int CoreCountDynamic = 1;
static int ActiveCore = gap_ncore();

static inline unsigned int __attribute__((always_inline)) ChunkSize(unsigned int X)

{
	unsigned int NCore;
	unsigned int Log2Core;
	unsigned int Chunk;

	if (CoreCountDynamic) NCore = ActiveCore; else NCore = gap_ncore();
	Log2Core = gap_fl1(NCore);
	Chunk = (X>>Log2Core) + ((X&(NCore-1))!=0);
	return Chunk;
}

#ifndef AT_NORM
#define AT_NORM(x, n)   gap_roundnorm_reg((x), (n))
#endif
#define ATLShift(x, n)  ((x) << (n))

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s18_kernel(s18_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (64, 64, 8) (uint8-150) 19.799 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (64, 64, 8) (uint8-6) 11.097 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (64, 64, 8) (uint8-12) 5.937 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 8) var shapes:
    // expr_0_out_0: (64, 64, 8) expr_0_in_1: (64, 64, 8) expr_0_in_0: (64, 64,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-6) 11.097 Q8 expr_0_in_0: (uint8-150)
        // 19.799 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [150]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_0_in_0, int32), [158]), [1]), [47400]), SigmoidLUTTable)), [8]), [228]), [14])), [239]), [8]), [-6]), 0, 255), uint8)
        // ADD_0_20 scale arg 0 (no zp adj) - (uint8-6) 11.097 Q8 -> (int32-6) 11.097 Q8
        int _SYMBOL_Cast12 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-6) 22.194 Q9 -> (uint8-12) 5.937 Q7
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast12+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(150))*SigmoidTable((((((int)expr_0_in_0[i0])*(158))<<((unsigned char)1))-(47400)), SigmoidLUTTable)), (8))*(228)), ((unsigned char)14)))*(239)), ((unsigned char)8))-(-6))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s255_kernel(s255_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    signed char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (2, 1, 1344) int8 31.748 Q7
    unsigned char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (2, 1, 1344) uint8 12.469 Q8
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (2, 1, 1344) int8 31.748 Q7
    unsigned char *__restrict__  expr_1_in_3 = Args->expr_1_in_3; // (2, 1, 1344) uint8 12.469 Q8
    signed char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (2, 1, 1344) (int8--124) 16.160 Q7
    signed char *__restrict__  expr_1_out_1 = Args->expr_1_out_1; // (2, 1, 1344) (int8--124) 16.160 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (2, 1, 1344) var shapes:
    // inter_SUB_0_245: (2, 1, 1344) expr_1_in_0: (2, 1, 1344) expr_1_in_1: (2,
    // 1, 1344) inter_ADD_0_247: (2, 1, 1344) expr_1_in_3: (2, 1, 1344)
    // expr_1_in_2: (2, 1, 1344) expr_1_out_0: (2, 1, 1344) expr_1_out_1: (2,
    // 1, 1344)
    // Iteration reduced to spaces ((0, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 2),)
    // Paralelized space (0, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_1_in_0: int8 31.748 Q7 expr_1_in_1: uint8 12.469 Q8
        // inter_SUB_0_245 = Sub(Norm(Mul(Cast(expr_1_in_0, int32), [163]), [5]), Cast(expr_1_in_1, int32))
        // SUB_0_245 scale arg 1 (equalize zp adj) - uint8 12.469 Q8 -> int32 12.469 Q8
        int _SYMBOL_Cast197 = ((int)expr_1_in_1[i0]);
        int inter_SUB_0_245 = (gap_roundnorm_reg((((int)expr_1_in_0[i0])*(163)), ((unsigned char)5))-_SYMBOL_Cast197);
        // inputs expr_1_in_3: uint8 12.469 Q8 expr_1_in_2: int8 31.748 Q7
        // inter_ADD_0_247 = Add(Cast(expr_1_in_3, int32), Norm(Mul(Cast(expr_1_in_2, int32), [163]), [5]))
        // ADD_0_247 scale arg 0 (equalize zp adj) - uint8 12.469 Q8 -> int32 12.469 Q8
        int _SYMBOL_Cast198 = ((int)expr_1_in_3[i0]);
        int inter_ADD_0_247 = (_SYMBOL_Cast198+gap_roundnorm_reg((((int)expr_1_in_2[i0])*(163)), ((unsigned char)5)));
        // inputs inter_ADD_0_247: int32 24.937 Q9 inter_SUB_0_245: int32
        // 24.937 Q9
        // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Sub(inter_ADD_0_247, inter_SUB_0_245), [198]), [9]), [124]), -128, 127), int8)
        // scale clip and cast - int32 49.875 Q10 -> (int8--124) 16.160 Q7
        expr_1_out_0[i0] = ((signed char)gap_clip(((gap_roundnorm_reg(((inter_ADD_0_247-inter_SUB_0_245)*(198)), ((unsigned char)9))-(124))), (((signed char)7))));
        // inputs inter_SUB_0_245: int32 24.937 Q9 inter_ADD_0_247: int32
        // 24.937 Q9
        // expr_1_out_1 = Cast(Clip(Sub(Norm(Mul(Mul(Add(inter_SUB_0_245, inter_ADD_0_247), [1]), [198]), [10]), [124]), -128, 127), int8)
        // scale clip and cast - int32 24.937 Q10 -> (int8--124) 16.160 Q7
        expr_1_out_1[i0] = ((signed char)gap_clip(((gap_roundnorm_reg((((inter_SUB_0_245+inter_ADD_0_247)*(1))*(198)), ((unsigned char)10))-(124))), (((signed char)7))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (32, 32, 16) (uint8-106) 12.028 Q8
    unsigned char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (32, 32, 16) (uint8-9) 7.552 Q8
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (32, 32, 16) (uint8-16) 4.378 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 16) var shapes:
    // expr_2_out_0: (32, 32, 16) expr_2_in_1: (32, 32, 16) expr_2_in_0: (32,
    // 32, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_2_in_1: (uint8-9) 7.552 Q8 expr_2_in_0: (uint8-106)
        // 12.028 Q8
        // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_2_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_2_in_0, int32), [106]), SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [192]), [20352]), SigmoidLUTTable)), [8]), [204]), [14])), [221]), [8]), [-8]), 0, 255), uint8)
        // ADD_0_38 scale arg 0 (no zp adj) - (uint8-9) 7.552 Q8 -> (int32-9) 7.552 Q8
        int _SYMBOL_Cast28 = ((int)expr_2_in_1[i0]);
        // scale clip and cast - (int32-9) 15.104 Q9 -> (uint8-16) 4.378 Q7
        expr_2_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast28+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_2_in_0[i0])-(106))*SigmoidTable(((((int)expr_2_in_0[i0])*(192))-(20352)), SigmoidLUTTable)), (8))*(204)), ((unsigned char)14)))*(221)), ((unsigned char)8))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s56_kernel(s56_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (16, 16, 28) (uint8-121) 10.569 Q8
    unsigned char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (16, 16, 28) (uint8-15) 4.622 Q8
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (16, 16, 28) (uint8-16) 4.430 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_3_out_0: (16, 16, 28) expr_3_in_1: (16, 16, 28) expr_3_in_0: (16,
    // 16, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_3_in_1: (uint8-15) 4.622 Q8 expr_3_in_0: (uint8-121)
        // 10.569 Q8
        // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_3_in_1, int32), [224]), [2]), Norm(Mul(Sub(Cast(expr_3_in_0, int32), [121]), SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [169]), [20449]), SigmoidLUTTable)), [8])), [153]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - (int32-840) 1352.798 Q22 -> (uint8-16) 4.430 Q7
        expr_3_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_3_in_1[i0])*(224)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_3_in_0[i0])-(121))*SigmoidTable(((((int)expr_3_in_0[i0])*(169))-(20449)), SigmoidLUTTable)), (8)))*(153)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s75_kernel(s75_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (8, 8, 52)  (uint8-129) 11.723 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (8, 8, 52)  (uint8-14) 5.209 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (8, 8, 52)  (uint8-15) 4.871 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 52) var shapes:
    // expr_4_out_0: (8, 8, 52) expr_4_in_1: (8, 8, 52) expr_4_in_0: (8, 8, 52)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-14) 5.209 Q8 expr_4_in_0: (uint8-129)
        // 11.723 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_4_in_1, int32), [227]), [2]), Norm(Mul(Sub(Cast(expr_4_in_0, int32), [129]), SigmoidLUT(Sub(Mul(Cast(expr_4_in_0, int32), [188]), [24252]), SigmoidLUTTable)), [8])), [154]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - (int32-795) 1500.523 Q22 -> (uint8-15) 4.871 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_4_in_1[i0])*(227)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(129))*SigmoidTable(((((int)expr_4_in_0[i0])*(188))-(24252)), SigmoidLUTTable)), (8)))*(154)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 2 external iteration spaces
void s257_kernel(s257_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    signed char *__restrict__  expr_64_in_0 = Args->expr_64_in_0; // (1, 1, 1344) int8 32.252 Q7
    signed char *__restrict__  expr_64_in_1 = Args->expr_64_in_1; // (4, 1, 1344) (int8--124) 16.160 Q7
    signed char *__restrict__  expr_64_out_0 = Args->expr_64_out_0; // (4, 1, 1344) int8 531.123 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (4, 1, 1344) var shapes:
    // expr_64_out_0: (4, 1, 1344) expr_64_in_1: (4, 1, 1344) expr_64_in_0: (1,
    // 1, 1344)
    // Iteration reduced to spaces ((0,), (2,))
    // Fixed spaces ()
    // Parameteric spaces ((0,), (2,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i0=0; i0<I0; i0++) {
        for (int i1=First; i1<Last; i1++) {
            // inputs expr_64_in_1: (int8--124) 16.160 Q7 expr_64_in_0: int8
            // 32.252 Q7
            // expr_64_out_0 = Cast(Clip(Norm(Mul(Mul(Sub(Cast(expr_64_in_1, int32), [-124]), Cast(expr_64_in_0, int32)), [251]), [15]), -128, 127), int8)
            // scale clip and cast - int32 521.177 Q14 -> int8 531.123 Q7
            expr_64_out_0[(i0*I1)+i1] = ((signed char)gap_clip((gap_roundnorm_reg((((((int)expr_64_in_1[(i0*I1)+i1])-(-124))*((int)expr_64_in_0[i1]))*(251)), ((unsigned char)15))), (((signed char)7))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_44(expr_44_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_44_in_0 = Args->expr_44_in_0;
    unsigned char *__restrict__  expr_44_out_0 = Args->expr_44_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (128, 128, 8) var shapes:
    // expr_44_out_0: (128, 128, 8) expr_44_in_0: (128, 128, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-119) 15.890 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [119]), SigmoidLUT(Sub(Mul(Cast(expr_44_in_0, int32), [254]), [30226]), SigmoidLUTTable)), [8]), [233]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 15.890 Q15 -> (uint8-8) 4.370 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(119))*SigmoidTable(((((int)expr_44_in_0[i0])*(254))-(30226)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_55(expr_55_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_55_in_0 = Args->expr_55_in_0;
    unsigned char *__restrict__  expr_55_out_0 = Args->expr_55_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_55_out_0: (64, 64, 16) expr_55_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-138) 23.249 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [138]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_55_in_0, int32), [186]), [1]), [51336]), SigmoidLUTTable)), [8]), [136]), [13]), [-7]), 0, 255), uint8)
        // scale clip and cast - int32 23.249 Q15 -> (uint8-7) 5.460 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(138))*SigmoidTable((((((int)expr_55_in_0[i0])*(186))<<((unsigned char)1))-(51336)), SigmoidLUTTable)), (8))*(136)), ((unsigned char)13))-(-7))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_13(expr_13_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_13_in_0 = Args->expr_13_in_0;
    unsigned char *__restrict__  expr_13_out_0 = Args->expr_13_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_13_out_0: (64, 64, 16) expr_13_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-127) 21.525 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [127]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_13_in_0, int32), [172]), [1]), [43688]), SigmoidLUTTable)), [8]), [248]), [14]), [-6]), 0, 255), uint8)
        // scale clip and cast - int32 21.525 Q15 -> (uint8-6) 5.549 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(127))*SigmoidTable((((((int)expr_13_in_0[i0])*(172))<<((unsigned char)1))-(43688)), SigmoidLUTTable)), (8))*(248)), ((unsigned char)14))-(-6))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_23(expr_23_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_23_in_0 = Args->expr_23_in_0;
    unsigned char *__restrict__  expr_23_out_0 = Args->expr_23_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 8) var shapes:
    // expr_23_out_0: (64, 64, 8) expr_23_in_0: (64, 64, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_23_in_0: (uint8-148) 17.669 Q8
        // expr_23_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_23_in_0, int32), [148]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_23_in_0, int32), [141]), [1]), [41736]), SigmoidLUTTable)), [8]), [147]), [13]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 17.669 Q15 -> (uint8-9) 3.853 Q7
        expr_23_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_23_in_0[i0])-(148))*SigmoidTable((((((int)expr_23_in_0[i0])*(141))<<((unsigned char)1))-(41736)), SigmoidLUTTable)), (8))*(147)), ((unsigned char)13))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_42(expr_42_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_42_in_0 = Args->expr_42_in_0;
    unsigned char *__restrict__  expr_42_out_0 = Args->expr_42_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_42_out_0: (64, 64, 16) expr_42_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-131) 18.370 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [131]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_42_in_0, int32), [147]), [1]), [38514]), SigmoidLUTTable)), [8]), [255]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 18.370 Q15 -> (uint8-8) 4.610 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(131))*SigmoidTable((((((int)expr_42_in_0[i0])*(147))<<((unsigned char)1))-(38514)), SigmoidLUTTable)), (8))*(255)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_43(expr_43_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_43_in_0 = Args->expr_43_in_0;
    unsigned char *__restrict__  expr_43_out_0 = Args->expr_43_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_43_out_0: (32, 32, 32) expr_43_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-131) 15.740 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [131]), SigmoidLUT(Sub(Mul(Cast(expr_43_in_0, int32), [252]), [33012]), SigmoidLUTTable)), [8]), [254]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 15.740 Q15 -> (uint8-9) 3.965 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(131))*SigmoidTable(((((int)expr_43_in_0[i0])*(252))-(33012)), SigmoidLUTTable)), (8))*(254)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_45(expr_45_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_45_in_0 = Args->expr_45_in_0;
    unsigned char *__restrict__  expr_45_out_0 = Args->expr_45_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_45_out_0: (32, 32, 32) expr_45_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-121) 13.898 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [121]), SigmoidLUT(Sub(Mul(Cast(expr_45_in_0, int32), [222]), [26862]), SigmoidLUTTable)), [8]), [236]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 13.898 Q15 -> (uint8-9) 3.776 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(121))*SigmoidTable(((((int)expr_45_in_0[i0])*(222))-(26862)), SigmoidLUTTable)), (8))*(236)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_46(expr_46_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_46_in_0 = Args->expr_46_in_0;
    unsigned char *__restrict__  expr_46_out_0 = Args->expr_46_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 16) var shapes:
    // expr_46_out_0: (32, 32, 16) expr_46_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_46_in_0: (uint8-127) 14.883 Q8
        // expr_46_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_46_in_0, int32), [127]), SigmoidLUT(Sub(Mul(Cast(expr_46_in_0, int32), [238]), [30226]), SigmoidLUTTable)), [8]), [247]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 14.883 Q15 -> (uint8-9) 3.861 Q7
        expr_46_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_46_in_0[i0])-(127))*SigmoidTable(((((int)expr_46_in_0[i0])*(238))-(30226)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_48(expr_48_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_48_in_0 = Args->expr_48_in_0;
    unsigned char *__restrict__  expr_48_out_0 = Args->expr_48_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_48_out_0: (32, 32, 32) expr_48_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-130) 11.857 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [130]), SigmoidLUT(Sub(Mul(Cast(expr_48_in_0, int32), [190]), [24700]), SigmoidLUTTable)), [8]), [251]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 11.857 Q15 -> (uint8-12) 3.028 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(130))*SigmoidTable(((((int)expr_48_in_0[i0])*(190))-(24700)), SigmoidLUTTable)), (8))*(251)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_49(expr_49_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_49_in_0 = Args->expr_49_in_0;
    unsigned char *__restrict__  expr_49_out_0 = Args->expr_49_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_49_out_0: (16, 16, 56) expr_49_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-130) 9.295 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [130]), SigmoidLUT(Sub(Mul(Cast(expr_49_in_0, int32), [149]), [19370]), SigmoidLUTTable)), [8]), [249]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 9.295 Q15 -> (uint8-15) 2.392 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(130))*SigmoidTable(((((int)expr_49_in_0[i0])*(149))-(19370)), SigmoidLUTTable)), (8))*(249)), ((unsigned char)14))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_50(expr_50_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_50_in_0 = Args->expr_50_in_0;
    unsigned char *__restrict__  expr_50_out_0 = Args->expr_50_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_50_out_0: (16, 16, 56) expr_50_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-148) 10.487 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [148]), SigmoidLUT(Sub(Mul(Cast(expr_50_in_0, int32), [168]), [24864]), SigmoidLUTTable)), [8]), [145]), [13]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 10.487 Q15 -> (uint8-15) 2.311 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(148))*SigmoidTable(((((int)expr_50_in_0[i0])*(168))-(24864)), SigmoidLUTTable)), (8))*(145)), ((unsigned char)13))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_51(expr_51_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_51_in_0 = Args->expr_51_in_0;
    unsigned char *__restrict__  expr_51_out_0 = Args->expr_51_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_51_out_0: (16, 16, 28) expr_51_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_51_in_0: (uint8-135) 10.978 Q8
        // expr_51_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_51_in_0, int32), [135]), SigmoidLUT(Sub(Mul(Cast(expr_51_in_0, int32), [176]), [23760]), SigmoidLUTTable)), [8]), [130]), [13]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.978 Q15 -> (uint8-13) 2.704 Q7
        expr_51_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_51_in_0[i0])-(135))*SigmoidTable(((((int)expr_51_in_0[i0])*(176))-(23760)), SigmoidLUTTable)), (8))*(130)), ((unsigned char)13))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_53(expr_53_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_53_in_0 = Args->expr_53_in_0;
    unsigned char *__restrict__  expr_53_out_0 = Args->expr_53_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_53_out_0: (16, 16, 56) expr_53_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-135) 11.262 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [135]), SigmoidLUT(Sub(Mul(Cast(expr_53_in_0, int32), [180]), [24300]), SigmoidLUTTable)), [8]), [129]), [13]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 11.262 Q15 -> (uint8-13) 2.787 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(135))*SigmoidTable(((((int)expr_53_in_0[i0])*(180))-(24300)), SigmoidLUTTable)), (8))*(129)), ((unsigned char)13))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_54(expr_54_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_54_in_0 = Args->expr_54_in_0;
    unsigned char *__restrict__  expr_54_out_0 = Args->expr_54_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 104) var shapes:
    // expr_54_out_0: (8, 8, 104) expr_54_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_54_in_0: (uint8-120) 10.547 Q8
        // expr_54_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_54_in_0, int32), [120]), SigmoidLUT(Sub(Mul(Cast(expr_54_in_0, int32), [169]), [20280]), SigmoidLUTTable)), [8]), [232]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.547 Q15 -> (uint8-12) 2.911 Q7
        expr_54_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_54_in_0[i0])-(120))*SigmoidTable(((((int)expr_54_in_0[i0])*(169))-(20280)), SigmoidLUTTable)), (8))*(232)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_56(expr_56_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_56_in_0 = Args->expr_56_in_0;
    unsigned char *__restrict__  expr_56_out_0 = Args->expr_56_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 104) var shapes:
    // expr_56_out_0: (8, 8, 104) expr_56_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-135) 10.560 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [135]), SigmoidLUT(Sub(Mul(Cast(expr_56_in_0, int32), [169]), [22815]), SigmoidLUTTable)), [8]), [130]), [13]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 10.560 Q15 -> (uint8-14) 2.604 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(135))*SigmoidTable(((((int)expr_56_in_0[i0])*(169))-(22815)), SigmoidLUTTable)), (8))*(130)), ((unsigned char)13))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_57(expr_57_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_57_in_0 = Args->expr_57_in_0;
    unsigned char *__restrict__  expr_57_out_0 = Args->expr_57_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 52) var shapes:
    // expr_57_out_0: (8, 8, 52) expr_57_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_57_in_0: (uint8-129) 11.818 Q8
        // expr_57_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_57_in_0, int32), [129]), SigmoidLUT(Sub(Mul(Cast(expr_57_in_0, int32), [189]), [24381]), SigmoidLUTTable)), [8]), [247]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 11.818 Q15 -> (uint8-12) 3.057 Q7
        expr_57_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_57_in_0[i0])-(129))*SigmoidTable(((((int)expr_57_in_0[i0])*(189))-(24381)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_59(expr_59_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_59_in_0 = Args->expr_59_in_0;
    unsigned char *__restrict__  expr_59_out_0 = Args->expr_59_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 104) var shapes:
    // expr_59_out_0: (8, 8, 104) expr_59_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_59_in_0: (uint8-129) 10.076 Q8
        // expr_59_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_59_in_0, int32), [129]), SigmoidLUT(Sub(Mul(Cast(expr_59_in_0, int32), [161]), [20769]), SigmoidLUTTable)), [8]), [247]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 10.076 Q15 -> (uint8-14) 2.613 Q7
        expr_59_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_59_in_0[i0])-(129))*SigmoidTable(((((int)expr_59_in_0[i0])*(161))-(20769)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_60(expr_60_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_60_in_0 = Args->expr_60_in_0;
    unsigned char *__restrict__  expr_60_out_0 = Args->expr_60_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 52) var shapes:
    // expr_60_out_0: (8, 8, 52) expr_60_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_60_in_0: (uint8-133) 10.598 Q8
        // expr_60_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_60_in_0, int32), [133]), SigmoidLUT(Sub(Mul(Cast(expr_60_in_0, int32), [170]), [22610]), SigmoidLUTTable)), [8]), [134]), [14]), [-128]), 0, 255), uint8)
        // scale clip and cast - int32 10.598 Q15 -> (uint8-128) 10.111 Q8
        expr_60_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_60_in_0[i0])-(133))*SigmoidTable(((((int)expr_60_in_0[i0])*(170))-(22610)), SigmoidLUTTable)), (8))*(134)), ((unsigned char)14))-(-128))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_61(expr_61_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_61_in_0 = Args->expr_61_in_0;
    unsigned char *__restrict__  expr_61_out_0 = Args->expr_61_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 104) var shapes:
    // expr_61_out_0: (8, 8, 104) expr_61_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_61_in_0: (uint8-114) 10.189 Q8
        // expr_61_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_61_in_0, int32), [114]), SigmoidLUT(Sub(Mul(Cast(expr_61_in_0, int32), [163]), [18582]), SigmoidLUTTable)), [8]), [221]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.189 Q15 -> (uint8-12) 2.953 Q7
        expr_61_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_61_in_0[i0])-(114))*SigmoidTable(((((int)expr_61_in_0[i0])*(163))-(18582)), SigmoidLUTTable)), (8))*(221)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_62(expr_62_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_62_in_0 = Args->expr_62_in_0;
    unsigned char *__restrict__  expr_62_out_0 = Args->expr_62_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 56) var shapes:
    // expr_62_out_0: (8, 8, 56) expr_62_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_62_in_0: (uint8-126) 8.528 Q8
        // expr_62_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_62_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_62_in_0, int32), [136]), [17136]), SigmoidLUTTable)), [8]), [225]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.528 Q15 -> (uint8-15) 4.846 Q8
        expr_62_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_62_in_0[i0])-(126))*SigmoidTable(((((int)expr_62_in_0[i0])*(136))-(17136)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_5(expr_5_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0;
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_5_out_0: (16, 16, 56) expr_5_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_0: (uint8-129) 10.727 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [129]), SigmoidLUT(Sub(Mul(Cast(expr_5_in_0, int32), [172]), [22188]), SigmoidLUTTable)), [8]), [247]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.727 Q15 -> (uint8-13) 2.783 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(129))*SigmoidTable(((((int)expr_5_in_0[i0])*(172))-(22188)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_6(expr_6_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0;
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_6_out_0: (16, 16, 28) expr_6_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_0: (uint8-128) 10.116 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_6_in_0, [128]), int8), int32), SigmoidLUT(Sub(Mul(Cast(expr_6_in_0, int32), [162]), [20736]), SigmoidLUTTable)), [8]), [245]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.116 Q15 -> (uint8-13) 2.643 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_6_in_0[i0]+((unsigned char)128))))*SigmoidTable(((((int)expr_6_in_0[i0])*(162))-(20736)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_7(expr_7_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_7_in_0 = Args->expr_7_in_0;
    unsigned char *__restrict__  expr_7_out_0 = Args->expr_7_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_7_out_0: (16, 16, 28) expr_7_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_7_in_0: (uint8-139) 9.891 Q8
        // expr_7_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_7_in_0, int32), [139]), SigmoidLUT(Sub(Mul(Cast(expr_7_in_0, int32), [158]), [21962]), SigmoidLUTTable)), [8]), [227]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 9.891 Q15 -> (uint8-13) 5.567 Q8
        expr_7_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_7_in_0[i0])-(139))*SigmoidTable(((((int)expr_7_in_0[i0])*(158))-(21962)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_9(expr_9_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_9_in_0 = Args->expr_9_in_0;
    unsigned char *__restrict__  expr_9_out_0 = Args->expr_9_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_9_out_0: (16, 16, 56) expr_9_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-123) 9.670 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [123]), SigmoidLUT(Sub(Mul(Cast(expr_9_in_0, int32), [155]), [19065]), SigmoidLUTTable)), [8]), [236]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 9.670 Q15 -> (uint8-14) 2.619 Q7
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(123))*SigmoidTable(((((int)expr_9_in_0[i0])*(155))-(19065)), SigmoidLUTTable)), (8))*(236)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_10(expr_10_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_10_in_0 = Args->expr_10_in_0;
    unsigned char *__restrict__  expr_10_out_0 = Args->expr_10_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 32) var shapes:
    // expr_10_out_0: (16, 16, 32) expr_10_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-127) 8.689 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [127]), SigmoidLUT(Sub(Mul(Cast(expr_10_in_0, int32), [139]), [17653]), SigmoidLUTTable)), [8]), [193]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 8.689 Q15 -> (uint8-12) 5.774 Q8
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(127))*SigmoidTable(((((int)expr_10_in_0[i0])*(139))-(17653)), SigmoidLUTTable)), (8))*(193)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_11(expr_11_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_11_in_0 = Args->expr_11_in_0;
    unsigned char *__restrict__  expr_11_out_0 = Args->expr_11_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_11_out_0: (32, 32, 32) expr_11_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-132) 10.004 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [132]), SigmoidLUT(Sub(Mul(Cast(expr_11_in_0, int32), [160]), [21120]), SigmoidLUTTable)), [8]), [253]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 10.004 Q15 -> (uint8-14) 2.528 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(132))*SigmoidTable(((((int)expr_11_in_0[i0])*(160))-(21120)), SigmoidLUTTable)), (8))*(253)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_12(expr_12_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_12_in_0 = Args->expr_12_in_0;
    unsigned char *__restrict__  expr_12_out_0 = Args->expr_12_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 16) var shapes:
    // expr_12_out_0: (32, 32, 16) expr_12_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-128) 9.484 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_12_in_0, [128]), int8), int32), SigmoidLUT(Sub(Mul(Cast(expr_12_in_0, int32), [152]), [19456]), SigmoidLUTTable)), [8]), [245]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 9.484 Q15 -> (uint8-14) 2.478 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_12_in_0[i0]+((unsigned char)128))))*SigmoidTable(((((int)expr_12_in_0[i0])*(152))-(19456)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_14(expr_14_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_14_in_0 = Args->expr_14_in_0;
    unsigned char *__restrict__  expr_14_out_0 = Args->expr_14_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 16) var shapes:
    // expr_14_out_0: (32, 32, 16) expr_14_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-93) 12.696 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [93]), SigmoidLUT(Sub(Mul(Cast(expr_14_in_0, int32), [203]), [18879]), SigmoidLUTTable)), [8]), [194]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 12.696 Q15 -> (uint8-9) 4.182 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(93))*SigmoidTable(((((int)expr_14_in_0[i0])*(203))-(18879)), SigmoidLUTTable)), (8))*(194)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_16(expr_16_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_16_in_0 = Args->expr_16_in_0;
    unsigned char *__restrict__  expr_16_out_0 = Args->expr_16_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_16_out_0: (32, 32, 32) expr_16_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-128) 10.268 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_16_in_0, [128]), int8), int32), SigmoidLUT(Sub(Mul(Cast(expr_16_in_0, int32), [164]), [20992]), SigmoidLUTTable)), [8]), [244]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.268 Q15 -> (uint8-13) 2.690 Q7
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_16_in_0[i0]+((unsigned char)128))))*SigmoidTable(((((int)expr_16_in_0[i0])*(164))-(20992)), SigmoidLUTTable)), (8))*(244)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_17(expr_17_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_17_in_0 = Args->expr_17_in_0;
    unsigned char *__restrict__  expr_17_out_0 = Args->expr_17_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 32) var shapes:
    // expr_17_out_0: (16, 16, 32) expr_17_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_17_in_0: (uint8-115) 10.026 Q8
        // expr_17_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_17_in_0, int32), [115]), SigmoidLUT(Sub(Mul(Cast(expr_17_in_0, int32), [160]), [18400]), SigmoidLUTTable)), [8]), [222]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.026 Q15 -> (uint8-12) 2.887 Q7
        expr_17_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_17_in_0[i0])-(115))*SigmoidTable(((((int)expr_17_in_0[i0])*(160))-(18400)), SigmoidLUTTable)), (8))*(222)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_18(expr_18_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_18_in_0 = Args->expr_18_in_0;
    unsigned char *__restrict__  expr_18_out_0 = Args->expr_18_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 64) var shapes:
    // expr_18_out_0: (32, 32, 64) expr_18_in_0: (32, 32, 64) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-131) 11.224 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [131]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [180]), [23580]), SigmoidLUTTable)), [8]), [251]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 11.224 Q15 -> (uint8-12) 2.866 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(131))*SigmoidTable(((((int)expr_18_in_0[i0])*(180))-(23580)), SigmoidLUTTable)), (8))*(251)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_19(expr_19_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_19_in_0 = Args->expr_19_in_0;
    unsigned char *__restrict__  expr_19_out_0 = Args->expr_19_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 64) var shapes:
    // expr_19_out_0: (32, 32, 64) expr_19_in_0: (32, 32, 64) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-93) 12.053 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [93]), SigmoidLUT(Sub(Mul(Cast(expr_19_in_0, int32), [193]), [17949]), SigmoidLUTTable)), [8]), [195]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 12.053 Q15 -> (uint8-9) 3.959 Q7
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(93))*SigmoidTable(((((int)expr_19_in_0[i0])*(193))-(17949)), SigmoidLUTTable)), (8))*(195)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_20(expr_20_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_20_in_0 = Args->expr_20_in_0;
    unsigned char *__restrict__  expr_20_out_0 = Args->expr_20_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_20_out_0: (32, 32, 32) expr_20_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-121) 14.035 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [121]), SigmoidLUT(Sub(Mul(Cast(expr_20_in_0, int32), [225]), [27225]), SigmoidLUTTable)), [8]), [235]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 14.035 Q15 -> (uint8-9) 3.828 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(121))*SigmoidTable(((((int)expr_20_in_0[i0])*(225))-(27225)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_21(expr_21_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_21_in_0 = Args->expr_21_in_0;
    unsigned char *__restrict__  expr_21_out_0 = Args->expr_21_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_21_out_0: (32, 32, 32) expr_21_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-122) 19.882 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [122]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_21_in_0, int32), [159]), [1]), [38796]), SigmoidLUTTable)), [8]), [239]), [14]), [-7]), 0, 255), uint8)
        // scale clip and cast - int32 19.882 Q15 -> (uint8-7) 5.321 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(122))*SigmoidTable((((((int)expr_21_in_0[i0])*(159))<<((unsigned char)1))-(38796)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-7))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_22(expr_22_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_22_in_0 = Args->expr_22_in_0;
    unsigned char *__restrict__  expr_22_out_0 = Args->expr_22_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_22_out_0: (16, 16, 56) expr_22_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-126) 10.056 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_22_in_0, int32), [161]), [20286]), SigmoidLUTTable)), [8]), [241]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.056 Q15 -> (uint8-13) 2.667 Q7
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(126))*SigmoidTable(((((int)expr_22_in_0[i0])*(161))-(20286)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_25(expr_25_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_25_in_0 = Args->expr_25_in_0;
    unsigned char *__restrict__  expr_25_out_0 = Args->expr_25_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_25_out_0: (16, 16, 28) expr_25_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-133) 10.621 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [133]), SigmoidLUT(Sub(Mul(Cast(expr_25_in_0, int32), [170]), [22610]), SigmoidLUTTable)), [8]), [256]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.621 Q15 -> (uint8-13) 2.656 Q7
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(133))*SigmoidTable(((((int)expr_25_in_0[i0])*(170))-(22610)), SigmoidLUTTable)), (8))*(256)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_26(expr_26_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_26_in_0 = Args->expr_26_in_0;
    unsigned char *__restrict__  expr_26_out_0 = Args->expr_26_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_26_out_0: (16, 16, 28) expr_26_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-111) 11.064 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [111]), SigmoidLUT(Sub(Mul(Cast(expr_26_in_0, int32), [177]), [19647]), SigmoidLUTTable)), [8]), [218]), [14]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 11.064 Q15 -> (uint8-11) 3.250 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(111))*SigmoidTable(((((int)expr_26_in_0[i0])*(177))-(19647)), SigmoidLUTTable)), (8))*(218)), ((unsigned char)14))-(-11))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_27(expr_27_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_27_in_0 = Args->expr_27_in_0;
    unsigned char *__restrict__  expr_27_out_0 = Args->expr_27_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_27_out_0: (16, 16, 56) expr_27_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-126) 10.935 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_27_in_0, int32), [175]), [22050]), SigmoidLUTTable)), [8]), [241]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.935 Q15 -> (uint8-12) 2.905 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(126))*SigmoidTable(((((int)expr_27_in_0[i0])*(175))-(22050)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_28(expr_28_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_28_in_0 = Args->expr_28_in_0;
    unsigned char *__restrict__  expr_28_out_0 = Args->expr_28_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 56) var shapes:
    // expr_28_out_0: (8, 8, 56) expr_28_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-135) 9.788 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [135]), SigmoidLUT(Sub(Mul(Cast(expr_28_in_0, int32), [157]), [21195]), SigmoidLUTTable)), [8]), [129]), [13]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 9.788 Q15 -> (uint8-15) 2.423 Q7
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(135))*SigmoidTable(((((int)expr_28_in_0[i0])*(157))-(21195)), SigmoidLUTTable)), (8))*(129)), ((unsigned char)13))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_29(expr_29_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_29_in_0 = Args->expr_29_in_0;
    unsigned char *__restrict__  expr_29_out_0 = Args->expr_29_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 64) var shapes:
    // expr_29_out_0: (16, 16, 64) expr_29_in_0: (16, 16, 64) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_29_in_0: (uint8-130) 11.099 Q8
        // expr_29_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_29_in_0, int32), [130]), SigmoidLUT(Sub(Mul(Cast(expr_29_in_0, int32), [178]), [23140]), SigmoidLUTTable)), [8]), [249]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 11.099 Q15 -> (uint8-12) 2.853 Q7
        expr_29_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_29_in_0[i0])-(130))*SigmoidTable(((((int)expr_29_in_0[i0])*(178))-(23140)), SigmoidLUTTable)), (8))*(249)), ((unsigned char)14))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_30(expr_30_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_30_in_0 = Args->expr_30_in_0;
    unsigned char *__restrict__  expr_30_out_0 = Args->expr_30_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 32) var shapes:
    // expr_30_out_0: (16, 16, 32) expr_30_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-124) 13.834 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [124]), SigmoidLUT(Sub(Mul(Cast(expr_30_in_0, int32), [221]), [27404]), SigmoidLUTTable)), [8]), [240]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 13.834 Q15 -> (uint8-10) 3.691 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(124))*SigmoidTable(((((int)expr_30_in_0[i0])*(221))-(27404)), SigmoidLUTTable)), (8))*(240)), ((unsigned char)14))-(-10))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_31(expr_31_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_31_in_0 = Args->expr_31_in_0;
    unsigned char *__restrict__  expr_31_out_0 = Args->expr_31_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 64) var shapes:
    // expr_31_out_0: (16, 16, 64) expr_31_in_0: (16, 16, 64) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-87) 13.537 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [87]), SigmoidLUT(Sub(Mul(Cast(expr_31_in_0, int32), [217]), [18879]), SigmoidLUTTable)), [8]), [188]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 13.537 Q15 -> (uint8-8) 4.609 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(87))*SigmoidTable(((((int)expr_31_in_0[i0])*(217))-(18879)), SigmoidLUTTable)), (8))*(188)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_32(expr_32_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0;
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 32) var shapes:
    // expr_32_out_0: (16, 16, 32) expr_32_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_32_in_0: (uint8-102) 15.303 Q8
        // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_32_in_0, int32), [102]), SigmoidLUT(Sub(Mul(Cast(expr_32_in_0, int32), [245]), [24990]), SigmoidLUTTable)), [8]), [207]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 15.303 Q15 -> (uint8-8) 4.729 Q7
        expr_32_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_32_in_0[i0])-(102))*SigmoidTable(((((int)expr_32_in_0[i0])*(245))-(24990)), SigmoidLUTTable)), (8))*(207)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_33(expr_33_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_33_in_0 = Args->expr_33_in_0;
    unsigned char *__restrict__  expr_33_out_0 = Args->expr_33_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 104) var shapes:
    // expr_33_out_0: (8, 8, 104) expr_33_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-143) 9.533 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [143]), SigmoidLUT(Sub(Mul(Cast(expr_33_in_0, int32), [153]), [21879]), SigmoidLUTTable)), [8]), [138]), [13]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 9.533 Q15 -> (uint8-16) 2.210 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(143))*SigmoidTable(((((int)expr_33_in_0[i0])*(153))-(21879)), SigmoidLUTTable)), (8))*(138)), ((unsigned char)13))-(-16))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_35(expr_35_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0;
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 52) var shapes:
    // expr_35_out_0: (8, 8, 52) expr_35_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_35_in_0: (uint8-133) 8.141 Q8
        // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_35_in_0, int32), [133]), SigmoidLUT(Sub(Mul(Cast(expr_35_in_0, int32), [130]), [17290]), SigmoidLUTTable)), [8]), [255]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 8.141 Q15 -> (uint8-17) 2.042 Q7
        expr_35_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_35_in_0[i0])-(133))*SigmoidTable(((((int)expr_35_in_0[i0])*(130))-(17290)), SigmoidLUTTable)), (8))*(255)), ((unsigned char)14))-(-17))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_36(expr_36_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_36_in_0 = Args->expr_36_in_0;
    unsigned char *__restrict__  expr_36_out_0 = Args->expr_36_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 52) var shapes:
    // expr_36_out_0: (8, 8, 52) expr_36_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-127) 6.392 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [127]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_36_in_0, int32), [205]), [1]), [13018]), SigmoidLUTTable)), [8]), [185]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 6.392 Q15 -> (uint8-16) 4.421 Q8
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(127))*SigmoidTable((gap_roundnorm_reg((((int)expr_36_in_0[i0])*(205)), ((unsigned char)1))-(13018)), SigmoidLUTTable)), (8))*(185)), ((unsigned char)14))-(-16))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_37(expr_37_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_37_in_0 = Args->expr_37_in_0;
    unsigned char *__restrict__  expr_37_out_0 = Args->expr_37_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 104) var shapes:
    // expr_37_out_0: (8, 8, 104) expr_37_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-123) 7.464 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_37_in_0, int32), [239]), [1]), [14699]), SigmoidLUTTable)), [8]), [235]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.464 Q15 -> (uint8-18) 2.036 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(123))*SigmoidTable((gap_roundnorm_reg((((int)expr_37_in_0[i0])*(239)), ((unsigned char)1))-(14699)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_38(expr_38_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_38_in_0 = Args->expr_38_in_0;
    unsigned char *__restrict__  expr_38_out_0 = Args->expr_38_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 64) var shapes:
    // expr_38_out_0: (8, 8, 64) expr_38_in_0: (8, 8, 64) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-121) 8.275 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [121]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [132]), [15972]), SigmoidLUTTable)), [8]), [232]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.275 Q15 -> (uint8-16) 2.285 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(121))*SigmoidTable(((((int)expr_38_in_0[i0])*(132))-(15972)), SigmoidLUTTable)), (8))*(232)), ((unsigned char)14))-(-16))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_39(expr_39_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_39_in_0 = Args->expr_39_in_0;
    unsigned char *__restrict__  expr_39_out_0 = Args->expr_39_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 32) var shapes:
    // expr_39_out_0: (8, 8, 32) expr_39_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-138) 6.240 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [138]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_39_in_0, int32), [200]), [1]), [13800]), SigmoidLUTTable)), [8]), [134]), [13]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 6.240 Q15 -> (uint8-24) 1.491 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(138))*SigmoidTable((gap_roundnorm_reg((((int)expr_39_in_0[i0])*(200)), ((unsigned char)1))-(13800)), SigmoidLUTTable)), (8))*(134)), ((unsigned char)13))-(-24))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_40(expr_40_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_40_in_0 = Args->expr_40_in_0;
    unsigned char *__restrict__  expr_40_out_0 = Args->expr_40_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 64) var shapes:
    // expr_40_out_0: (8, 8, 64) expr_40_in_0: (8, 8, 64) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_40_in_0: (uint8-118) 11.247 Q8
        // expr_40_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_40_in_0, int32), [118]), SigmoidLUT(Sub(Mul(Cast(expr_40_in_0, int32), [180]), [21240]), SigmoidLUTTable)), [8]), [229]), [14]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 11.247 Q15 -> (uint8-11) 3.144 Q7
        expr_40_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_40_in_0[i0])-(118))*SigmoidTable(((((int)expr_40_in_0[i0])*(180))-(21240)), SigmoidLUTTable)), (8))*(229)), ((unsigned char)14))-(-11))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_41(expr_41_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_41_in_0 = Args->expr_41_in_0;
    unsigned char *__restrict__  expr_41_out_0 = Args->expr_41_out_0; // (1, 1, 256) 
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 32) var shapes:
    // expr_41_out_0: (8, 8, 32) expr_41_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-123) 5.215 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [167]), [1]), [10271]), SigmoidLUTTable)), [8]), [237]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.215 Q15 -> (uint8-25) 1.407 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(123))*SigmoidTable((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(167)), ((unsigned char)1))-(10271)), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-25))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop
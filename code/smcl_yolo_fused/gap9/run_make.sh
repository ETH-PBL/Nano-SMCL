cd /home/hanna/Documents/ETH/Drones/tinyissimoyolo-gap9/nntool/yolov5picolo_on_gap9_tflite_small_L2

source /home/hanna/Documents/ETH/GAP9/gap_sdk_private/configs/gap9_evk_audio.sh
export TILER_INTEGRAL_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Generators/IntegralImage
export TILER_CNN_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Generators
export TILER_FFT_GEN_LUT_SCRIPT=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/DSP_Libraries/LUT_Tables/gen_scripts/GenFFTLUT.py
export TILER_INTEGRAL_KERNEL_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Generators/IntegralImage
export TILER_WIN_GEN_LUT_SCRIPT=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/DSP_Libraries/LUT_Tables/gen_scripts/GenWinLUT.py
export TILER_ISP_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/ISP_Generators
export TILER_FFT2D_TWIDDLE_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Generators/FFT2DModel
export TILER_CNN_GENERATOR_PATH_SQ8=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Generators_SQ8
export TILER_BILINEAR_RESIZE_KERNEL_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/ISP_Libraries
export TILER_LIB=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Autotiler/LibTile.a
export TILER_FFT2D_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Generators/FFT2DModel
export TILER_CNN_KERNEL_PATH_SQ8=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Libraries_SQ8
export TILER_DSP_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/DSP_Generators
export TILER_INC=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Autotiler
export TILER_MFCC_GEN_LUT_SCRIPT=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/DSP_Libraries/LUT_Tables/gen_scripts/GenMFCCLUT.py
export TILER_CNN_KERNEL_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Libraries
export TILER_CNN_KERNEL_PATH_NE16=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Libraries_NE16
export TILER_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Generators
export TILER_CNN_KERNEL_PATH_FP16=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Libraries_fp16
export TILER_ISP_KERNEL_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/ISP_Libraries
export TILER_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3
export TILER_CNN_GENERATOR_PATH_FP16=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Generators_fp16
export TILER_BILINEAR_RESIZE_GENERATOR_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/ISP_Generators
export TILER_DSP_KERNEL_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/DSP_Libraries
export TILER_FFT2D_KERNEL_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Generators/FFT2DModel
export TILER_CNN_GENERATOR_PATH_NE16=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/CNN_Generators_NE16
export TILER_EMU_INC=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/Emulation
export TILER_FFT_LUT_PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/autotiler_v3/DSP_Libraries/LUT_Tables
export PATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/nntool/scripts:$PATH
export PYTHONPATH=/home/hanna/Documents/ETH/GAP9/gap_sdk_private/tools/nntool:$PYTHONPATH
export CCACHE_BASEDIR=/home/hanna/Documents/ETH/Drones/tinyissimoyolo-gap9/nntool/yolov5picolo_on_gap9_tflite_small_L2
mkdir -p /home/hanna/Documents/ETH/Drones/tinyissimoyolo-gap9/nntool/yolov5picolo_on_gap9_tflite_small_L2/build
retVal=$?
if [ $retVal -ne 0 ]; then
    exit $retVal
fi
(cd /home/hanna/Documents/ETH/Drones/tinyissimoyolo-gap9/nntool/yolov5picolo_on_gap9_tflite_small_L2/build; cmake ..)
retVal=$?
if [ $retVal -ne 0 ]; then
    exit $retVal
fi
(cd /home/hanna/Documents/ETH/Drones/tinyissimoyolo-gap9/nntool/yolov5picolo_on_gap9_tflite_small_L2/build; make -j clean all )
retVal=$?
if [ $retVal -ne 0 ]; then
    exit $retVal
fi
(cd /home/hanna/Documents/ETH/Drones/tinyissimoyolo-gap9/nntool/yolov5picolo_on_gap9_tflite_small_L2/build; make run  )
exit $?

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hdudispfcbit.c \
../src/hdudispfmain.c \
../src/hdudispfpbit.c 

OBJS += \
./src/hdudispfcbit.o \
./src/hdudispfmain.o \
./src/hdudispfpbit.o 

C_DEPS += \
./src/hdudispfcbit.d \
./src/hdudispfmain.d \
./src/hdudispfpbit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746BGTx -DSTM32F746xx -DSTM32F7 -DSTM32 -DUSE_HAL_DRIVER -DARM_MATH_CM7 -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/core" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/device" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/COMMON/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/UCOS" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/app" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/BSP" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/fonts" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/config" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/fastmath" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/font" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/Shared" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/utils" -O0 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



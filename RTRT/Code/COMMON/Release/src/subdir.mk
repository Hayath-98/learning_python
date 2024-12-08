################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hdudispfa429.c \
../src/hdudispfbspnor.c \
../src/hdudispfcas.c \
../src/hdudispfcrc.c \
../src/hdudispfdma2.c \
../src/hdudispfdma2d.c \
../src/hdudispfglobalsettings.c \
../src/hdudispflmsscu.c \
../src/hdudispfoffside.c \
../src/hdudispfpara.c \
../src/hdudispfrtd.c 

OBJS += \
./src/hdudispfa429.o \
./src/hdudispfbspnor.o \
./src/hdudispfcas.o \
./src/hdudispfcrc.o \
./src/hdudispfdma2.o \
./src/hdudispfdma2d.o \
./src/hdudispfglobalsettings.o \
./src/hdudispflmsscu.o \
./src/hdudispfoffside.o \
./src/hdudispfpara.o \
./src/hdudispfrtd.o 

C_DEPS += \
./src/hdudispfa429.d \
./src/hdudispfbspnor.d \
./src/hdudispfcas.d \
./src/hdudispfcrc.d \
./src/hdudispfdma2.d \
./src/hdudispfdma2d.d \
./src/hdudispfglobalsettings.d \
./src/hdudispflmsscu.d \
./src/hdudispfoffside.d \
./src/hdudispfpara.d \
./src/hdudispfrtd.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746NGHx -DSTM32F7 -DSTM32 -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/Shared" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/UCOS" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/utils" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/font" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/config" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/core" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/device" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/app" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/COMMON/inc" -O0 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



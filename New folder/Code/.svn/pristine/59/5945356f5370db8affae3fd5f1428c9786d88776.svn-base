################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hdudispfbargraphs.c \
../src/hdudispfcarrotgraph.c \
../src/hdudispfnumbox.c \
../src/hdudispfpolygon1.c \
../src/hdudispfpolygon2.c \
../src/hdudispfrounddial.c \
../src/hdudispftext.c \
../src/hdudispftextbox.c \
../src/hdudispftimers.c \
../src/hdudispfwidgets.c 

OBJS += \
./src/hdudispfbargraphs.o \
./src/hdudispfcarrotgraph.o \
./src/hdudispfnumbox.o \
./src/hdudispfpolygon1.o \
./src/hdudispfpolygon2.o \
./src/hdudispfrounddial.o \
./src/hdudispftext.o \
./src/hdudispftextbox.o \
./src/hdudispftimers.o \
./src/hdudispfwidgets.o 

C_DEPS += \
./src/hdudispfbargraphs.d \
./src/hdudispfcarrotgraph.d \
./src/hdudispfnumbox.d \
./src/hdudispfpolygon1.d \
./src/hdudispfpolygon2.d \
./src/hdudispfrounddial.d \
./src/hdudispftext.d \
./src/hdudispftextbox.d \
./src/hdudispftimers.d \
./src/hdudispfwidgets.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746NGHx -D_XOPEN_SOURCE -DSTM32F7 -DSTM32 -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/UCOS" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/COMMON/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/utils" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/fastmath" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/font" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/WIDGETS/config" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/core" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/device" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/Shared" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HDU-004-001/app" -O0 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



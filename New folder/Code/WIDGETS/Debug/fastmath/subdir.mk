################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fastmath/hdudispfbfarmcommontables.c \
../fastmath/hdudispfbfarmcosq15.c \
../fastmath/hdudispfbfarmsinq15.c 

OBJS += \
./fastmath/hdudispfbfarmcommontables.o \
./fastmath/hdudispfbfarmcosq15.o \
./fastmath/hdudispfbfarmsinq15.o 

C_DEPS += \
./fastmath/hdudispfbfarmcommontables.d \
./fastmath/hdudispfbfarmcosq15.d \
./fastmath/hdudispfbfarmsinq15.d 


# Each subdirectory must supply rules for building sources it contributes
fastmath/%.o: ../fastmath/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746NGHx -D_XOPEN_SOURCE -DSTM32F7 -DSTM32 -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HAL_Driver" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/UCOS" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/COMMON/inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/utils" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/fastmath" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/font" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/config" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/CMSIS/core" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/CMSIS/device" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/Shared" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HAL_Driver/Inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HDU-004-001/app" -O0 -g3 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



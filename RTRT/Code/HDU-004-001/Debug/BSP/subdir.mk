################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/hdudispfpbs.c \
../BSP/hdudispfpwm.c \
../BSP/hdudispfstmadc.c 

OBJS += \
./BSP/hdudispfpbs.o \
./BSP/hdudispfpwm.o \
./BSP/hdudispfstmadc.o 

C_DEPS += \
./BSP/hdudispfpbs.d \
./BSP/hdudispfpwm.d \
./BSP/hdudispfstmadc.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o: ../BSP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746BGTx -DSTM32F746xx -DSTM32F7 -DSTM32 -DUSE_HAL_DRIVER -DARM_MATH_CM7 -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/CMSIS/core" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/CMSIS/device" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/COMMON/inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HAL_Driver/Inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/UCOS" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HDU-004-001/app" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HDU-004-001/BSP" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HDU-004-001/inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/HDU-004-001/fonts" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/config" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/fastmath" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/font" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/inc" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/Shared" -I"E:/dhanalakshmi/ECM68A/Work/MARCH/29th_code/DisplayBoard/WIDGETS/utils" -O0 -g3 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



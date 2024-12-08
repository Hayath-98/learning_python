################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hdudispfoscpu.c \
../hdudispfucos.c 

OBJS += \
./hdudispfoscpu.o \
./hdudispfucos.o 

C_DEPS += \
./hdudispfoscpu.d \
./hdudispfucos.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746BGTx -DSTM32F7 -DSTM32 -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Inc" -O0 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



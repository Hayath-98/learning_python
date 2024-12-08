################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hdudispbbinascii.c \
../src/hdudispbboot.c \
../src/hdudispbconsolas24haa4.c \
../src/hdudispbcrc.c \
../src/hdudispbfonts.c \
../src/hdudispbmain.c \
../src/hdudispbpanel.c \
../src/hdudispbpwm.c \
../src/hdudispbrevno.c \
../src/hdudispbrterr.c \
../src/hdudispbtext.c 

OBJS += \
./src/hdudispbbinascii.o \
./src/hdudispbboot.o \
./src/hdudispbconsolas24haa4.o \
./src/hdudispbcrc.o \
./src/hdudispbfonts.o \
./src/hdudispbmain.o \
./src/hdudispbpanel.o \
./src/hdudispbpwm.o \
./src/hdudispbrevno.o \
./src/hdudispbrterr.o \
./src/hdudispbtext.o 

C_DEPS += \
./src/hdudispbbinascii.d \
./src/hdudispbboot.d \
./src/hdudispbconsolas24haa4.d \
./src/hdudispbcrc.d \
./src/hdudispbfonts.d \
./src/hdudispbmain.d \
./src/hdudispbpanel.d \
./src/hdudispbpwm.d \
./src/hdudispbrevno.d \
./src/hdudispbrterr.d \
./src/hdudispbtext.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746NGHx -DSTM32F7 -DSTM32 -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/chaithra/HDU_2021/feb_25_eicas/HAL_Driver" -I"C:/chaithra/HDU_2021/feb_25_eicas/HAL_Driver/Inc" -I"C:/chaithra/HDU_2021/feb_25_eicas/HDU-004-002/inc" -I"C:/chaithra/HDU_2021/feb_25_eicas/CMSIS/core" -I"C:/chaithra/HDU_2021/feb_25_eicas/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



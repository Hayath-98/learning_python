################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/hdudispfoscpua.s \
../startup/hdudispfpbita.s \
../startup/hdudispfstartupstm32f746xx.s 

OBJS += \
./startup/hdudispfoscpua.o \
./startup/hdudispfpbita.o \
./startup/hdudispfstartupstm32f746xx.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/UCOS" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/hdudispbstartupstm32f746xx.s 

OBJS += \
./startup/hdudispbstartupstm32f746xx.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -I"C:/chaithra/HDU_2021/feb_25_eicas/HAL_Driver" -I"C:/chaithra/HDU_2021/feb_25_eicas/HAL_Driver/Inc" -I"C:/chaithra/HDU_2021/feb_25_eicas/CMSIS/core" -I"C:/chaithra/HDU_2021/feb_25_eicas/CMSIS/device" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


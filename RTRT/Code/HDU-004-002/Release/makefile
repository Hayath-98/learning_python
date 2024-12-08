################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: H108E-132.elf

dependents:
	-cd E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Release && $(MAKE) all

# Tool invocations
H108E-132.elf: $(OBJS) $(USER_OBJS) E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Release/libHAL_Driver.a E:\HOWELL_2021\HDU\MAY\DisplayBoard\HDU-004-002\H108E-132.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -L"E:\HOWELL_2021\HDU\MAY\DisplayBoard\HAL_Driver\Release" -T"E:\HOWELL_2021\HDU\MAY\DisplayBoard\HDU-004-002\H108E-132.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "H108E-132.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O srec "H108E-132.elf" "H108E-132.srec"
	arm-none-eabi-size "H108E-132.elf"
	
	..\..\tools\STM_SRECCRC H108E-132.srec 0x08000000 0x010000 H108E-132.s19
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Release/libHAL_Driver.a:

-include ../makefile.targets

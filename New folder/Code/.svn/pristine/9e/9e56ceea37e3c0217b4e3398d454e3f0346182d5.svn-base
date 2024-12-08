################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include fonts/subdir.mk
-include app/subdir.mk
-include Shared/subdir.mk
-include BSP/subdir.mk
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
all: H108E133.elf

# Tool invocations
H108E133.elf: $(OBJS) $(USER_OBJS) E:\dhanalakshmi\ECM68A\Work\MARCH\29th_code\DisplayBoard\HDU-004-001\H108E-133.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -L"E:\dhanalakshmi\ECM68A\Work\MARCH\29th_code\DisplayBoard\HAL_Driver\Debug" -L"E:\dhanalakshmi\ECM68A\Work\MARCH\29th_code\DisplayBoard\UCOS\Debug" -L"E:\dhanalakshmi\ECM68A\Work\MARCH\29th_code\DisplayBoard\WIDGETS\Debug" -L"E:\dhanalakshmi\ECM68A\Work\MARCH\29th_code\DisplayBoard\COMMON\Debug" -T"E:\dhanalakshmi\ECM68A\Work\MARCH\29th_code\DisplayBoard\HDU-004-001\H108E-133.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "H108E133.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O srec "H108E133.elf" "H108E133.srec"
	arm-none-eabi-size "H108E133.elf"
	
	..\..\tools\stm_sreccrc H108E133.srec 0x80C0000 0xC0000 H108E133.mot
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

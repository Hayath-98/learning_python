################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/hdulibstm32756gevalsdram.c \
../Src/hdulibstm32f7xxhal.c \
../Src/hdulibstm32f7xxhaladc.c \
../Src/hdulibstm32f7xxhalcan.c \
../Src/hdulibstm32f7xxhalcortex.c \
../Src/hdulibstm32f7xxhalcrc.c \
../Src/hdulibstm32f7xxhalcrcex.c \
../Src/hdulibstm32f7xxhaldma.c \
../Src/hdulibstm32f7xxhaldma2d.c \
../Src/hdulibstm32f7xxhalfmc.c \
../Src/hdulibstm32f7xxhalgpio.c \
../Src/hdulibstm32f7xxhaliwdg.c \
../Src/hdulibstm32f7xxhalltdc.c \
../Src/hdulibstm32f7xxhalmsp.c \
../Src/hdulibstm32f7xxhalnor.c \
../Src/hdulibstm32f7xxhalpwrex.c \
../Src/hdulibstm32f7xxhalrcc.c \
../Src/hdulibstm32f7xxhalrccex.c \
../Src/hdulibstm32f7xxhalsdram.c \
../Src/hdulibstm32f7xxhaltim.c \
../Src/hdulibstm32f7xxit.c \
../Src/hdulibsystemstm32f7xx.c 

OBJS += \
./Src/hdulibstm32756gevalsdram.o \
./Src/hdulibstm32f7xxhal.o \
./Src/hdulibstm32f7xxhaladc.o \
./Src/hdulibstm32f7xxhalcan.o \
./Src/hdulibstm32f7xxhalcortex.o \
./Src/hdulibstm32f7xxhalcrc.o \
./Src/hdulibstm32f7xxhalcrcex.o \
./Src/hdulibstm32f7xxhaldma.o \
./Src/hdulibstm32f7xxhaldma2d.o \
./Src/hdulibstm32f7xxhalfmc.o \
./Src/hdulibstm32f7xxhalgpio.o \
./Src/hdulibstm32f7xxhaliwdg.o \
./Src/hdulibstm32f7xxhalltdc.o \
./Src/hdulibstm32f7xxhalmsp.o \
./Src/hdulibstm32f7xxhalnor.o \
./Src/hdulibstm32f7xxhalpwrex.o \
./Src/hdulibstm32f7xxhalrcc.o \
./Src/hdulibstm32f7xxhalrccex.o \
./Src/hdulibstm32f7xxhalsdram.o \
./Src/hdulibstm32f7xxhaltim.o \
./Src/hdulibstm32f7xxit.o \
./Src/hdulibsystemstm32f7xx.o 

C_DEPS += \
./Src/hdulibstm32756gevalsdram.d \
./Src/hdulibstm32f7xxhal.d \
./Src/hdulibstm32f7xxhaladc.d \
./Src/hdulibstm32f7xxhalcan.d \
./Src/hdulibstm32f7xxhalcortex.d \
./Src/hdulibstm32f7xxhalcrc.d \
./Src/hdulibstm32f7xxhalcrcex.d \
./Src/hdulibstm32f7xxhaldma.d \
./Src/hdulibstm32f7xxhaldma2d.d \
./Src/hdulibstm32f7xxhalfmc.d \
./Src/hdulibstm32f7xxhalgpio.d \
./Src/hdulibstm32f7xxhaliwdg.d \
./Src/hdulibstm32f7xxhalltdc.d \
./Src/hdulibstm32f7xxhalmsp.d \
./Src/hdulibstm32f7xxhalnor.d \
./Src/hdulibstm32f7xxhalpwrex.d \
./Src/hdulibstm32f7xxhalrcc.d \
./Src/hdulibstm32f7xxhalrccex.d \
./Src/hdulibstm32f7xxhalsdram.d \
./Src/hdulibstm32f7xxhaltim.d \
./Src/hdulibstm32f7xxit.d \
./Src/hdulibsystemstm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746BGTx -DSTM32F7 -DSTM32 -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/core" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/CMSIS/device" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/Shared" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/HAL_Driver/Inc" -I"E:/HOWELL_2021/HDU/MAY/DisplayBoard/UCOS" -O0 -Wall -fmessage-length=0 -Wextra -Wconversion -fdata-sections -Wdouble-promotion -Waggregate-return -Wcast-qual -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat-security -Wjump-misses-init -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Woverlength-strings -Wpacked-bitfield-compat -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wmissing-format-attribute -Wswitch-default -Wsystem-headers -Wundef -Wunsuffixed-float-constants -Wvla -Wwrite-strings -DSTM32F746xx -DARM_MATH_CM7 -D__FPU_PRESENT -Wfatal-errors -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



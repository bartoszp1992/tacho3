################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/tacho/battery.c \
../Src/tacho/buttons.c \
../Src/tacho/interface.c \
../Src/tacho/sleep.c \
../Src/tacho/timers.c \
../Src/tacho/watch.c 

OBJS += \
./Src/tacho/battery.o \
./Src/tacho/buttons.o \
./Src/tacho/interface.o \
./Src/tacho/sleep.o \
./Src/tacho/timers.o \
./Src/tacho/watch.o 

C_DEPS += \
./Src/tacho/battery.d \
./Src/tacho/buttons.d \
./Src/tacho/interface.d \
./Src/tacho/sleep.d \
./Src/tacho/timers.d \
./Src/tacho/watch.d 


# Each subdirectory must supply rules for building sources it contributes
Src/tacho/%.o: ../Src/tacho/%.c Src/tacho/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-tacho

clean-Src-2f-tacho:
	-$(RM) ./Src/tacho/battery.d ./Src/tacho/battery.o ./Src/tacho/buttons.d ./Src/tacho/buttons.o ./Src/tacho/interface.d ./Src/tacho/interface.o ./Src/tacho/sleep.d ./Src/tacho/sleep.o ./Src/tacho/timers.d ./Src/tacho/timers.o ./Src/tacho/watch.d ./Src/tacho/watch.o

.PHONY: clean-Src-2f-tacho


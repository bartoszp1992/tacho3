################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/chrono/battery.c \
../Src/chrono/interface.c \
../Src/chrono/sleep.c \
../Src/chrono/timers.c \
../Src/chrono/touch.c \
../Src/chrono/watch.c 

OBJS += \
./Src/chrono/battery.o \
./Src/chrono/interface.o \
./Src/chrono/sleep.o \
./Src/chrono/timers.o \
./Src/chrono/touch.o \
./Src/chrono/watch.o 

C_DEPS += \
./Src/chrono/battery.d \
./Src/chrono/interface.d \
./Src/chrono/sleep.d \
./Src/chrono/timers.d \
./Src/chrono/touch.d \
./Src/chrono/watch.d 


# Each subdirectory must supply rules for building sources it contributes
Src/chrono/%.o Src/chrono/%.su: ../Src/chrono/%.c Src/chrono/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-chrono

clean-Src-2f-chrono:
	-$(RM) ./Src/chrono/battery.d ./Src/chrono/battery.o ./Src/chrono/battery.su ./Src/chrono/interface.d ./Src/chrono/interface.o ./Src/chrono/interface.su ./Src/chrono/sleep.d ./Src/chrono/sleep.o ./Src/chrono/sleep.su ./Src/chrono/timers.d ./Src/chrono/timers.o ./Src/chrono/timers.su ./Src/chrono/touch.d ./Src/chrono/touch.o ./Src/chrono/touch.su ./Src/chrono/watch.d ./Src/chrono/watch.o ./Src/chrono/watch.su

.PHONY: clean-Src-2f-chrono


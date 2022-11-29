################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
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
Src/chrono/%.o: ../Src/chrono/%.c Src/chrono/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-chrono

clean-Src-2f-chrono:
	-$(RM) ./Src/chrono/battery.d ./Src/chrono/battery.o ./Src/chrono/interface.d ./Src/chrono/interface.o ./Src/chrono/sleep.d ./Src/chrono/sleep.o ./Src/chrono/timers.d ./Src/chrono/timers.o ./Src/chrono/touch.d ./Src/chrono/touch.o ./Src/chrono/watch.d ./Src/chrono/watch.o

.PHONY: clean-Src-2f-chrono


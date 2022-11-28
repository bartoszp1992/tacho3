################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/crc.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/rtc.c \
../Src/spi.c \
../Src/stm32g0xx_hal_msp.c \
../Src/stm32g0xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32g0xx.c \
../Src/tim.c 

OBJS += \
./Src/adc.o \
./Src/crc.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/rtc.o \
./Src/spi.o \
./Src/stm32g0xx_hal_msp.o \
./Src/stm32g0xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32g0xx.o \
./Src/tim.o 

C_DEPS += \
./Src/adc.d \
./Src/crc.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/rtc.d \
./Src/spi.d \
./Src/stm32g0xx_hal_msp.d \
./Src/stm32g0xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32g0xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.d ./Src/adc.o ./Src/crc.d ./Src/crc.o ./Src/gpio.d ./Src/gpio.o ./Src/i2c.d ./Src/i2c.o ./Src/main.d ./Src/main.o ./Src/rtc.d ./Src/rtc.o ./Src/spi.d ./Src/spi.o ./Src/stm32g0xx_hal_msp.d ./Src/stm32g0xx_hal_msp.o ./Src/stm32g0xx_it.d ./Src/stm32g0xx_it.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32g0xx.d ./Src/system_stm32g0xx.o ./Src/tim.d ./Src/tim.o

.PHONY: clean-Src


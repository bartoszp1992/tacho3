################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/adc_bd.c \
../Src/backup_bd.c \
../Src/bme280_bd.c \
../Src/buttons.c \
../Src/crc.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/interface_bd.c \
../Src/lis3mdl_bd.c \
../Src/main.c \
../Src/rtc.c \
../Src/rtc_bd.c \
../Src/sleep.c \
../Src/spi.c \
../Src/stm32g0xx_hal_msp.c \
../Src/stm32g0xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32g0xx.c \
../Src/tim.c \
../Src/timers.c \
../Src/watch.c 

OBJS += \
./Src/adc.o \
./Src/adc_bd.o \
./Src/backup_bd.o \
./Src/bme280_bd.o \
./Src/buttons.o \
./Src/crc.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/interface_bd.o \
./Src/lis3mdl_bd.o \
./Src/main.o \
./Src/rtc.o \
./Src/rtc_bd.o \
./Src/sleep.o \
./Src/spi.o \
./Src/stm32g0xx_hal_msp.o \
./Src/stm32g0xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32g0xx.o \
./Src/tim.o \
./Src/timers.o \
./Src/watch.o 

C_DEPS += \
./Src/adc.d \
./Src/adc_bd.d \
./Src/backup_bd.d \
./Src/bme280_bd.d \
./Src/buttons.d \
./Src/crc.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/interface_bd.d \
./Src/lis3mdl_bd.d \
./Src/main.d \
./Src/rtc.d \
./Src/rtc_bd.d \
./Src/sleep.d \
./Src/spi.d \
./Src/stm32g0xx_hal_msp.d \
./Src/stm32g0xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32g0xx.d \
./Src/tim.d \
./Src/timers.d \
./Src/watch.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.d ./Src/adc.o ./Src/adc_bd.d ./Src/adc_bd.o ./Src/backup_bd.d ./Src/backup_bd.o ./Src/bme280_bd.d ./Src/bme280_bd.o ./Src/buttons.d ./Src/buttons.o ./Src/crc.d ./Src/crc.o ./Src/gpio.d ./Src/gpio.o ./Src/i2c.d ./Src/i2c.o ./Src/interface_bd.d ./Src/interface_bd.o ./Src/lis3mdl_bd.d ./Src/lis3mdl_bd.o ./Src/main.d ./Src/main.o ./Src/rtc.d ./Src/rtc.o ./Src/rtc_bd.d ./Src/rtc_bd.o ./Src/sleep.d ./Src/sleep.o ./Src/spi.d ./Src/spi.o ./Src/stm32g0xx_hal_msp.d ./Src/stm32g0xx_hal_msp.o ./Src/stm32g0xx_it.d ./Src/stm32g0xx_it.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32g0xx.d ./Src/system_stm32g0xx.o ./Src/tim.d ./Src/tim.o ./Src/timers.d ./Src/timers.o ./Src/watch.d ./Src/watch.o

.PHONY: clean-Src


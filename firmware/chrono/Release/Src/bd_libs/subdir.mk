################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bd_libs/adc_bd.c \
../Src/bd_libs/backup_bd.c \
../Src/bd_libs/bme280_bd.c \
../Src/bd_libs/forecast_bd.c \
../Src/bd_libs/lis3mdl_bd.c \
../Src/bd_libs/rtc_bd.c 

OBJS += \
./Src/bd_libs/adc_bd.o \
./Src/bd_libs/backup_bd.o \
./Src/bd_libs/bme280_bd.o \
./Src/bd_libs/forecast_bd.o \
./Src/bd_libs/lis3mdl_bd.o \
./Src/bd_libs/rtc_bd.o 

C_DEPS += \
./Src/bd_libs/adc_bd.d \
./Src/bd_libs/backup_bd.d \
./Src/bd_libs/bme280_bd.d \
./Src/bd_libs/forecast_bd.d \
./Src/bd_libs/lis3mdl_bd.d \
./Src/bd_libs/rtc_bd.d 


# Each subdirectory must supply rules for building sources it contributes
Src/bd_libs/%.o: ../Src/bd_libs/%.c Src/bd_libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-bd_libs

clean-Src-2f-bd_libs:
	-$(RM) ./Src/bd_libs/adc_bd.d ./Src/bd_libs/adc_bd.o ./Src/bd_libs/backup_bd.d ./Src/bd_libs/backup_bd.o ./Src/bd_libs/bme280_bd.d ./Src/bd_libs/bme280_bd.o ./Src/bd_libs/forecast_bd.d ./Src/bd_libs/forecast_bd.o ./Src/bd_libs/lis3mdl_bd.d ./Src/bd_libs/lis3mdl_bd.o ./Src/bd_libs/rtc_bd.d ./Src/bd_libs/rtc_bd.o

.PHONY: clean-Src-2f-bd_libs


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Flash_Interface/flash_interface.c 

OBJS += \
./Src/Flash_Interface/flash_interface.o 

C_DEPS += \
./Src/Flash_Interface/flash_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Flash_Interface/%.o Src/Flash_Interface/%.su: ../Src/Flash_Interface/%.c Src/Flash_Interface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Flash_Interface

clean-Src-2f-Flash_Interface:
	-$(RM) ./Src/Flash_Interface/flash_interface.d ./Src/Flash_Interface/flash_interface.o ./Src/Flash_Interface/flash_interface.su

.PHONY: clean-Src-2f-Flash_Interface


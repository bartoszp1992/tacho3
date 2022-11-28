################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Flash_Interface/flash_interface.c 

OBJS += \
./Src/Flash_Interface/flash_interface.o 

C_DEPS += \
./Src/Flash_Interface/flash_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Flash_Interface/%.o: ../Src/Flash_Interface/%.c Src/Flash_Interface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Flash_Interface

clean-Src-2f-Flash_Interface:
	-$(RM) ./Src/Flash_Interface/flash_interface.d ./Src/Flash_Interface/flash_interface.o

.PHONY: clean-Src-2f-Flash_Interface


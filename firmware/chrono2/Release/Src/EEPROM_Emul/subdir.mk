################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/EEPROM_Emul/eeprom_emul.c 

OBJS += \
./Src/EEPROM_Emul/eeprom_emul.o 

C_DEPS += \
./Src/EEPROM_Emul/eeprom_emul.d 


# Each subdirectory must supply rules for building sources it contributes
Src/EEPROM_Emul/%.o Src/EEPROM_Emul/%.su: ../Src/EEPROM_Emul/%.c Src/EEPROM_Emul/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-EEPROM_Emul

clean-Src-2f-EEPROM_Emul:
	-$(RM) ./Src/EEPROM_Emul/eeprom_emul.d ./Src/EEPROM_Emul/eeprom_emul.o ./Src/EEPROM_Emul/eeprom_emul.su

.PHONY: clean-Src-2f-EEPROM_Emul


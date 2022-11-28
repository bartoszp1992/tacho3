################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Display_Config/DEV_Config.c 

OBJS += \
./Src/Display_Config/DEV_Config.o 

C_DEPS += \
./Src/Display_Config/DEV_Config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Display_Config/%.o: ../Src/Display_Config/%.c Src/Display_Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Display_Config

clean-Src-2f-Display_Config:
	-$(RM) ./Src/Display_Config/DEV_Config.d ./Src/Display_Config/DEV_Config.o

.PHONY: clean-Src-2f-Display_Config


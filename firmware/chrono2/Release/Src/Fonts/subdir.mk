################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Fonts/font12.c \
../Src/Fonts/font12CN.c \
../Src/Fonts/font16.c \
../Src/Fonts/font20.c \
../Src/Fonts/font24.c \
../Src/Fonts/font24CN.c \
../Src/Fonts/font8.c 

OBJS += \
./Src/Fonts/font12.o \
./Src/Fonts/font12CN.o \
./Src/Fonts/font16.o \
./Src/Fonts/font20.o \
./Src/Fonts/font24.o \
./Src/Fonts/font24CN.o \
./Src/Fonts/font8.o 

C_DEPS += \
./Src/Fonts/font12.d \
./Src/Fonts/font12CN.d \
./Src/Fonts/font16.d \
./Src/Fonts/font20.d \
./Src/Fonts/font24.d \
./Src/Fonts/font24CN.d \
./Src/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Fonts/%.o Src/Fonts/%.su: ../Src/Fonts/%.c Src/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Fonts

clean-Src-2f-Fonts:
	-$(RM) ./Src/Fonts/font12.d ./Src/Fonts/font12.o ./Src/Fonts/font12.su ./Src/Fonts/font12CN.d ./Src/Fonts/font12CN.o ./Src/Fonts/font12CN.su ./Src/Fonts/font16.d ./Src/Fonts/font16.o ./Src/Fonts/font16.su ./Src/Fonts/font20.d ./Src/Fonts/font20.o ./Src/Fonts/font20.su ./Src/Fonts/font24.d ./Src/Fonts/font24.o ./Src/Fonts/font24.su ./Src/Fonts/font24CN.d ./Src/Fonts/font24CN.o ./Src/Fonts/font24CN.su ./Src/Fonts/font8.d ./Src/Fonts/font8.o ./Src/Fonts/font8.su

.PHONY: clean-Src-2f-Fonts


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
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
Src/Fonts/%.o: ../Src/Fonts/%.c Src/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Fonts

clean-Src-2f-Fonts:
	-$(RM) ./Src/Fonts/font12.d ./Src/Fonts/font12.o ./Src/Fonts/font12CN.d ./Src/Fonts/font12CN.o ./Src/Fonts/font16.d ./Src/Fonts/font16.o ./Src/Fonts/font20.d ./Src/Fonts/font20.o ./Src/Fonts/font24.d ./Src/Fonts/font24.o ./Src/Fonts/font24CN.d ./Src/Fonts/font24CN.o ./Src/Fonts/font8.d ./Src/Fonts/font8.o

.PHONY: clean-Src-2f-Fonts


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src_cpp/Adafruit_RA8875.cpp \
../Core/Src_cpp/GPIO.cpp \
../Core/Src_cpp/SPI.cpp 

OBJS += \
./Core/Src_cpp/Adafruit_RA8875.o \
./Core/Src_cpp/GPIO.o \
./Core/Src_cpp/SPI.o 

CPP_DEPS += \
./Core/Src_cpp/Adafruit_RA8875.d \
./Core/Src_cpp/GPIO.d \
./Core/Src_cpp/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src_cpp/%.o Core/Src_cpp/%.su Core/Src_cpp/%.cyclo: ../Core/Src_cpp/%.cpp Core/Src_cpp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../Core/Src_cpp -I../Core/Inc_hpp -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src_cpp

clean-Core-2f-Src_cpp:
	-$(RM) ./Core/Src_cpp/Adafruit_RA8875.cyclo ./Core/Src_cpp/Adafruit_RA8875.d ./Core/Src_cpp/Adafruit_RA8875.o ./Core/Src_cpp/Adafruit_RA8875.su ./Core/Src_cpp/GPIO.cyclo ./Core/Src_cpp/GPIO.d ./Core/Src_cpp/GPIO.o ./Core/Src_cpp/GPIO.su ./Core/Src_cpp/SPI.cyclo ./Core/Src_cpp/SPI.d ./Core/Src_cpp/SPI.o ./Core/Src_cpp/SPI.su

.PHONY: clean-Core-2f-Src_cpp


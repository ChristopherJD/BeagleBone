################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GPS.cpp \
../GPS_Test.cpp \
../UART.cpp \
../nmea.cpp 

OBJS += \
./GPS.o \
./GPS_Test.o \
./UART.o \
./nmea.o 

CPP_DEPS += \
./GPS.d \
./GPS_Test.d \
./UART.d \
./nmea.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -I/usr/arm-linux-gnueabihf/include/c++/4.8.5 -O0 -g3 -Wall -c -fmessage-length=0 -static-libstdc++ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



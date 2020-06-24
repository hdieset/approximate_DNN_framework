################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../layers/activations.cpp \
../layers/convolutions.cpp \
../layers/dropout.cpp \
../layers/flatten.cpp \
../layers/linear.cpp \
../layers/pooling.cpp \
../layers/sequential.cpp 

OBJS += \
./layers/activations.o \
./layers/convolutions.o \
./layers/dropout.o \
./layers/flatten.o \
./layers/linear.o \
./layers/pooling.o \
./layers/sequential.o 

CPP_DEPS += \
./layers/activations.d \
./layers/convolutions.d \
./layers/dropout.d \
./layers/flatten.d \
./layers/linear.d \
./layers/pooling.d \
./layers/sequential.d 


# Each subdirectory must supply rules for building sources it contributes
layers/%.o: ../layers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



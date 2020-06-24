################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dataset_handlers/imagenet.cpp 

OBJS += \
./dataset_handlers/imagenet.o 

CPP_DEPS += \
./dataset_handlers/imagenet.d 


# Each subdirectory must supply rules for building sources it contributes
dataset_handlers/%.o: ../dataset_handlers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../init.c \
../lcd_toolbox.c \
../main.c \
../newlib_stubs.c 

S_UPPER_SRCS += \
../crt0_arm.S 

OBJS += \
./crt0_arm.o \
./init.o \
./lcd_toolbox.o \
./main.o \
./newlib_stubs.o 

C_DEPS += \
./init.d \
./lcd_toolbox.d \
./main.d \
./newlib_stubs.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



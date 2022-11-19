################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syslog2.c \
../src/tst_time.c 

C_DEPS += \
./src/main.d \
./src/syslog2.d \
./src/tst_time.d 

OBJS += \
./src/main.o \
./src/syslog2.o \
./src/tst_time.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -D__USE_MISC -D__USE_GNU -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/main.d ./src/main.o ./src/syslog2.d ./src/syslog2.o ./src/tst_time.d ./src/tst_time.o

.PHONY: clean-src


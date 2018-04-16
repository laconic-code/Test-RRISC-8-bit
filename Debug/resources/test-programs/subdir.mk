################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../resources/test-programs/hello_word.asm 

OBJS += \
./resources/test-programs/hello_word.o 


# Each subdirectory must supply rules for building sources it contributes
resources/test-programs/%.o: ../resources/test-programs/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



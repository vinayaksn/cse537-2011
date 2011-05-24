################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdcard/byteordering.c \
../sdcard/fat.c \
../sdcard/partition.c \
../sdcard/sd_raw.c \
../sdcard/sdcard.c \
../sdcard/uart.c 

OBJS += \
./sdcard/byteordering.o \
./sdcard/fat.o \
./sdcard/partition.o \
./sdcard/sd_raw.o \
./sdcard/sdcard.o \
./sdcard/uart.o 

C_DEPS += \
./sdcard/byteordering.d \
./sdcard/fat.d \
./sdcard/partition.d \
./sdcard/sd_raw.d \
./sdcard/sdcard.d \
./sdcard/uart.d 


# Each subdirectory must supply rules for building sources it contributes
sdcard/%.o: ../sdcard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



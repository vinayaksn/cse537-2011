################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include sdcard/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
328_sdcard2_02-05.lss \

FLASH_IMAGE += \
328_sdcard2_02-05.hex \

EEPROM_IMAGE += \
328_sdcard2_02-05.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 328_sdcard2_02-05.elf secondary-outputs

# Tool invocations
328_sdcard2_02-05.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,328_sdcard2_02-05.map -mmcu=atmega328p -o"328_sdcard2_02-05.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

328_sdcard2_02-05.lss: 328_sdcard2_02-05.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 328_sdcard2_02-05.elf  >"328_sdcard2_02-05.lss"
	@echo 'Finished building: $@'
	@echo ' '

328_sdcard2_02-05.hex: 328_sdcard2_02-05.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex 328_sdcard2_02-05.elf  "328_sdcard2_02-05.hex"
	@echo 'Finished building: $@'
	@echo ' '

328_sdcard2_02-05.eep: 328_sdcard2_02-05.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 328_sdcard2_02-05.elf  "328_sdcard2_02-05.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 328_sdcard2_02-05.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t 328_sdcard2_02-05.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) 328_sdcard2_02-05.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

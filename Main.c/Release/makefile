################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/DIO/subdir.mk
-include HAL/LCD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Main.c.lss \

FLASH_IMAGE += \
Main.c.hex \

EEPROM_IMAGE += \
Main.c.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Main.c.elf secondary-outputs

# Tool invocations
Main.c.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Main.c.map -mmcu=atmega32 -o "Main.c.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Main.c.lss: Main.c.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Main.c.elf  >"Main.c.lss"
	@echo 'Finished building: $@'
	@echo ' '

Main.c.hex: Main.c.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Main.c.elf  "Main.c.hex"
	@echo 'Finished building: $@'
	@echo ' '

Main.c.eep: Main.c.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Main.c.elf  "Main.c.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Main.c.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Main.c.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Main.c.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

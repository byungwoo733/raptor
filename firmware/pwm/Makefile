ARMGNU := arm-none-eabi

# GCCOPS := -Wall -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-m0 -Wno-unused-value
GCCOPS := -g -Wall -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-m0 -Wno-unused-value
AOPS := --warn -Wa -mcpu=cortex-m0 #--fatal-warnings

COMPILE := $(ARMGNU)-gcc $(GCCOPS) -O1 -c

SRC_PREFIX := ../sw

SOURCES = $(shell find $(SRC_PREFIX) | grep _drv.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

STARTUP := $(SRC_PREFIX)/cm0_startup.s
STARTUP_OBJECT := $(SRC_PREFIX)/start.o

LINKSCRIPT := $(SRC_PREFIX)/sections.ld

PATTERN = pwm

all:  hex

hex:  ${PATTERN:=.hex}

.PHONY: clean flash hex all bin

$(OBJECTS): %.o : %.c ../raptor.h
	@echo ">> Compiling $<"
	$(COMPILE) -o $@ $<

#.SILENT:
%.hex : $(OBJECTS) %.c ../raptor.h
	$(ARMGNU)-as $(AOPS) -o $(STARTUP_OBJECT) $(STARTUP)
	$(COMPILE) -o pwm.o pwm.c
# 	$(ARMGNU)-ld $(LDOPS) -T $(LINKSCRIPT) $(STARTUP_OBJECT) $(OBJECTS) pwm.o -o pwm.elf
	$(ARMGNU)-ld $(LDOPS) -T $(LINKSCRIPT) $(STARTUP_OBJECT) ../sw/gpio_drv.o ../sw/pwm_drv.o pwm.o -o pwm.elf
	$(ARMGNU)-objdump -D pwm.elf > pwm.lst
	$(ARMGNU)-objcopy pwm.elf -O verilog pwm.hex
    python3 ../../util/check_bug.py pwm.lst


clean :
	rm -rf Dumps
	rm -f $(OBJECTS)
	rm -f *.bin
	rm -f *.elf
	rm -f *.lst
	rm -f *.hex
	rm -f *.vvp
	rm -f *.vcd
	rm -f *.out

flash: pwm.hex
	python3 ../../util/raptor_flash.py pwm.hex



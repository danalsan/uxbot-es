# This makefile is based on the LPC1343 Code Base from microbuilder.eu 

TARGET = LPC13xx

FLASH_DRIVE = G
REMOVE = rm -f
COPY = cp
OUTFILE = firmware


CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)gcc
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
OUTFILE = firmware



##########################################################################
#  files
##########################################################################
VPATH = 
OBJS = main.o


##########################################################################
# Startup & Linker script files
##########################################################################

LD_PATH =$(UXBOT_DISTR_PATH)\lpc1xxx
LD_SCRIPT = $(LD_PATH)\linkscript.ld


CPU_TYPE = cortex-m3
VPATH += $(UXBOT_DISTR_PATH)\lpc1xxx
OBJS += cr_startup_lpc13.o



##########################################################################
# Compiler settings, parameters and flags
##########################################################################
LDPATH=$(UXBOT_DISTR_PATH)\libs
INCPATH=$(UXBOT_DISTR_PATH)\inc
DEFS          = -D__USE_CMSIS
LIBS = -luXbot -lHALlib -lCMSISv1p30_LPC13xx -lvcomlib


CFLAGS  = -c -Os -I. -Wall -mthumb -ffunction-sections -fdata-sections -fmessage-length=0 -mcpu=$(CPU_TYPE) -DTARGET=$(TARGET) -fno-builtin -I$(INCPATH) $(DEFS) 
ASFLAGS = -c -Os -I. -Wall -mthumb -ffunction-sections -fdata-sections -fmessage-length=0 -mcpu=$(CPU_TYPE) -D__ASSEMBLY__ -x assembler-with-cpp
LDFLAGS = -nostartfiles -mcpu=$(CPU_TYPE) -mthumb -Wl,--gc-sections 
OCFLAGS = --strip-unneeded



all: firmware program


%.o : %.c
	$(CC) $(CFLAGS) -o $@ $< 

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<


    
firmware: $(OBJS) $(SYS_OBJS)
	$(LD) $(LDFLAGS) -T $(LD_SCRIPT) -o $(OUTFILE).elf $(OBJS) -L$(LDPATH) $(LIBS)
	-@echo 
	$(SIZE) $(OUTFILE).elf
	-@echo 
	$(OBJCOPY) $(OCFLAGS) -O binary $(OUTFILE).elf $(OUTFILE).bin
	$(OBJCOPY) $(OCFLAGS) -O ihex $(OUTFILE).elf $(OUTFILE).hex

program:
	-@echo
	-@echo Installing firmware
		$(UXBOT_DISTR_PATH)\tools\lpcrc firmware.bin
		$(COPY) $(OUTFILE).bin $(FLASH_DRIVE):firmware.bin -f
clean:
	rm -f $(OBJS)  $(OUTFILE).elf $(OUTFILE).bin $(OUTFILE).hex


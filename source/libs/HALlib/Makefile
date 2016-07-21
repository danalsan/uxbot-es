# This makefile is based on the LPC1343 Code Base from microbuilder.eu 

TARGET = LPC13xx
CPU_TYPE = cortex-m3

REMOVE = rm -f
COPY = cp
OUTFILE = libHALLib.a


CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)gcc
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
SIZE = $(CROSS_COMPILE)size



##########################################################################
#  files
##########################################################################



VPATH = ./src
OBJS = adc.o delay.o gpio.o hal.o motor.o sensor.o pushbutton.o led.o 



INCLUDES = -I. -I./inc -I../CMSISv1p30_LPC13xx/inc
DEFS          = -D__USE_CMSIS

##########################################################################
# Compiler settings, parameters and flags
##########################################################################
CFLAGS  = -c -Os -I. -Wall -mthumb -ffunction-sections -fdata-sections -fmessage-length=0 -mcpu=$(CPU_TYPE) -DTARGET=$(TARGET) -fno-builtin -I$(INCLUDES) $(DEFS) 
ASFLAGS = -c -Os -I. -Wall -mthumb -ffunction-sections -fdata-sections -fmessage-length=0 -mcpu=$(CPU_TYPE) -D__ASSEMBLY__ -x assembler-with-cpp



default: $(OUTFILE)


%.o : %.c
	$(CC) $(CFLAGS) -o $@ $< 

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

    
$(OUTFILE): $(OBJS)
	$(AR) rcs $(OUTFILE) $(OBJS)

clean:
	rm -f $(OBJS) $(OUTFILE)


/*
 * 	\file pushbutton.c
 *	uXbot - Hardware abstraction Layer
 *  \date 	12/06/2010
 *  \author uXbot
 */
 
#include "LPC13xx.h"
#include "gpio.h"

void pushbutton_init()
{
	GPIOInit();
	GPIOSetDir( PORT2, 9, 0 );
	GPIOSetDir( PORT2, 2, 0 );
}

uint8_t 	HAL_Pushbutton1Pressed()
{
	return !(GPIOReadValue(PORT2,9));
}

uint8_t 	HAL_Pushbutton2Pressed()
{
	return !(GPIOReadValue(PORT2,2));
}
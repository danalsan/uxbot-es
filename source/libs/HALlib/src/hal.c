/*
 * 	\file hal.c
 *	uXbot - Hardware abstraction Layer
 *  \date 	12/06/2010
 *  \author uXbot
 */

#ifdef __USE_CMSIS
#include "system_LPC13xx.h"
#endif

#include "LPC13xx.h"
#include "led.h"
#include "sensor.h"
#include "motor.h"
#include "delay.h"
#include "pushbutton.h"

/**
 * Initialize uXbot hardware
 */
void HAL_init(void)
{

	/// Initialize leds
	led_init();

	/// Initialize sensors
	sensor_init();

	/// Initialize motors
	motor_init();

	/// Initialize delay module
	delay_init();

	/// Initialize pushbutton
	pushbutton_init();
}

/**
 * Put the device into sleep mode
 * Sleep mode is exited automatically when an interrupt arrives at the processor
 */
void HAL_enter_sleep_mode()
{
	LPC_SYSCON->PDAWAKECFG = LPC_SYSCON->PDRUNCFG;
	__ASM volatile ("WFI");
	return;
}



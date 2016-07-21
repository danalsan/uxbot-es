/**
 * \file	led.c
 * \date	12/06/2010
 *
 */

#include "LPC13xx.h"
#include "gpio.h"

/**
 * Initialize uXbot leds - by default switched off
 */
void led_init(void)
{
	GPIOInit();

	GPIOSetDir( PORT3, 0, 1 );	GPIOSetValue( PORT3, 0, 1 );
	GPIOSetDir( PORT3, 1, 1 );	GPIOSetValue( PORT3, 1, 1 );
	GPIOSetDir( PORT3, 2, 1 );	GPIOSetValue( PORT3, 2, 1 );
	GPIOSetDir( PORT3, 3, 1 );	GPIOSetValue( PORT3, 3, 1 );
}

/**
 * Switch on the specified led (0-3) on uXbot
 * \param index LED index (0 to 3)
 */
void HAL_led_on(uint8_t index)
{
	GPIOSetValue( PORT3, index, 0 );
}


/**
 * Switch off the specified led (0-3) on uXbot
 * \param index LED index (0 to 3)
 */
void HAL_led_off(uint8_t index)
{
	GPIOSetValue( PORT3, index, 1 );
}

/**
 * Switch on all the leds on uXbot
 */
void HAL_leds_on(void)
{
	GPIOSetValue( PORT3, 0, 0 );
	GPIOSetValue( PORT3, 1, 0 );
	GPIOSetValue( PORT3, 2, 0 );
	GPIOSetValue( PORT3, 3, 0 );
}

/**
 * Switch off all the leds on uXbot
 */
void HAL_leds_off(void)
{
	GPIOSetValue( PORT3, 0, 1 );
	GPIOSetValue( PORT3, 1, 1 );
	GPIOSetValue( PORT3, 2, 1 );
	GPIOSetValue( PORT3, 3, 1 );
}

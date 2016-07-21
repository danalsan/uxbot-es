/*
 * 	\file sensorlib.c
 *
 *  \date 	01/07/2010
 *  \author uXbot
 */

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "uXbotLib.h"
#include "HALlib.h"
#include "sensorlib.h"



/** uXbot robot initialization function */
void uXbot_Init()
{
	HAL_init(); 				//> Initialize hardware abstraction layer
	initialize_sensorlib();	//> Initialize sensor library
}


/** Set a particular LED to the specified state
	@param led 	- 	LED_D1,LED_D2,LED_D3 or LED_D4
	@param action 	-	LED_OFF or LED_ON
	*/
void led_set(uint8_t led, uint8_t action)
{
	if(action==LED_ON)
		HAL_led_on(led);
	else
		HAL_led_off(led);
}

/** Switch all the uXbot LEDs on  */
void turn_leds_on(void)
{
	HAL_leds_on();
}

/** Switch all the uXbot LEDs off  */
void turn_leds_off(void)
{
	HAL_leds_off();
}


/** Check whether the uXbot pushbutton 1 is pressed or not
	@return 1 if the pusbutton 1 is pressed / 0 otherwise
 */
uint8_t pushbutton1_pressed()
{
	return HAL_Pushbutton1Pressed();
}

/** Check whether the uXbot pushbutton 2 is pressed or not
	@return 1 if the pusbutton 2 is pressed / 0 otherwise
 */
uint8_t pushbutton2_pressed()
{
	return HAL_Pushbutton2Pressed();
}


/** Get the uXbot battery voltage (motors switch must be ON)
	@return Battery voltage in millivolts
 */
uint32_t get_battery_voltage()
{
	return HAL_get_battery_voltage();
}

/** Wait for the pushbutton 1 to be pressed and released 
	*/
void pushbutton1_wait()
{
	while(1)
	{
		/// Mecanismo anti-rebote
		while(!HAL_Pushbutton1Pressed()); HAL_delay_ms(20);
		if(!HAL_Pushbutton1Pressed()) continue;
		
		while(HAL_Pushbutton1Pressed());  HAL_delay_ms(20);
		if(!HAL_Pushbutton1Pressed())	return;
	}
}

/** Wait for the pushbutton 2 to be pressed and released 
	*/
void pushbutton2_wait()
{
	while(1)
	{
		/// Mecanismo anti-rebote
		while(!HAL_Pushbutton2Pressed()); HAL_delay_ms(20);
		if(!HAL_Pushbutton2Pressed()) continue;
		
		while(HAL_Pushbutton2Pressed());  HAL_delay_ms(20);
		if(!HAL_Pushbutton2Pressed())	return;
	}
}


/** Wait for the pushbutton 1  to be pressed and released. 
	In the meantime, LEDs will blink every 200ms
 */
void pushbutton1_wait_blink()
{
	int leds_state=1;
	HAL_start_counting_ms_c1(200);			///> Iniciar un contador de 200ms
	while(1)
	{
		if(HAL_Pushbutton1Pressed() == 1)	///> Si el pulsador está presionado
		{									///> esperar a que se suelte y retornar con los leds apagados
			HAL_delay_ms(20);
			if(!HAL_Pushbutton1Pressed()) continue;
			while(HAL_Pushbutton1Pressed());
			HAL_delay_ms(20);
			if(!HAL_Pushbutton1Pressed()) { HAL_leds_off(); return; }
			return;
		}

		if(HAL_is_c1_off())					///> Si el contador ha expirado, invertimos el estado de los leds
		{									///> y relanzamos el contador nuevamente
			HAL_start_counting_ms_c1(200);
			if(leds_state==0) 	{ HAL_leds_off(); 	leds_state=1; }
			else				{ HAL_leds_on();	leds_state=0; }
		}
	}
}

/** Wait for the pushbutton 2  to be pressed and released. 
	In the meantime, LEDs will blink every 200ms
 */
void pushbutton2_wait_blink()
{
	int leds_state=1;
	HAL_start_counting_ms_c1(200);			///> Iniciar un contador de 200ms
	while(1)
	{
		if(HAL_Pushbutton2Pressed() == 1)	///> Si el pulsador está presionado
		{									///> esperar a que se suelte y retornar con los leds apagados
			HAL_delay_ms(20);
			if(!HAL_Pushbutton2Pressed()) continue;
			while(HAL_Pushbutton2Pressed());
			HAL_delay_ms(20);
			if(!HAL_Pushbutton2Pressed()) { HAL_leds_off(); return; }
			return;
		}

		if(HAL_is_c1_off())					///> Si el contador ha expirado, invertimos el estado de los leds
		{									///> y relanzamos el contador nuevamente
			HAL_start_counting_ms_c1(200);
			if(leds_state==0) 	{ HAL_leds_off(); 	leds_state=1; }
			else				{ HAL_leds_on();	leds_state=0; }
		}
	}
}
/*
Copyright (c) 2010, Daniel Alvarez <daniel@uxbot.es> / Alberto Calvo <alberto@uxbot.es>
http://www.uxbot.es			All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote
   products derived from this software without specific prior
   written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR `AS IS' AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


// //////////////////////////////////////////////////
// This file describes all the functions exported by the 
// uXbot Hardware Abstraction Layer library
//
// Date	March 2011
// //////////////////////////////////////////////////


#ifndef HALLIB_H_
#define HALLIB_H_

#include "LPC13xx.h"


/**	uXbot hardware initialization */
void 		HAL_init(void);

/** Enter the uXbot processor into sleep-mode to save energy
	Will wake up if an interrupt occurs*/
void 		HAL_enter_sleep_mode(void);



// //////////////////////////////////////////////////
//  Delay and temporization functions
// //////////////////////////////////////////////////

	/** Stop the execution during the specified amount of milliseconds 
		@param ms - Number of milliseconds to delay


		@section Example
		@code

			// Usage example of delay function. Leds will blink every 200ms
			while(1)
			{
				HAL_leds_on();
				HAL_delay_ms(200);
				HAL_leds_off();
				HAL_delay_ms(200);
			}

		@endcode
		*/
	void 		HAL_delay_ms(uint32_t ms);


	/** Stop the execution during the specified amount of microseconds
		@param us - Number of microseconds to delay
		*/
	void 		HAL_delay_us(uint32_t us);

	/** This function starts the count for the sepicified amount of milliseconds
		without interrupting the execution flow of the program.
		To check whether the count is finished, the user must call HAL_is_c1_off function
		@param ms - Number of milliseconds to count
		@section Example
		@code

			// Periodic execution every 10 ms (also valid for the c2 counter)
			while(1)
			{
				HAL_start_counting_ms_c1(10);

				// Task code goes here
				// Executed every 10ms

				while( HAL_is_c1_off() == 0 );	// Wait until the count is over
			}
		@endcode
		*/
	void 		HAL_start_counting_ms_c1(uint32_t ms);


	/** This function starts the count for the sepicified amount of milliseconds
		without interrupting the execution flow of the program.
		To check whether the count is finished, the user must call HAL_is_c2_off function
		@param ms - Number of milliseconds to count
		*/
	void 		HAL_start_counting_ms_c2(uint32_t ms);

	/** This function will test the end of the previously started count
		by the HAL_start_counting_ms_c1 function 
		@return	1 if over / 0 if still in progress
	 */
	uint8_t 	HAL_is_c1_off(void);

	/** This function will test the end of the previously started count
		by the HAL_start_counting_ms_c2 function 
		@return	1 if over / 0 if still in progress
	 */
	uint8_t 	HAL_is_c2_off(void);



// /////////////////////////////////////////////////
//  Sensor related functions
// /////////////////////////////////////////////////
	#define NUM_SENSORS	12

	/** This array will hold sensor values after a valid read (values between 0 and 1023) */
	extern uint32_t sensors[NUM_SENSORS];

	/** Perform a reading of all the 12 uXbot sensors and stores the values in the "sensors" array */
	void 		HAL_sensor_read(void);

	/** Perform a reading of a particular sensor
		@param  index	-	sensor index to be read (0 to 11)
		@return value between 0 (black) y 1023 (white)
		*/
	uint32_t 	HAL_sensor_read_nth(uint8_t index);


// /////////////////////////////////////////////////
//  Motor related functions
// /////////////////////////////////////////////////

	/** Set the motors to the specified speed
		@param left_motor	-	Speed between -1023 and 1023 of the left motor (negative values will make the motor spin backward)
		@param right_motor	-	Speed between -1023 and 1023 of the right motor(negative values will make the motor spin backward)
		*/
	void 		HAL_set_motors(int16_t left_motor, int16_t right_motor);


// //////////////////////////////////////////////////
//  LED related functions
// /////////////////////////////////////////////////

	/** Switch on a particular LED of the uXbot
		@param index	-	LED index (0 to 3)
		*/
	void 		HAL_led_on(uint8_t index);

	/** Switch off a particular LED of the uXbot
		@param index	-	LED index (0 to 3)
		*/
	void 		HAL_led_off(uint8_t index);

	/** Switch on all the uXbot LEDs */
	void 		HAL_leds_on(void);

	/** Switch off all the uXbot LEDs  */
	void 		HAL_leds_off(void);


// /////////////////////////////////////////////////
//  Pushbutton related functions
// /////////////////////////////////////////////////

	/** Check whether the uXbot button 1 is pressed
		@return  1 if pressed / 0 otherwise
	 */
	uint8_t 	HAL_Pushbutton1Pressed(void);

	/** Check whether the uXbot button 2 is pressed
		@return  1 if pressed / 0 otherwise
	 */
	uint8_t 	HAL_Pushbutton2Pressed(void);

	
// /////////////////////////////////////////////////
//  Battery related functions
// /////////////////////////////////////////////////

	/** Get the uXbot battery voltage
		@return  Battery voltage in millivolts
	 */
	uint32_t 	HAL_get_battery_voltage(void);

#endif /* HALLIB_H_ */

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
//  This file describes the functions exported by the libuXbot
//  library
//
// Date	March 2011
// //////////////////////////////////////////////////

#ifndef UXBOTLIB_H_
#define UXBOTLIB_H_

#include "LPC13xx.h"

/**
  Sensor values (S0 to S11)

  After a call to "get_sensors_binary":
  - 0: The sensor is over a white surface
  - 1: The sensor is over a black surface

   After a call to "get_sensors_analog", the value will be between 0 and 255 depending on the received light
   - High values: The sensor is over a dark surface
   - Low values: The sensor is over a light surface
    
	 */
extern uint32_t S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;

/** uXbot robot initialization function */
void uXbot_Init(void);



// /////////////////////////////////////////////////
// Sensor related functions
// /////////////////////////////////////////////////

	/** Perform a reading of all the twelve sensors and store their binarized value in S0-S11 variables
		0: The sensor is over a white surface
		1:  The sensor is over a black surface

		@section Example
		@code

			//Basic line-folloing example

			int main(void)
			{
				// Init the uXbot robot
				uXbot_Init();

				while(1)
				{
					// Get binarized sensor values 
					get_sensors_binary();

					// If the two central sensors are over black, move forward
					if( S5 == 1  &&  S6 == 1)
						forward(SPEED);

					// If S6 is over white, turn left 
					else if( S5 == 1 && S6 == 0)
						turn_left(SPEED);

					// If S5 is over white, turn right
					else if( S5 == 0 && S6 == 1)
						turn_right(SPEED);

					// If none of the two central sensors is over the line, stop the robot
					else
						stop_motors();
				}
			}

		@endcode
	    */
	void get_sensors_binary(void);

	/** Modify the binarization threshold used by the "get_sensors_binary" function
		@param threshold- Binarization threshold between 0 and 1023 (set to 600 by default)
		*/
	void change_binarization_threshold(int threshold);

	/** Perform a reading of all the twelve sensors and store their  value (0-255) in S0-S11 variables 
		- High values: The sensor is over a dark surface
		- Low values: The sensor is over a light surface
	    */
	void get_sensors_analog(void);


	/** Get how many line segments are being seen by the uXbot
		@return number of segments
		 */
	uint8_t get_num_segments();

	/** Get the center of a particular segment
		A call to "get_num_segments" must be done prior to obtain the center of a segment
		@param segment_index - index of the segment to be analyzed (0 to num_segments)
		@return value between 0 and 255 representing the center of the analyzed segment 

		@section Example
		@code

		// Basic example to always follow the left side of a branch


		int main(void)
		{
			int num_segments;
			int center;

			uXbot_Init();

			while(1)
			{
				num_segments = get_num_segments();
				if(num_segments > 0)
				{
					//  [ 0 --[ROTATE_LEFT]-- 100 --[MOVE_FORWARD]-- 160 --[ROTATE_RIGHT]-- 255 ]
					center = get_segment_center(0);		// Segment at index 0 will be the left most one
					if(center > 160)
						rotate_right(VELOCIDAD);
					else if(center < 100)
						rotate_left(VELOCIDAD);
					else
						forward(VELOCIDAD);
				}
				else
					stop_motors();
			}
		}

		@endcode

		 */
	int get_segment_center(int segment_index);

	/** Compute the width of a particular segment. Useful to detect branches and 90-degrees corners
		@param segment_index - index of the segment to be analyzed (0 to num_segments)
		@return number of sensors  over this particular segment
	 */
	int get_segment_width(int segment_index);


// /////////////////////////////////////////////////
//  LED related functions
// /////////////////////////////////////////////////

	#define LED_OFF		0
	#define LED_ON 		1

	#define LED_D1		0
	#define LED_D2		1
	#define LED_D3		2
	#define LED_D4		3

	/** Set a particular LED to the specified state
		@param led 	- 	LED_D1,LED_D2,LED_D3 or LED_D4
		@param action 	-	LED_OFF or LED_ON
		*/
	void led_set(uint8_t led, uint8_t action);

	/** Switch all the uXbot LEDs on  */
	void turn_leds_on(void);

	/** Switch all the uXbot LEDs off  */
	void turn_leds_off(void);

// /////////////////////////////////////////////////
//  Motor related functions
// /////////////////////////////////////////////////

	/** Move the uXbot forward at the specified speed
		@param speed	- robot speed (0 to 100)
		*/
	void forward(uint8_t speed);

	/** Move the uXbot backward at the specified speed
		@param speed	- robot speed (0 to 100)
		*/
	void backward(uint8_t speed);

	/** Turn right by stopping the right motor 
		and moving the left one forward  at the specified speed
		@param speed	- robot speed (0 to 100)
		*/
	void turn_right(uint8_t speed);

	/** Turn right by stopping the left motor 
		and moving the right one forward at the specified speed
		@param speed	- robot speed (0 to 100)
		*/
	void turn_left(uint8_t speed);

	/** Rotate the robot to the right by moving the right motor backward and the left one
		forward at the specified speed
		@param speed	- robot speed (0 to 100)
		*/
	void rotate_right(uint8_t speed);

	/** Rotate the robot to the left by moving the left motor backward and the right one
		forward at the specified speed
		@param speed	- robot speed (0 to 100)
		*/
	void rotate_left(uint8_t speed);

	/** Stop both motors of the uXbot  */
	void stop_motors(void);

	/** Move the uXbot setting the speed of each motor independently
		@param left_motor	-	Left motor speed (0 to 100). If speed is negative, the motor will spin backward
		@param right_motor	-	Right motor speed (0 to 100). If speed is negative, the motor will spin backward
		*/
	void uXbot_move(int8_t left_motor, int8_t right_motor);

// /////////////////////////////////////////////////
//  Temporization functions
// /////////////////////////////////////////////////

	/** Perform a blocking delay for the specified amount of milliseconds
		@param milliseconds	-	Number of milliseconds to delay

		@section Example
		@code
			//1 second LED blinking example 
			int main()
			{
				uXbot_Init();

				while(1)
				{
					turn_leds_on();
					wait_milliseconds(1000);
					turn_leds_off();
					wait_milliseconds(1000);
				}
			}
		@endcode
	 */
	void wait_milliseconds(uint32_t milliseconds);

	/** Perform a blocking delay for the specified amount of microseconds
		@param microseconds	-	Number of microseconds to delay
	 */
	void wait_microseconds(uint32_t microseconds);

	/** Start a count of the specified number of milliseconds over counter c1
		After a call to this function, the execution won't be suspended
		@param milliseconds	-	Number of milliseconds to count
	*/
	void begin_count1(uint32_t milliseconds);

	/** Check if the previously started count by "begin_count1" is over
		@return	1 if over / 0 if still in progress

		@section Example
		@code
			//Periodic task execution example every 100 ms
			int main()
			{
				uXbot_Init();

				while(1)
				{
					begin_count1(100);

					// Periodic task code goes here
					.....

					//Wait until the count is over to repeat the execution
					while( check_count1_over() == 0 );
				}
			}
		@endcode

	*/
	uint8_t check_count1_over();
	
	/** Start a count of the specified number of milliseconds over counter c2
		After a call to this function, the execution won't be suspended
		@param milliseconds	-	Number of milliseconds to count
	*/
	void begin_count2(uint32_t milliseconds);

	/** Check if the previously started count by "begin_count2" is over
		@return	1 if over / 0 if still in progress
	*/
	uint8_t check_count2_over();


// /////////////////////////////////////////////////
//  Pushbutton related functions
// /////////////////////////////////////////////////

	/** Check whether the uXbot pushbutton 1 is pressed or not
		@return 1 if the pusbutton is pressed / 0 otherwise
	 */
	uint8_t pushbutton1_pressed();

	/** Wait for the pushbutton 1 to be pressed and released 
		*/
	void pushbutton1_wait();

	/** Wait for the pushbutton 1  to be pressed and released. 
		In the meantime, LEDs will blink every 200ms
	 */
	void pushbutton1_wait_blink();

	/** Check whether the uXbot pushbutton 2 is pressed or not
		@return 1 if the pusbutton is pressed / 0 otherwise
	 */
	uint8_t pushbutton2_pressed();

	/** Wait for the pushbutton 12to be pressed and released 
		*/
	void pushbutton2_wait();

	/** Wait for the pushbutton 2  to be pressed and released. 
		In the meantime, LEDs will blink every 200ms
	 */
	void pushbutton2_wait_blink();
// /////////////////////////////////////////////////
//  Battery related functions
// /////////////////////////////////////////////////

	/** Get the uXbot battery voltage (motors switch must be ON)
		@return Battery voltage in millivolts
	 */
	uint32_t get_battery_voltage(void);
	

// /////////////////////////////////////////////////
//  PID Controller
// /////////////////////////////////////////////////

	/** PID controller initialization 
		@param Kp: Proportional constant
		@param Kd: Derivative constant
		@param Ki: Integral constant
		@param base_speed		-	uXbot base speed
		@param max_speed		-	Max. speed of the motors (0 to 100)
		@param min_speed		-	Min. speed of the motors (0 to 100) (The lowest value for the motors will be -min_speed)
		*/
	void initialize_PID(float Kp, float Kd, float Ki, int8_t base_speed, int8_t max_speed, int8_t min_speed);
	
	
	/** Execute the PID controller and update motor speeds
		It's crucial that this function is called at a constant frequency
		@param	error -	Estimated error
		*/
	void execute_PID(int error);

#endif /* UXBOTLIB_H_ */

/**
 * 	\file timelib.c
 *
 *  \date 	01/07/2010
 *  \author uXbot
 */
#include "LPC13xx.h"
#include "HALlib.h"


	/** Perform a blocking delay for the specified amount of milliseconds
		@param milliseconds	-	Number of milliseconds to delay
	 */
	void wait_milliseconds(uint32_t milliseconds)
	{
		HAL_delay_ms(milliseconds);
	}

	/** Perform a blocking delay for the specified amount of microseconds
		@param microseconds	-	Number of microseconds to delay
	 */
	void wait_microseconds(uint32_t microseconds)
	{
		HAL_delay_us(microseconds);
	}

	/** Start a count of the specified number of milliseconds over counter c1
		After a call to this function, the execution won't be suspended
		@param milliseconds	-	Number of milliseconds to count
	*/
	void begin_count1(uint32_t milliseconds)
	{
		HAL_start_counting_ms_c1(milliseconds);
	}

	/** Check if the previously started count by "begin_count1" is over
		@return	1 if over / 0 if still in progress
	*/
	uint8_t check_count1_over()
	{
		return HAL_is_c1_off();
	}

	/** Start a count of the specified number of milliseconds over counter c2
		After a call to this function, the execution won't be suspended
		@param milliseconds	-	Number of milliseconds to count
	*/
	void begin_count2(uint32_t milliseconds)
	{
		HAL_start_counting_ms_c1(milliseconds);
	}

	/** Check if the previously started count by "begin_count2" is over
		@return	1 if over / 0 if still in progress
	*/
	uint8_t check_count2_over()
	{
		return HAL_is_c1_off();
	}
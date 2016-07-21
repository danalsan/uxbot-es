#include "uXbotLib.h"		
#include <stdio.h>
#include <stdlib.h>


/// Speed parameters
#define MAX_SPEED			100 ///< Max speed in %
#define BASE_SPEED			20	///< Base speed in %
#define MIN_SPEED			0	///< Minimum speed in % (if this value is negative, motors might go backwards)

/// PID-loop controller parameters
#define KP	0.4f				///< Proportional constant
#define KD	0.0f				///< Derivative constant
#define KI	0.0f				///< Integral constant

#define PID_FREQUENCY_HZ	100	///< Execution frequency of the PID loop (by default, 100Hz)
#define PERIOD_MS	(1000/PID_FREQUENCY_HZ)	/// Execution period in milliseconds


int main()
{
	
	int error;
	uint8_t num_segments;
	
	uXbot_Init();				///< uXbot hardware initialization
	
	pushbutton1_wait_blink();	///< Wait for the BTN1 to be pressed by the user
	
	initialize_PID(KP, KD, KI, BASE_SPEED,MAX_SPEED, MIN_SPEED);
	
	while(1)
	{
		begin_count1(PERIOD_MS);					///< Periodic execution
		
		num_segments=get_num_segments();			///< Get how many line segments are being seen by the uXbot
		if(num_segments > 0)
		{
			error=128 - get_segment_center(0);		///< If there's at least one, get its center
			execute_PID(error);						///< And execute the PID loop
		}
		else
			stop_motors();							///< If the uXbot lost the line, stop 
		
		while( check_count1_over() == 0 );
	}
}
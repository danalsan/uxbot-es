/*
 * 	\file sensorlib.c
 *
 *  \date 	01/07/2010
 *  \author uXbot
 */
#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "HALlib.h"


//*****************************************
//* 	Constants
//*****************************************
#define NUM_SENSORS				12
#define SENSOR_THRESHOLD		300
#define HYSTERESIS_VALUE		50

//*****************************************
//* 	Type definition
//*****************************************
typedef struct
{
	uint32_t 	sensor_init;
	uint32_t	sensor_end;
	uint32_t 	segment_width;
	uint32_t	center;
} segment_t;

//*****************************************
//* 	Variables
//*****************************************

uint32_t S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;
static uint32_t last_sensors[NUM_SENSORS];		//> Array with the last sensor readings
static uint32_t *ptr_sensors[NUM_SENSORS];		//> Array with pointers to the sensor values
static uint32_t m_sensor_threshold = SENSOR_THRESHOLD;
static uint32_t numlines=0;
extern uint32_t sensors[NUM_SENSORS];
static segment_t segments[8];

//*****************************************
//* 	Functions
//*****************************************
void initialize_sensorlib()
{
	ptr_sensors[0]=&S0;	ptr_sensors[1]=&S1;	ptr_sensors[2]=&S2;	ptr_sensors[3]=&S3;
	ptr_sensors[4]=&S4;	ptr_sensors[5]=&S5;	ptr_sensors[6]=&S6;	ptr_sensors[7]=&S7;
	ptr_sensors[8]=&S8;	ptr_sensors[9]=&S9;	ptr_sensors[10]=&S10;ptr_sensors[11]=&S11;
}

/** Perform a reading of all the twelve sensors and store their binarized value in S0-S11 variables
	0: The sensor is over a white surface
	1:  The sensor is over a black surface
	*/
void get_sensors_binary()
{
	uint32_t i;

	HAL_sensor_read();
	for(i=0;i<NUM_SENSORS;i++)
	{
		if( last_sensors[i] == 1 )
		{
			if(sensors[i] > (m_sensor_threshold+HYSTERESIS_VALUE))
				sensors[i] = 0;
			else
				sensors[i] = 1;
		}
		else
		{
			if(sensors[i] < (m_sensor_threshold-HYSTERESIS_VALUE))
				sensors[i] = 1;
			else
				sensors[i] = 0;
		}

		last_sensors[i] = sensors[i];
		*ptr_sensors[i] = sensors[i];
	}

}

/** Modify the binarization threshold used by the "get_sensors_binary" function
	@param threshold- Binarization threshold between 0 and 1023 (set to 600 by default)
	*/
void change_binarization_threshold(int threshold)
{
	m_sensor_threshold=threshold;
}

/** Perform a reading of all the twelve sensors and store their  value (0-255) in S0-S11 variables 
	- High values: The sensor is over a dark surface
	- Low values: The sensor is over a light surface
	*/
void get_sensors_analog()
{
	uint32_t i;
	HAL_sensor_read();
	for(i=0;i<NUM_SENSORS;i++)
		*ptr_sensors[i] = 255-(uint8_t)((sensors[i]>>2)&0xff);
}




/** Get how many line segments are being seen by the uXbot
	@return number of segments
	 */
uint8_t get_num_segments()
{
	uint32_t  i;
	numlines=0;
	HAL_sensor_read();
	if(sensors[0] < SENSOR_THRESHOLD)
	{
		numlines++;
		segments[numlines-1].sensor_init = 0;
	}
	for(i=1;i<NUM_SENSORS;i++)
	{
		if(sensors[i] < SENSOR_THRESHOLD && sensors[i-1] > SENSOR_THRESHOLD)
		{
				numlines++;
				segments[numlines-1].sensor_init = i;
		}
		else if(sensors[i] > SENSOR_THRESHOLD && sensors[i-1] < SENSOR_THRESHOLD)
		{
				segments[numlines-1].sensor_end = (i-1);
				segments[numlines-1].segment_width  =  segments[numlines-1].sensor_end - segments[numlines-1].sensor_init + 1;
		}

	}

	if(sensors[NUM_SENSORS-1] < SENSOR_THRESHOLD)
	{
		segments[numlines-1].sensor_end = (NUM_SENSORS-1);
		segments[numlines-1].segment_width  =  segments[numlines-1].sensor_end - segments[numlines-1].sensor_init - 1;
	}


	return numlines;
}

/** Get the center of a particular segment
	A call to "get_num_segments" must be done prior to obtain the center of a segment
	@param segment_index - index of the segment to be analyzed (0 to num_segments)
	@return value between 0 and 255 representing the center of the analyzed segment 
	*/
int get_segment_center(int segment_index)
{

	unsigned int avg=0;
	unsigned int sum=0;
	int value,i;

	if(segments[segment_index].sensor_init == 0 && segments[segment_index].segment_width < 6)
		return 0;
	if(segments[segment_index].sensor_end == (NUM_SENSORS-1) && segments[segment_index].segment_width < 6 )
		return 255;

	for(i=segments[segment_index].sensor_init ;i<=segments[segment_index].sensor_end ;i++)
	{
		value=1023-sensors[i];
		if(value > 200)
		{
			avg += (value) * (i * 100);
			sum += value;
		}
	}

	value = ((avg/sum)&0xfffffffe);
 	return ((255*value)/((NUM_SENSORS-1)*100))&0xFF;

}


/** Compute the width of a particular segment. Useful to detect branches and 90-degrees corners
	@param segment_index - index of the segment to be analyzed (0 to num_segments)
	@return number of sensors  over this particular segment
 */
int get_segment_width(int segment_index)
{
	return (segments[segment_index].sensor_end - segments[segment_index].sensor_init);
}

/**
 * \file sensor.c
 *
 * \date 13/06/2010
 */

#include "LPC13xx.h"
#include "adc.h"
#include "gpio.h"
#include "sensor.h"
#include "delay.h"
#include "HALlib.h"


// SENSORS SEL  @   PIO2_10
// LPC_IR_SW	@ 	PIO1_8
// S1/S7  @  AD0
// S2/S8  @  AD1
// S3/S9  @  AD2
// S4/S10 @  AD3
// S5/S11 @  AD6
// S6/S12 @  AD5

#define S1_S7_ADC_CHANNEL	0
#define S2_S8_ADC_CHANNEL	1
#define S3_S9_ADC_CHANNEL	2
#define S4_S10_ADC_CHANNEL	3
#define S5_S11_ADC_CHANNEL	6
#define S6_S12_ADC_CHANNEL	5

#define VBAT_SENSOR_CHANNEL	7

uint32_t sensors[NUM_SENSORS];

/**
 * Initialize sensors on uXbot
 */
void sensor_init(void)
{
	GPIOInit();					///< Init GPIO
	ADCInit( ADC_CLK );			///< Init AD converter
	GPIOSetDir(PORT2, 10, 1);	///< Configure SENSORS_SEL as output
	GPIOSetDir(PORT1, 8, 1);	///< Configure LPC_IR_SW as output
	GPIOSetValue(PORT2, 10, 0);	///< Switch on the IR LED of the sensors
}

/**
 * Read all twelve sensors
 */
void HAL_sensor_read(void)
{
	GPIOSetValue(PORT1, 8, 1);	///< Switch IR led on

	GPIOSetValue(PORT2,10,0);	///< Select mux channel

	HAL_delay_us(100);

	/// Read first 6 sensors
	sensors[0]=ADCRead(S1_S7_ADC_CHANNEL);
	sensors[1]=ADCRead(S2_S8_ADC_CHANNEL);
	sensors[2]=ADCRead(S3_S9_ADC_CHANNEL);
	sensors[3]=ADCRead(S4_S10_ADC_CHANNEL);
	sensors[4]=ADCRead(S5_S11_ADC_CHANNEL);
	sensors[5]=ADCRead(S6_S12_ADC_CHANNEL);

	GPIOSetValue(PORT2,10,1);	///< Select the other mux channel
	HAL_delay_us(100);

	/// Read the remaining 6 sensors
	sensors[6]=ADCRead(S1_S7_ADC_CHANNEL);
	sensors[7]=ADCRead(S2_S8_ADC_CHANNEL);
	sensors[8]=ADCRead(S3_S9_ADC_CHANNEL);
	sensors[9]=ADCRead(S4_S10_ADC_CHANNEL);
	sensors[10]=ADCRead(S5_S11_ADC_CHANNEL);
	sensors[11]=ADCRead(S6_S12_ADC_CHANNEL);

	GPIOSetValue(PORT1, 8, 0);	///< Switch IR led off to save power

}


/**
 * Read the n-th sensor
 * \param index Sensor index (0 to 11)
 */
uint32_t HAL_sensor_read_nth(uint8_t index)
{
	uint32_t adc_val=0;

	GPIOSetValue(PORT1, 8, 1);	///< Switch IR led on

	if(index < 6)				///< Select mux channel
		GPIOSetValue(PORT2,10,0);
	else
	{
		GPIOSetValue(PORT2,10,1);
		index-=6;
	}

	HAL_delay_us(100);

	switch(index)
	{
	case 0:
		adc_val=S1_S7_ADC_CHANNEL;
		break;
	case 1:
		adc_val=S2_S8_ADC_CHANNEL;
		break;
	case 2:
		adc_val=S3_S9_ADC_CHANNEL;
		break;
	case 3:
		adc_val=S4_S10_ADC_CHANNEL;
		break;
	case 4:
		adc_val=S5_S11_ADC_CHANNEL;
		break;
	case 5:
		adc_val=S6_S12_ADC_CHANNEL;
		break;
	}

	adc_val=ADCRead(adc_val);
	GPIOSetValue(PORT1, 8, 0);	///< Switch IR led off

	return adc_val;

}

/**
 * Retrieves battery voltage in milivolts
 */
uint32_t HAL_get_battery_voltage()
{
	/// The read value will be 1/3 of the battery voltage
	return 3.19*ADCRead(VBAT_SENSOR_CHANNEL)*3300/0x3ff;
}


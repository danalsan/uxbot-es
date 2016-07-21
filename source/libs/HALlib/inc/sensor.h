/**
 * \file sensor.h
 *
 *  \date 13/06/2010
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#define NUM_SENSORS	12

void sensor_init(void);
void sensor_read(void);
uint32_t sensor_read_nth(uint8_t index);


#endif /* SENSOR_H_ */

/**
 * 	\file motorlib.c
 *
 *  \date 	01/07/2010
 *  \author uXbot
 */

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "HALlib.h"

void forward(uint8_t speed)
{
	int16_t ispeed = (int16_t) (((uint32_t)speed*(uint32_t)0x3ff)/100);
	HAL_set_motors(ispeed,ispeed);
}

void backward(uint8_t speed)
{
	int16_t ispeed = (int16_t) (((uint32_t)speed*(uint32_t)0x3ff)/100);
	HAL_set_motors(-ispeed,-ispeed);
}

void turn_right(uint8_t speed)
{
	int16_t ispeed = (int16_t) ((uint32_t)speed*(uint32_t)0x3ff)/100;
	HAL_set_motors(ispeed,0);
}

void turn_left(uint8_t speed)
{
	int16_t ispeed = (int16_t) (((uint32_t)speed*(uint32_t)0x3ff)/100);
	HAL_set_motors(0,ispeed);
}

void rotate_right(uint8_t speed)
{
	int16_t ispeed = (int16_t) (((uint32_t)speed*(uint32_t)0x3ff)/100);
	HAL_set_motors(ispeed,-ispeed);
}

void rotate_left(uint8_t speed)
{
	int16_t ispeed = (int16_t) (((uint32_t)speed*(uint32_t)0x3ff)/100);
	HAL_set_motors(-ispeed,ispeed);
}

void stop_motors(void)
{
	HAL_set_motors(0,0);
}

void uXbot_move(int8_t left_motor, int8_t right_motor)
{
	int16_t speedL, speedR;
	speedL = (int16_t) (((int32_t)left_motor*(int32_t)0x3ff)/100);
	speedR = (int16_t) (((int32_t)right_motor*(int32_t)0x3ff)/100);
	HAL_set_motors(speedL, speedR);
}
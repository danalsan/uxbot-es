/**
 * 	\file motorlib.h
 *
 *  \date 	01/07/2010
 *  \author uXbot
 */

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif


void forward(uint8_t speed);

void backward(uint8_t speed);

void turn_right(uint8_t speed);

void turn_left(uint8_t speed);

void rotate_right(uint8_t speed);

void rotate_left(uint8_t speed);

void stop_motors(void);

void uXbot_move(int8_t left_motor, int8_t right_motor);
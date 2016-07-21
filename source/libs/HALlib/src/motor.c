/**
 * \file motor.c
 *
 * \date 14/06/2010
 *
 */

#include "LPC13xx.h"
#include "gpio.h"


// PWM1 @ CT16B1_MAT0
// PWM2 @ CT16B0_MAT0

// Motor1 @ PIO2_4 & PIO2_5
// Motor2 @ PIO2_7 & PIO2_8

#define EMC0	4
#define EMC3	10
#define MATCH0	(1<<0)
#define MATCH3	(1<<3)


#define PWM_FREQUENCY	14400	///< PWM @ 14.4KHz



static __INLINE void RightMotorBackward() 	{GPIOSetValue( PORT2, 4, 0 ); GPIOSetValue( PORT2, 5, 1 ); }
static __INLINE void RightMotorForward() 	{GPIOSetValue( PORT2, 4, 1 ); GPIOSetValue( PORT2, 5, 0 ); }
static __INLINE void LeftMotorBackward() 	{GPIOSetValue( PORT2, 7, 0 ); GPIOSetValue( PORT2, 8, 1 ); }
static __INLINE void LeftMotorForward() 	{GPIOSetValue( PORT2, 7, 1 ); GPIOSetValue( PORT2, 8, 0 ); }


/**
 * Initialize the PWM hardware for uXbot motors
 */
static void pwm_init(void)
{

	/// Power on 16-bit timers
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);

	/// Setup the outputs
	LPC_IOCON->PIO0_8           &= ~0x07;
	LPC_IOCON->PIO0_8           |= 0x02;		///< Timer0_16 MAT0

	LPC_IOCON->PIO1_9           &= ~0x07;
	LPC_IOCON->PIO1_9           |= 0x01;		///< Timer1_16 MAT0

	/// Setup the external match register
	LPC_TMR16B0->EMR = (1<<EMC0) | MATCH0;
	LPC_TMR16B1->EMR = (1<<EMC0) | MATCH0;


	///Enable the selected PWMs and enable Match3
	LPC_TMR16B0->PWMC = MATCH3 | MATCH0;
	LPC_TMR16B1->PWMC = MATCH3 | MATCH0;

	/// Set prescaler
	LPC_TMR16B0->PR  = ((SystemCoreClock/PWM_FREQUENCY)/1024)-1;
	LPC_TMR16B1->PR  = ((SystemCoreClock/PWM_FREQUENCY)/1024)-1;

	/// Set PWM period on MATCH3
	LPC_TMR16B0->MR3 = 0x3ff;
	LPC_TMR16B1->MR3 = 0x3ff;

	LPC_TMR16B0->MR0 = 0x00;
	LPC_TMR16B1->MR0 = 0x00;

	/// Set match control register
	LPC_TMR16B0->MCR = 1<<10;
	LPC_TMR16B1->MCR = 1<<10;

	/// Reset pwm
	LPC_TMR16B0->TCR = 3<<0;
	LPC_TMR16B1->TCR = 3<<0;

	/// Enable pwm
	LPC_TMR16B0->TCR = 1<<0;
	LPC_TMR16B1->TCR = 1<<0;

}

/**
 * Set motor speeds
 * \param left_motor 	left motor speed ranging from 0 to 1023. Sign indicates rotation direction
 * \param right_motor 	right motor speed ranging from 0 to 1023. Sign indicates rotation direction
  */
void HAL_set_motors(int16_t left_motor, int16_t right_motor)
{
	/// right motor and left motor values must be between -1023 and 1023. No sanity checks so far
	if(right_motor < 0)
	{
		right_motor=-right_motor;
		RightMotorBackward();
	}
	else
		RightMotorForward();


	if(left_motor < 0)
	{
		left_motor=-left_motor;
		LeftMotorBackward();
	}
	else
		LeftMotorForward();

	LPC_TMR16B0->MR0 = 0x3ff-left_motor;
	LPC_TMR16B1->MR0 = 0x3ff-right_motor;
}


/**
 * Initialize the motors on uXbot
 */
void motor_init(void)
{
	/// Init GPIO
	GPIOInit();

	/// Configure I/O pins
	GPIOSetDir( PORT2, 4, 1 );	GPIOSetValue( PORT2, 4, 0 );
	GPIOSetDir( PORT2, 5, 1 );	GPIOSetValue( PORT2, 5, 0 );
	GPIOSetDir( PORT2, 7, 1 );	GPIOSetValue( PORT2, 7, 0 );
	GPIOSetDir( PORT2, 8, 1 );	GPIOSetValue( PORT2, 8, 0 );

	/// Init PWM hardware
	pwm_init();

	/// Motors are initially stopped
	HAL_set_motors(0,0);
}


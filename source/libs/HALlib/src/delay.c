/*
 * \file delay.c
 *
 *  \date	13/06/2010
 *
 */
#include "LPC13xx.h"


static volatile uint32_t msTicks;
static uint32_t ms_count1=0;
static uint32_t ms_count2=0;

/**
 * Initialize timing module
 */
void delay_init(void)
{
	SysTick->CTRL  = 0; ///> Disable systick timer
	msTicks=0;
	SysTick_Config(SystemCoreClock / 1000);	///> Enable systick timer every ms
}

/**
 * Delay a number of microseconds.
 * This function makes use of the 32bit TIMER0
 * \param us microseconds to stop the execution
 */
void HAL_delay_us(uint32_t us)
{
    /* setup timer #0 for delay */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);	/* power timer #0 on */
    LPC_TMR32B0->TCR = 0x03;		/* reset timer */
    LPC_TMR32B0->PR  = 0x00;		/* set prescaler to zero */
    LPC_TMR32B0->MR0 = us * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000000);
    LPC_TMR32B0->IR  = 0xff;		/* reset all interrrupts */
    LPC_TMR32B0->MCR = 0x04;		/* stop timer on match */
    LPC_TMR32B0->TCR = 0x01;		/* start timer */

    /* wait until delay time has elapsed */
    while (LPC_TMR32B0->TCR & 0x01);
 }

/**
 * Delay a number of milliseconds.
 * This function makes use of the 32bit TIMER0
 * \param us microseconds to stop the execution
 */
void HAL_delay_ms(uint32_t ms)
{
    /* setup timer #0 for delay */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);	/* power timer #0 on */
    LPC_TMR32B0->TCR = 0x03;		/* reset timer */
    LPC_TMR32B0->PR  = 0x00;		/* set prescaler to zero */
    LPC_TMR32B0->MR0 = ms * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000);
    LPC_TMR32B0->IR  = 0xff;		/* reset all interrrupts */
    LPC_TMR32B0->MCR = 0x04;		/* stop timer on match */
    LPC_TMR32B0->TCR = 0x01;		/* start timer */

    /* wait until delay time has elapsed */
    while (LPC_TMR32B0->TCR & 0x01);
}

/**
 * Systick handler
 */
void SysTick_Handler(void)
{
  msTicks++;                        /* increment counter necessary in Delay() */
}


/**
 * When this function is called, the system will start counting to the specified
 * number of milliseconds
 * To check whether the count is off, user must call the "is_c1_off" function
 * \param ms number of milliseconds to count to
 */
void HAL_start_counting_ms_c1(uint32_t ms)
{
	ms_count1 = msTicks + ms;
}

/**
 * Check whether the already started count is off on counter 1
 * \return 1 if the count's expired / 0 otherwise
 */
uint8_t HAL_is_c1_off(void)
{
	if( msTicks < ms_count1)
		return 0;
	return 1;
}

/**
 * When this function is called, the system will start counting to the specified
 * number of milliseconds
 * To check whether the count is off, user must call the "is_c2_off" function
 * \param ms number of milliseconds to count to
 */
void HAL_start_counting_ms_c2(uint32_t ms)
{
	ms_count2 = msTicks + ms;
}

/**
 * Check whether the already started count is off on counter 2
 * \return 1 if the count's expired / 0 otherwise
 */
uint8_t HAL_is_c2_off(void)
{
	if( msTicks < ms_count2 )
		return 0;
	return 1;
}




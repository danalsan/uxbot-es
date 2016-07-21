/*****************************************************************************
 *   main.c:  Main C file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.20  ver 1.00    Preliminary version, first Release
 *
*****************************************************************************/
#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */
#include "adc.h"

volatile uint32_t ADCValue[ADC_NUM];


/*****************************************************************************
** Function name:		ADCInit
**
** Descriptions:		initialize ADC channel
**
** parameters:			ADC clock rate
** Returned value:		None
**
*****************************************************************************/
void ADCInit( uint32_t ADC_Clk )
{
  /* Disable Power down bit to the ADC block. */
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);

  /* Enable AHB clock to the ADC. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);

  LPC_IOCON->JTAG_TDI_PIO0_11   = 0x02;	// Select AD0 pin function
  LPC_IOCON->JTAG_TMS_PIO1_0    = 0x02;	// Select AD1 pin function
  LPC_IOCON->JTAG_TDO_PIO1_1    = 0x02;	// Select AD2 pin function
  LPC_IOCON->JTAG_nTRST_PIO1_2    = 0x02;	// Select AD3 pin function
//  LPC_IOCON->ARM_SWDIO_PIO1_3    = 0x02;	// Select AD4 pin function
  LPC_IOCON->PIO1_4    = 0x01;	// Select AD5 pin function
  LPC_IOCON->PIO1_10   = 0x01;	// Select AD6 pin function
  LPC_IOCON->PIO1_11   = 0x01;	// Select AD7 pin function

  LPC_ADC->CR = ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/ADC_Clk-1)<<8;

  return;
}

/*****************************************************************************
** Function name:		ADCRead
**
** Descriptions:		Read ADC channel
**
** parameters:			Channel number
** Returned value:		Value read, if interrupt driven, return channel #
**
*****************************************************************************/
uint32_t ADCRead( uint8_t channelNum )
{

  uint32_t regVal, ADC_Data;


  /* channel number is 0 through 7 */
  if ( channelNum >= ADC_NUM )
  {
	channelNum = 0;		/* reset channel number to 0 */
  }
  LPC_ADC->CR &= 0xFFFFFF00; // clear channel selection
  LPC_ADC->CR |= (1 << 24) | (1 << channelNum);

  /* switch channel,start A/D convert */
  while ( 1 )			/* wait until end of A/D convert */
  {
	regVal = *(volatile unsigned long *)(ADC_BASE
			+ ADC_OFFSET + ADC_INDEX * channelNum);
	/* read result of A/D conversion */
	if ( regVal & ADC_DONE )
	{
	  break;
	}
  }

  LPC_ADC->CR &= 0xF8FFFFFF;	/* stop ADC now */
  if ( regVal & ADC_OVERRUN )	/* save data when it's not overrun, otherwise, return zero */
  {
	return ( 0 );
  }
  ADC_Data = ( regVal >> 6 ) & 0x3FF;
  return ( ADC_Data );	/* return A/D conversion value */

}


/*********************************************************************************
**                            End Of File
*********************************************************************************/

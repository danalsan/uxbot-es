/*
Copyright (c) 2010, Daniel Alvarez <daniel@uxbot.es> / Alberto Calvo <alberto@uxbot.es>
http://www.uxbot.es			All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote
   products derived from this software without specific prior
   written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR `AS IS' AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "uXbotLib.h"


/**
	LEDP:
		This example switches on the uXbot LEDs sequentially each time the user presses
		the BTN1 pushbutton.
	*/
int main()
{
	uint8_t led_index = LED_D4;			///< Variable that holds the LED number to be switched on
	
	uXbot_Init();						///< uXbot hardware initialization

	while(1)							///< Infinite loop
	{
		pushbutton1_wait();				///< Wait until the user presses the BTN1 pushbutton
		
		turn_leds_off();					
		led_set(led_index,LED_ON);		///< Switch on this single LED
		
		switch(led_index)				///< Calculate what LED to switch on next
		{
			case LED_D4:				///< If last LED was D4, the next one will be D3
				led_index = LED_D3;
				break;
			case LED_D3:				///< If last LED was D3, the next one will be D2
				led_index = LED_D2;
				break;
			case LED_D2:
				led_index = LED_D1;		///< If last LED was D2, the next one will be D1
				break;
			case LED_D1:
				led_index = LED_D4;		///< If last LED was D1, the next one will be D4 to start over
				break;				
		}
		
	}
}
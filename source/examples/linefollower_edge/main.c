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


#define SPEED 15	///< Motors set at 15% of the max speed

/// Program to follow the left edge of a black line over a white background

int main()
{
	uXbot_Init();					///< uXbot Hardware initialization
	
	pushbutton1_wait_blink();		///< Wait for the BTN1 to be pressed by the user
	
    while(1)						///< Infinite loop
    {
        get_sensors_binary();		///< Binary reading of uXbot sensors

        if( S4 == 0 &&  S5 == 1 )		
			forward(SPEED);
		else if( S4 == 1 && S5 == 1 )	
			turn_left(SPEED);
        else if( S4 == 0 && S5 == 0 )	
			turn_right(SPEED);
        else
			stop_motors();
    }
}

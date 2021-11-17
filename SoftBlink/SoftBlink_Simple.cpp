/*
 * GccApplication1.cpp
 *
 * Created: 17.11.2021 19:28:54
 * Author : kevin
 */ 
#define F_CPU 1000000UL
#define LED_Pin (6)

#include <avr/io.h>
#include <util/delay.h>
unsigned int i = 0;
unsigned int dutycycle = 0;

int main(void)
{	
	DDRD = (1<<LED_Pin);
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);      // Non inverting mode on OC0A and OC0B, Mode = Mode 3 FAST PWM
	TCCR0B = (1<<CS00);
	
	
    while (1) 
    {
		
	if (i == 0)
	{
		_delay_ms(10);
		dutycycle+=1;
		OCR0A = dutycycle;
		if(dutycycle>255)
		{
			i = 1;
		}
	}
	
	if (i == 1)
	{
		_delay_ms(10);
		dutycycle-=1;
		OCR0A = dutycycle;
		if(dutycycle==0)
		{
			i = 0;
		}
	}
		
    }
}



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
	DDRD = (1<<LED_Pin); //definerer LED pin som output
	TCCR0A |=  (1<<WGM00) | (1<<WGM01);// Setter WGM00 og WGM01 til 1 for å sette porten til Fast PWM mode (tabell 12-8 side 87). 
	TCCR0A |= (1<<COM0A1);//Setter COM0A1 til 1 for å bestemme compare output mode(tabell 12-3 side 85).
	TCCR0B = (1<<CS00);// CS00 blir satt til 1, som gir null prescaler(se tabell 12-9 side 77).
	
	
    while (1) 
    {
		//dette er essensielt to for-loops.
		if (i == 0)
		{
			_delay_ms(100);
			dutycycle+=1;
			OCR0A = dutycycle;
			if(dutycycle>20)
			{
				i = 1;
			}
		}
		
		if (i == 1)
		{
			_delay_ms(100);
			dutycycle-=1;
			OCR0A = dutycycle;
			if(dutycycle==0)
			{
				i = 0;
			}
		}
				
    }
}


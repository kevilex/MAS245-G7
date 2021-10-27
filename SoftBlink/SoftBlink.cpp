/*/*
 * test.cpp
 *
 * Created: 09.10.2021 13:11:16
 * Author : kevin
 */ 

#define LED_Pin (6) // man bruker DEFINE for å definere en output pin, man bruker den med #define "ønsket navn til pin" ("pin nummer")
#define F_CPU 1000000UL // Definerer clockspeed


#include <avr/io.h>
#include <math.h> //Not sure about including math.h

#include <util/delay.h> // For å få Delay
#include <avr/interrupt.h>

double dutycycle = 0;
int i = 0;


int main(void)
{
	DDRD = (1<<LED_Pin); // DDRB er "Data Direction Register D". Det er en 8 bit output og når man setter den = 1 så er det en output.

	TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1); //"Timer Counter Control Register A" tar på fast pwm mode. Side 87 i datablad viser at WGM01 og WGM00 må være 1 og på side 85 ser vi at vi trenger COM0A1 for å sette den til compare output mode.
	TIMSK0 = (1 << TOIE0); //"Timer/Counter Interrupt Mask Register" er registeret som XXXXXXX. TOIE0 er overflow
	
	sei(); // "sets internal interrupts" setter i-bitten i interrupten til OCIE0A
	
	TCCR0B = (1 << CS00); //"Timer Counter Control Register B"  velger hvilken pre-scalar vi vil ha. ved pwm trenger vi ikke pre-scalar og vi kan derfor sette CS00 til 0, som vist i datablad på side 88.
	
	while (1)
	{	
		
		if (i == 0)
		{
			_delay_ms(0.01);
			dutycycle+=1;
			
			if(dutycycle>20)
			{
				i = 1;
			}
		}
		
		if (i == 1)
		{
			_delay_ms(0.01);
			dutycycle-=1;
			
			if(dutycycle==0)
			{
				i = 0;
			}
		}
	}
	
	
	return(0);
}
ISR(TIMER0_OVF_vect) //"Interrupt Service Rutine", funksjonen som blir kalt når interrupten er trigget. Vektoren er interrupten.
{
	OCR0A = (dutycycle/100)*255; //"Output Compare Register A" tar er satt til verdien den skal bli sammenliknet med i PWM timeren vår. Vi velger prosenten i dutycycle og ganger med 255 for å få det inn som pwm verdi. Dette steget velger hvor man bryter toppene i figur 12-6 på side 81.
	
}
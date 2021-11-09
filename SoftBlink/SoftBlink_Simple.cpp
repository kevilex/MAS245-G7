/*
 * SoftBlink_Simple.cpp
 *
 * Created: 09.11.2021 13:59:26
 * Author : kevin
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL //setter clockspeed
#define LED_Pin (6) //setter en variabel for led-pin

#include<math.h>
#include<util/delay.h>


double dutycycle = 0;




int main(void)
{
	DDRD = (1<<LED_Pin); //PIN 6 på register D er satt til output
	// Table 15-3 side 101. COM0A1 (Compare Output Mode) gjør at vi får fast pwm som tømmer OC0A når den matcher telleren og setter OC0A på bunnen
	TCCR0A = (COM0A1<<1)
	//  Table 15-8 side 103. WGM01 og WGM00 (Waveform Generation Mode) gjør at vi får fast pwm modus og toppen blir 0xFF og man oppdaterer OCRx på bunnen.
	TCCR0A = (WGM01<<1) | (WGM00<<1);
	// Table 15-9 side 105. Setter pre-scalar, men siden vi ikke har skalert noe, så setter vi CS00 som 1.
	TCCR0A = (CS00<<1);
   
    while (1) 
    {
		//dimmer opp med delay på 10ms slik at man kan se forandringene i lyset.
		for (dutycycle = 0, dutycycle == 255, dutycycle++)
		{
			OCR2A = dutycycle;
			_delay_ms(10);
		}
		//dimmer ned med delay på 10ms slik at man kan se forandringene i lyset.
		for (dutycycle = 255, dutycycle == 0, dutycycle--)
		{
			OCR2A = dutycycle;
			_delay_ms(10);
		}
		
    }
}


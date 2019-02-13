/*
 * main.c
 *
 *  Created on: 9 feb. 2019
 *      Author: josefe
 */

#define F_CPU 20000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "dimmer.h"

//Using fuses lfuse:0xf7 hfuse:0xdf efuse:0x07


ISR(TIMER1_OVF_vect)
{
	freqMeasuringOverflowISR();
}


ISR(TIMER1_CAPT_vect)
{
	zeroCrossingISR();
}

int main (void)
{
	//DDRB|=(1<<2);
	//PORTB&=~(1<<2);
	dimmer_init();
	sei();
	setFiringAngle(150);

	while(1)
	{
		setFiringAngle(15000);
		_delay_ms(500);
		setFiringAngle(5000);
		_delay_ms(500);
	}


}

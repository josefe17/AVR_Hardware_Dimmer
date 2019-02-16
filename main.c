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

void InitADC(void)
{
	// Select Vref=AVcc & Left justified
	ADMUX |= (1<<REFS0) | (1<<ADLAR);
	//set prescaler to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

unsigned char ReadADC(unsigned char ADCchannel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADCH;
}


int main (void)
{
	//DDRB|=(1<<2);
	//PORTB&=~(1<<2);

	dimmer_init();
	sei();
	InitADC();
	while(1)
	{

		//setDimmingValue(ReadADC(0));
		setVoltageRMS(ReadADC(0), 1);
		setVoltageRMS(MAINS_VOLTAGE-ReadADC(0), 2);
		_delay_ms(30);
		//_delay_ms(5000);
	}


}

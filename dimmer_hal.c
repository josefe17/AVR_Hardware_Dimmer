/*
 * File:   dimmer_hal.c
 * Author: Rober
 *
 * Created on 17 April 2017, 10:49
 * Modified on 9 February 2019
 */


#include "dimmer_hal.h"

/* Zero crossing */
void zeroCrossingInit(void)
{
    zeroCrossingInputTris &= ~(1<<zeroCrossingInputPin_bit); //set as input pin
    zeroCrossingInputPort &= ~(1<<zeroCrossingInputPin_bit);
    TCCR1B|=(1<<ICNC1);
    ACSR=0x00;
    zeroCrossingSetEdgeDirection(zeroCrossingRisingEdge);
    zeroCrossingInterruptFlag |= (1<<zeroCrossingInterruptFlag_bit);
    zeroCrossingInterruptEnable |= (1<<zeroCrossingInterruptEnable_bit);
}

/* Firing timer*/
void firing_timer_init(void)
{
	TCNT1H=0; //Clear count??
	TCNT1L=0;
	TCCR1A=(1<<COM1A1); //Clear on compare
	TCCR1B|= (firing_timer_prescaler_mask & firing_timer_prescaler); // Timer already running
	TCCR1C=(1<<FOC1A); //ensure pin is off
	TCCR1A|=(1<<COM1A0); //reconfigure to set on compare

}

/* GPIO functions */
void channel_init (void)
{
	outputChannelTris|=(1<<outputChannelPin_bit); //Set output mode
	outputChannelPort&=~(1<<outputChannelPin_bit);//Write 0 to output
}

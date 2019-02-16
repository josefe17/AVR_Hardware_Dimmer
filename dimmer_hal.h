/*
 * File:   dimmer_hal.h
 * Author: Rober
 *
 * Created on 17 April 2017, 10:49
 * Modified on 9 February 2019
 */

#ifndef DIMMER_HAL_H
#define	DIMMER_HAL_H

#include <avr/io.h>

#ifndef NUM_CHANNELS
	#define NUM_CHANNELS 1
#endif


/*Interrupt flags*/

#define firingTimerInterruptFlag				TIFR1
#define firingTimerInterruptFlag_bit 			OCF1A
#define firingTimerInterruptEnable				TIMSK1
#define firingTimerInterruptEnable_bit 			OCIE1A

#define freqMeasuringOverflowInterruptFlag		TIFR1
#define freqMeasuringOverflowInterruptFlag_bit	TOV1
#define freqMeasuringOverflowInterruptEnable	TIMSK1
#define freqMeasuringOverflowInterruptEnable_bit	TOIE1

/*Firing timer registers*/
#define firing_timer_prescaler 0x02
#define firing_timer_prescaler_mask 0x07

/*Zero crossing registers*/
#define zeroCrossingInputTris 					DDRB
#define zeroCrossingInputPort 					PORTB
#define zeroCrossingInputPin_bit 				0

#define zeroCrossingInterruptFlag 				TIFR1
#define zeroCrossingInterruptFlag_bit			ICF1

#define zeroCrossingInterruptEnable 			TIMSK1
#define zeroCrossingInterruptEnable_bit 		ICIE1

#define zeroCrossingInterruptEdgeSelection    	TCCR1B
#define zeroCrossingInterruptEdgeSelection_bit	ICES1

#define zeroCrossingRisingEdge 					1
#define zeroCrossingFallingEdge 				0

#define channel1 1
#define channel2 2


#define outputChannel1Port 		PORTB
#define outputChannel1Tris		DDRB
#define outputChannel1Pin_bit	1

#define outputChannel2Port 		PORTB
#define outputChannel2Tris		DDRB
#define outputChannel2Pin_bit	2

/*HAL functions*/
void zeroCrossingInit(void);
inline char zeroCrossingCheckFlag(void);
inline void zeroCrossingClearFlag(void);
inline void zeroCrossingSetEdgeDirection(char direction);

void firing_timer_init(void);
inline void firing_timer_enable(void);
inline void firing_timer_disable(void);
inline void firing_timer_reset(void);
inline char firing_timer_check_flag(void);
inline void firing_timer_clear_flag(void);
inline void firing_timer_update_period(unsigned int period, unsigned char channel);

inline void freqMeasuringOverflowInit(void);
inline unsigned int freqMeasuringTimerRead(void);
inline char freqMeasuringOverflowCheckFlag (void);
inline void freqMeasuringOverflowClearFlag(void);
inline void freqMeasuringOverflowDisable(void);

void channel_init (void);
inline void turn_channel_off(void);

/* Zero crossing inline functions*/
inline char zeroCrossingCheckFlag(void)
{
    return ((zeroCrossingInterruptEnable & (1<<zeroCrossingInterruptEnable_bit)) && (zeroCrossingInterruptFlag & (1<<zeroCrossingInterruptFlag_bit)));
}

inline void zeroCrossingClearFlag(void)
{
    zeroCrossingInterruptFlag &= ~(1<<zeroCrossingInterruptFlag_bit);
}

inline void zeroCrossingSetEdgeDirection(char direction)
{
	if (direction==zeroCrossingRisingEdge)
	{
		zeroCrossingInterruptEdgeSelection|=(1<<zeroCrossingInterruptEdgeSelection_bit);
	}
	else
	{
		zeroCrossingInterruptEdgeSelection&=~(1<<zeroCrossingInterruptEdgeSelection_bit);
	}
    //zeroCrossingClearFlag();
}

/* Firing timer inline functions*/
inline void firing_timer_enable(void)
{
	TCCR1A=(1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0); //Set on compare
}

//DEPRECATED
inline void firing_timer_disable(void) //It also turns all off because timer keeps running in background
{
	turn_channel_off();
	//firing_timer_update_period(0xFFFF);
}

inline void firing_timer_reset(void)
{

	TCNT1H=0;
	TCNT1L=0;
}

inline void firing_timer_update_period(unsigned int period, unsigned char channel)
{
	switch (channel)
	{
	case channel1:
		OCR1A=period;
		return;
	case channel2:
		OCR1B=period;
		return;
	default:
		return;
	}
	return;
}

//Not used
inline char firing_timer_check_flag(void)
{
    return ((firingTimerInterruptEnable & (1<<firingTimerInterruptEnable_bit)) && (firingTimerInterruptFlag & (1<<firingTimerInterruptFlag_bit)));
}

//Not used
inline void firing_timer_clear_flag(void)
{
	firingTimerInterruptFlag|=(1<<firingTimerInterruptFlag_bit);
}

/* Frequency measuring timer overflow inline functions */
inline void freqMeasuringOverflowInit (void)
{
	freqMeasuringOverflowInterruptFlag |= (1<< freqMeasuringOverflowInterruptFlag_bit);
	freqMeasuringOverflowInterruptEnable |= (1<<freqMeasuringOverflowInterruptEnable_bit);  //Enable interrupts
}

inline char freqMeasuringOverflowCheckFlag(void)
{
    return ((freqMeasuringOverflowInterruptEnable & (1<<freqMeasuringOverflowInterruptEnable_bit)) &&  (freqMeasuringOverflowInterruptFlag & (1<<freqMeasuringOverflowInterruptFlag_bit)));
}

inline void freqMeasuringOverflowClearFlag(void)
{
	freqMeasuringOverflowInterruptFlag|=(1<<freqMeasuringOverflowInterruptFlag_bit);
}

inline void freqMeasuringOverflowDisable(void)
{
	freqMeasuringOverflowInterruptEnable &= ~(1<<freqMeasuringOverflowInterruptEnable_bit);  //Disable interrupts
}

inline unsigned int freqMeasuringTimerRead(void)
{
//	unsigned char aux = ICR1L;
//    return ((ICR1H<<8) & aux);
	return ICR1;

}

/* GPIO inline functions */
inline void turn_channel_off(void)
{
	TCCR1A=(1<<COM1A1)|(1<<COM1B1); //Clear on compare
	TCCR1C=(1<<FOC1A)|(1<<FOC1B); //ensure pins are off
}


#endif	/* DIMMER_HAL_H */


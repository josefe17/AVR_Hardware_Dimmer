/*
 * File:   dimmer.c
 * Author: Rober
 *
 * Created on 17 April 2017, 10:46
 */


#include "dimmer.h"
#include <avr/pgmspace.h>

//unsigned char firing_map[] = {255, 255, 227, 223, 220, 217, 215, 212, 210, 209, 207, 205, 204, 202, 201, 200, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 181, 180, 179, 178, 178, 177, 176, 175, 175, 174, 173, 172, 172, 171, 170, 170, 169, 168, 168, 167, 166, 166, 165, 164, 164, 163, 163, 162, 161, 161, 160, 160, 159, 158, 158, 157, 157, 156, 156, 155, 154, 154, 153, 153, 152, 152, 151, 151, 150, 149, 149, 148, 148, 147, 147, 146, 146, 145, 145, 144, 144, 143, 143, 142, 142, 141, 140, 140, 139, 139, 138, 138, 137, 137, 136, 136, 135, 135, 134, 134, 133, 133, 132, 132, 131, 131, 130, 130, 129, 129, 128, 128, 127, 127, 126, 126, 125, 125, 124, 124, 123, 123, 122, 122, 121, 121, 120, 120, 119, 119, 118, 118, 117, 117, 116, 116, 115, 115, 114, 114, 113, 113, 112, 112, 111, 111, 110, 110, 109, 109, 108, 107, 107, 106, 106, 105, 105, 104, 104, 103, 103, 102, 102, 101, 100, 100, 99, 99, 98, 98, 97, 97, 96, 95, 95, 94, 94, 93, 92, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 81, 81, 80, 79, 79, 78, 77, 76, 76, 75, 74, 73, 73, 72, 71, 70, 69, 68, 67, 67, 66, 65, 64, 63, 62, 61, 60, 59, 57, 56, 55, 54, 52, 51, 50, 48, 47, 45, 43, 41, 39, 37, 34, 31, 27, 0, 0};
//unsigned char firing_map[] = {255, 219, 214, 210, 207, 204, 202, 200, 198, 196, 195, 193, 192, 191, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 174, 173, 172, 171, 170, 170, 169, 168, 167, 167, 166, 165, 165, 164, 163, 163, 162, 161, 161, 160, 159, 159, 158, 158, 157, 156, 156, 155, 155, 154, 153, 153, 152, 152, 151, 151, 150, 150, 149, 148, 148, 147, 147, 146, 146, 145, 145, 144, 144, 143, 143, 142, 142, 141, 141, 140, 140, 139, 139, 138, 138, 137, 137, 136, 136, 135, 135, 134, 134, 133, 133, 132, 132, 131, 131, 130, 130, 129, 129, 128, 128, 127, 127, 126, 126, 126, 125, 125, 124, 124, 123, 123, 122, 122, 121, 121, 120, 120, 119, 119, 118, 118, 118, 117, 117, 116, 116, 115, 115, 114, 114, 113, 113, 112, 112, 111, 111, 110, 110, 109, 109, 109, 108, 108, 107, 107, 106, 106, 105, 105, 104, 104, 103, 103, 102, 102, 101, 101, 100, 100, 99, 99, 98, 98, 97, 97, 96, 96, 95, 95, 94, 94, 93, 92, 92, 91, 91, 90, 90, 89, 89, 88, 88, 87, 86, 86, 85, 85, 84, 83, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77, 77, 76, 75, 75, 74, 73, 73, 72, 71, 70, 70, 69, 68, 67, 67, 66, 65, 64, 63, 62, 61, 61, 60, 59, 58, 57, 56, 55, 54, 52, 51, 50, 49, 47, 46, 44, 43, 41, 39, 37, 35, 32, 29, 26, 20, 0 };
const unsigned int firingMap[] PROGMEM=   {255, 238, 232, 227, 224, 221, 218, 216, 214, 212, 210, 208, 207, 205, 204, 202, 201, 200, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 180, 179, 178, 177, 176, 176, 175, 174, 173, 173, 172, 171, 170, 170, 169, 168, 168, 167, 166, 166, 165, 164, 164, 163, 162, 162, 161, 160, 160, 159, 158, 158, 157, 157, 156, 155, 155, 154, 154, 153, 152, 152, 151, 151, 150, 149, 149, 148, 148, 147, 147, 146, 145, 145, 144, 144, 143, 143, 142, 141, 141, 140, 140, 139, 139, 138, 138, 137, 136, 136, 135, 135, 134, 134, 133, 133, 132, 132, 131, 131, 130, 129, 129, 128, 128, 127, 127, 126, 126, 125, 125, 124, 124, 123, 123, 122, 121, 121, 120, 120, 119, 119, 118, 118, 117, 117, 116, 116, 115, 114, 114, 113, 113, 112, 112, 111, 111, 110, 110, 109, 108, 108, 107, 107, 106, 106, 105, 105, 104, 103, 103, 102, 102, 101, 101, 100, 99, 99, 98, 98, 97, 96, 96, 95, 95, 94, 93, 93, 92, 92, 91, 90, 90, 89, 89, 88, 87, 87, 86, 85, 85, 84, 83, 83, 82, 81, 81, 80, 79, 78, 78, 77, 76, 75, 75, 74, 73, 72, 72, 71, 70, 69, 68, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 50, 49, 48, 46, 45, 44, 42, 40, 39, 37, 35, 33, 31, 28, 25, 22, 17, 11, 0};

typedef enum
{
    DIMMER_IDLE,
    DIMMER_START_FREQ_MEASURING,
    DIMMER_FREQ_LOADED,
    DIMMER_ZC,
    DIMMER_FIRING
}states;

volatile unsigned int barePeriod;
volatile unsigned int firingAngle;
volatile unsigned int i =0;
states dimmer_status;

void setFiringAngle (volatile unsigned int dimmingValue)
{

//	firingAngle = (unsigned int) (((unsigned long)pgm_read_word(&(firingMap[dimmingValue]))*barePeriod)>>8);

	firingAngle=dimmingValue;

	if (firingAngle==0) //This avoids not triggering when setting to zero because it's the timer reset value
	{
		firingAngle=1; //Timer doesnt't trigger compare during its writing cycle and we do write it to 0 to reset it
	}

	//firingAngle=dimmingValue;

}

volatile unsigned int getBareFrequency(void)
{
    return barePeriod;
}

void dimmer_init (void)
{
	barePeriod=0xFFFF;
    firingAngle=0xFFFF;
    dimmer_status=DIMMER_IDLE;
    channel_init();
    zeroCrossingInit(); //Here zero crossing interrupts start to be enabled
    firing_timer_init(); //Now the timer is running
    freqMeasuringOverflowDisable();
}


void zeroCrossingISR(void)
{
	switch (dimmer_status)
	{
		case DIMMER_START_FREQ_MEASURING: //Falling edge has happened
			zeroCrossingSetEdgeDirection(zeroCrossingRisingEdge); //Wait for rising
			turn_channel_off();
			firing_timer_update_period(0xFFFF); //Ensures nothing fires
			firing_timer_reset(); //Sets count to 0
			freqMeasuringOverflowInit();   //Start first measuring
			//TODO
			//Verify whether the interrupt can trip itsel if timer is resetted
			dimmer_status=DIMMER_FREQ_LOADED; //Next rising is a valid zero crossing
			PORTB&=~(1<<2);
			break;
		case DIMMER_ZC:      //Valid zero crossing
		case DIMMER_FREQ_LOADED: //Rising has happened
			turn_channel_off(); //Turn all triac gates off
			zeroCrossingSetEdgeDirection(zeroCrossingFallingEdge);   //Wait for falling (and re-start firing)
			//firing_timer_disable(); //Stop firing and turs channel off
			barePeriod=freqMeasuringTimerRead(); //Holds measured frequency
			firing_timer_update_period(firingAngle); //update firing angle
			//firing_timer_reset();
			dimmer_status=DIMMER_FIRING; //Next falling is firing!!
			PORTB|=(1<<2);
			break;
		case DIMMER_FIRING: //Falling has happened, firing begins
			zeroCrossingSetEdgeDirection(zeroCrossingRisingEdge); //Wait for rising and zero crossing
			firing_timer_update_period(firingAngle); //update firing angle
			firing_timer_reset();
			firing_timer_enable(); //Reset and start firing timer
			freqMeasuringOverflowInit(); //Measure again
			dimmer_status=DIMMER_ZC; //wait for ZC
			PORTB&=~(1<<2);
			break;
		default:
		case DIMMER_IDLE: //First rising edge has happened
			turn_channel_off(); //Output is off
			zeroCrossingSetEdgeDirection(zeroCrossingFallingEdge); //Wait for falling
			firing_timer_update_period(0xFFFF);        //No firing and sets compare register to top value
			dimmer_status=DIMMER_START_FREQ_MEASURING; //Next falling start measuring
			PORTB|=(1<<2);
			break;
	}
}


void freqMeasuringOverflowISR(void)
{
	PORTB|=(1<<2);
	freqMeasuringOverflowDisable();
	zeroCrossingSetEdgeDirection(zeroCrossingRisingEdge); //Wait for rising
	turn_channel_off();
	//firing_timer_disable();        //No firing
	dimmer_status=DIMMER_IDLE;//wait for new measurement

}

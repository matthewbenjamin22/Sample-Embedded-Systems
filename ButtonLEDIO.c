/*
 * Button & LED Control Source File
 * For Button interrupts, Input, and LED Output
 * Matthew Benjamin
 * Created February 2022
 */

#include <ButtonLEDIO.h>

//------------------------------------------------
//Button Functions

//Interrupt handler - button
void PORTC_PORTD_IRQHandler(void)
{
	//Location defined in startup/startup_MKL46Z4.c
	PORTC->PCR[3] |= (1 << 24); //Clear Interrupt Flag!
	driveStop();//Always stop the rover when the button is pressed - for emergencies!
	setButtonPressed();
}

//Initiate Button switch
void setup_SW1_interrupt()
{
	SIM->SCGC5 |= (1<<11);//Enable Port C Clock
	PORTC->PCR[3] &= ~0xF0703;//Clear MUX
	PORTC->PCR[3] |= 0xF0703 & ((0xA << 16) | (1 << 8) | 0x3 ); //Set MUX bits, enable pullups, interrupt on falling edge
	GPIOC->PDDR &= ~(1 << 3); //Setup Pin 3 Port C as input

	//Call Core API to Enable IRQ
	NVIC_EnableIRQ(31);
}

//Busy delay until button pressed.
void waitForButton()
{
	long i = 0;
    //Wait for the button Press
    do
    {
	    	__asm volatile ("nop");//Do nothin
    }
    while(getButtonPressed() != 1);
    clearButtonPressed();
}

//Accessors and Modifiers
short getButtonPressed(){return buttonPressed;}
void setButtonPressed(){buttonPressed = 1;}
void clearButtonPressed(){buttonPressed = 0;}

//------------------------------------------------------------------------------------------------------------------------------------
//LED Funtions

//Setup LED
void setupLED1()
{
	SIM->SCGC5 |= (1<<12);//Enable Clock
	PORTD->PCR[5] &= ~0x700; //Clear MUX
	PORTD->PCR[5] |= 0x700 & (1 << 8); //Set MUX for GPIO
	GPIOD->PDDR |= (1 << 5); //Setup Data Direction to output
}

//Activate LED
void LEDOn()
{
	GPIOD->PCOR |= (1<<5);//Clear it, because active low
}

//Deactivate LED
void LEDOff()
{
	GPIOD->PSOR |= (1<<5);//Set it, because active low.
}

//Toggle LED
void LEDTog()
{
	GPIOD->PTOR |= (1<<5);
}
/*
 * Line Sensor control source code
 * For sensor setup and reading
 * Matthew Benjamin
 * Created April 2022
 */

#include "LineSensor.h"

//Setup lineSensor functions
void initLineSensors()
{
	//Enable Clock Gating
	SIM->SCGC5 |= (1<<13);//to Port E
	SIM->SCGC6 |= (1<<27);//to ADC Module

	//Clear Mux Pins
	PORTE->PCR[16] &= ~0x700;//Clear
	PORTE->PCR[17] &= ~0x700;//Clear

	//We don't set these mux pins. We keep them at 0 for ADC0.

	// Setup ADC Clock ( < 4 MHz)
	ADC0->CFG1 = 0;  // Default everything

	// Analog Calibrate
	ADC0->SC3 = 0x07; // Enable Maximum Hardware Averaging
	ADC0->SC3 |= 0x80; // Start Calibration

	// Wait for Calibration to Complete (either COCO or CALF)
	while(!(ADC0->SC1[0] & 0x80)){	}

	// Calibration Complete, write calibration registers.
	unsigned short cal_v = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS;
	cal_v = cal_v >> 1 | 0x8000;
	ADC0->PG = cal_v;

	cal_v = 0;
	cal_v = ADC0->CLM0 + ADC0->CLM1 + ADC0->CLM2 + ADC0->CLM3 + ADC0->CLM4 + ADC0->CLMS;
	cal_v = cal_v >> 1 | 0x8000;
	ADC0->MG = cal_v;

	ADC0->SC3 = 0; // Turn off Hardware Averaging
}

//Function to update line sensor values
void updateLineSensors()
{
	//Left Sensor
	ADC0->SC1[0] = (1<<0);//Set Channel to DADP1, Starts Conversion
	while(!(ADC0->SC1[0] & 0x80))//While Conversion not complete...
	{
		__asm volatile("nop");//...Do Nothing
	}
	leftLineValue = ADC0->R[0]; // Resets COCO

	//Right Sensor
	ADC0->SC1[0] = (1<<5);
	while(!(ADC0->SC1[0] & 0x80))//While Conversion not complete...
	{
		__asm volatile("nop");//Do Nothing
	}
	rightLineValue = ADC0->R[0]; // Resets COCO

}

//Accessor Functions

int getLeftLineValue(){ return leftLineValue; }

int getRightLineValue(){ return rightLineValue; }

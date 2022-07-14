/*
 * Button & LED Control Source File
 * For Button interrupts, Input, and LED Output
 * Matthew Benjamin
 * Created February 2022
 */

#include "Root.h"


#ifndef BUTTONINPUT_H_
#define BUTTONINPUT_H_

//Button setup Functions
void PORTC_PORTD_IRQHandler(void);
void setup_SW1_interrupt();

//Button Input Functions
volatile static short buttonPressed = 0;
void waitForButton();
short getButtonPressed();
void setButtonPressed();
void clearButtonPressed();

//LED fucntions
void setupLED1();
void LEDOn();
void LEDOff();
void LEDTog();

#endif /* BUTTONINPUT_H_ */

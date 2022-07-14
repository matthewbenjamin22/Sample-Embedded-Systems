/*
 * Line Sensor control source code
 * For sensor setup and reading
 * Matthew Benjamin
 * Created April 2022
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

#include "Root.h"

volatile static int leftLineValue;
volatile static int rightLineValue;

void initLineSensors();

void updateLineSensors();

int getLeftLineValue();
int getRightLineValue();

#endif /* LINESENSOR_H_ */

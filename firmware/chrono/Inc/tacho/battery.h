/*
 * battery.h
 *
 *  Created on: 28 lis 2022
 *      Author: bartosz
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include "adc.h"


#define LOW_BATTERY_LIMIT 2230



void batteryCheckInit(void);
void batteryReadState(void);


#endif /* BATTERY_H_ */

/*
 * buttons.h
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include <chrono/watch.h>
#include <stdint.h>
#include "main.h"
#include "bd_libs/rtc_bd.h"
#include "bd_libs/bme280_bd.h"


#define AVOID_CONTACT_VIBRATIONS 0


#if AVOID_CONTACT_VIBRATIONS
//after reach these value busy flag are set back to 0
#define TOUCH_COUNTER 10
#endif

//returns of button read function
#define BUTTON_ALL 0
#define BUTTON_START_SET 1
#define BUTTON_START_RESET 2
#define BUTTON_START 3
#define BUTTON_SET_RESET 4
#define BUTTON_SET 5
#define BUTTON_RESET 6
#define BUTTON_NONE 7


#if AVOID_CONTACT_VIBRATIONS
volatile uint16_t touchSensorsTimer; //starts counting when sensor touched
volatile uint16_t touchSensorsBusyFlag; //active when sensor touched
#endif


uint8_t touchRead(void);

#endif /* TOUCH_H_ */

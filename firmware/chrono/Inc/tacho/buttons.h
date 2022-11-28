/*
 * buttons.h
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>
#include "main.h"
#include "watch.h"
#include "bd_libs/rtc_bd.h"
#include "bd_libs/bme280_bd.h"

//returns of button read function
#define BUTTON_ALL 0
#define BUTTON_START_SET 1
#define BUTTON_START_RESET 2
#define BUTTON_START 3
#define BUTTON_SET_RESET 4
#define BUTTON_SET 5
#define BUTTON_RESET 6
#define BUTTON_NONE 7


uint8_t buttonRead(void);

#endif /* BUTTONS_H_ */

/*
 * watch.h
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */

#ifndef WATCH_H_
#define WATCH_H_

#include <stdint.h>

#define WATCH_MODE_NORMAL 0
#define WATCH_MODE_SETTINGS 1


#define WATCH_TIME_SETTINGS_MODE 3
#define WATCH_TIME_DONT_SLEEP 50



#define WATCH_SETTINGS_ITEM_HOUR 1
#define WATCH_SETTINGS_ITEM_MINUTE 2
#define WATCH_SETTINGS_ITEM_SECOND 3
#define WATCH_SETTINGS_ITEM_DAY 4
#define WATCH_SETTINGS_ITEM_MONTH 5
#define WATCH_SETTINGS_ITEM_YEAR 6
#define WATCH_SETTINGS_ITEM_PREF 7
#define WATCH_SETTINGS_ITEM_TOFFSET 8
#define WATCH_SETTINGS_ITEM_BLANK 9

typedef struct {

	uint8_t mode;

	//up counter for settings auto close(if reaches WATCH_SETTINGS_MODE_COUNTER)
	uint8_t counterSettingsMode;


	uint8_t counterDontSleepTimer;

	//for store actually highlighted setting
	uint8_t settingsItem;

	uint8_t flagLowBattery;



} watchTypeDef;

void watchInit(watchTypeDef *watch);
void watchSwitchMode(watchTypeDef *watch, uint8_t mode);
void watchSwitchSettingsItem(watchTypeDef *watch);

#endif /* WATCH_H_ */

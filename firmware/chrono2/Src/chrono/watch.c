/*
 * watch.c
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */


#include <chrono/watch.h>

void watchInit(watchTypeDef *watch){

	watch->mode = WATCH_MODE_NORMAL;
	watch->counterSettingsMode = 0;
	watch->flagLowBattery = 1;
	watch->counterDontSleepTimer = WATCH_TIME_DONT_SLEEP;
}

void watchSwitchMode(watchTypeDef *watch, uint8_t mode){
	watch->mode = mode;
	watch->settingsItem = WATCH_SETTINGS_ITEM_PREF; //after enter settings, set blank1 as default position
}

void watchSwitchSettingsItem(watchTypeDef *watch){
	watch->settingsItem++;
	if(watch->settingsItem > WATCH_SETTINGS_ITEM_BLANK) watch->settingsItem = WATCH_SETTINGS_ITEM_HOUR;
}

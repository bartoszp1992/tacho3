/*
 * timers.c
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */

#include "tacho/timers.h"

#include <tacho/watch.h>

extern watchTypeDef watch;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM3) {

		//auto turn-off settings after 5 seconds
	if (watch.mode == WATCH_MODE_SETTINGS) {
		watch.counterSettingsMode++;
		if(watch.counterSettingsMode > WATCH_TIME_SETTINGS_MODE) {
			watchSwitchMode(&watch, WATCH_MODE_NORMAL);
			watch.counterSettingsMode = 0;
		}
	} else if (watch.mode == WATCH_MODE_NORMAL){
		watch.counterDontSleepTimer++;
		if(watch.counterDontSleepTimer > WATCH_TIME_DONT_SLEEP){
			watch.counterDontSleepTimer = WATCH_TIME_DONT_SLEEP;
		}
	}

}
}

void timersInit(void) {
HAL_TIM_Base_Start_IT(&htim3);
}

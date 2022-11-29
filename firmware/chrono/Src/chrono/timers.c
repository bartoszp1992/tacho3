/*
 * timers.c
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */

#include <chrono/timers.h>
#include <chrono/watch.h>

extern watchTypeDef watch;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM3) { //1Hz

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
#if AVOID_CONTACT_VIBRATIONS
	else if(htim->Instance == TIM6){
		touchSensorsTimer++;
		if(touchSensorsTimer >= TOUCH_COUNTER){
			touchSensorsTimer = 0;
			touchSensorsBusyFlag = 0;
			HAL_TIM_Base_Stop_IT(&htim6);
		}
	}

#endif
}

void timersInit(void) {
HAL_TIM_Base_Start_IT(&htim3);
}

/*
 * buttons.c
 *
 *  Created on: 26 lis 2022
 *      Author: bartosz
 */

#include <chrono/touch.h>

extern watchTypeDef watch;
extern RTCChronoTypeDef chrono;
extern bme280TypeDef atmospherical;
extern TIM_HandleTypeDef htim6;

#if AVOID_CONTACT_VIBRATIONS
volatile uint16_t touchSensorsTimer = 0; //starts counting when sensor touched
volatile uint16_t touchSensorsBusyFlag = 0; //active when sensor touched
#endif

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {

#if AVOID_CONTACT_VIBRATIONS
	if (touchSensorsBusyFlag == 0) {
		touchSensorsBusyFlag = 1;
		HAL_TIM_Base_Start_IT(&htim6); //start counting

#endif

	uint8_t buttonRegister = touchRead();

	if (watch.mode == WATCH_MODE_NORMAL) {
		if (buttonRegister == BUTTON_SET) {
			watchSwitchMode(&watch, WATCH_MODE_SETTINGS);
			watch.counterDontSleepTimer = WATCH_TIME_DONT_SLEEP
					- WATCH_TIME_SETTINGS_MODE + 2;
		} else {
			watch.counterDontSleepTimer = 0;
		}


		if (buttonRegister == BUTTON_START) {

			if (chrono.chronoMode == RTC_CHRONO_MODE_INACTIVE) {
				rtcStartChrono(&chrono);
			} else if (chrono.chronoMode == RTC_CHRONO_MODE_RUNNING) {
				rtcStopChrono(&chrono);
			} else if (chrono.chronoMode == RTC_CHRONO_MODE_STOP) {
				rtcResumeChrono(&chrono);
			}

		} else if (buttonRegister == BUTTON_RESET) {

			if (chrono.chronoMode == RTC_CHRONO_MODE_STOP) {
				rtcResetChrono(&chrono);
			}

		}

	}

	else if (watch.mode == WATCH_MODE_SETTINGS) {
		watch.counterSettingsMode = 0; // if any pressed in settings, refresh timer to avoid exit settings mode

		if (buttonRegister == BUTTON_RESET)
			watchSwitchSettingsItem(&watch);
		else if (buttonRegister == BUTTON_START || buttonRegister == BUTTON_SET) {

			uint8_t upOrDown;
			if (buttonRegister == BUTTON_START)
				upOrDown = RTC_CHANGE_DIR_UP;
			else if (buttonRegister == BUTTON_SET)
				upOrDown = RTC_CHANGE_DIR_DOWN;

			switch (watch.settingsItem) {
			case WATCH_SETTINGS_ITEM_HOUR:
				rtcChangeValue(&chrono, RTC_CHANGE_HOUR, upOrDown);
				break;
			case WATCH_SETTINGS_ITEM_MINUTE:
				rtcChangeValue(&chrono, RTC_CHANGE_MINUTE, upOrDown);
				break;
			case WATCH_SETTINGS_ITEM_SECOND:
				rtcChangeValue(&chrono, RTC_CHANGE_SECOND, upOrDown);
				break;
			case WATCH_SETTINGS_ITEM_DAY:
				rtcChangeValue(&chrono, RTC_CHANGE_DAY, upOrDown);
				break;
			case WATCH_SETTINGS_ITEM_MONTH:
				rtcChangeValue(&chrono, RTC_CHANGE_MONTH, upOrDown);
				break;
			case WATCH_SETTINGS_ITEM_YEAR:
				rtcChangeValue(&chrono, RTC_CHANGE_YEAR, upOrDown);
				break;

			case WATCH_SETTINGS_ITEM_PREF:
				bme280ChangeValue(&atmospherical, BME280_CHANGE_PREF, upOrDown);
				break;

			case WATCH_SETTINGS_ITEM_TOFFSET:
				bme280ChangeValue(&atmospherical, BME280_CHANGE_TOFFSET,
						upOrDown);
				break;
			}

		}

	}
#if AVOID_CONTACT_VIBRATIONS
	}
#endif

}

/*
 * brief: returns button matrix states
 * parameter: none
 * retval: buttons register described in buttons.h
 */
uint8_t touchRead(void) {

	uint8_t touchReg = 0; //stores configuration of pressed buttons

	touchReg = touchReg
			| (HAL_GPIO_ReadPin(BUTTON_START_GPIO_Port, BUTTON_START_Pin) << 2);
	touchReg = touchReg
			| (HAL_GPIO_ReadPin(BUTTON_SET_GPIO_Port, BUTTON_SET_Pin) << 1);
	touchReg = touchReg
			| (HAL_GPIO_ReadPin(BUTTON_RESET_GPIO_Port, BUTTON_RESET_Pin));

	return touchReg;

}

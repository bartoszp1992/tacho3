/*
 * sleep.c
 *
 *  Created on: 8 lis 2022
 *      Author: bartosz
 */

#include <chrono/sleep.h>

void goodNight(void) {
	//enter sleep mode
		EPD_1IN54_V2_Sleep();

	HAL_GPIO_WritePin(LED_WKUP_GPIO_Port, LED_WKUP_Pin, 0);
	HAL_SuspendTick();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

	//on wake up

	HAL_ResumeTick();
	SystemClock_Config();
	HAL_GPIO_WritePin(LED_WKUP_GPIO_Port, LED_WKUP_Pin, 1);
}

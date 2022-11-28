/*
 * battery.c
 *
 *  Created on: 28 lis 2022
 *      Author: bartosz
 */

#include <tacho/battery.h>
#include <tacho/watch.h>

extern watchTypeDef watch;

void batteryCheckInit(void) {
	HAL_ADCEx_Calibration_Start(&hadc1);

}

void batteryReadState(void){
	HAL_ADC_Start(&hadc1);
	if(HAL_ADC_PollForConversion(&hadc1, 200) == HAL_OK){
		uint32_t adcValue = HAL_ADC_GetValue(&hadc1);
		if(adcValue < LOW_BATTERY_LIMIT){
			watch.flagLowBattery = 1;
		}else{
			watch.flagLowBattery = 0;
		}
	}

}

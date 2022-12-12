/*
 * forecast_bd.c
 * addon for bme280_bd  and rtc_bd libraries
 * allow to make simple forecasts, based on barometer and clock readings
 *
 *  Created on: 28 lis 2022
 *      Author: bartosz
 */

#include "bd_libs/forecast_bd.h"

void forecastInit(forecastTypeDef *forecast) {
//	memset(forecast->pressureDatabase, 1013, sizeof(forecast->pressureDatabase));

	for (uint8_t i = 0; i < 24; i++) {
		forecast->pressureDatabase[i] = 1013;
	}

}


/*
 * brief: add pressure measurement, refresh tables od pressures
 */
void forecastAppendActual(forecastTypeDef *forecast, bme280TypeDef *bme280,
		RTCChronoTypeDef *chrono) {
	forecast->pressureDatabase[chrono->actual.hour] = bme280->pressureValue
			/ 100;

	//for debug

//	for(uint8_t i = 0; i<24; i++){
//		forecast->pressureDatabase[i] = 1000+i;
//	}

	//enf of debug

	for (uint8_t i = 0; i < 24; i++) {
		if (chrono->actual.hour >= i) {
			forecast->pastPressureReadings[i] =
					forecast->pressureDatabase[chrono->actual.hour - i];
		} else {
			forecast->pastPressureReadings[i] = forecast->pressureDatabase[24-i+chrono->actual.hour];
		}
	}

}

/*
 * returns pressure difference
 */
//int16_t forecastPressureDifference(forecastTypeDef *forecast, uint8_t hour){
//
//	return forecast->pastPressureReadings[hour];
//}

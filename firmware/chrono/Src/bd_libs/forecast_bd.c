/*
 * forecast_bd.c
 * addon for bme280_bd  and rtc_bd libraries
 * allow to make simple forecasts, based on barometer and clock readings
 *
 *  Created on: 28 lis 2022
 *      Author: bartosz
 */


#include "bd_libs/forecast_bd.h"

void forecastInit(forecastTypeDef *forecast, RTCChronoTypeDef *chrono){
	memset(forecast->pressureDatabase, 1013, sizeof(forecast->pressureDatabase));

}

void forecastSaveValue(forecastTypeDef *forecast, bme280TypeDef *bme280, RTCChronoTypeDef *chrono){
	forecast->pressureDatabase[chrono->actual.hour] = bme280->pressureValue/100;
}

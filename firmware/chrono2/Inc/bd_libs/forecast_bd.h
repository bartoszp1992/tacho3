/*
 * forecast_bd.h
 *
 *  Created on: 28 lis 2022
 *      Author: bartosz
 */

#ifndef FORECAST_BD_H_
#define FORECAST_BD_H_

#include <string.h>
#include <stdint.h>
#include "bd_libs/rtc_bd.h"
#include "bd_libs/bme280_bd.h"

typedef struct{

	//index number corresponds to the hour
uint32_t pressureDatabase[24];//[hPa]

//uint8_t actualHour;

	/*
	 * index corresponds to hour difference.
	 * 0- actual pressure
	 * 1- pressure 1 hour before
	 * 2- pressure 2 hours before
	 * etc up to 24 hours before
	 */
uint32_t pastPressureReadings[24];



}forecastTypeDef;


void forecastInit(forecastTypeDef *forecast);
void forecastAppendActual(forecastTypeDef *forecast, bme280TypeDef *bme280, RTCChronoTypeDef *chrono);
//int16_t forecastPressureDifference(forecastTypeDef *forecast, uint8_t hour);


#endif /* FORECAST_BD_H_ */

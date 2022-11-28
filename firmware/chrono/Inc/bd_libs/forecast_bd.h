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

uint32_t pressureDatabase[24];//[hPa]



}forecastTypeDef;


void forecastInit(forecastTypeDef *forecast, RTCChronoTypeDef *chrono);

#endif /* FORECAST_BD_H_ */

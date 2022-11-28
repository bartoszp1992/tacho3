/*
 * adc.h
 *
 *  Created on: 24 kwi 2022
 *      Author: bartosz
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32g0xx_hal.h"


void Error_Handler(void);
void adcInit(ADC_HandleTypeDef *adcHandler);
void adcSetChannel(ADC_HandleTypeDef *adcHandler, uint32_t channel);
uint32_t adcRead(ADC_HandleTypeDef *adcHandler);
uint32_t adcTemperature(uint32_t adcReading, uint32_t reference);
uint32_t adcVoltage(uint32_t adcReading);




#endif /* ADC_H_ */

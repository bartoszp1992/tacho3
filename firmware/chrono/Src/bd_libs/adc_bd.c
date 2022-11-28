/*
 * adc.c
 * ADC HAL WRAPPER
 *
 *
 * 	Created on: 16 APR 2022
 *      Author: Bartosz
 *      version: 1.0
 *
 *      changelog:
 *
 */

#include "adc.h"

/**
 * @brief  Calibrates ADC
 *
 * @note   none
 *
 * @param  adc handler
 *
 * @retval None
 */
void adcInit(ADC_HandleTypeDef *adcHandler){
	HAL_ADCEx_Calibration_Start(adcHandler);
}

/**
 * @brief  Set actual channel for measurement
 *
 * @note   none
 *
 * @param  adc handler
 *
 * @param adc channel- e.g. ADC_CHANNEL_0, ADC_CHANNEL_TEMPSENSOR
 *
 * @retval None
 */
void adcSetChannel(ADC_HandleTypeDef *adcHandler, uint32_t channel) {

	ADC_ChannelConfTypeDef chConf = { 0 };
	chConf.Channel = channel;
	chConf.Rank = ADC_REGULAR_RANK_1;
	chConf.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;

	if (HAL_ADC_ConfigChannel(adcHandler, &chConf) != HAL_OK) {
		Error_Handler();
	}

}

/**
 * @brief  Reads ADC value
 *
 * @note   none
 *
 * @param  adc handler
 *
 * @retval raw adc reading
 */
uint32_t adcRead(ADC_HandleTypeDef *adcHandler){
	HAL_ADC_Start(adcHandler);

	while(HAL_ADC_PollForConversion(adcHandler, 100) != HAL_OK);
	return HAL_ADC_GetValue(adcHandler);


}

/**
 * @brief  Count temperature from reading
 *
 * @note   works correctly only with ADC_CHANNEL_TEMPSENSOR channel
 *
 * @param  adc handler
 *
 * @retval temperature in Celcius degree
 */
uint32_t adcTemperature(uint32_t adcReading, uint32_t reference){
	return __HAL_ADC_CALC_TEMPERATURE(reference, adcReading, ADC_RESOLUTION_12B);
}


/**
 * @brief  Count voltage from reading
 *
 * @note   none
 *
 * @param  adc handler
 *
 * @retval voltage in mV
 */
uint32_t adcVoltage(uint32_t adcReading){
//	return (3300*1000)/4095;
	return __HAL_ADC_CALC_VREFANALOG_VOLTAGE(adcReading, ADC_RESOLUTION_12B);
}



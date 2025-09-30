/*
 * bme280.h
 *
 *  Created on: 28 kwi 2022
 *      Author: bartosz
 */

#ifndef BME280_H_
#define BME280_H_

#include "stm32g0xx_hal.h"
#include <math.h>

//									CHANGING Pressure reference(for counting altitude) and temperature compensation
#define BME280_CHANGE_PREF 1
#define BME280_CHANGE_TOFFSET 0

#define BME280_CHANGE_DIR_UP 0
#define BME280_CHANGE_DIR_DOWN 1


//									CONFIGURATION / MODES
#define BME280_SKIPPED 0x00
#define BME280_OVERSAMPLING_DISABLED 0x1
#define BME280_OVERSAMPLING_X2 0x2
#define BME280_OVERSAMPLING_X4 0x3
#define BME280_OVERSAMPLING_X8 0x4
#define BME280_OVERSAMPLING_X16 0x5

#define BME280_IIR_OFF 0x0
#define BME280_IIR_2 0x1
#define BME280_IIR_4 0x2
#define BME280_IIR_8 0x4
#define BME280_IIR_16 0x4

//USER CONFIGURATION
#define BME280_I2C_TIMEOUT 100

#define BME280_OVERSAMPLING_HUM BME280_OVERSAMPLING_X16
#define BME280_OVERSAMPLING_TEM BME280_OVERSAMPLING_X16
#define BME280_OVERSAMPLING_PRE BME280_OVERSAMPLING_X16

#define BME280_IIR_FILTER BME280_IIR_4




typedef struct {
	uint8_t i2cAddr;
//									DATA OUTPUT
	int32_t temperatureValue; //[Celsius cDegree]
	uint32_t pressureValue; //[Pa]
	uint32_t humidityValue; //[% RH]
	int32_t altitudeValue; //[cm]
	uint32_t pressureReference; //hPa
	int32_t temperatureOffset; //[Celsius Degree]- for store temperature offset
	int32_t temperatureValueCompensated; //[Celsius cDegree] for store temperature corrected by offset

//									MODE/OVERSAMPLING CONFIG
	uint8_t ctrlMeas;
	uint8_t ctrlHum ;

//									CONFIG
	uint8_t config;

//									i2c timeout
	uint8_t i2cTimeout;

//									VARIABLES FOR STORE COMPENSATION DATA
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;

	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;

	unsigned char dig_H1;
	int16_t dig_H2;
	unsigned char dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	unsigned char dig_H6;

	int32_t t_fine;


	I2C_HandleTypeDef *I2Chandler;


}bme280TypeDef;

void bme280Init(bme280TypeDef *bme280, I2C_HandleTypeDef *I2Chandler);
void bme280Read(bme280TypeDef *bme280);
void bme280ChangeValue(bme280TypeDef *bme280, uint8_t value, uint8_t direction);

#endif /* BME280_H_ */

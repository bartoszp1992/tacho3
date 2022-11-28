/*
 * lis3mdl.h
 *
 *  Created on: 17 cze 2022
 *      Author: bartosz
 */

#ifndef LIS3MDL_H_
#define LIS3MDL_H_

#include "stm32g0xx_hal.h"
#include <math.h>


//									CONFIGURATION

#define LIS3MDL_CTRL1_REG_OM_LP 0x0 //default
#define LIS3MDL_CTRL1_REG_OM_MP 0x1
#define LIS3MDL_CTRL1_REG_OM_HP 0x2
#define LIS3MDL_CTRL1_REG_OM_UHP 0x3

#define LIS3MDL_CTRL1_REG_ODR_0_625 0x0
#define LIS3MDL_CTRL1_REG_ODR_1_25 0x1
#define LIS3MDL_CTRL1_REG_ODR_2_5 0x2
#define LIS3MDL_CTRL1_REG_ODR_5 0x3
#define LIS3MDL_CTRL1_REG_ODR_10 0x4//default
#define LIS3MDL_CTRL1_REG_ODR_20 0x5
#define LIS3MDL_CTRL1_REG_ODR_40 0x6
#define LIS3MDL_CTRL1_REG_ODR_80 0x7

#define LIS3MDL_CTRL2_REG_FS_4G 0x0//default
#define LIS3MDL_CTRL2_REG_FS_8G 0x1
#define LIS3MDL_CTRL2_REG_FS_12G 0x2
#define LIS3MDL_CTRL2_REG_FS_16G 0x3

//#define LIS3MDL_CTRL3_REG_MODE_CONTINOUS 0x0
#define LIS3MDL_CTRL3_REG_MODE_SINGLE 0x1
#define LIS3MDL_CTRL3_REG_MODE_POWERDOWN 0x2


//USER CONFIGURATION
#define LIS3MDL_I2C_TIMEOUT 100
#define LIS3MDL_CTRL1_REG_OM LIS3MDL_CTRL1_REG_OM_LP
#define LIS3MDL_CTRL1_REG_ODR LIS3MDL_CTRL1_REG_ODR_10
#define LIS3MDL_CTRL2_REG_FS LIS3MDL_CTRL2_REG_FS_4G

#define LIS3MDL_CONTAINER_SIZE 100 //calibration container size



typedef struct{

	int16_t xValue;
	int16_t yValue;
	int16_t zValue;

	int16_t xCalibrated;
	int16_t yCalibrated;
	int16_t zCalibrated;

	uint16_t measurementCounter;//for store number of conversion

	//calibration containers
	int16_t xValueContainter[LIS3MDL_CONTAINER_SIZE];
	int16_t yValueContainter[LIS3MDL_CONTAINER_SIZE];
	int16_t zValueContainter[LIS3MDL_CONTAINER_SIZE];

	int16_t xMax, yMax, zMax;
	int16_t xMin, yMin, zMin;

	int16_t xMid, yMid, zMid;

	//compass angle[RAD]
	float compassAngleXY;
	float compassAngleXZ;
	float compassAngleYZ;

	I2C_HandleTypeDef *I2Chandler;

}lis3mdlTypeDef;


void lis3mdlInit(lis3mdlTypeDef *lis3mdl, I2C_HandleTypeDef *I2Chandler);
void lis3mdlRead(lis3mdlTypeDef *lis3mdl);
void lis3mdlGetCalibrationSample(lis3mdlTypeDef *lis3mdl);

#endif /* LIS3MDL_H_ */

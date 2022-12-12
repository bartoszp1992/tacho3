/*
 * lis3mdl.c
 *
 *  Created on: 17 cze 2022
 *      Author: bartosz
 */

#include <bd_libs/lis3mdl_bd.h>

//									MAIN I2C ADDRESS, STATUS AND CONTROL REGISTER
#define LIS3MDL_ADDR 0x1C<<1

#define LIS3MDL_WHO_AM_I 0x0F
#define LIS3MDL_CTRL_REG1 0x20
#define LIS3MDL_CTRL_REG2 0x21
#define LIS3MDL_CTRL_REG3 0x22
#define LIS3MDL_CTRL_REG4 0x23
#define LIS3MDL_CTRL_REG5 0x24
#define LIS3MDL_STATUS_REG 0x27

//									DATA REGISTERS
#define LIS3MDL_OUT_X_L 0x28
#define LIS3MDL_OUT_X_H 0x29
#define LIS3MDL_OUT_Y_L 0x2A
#define LIS3MDL_OUT_Y_H 0x2B
#define LIS3MDL_OUT_Z_L 0x2C
#define LIS3MDL_OUT_Z_H 0x2D

int16_t findMax(int16_t *data, uint16_t size);
int16_t findMin(int16_t *data, uint16_t size);

/**
 * @brief  Initialize sensor
 *
 * @note   none
 *
 * @param  LIS3MDL handler
 *
 * @param  I2C handler
 *
 * @retval None
 */
void lis3mdlInit(lis3mdlTypeDef *lis3mdl, I2C_HandleTypeDef *I2Chandler) {
	uint8_t ctrl1 = LIS3MDL_CTRL1_REG_OM << 6 | LIS3MDL_CTRL1_REG_ODR << 4;
	uint8_t ctrl2 = LIS3MDL_CTRL2_REG_FS << 6;
	uint8_t ctrl3 = LIS3MDL_CTRL3_REG_MODE_POWERDOWN;
	HAL_I2C_Mem_Write(I2Chandler, LIS3MDL_ADDR, LIS3MDL_CTRL_REG1, 1, &ctrl1, 1,
	LIS3MDL_I2C_TIMEOUT);
	HAL_I2C_Mem_Write(I2Chandler, LIS3MDL_ADDR, LIS3MDL_CTRL_REG2, 1, &ctrl2, 1,
	LIS3MDL_I2C_TIMEOUT);
	HAL_I2C_Mem_Write(I2Chandler, LIS3MDL_ADDR, LIS3MDL_CTRL_REG3, 1, &ctrl3, 1,
	LIS3MDL_I2C_TIMEOUT);
	lis3mdl->I2Chandler = I2Chandler;
}

/**
 * @brief  Read data
 *
 * @note   Data are stored in lis3mdl structure
 *
 * @param  LIS3MDL handler
 *
 * @retval None
 */
void lis3mdlRead(lis3mdlTypeDef *lis3mdl) {

	uint8_t ctrl3 = LIS3MDL_CTRL3_REG_MODE_SINGLE; //set single
	HAL_I2C_Mem_Write(lis3mdl->I2Chandler, LIS3MDL_ADDR, LIS3MDL_CTRL_REG3, 1,
			&ctrl3, 1, LIS3MDL_I2C_TIMEOUT); //turn on
	HAL_Delay(10);
	uint8_t readings[6];

	HAL_I2C_Mem_Read(lis3mdl->I2Chandler, LIS3MDL_ADDR, LIS3MDL_OUT_X_H, 1,
			readings, 6, LIS3MDL_I2C_TIMEOUT); //read

	ctrl3 = LIS3MDL_CTRL3_REG_MODE_POWERDOWN; //set power down
	HAL_I2C_Mem_Write(lis3mdl->I2Chandler, LIS3MDL_ADDR, LIS3MDL_CTRL_REG3, 1,
			&ctrl3, 1, LIS3MDL_I2C_TIMEOUT); //turn off

	lis3mdl->xValue = (uint16_t) readings[0] << 8 | readings[1];
	lis3mdl->yValue = (uint16_t) readings[2] << 8 | readings[3];
	lis3mdl->zValue = (uint16_t) readings[4] << 8 | readings[5];

	//search for max and min values in conatainer
	lis3mdl->xMax = findMax(lis3mdl->xValueContainter,
	LIS3MDL_CONTAINER_SIZE);
	lis3mdl->yMax = findMax(lis3mdl->yValueContainter,
	LIS3MDL_CONTAINER_SIZE);
	lis3mdl->zMax = findMax(lis3mdl->zValueContainter,
	LIS3MDL_CONTAINER_SIZE);

	lis3mdl->xMin = findMin(lis3mdl->xValueContainter,
	LIS3MDL_CONTAINER_SIZE);
	lis3mdl->yMin = findMin(lis3mdl->yValueContainter,
	LIS3MDL_CONTAINER_SIZE);
	lis3mdl->zMin = findMin(lis3mdl->zValueContainter,
	LIS3MDL_CONTAINER_SIZE);

	//count mid values
	lis3mdl->xMid = (lis3mdl->xMax + lis3mdl->xMin) / 2;
	lis3mdl->yMid = (lis3mdl->yMax + lis3mdl->yMin) / 2;
	lis3mdl->zMid = (lis3mdl->zMax + lis3mdl->zMin) / 2;

	//correct measurement with calibration data
	lis3mdl->xCalibrated = lis3mdl->xValue - lis3mdl->xMid;
	lis3mdl->yCalibrated = lis3mdl->yValue - lis3mdl->yMid;
	lis3mdl->zCalibrated = lis3mdl->zValue - lis3mdl->zMid;

	lis3mdl->compassAngleXY = atan2((double) lis3mdl->yCalibrated,
			(double) lis3mdl->xCalibrated);
	lis3mdl->compassAngleXZ = atan2((double) lis3mdl->zCalibrated,
			(double) lis3mdl->xCalibrated);
	lis3mdl->compassAngleYZ = atan2((double) lis3mdl->zCalibrated,
			(double) lis3mdl->yCalibrated);

}

/**
 * @brief  Get sample for calibration
 *
 * @note   Collect sample of data required for calculate offset in "Calibrated" values
 *
 * @param  LIS3MDL handler
 *
 * @retval None
 */
void lis3mdlGetCalibrationSample(lis3mdlTypeDef *lis3mdl) {

	//store actual values into calibration containter
	lis3mdl->xValueContainter[lis3mdl->measurementCounter] = lis3mdl->xValue;
	lis3mdl->yValueContainter[lis3mdl->measurementCounter] = lis3mdl->yValue;
	lis3mdl->zValueContainter[lis3mdl->measurementCounter] = lis3mdl->zValue;

	//increment counter of actually readed value
	lis3mdl->measurementCounter++;
	if (lis3mdl->measurementCounter > (LIS3MDL_CONTAINER_SIZE - 1))
		lis3mdl->measurementCounter = 0;
}

int16_t findMax(int16_t *data, uint16_t size) {

	int16_t max = -32768;
	for (uint32_t i = 0; i < size; i++) {
		if (data[i] > max)
			max = data[i];
	}

	return max;

}
int16_t findMin(int16_t *data, uint16_t size) {
	int16_t min = 32767;
	for (uint32_t i = 0; i < size; i++) {
		if (data[i] < min)
			min = data[i];
	}

	return min;
}

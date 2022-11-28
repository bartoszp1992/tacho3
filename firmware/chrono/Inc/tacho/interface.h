/*
 * interface_bd.h
 *
 *  Created on: 5 lis 2022
 *      Author: bartosz
 */

#ifndef INTERFACE_BD_H_
#define INTERFACE_BD_H_

#include "tacho/interface.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "Display_EPD/EPD_1in54_V2.h"
#include "Display_Config/DEV_Config.h"
#include "Display_GUI/GUI_Paint.h"

#include "bd_libs/rtc_bd.h"
#include "bd_libs/bme280_bd.h"
#include "bd_libs/lis3mdl_bd.h"
#include "watch.h"
#include <string.h>

#define X 0
#define Y 1
#define EN 2
#define NUMBER EN

#define INTERFACE_ELEMENT_ENABLED 0
#define INTERFACE_ELEMENT_DISABLED 1

#define INTERFACE_UPDATE_MODE_FULL 0
#define INTERFACE_UPDATE_MODE_PARTIAL 1

#define INTERFACE_COLOR_WHITE WHITE
#define INTERFACE_COLOR_BLACK BLACK

//			Settings numbers - only for elements whitch can be changed by user
//			for incrementing in settings
//enum settings{
//	hours,
//	minutes,
//	seconds,
//	days,
//	months,
//	years,
//	pressureReference,
//	temperatureCompensation
//
//};

typedef struct {

	/*
	 * positions and enable
	 * for each:
	 * 0- X position
	 * 1- Y position
	 * 2- enabled/disabled
	 */

	uint8_t coordinatesMain[3];
	uint8_t coordinatesChronoMinutes[3];
	uint8_t coordinatesChronoDecimals[3];
	uint8_t coordinatesTemperature[3];
	uint8_t coordinatesHumidity[3];
	uint8_t coordinatesPressure[3];
	uint8_t coordinatesCompass[3];
	uint8_t coordinatesDate[3];
	uint8_t coordinatesBatteryState[3];
	uint8_t coordinatesMoonPhase[3];

	//radii of dials
	uint8_t radiusMain;
	uint8_t radiusSmall;
	uint8_t radiusCompass;
	uint8_t radiusMoonPhase;

	//pointer lengths
	uint8_t pointerLengthHours; //for main board
	uint8_t pointerLengthMinutes; //for main board
	uint8_t pointerLengthChronoSeconds;
	uint8_t pointerLengthChronoMinutes;
	uint8_t pointerLengthChronoDecimals;
	uint8_t pointerLengthBatteryState;
	uint8_t pointerLengthPressure;
	uint8_t pointerLenghtCompass;

	//indexes lengths
	uint8_t indexLengthChronoDecimals;
	uint8_t indexLengthChronoMinutes;
	uint8_t indexLengthMain;

	//pointer shifts
	/*
	 * pointer shift describes shift between center position and pointer beginning
	 */
	uint8_t pointerShiftPressure;

	//pointers angles
	float pointerAngleHours;
	float pointerAngleMinutes;
	float pointerAngleChronoDecimals;
	float pointerAngleChronoSeconds;
	float pointerAngleChronoMinutes;

	float pointerAngleBatteryState;
	float pointerAngleCompass;
	float pointerAnglePressure;

	//indexes angles
	float indexAngleChronoDecimals[10];
	float indexAngleChronoMinutes[30];
	float indexAngleMain[12];

	//shadow shift
	uint8_t shadowShift;

	//colors
	uint8_t colorBackground;
	uint8_t colorForeground;

	//pointer to framebuffer
	uint8_t *framebuffer;

	uint8_t updateMode;


} interfaceTypeDef;

typedef struct{



	//		coordinates- X[0], Y[1] and setting number[2]
	//		settings number only for changeable values
	//clock
	uint8_t coordinatesHours[3];
	uint8_t coordinatesMinutes[3];
	uint8_t coordinatesSeconds[3];

	//date
	uint8_t coordinatesDays[3];
	uint8_t coordinatesMonths[3];
	uint8_t coordinatesYears[3];

	//others
	uint8_t coordinatesPressureReference[3];
	uint8_t coordinatesTemperatureCompensation[3];

	//not changeable
	uint8_t coordinatesTemperature[2];
	uint8_t coordinatesHumidity[2];
	uint8_t coordinatesPressure[2];
	uint8_t coordinatesAltitude[2];

	uint8_t colorBackground;
	uint8_t colorForeground;



}interfaceSettingsTypeDef;


void interfaceClear(interfaceTypeDef *interface);
void interfaceUpdateModeSwitch(interfaceTypeDef *interface, uint8_t mode);
void interfaceInit(interfaceTypeDef *interface);
void interfaceDraw(interfaceTypeDef *interface, RTCChronoTypeDef *chrono,
		lis3mdlTypeDef *magnetometer, bme280TypeDef *atmospherical,
		watchTypeDef *watch);

void interfaceSettingsClear(interfaceSettingsTypeDef *settings);
void interfaceSettingsInit(interfaceSettingsTypeDef *settings);
void interfaceSettingsDraw(interfaceSettingsTypeDef *settings,
		RTCChronoTypeDef *chrono, lis3mdlTypeDef *magnetometer,
		bme280TypeDef *atmospherical, watchTypeDef *watch);

void interfaceBurn(interfaceTypeDef *interface);

#endif /* INTERFACE_BD_H_ */

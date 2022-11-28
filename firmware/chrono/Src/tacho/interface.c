/*
 * interface.c
 *
 *  Created on: 5 lis 2022
 *      Author: bartosz
 *
 *      libra interface for EPD watch
 */

#include <tacho/interface.h>

/*
 * brief: initialisation of watch interface
 * note: remember of set coordintaes, lenghts etc. outside
 * param: interface struct
 * retval: none
 */
void interfaceInit(interfaceTypeDef *interface) {

//			display init

	printf("EPD_1in54_V2_test Demo\r\n");
	DEV_Module_Init();

	printf("e-Paper Init and Clear...\r\n");
	EPD_1IN54_V2_Init();
	EPD_1IN54_V2_Clear();
	DEV_Delay_ms(500);

	//Create a new image cache
	/* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
	uint16_t Imagesize = (
			(EPD_1IN54_V2_WIDTH % 8 == 0) ?
					(EPD_1IN54_V2_WIDTH / 8) : (EPD_1IN54_V2_WIDTH / 8 + 1))
			* EPD_1IN54_V2_HEIGHT;
	if ((interface->framebuffer = (uint8_t*) malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		// return -1;
	}
	printf("Paint_NewImage\r\n");
	Paint_NewImage(interface->framebuffer, EPD_1IN54_V2_WIDTH,
	EPD_1IN54_V2_HEIGHT, 0, interface->colorForeground);

	interfaceUpdateModeSwitch(interface, INTERFACE_UPDATE_MODE_FULL);

	interface->coordinatesMain[X] = 100;
	interface->coordinatesMain[Y] = 100;

	interface->coordinatesChronoMinutes[X] = 100;
	interface->coordinatesChronoMinutes[Y] = 150;

	interface->coordinatesChronoDecimals[X] = 100;
	interface->coordinatesChronoDecimals[Y] = 50;

	interface->coordinatesTemperature[X] = 22;
	interface->coordinatesTemperature[Y] = 44;

	interface->coordinatesHumidity[X] = 130;
	interface->coordinatesHumidity[Y] = 75;

	interface->coordinatesPressure[X] = 100;
	interface->coordinatesPressure[Y] = 100;

	interface->coordinatesCompass[X] = 55;
	interface->coordinatesCompass[Y] = 100;

	interface->coordinatesDate[X] = 149;
	interface->coordinatesDate[Y] = 93;

	interface->coordinatesBatteryState[X] = 130;
	interface->coordinatesBatteryState[Y] = 135;

	interface->coordinatesMoonPhase[X] = 150;
	interface->coordinatesMoonPhase[Y] = 50;

	interface->radiusMain = 97;
	interface->radiusSmall = 28;
	interface->radiusCompass = 25;
	interface->radiusMoonPhase = 10;

	interface->pointerLengthHours = 55;
	interface->pointerLengthMinutes = 80;
	interface->pointerLengthChronoSeconds = 80;
	interface->pointerLengthChronoMinutes = 20;
	interface->pointerLengthChronoDecimals = 20;
	interface->pointerLengthBatteryState = 35;
	interface->pointerLengthPressure = 100;
	interface->pointerLenghtCompass = 18;
	interface->pointerShiftPressure = 80;

	interface->indexLengthChronoDecimals = 4;
	interface->indexLengthChronoMinutes = 2;
	interface->indexLengthMain = 10;

	interface->shadowShift = 2;
	interface->colorBackground = INTERFACE_COLOR_BLACK;
	interface->colorForeground = INTERFACE_COLOR_WHITE;
}

void interfaceSettingsInit(interfaceSettingsTypeDef *settings) {
	settings->coordinatesTemperature[X] = 70;
	settings->coordinatesTemperature[Y] = 5;

	settings->coordinatesHumidity[X] = 40;
	settings->coordinatesHumidity[Y] = 20;

	settings->coordinatesPressure[X] = 30;
	settings->coordinatesPressure[Y] = 35;

	settings->coordinatesAltitude[X] = 20;
	settings->coordinatesAltitude[Y] = 50;

	settings->coordinatesHours[X] = 10;
	settings->coordinatesHours[Y] = 80;

	settings->coordinatesMinutes[X] = 50;
	settings->coordinatesMinutes[Y] = 80;

	settings->coordinatesSeconds[X] = 90;
	settings->coordinatesSeconds[Y] = 80;

	settings->coordinatesDays[X] = 10;
	settings->coordinatesDays[Y] = 100;

	settings->coordinatesMonths[X] = 50;
	settings->coordinatesMonths[Y] = 100;

	settings->coordinatesYears[X] = 90;
	settings->coordinatesYears[Y] = 100;

	settings->coordinatesPressureReference[X] = 20;
	settings->coordinatesPressureReference[Y] = 125;

	settings->coordinatesTemperatureCompensation[X] = 30;
	settings->coordinatesTemperatureCompensation[Y] = 140;

	settings->colorBackground = INTERFACE_COLOR_WHITE;
	settings->colorForeground = INTERFACE_COLOR_BLACK;
}

/*
 * brief: change update method
 * note: full or partial EPD refresh
 * param: interface struct
 * param: INTERFACE_UPDATE_MODE_FULL / INTERFACE_UPDATE_MODE_PARTIAL
 */
void interfaceUpdateModeSwitch(interfaceTypeDef *interface, uint8_t mode) {
	if (mode == INTERFACE_UPDATE_MODE_FULL) {

		EPD_1IN54_V2_Init();
		Paint_SelectImage(interface->framebuffer);

		interface->updateMode = INTERFACE_UPDATE_MODE_FULL;

	} else if (mode == INTERFACE_UPDATE_MODE_PARTIAL) {

		EPD_1IN54_V2_Init();
		EPD_1IN54_V2_DisplayPartBaseImage(interface->framebuffer);
		Paint_SelectImage(interface->framebuffer);

		interface->updateMode = INTERFACE_UPDATE_MODE_PARTIAL;
	}

}

/*
 * brief: burn framebuffer on matrix
 * param: interface struct
 * retval: none
 */
void interfaceBurn(interfaceTypeDef *interface) {

	if (interface->updateMode == INTERFACE_UPDATE_MODE_PARTIAL) {

		EPD_1IN54_V2_DisplayPart(interface->framebuffer);

	} else if (interface->updateMode == INTERFACE_UPDATE_MODE_FULL) {

		EPD_1IN54_V2_Display(interface->framebuffer);

	}

}

/*
 * brief: burn framebuffer on matrix
 * param: interface struct
 * retval: none
 */
void interfaceClear(interfaceTypeDef *interface) {
	Paint_Clear(interface->colorBackground);
}

void interfaceSettingsClear(interfaceSettingsTypeDef *settings) {
	Paint_Clear(settings->colorBackground);
}

void interfaceDraw(interfaceTypeDef *interface, RTCChronoTypeDef *chrono,
		lis3mdlTypeDef *magnetometer, bme280TypeDef *atmospherical,
		watchTypeDef *watch, forecastTypeDef *forecast) {

	//			LOGO
	Paint_DrawString_EN(82, 7, "libra", &Font12, interface->colorForeground,
			interface->colorBackground);

	//			MOON PHASE BOARD
	if (interface->coordinatesMoonPhase[EN] == INTERFACE_ELEMENT_ENABLED) {
		Paint_DrawCircle(interface->coordinatesMoonPhase[X],
				interface->coordinatesMoonPhase[Y], interface->radiusMoonPhase,
				interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		//draw craters
		Paint_DrawCircle(interface->coordinatesMoonPhase[X] - 2,
				interface->coordinatesMoonPhase[Y] + 1, 3,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
		Paint_DrawCircle(interface->coordinatesMoonPhase[X] + 2,
				interface->coordinatesMoonPhase[Y] - 5, 1,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
		Paint_DrawCircle(interface->coordinatesMoonPhase[X] - 9,
				interface->coordinatesMoonPhase[Y] + 3, 2,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

		if (chrono->actual.moonPhase < 50) {

			float moonPhaseShift = ((float) chrono->actual.moonPhase / 25)
					* interface->radiusMoonPhase;
			Paint_DrawCircle(
					interface->coordinatesMoonPhase[X]
							- (uint32_t) moonPhaseShift,
					interface->coordinatesMoonPhase[Y],
					interface->radiusMoonPhase, interface->colorBackground,
					DOT_PIXEL_1X1, DRAW_FILL_FULL);

		} else if (chrono->actual.moonPhase > 50) {
			uint32_t moonPhase = 100 - chrono->actual.moonPhase;

			float moonPhaseShift = ((float) moonPhase / 25)
					* interface->radiusMoonPhase;
			Paint_DrawCircle(
					interface->coordinatesMoonPhase[X]
							+ (uint32_t) moonPhaseShift,
					interface->coordinatesMoonPhase[Y],
					interface->radiusMoonPhase, interface->colorBackground,
					DOT_PIXEL_1X1, DRAW_FILL_FULL);

		}

		//			draw stars
		Paint_DrawPoint(interface->coordinatesMoonPhase[X] - 15,
				interface->coordinatesMoonPhase[Y] - 5,
				interface->colorForeground, DOT_PIXEL_1X1, DOT_STYLE_DFT);
		Paint_DrawPoint(interface->coordinatesMoonPhase[X] + 13,
				interface->coordinatesMoonPhase[Y] + 2,
				interface->colorForeground, DOT_PIXEL_1X1, DOT_STYLE_DFT);
		Paint_DrawPoint(interface->coordinatesMoonPhase[X] - 9,
				interface->coordinatesMoonPhase[Y] + 17,
				interface->colorForeground, DOT_PIXEL_1X1, DOT_STYLE_DFT);
		Paint_DrawPoint(interface->coordinatesMoonPhase[X] + 8,
				interface->coordinatesMoonPhase[Y] - 18,
				interface->colorForeground, DOT_PIXEL_2X2, DOT_STYLE_DFT);

	}

	//			TEMPERATURE
	if (interface->coordinatesTemperature[EN] == INTERFACE_ELEMENT_ENABLED) {

		//frame
		Paint_DrawRectangle(interface->coordinatesTemperature[X] - 20,
				interface->coordinatesTemperature[Y] - 4,
				interface->coordinatesTemperature[X] + 50,
				interface->coordinatesTemperature[Y] + 18,
				interface->colorForeground, DOT_PIXEL_2X2, DRAW_FILL_FULL);

		//unit
		Paint_DrawCircle(interface->coordinatesTemperature[X] + 26,
				interface->coordinatesTemperature[Y] + 4, 2,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
		Paint_DrawString_EN(interface->coordinatesTemperature[X] + 31,
				interface->coordinatesTemperature[Y], "C", &Font16,
				interface->colorBackground, interface->colorForeground);

		//value
		if (atmospherical->temperatureValue < 0) {
			Paint_DrawChar(interface->coordinatesTemperature[X] - 8,
					interface->coordinatesTemperature[Y], '-', &Font16,
					interface->colorBackground, interface->colorForeground);
			Paint_DrawNum(interface->coordinatesTemperature[X],
					interface->coordinatesTemperature[Y],
					abs(atmospherical->temperatureValueCompensated / 100),
					&Font16, interface->colorBackground,
					interface->colorForeground);
		} else {
			Paint_DrawNum(interface->coordinatesTemperature[X],
					interface->coordinatesTemperature[Y],
					atmospherical->temperatureValueCompensated / 100, &Font16,
					interface->colorBackground, interface->colorForeground);
		}
	}

	//			HUMIDITY
	if (interface->coordinatesHumidity[EN] == INTERFACE_ELEMENT_ENABLED) {

		//frame
		Paint_DrawRectangle(interface->coordinatesHumidity[X],
				interface->coordinatesHumidity[Y],
				interface->coordinatesHumidity[X] + 5,
				interface->coordinatesHumidity[Y] + 50,
				interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

		//indexes
		for (uint8_t i = 0; i <= 50; i = i + 5) {
			Paint_DrawLine(interface->coordinatesHumidity[X],
					interface->coordinatesHumidity[Y] + i,
					interface->coordinatesHumidity[X] - 2,
					interface->coordinatesHumidity[Y] + i,
					interface->colorForeground, DOT_PIXEL_1X1,
					LINE_STYLE_SOLID);
		}
		Paint_DrawString_EN(interface->coordinatesHumidity[X] + 6,
				interface->coordinatesHumidity[Y], "0%RH", &Font8,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawString_EN(interface->coordinatesHumidity[X] + 6,
				interface->coordinatesHumidity[Y] + 43, "100", &Font8,
				interface->colorForeground, interface->colorBackground);

		//value
		Paint_DrawRectangle(interface->coordinatesHumidity[X],
				interface->coordinatesHumidity[Y],
				interface->coordinatesHumidity[X] + 5,
				interface->coordinatesHumidity[Y]
						+ (atmospherical->humidityValue / 2),
				interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	}

	//			COMPASS
	if (interface->coordinatesCompass[EN] == INTERFACE_ELEMENT_ENABLED) {

		//board
		Paint_DrawCircle(interface->coordinatesCompass[X],
				interface->coordinatesCompass[Y], interface->radiusCompass,
				interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

		//altimeter unit
		Paint_DrawChar(interface->coordinatesCompass[X] - 4,
				interface->coordinatesCompass[Y] + 3, 'm', &Font12,
				interface->colorForeground, interface->colorBackground);

		//fields for indexes
		Paint_DrawRectangle(interface->coordinatesCompass[X] - 3,
				interface->coordinatesCompass[Y] - 30,
				interface->coordinatesCompass[X] - 3 + 8,
				interface->coordinatesCompass[Y] - 30 + 12,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Paint_DrawRectangle(interface->coordinatesCompass[X] - 3,
				interface->coordinatesCompass[Y] + 19,
				interface->coordinatesCompass[X] - 3 + 8,
				interface->coordinatesCompass[Y] + 19 + 12,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Paint_DrawRectangle(interface->coordinatesCompass[X] - 28,
				interface->coordinatesCompass[Y] - 5,
				interface->coordinatesCompass[X] - 28 + 8,
				interface->coordinatesCompass[Y] - 5 + 12,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Paint_DrawRectangle(interface->coordinatesCompass[X] + 20,
				interface->coordinatesCompass[Y] - 5,
				interface->coordinatesCompass[X] + 20 + 8,
				interface->coordinatesCompass[Y] - 5 + 12,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		//indexes
		Paint_DrawChar(interface->coordinatesCompass[X] - 3,
				interface->coordinatesCompass[Y] - 30, 'N', &Font12,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawChar(interface->coordinatesCompass[X] - 3,
				interface->coordinatesCompass[Y] + 19, 'S', &Font12,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawChar(interface->coordinatesCompass[X] - 28,
				interface->coordinatesCompass[Y] - 5, 'W', &Font12,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawChar(interface->coordinatesCompass[X] + 20,
				interface->coordinatesCompass[Y] - 5, 'E', &Font12,
				interface->colorForeground, interface->colorBackground);

		//alti value
		if (atmospherical->altitudeValue < 0) {
			Paint_DrawChar(interface->coordinatesCompass[X] - 12,
					interface->coordinatesCompass[Y] - 14, '-', &Font12,
					interface->colorForeground, interface->colorBackground);
			Paint_DrawNum(interface->coordinatesCompass[X] - 12 + 8,
					interface->coordinatesCompass[Y] - 14,
					abs(atmospherical->altitudeValue / 100), &Font12,
					interface->colorForeground, interface->colorBackground);
		} else {
			Paint_DrawNum(interface->coordinatesCompass[X] - 12,
					interface->coordinatesCompass[Y] - 14,
					atmospherical->altitudeValue / 100, &Font12,
					interface->colorForeground, interface->colorBackground);
		}

		//compass pointers
		Paint_DrawPointer(interface->coordinatesCompass[X],
				interface->coordinatesCompass[Y], magnetometer->compassAngleXY,
				interface->pointerLenghtCompass, 0, interface->colorForeground,
				DOT_PIXEL_2X2, LINE_STYLE_SOLID);
		Paint_DrawPointer(interface->coordinatesCompass[X],
				interface->coordinatesCompass[Y],
				magnetometer->compassAngleXY + 3.14,
				interface->pointerLenghtCompass, 0, interface->colorForeground,
				DOT_PIXEL_1X1, LINE_STYLE_SOLID);

		//dot
		Paint_DrawCircle(interface->coordinatesCompass[X],
				interface->coordinatesCompass[Y], 3, interface->colorForeground,
				DOT_PIXEL_2X2, DRAW_FILL_FULL);

	}

	//			CHRONO DECIMALS
	if (interface->coordinatesChronoDecimals[EN] == INTERFACE_ELEMENT_ENABLED) {

		//outer circle
		Paint_DrawCircle(interface->coordinatesChronoDecimals[X],
				interface->coordinatesChronoDecimals[Y],
				interface->radiusSmall + 2, interface->colorForeground,
				DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

		//inner circle
		Paint_DrawCircle(interface->coordinatesChronoDecimals[X],
				interface->coordinatesChronoDecimals[Y], interface->radiusSmall,
				interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		//dot at center
		Paint_DrawCircle(interface->coordinatesChronoDecimals[X],
				interface->coordinatesChronoDecimals[Y], 2,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		//index - count angles

		uint8_t numberOfIndexesChronoDecimals =
				sizeof(interface->indexAngleChronoDecimals)
						/ sizeof(interface->indexAngleChronoDecimals[0]);

		for (uint8_t i = 0; i < numberOfIndexesChronoDecimals; i++) {
			interface->indexAngleChronoDecimals[i] = 2 * 3.14
					/ numberOfIndexesChronoDecimals
					* (i - (numberOfIndexesChronoDecimals / 4));
		}

		//indexes- draw
		for (uint8_t i = 0; i < numberOfIndexesChronoDecimals; i++) {

			Paint_DrawLine(
					cos(interface->indexAngleChronoDecimals[i])
							* (interface->radiusSmall
									- interface->indexLengthChronoDecimals)
							+ interface->coordinatesChronoDecimals[X],
					sin(interface->indexAngleChronoDecimals[i])
							* (interface->radiusSmall
									- interface->indexLengthChronoDecimals)
							+ interface->coordinatesChronoDecimals[Y],

					cos(interface->indexAngleChronoDecimals[i])
							* (interface->radiusSmall)
							+ interface->coordinatesChronoDecimals[X],
					sin(interface->indexAngleChronoDecimals[i])
							* (interface->radiusSmall)
							+ interface->coordinatesChronoDecimals[Y],
					interface->colorBackground, DOT_PIXEL_1X1,
					LINE_STYLE_SOLID);
		}

		//digits
		Paint_DrawString_EN(interface->coordinatesChronoDecimals[X] - 4,
				interface->coordinatesChronoDecimals[Y] - 24, "0", &Font12,
				interface->colorBackground, interface->colorForeground);
		Paint_DrawString_EN(interface->coordinatesChronoDecimals[X] + 12,
				interface->coordinatesChronoDecimals[Y] - 12, "2", &Font12,
				interface->colorBackground, interface->colorForeground);
		Paint_DrawString_EN(interface->coordinatesChronoDecimals[X] + 6,
				interface->coordinatesChronoDecimals[Y] + 6, "4", &Font12,
				interface->colorBackground, interface->colorForeground);
		Paint_DrawString_EN(interface->coordinatesChronoDecimals[X] - 14,
				interface->coordinatesChronoDecimals[Y] + 6, "6", &Font12,
				interface->colorBackground, interface->colorForeground);
		Paint_DrawString_EN(interface->coordinatesChronoDecimals[X] - 18,
				interface->coordinatesChronoDecimals[Y] - 12, "8", &Font12,
				interface->colorBackground, interface->colorForeground);

		//pointer
		interface->pointerAngleChronoDecimals = 2 * 3.14 / 10
				* ((chrono->chrono.hundredth / 10) - 2.5);

		Paint_DrawPointer(interface->coordinatesChronoDecimals[X],
				interface->coordinatesChronoDecimals[Y],
				interface->pointerAngleChronoDecimals,
				interface->pointerLengthChronoDecimals, 0,
				interface->colorBackground, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	}

	//			CHRONO MINUTES

	if (interface->coordinatesChronoMinutes[EN] == INTERFACE_ELEMENT_ENABLED) {
		//outer circle
		Paint_DrawCircle(interface->coordinatesChronoMinutes[X],
				interface->coordinatesChronoMinutes[Y],
				interface->radiusSmall + 2, interface->colorForeground,
				DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
		//inner circle
		Paint_DrawCircle(interface->coordinatesChronoMinutes[X],
				interface->coordinatesChronoMinutes[Y], interface->radiusSmall,
				interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		//dot at center
		Paint_DrawCircle(interface->coordinatesChronoMinutes[X],
				interface->coordinatesChronoMinutes[Y], 2,
				interface->colorBackground, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		//indexes- count angles
		uint8_t numberOfIndexesChronoMinutes =
				sizeof(interface->indexAngleChronoMinutes)
						/ sizeof(interface->indexAngleChronoMinutes[0]);

		for (uint8_t i = 0; i < numberOfIndexesChronoMinutes; i++) {
			interface->indexAngleChronoMinutes[i] = 2 * 3.14
					/ numberOfIndexesChronoMinutes
					* (i - (numberOfIndexesChronoMinutes / 4));
		}

		//indexes- draw
		for (uint8_t i = 0; i < numberOfIndexesChronoMinutes; i++) {

			Paint_DrawLine(
					cos(interface->indexAngleChronoMinutes[i])
							* (interface->radiusSmall
									- interface->indexLengthChronoMinutes)
							+ interface->coordinatesChronoMinutes[X],
					sin(interface->indexAngleChronoMinutes[i])
							* (interface->radiusSmall
									- interface->indexLengthChronoMinutes)
							+ interface->coordinatesChronoMinutes[Y],

					cos(interface->indexAngleChronoMinutes[i])
							* (interface->radiusSmall)
							+ interface->coordinatesChronoMinutes[X],
					sin(interface->indexAngleChronoMinutes[i])
							* (interface->radiusSmall)
							+ interface->coordinatesChronoMinutes[Y],
					interface->colorBackground, DOT_PIXEL_1X1,
					LINE_STYLE_SOLID);

			if (i % 5 == 0) {
				Paint_DrawLine(
						cos(interface->indexAngleChronoMinutes[i])
								* (interface->radiusSmall
										- (interface->indexLengthChronoMinutes
												+ 5))
								+ interface->coordinatesChronoMinutes[X],
						sin(interface->indexAngleChronoMinutes[i])
								* (interface->radiusSmall
										- (interface->indexLengthChronoMinutes
												+ 5))
								+ interface->coordinatesChronoMinutes[Y],

						cos(interface->indexAngleChronoMinutes[i])
								* (interface->radiusSmall)
								+ interface->coordinatesChronoMinutes[X],
						sin(interface->indexAngleChronoMinutes[i])
								* (interface->radiusSmall)
								+ interface->coordinatesChronoMinutes[Y],
						interface->colorBackground, DOT_PIXEL_1X1,
						LINE_STYLE_SOLID);
			}
		}

		//digits
		Paint_DrawString_EN(interface->coordinatesChronoMinutes[X] - 8,
				interface->coordinatesChronoMinutes[Y] - 20, "30", &Font12,
				interface->colorBackground, interface->colorForeground);
		Paint_DrawString_EN(interface->coordinatesChronoMinutes[X] + 2,
				interface->coordinatesChronoMinutes[Y] + 2, "10", &Font12,
				interface->colorBackground, interface->colorForeground);
		Paint_DrawString_EN(interface->coordinatesChronoMinutes[X] - 18,
				interface->coordinatesChronoMinutes[Y] + 2, "20", &Font12,
				interface->colorBackground, interface->colorForeground);

		//pointer
		interface->pointerAngleChronoMinutes = 2 * 3.14 / 30
				* (chrono->chrono.minute - 7.5);

		Paint_DrawPointer(interface->coordinatesChronoMinutes[X],
				interface->coordinatesChronoMinutes[Y],
				interface->pointerAngleChronoMinutes,
				interface->pointerLengthChronoMinutes, 0,
				interface->colorBackground, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

		//half hours dots
		for (uint8_t halfHours = (chrono->chrono.hour * 2)
				+ (chrono->chrono.minute / 30); halfHours > 0; halfHours--) {
			Paint_DrawPoint(
					interface->coordinatesChronoMinutes[X]
							- interface->pointerLengthChronoMinutes
							+ (halfHours * 4),
					interface->coordinatesChronoMinutes[Y] - 5,
					interface->colorBackground, DOT_PIXEL_2X2, DOT_STYLE_DFT);
		};

	}

	//			DATE
	if (interface->coordinatesDate[EN] == INTERFACE_ELEMENT_ENABLED) {

		//window
		Paint_DrawRectangle(interface->coordinatesDate[X] - 1,
				interface->coordinatesDate[Y] - 3,
				interface->coordinatesDate[X] + 24,
				interface->coordinatesDate[Y] + 18, interface->colorForeground,
				DOT_PIXEL_2X2, DRAW_FILL_EMPTY); // date window

		//value
		Paint_DrawNum(interface->coordinatesDate[X],
				interface->coordinatesDate[Y], chrono->actual.day, &Font16,
				interface->colorForeground, interface->colorBackground); //date

	}

	//			BAROMETER
	if (interface->coordinatesPressure[EN] == INTERFACE_ELEMENT_ENABLED) {

		//indexes
		Paint_DrawNum(interface->coordinatesPressure[X] + 77,
				interface->coordinatesPressure[Y] + 2, 975, &Font8,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawString_EN(interface->coordinatesPressure[X] + 77,
				interface->coordinatesPressure[Y] + 11, "hPa", &Font8,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawNum(interface->coordinatesPressure[X] + 2,
				interface->coordinatesPressure[Y] + 85, 1000, &Font8,
				interface->colorForeground, interface->colorBackground);
		Paint_DrawNum(interface->coordinatesPressure[X] - 95,
				interface->coordinatesPressure[Y] + 2, 1025, &Font8,
				interface->colorForeground, interface->colorBackground);

		//pointer
		interface->pointerAnglePressure = 2 * 3.14 / 100
				* ((int32_t) atmospherical->pressureValue / 100 - 950 - 25);

		Paint_DrawPointer(interface->coordinatesPressure[X],
				interface->coordinatesPressure[Y],
				interface->pointerAnglePressure,
				interface->pointerLengthPressure,
				interface->pointerShiftPressure, interface->colorForeground,
				DOT_PIXEL_3X3, LINE_STYLE_SOLID);

		//past pressure pointer

		interface->pointerAnglePressure = 2 * 3.14 / 100
				* ((int32_t) forecast->pastPressureReadings[5] - 950 - 25);

		Paint_DrawPointer(interface->coordinatesPressure[X],
				interface->coordinatesPressure[Y],
				interface->pointerAnglePressure,
				interface->pointerLengthPressure,
				interface->pointerShiftPressure+5, interface->colorForeground,
				DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	}

	//			LOW BATTERY INDICATOR
	if (interface->coordinatesBatteryState[EN] == INTERFACE_ELEMENT_ENABLED) {

		if (watch->flagLowBattery) {
			Paint_DrawString_EN(interface->coordinatesBatteryState[X],
					interface->coordinatesBatteryState[Y], "CHARGE", &Font12,
					interface->colorForeground, interface->colorBackground);
		}

	}

	//			MAIN BOARD
	//circle
	Paint_DrawCircle(interface->coordinatesMain[X],
			interface->coordinatesMain[Y], interface->radiusMain,
			interface->colorForeground, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

	//indexes - count angles

	uint8_t numberOfIndexesMain = sizeof(interface->indexAngleMain)
			/ sizeof(interface->indexAngleMain[0]);

	for (uint8_t i = 0; i < numberOfIndexesMain; i++) {

		interface->indexAngleMain[i] = 2 * 3.14 / numberOfIndexesMain
				* (i - (numberOfIndexesMain / 4));
	};

	//indexes- draw
	for (uint8_t i = 1; i < numberOfIndexesMain; i++) {

		Paint_DrawLine(
				cos(interface->indexAngleMain[i])
						* (interface->radiusMain - interface->indexLengthMain)
						+ interface->coordinatesMain[X],
				sin(interface->indexAngleMain[i])
						* (interface->radiusMain - interface->indexLengthMain)
						+ interface->coordinatesMain[Y],

				cos(interface->indexAngleMain[i]) * (interface->radiusMain)
						+ interface->coordinatesMain[X],
				sin(interface->indexAngleMain[i]) * (interface->radiusMain)
						+ interface->coordinatesMain[Y],
				interface->colorForeground, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	}

	//hour shadow
	interface->pointerAngleHours = 2 * 3.14 / 60
			* ((chrono->actual.hour * 5 + (chrono->actual.minute / 10)) - 15);

	Paint_DrawPointer(interface->coordinatesMain[X] + interface->shadowShift,
			interface->coordinatesMain[Y] + interface->shadowShift,
			interface->pointerAngleHours, interface->pointerLengthHours, 0,
			interface->colorBackground, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
	//hour pointer
	Paint_DrawPointer(interface->coordinatesMain[X],
			interface->coordinatesMain[Y], interface->pointerAngleHours,
			interface->pointerLengthHours, 0, interface->colorForeground,
			DOT_PIXEL_3X3, LINE_STYLE_SOLID);

	//minute shadow
	interface->pointerAngleMinutes = 2 * 3.14 / 60
			* (chrono->actual.minute - 15);
	Paint_DrawPointer(interface->coordinatesMain[X] + interface->shadowShift,
			interface->coordinatesMain[Y] + interface->shadowShift,
			interface->pointerAngleMinutes, interface->pointerLengthMinutes, 0,
			interface->colorBackground, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

	//minute pointer
	Paint_DrawPointer(interface->coordinatesMain[X],
			interface->coordinatesMain[Y], interface->pointerAngleMinutes,
			interface->pointerLengthMinutes, 0, interface->colorForeground,
			DOT_PIXEL_2X2, LINE_STYLE_SOLID);

	//chrono seconds pointer
	interface->pointerAngleChronoSeconds = 2 * 3.14 / 60
			* (chrono->chrono.second - 15);

	Paint_DrawPointer(interface->coordinatesMain[X],
			interface->coordinatesMain[Y], interface->pointerAngleChronoSeconds,
			interface->pointerLengthChronoSeconds, 0,
			interface->colorBackground, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	//chrono seconds shadow
	Paint_DrawPointer(interface->coordinatesMain[X] + interface->shadowShift,
			interface->coordinatesMain[Y] + interface->shadowShift,
			interface->pointerAngleChronoSeconds,
			interface->pointerLengthChronoSeconds, 0,
			interface->colorForeground, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	//dot
	Paint_DrawCircle(interface->coordinatesMain[X],
			interface->coordinatesMain[Y], 8, interface->colorForeground,
			DOT_PIXEL_2X2, DRAW_FILL_FULL);
	Paint_DrawCircle(interface->coordinatesMain[X],
			interface->coordinatesMain[Y], 2, interface->colorBackground,
			DOT_PIXEL_2X2, DRAW_FILL_FULL);

}

void interfaceSettingsDraw(interfaceSettingsTypeDef *settings,
		RTCChronoTypeDef *chrono, lis3mdlTypeDef *magnetometer,
		bme280TypeDef *atmospherical, watchTypeDef *watch) {

	//			temperature
	if (atmospherical->temperatureValue < 0) {
		Paint_DrawChar(settings->coordinatesTemperature[X] - 8,
				settings->coordinatesTemperature[Y], '-', &Font16,
				settings->colorForeground, settings->colorBackground);
		Paint_DrawNum(settings->coordinatesTemperature[X],
				settings->coordinatesTemperature[Y],
				abs(atmospherical->temperatureValueCompensated / 100), &Font16,
				settings->colorForeground, settings->colorBackground);
	} else {
		Paint_DrawNum(settings->coordinatesTemperature[X],
				settings->coordinatesTemperature[Y],
				atmospherical->temperatureValueCompensated / 100, &Font16,
				settings->colorForeground, settings->colorBackground);
	}

	Paint_DrawChar(settings->coordinatesTemperature[X] + 25,
			settings->coordinatesTemperature[Y], 'C', &Font16,
			settings->colorForeground, settings->colorBackground);

	//			humidity
	Paint_DrawNum(settings->coordinatesHumidity[X],
			settings->coordinatesHumidity[Y], atmospherical->humidityValue,
			&Font16, settings->colorForeground, settings->colorBackground);
	Paint_DrawChar(settings->coordinatesHumidity[X] + 25,
			settings->coordinatesHumidity[Y], '%', &Font16,
			settings->colorForeground, settings->colorBackground);

	//pressure
	Paint_DrawNum(settings->coordinatesPressure[X],
			settings->coordinatesPressure[Y],
			atmospherical->pressureValue / 100, &Font16,
			settings->colorForeground, settings->colorBackground);

	Paint_DrawString_EN(settings->coordinatesPressure[X] + 50,
			settings->coordinatesPressure[Y], "hPa", &Font16,
			settings->colorForeground, settings->colorBackground);

	//altitude
	if (atmospherical->altitudeValue < 0) {
		Paint_DrawChar(settings->coordinatesAltitude[X] - 8,
				settings->coordinatesAltitude[Y], '-', &Font16,
				settings->colorForeground, settings->colorBackground);
		Paint_DrawNum(settings->coordinatesAltitude[X],
				settings->coordinatesAltitude[Y],
				abs(atmospherical->altitudeValue / 100), &Font16,
				settings->colorForeground, settings->colorBackground);
	} else {
		Paint_DrawNum(settings->coordinatesAltitude[X],
				settings->coordinatesAltitude[Y],
				atmospherical->altitudeValue / 100, &Font16,
				settings->colorForeground, settings->colorBackground);
	}

	Paint_DrawChar(settings->coordinatesAltitude[X] + 50,
			settings->coordinatesAltitude[Y], 'm', &Font16,
			settings->colorForeground, settings->colorBackground);

	//hours
	Paint_DrawNum(settings->coordinatesHours[X], settings->coordinatesHours[Y],
			chrono->actual.hour, &Font20, settings->colorForeground,
			settings->colorBackground);

	//minutes
	Paint_DrawNum(settings->coordinatesMinutes[X],
			settings->coordinatesMinutes[Y], chrono->actual.minute, &Font20,
			settings->colorForeground, settings->colorBackground);
	//seconds
	Paint_DrawNum(settings->coordinatesSeconds[X],
			settings->coordinatesSeconds[Y], chrono->actual.second, &Font20,
			settings->colorForeground, settings->colorBackground);

	//days
	Paint_DrawNum(settings->coordinatesDays[X], settings->coordinatesDays[Y],
			chrono->actual.day, &Font20, settings->colorForeground,
			settings->colorBackground);
	//months
	Paint_DrawNum(settings->coordinatesMonths[X],
			settings->coordinatesMonths[Y], chrono->actual.month, &Font20,
			settings->colorForeground, settings->colorBackground);
	//years
	Paint_DrawNum(settings->coordinatesYears[X], settings->coordinatesYears[Y],
			chrono->actual.year, &Font20, settings->colorForeground,
			settings->colorBackground);

	//Pressure ref
	Paint_DrawNum(settings->coordinatesPressureReference[X],
			settings->coordinatesPressureReference[Y],
			atmospherical->pressureReference, &Font16,
			settings->colorForeground, settings->colorBackground);
	Paint_DrawString_EN(settings->coordinatesPressureReference[X] + 50,
			settings->coordinatesPressureReference[Y], "hPa", &Font16,
			settings->colorForeground, settings->colorBackground);

	//temperature compensation
	if (atmospherical->temperatureOffset < 0) {
		Paint_DrawChar(settings->coordinatesTemperatureCompensation[X] - 8,
				settings->coordinatesTemperatureCompensation[Y], '-', &Font16,
				settings->colorForeground, settings->colorBackground);
		Paint_DrawNum(settings->coordinatesTemperatureCompensation[X],
				settings->coordinatesTemperatureCompensation[Y],
				abs(atmospherical->temperatureOffset), &Font16,
				settings->colorForeground, settings->colorBackground);
	} else {
		Paint_DrawNum(settings->coordinatesTemperatureCompensation[X],
				settings->coordinatesTemperatureCompensation[Y],
				atmospherical->temperatureOffset, &Font16,
				settings->colorForeground, settings->colorBackground);
	}

	Paint_DrawChar(settings->coordinatesTemperatureCompensation[X] + 25,
			settings->coordinatesTemperatureCompensation[Y], 'C', &Font16,
			settings->colorForeground, settings->colorBackground);

	//actual setting marker

	uint8_t markerPosition[2] = { 0, 0 };

	switch (watch->settingsItem) {

	case WATCH_SETTINGS_ITEM_HOUR:
		memcpy(markerPosition, settings->coordinatesHours, 2);
		break;
	case WATCH_SETTINGS_ITEM_MINUTE:
		memcpy(markerPosition, settings->coordinatesMinutes, 2);
		break;
	case WATCH_SETTINGS_ITEM_SECOND:
		memcpy(markerPosition, settings->coordinatesSeconds, 2);
		break;
	case WATCH_SETTINGS_ITEM_DAY:
		memcpy(markerPosition, settings->coordinatesDays, 2);
		break;
	case WATCH_SETTINGS_ITEM_MONTH:
		memcpy(markerPosition, settings->coordinatesMonths, 2);
		break;
	case WATCH_SETTINGS_ITEM_YEAR:
		memcpy(markerPosition, settings->coordinatesYears, 2);
		break;
	case WATCH_SETTINGS_ITEM_PREF:
		memcpy(markerPosition, settings->coordinatesPressureReference, 2);
		break;
	case WATCH_SETTINGS_ITEM_TOFFSET:
		memcpy(markerPosition, settings->coordinatesTemperatureCompensation, 2);
		markerPosition[X] = markerPosition[X] - 7;
		break;

	}

	Paint_DrawPoint(markerPosition[X] - 2, markerPosition[Y] + 7,
			settings->colorForeground, DOT_PIXEL_3X3, DOT_STYLE_DFT);
//	Paint_DrawNum(100, 100, watch->settingsItem, &Font16,
//			settings->colorForeground, settings->colorBackground);

	//net
//	Paint_DrawLine(130, 0, 130, 200, settings->colorForeground, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	Paint_DrawRectangle(130, 0, 200, 200, settings->colorForeground,
			DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawLine(0, 75, 200, 75, settings->colorForeground, DOT_PIXEL_3X3,
			LINE_STYLE_SOLID);
	Paint_DrawLine(0, 120, 200, 120, settings->colorForeground, DOT_PIXEL_3X3,
			LINE_STYLE_SOLID);

	//sensors labels
	Paint_DrawChar(160, 30, '+', &Font24, settings->colorBackground,
			settings->colorForeground);
	Paint_DrawChar(180, 90, '-', &Font24, settings->colorBackground,
			settings->colorForeground);
	Paint_DrawChar(160, 150, '>', &Font24, settings->colorBackground,
			settings->colorForeground);

	//logo
	Paint_DrawString_EN(60, 175, "libra", &Font16, settings->colorForeground,
			settings->colorBackground);

}

/*
 * rtc.c
 * REAL TIME CLOCK WITH CHRONO HAL WRAPPER
 *
 *
 * 	Created on: 16 APR 2022
 *      Author: Bartosz
 *      version: 1.1
 *
 *      changelog:
 *      1.1 added resume, decimal changed by hundredths
 *
 */

#include <bd_libs/rtc_bd.h>
#include "main.h"
#include <stdint.h>

/**
 * @brief  Initialize RTC and reset chrono
 *
 * @note
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcInit(RTCChronoTypeDef *chrono) {
	HAL_RTC_Init(&hrtc);
	chrono->chronoMode = RTC_CHRONO_MODE_INACTIVE;

	chrono->chrono.year = 0;
	chrono->chrono.month = 0;
	chrono->chrono.day = 0;
	chrono->chrono.hour = 0;
	chrono->chrono.minute = 0;
	chrono->chrono.second = 0;
	chrono->chrono.hundredth = 0;

}

/**
 * @brief  Actualize data in chrono structure
 *
 * @note Should be run before reading values
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcGetTime(RTCChronoTypeDef *chrono) {

	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);

	chrono->actual.hour = Time.Hours;

	chrono->actual.minute = Time.Minutes;
	chrono->actual.second = Time.Seconds;

	chrono->actual.hundredth = (((255 - Time.SubSeconds) * 100) / 255); //^ subsecond from RTC is 1/255 of second(becouse of RTC sync predivider)

	chrono->actual.day = Date.Date;
	chrono->actual.month = Date.Month;
	chrono->actual.year = Date.Year;

	//							MOON PHASE COUNT

	float X = (chrono->actual.month + 9) / 12;
	uint32_t A = 4716 + (chrono->actual.year + 2000) + (uint32_t) X;
	float Y = 275 * chrono->actual.month / 9;
	float V = 7 * A / 4;
	float B = 1729279.5 + 367 * (chrono->actual.year + 2000) + (uint32_t) Y
			- (uint32_t) V + chrono->actual.day;
	float Q = (A + 83) / 100;
	uint32_t C = (uint32_t) Q;
	float W = 3 * (C + 1) / 4;
	uint32_t E = (uint32_t) W;
	float JD = B + 38 - E; //julian day
	float MS = 29.5305902778; //average value of synodic month
	float phasePrimary = ((JD / MS) - 0.3033);
	uint32_t phaseInteger = (uint32_t) phasePrimary;
	float phaseFinal = (phasePrimary - (float) phaseInteger) * 100;
	chrono->actual.moonPhase = (uint32_t) phaseFinal;

	// 0 - new moon, 25- I, 50- II(full moon), 75- III

	if (chrono->chronoMode == RTC_CHRONO_MODE_INACTIVE) {
		chrono->chrono.minute = 0;
		chrono->chrono.second = 0;
		chrono->chrono.hundredth = 0;
		chrono->chrono.hour = 0;
		chrono->chrono.day = 0;
		chrono->chrono.month = 0;
		chrono->chrono.year = 0;
	}
	if (chrono->chronoMode == RTC_CHRONO_MODE_RUNNING) {

		chrono->chrono.hundredth = chrono->actual.hundredth - chrono->chronoStart.hundredth;

		chrono->chrono.second = chrono->actual.second
				- chrono->chronoStart.second;
		chrono->chrono.minute = chrono->actual.minute
				- chrono->chronoStart.minute;
		chrono->chrono.hour = chrono->actual.hour - chrono->chronoStart.hour;
		chrono->chrono.day = chrono->actual.day - chrono->chronoStart.day;
		chrono->chrono.month = chrono->actual.month - chrono->chronoStart.month;

		if (chrono->chrono.hundredth < 0) {
			chrono->chrono.second--;
			chrono->chrono.hundredth = chrono->chrono.hundredth + 100;
		}

		if (chrono->chrono.second < 0) {
			chrono->chrono.minute--;
			chrono->chrono.second = chrono->chrono.second + 60;
		}

		if (chrono->chrono.minute < 0) {
			chrono->chrono.hour--;
			chrono->chrono.minute = chrono->chrono.minute + 60;
		}

		if (chrono->chrono.hour < 0) {
			chrono->chrono.day--;
			chrono->chrono.hour = chrono->chrono.hour + 24;
		}

		if (chrono->chrono.day < 0) {
			chrono->chrono.month--;
			chrono->chrono.day = chrono->chrono.day + 30;
		}

		if (chrono->chrono.month < 0) {
			chrono->chrono.year--;
			chrono->chrono.month = chrono->chrono.month + 12;
		}

	}

}

/**
 * @brief  Write data from chrono structure to RTC
 *
 * @note Should be run after any time change
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcSetTime(RTCChronoTypeDef *chrono) {

	Time.Hours = chrono->actual.hour;
	Time.Minutes = chrono->actual.minute;
	Time.Seconds = chrono->actual.second;
	Date.Date = chrono->actual.day;
	Date.Month = chrono->actual.month;
	Date.Year = chrono->actual.year;
	HAL_RTC_SetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &Date, RTC_FORMAT_BIN);

}

/**
 * @brief  Starting chrornograph
 *
 * @note none
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcStartChrono(RTCChronoTypeDef *chrono) {

//	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
//	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
	rtcGetTime(chrono);

	chrono->chronoStart.second = Time.Seconds;
	chrono->chronoStart.minute = Time.Minutes;
	chrono->chronoStart.hundredth = (((255 - Time.SubSeconds) * 100) / 255);
	chrono->chronoStart.hour = Time.Hours;
	chrono->chronoStart.day = Date.Date;
	chrono->chronoStart.month = Date.Month;
	chrono->chronoStart.year = Date.Year;

	chrono->chronoMode = RTC_CHRONO_MODE_RUNNING;
}

/**
 * @brief  Stop chronograph
 *
 * @note
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcStopChrono(RTCChronoTypeDef *chrono) {

	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);

	chrono->actual.minute = Time.Minutes;
	chrono->actual.second = Time.Seconds;
	chrono->actual.hundredth = (((255 - Time.SubSeconds) * 100) / 255);
	chrono->actual.hour = Time.Hours;
	chrono->actual.day = Date.Date;
	chrono->actual.month = Date.Month;
	chrono->actual.year = Date.Year;

	chrono->chrono.hundredth = chrono->actual.hundredth
			- chrono->chronoStart.hundredth;
	chrono->chrono.second = chrono->actual.second - chrono->chronoStart.second;
	chrono->chrono.minute = chrono->actual.minute - chrono->chronoStart.minute;
	chrono->chrono.hour = chrono->actual.hour - chrono->chronoStart.hour;
	chrono->chrono.day = chrono->actual.day - chrono->chronoStart.day;
	chrono->chrono.month = chrono->actual.month - chrono->chronoStart.month;
	chrono->chrono.year = chrono->actual.year - chrono->chronoStart.year;

	rtcGetTime(chrono);

	chrono->chronoMode = RTC_CHRONO_MODE_STOP;


}

/**
 * @brief  Resume chronograph
 *
 * @note without reseting start time
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcResumeChrono(RTCChronoTypeDef * chrono){
	chrono->chronoMode = RTC_CHRONO_MODE_RUNNING;
}

/**
 * @brief  Reset chronograph data
 *
 * @note
 *
 * @param  RTC item handler
 *
 * @retval None
 */
void rtcResetChrono(RTCChronoTypeDef *chrono) {

	chrono->chrono.hundredth = 0;
	chrono->chrono.minute = 0;
	chrono->chrono.second = 0;
	chrono->chrono.hour = 0;

	chrono->chronoStart.second = 0;
	chrono->chronoStart.minute = 0;
	chrono->chronoStart.hundredth = 0;
	chrono->chronoStart.hour = 0;

	chrono->chronoMode = RTC_CHRONO_MODE_INACTIVE;

}

/**
 * @brief  Change single data in chrono structure
 *
 * @note Inly increment/decrement. Automatically run rtcSetTime();
 *
 * @param  RTC item handler
 *
 * @param RTC element:
 * 	RTC_CHANGE_HOUR 0
 *	RTC_CHANGE_MINUTE 1
 *	RTC_CHANGE_SECOND 2
 *	RTC_CHANGE_DAY 3
 *	RTC_CHANGE_MONTH 4
 *	RTC_CHANGE_YEAR 5
 *
 * @param RTC_CHANGE_DIR_UP/DOWN
 *
 * @retval None
 */
void rtcChangeValue(RTCChronoTypeDef *chrono, uint8_t element,
		uint8_t direction) {

	if (direction == RTC_CHANGE_DIR_DOWN) {
		switch (element) {
		case RTC_CHANGE_HOUR:
			if (chrono->actual.hour > 0)
				chrono->actual.hour--;
			else if (chrono->actual.hour == 0)
				chrono->actual.hour = 23;
			break;
		case RTC_CHANGE_MINUTE:
			if (chrono->actual.minute > 0)
				chrono->actual.minute--;
			else if (chrono->actual.minute == 0) {
				chrono->actual.minute = 59;
			}
			break;
		case RTC_CHANGE_SECOND:
			chrono->actual.second = 0;
			break;
		case RTC_CHANGE_DAY:
			if (chrono->actual.day > 1)
				chrono->actual.day--;
			else if (chrono->actual.day == 1)
				chrono->actual.day = 31;
			break;
		case RTC_CHANGE_MONTH:
			if (chrono->actual.month > 1)
				chrono->actual.month--;
			else if(chrono->actual.month == 1)
				chrono->actual.month = 12;
			break;
		case RTC_CHANGE_YEAR:
			if (chrono->actual.year > 0)
				chrono->actual.year--;
			break;
		}

		rtcSetTime(chrono);
	} else if (direction == RTC_CHANGE_DIR_UP) {
		switch (element) {
		case RTC_CHANGE_HOUR:
			if (chrono->actual.hour < 23)
				chrono->actual.hour++;
			else if (chrono->actual.hour >= 23)
				chrono->actual.hour = 0;
			break;
		case RTC_CHANGE_MINUTE:
			if (chrono->actual.minute < 59)
				chrono->actual.minute++;
			else if (chrono->actual.minute >= 59)
				chrono->actual.minute = 0;
			break;
		case RTC_CHANGE_SECOND:
			chrono->actual.second = 0;
			break;
		case RTC_CHANGE_DAY:
			if (chrono->actual.day < 31)
				chrono->actual.day++;
			else if (chrono->actual.day == 31)
				chrono->actual.day = 1;
			break;
		case RTC_CHANGE_MONTH:
			if (chrono->actual.month < 12)
				chrono->actual.month++;
			else if(chrono->actual.month == 12)
				chrono->actual.month = 1;
			break;
		case RTC_CHANGE_YEAR:
			if (chrono->actual.year < 99)
				chrono->actual.year++;
			break;
		}

		rtcSetTime(chrono);
	}

}

/**
 * @brief  Tells that seconds is even
 *
 * @note for blinking at seconds changes
 *
 * @param  RTC item handler
 *
 * @retval Even- 1, Odd- 0
 */
uint8_t rtcBlink(RTCChronoTypeDef *chrono) {
	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);

	chrono->actual.second = Time.Seconds;

	if (chrono->actual.second % 2) {
		return 1;
	} else {
		return 0;
	}
}


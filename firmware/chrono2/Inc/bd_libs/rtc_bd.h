/*
 * rtc.h
 *
 *  Created on: 18 kwi 2022
 *      Author: bartosz
 */

#ifndef RTC_BD_H_
#define RTC_BD_H_

#include "main.h"

//USER CONFIGURATION

//END OF USER CONFIGURATION

#define RTC_CHRONO_MODE_INACTIVE 0
#define RTC_CHRONO_MODE_RUNNING 1
#define RTC_CHRONO_MODE_STOP 2

#define RTC_CHANGE_HOUR 0
#define RTC_CHANGE_MINUTE 1
#define RTC_CHANGE_SECOND 2
#define RTC_CHANGE_DAY 3
#define RTC_CHANGE_MONTH 4
#define RTC_CHANGE_YEAR 5

#define RTC_CHANGE_DIR_UP 0
#define RTC_CHANGE_DIR_DOWN 1



extern RTC_HandleTypeDef hrtc;

RTC_DateTypeDef Date;
RTC_TimeTypeDef Time;

typedef struct{
	int8_t year;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
	int8_t second;
//	int8_t decimal;
	int8_t hundredth;
	uint32_t moonPhase;
}	RTCTimeTypeDef;

typedef struct{
	RTCTimeTypeDef actual, chronoStart, chrono;
	uint8_t chronoMode;
}RTCChronoTypeDef;




void rtcInit(RTCChronoTypeDef *chrono);
void rtcGetTime(RTCChronoTypeDef *chrono);
void rtcSetTime(RTCChronoTypeDef *chrono);
void rtcStartChrono(RTCChronoTypeDef *chrono);
void rtcStopChrono(RTCChronoTypeDef *chrono);
void rtcResumeChrono(RTCChronoTypeDef * chrono);
void rtcResetChrono(RTCChronoTypeDef *chrono);
void rtcChangeValue(RTCChronoTypeDef * chrono, uint8_t position, uint8_t direction);
uint8_t rtcBlink(RTCChronoTypeDef *chrono);



#endif /* RTC_H_ */

/*
 * backup.c
 * ADDON FOR "REAL TIME CLOCK WITH CHRONO HAL WRAPPER"
 *
 * allow for use flash emulation for backup actual rtc time.
 * requirements:
 *
 * -rtc.h
 * -eeprom_emul.h(properly configured for specified MCU)
 * -2 32bit variables for store in flash
 *
 *  Created on: 2 maj 2022
 *      Author: bartosz
 *
 */

#include <bd_libs/backup_bd.h>

/**
 * @brief  Initialize flash memory
 *
 * @note run only if flash isn't non initialzed before
 *
 * @param  none
 *
 * @retval None
 */
void backupInit(void) {
	HAL_FLASH_Unlock();

	eeStatus = EE_Format(EE_FORCED_ERASE);
	eeStatus = EE_Init(EE_FORCED_ERASE);

	if (eeStatus != EE_OK) {
		eeStatus = EE_Format(EE_FORCED_ERASE);

		if (eeStatus != EE_OK) {
			Error_Handler();
		}

		eeStatus = EE_Init(EE_FORCED_ERASE);
		if (eeStatus != EE_OK) {
			Error_Handler();
		}

	}

	HAL_FLASH_Lock();
}

/**
 * @brief  Reads actual time from flash memory
 *
 * @note none
 *
 * @param  RTC handler
 *
 * @retval None
 */
void backupRestore(RTCChronoTypeDef *chrono) {

	uint16_t virtualAddress[2];
	uint32_t timeBackup[2];

	virtualAddress[0] = BACKUP_VIRTUAL_ADRESS;
	virtualAddress[1] = BACKUP_VIRTUAL_ADRESS + 1;

	HAL_FLASH_Unlock();

	eeStatus = EE_Init(EE_CONDITIONAL_ERASE);
	if (eeStatus != EE_OK) {
		Error_Handler();
	}

	for (uint8_t i = 0; i < 2; i++) {
		eeStatus = EE_ReadVariable32bits(virtualAddress[i], &timeBackup[i]);
		if (eeStatus == EE_NO_DATA) {

		}
	}

	HAL_FLASH_Lock();

	chrono->actual.hour = timeBackup[0] >> 24;
	chrono->actual.minute = timeBackup[0] >> 16;
	chrono->actual.second = timeBackup[0] >> 8;
	chrono->actual.day = timeBackup[1] >> 24;
	chrono->actual.month = timeBackup[1] >> 16;
	chrono->actual.year = timeBackup[1] >> 8;

	rtcSetTime(chrono);
}

/**
 * @brief  Write actual time to flash memory
 *
 * @note none
 *
 * @param  RTC handler
 *
 * @retval None
 */
void backupWrite(RTCChronoTypeDef *chrono) {

	uint16_t virtualAddress[2];
	uint32_t timeBackup[2];

	virtualAddress[0] = BACKUP_VIRTUAL_ADRESS;
	virtualAddress[1] = BACKUP_VIRTUAL_ADRESS + 1;

	timeBackup[0] = ((uint32_t) chrono->actual.hour << 24)
			| ((uint32_t) chrono->actual.minute << 16)
			| ((uint32_t) chrono->actual.second << 8);

	timeBackup[1] = ((uint32_t) chrono->actual.day << 24)
			| ((uint32_t) chrono->actual.month << 16)
			| ((uint32_t) chrono->actual.year << 8);

	HAL_FLASH_Unlock();

	eeStatus = EE_Init(EE_CONDITIONAL_ERASE);
	if (eeStatus != EE_OK) {
		Error_Handler();
	}

	for (uint8_t i = 0; i < 2; i++) {

		eeStatus = EE_WriteVariable32bits(virtualAddress[i], timeBackup[i]);

		if (eeStatus != EE_OK) {
			Error_Handler();
		}
	}

	HAL_FLASH_Lock();
}

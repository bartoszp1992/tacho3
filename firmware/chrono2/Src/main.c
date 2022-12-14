/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/*
 * Chrono 2 by Bart's design
 *
 *todo:
 *-automatic color change at night
 *-fix magnetometer current drain
 *-move settings to separate files
 *
 *
 *in cause of multiple definitions in .o files
project->properties->C/C++ Build->Settings->MCU GCC Compiler->Miscellanous
add other flag: -fcommon
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//			Barts design libraries
#include <bd_libs/adc_bd.h>
#include <bd_libs/backup_bd.h>
#include <bd_libs/bme280_bd.h>
#include <bd_libs/lis3mdl_bd.h>
#include <bd_libs/rtc_bd.h>
#include <bd_libs/forecast_bd.h>
#include <chrono/battery.h>
#include <chrono/interface.h>
#include <chrono/sleep.h>
#include <chrono/timers.h>
#include <chrono/watch.h>

//			Display libraries
#include "Display_EPD/EPD_1in54_V2.h"
#include "Display_Config/DEV_Config.h"

//			Waveshare GUI Library
#include "Display_GUI/GUI_Paint.h"

//			tacho libraries
#include <stdlib.h>

//			EEPROM emulation libs
#include "EEPROM_Emul/eeprom_emul.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//			Create chronograph structure
RTCChronoTypeDef chrono = { 0 };

//			Create sensors structures
lis3mdlTypeDef magnetometer = { 0 };
bme280TypeDef atmospherical = { 0 };

//			Create interface structure
interfaceTypeDef interface = { 0 };

//			Create interface settings structure
interfaceSettingsTypeDef settings = { 0 };

//			Create watch structure
watchTypeDef watch = { 0 };

//			Create forecast structure
forecastTypeDef forecast = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ADC1_Init();
	MX_I2C1_Init();
	MX_RTC_Init();
	MX_SPI1_Init();
	MX_TIM3_Init();
	MX_CRC_Init();
	MX_TIM6_Init();
	/* USER CODE BEGIN 2 */
	rtcInit(&chrono);
	lis3mdlInit(&magnetometer, &hi2c1);
	bme280Init(&atmospherical, &hi2c1);
	interfaceInit(&interface);
	interfaceSettingsInit(&settings);
	watchInit(&watch);
	timersInit();
	batteryCheckInit();
	forecastInit(&forecast);

	interfaceClear(&interface);
	interfaceUpdateModeSwitch(&interface, INTERFACE_UPDATE_MODE_PARTIAL);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		rtcGetTime(&chrono);
		lis3mdlRead(&magnetometer);
		lis3mdlGetCalibrationSample(&magnetometer);
		bme280Read(&atmospherical);
		batteryReadState();
		forecastAppendActual(&forecast, &atmospherical, &chrono);

		if (watch.mode == WATCH_MODE_NORMAL) {
			interfaceClear(&interface);

			HAL_GPIO_WritePin(LED_WKUP_GPIO_Port, LED_WKUP_Pin, 0);

			interfaceDrawMain(&interface, &chrono, &magnetometer,
					&atmospherical, &watch, &forecast);

			HAL_GPIO_WritePin(LED_WKUP_GPIO_Port, LED_WKUP_Pin, 1);

		} else if (watch.mode == WATCH_MODE_SETTINGS) {
			interfaceSettingsClear(&settings);
			interfaceSettingsDraw(&settings, &chrono, &magnetometer,
					&atmospherical, &watch);
		}

		interfaceBurn(&interface);

		if (watch.mode == WATCH_MODE_NORMAL
				&& watch.counterDontSleepTimer >= WATCH_TIME_DONT_SLEEP) {
			goodNight();
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
	RCC_OscInitStruct.PLL.PLLN = 8;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

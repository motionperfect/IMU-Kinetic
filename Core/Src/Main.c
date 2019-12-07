/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include <string.h>

#include "Main.h"
#include "cmsis_os.h"

#include "Peripherals/USART.h"
#include "Peripherals/GPIO.h"

static void vSystemClockConfig (void);
void vFreeRTOSInit (void);

/**
 * @brief Initializes the STM32L475 IoT node board.
 *
 * Initialization of clock, LEDs, RNG, RTC, and WIFI module.
 */
static void prvMiscInitialization (void);

/**
 * Output a character to UART, used by the printf() function
 * \param character Character to output
 */
void _putchar (char character)
{
  const uint32_t ulTimeout = 3000UL;

  HAL_UART_Transmit (&xConsoleUART, (uint8_t *)&character, 1, ulTimeout);
}

/**
 * Output a string to UART, used by the logger
 * \param pcString String to output
 */
void vMainUARTPrintString (char *pcString)
{
  const uint32_t ulTimeout = 3000UL;

  HAL_UART_Transmit (&xConsoleUART,
					 (uint8_t *)pcString,
					 strlen (pcString),
					 ulTimeout);
}

int main (void)
{
  /*
   * Perform any hardware initialization that does not require
   * the RTOS to be running.
   */
  prvMiscInitialization ();

  /* Start the scheduler. */
  if (osKernelStart () != osOK)
	{
	  vMainUARTPrintString ("Fatal: µKernel failed to start.\n");

	  for (;;)
		{

		}
	}
}

/**
 * @brief Initializes the board.
 */
// #include <stm32l475e_iot01.h>
static void prvMiscInitialization (void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init ();

  /* Configure the system clock. */
  vSystemClockConfig ();

  // BSP_LED_Init( LED_GREEN );
  // BSP_PB_Init( BUTTON_USER, BUTTON_MODE_EXTI );
  vGPIOInit ();

  /* RTC init. */
  // RTC_Init();

  /* UART console init. */
  vConsoleUARTInit ();

  /* FreeRTOS Tasks init. */
  vFreeRTOSInit ();
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void vSystemClockConfig (void)
{
  RCC_OscInitTypeDef xRCCOscInitStruct = {0};
  RCC_ClkInitTypeDef xRCCClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef xPeriphClkInit = {0};

  /*
   * Initializes the CPU, AHB and APB busses clocks
   */
  xRCCOscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  xRCCOscInitStruct.HSIState = RCC_HSI_ON;
  xRCCOscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  xRCCOscInitStruct.PLL.PLLState = RCC_PLL_ON;
  xRCCOscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  xRCCOscInitStruct.PLL.PLLM = 1;
  xRCCOscInitStruct.PLL.PLLN = 20;
  xRCCOscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  xRCCOscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  xRCCOscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
  if (HAL_RCC_OscConfig (&xRCCOscInitStruct) != HAL_OK)
	{
	  vErrorHandler ();
	}

  /*
   * Initializes the CPU, AHB and APB busses clocks
   */
  xRCCClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
								| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  xRCCClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  xRCCClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  xRCCClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  xRCCClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig (&xRCCClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
	  vErrorHandler ();
	}
  xPeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  xPeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig (&xPeriphClkInit) != HAL_OK)
	{
	  vErrorHandler ();
	}

  /*
   * Configure the main internal regulator output voltage
   */
  if (HAL_PWREx_ControlVoltageScaling (PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
	  vErrorHandler ();
	}
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1)
	{
	  HAL_IncTick ();
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

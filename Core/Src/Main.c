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
#include "Main.h"
#include "cmsis_os.h"

#include "Peripherals/USART.h"
#include "Peripherals/GPIO.h"

void vSystemClockConfig (void);
void vFreeRTOSInit (void);

/**
 * @brief Initializes the STM32L475 IoT node board.
 *
 * Initialization of clock, LEDs, RNG, RTC, and WIFI module.
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

	  for (;;);
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

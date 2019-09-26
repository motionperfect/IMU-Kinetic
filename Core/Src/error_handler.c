/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/

#include "error_handler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <inttypes.h>

void
vApplicationStackOverflowHook (TaskHandle_t xTask, signed char *pcTaskName)
{
  configPRINTF (("stack overflow on task: %s\n", pcTaskName));
  HAL_Error_Handler ();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void HAL_Error_Handler (void)
{
  /* Implementation to report the HAL error return state */
  for (;;)
	{
	  HAL_GPIO_TogglePin (
		  LED3_WIFI__LED4_BLE_GPIO_Port,
		  LED3_WIFI__LED4_BLE_Pin
	  );
	  osDelay (1000);
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed (char *file, uint32_t line)
{
  const char error[] = "Wrong parameters value: file %s on line %" PRIu32 "\r\n";

  configPRINTF ((error, file, line));
  HAL_Error_Handler ();
}
#endif /* USE_FULL_ASSERT */
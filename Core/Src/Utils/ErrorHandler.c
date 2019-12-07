/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/
#include <inttypes.h>

#include "FreeRTOS.h"
#include "task.h"
#include "stm32l475e_iot01.h"
#include "printf.h"

#include "Utils/ErrorHandler.h"

void vApplicationStackOverflowHook (TaskHandle_t xTask,
									signed char *pcTaskName)
{
  UNUSED (xTask);

  taskDISABLE_INTERRUPTS ();
  printf ("%ul [%s] Fatal: Stack overflow.\n",
		  (unsigned long)HAL_GetTick (),
		  pcTaskName);

  vErrorHandler ();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void vErrorHandler (void)
{
  for (;;)
	{
	  BSP_LED_Toggle (LED2);
	  HAL_Delay (1000);
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  pcFile: pointer to the source file name
  * @param  ulLine: assert_param error line source number
  * @retval None
  */
void assert_failed (char *pcFile, uint32_t ulLine)
{
  const char *pcTaskName = "None";

  printf ("%ul [%s] Fatal: Wrong parameters (file %s on line %" PRIu32 ").\n",
		  (unsigned long)HAL_GetTick (),
		  pcTaskName,
		  pcFile,
		  ulLine);

  vErrorHandler ();
}
#endif /* USE_FULL_ASSERT */
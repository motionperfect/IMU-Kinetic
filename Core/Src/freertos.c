/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"

osThreadId_t defaultTaskHandle;

void StartDefaultTask (void *argument);

void MX_FREERTOS_Init (void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init (void)
{
  osKernelInitialize ();

  const osThreadAttr_t defaultTask_attributes = {
	  .name = "defaultTask",
	  .priority = (osPriority_t)osPriorityNormal,
	  .stack_size = 128
  };
  defaultTaskHandle = osThreadNew (StartDefaultTask, NULL, &defaultTask_attributes);
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
void StartDefaultTask (void *argument)
{
  for (;;)
	{
	  HAL_GPIO_TogglePin (LED3_WIFI__LED4_BLE_GPIO_Port, LED3_WIFI__LED4_BLE_Pin);
	  osDelay (1000);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

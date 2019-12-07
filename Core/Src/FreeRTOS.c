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
#include "cmsis_os.h"

#include "FreeRTOSTasksConfig.h"
#include "Utils/Logger.h"

#include "Tasks/Measurement.h"
#include "Tasks/Logging.h"

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void vFreeRTOSInit (void)
{
  osKernelInitialize ();

  vLoggingTaskInit (configLOGGING_TASK_STACK_SIZE,
					configLOGGING_TASK_PRIORITY,
					configLOGGING_MESSAGE_QUEUE_LENGTH);

  vMeasurementTaskInit (configMEASUREMENT_TASK_STACK_SIZE,
						configMEASUREMENT_TASK_PRIORITY);

  configPRINT_STRING ("Info: µKernel successfully initialized.\n");
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

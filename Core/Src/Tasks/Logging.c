/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/
#include "FreeRTOS.h"
#include "cmsis_os.h"

#include "Peripherals/USART.h"
#include "Utils/ErrorHandler.h"
#include "LoggerConfig.h"

osMessageQueueId_t xLoggingMQ = NULL;

static void vStartLoggingTask (void *pvArgument);

void vLoggingTaskInit (uint32_t ulStackSize,
					   osPriority_t xPriority,
					   uint32_t ulQueueLength)
{
  const osThreadAttr_t xAttributes = {
	  .name = "Logging",
	  .priority = xPriority,
	  .stack_size = ulStackSize
  };

  xLoggingMQ = osMessageQueueNew (ulQueueLength, sizeof (char **), NULL);

  if (xLoggingMQ != NULL)
	{
	  if ((osThreadNew (&vStartLoggingTask, NULL, &xAttributes)) == NULL)
		{
		  osMessageQueueDelete (xLoggingMQ);
		  vErrorHandler ();
		}
	}
}

static void vStartLoggingTask (void *pvArgument)
{
  char *pcRecord = NULL;
  osStatus_t xStatus;

  UNUSED (pvArgument);
  for (;;)
	{
	  xStatus = osMessageQueueGet (xLoggingMQ,
								   &pcRecord,
								   NULL,
								   configMESSAGE_QUEUE_DONT_BLOCK);

	  if (xStatus == osOK)
		{
		  vMainUARTPrintString (pcRecord);
		  vPortFree ((void *)pcRecord);
		}
	}
}
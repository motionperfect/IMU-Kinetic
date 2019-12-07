/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/

#include <string.h>
#include <stdarg.h>

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
#include "printf.h"

#include "Tasks/Logging.h"
#include "LoggerConfig.h"

/*!
 * \brief Formats a string to be printed and sends it
 * to the print queue.
 *
 * Appends the message number, time (in ticks), and task
 * that called vLoggingPrintf to the beginning of each
 * print statement.
 *
 */
void vLoggerPrintf (const char *pcFormat, ...)
{
  size_t xTotalLength = 0;
  int32_t xMessageLength = 0;
  char *pcRecord = NULL;
  va_list xVarArgs;
  osStatus_t xStatus;

  configASSERT(xLoggingMQ)

  if ((pcRecord = pvPortMalloc (configLOGGER_MAX_MESSAGE_LENGTH)) == NULL)
	{
	  return;
	}

  va_start (xVarArgs, pcFormat);

  if (strcmp (pcFormat, "\n") != 0)
	{
	  #if (configLOGGER_INCLUDE_TIME_AND_TASK_NAME == 1)
	  {
		const char *pcTaskName;

		pcTaskName = xTaskGetSchedulerState () != taskSCHEDULER_NOT_STARTED
			? pcTaskGetName (NULL)
			: "None";

		xTotalLength = snprintf (pcRecord,
								 configLOGGER_MAX_MESSAGE_LENGTH,
								 "%lu [%s] ",
								 (unsigned long)xTaskGetTickCount (),
								 pcTaskName);
	  }
	  #endif
	}

  xMessageLength = vsnprintf (pcRecord + xTotalLength,
							  configLOGGER_MAX_MESSAGE_LENGTH - xTotalLength,
							  pcFormat,
							  xVarArgs);

  if (xMessageLength < 0)
	{
	  xMessageLength = 0;
	  pcRecord[xTotalLength] = '\0';
	}

  xTotalLength += (size_t)xMessageLength;
  va_end (xVarArgs);

  if (xTotalLength > 0)
	{
	  xStatus = osMessageQueuePut (xLoggingMQ,
								   &pcRecord,
								   0,
								   configMESSAGE_QUEUE_DONT_BLOCK);

	  if (xStatus == osOK) return;
	}
  vPortFree ((void *)pcRecord);
}

void vLoggerPrint (const char *pcMessage)
{
  char *pcRecord = NULL;
  size_t xTotalLength = 0;
  osStatus_t xStatus;

  configASSERT(xLoggingMQ)

  #if (configLOGGER_INCLUDE_TIME_AND_TASK_NAME == 1)
  {
	if ((pcRecord = pvPortMalloc (configLOGGER_MAX_MESSAGE_LENGTH)) == NULL)
	  {
		return;
	  }

	const char *pcTaskName;

	pcTaskName = xTaskGetSchedulerState () != taskSCHEDULER_NOT_STARTED
		? pcTaskGetName (NULL)
		: "None";

	xTotalLength = snprintf (pcRecord,
							 configLOGGER_MAX_MESSAGE_LENGTH,
							 "%lu [%s] %s",
							 (unsigned long)xTaskGetTickCount (),
							 pcTaskName,
							 pcMessage);
  }
  #else
  xTotalLength = strlen (pcMessage) + 1;
  if ((pcRecord = pvPortMalloc (xTotalLength)) == NULL)
	{
	  return;
	}
  #endif

  strncpy (pcRecord, pcMessage, xTotalLength);

  xStatus = osMessageQueuePut (xLoggingMQ,
							   &pcRecord,
							   0,
							   configMESSAGE_QUEUE_DONT_BLOCK);

  if (xStatus != osOK)
	{
	  vPortFree ((void *)pcRecord);
	}
}
/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/

#include "Tasks/accelerometer.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"

osThreadId_t accelerometerTaskHandle;

void startAccelerometerTask (void *argument);

void initAccelerometerTask (void)
{
  const osThreadAttr_t attributes = {
	  .name = "accelerometerTask",
	  .priority = (osPriority_t)osPriorityNormal,
	  .stack_size = 256
  };

  accelerometerTaskHandle = osThreadNew (
	  &startAccelerometerTask,
	  NULL,
	  &attributes
  );
}

void startAccelerometerTask (void *argument)
{
  for (;;)
	{
	  HAL_GPIO_TogglePin (LED2_GPIO_Port, LED2_Pin);
	  osDelay (1000);
	}
}
/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/
#include "FreeRTOS.h"
#include "cmsis_os.h"

#include "Utils/ErrorHandler.h"
#include "Utils/Logger.h"

#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_gyro.h"

static void vStartMeasurementTask (void *pvArgument);

void vMeasurementTaskInit (uint32_t ulStackSize, osPriority_t xPriority)
{
  const osThreadAttr_t attributes = {
	  .name = "Measurement",
	  .priority = xPriority,
	  .stack_size = ulStackSize
  };

  if ((osThreadNew (&vStartMeasurementTask, NULL, &attributes)) == NULL)
	{
	  vErrorHandler ();
	}
}

static void vStartMeasurementTask (void *pvArgument)
{
  int16_t sAcceleroDataXYZ[3];
  float fGyroDataXYZ[3];

  UNUSED (pvArgument);
  BSP_ACCELERO_Init ();
  BSP_GYRO_Init ();
  for (;;)
	{
	  BSP_ACCELERO_AccGetXYZ (sAcceleroDataXYZ);
	  BSP_GYRO_GetXYZ (fGyroDataXYZ);

	  configPRINTF (("Accelerometer: [X: %d, Y: %d, Z: Z: %d] Gyroscope: [X: %f, Y: %f, Z: %f]\n",
		  sAcceleroDataXYZ[0],
		  sAcceleroDataXYZ[1],
		  sAcceleroDataXYZ[2],
		  fGyroDataXYZ[0],
		  fGyroDataXYZ[1],
		  fGyroDataXYZ[2]));

	  osDelay (64); // 1000 / 208
	}
}
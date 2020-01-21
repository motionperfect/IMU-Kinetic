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

#include "Algorithms/AHRS/6dof.h"

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

static void prvNormalizeDataForAnalysis (SensorsData_t *const xSensorsData,
                                         const int16_t *const usAccelerometerData)
{
  const float32_t fDivider = 1000.0;

  xSensorsData->accelerometer.x = (float32_t)usAccelerometerData[0] / fDivider;
  xSensorsData->gyroscope.x /= fDivider;

  xSensorsData->accelerometer.y = (float32_t)usAccelerometerData[1] / fDivider;
  xSensorsData->gyroscope.y /= fDivider;

  xSensorsData->accelerometer.z = (float32_t)usAccelerometerData[2] / fDivider;
  xSensorsData->gyroscope.z /= fDivider;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
static void vStartMeasurementTask (void *pvArgument)
{
  SensorsData_t xSensorsData = {0};
  int16_t usAccelerometerData[3];

  UNUSED (pvArgument);
  BSP_ACCELERO_Init ();
  BSP_GYRO_Init ();
  for (;;)
    {
      BSP_ACCELERO_AccGetXYZ (usAccelerometerData);
      BSP_GYRO_GetXYZ ((float *)&xSensorsData.gyroscope);

      prvNormalizeDataForAnalysis (&xSensorsData, usAccelerometerData);
      JointState_t eState = eMovementAnalysis (&xSensorsData, SHOULDER);

      configPRINTF (("Accelerometer: [X: %f, Y: %f, Z: %f] Gyroscope: [X: %f, Y: %f, Z: %f]\n",
          xSensorsData.accelerometer.x,
          xSensorsData.accelerometer.y,
          xSensorsData.accelerometer.z,
          xSensorsData.gyroscope.x,
          xSensorsData.gyroscope.y,
          xSensorsData.gyroscope.z));
      configPRINTF(("Shoulder state: %d\n", eState));

      osDelay (64); // 1000 / 208
    }
}
#pragma clang diagnostic pop
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

static void fMilliGForceToGForce (arm_6dof_instance_f32 *instance)
{
  float32_t divider = 1000.0;

  instance->acc_x /= divider;
  instance->acc_y /= divider;
  instance->acc_z /= divider;

  instance->gyr_x /= divider;
  instance->gyr_y /= divider;
  instance->gyr_z /= divider;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
static void vStartMeasurementTask (void *pvArgument)
{
  int16_t sAcceleroDataXYZ[3];
  arm_6dof_instance_f32 sensorsData = {0};

  UNUSED (pvArgument);
  BSP_ACCELERO_Init ();
  BSP_GYRO_Init ();
  for (;;)
    {
      BSP_ACCELERO_AccGetXYZ (sAcceleroDataXYZ);
      BSP_GYRO_GetXYZ (&sensorsData.gyr_x);

      sensorsData.acc_x = (float32_t)sAcceleroDataXYZ[0];
      sensorsData.acc_y = (float32_t)sAcceleroDataXYZ[1];
      sensorsData.acc_z = (float32_t)sAcceleroDataXYZ[2];

      fMilliGForceToGForce (&sensorsData);
      jointures_state state = movement_analysis (&sensorsData, SHOULDER);

      configPRINTF (("Accelerometer: [X: %f, Y: %f, Z: %f] Gyroscope: [X: %f, Y: %f, Z: %f]\n",
          sensorsData.acc_x,
          sensorsData.acc_y,
          sensorsData.acc_z,
          sensorsData.gyr_x,
          sensorsData.gyr_y,
          sensorsData.gyr_z));
      configPRINTF(("shoulder state: %d\n", state));

      osDelay (64); // 1000 / 208
    }
}
#pragma clang diagnostic pop
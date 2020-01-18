/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2020 by Julien Sarriot
** All rights reserved.
*/

#include "Main.h"

/**
  * @brief System Clock Configuration
  * @retval None
  */
void vSystemClockConfig (void)
{
  RCC_OscInitTypeDef xRCCOscInitStruct = {0};
  RCC_ClkInitTypeDef xRCCClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef xPeriphClkInit = {0};

  /*
   * Initializes the CPU, AHB and APB busses clocks
   */
  xRCCOscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  xRCCOscInitStruct.HSIState = RCC_HSI_ON;
  xRCCOscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  xRCCOscInitStruct.PLL.PLLState = RCC_PLL_ON;
  xRCCOscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  xRCCOscInitStruct.PLL.PLLM = 1;
  xRCCOscInitStruct.PLL.PLLN = 20;
  xRCCOscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  xRCCOscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  xRCCOscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
  if (HAL_RCC_OscConfig (&xRCCOscInitStruct) != HAL_OK)
    {
      vErrorHandler ();
    }

  /*
   * Initializes the CPU, AHB and APB busses clocks
   */
  xRCCClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  xRCCClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  xRCCClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  xRCCClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  xRCCClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig (&xRCCClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
      vErrorHandler ();
    }
  xPeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  xPeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig (&xPeriphClkInit) != HAL_OK)
    {
      vErrorHandler ();
    }

  /*
   * Configure the main internal regulator output voltage
   */
  if (HAL_PWREx_ControlVoltageScaling (PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
      vErrorHandler ();
    }
}
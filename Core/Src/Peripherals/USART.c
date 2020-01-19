/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "Peripherals/USART.h"

UART_HandleTypeDef xConsoleUART;

void vConsoleUARTInit (void)
{

  xConsoleUART.Instance = USART1;
  xConsoleUART.Init.BaudRate = 115200;
  xConsoleUART.Init.WordLength = UART_WORDLENGTH_8B;
  xConsoleUART.Init.StopBits = UART_STOPBITS_1;
  xConsoleUART.Init.Parity = UART_PARITY_NONE;
  xConsoleUART.Init.Mode = UART_MODE_TX_RX;
  xConsoleUART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  xConsoleUART.Init.OverSampling = UART_OVERSAMPLING_16;
  xConsoleUART.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  xConsoleUART.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init (&xConsoleUART) != HAL_OK)
	{
	  vErrorHandler ();
	}

}

void HAL_UART_MspInit (UART_HandleTypeDef *pxUARTHandle)
{

  GPIO_InitTypeDef xGPIOInitStruct = {0};
  if (pxUARTHandle->Instance == USART1)
	{
	  /* USART1 clock enable */
	  __HAL_RCC_USART1_CLK_ENABLE();

	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  /**USART1 GPIO Configuration
	  PB6     ------> USART1_TX
	  PB7     ------> USART1_RX
	  */
	  xGPIOInitStruct.Pin = ST_LINK_UART1_TX_Pin | ST_LINK_UART1_RX_Pin;
	  xGPIOInitStruct.Mode = GPIO_MODE_AF_PP;
	  xGPIOInitStruct.Pull = GPIO_NOPULL;
	  xGPIOInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  xGPIOInitStruct.Alternate = GPIO_AF7_USART1;
	  HAL_GPIO_Init (GPIOB, &xGPIOInitStruct);
	}
}

void HAL_UART_MspDeInit (UART_HandleTypeDef *pxUARTHandle)
{

  if (pxUARTHandle->Instance == USART1)
	{
	  /* Peripheral clock disable */
	  __HAL_RCC_USART1_CLK_DISABLE();

	  /**USART1 GPIO Configuration
	  PB6     ------> USART1_TX
	  PB7     ------> USART1_RX
	  */
	  HAL_GPIO_DeInit (GPIOB, ST_LINK_UART1_TX_Pin | ST_LINK_UART1_RX_Pin);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

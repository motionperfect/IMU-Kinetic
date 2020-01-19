/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
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

#include "Main.h"
#include "stm32l4xx_it.h"
#include "FreeRTOS.h"
#include "task.h"

extern TIM_HandleTypeDef htim1;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler (void)
{

}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler (void)
{
  for (;;);
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler (void)
{
  for (;;);
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler (void)
{
  for (;;);
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler (void)
{
  for (;;);
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler (void)
{

}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler (void)
{
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_7);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_8);
}

/**
  * @brief This function handles TIM1 update interrupt and TIM16 global interrupt.
  */
void TIM1_UP_TIM16_IRQHandler (void)
{
  HAL_TIM_IRQHandler (&htim1);
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler (void)
{
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_13);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_14);
  HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_15);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

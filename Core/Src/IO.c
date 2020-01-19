/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2020 by Julien Sarriot
** All rights reserved.
*/
#include <string.h>

#include "Peripherals/USART.h"

/**
 * Output a character to UART, used by the printf() function
 * \param character Character to output
 */
void _putchar (char character)
{
  const uint32_t ulTimeout = 3000UL;

  HAL_UART_Transmit (&xConsoleUART, (uint8_t *)&character, 1, ulTimeout);
}

/**
 * Output a string to UART, used by the logger
 * \param pcString String to output
 */
void vMainUARTPrintString (char *pcString)
{
  const uint32_t ulTimeout = 3000UL;

  HAL_UART_Transmit (&xConsoleUART,
                     (uint8_t *)pcString,
                     strlen (pcString),
                     ulTimeout);
}

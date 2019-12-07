/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/
#ifndef _FREERTOSTASKSCONFIG_H_
#define _FREERTOSTASKSCONFIG_H_

/**
 * Logging task
 */
#define configLOGGING_TASK_PRIORITY                ((osPriority_t) osPriorityLow)
#define configLOGGING_TASK_STACK_SIZE            ( configMINIMAL_STACK_SIZE * 5 )
#define configLOGGING_MESSAGE_QUEUE_LENGTH        ( 15 )

/**
 * Measurement task
 */
#define configMEASUREMENT_TASK_STACK_SIZE        ( configMINIMAL_STACK_SIZE * 5 )
#define configMEASUREMENT_TASK_PRIORITY            ((osPriority_t) osPriorityHigh)

#endif //_FREERTOSTASKSCONFIG_H_

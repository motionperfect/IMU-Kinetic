/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/
#ifndef _LOGGERCONFIG_H_
#define _LOGGERCONFIG_H_

/*
 * Sets the length of the buffers into which logging messages are written.
 * So also defines the maximum length of each log message.
 */
#define configLOGGER_MAX_MESSAGE_LENGTH                ( 160 )

/* Prefix every message with time and task name */
#define configLOGGER_INCLUDE_TIME_AND_TASK_NAME        ( 1 )

/* A block time of 0 just means don't block. */
#define configMESSAGE_QUEUE_DONT_BLOCK                ( 0 )

#endif //_LOGGERCONFIG_H_

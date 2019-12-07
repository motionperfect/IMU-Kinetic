/*
** EPITECH PROJECT, 2021
** MotionPerfect
** File description:
** Copyright (c) 2019 by Julien Sarriot
** All rights reserved.
*/
#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "cmsis_os.h"

extern osMessageQueueId_t xLoggingMQ;

void vLoggingTaskInit (uint32_t ulStackSize,
					   osPriority_t xPriority,
					   uint32_t ulQueueLength);

#endif //_LOGGING_H_

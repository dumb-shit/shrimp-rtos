#ifndef __4GDTU_H
#define __4GDTU_H


#include "stm32f4xx.h"       
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ds18b20.h"
#include "relay.h"
#include "motor.h"

#define BUFFER_SIZE 350
#define KEYWORD_COUNT 7

void vReceiveTask(void *pvParameters);
void vReceiveQueueTask(void *pvParameters);

void HAL_UART_INTERRUPT(void);


#endif


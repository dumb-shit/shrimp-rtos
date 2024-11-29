#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f4xx.h"                  // Device header
#include "gpio.h"
#include "main.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "usart.h"
#include "string.h"


#define PORT_DQ         GPIOD
#define GPIO_DQ         GPIO_PIN_11
#define DQ(x)           HAL_GPIO_WritePin(PORT_DQ, GPIO_DQ, (x ? GPIO_PIN_SET : GPIO_PIN_RESET))
#define	DQ_GET()        HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_11)


void DQ_OUT(void);
void DQ_IN(void);
uint8_t DS18B20_Read_Byte(void);
void DS18B20_Reset(void);
uint8_t DS18B20_Check(void);
char DS18B20_GPIO_Init(void);
void DS18B20_Start(void);
float DS18B20_GetTemperture(void);
void vTaskDS18B20Print(void *pvParameters);

#endif

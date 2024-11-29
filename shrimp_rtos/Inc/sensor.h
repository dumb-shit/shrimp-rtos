#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f4xx.h"                  // Device header
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "usart.h"
#include "string.h"
#include "tim.h"

#define VCC 3.3


uint32_t Get_ADC_Value(ADC_HandleTypeDef *hadc);
float Calculate_PH(void);
float Calculate_tur(void);
float Calculate_tds(void);
void vTaskTur(void *pvParameters);
void vTaskpH(void *pvParameters);
void vTaskTDS(void *pvParameters);


#endif

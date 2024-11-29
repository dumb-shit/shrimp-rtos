#include "RELAY.h"

#define RELAY GPIOD

typedef enum {
    RELAY_LIGHT = GPIO_PIN_8,
    RELAY_WATER = GPIO_PIN_9,
    RELAY_OXYGEN = GPIO_PIN_10
} RelayPin;


/*
	接收字符串并解析，若数值为1，则开，0则关(灯，水泵，氧泵)
*/

void light_control(int light)
{
	if(light==1)
	{
		HAL_GPIO_WritePin(RELAY,RELAY_LIGHT,GPIO_PIN_RESET);
	}else
	{
		HAL_GPIO_WritePin(RELAY,RELAY_LIGHT,GPIO_PIN_SET);
	}
}

void water_control(int water)
{
	if(water==1)
	{
		HAL_GPIO_WritePin(RELAY,RELAY_WATER,GPIO_PIN_RESET);
	}else
	{
		HAL_GPIO_WritePin(RELAY,RELAY_WATER,GPIO_PIN_SET);
	}
}

void oxygen_control(int oxygen)
{
	if(oxygen==1)
	{
		HAL_GPIO_WritePin(RELAY,RELAY_OXYGEN,GPIO_PIN_RESET);
	}else
	{
		HAL_GPIO_WritePin(RELAY,RELAY_OXYGEN,GPIO_PIN_SET);
	}
}


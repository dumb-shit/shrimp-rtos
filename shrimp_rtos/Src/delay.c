#include "delay.h"



void delay_us(uint32_t nus)
{
 
 uint16_t  differ = 0xffff-nus-5;

  __HAL_TIM_SetCounter(&htim6,differ);

  HAL_TIM_Base_Start(&htim6);
 
  while( differ<0xffff-5)
 {
  differ = __HAL_TIM_GetCounter(&htim6);
 };
  HAL_TIM_Base_Stop(&htim6);
}





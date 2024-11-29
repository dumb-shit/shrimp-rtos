#include "motor.h"

/*
 * @brief  PWM初始化（电机投喂）
 * @param  无
 * @retval 无
 */
void Pwm_Init(void)
{
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1); //MOTORA
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2); //MOTORA
	
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);  //MOROTB
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);  //MOTORB
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);  //MOTORC
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);  //MOROTC
	
	HAL_TIM_PWM_Start(&htim13,TIM_CHANNEL_1); //MOTORD
	HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1); //MOTORD
}

/*
	START为开始投喂，STOP为停止，1234分别代表四个电机
*/

void PWM_START1(void)
{
  __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,99);
}

void PWM_START2(void)
{
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,99);
}

void PWM_START3(void)
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,99);
}

void PWM_START4(void)
{
	__HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1,99);
}

void PWM_STOP1(void)
{
  __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,0);
}

void PWM_STOP2(void)
{
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,0);
}

void PWM_STOP3(void)
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
}

void PWM_STOP4(void)
{
	__HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1,0);
}






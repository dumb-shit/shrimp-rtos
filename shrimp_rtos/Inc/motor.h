#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx.h"                  // Device header
#include "tim.h"

void Pwm_Init(void);
void PWM_START1(void);
void PWM_START2(void);
void PWM_START3(void);
void PWM_START4(void);
void PWM_STOP1(void);
void PWM_STOP2(void);
void PWM_STOP3(void);
void PWM_STOP4(void);


#endif

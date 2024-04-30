#ifndef _NODE_H_
#define _NODE_H_

#include "main.h"
#include "tim.h"
#include "pid.h"
#include "interrupt.h"

#define RELOADVALUE0 __HAL_TIM_GetAutoreload(&htim1)
#define RELOADVALUE1 __HAL_TIM_GetAutoreload(&htim3)
#define COUNTERNUM0 __HAL_TIM_GetCounter(&htim1)
#define COUNTERNUM1 __HAL_TIM_GetCounter(&htim3)
#define IN1(state) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,(GPIO_PinState)(state))
#define IN2(state) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,(GPIO_PinState)(state))
#define IN3(state) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,(GPIO_PinState)(state))
#define IN4(state) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,(GPIO_PinState)(state))



//±äÁ¿




//º¯Êý
void START_INIT();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Motor_Send();

#endif


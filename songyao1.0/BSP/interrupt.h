#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "main.h"
#include "tim.h"
#include "node.h"


#define cnt1 TIM2->CNT
#define cnt2 TIM3->CNT
#define arr1 TIM2->ARR
#define arr2 TIM3->ARR


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void UPDATA_NODE(void);


#endif

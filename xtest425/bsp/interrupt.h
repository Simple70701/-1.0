#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "main.h"
#include "tim.h"
#include "pid.h"
#include "node.h"
extern pid_def* mypid[2];
typedef struct 
{
    int32_t lastAngle; //上10ms转过的角度
    int32_t totalAngle;	//总转过角度
    int32_t loopnum; //防超过上限
    float speed;//当前电机速度
    float set; 
    float targetSpeed;
}Motor;//电调结构体

extern Motor motor[2];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void MOTOR_NODE();

#endif

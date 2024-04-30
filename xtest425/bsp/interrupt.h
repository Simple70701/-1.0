#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "main.h"
#include "tim.h"
#include "pid.h"
#include "node.h"
extern pid_def* mypid[2];
typedef struct 
{
    int32_t lastAngle; //��10msת���ĽǶ�
    int32_t totalAngle;	//��ת���Ƕ�
    int32_t loopnum; //����������
    float speed;//��ǰ����ٶ�
    float set; 
    float targetSpeed;
}Motor;//����ṹ��

extern Motor motor[2];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void MOTOR_NODE();

#endif

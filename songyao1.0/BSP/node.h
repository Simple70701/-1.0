#ifndef _NODE_H_
#define _NODE_H_

#include "main.h"
#include "tim.h"
#include "pid.h"


#define IN1(state) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,(GPIO_PinState)(state))
#define IN2(state) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,(GPIO_PinState)(state))
#define IN3(state) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,(GPIO_PinState)(state))
#define IN4(state) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,(GPIO_PinState)(state))

typedef struct 
{
    int32_t lastAngle; //��10msת���ĽǶ�
    int32_t totalAngle;	//��ת���Ƕ�
    int32_t loopnum; //����������
    float speed;//��ǰ����ٶ�
    float targetSpeed;
}Motor;//����ṹ��

typedef struct 
{
    pid_def selfpid;
    fp32 ref;
    fp32 set;
    fp32 pid_pwm;

}pid_user;

extern Motor motor[2];



void START_INIT(void);
void MOTOR_NODE(void);

#endif


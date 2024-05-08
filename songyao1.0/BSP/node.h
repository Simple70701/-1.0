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
    int32_t lastAngle; //上10ms转过的角度
    int32_t totalAngle;	//总转过角度
    int32_t loopnum; //防超过上限
    float speed;//当前电机速度
    float targetSpeed;
}Motor;//电调结构体

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


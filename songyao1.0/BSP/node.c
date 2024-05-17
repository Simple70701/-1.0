#include "node.h"

#define RESO 1000/130

Motor motor[2];
//PID相关
pid_user mypid[2];
int pid_lock=0;

//PID参数
fp32 kpid[3]={2,0,2};//kp,ki,kd系数
fp32 max_out=130;
fp32 max_iout=0;



void START_INIT(void)
{
    //PID初始化
    PID_init(&mypid[0].selfpid,0,kpid,max_out,max_iout);
    PID_init(&mypid[1].selfpid,0,kpid,max_out,max_iout);
    
    
    //TIM4,定时10MS
    HAL_TIM_Base_Start_IT(&htim4);
    
    //TIM1,输出PWM
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    
    //TIM2,TIM3,编码器模式
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_UPDATE);
    __HAL_TIM_ENABLE_IT(&htim3,TIM_IT_UPDATE);
    __HAL_TIM_SetCounter(&htim2,10000);
	__HAL_TIM_SetCounter(&htim3,10000);
    
    
    motor[0].loopnum=0;
    motor[1].loopnum=0;
    mypid[0].set=50;
    mypid[1].set=50;
}


void PWM_NODE(void)
{

    IN1(1);
    IN2(0);
    IN3(1);
    IN4(0);
}

void MOTOR_NODE(void)
{
    if(pid_lock==1)
    {
        for(int i=0;i<2;i++)
        {
            mypid[i].ref=motor[i].speed;
            mypid[i].pid_speed=PID_calc(&mypid[i].selfpid,mypid[i].ref,mypid[i].set);
            PID_clear(&mypid[i].selfpid);

        }
        
        __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,mypid[0].pid_speed*RESO);
        __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,mypid[1].pid_speed*RESO);
        pid_lock=0;
    }
    

}



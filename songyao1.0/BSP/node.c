#include "node.h"

#define RESO 400/170

Motor motor[2]={0};
//PID相关
pid_user mypid[2]={0};
int pid_lock=0;

//PID参数
fp32 kpid[3]={13,3.5,0.04};//kp,ki,kd系数
fp32 max_out=170;
fp32 max_iout=10;



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
    mypid[0].set=150;
    mypid[1].set=150;
}



void MOTOR_NODE(void)
{

        for(int i=0;i<2;i++)
        {
            mypid[i].ref=motor[i].speed;
            mypid[i].pid_speed=PID_calc(&mypid[i].selfpid,mypid[i].ref,mypid[i].set);
            PID_clear(&mypid[i].selfpid);

        }

        if(mypid[0].pid_speed>0)
        {
            IN1(0);
            IN2(1);
            __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,mypid[0].pid_speed*RESO);
        }
        else 
        {
            IN1(1);
            IN2(0);
            __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,mypid[0].pid_speed*RESO);
        }
        
        if(mypid[1].pid_speed>0)
        {
            IN3(0);
            IN4(1);
            __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,mypid[1].pid_speed*RESO);
        }
        else 
        {
            IN3(1);
            IN4(0);
            __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,mypid[1].pid_speed*RESO);
        }
        
    

}



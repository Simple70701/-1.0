#include "node.h"
//pid_init相关参数
fp32 kpid[3]={10,-1,3};
fp32 max_out=10000;
fp32 max_iout=10000;
extern pid_def* mypid[2];
//电调相关数组
Motor motor[2]={0,0,0,0,0,200};
fp32 output[2]={0};

void START_INIT()
{
    //HTIM1.3
    HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);//开启编码器定时器
	__HAL_TIM_ENABLE_IT(&htim3,TIM_IT_UPDATE);
    __HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);//开启编码器中断
    __HAL_TIM_SetCounter(&htim1,10000);//左右轮子要标出
	__HAL_TIM_SetCounter(&htim3,10000);//设编码器定时器计数值为10000
    
    //HTIM2，PWM输出
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);//输出PWM
    
    //HTIM4,定时功能
    HAL_TIM_Base_Start_IT(&htim4);//开启10ms定时器中断
    
    //pid初始化
    PID_init(mypid[0],0,kpid,max_out,max_iout);
    PID_init(mypid[1],0,kpid,max_out,max_iout);
    motor[0].loopnum=0;//防溢出
	motor[1].loopnum=0;
}


void Motor_Send()
{
	output[0]=PID_calc(mypid[0],motor[0].targetSpeed, motor[0].speed);
    output[1]=PID_calc(mypid[1],motor[1].targetSpeed, motor[1].speed);
	if(output[0] < 0)	//正转
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, (uint32_t)-output[0]);
		IN3(1);
		IN4(0);
	}
	else										//反转
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, (uint32_t)(+output[0]));
		IN3(0);
		IN4(1);
	}
	if(output[1] < 0)	//正转
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, (uint32_t)-output[1]);
		IN1(0);
		IN2(1);
	}
	else										//反转
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, (uint32_t)(+output[1]));
		IN1(1);
		IN2(0);
	}
}



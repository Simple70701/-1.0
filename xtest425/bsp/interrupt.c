#include "interrupt.h"

void MOTOR_NODE()
{
        int16_t plus0=COUNTERNUM0-RELOADVALUE0/2;//��ǰ������ֵ-10000
        int16_t plus1=COUNTERNUM1-RELOADVALUE1/2;
        motor[0].totalAngle=plus0+motor[0].loopnum*RELOADVALUE0/2;
        motor[1].totalAngle=plus1+motor[1].loopnum*RELOADVALUE1/2;//ת���ܽǶ�=��ǰ������ֵ-10000+0*10000	
        motor[0].speed=(float)(motor[0].totalAngle-motor[0].lastAngle)*6000/(4*13*30);//���10ms�ڵ��ٶ�r/min
        motor[1].speed=(float)(motor[1].totalAngle-motor[1].lastAngle)*6000/(4*13*30);
        motor[0].lastAngle=motor[0].totalAngle;
        motor[1].lastAngle=motor[1].totalAngle;//�������һ�μ�������ֵ
		Motor_Send();
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM4)//10ms��һ���ж�
	{
       MOTOR_NODE();
	}
	
	if(htim->Instance==TIM1)
	{
        if(COUNTERNUM0 < 10000)	
            motor[0].loopnum++;
		else if(COUNTERNUM0 > 10000)	
            motor[0].loopnum--;
		
		__HAL_TIM_SetCounter(&htim1, 10000);
	}
    if(htim->Instance==TIM3)
    {
        if(COUNTERNUM1 < 10000)	
            motor[1].loopnum++;
		else if(COUNTERNUM1 > 10000)	
            motor[1].loopnum--;
		__HAL_TIM_SetCounter(&htim3, 10000);
    }
} 


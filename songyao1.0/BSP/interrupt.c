#include "interrupt.h"


//�յ����������ݣ��������ݺ���
void UPDATA_NODE()
{
    int16_t pluse1=cnt1-arr1/2;
    int16_t pluse2=cnt2-arr2/2;
    
    motor[0].totalAngle=pluse1+motor[0].loopnum*arr1/2;
    motor[0].speed=(float)(motor[0].totalAngle-motor[0].lastAngle)*6000/(4*13*30);//���10ms�ڵ��ٶ�r/min
    motor[0].lastAngle=motor[0].totalAngle;
    
    motor[1].totalAngle=pluse2+motor[1].loopnum*arr2/2;//ת���ܽǶ�=��ǰ������ֵ-10000+0*10000	
    motor[1].speed=(float)(motor[1].totalAngle-motor[1].lastAngle)*6000/(4*13*30);
    motor[1].lastAngle=motor[1].totalAngle;//�������һ�μ�������ֵ
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM4)
    {
        UPDATA_NODE();
    }
    else if(htim->Instance==TIM2)
    {
        if(cnt1 < 10000)	
            motor[0].loopnum++;
		else if(cnt1 > 10000)	
            motor[0].loopnum--;
        
		__HAL_TIM_SetCounter(&htim2, 10000); 
    }
    else if(htim->Instance==TIM3)
    {
        if(cnt2 < 10000)	
            motor[0].loopnum++;
		else if(cnt2 > 10000)	
            motor[0].loopnum--;
        
		__HAL_TIM_SetCounter(&htim3, 10000); 
    }
}
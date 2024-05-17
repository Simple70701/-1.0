#include "interrupt.h"


//收到编码器数据，更新数据函数
void UPDATA_NODE()
{


        motor[0].totalAngle=(cnt1-10000)+motor[0].loopnum*10000;
        motor[0].speed=(float)(motor[0].totalAngle-motor[0].lastAngle)/(4*11*35)*6000;    
        motor[0].lastAngle=motor[0].totalAngle;
    
        motor[1].totalAngle=(cnt2-10000)+motor[0].loopnum*10000;
        motor[1].speed=(float)(motor[1].totalAngle-motor[1].lastAngle)/(4*11*35)*6000;    
        motor[1].lastAngle=motor[1].totalAngle;

    



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
            motor[1].loopnum++;
		else if(cnt2 > 10000)	
            motor[1].loopnum--;
        __HAL_TIM_SetCounter(&htim3, 10000); 
        
    }
}
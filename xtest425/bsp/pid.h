#ifndef _PID_H_
#define _PID_H_

#include "main.h"
#include "struct_typedef.h"
#include "stdio.h"

typedef struct
{
    uint8_t mode;
    //PID 三参数
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_out;  //最大输出
    fp32 max_iout; //最大积分输出

    fp32 set;
    fp32 fdb;

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
    fp32 Dbuf[3];  //微分项 0最新 1上一次 2上上次
    fp32 error[3]; //误差项 0最新 1上一次 2上上次
}pid_def;

extern void PID_clear(pid_def *pid);
extern void PID_init(pid_def *pid, uint8_t mode,  fp32 PID[3], fp32 max_out, fp32 max_iout);
/*
*pid：pidPID结构数据指针
mode:普通PID模式
PID[3]:差分PID[],就是三个系数
max_out,max_iout:PID最大输出，pid最大积分输出
*/
extern fp32 PID_calc(pid_def *pid, fp32 ref, fp32 set);
/*
*pid：pidPID结构数据指针
REF:输入反馈数值（实际值）
SET:输出设定值（期望值）
*/
#endif




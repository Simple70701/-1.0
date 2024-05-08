#ifndef _PID_H_
#define _PID_H_

#include "main.h"
#include "struct_typedef.h"
#include "stdio.h"

typedef struct
{
    uint8_t mode;
    //PID ������
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_out;  //������
    fp32 max_iout; //���������

    fp32 set;
    fp32 fdb;

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
    fp32 Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
    fp32 error[3]; //����� 0���� 1��һ�� 2���ϴ�
}pid_def;

extern void PID_clear(pid_def *pid);
extern void PID_init(pid_def *pid, uint8_t mode,  fp32 PID[3], fp32 max_out, fp32 max_iout);
/*
*pid��pidPID�ṹ����ָ��
mode:��ͨPIDģʽ
PID[3]:���PID[],��������ϵ��
max_out,max_iout:PID��������pid���������
*/
extern fp32 PID_calc(pid_def *pid, fp32 ref, fp32 set);
/*
*pid��pidPID�ṹ����ָ��
REF:���뷴����ֵ��ʵ��ֵ��
SET:����趨ֵ������ֵ��
*/
#endif




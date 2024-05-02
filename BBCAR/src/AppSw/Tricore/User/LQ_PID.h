#ifndef SRC_APPSW_TRICORE_USER_LQ_PID_H_
#define SRC_APPSW_TRICORE_USER_LQ_PID_H_

#include <stdint.h>
#include <LQ_CCU6.h>

typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //�����޷�

    float                out_p;  //KP���
    float                out_i;  //KI���
    float                out_d;  //KD���
    float                out;    //pid���

    float                integrator; //< ����ֵ
    float                last_error; //< �ϴ����
    float                last_derivative;//< �ϴ���������ϴ����֮��
    unsigned long        last_t;     //< �ϴ�ʱ��
}pid_param_t;


void Set_PID(void);

void Pid_Value(void);

void PidInit(pid_param_t * pid);

float constrain_float(float amt, float low, float high);

float PidLocCtrl(pid_param_t * pid, float error);

float PidIncCtrl(pid_param_t * pid, float error);

#endif /* SRC_APPSW_TRICORE_USER_LQ_PID_H_ */

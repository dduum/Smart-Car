#ifndef SRC_APPSW_TRICORE_USER_LQ_PID_H_
#define SRC_APPSW_TRICORE_USER_LQ_PID_H_

#include <stdint.h>
#include <LQ_CCU6.h>

typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //锟斤拷锟斤拷锟睫凤拷

    float                out_p;  //KP锟斤拷锟�
    float                out_i;  //KI锟斤拷锟�
    float                out_d;  //KD锟斤拷锟�
    float                out;    //pid锟斤拷锟�

    float                integrator; //< 锟斤拷锟斤拷值
    float                last_error; //< 锟较达拷锟斤拷锟�
    float                last_derivative;//< 锟较达拷锟斤拷锟斤拷锟斤拷锟斤拷洗锟斤拷锟斤拷之锟斤拷
    unsigned long        last_t;     //< 锟较达拷时锟斤拷
}pid_param_t;

extern pid_param_t Servo_Loc_PID;
extern pid_param_t Motor_Inc_PID1;
extern pid_param_t Motor_Inc_PID2;

void Set_PID(void);

void Pid_Value(void);

void PidInit(pid_param_t * pid);

float constrain_float(float amt, float low, float high);

float PidLocCtrl(pid_param_t * pid, float error);

float PidIncCtrl(pid_param_t * pid, float error);

#endif /* SRC_APPSW_TRICORE_USER_LQ_PID_H_ */

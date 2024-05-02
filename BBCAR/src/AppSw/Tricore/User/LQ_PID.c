#include <LQ_PID.h>

pid_param_t Servo_Loc_PID;  //
pid_param_t Motor_Inc_PID1; //
pid_param_t Motor_Inc_PID2; //
pid_param_t Servo_Loc_PID2; //

void Set_PID(void)
{
    PidInit(&Servo_Loc_PID);
    PidInit(&Motor_Inc_PID1);
    PidInit(&Motor_Inc_PID2);
    PidInit(&Servo_Loc_PID2);
    Pid_Value();
}

void Pid_Value(void)
{
    //
    Servo_Loc_PID.kp=20.5;
    Servo_Loc_PID.ki=10.5;
    Servo_Loc_PID.kd=5.5; //1
    //
    Motor_Inc_PID1.kp=40;
    Motor_Inc_PID1.ki=0.62;
    Motor_Inc_PID1.kd=0;
    //
    Motor_Inc_PID2.kp=40;
    Motor_Inc_PID2.ki=0.62;
    Motor_Inc_PID2.kd=0;
    //
    Servo_Loc_PID2.kp=30;
    Servo_Loc_PID2.ki=0;
    Servo_Loc_PID2.kd=0;

}

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷float constrain_float(float amt, float low, float high)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷锟睫凤拷锟斤拷锟斤拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
  * @param    amt   锟斤拷 锟斤拷锟斤拷
  * @param    low   锟斤拷 锟斤拷锟街�
  * @param    high  锟斤拷 锟斤拷锟街�
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷4锟斤拷1锟斤拷
 *  锟斤拷    注锟斤拷
 *************************************************************************/
float constrain_float(float amt, float low, float high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// pid锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
void PidInit(pid_param_t * pid)
{
    pid->kp        = 0;
    pid->ki        = 0;
    pid->kd        = 0;
    pid->imax      = 0;
    pid->out_p     = 0;
    pid->out_i     = 0;
    pid->out_d     = 0;
    pid->out       = 0;
    pid->integrator= 0;
    pid->last_error= 0;
    pid->last_derivative   = 0;
    pid->last_t    = 0;
}


/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷float constrain_float(float amt, float low, float high)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷pid位锟斤拷式锟斤拷锟斤拷锟斤拷锟斤拷锟�
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
  * @param    pid     pid锟斤拷锟斤拷
  * @param    error   pid锟斤拷锟斤拷锟斤拷锟�
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷PID锟斤拷锟斤拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷4锟斤拷1锟斤拷
 *  锟斤拷    注锟斤拷位锟斤拷式锟斤拷锟斤拷锟斤拷锟�
 *************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{
	/* 锟桔伙拷锟斤拷锟� */
	pid->integrator += error;

	/* 锟斤拷锟斤拷薹锟� */
	constrain_float(pid->integrator, -pid->imax, pid->imax);

	pid->out_p = pid->kp * error;
	pid->out_i = pid->ki * pid->integrator;
	pid->out_d = pid->kd * (error - pid->last_error);

	pid->last_error = error;

	pid->out = pid->out_p + pid->out_i + pid->out_d;

	return pid->out;
}


/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷float constrain_float(float amt, float low, float high)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷pid锟斤拷锟斤拷式锟斤拷锟斤拷锟斤拷锟斤拷锟�
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
  * @param    pid     pid锟斤拷锟斤拷
  * @param    error   pid锟斤拷锟斤拷锟斤拷锟�
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷PID锟斤拷锟斤拷锟斤拷   注锟斤拷锟斤拷锟斤拷锟斤拷锟窖撅拷锟斤拷锟斤拷锟斤拷锟较次斤拷锟�
 *  锟睫革拷时锟戒：2020锟斤拷4锟斤拷1锟斤拷
 *  锟斤拷    注锟斤拷
 *************************************************************************/
float PidIncCtrl(pid_param_t * pid, float error)
{
	pid->out_p = pid->kp * (error - pid->last_error);
	pid->out_i = pid->ki * error;
	pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

	pid->last_derivative = error - pid->last_error;
	pid->last_error = error;

	pid->out += pid->out_p + pid->out_i + pid->out_d;

	return pid->out;
}


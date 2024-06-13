/*
 * My_Control_Code.h
 * 存放原本存储在CCU6中的代码
 *  Created on: 2024年4月21日
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_
#define SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_

#include <My_Key.h>
#include <LQ_PID.h>
#include <LQ_CAMERA.h>
#include <LQ_MotorServo.h>
#include <Platform_Types.h>
#include <My_UART.h>
#include <FuzzyPID.h>
#include <Element_handle.h>

extern float Tmp_FuzzyOut;
extern short Dir_out;
extern float K_Dir;
extern float Image_kp;
extern float Image_kd;
extern uint8 Look_Line;
extern uint8 Key_Value;
extern int change_count;
extern uint8 Select_PID;
extern float Motor_IncPID;
extern float Motor_IncPID1;
extern float Motor_IncPID2;
extern float Current_Speed;
extern float Current_Speed1;        //速度单位m/s
extern float Current_Speed2;
extern int Servo_duty;
extern uint8 Motor_openFlag;         //电机启动标志
extern uint8 Servo_openFlag;         //舵机启动标志
extern short Motor_duty1;
extern short Motor_duty2;
extern int Target_Speed;
extern int max_pix;
extern int min_pix;
extern volatile sint16 LPulse;          // 速度全局变量
extern volatile sint16 YPulse;          // 速度全局变量
extern int Test_err;
extern int Test_err_d;


void Modify_PID(void);
void Key_Control(void);
void Motor_Control(void);
void Servo_Control_Fuzzy(void);
void Servo_Control_PD(void);
int Low_Pass_Filter(int encinput,int* Feedback_enc,long int* Feedback_enc_tmp);

#endif /* SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_ */

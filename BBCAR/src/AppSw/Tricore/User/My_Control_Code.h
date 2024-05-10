/*
 * My_Control_Code.h
 * ���ԭ���洢��CCU6�еĴ���
 *  Created on: 2024��4��21��
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_
#define SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_

#include <My_Key.h>
#include <LQ_PID.h>
#include <LQ_CAMERA.h>
#include <LQ_MotorServo.h>
#include <Platform_Types.h>
#include <image_Handle.h>
#include <My_UART.h>

extern uint8 Key_Value;
extern uint8 Select_PID;
extern float Motor1_IncPID;
extern float Motor2_IncPID;                  //
extern float Motor_DirPId;                   //
extern float Current_Speed1;        //�ٶȵ�λm/s
extern float Current_Speed2;
extern volatile sint16 LPulse;                 //
extern volatile sint16 YPulse;                 //
extern int Servo_duty;
extern uint8 Motor_openFlag;         //���������־
extern uint8 Servo_openFlag;         //���������־
extern short Motor_duty1;
extern short Motor_duty2;
extern float Target_Speed;

void Modify_PID(void);
void Key_Control(void);
void Motor_Control(void);
void Servo_Control(void);
void Camera_Control(void);

#endif /* SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_ */

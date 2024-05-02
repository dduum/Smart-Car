/*
 * My_Control_Code.h
 * ���ԭ���洢��CCU6�еĴ���
 *  Created on: 2024��4��21��
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_
#define SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_

#include "My_Key.h"

#include <LQ_PID.h>
#include <LQ_CAMERA.h>
#include <LQ_MotorServo.h>
#include <Platform_Types.h>

extern int Servo_Loc_error;                 //���λ��ʽPID���
extern volatile uint8 Servo_openFlag;
extern volatile uint8 Motor_openFlag;
extern volatile short Motor_duty1;
extern volatile short Motor_duty2;
extern volatile float Target_Speed1;        //����Ŀ���ٶ�m/s
extern volatile float Target_Speed2;        //�ҵ��Ŀ���ٶ�m/s
extern volatile uint8 Motor_openFlag;
extern volatile int Left_Line[LCDH];           //��߽�
extern volatile int Right_Line[LCDH];          //�ұ߽�
extern volatile int Middle_Line[LCDH];         //�б߽�

void Key_Control(void);
void Motor_Control(void);
void Servo_Control(void);
void Camera_Control(void);


#endif /* SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_ */

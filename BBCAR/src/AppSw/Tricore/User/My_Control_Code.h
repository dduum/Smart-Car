/*
 * My_Control_Code.h
 * 存放原本存储在CCU6中的代码
 *  Created on: 2024年4月21日
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_
#define SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_

#include "My_Key.h"

#include <LQ_PID.h>
#include <LQ_CAMERA.h>
#include <LQ_MotorServo.h>
#include <Platform_Types.h>

extern int Servo_Loc_error;                 //舵机位置式PID误差
extern volatile uint8 Servo_openFlag;
extern volatile uint8 Motor_openFlag;
extern volatile short Motor_duty1;
extern volatile short Motor_duty2;
extern volatile float Target_Speed1;        //左电机目标速度m/s
extern volatile float Target_Speed2;        //右电机目标速度m/s
extern volatile uint8 Motor_openFlag;
extern volatile int Left_Line[LCDH];           //左边界
extern volatile int Right_Line[LCDH];          //右边界
extern volatile int Middle_Line[LCDH];         //中边界

void Key_Control(void);
void Motor_Control(void);
void Servo_Control(void);
void Camera_Control(void);


#endif /* SRC_APPSW_TRICORE_USER_MY_CONTROL_CODE_H_ */

#ifndef SRC_APPSW_TRICORE_USER_MY_MENU_H_
#define SRC_APPSW_TRICORE_USER_MY_MENU_H_

#include <LQ_TFT18.h>
#include "My_Key.h"
#include <LQ_CAMERA.h>
#include <stdio.h>
#include <LQ_MotorServo.h>
#include <LQ_PID.h>

int menu_one(void);
int menu_two(int flag);
void menu_three(int Key_flag);
void ShowPID(void);
void ShowCamera(void);
void Show_Island(void);
void Show_ServoPid(void);
void Show_MotorIncPid1(void);
void Show_MotorIncPid2(void);
void Base_Information_One(void);
void Base_Information_Two(void);
void Show_CameraElementFlag(void);
void Show_MotorDirPid(void);
void Show_CrossWay(void);
void Show_PIDALL(void);
void Show_ENC(void);


#endif /* SRC_APPSW_TRICORE_USER_MY_MENU_H_ */

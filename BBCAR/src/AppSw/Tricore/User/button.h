/*
 * button.h
 *
 *  Created on: 2024年4月29日
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_BUTTON_H_
#define SRC_APPSW_TRICORE_USER_BUTTON_H_

#define BtnN    0    /* 右键 */
#define BtnE    1    /* 确认键 */
#define BtnR    2    /* 返回键 */

#define KEY0_Pin P22_3   //K1
#define KEY1_Pin P22_1   //K2
#define KEY2_Pin P22_2   //k3
#define KEY3_Pin P22_0   //K4
#define KEY4_Pin P33.12  //k5

#define BtnUp   1    /* 按键弹起 */
#define BtnDown 0    /* 按键按下 */

#include <LQ_GPIO.h>
#include <LQ_TFT18.h>
#include <stdio.h>
#include "new_menu.h"

void Button_Scan(void);
static void Button_GetAllState();
static void resetBtnFlag();
int isBtnN();
int isBtnE();
int isBtnR();


#endif /* SRC_APPSW_TRICORE_USER_BUTTON_H_ */

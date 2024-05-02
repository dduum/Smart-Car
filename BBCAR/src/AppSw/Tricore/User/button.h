/*
 * button.h
 *
 *  Created on: 2024��4��29��
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_BUTTON_H_
#define SRC_APPSW_TRICORE_USER_BUTTON_H_

#define BtnN    0    /* �Ҽ� */
#define BtnE    1    /* ȷ�ϼ� */
#define BtnR    2    /* ���ؼ� */

#define KEY0_Pin P22_0  //������Դ�İ���
#define KEY1_Pin P22_1
#define KEY2_Pin P22_2


#define BtnUp   1    /* �������� */
#define BtnDown 0    /* �������� */

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
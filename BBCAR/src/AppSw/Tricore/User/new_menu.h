/*
 * new_menu.h
 *
 *  Created on: 2024��4��29��
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_NEW_MENU_H_
#define SRC_APPSW_TRICORE_USER_NEW_MENU_H_

#include <LQ_TFT18.h>
#include <LQ_CAMERA.h>
#include <LQ_PID.h>
#include "My_menu.h"

typedef struct Menu
{
    int mode1;    // 0-�������˵���ѡ������Ӧ�����˵�    1��2��3...��������˵�
    int mode2;    // 0-��������˵���ѡ������Ӧ�����˵�  1��2��3...���������˵�
    int mode3;    // 0-���������˵���ѡ������Ӧ�ļ��˵�  1��2��3...�����ļ��˵�
    int mode4;    // ͬ��
}sMenu;

void Menu_Scan(void);
void main_menu(void);
void menu_pid(void);
void menu_ENC(void);
void menu_image(void);
void menu_ServoMotor(void);


#endif /* SRC_APPSW_TRICORE_USER_NEW_MENU_H_ */

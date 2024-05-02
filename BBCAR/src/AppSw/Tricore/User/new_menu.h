/*
 * new_menu.h
 *
 *  Created on: 2024年4月29日
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
    int mode1;    // 0-代表主菜单，选择进入对应二级菜单    1、2、3...代表二级菜单
    int mode2;    // 0-代表二级菜单，选择进入对应三级菜单  1、2、3...代表三级菜单
    int mode3;    // 0-代表三级菜单，选择进入对应四级菜单  1、2、3...代表四级菜单
    int mode4;    // 同理
}sMenu;

void Menu_Scan(void);
void main_menu(void);
void menu_pid(void);
void menu_ENC(void);
void menu_image(void);
void menu_ServoMotor(void);


#endif /* SRC_APPSW_TRICORE_USER_NEW_MENU_H_ */

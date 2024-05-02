/*
 * new_menu.c
 *
 *  Created on: 2024年4月29日
 *      Author: dduu
 */
#include "new_menu.h"

//创建一个菜单

char txt_try[32];
sMenu menu = {0,0,0,0};

extern int chooseBuf;
extern int switch_flag;
extern volatile uint8 Motor_openFlag;
extern volatile uint8 Servo_openFlag;

//放在主循环中扫描
void Menu_Scan(void)
{
    if(switch_flag==1){
        switch_flag=0;
        TFTSPI_CLS(u16BLACK);         // 清屏
    }
    switch(menu.mode1)
    {
        /* 主菜单，选择进入对应二级菜单 */
        //进入主菜单时显示“主菜单”，并播报一遍
        case 0: main_menu(); break;
        /* 二级菜单1 启动电机舵机菜单*/
        case 1:
            switch(menu.mode2)
            {
                /* 二级菜单，选择进入对应三级菜单  */
                    //进入二级菜单时显示“二级菜单1”，并播报一遍
                case 0:menu_ServoMotor();break;
                /* 三级菜单1，进入可运行App1 启动电机舵机*/
                case 1:
                    Motor_openFlag=1;
                    Servo_openFlag=1;
                    TFTSPI_P8X16Str(2,1,(char*)"open is OK",u16WHITE,u16BLACK);
                    break;
                /* 三级菜单2，进入可运行App2 关闭电机舵机*/
                case 2:
                    Motor_openFlag=0;
                    Servo_openFlag=0;
                    TFTSPI_P8X16Str(2,1,(char*)"close is OK",u16WHITE,u16BLACK);
                    break;
            }
            break;
        /* 二级菜单2    各个图像数据*/
        case 2:
            switch(menu.mode2)
            {
                /* 二级菜单，选择进入对应三级菜单  */
                    //进入二级菜单时显示“二级菜单1”，并播报一遍
                case 0:menu_image();break;
                /* 三级菜单1，进入可运行App1 */
                case 1: TFTSPI_Road(0, 0, LCDH, LCDW, (unsigned char *)Image_Use); break;
                /* 三级菜单2，进入可运行App2 */
                case 2:  TFTSPI_BinRoad(0, 0, LCDH, LCDW, (unsigned char *)Bin_Image);break;
            }
            break;
            /* 二级菜单2    PID主菜单*/
        case 3:
            switch(menu.mode2)
            {
                case 0:
                    //PID主菜单
                    menu_pid();
                    break;
                //三级菜单1APP
                case 1:
                    Show_ServoPid();
                    break;
                //三级菜单2APP
                case 2:
                    Show_MotorIncPid1();
                    break;
                //三级菜单3APP
                case 3:
                    Show_MotorIncPid2();
                    break;
            }
            break;
        case 4:
            switch(menu.mode2)
            {
                case 0:
                    //ENC编码器主菜单
                    menu_ENC();
                    break;
                //三级菜单1APP
                case 1:
                    Show_ENC();
                    break;
            }
            break;
    }
}

void main_menu(void)
{
    switch(chooseBuf){
        case 1:
            TFTSPI_P8X16Str(2,0,(char*)"->QIDong!!!",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  My_Image",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"  PID_Value",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,3,(char*)"  ENC_Value",u16WHITE,u16BLACK);
            break;
        case 2:
            TFTSPI_P8X16Str(2,0,(char*)"  QIDong!!!",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"->My_Image",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"  PID_Value",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,3,(char*)"  ENC_Value",u16WHITE,u16BLACK);
            break;
        case 3:
            TFTSPI_P8X16Str(2,0,(char*)"  QIDong!!!",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  My_Image",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"->PID_Value",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,3,(char*)"  ENC_Value",u16WHITE,u16BLACK);
            break;
        case 4:
            TFTSPI_P8X16Str(2,0,(char*)"  QIDong!!!",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  My_Image",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"  PID_Value",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,3,(char*)"->ENC_Value",u16WHITE,u16BLACK);
            break;
    }
}

void menu_ENC(void)
{
    switch(chooseBuf){
        case 1:
            TFTSPI_P8X16Str(2,0,(char*)"->ALLENC",u16WHITE,u16BLACK);
            break;
    }
}

void menu_ServoMotor(void)
{
    switch(chooseBuf){
        case 1:
            TFTSPI_P8X16Str(2,0,(char*)"->open",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  close",u16WHITE,u16BLACK);
            break;
        case 2:
            TFTSPI_P8X16Str(2,0,(char*)"  open",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"->close",u16WHITE,u16BLACK);
            break;
    }
}

void menu_image(void)
{
    switch(chooseBuf){
        case 1:
            TFTSPI_P8X16Str(2,0,(char*)"->No_Handler",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  Do_Handler",u16WHITE,u16BLACK);
            break;
        case 2:
            TFTSPI_P8X16Str(2,0,(char*)"  No_Handler",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"->Do_Handler",u16WHITE,u16BLACK);
            break;
    }
}

void menu_pid(void)
{
    switch(chooseBuf){
        case 1:
            TFTSPI_P8X16Str(2,0,(char*)"->Servo_Loc_PID",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  Motor_Inc_PID1",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"  Motor_Inc_PID2",u16WHITE,u16BLACK);
            break;
        case 2:
            TFTSPI_P8X16Str(2,0,(char*)"  Servo_Loc_PID",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"->Motor_Inc_PID1",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"  Motor_Inc_PID2",u16WHITE,u16BLACK);
            break;
        case 3:
            TFTSPI_P8X16Str(2,0,(char*)"  Servo_Loc_PID",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,1,(char*)"  Motor_Inc_PID1",u16WHITE,u16BLACK);
            TFTSPI_P8X16Str(2,2,(char*)"->Motor_Inc_PID2",u16WHITE,u16BLACK);
            break;
    }
}


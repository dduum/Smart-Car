/*
 * new_menu.c
 *
 *  Created on: 2024��4��29��
 *      Author: dduu
 */
#include "new_menu.h"

//����һ���˵�

char txt_try[32];
sMenu menu = {0,0,0,0};

extern int chooseBuf;
extern int switch_flag;
extern volatile uint8 Motor_openFlag;
extern volatile uint8 Servo_openFlag;

//������ѭ����ɨ��
void Menu_Scan(void)
{
    if(switch_flag==1){
        switch_flag=0;
        TFTSPI_CLS(u16BLACK);         // ����
    }
    switch(menu.mode1)
    {
        /* ���˵���ѡ������Ӧ�����˵� */
        //�������˵�ʱ��ʾ�����˵�����������һ��
        case 0: main_menu(); break;
        /* �����˵�1 �����������˵�*/
        case 1:
            switch(menu.mode2)
            {
                /* �����˵���ѡ������Ӧ�����˵�  */
                    //��������˵�ʱ��ʾ�������˵�1����������һ��
                case 0:menu_ServoMotor();break;
                /* �����˵�1�����������App1 ����������*/
                case 1:
                    Motor_openFlag=1;
                    Servo_openFlag=1;
                    TFTSPI_P8X16Str(2,1,(char*)"open is OK",u16WHITE,u16BLACK);
                    break;
                /* �����˵�2�����������App2 �رյ�����*/
                case 2:
                    Motor_openFlag=0;
                    Servo_openFlag=0;
                    TFTSPI_P8X16Str(2,1,(char*)"close is OK",u16WHITE,u16BLACK);
                    break;
            }
            break;
        /* �����˵�2    ����ͼ������*/
        case 2:
            switch(menu.mode2)
            {
                /* �����˵���ѡ������Ӧ�����˵�  */
                    //��������˵�ʱ��ʾ�������˵�1����������һ��
                case 0:menu_image();break;
                /* �����˵�1�����������App1 */
                case 1: TFTSPI_Road(0, 0, LCDH, LCDW, (unsigned char *)Image_Use); break;
                /* �����˵�2�����������App2 */
                case 2:  TFTSPI_BinRoad(0, 0, LCDH, LCDW, (unsigned char *)Bin_Image);break;
            }
            break;
            /* �����˵�2    PID���˵�*/
        case 3:
            switch(menu.mode2)
            {
                case 0:
                    //PID���˵�
                    menu_pid();
                    break;
                //�����˵�1APP
                case 1:
                    Show_ServoPid();
                    break;
                //�����˵�2APP
                case 2:
                    Show_MotorIncPid1();
                    break;
                //�����˵�3APP
                case 3:
                    Show_MotorIncPid2();
                    break;
            }
            break;
        case 4:
            switch(menu.mode2)
            {
                case 0:
                    //ENC���������˵�
                    menu_ENC();
                    break;
                //�����˵�1APP
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


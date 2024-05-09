/*
 * My_menu.c
 *
 *  Created on: 2024��4��29��
 *      Author: dduu
 */
#include <My_menu.h>

//����һ���˵�
sMenu menu = {0,0,0,0};

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

void Show_ENC(void)
{
    char txt[30];
    TFTSPI_P8X16Str(0, 0, (char *)"ENC:", u16WHITE, u16BLACK);
    sprintf(txt, "LPulse: %4d", LPulse);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "YPulse: %4d", YPulse);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Cur_Speed1: %.1f; ", Current_Speed1);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Cur_Speed2: %.1f; ", Current_Speed2);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
    sprintf(txt, "TarSpeed12: %.1f,%.1f; ", Target_Speed1,Target_Speed2);
    TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Motor_openFlag: %d ", Motor_openFlag);
    TFTSPI_P8X16Str(0, 7, txt, u16WHITE, u16BLACK);
}

void Show_ServoPid(void)
{
    char txt[30];
    sprintf(txt, "Select_PID=%1d",Select_PID);
    TFTSPI_P8X16Str(0, 0, txt, u16WHITE, u16BLACK);
    sprintf(txt, "SP=%.2f",Servo_Loc_PID.kp);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "SI=%.2f",Servo_Loc_PID.ki);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "SD=%.2f",Servo_Loc_PID.kd);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KP_error=%.2f",Servo_Loc_PID.out_p);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KD_error=%.2f ",Servo_Loc_PID.out_d);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Servo_error=%3d",(int)Servo_Loc_error);
    TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Servo_duty=%4d ",Servo_duty);              //1370~1700
    TFTSPI_P8X16Str(0, 7, txt, u16WHITE, u16BLACK);
}

void Show_MotorIncPid1(void)
{
    char txt[30];
    sprintf(txt, "Select_PID=%1d",Select_PID);
    TFTSPI_P8X16Str(0, 0, txt, u16WHITE, u16BLACK);
    sprintf(txt, "MP=%.2f",Motor_Inc_PID1.kp);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "MI=%.2f",Motor_Inc_PID1.ki);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "MD=%.2f",Motor_Inc_PID1.kd);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KP_error=%.2f",Motor_Inc_PID1.out_p);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Motor_duty1: %4d", Motor_duty1);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Motor1_IncPID: %.2f", Motor1_IncPID);
    TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);
}

void Show_MotorIncPid2(void)
{
    char txt[30];
    TFTSPI_P8X16Str(0, 0, (char *)"Motor_Inc_PID2:", u16WHITE, u16BLACK);
    sprintf(txt, "KP=%.2f",Motor_Inc_PID2.kp);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KI=%.2f",Motor_Inc_PID2.ki);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KD=%.2f",Motor_Inc_PID2.kd);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KP_error=%.2f",Motor_Inc_PID2.out_p);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Motor_duty2: %4d", Motor_duty2);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Motor2_IncPID: %.2f", Motor2_IncPID);
    TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);
}


/*
 * My_menu.c
 *
 *  Created on: 2023年12月10日
 *      Author: dduu
 */
#include "My_menu.h"

char txt[32];
uint8 ShowPID_Mode=0; //显示PID模式
uint8 ShowCamera_Mode=0; //显示CAMERA模式
uint8 Key_flag=0;

extern uint8 _sta;
extern volatile sint16 LPulse;                 //左编码器脉冲
extern volatile sint16 YPulse;                 //右编码器脉冲
extern volatile uint8 CrossWay_Flag;          //十字路口标志
extern volatile uint8 Island_Flag;            //环岛标志
extern volatile int Mon_change_Right_Line;     //右单调变化点
extern volatile uint8 Island_State;          //环岛状态数
extern unsigned char Camera_Flag;
extern uint8 Mode;
extern int Servo_duty;
extern volatile int Search_Stop_Line;
extern volatile uint8 Motor_openFlag; //电机启动标志
extern volatile uint8 Servo_openFlag;
extern volatile float Target_Speed1; //左电机目标速度m/s
extern volatile float Target_Speed2; //右电机目标速度m/s
extern volatile short Motor_duty1;
extern volatile short Motor_duty2;
extern pid_param_t Servo_Loc_PID;
extern pid_param_t Motor_Inc_PID1;  //电机1速度环PID
extern pid_param_t Motor_Inc_PID2;  //电机2速度环PID
extern int Servo_Loc_error;  //舵机位置式PID误差
extern float Motor1_IncPID;
extern float Motor2_IncPID;  //电机速度环
extern volatile float Current_Speed1;     //单位m/s
extern volatile float Current_Speed2;
extern volatile int Longest_White_Column_Left[];  //存储左边最长白列的数量和位置
extern volatile int Longest_White_Column_Right[]; //存储右边最长白列的数量和位置
extern volatile int Right_Lost_Time;        //右丢线行数
extern volatile int Left_Lost_Time;         //左丢线行数
extern volatile int Boundry_Start_Left;     //左边第一个非丢线点
extern volatile int Boundry_Start_Right;    //右边第一个非丢线点
extern volatile int Both_Lost_Time;         //两边同时丢线数

extern volatile int Right_Down_Find;          //右下拐点
extern volatile int Left_Down_Find;           //左下拐点
extern volatile int Left_Up_Find;             //左上拐点
extern volatile int Right_Up_Find;            //右上拐点
extern volatile int monotonicity_change_line[2];


int menu_one(void)
{
    TFTSPI_CLS(u16BLACK);
    TFTSPI_P8X16Str(2,0,(char*)"Motor!!!!",u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,1,(char*)"My_Image", u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,2,(char*)"PID_Value",u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,3,(char*)"ADC_Value",u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,4,(char*)"ENC_Value",u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,5,(char*)"MPU_Value",u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,6,(char*)"CAMERA!!!",u16WHITE,u16BLACK);
    TFTSPI_P8X16Str(2,7,(char*)"Camera_Switch",u16WHITE,u16BLACK);

    while(1)
    {
        if(Mode==1)
        {
            Mode=0;
            Key_flag++;
            if(Key_flag>7){Key_flag=7;}
        }
        else if(Mode==2)
        {
            Mode=0;
            Key_flag--;
            if(Key_flag<0){Key_flag=0;}
        }
        else if(Mode==3)
        {
            Mode=0;
            TFTSPI_CLS(u16BLACK);         // 清屏
            return (Key_flag);
        }
        switch(Key_flag)
        {
            case 0:
                TFTSPI_P8X16Str(0,0,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 1:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 2:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 3:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 4:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 5:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 6:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"->",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"  ",u16WHITE,u16BLACK);
                break;
            case 7:
                TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,4,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,5,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,6,(char*)"  ",u16WHITE,u16BLACK);
                TFTSPI_P8X16Str(0,7,(char*)"->",u16WHITE,u16BLACK);
                break;
        }
    }
}

int menu_two(int flag)
{
    if(flag==1)
    {
        while(1)
        {
            TFTSPI_Road(0, 0, LCDH, LCDW, (unsigned char *)Image_Use);
            if(Mode!=0)  //如果有按键按下
            {
                Mode=0;
                return (flag);
            }
        }
    }
    else if(flag==2)
    {
        TFTSPI_CLS(u16BLACK);         // 清屏
        TFTSPI_P8X16Str(2,0,(char*)"Servo_Loc_PID",u16WHITE,u16BLACK);
        TFTSPI_P8X16Str(2,1,(char*)"Motor_Inc_PID1",u16WHITE,u16BLACK);
        TFTSPI_P8X16Str(2,2,(char*)"Motor_Inc_PID2",u16WHITE,u16BLACK);
        TFTSPI_P8X16Str(2,3,(char*)"Motor_Dir_PID",u16WHITE,u16BLACK);
        while(1)
       {
           if(Mode==1)
           {
               Mode=0;
               ShowPID_Mode++;
               if(ShowPID_Mode>3){ShowPID_Mode=3;}
           }
           else if(Mode==2)
           {
               Mode=0;
               ShowPID_Mode--;
               if(ShowPID_Mode<0){ShowPID_Mode=0;}
           }
           else if(Mode==3)
           {
               Mode=0;
               TFTSPI_CLS(u16BLACK);         // 清屏
               return (flag);
           }
           switch(ShowPID_Mode)
           {
               case 0:
                   TFTSPI_P8X16Str(0,0,(char*)"->",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                   break;
               case 1:
                   TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"->",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                   break;
               case 2:
                   TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"->",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                   break;
               case 3:
                   TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"->",u16WHITE,u16BLACK);
                   break;
           }
       }
    }
    else if(flag==6)
    {
        TFTSPI_CLS(u16BLACK);         // 清屏
        TFTSPI_P8X16Str(2,0,(char*)"BaseInfor_One",u16WHITE,u16BLACK);
        TFTSPI_P8X16Str(2,1,(char*)"BaseInfor_Two",u16WHITE,u16BLACK);
        TFTSPI_P8X16Str(2,2,(char*)"Element_Flag",u16WHITE,u16BLACK);
        TFTSPI_P8X16Str(2,3,(char*)"Island_data",u16WHITE,u16BLACK);
        while(1)
       {
           if(Mode==1)
           {
               Mode=0;
               ShowCamera_Mode++;
               if(ShowCamera_Mode>3){ShowCamera_Mode=3;}
           }
           else if(Mode==2)
           {
               Mode=0;
               ShowCamera_Mode--;
               if(ShowCamera_Mode<0){ShowCamera_Mode=0;}
           }
           else if(Mode==3)
           {
               Mode=0;
               TFTSPI_CLS(u16BLACK);         // 清屏
               return (flag);
           }
           switch(ShowCamera_Mode)
           {
               case 0:
                   TFTSPI_P8X16Str(0,0,(char*)"->",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                   break;
               case 1:
                   TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"->",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                   break;
               case 2:
                   TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"->",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"  ",u16WHITE,u16BLACK);
                   break;
               case 3:
                   TFTSPI_P8X16Str(0,0,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,1,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,2,(char*)"  ",u16WHITE,u16BLACK);
                   TFTSPI_P8X16Str(0,3,(char*)"->",u16WHITE,u16BLACK);
                   break;

           }
       }
    }
    else
    {
        return (flag);
    }
}

extern uint16 dlen;
extern uint16 dcnt;

void menu_three(int Key_flag)
{
    while(1)
    {
        if(Mode==1)
        {
            TFTSPI_CLS(u16BLACK);         // 清屏
            ShowPID_Mode=0;
            ShowCamera_Mode=0;
            return;
        }
        switch(Key_flag)
        {
            case 0:
                Motor_openFlag=!Motor_openFlag;
                Servo_openFlag=!Servo_openFlag;
                return;
                break;
            case 1: //Image
                TFTSPI_BinRoad(0, 0, LCDH, LCDW, (unsigned char *)Bin_Image);
                break;
            case 2: //PID
                ShowPID();
                break;
            case 3:  //ADC
                TFTSPI_P8X16Str(0, 0, (char *)"ADC:", u16WHITE, u16BLACK);
                sprintf(txt, "dlen: %4d", dlen);
                TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
                sprintf(txt, "dcnt: %4d", dcnt);
                TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
                sprintf(txt, "SP: %3.1f", Servo_Loc_PID.kp);
                TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
                sprintf(txt, "SI: %3.1f", Servo_Loc_PID.ki);
                TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
                sprintf(txt, "SD: %3.1f", Servo_Loc_PID.kd);
                TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
                sprintf(txt, "_sta: %d", _sta);
                TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);

                break;
            case 4:  //ENC
                Show_ENC();
                break;
            case 5:  //MPU
                TFTSPI_P8X16Str(0, 0, (char *)"MPU:", u16WHITE, u16BLACK);
                break;
            case 6:  //Camera
                ShowCamera();
                break;
            case 7: //Switch
                Camera_Flag=0;
                return;
                break;
            default:
                break;
        }
    }
}

void Show_ENC(void)
{
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

void ShowPID(void)
{
    switch(ShowPID_Mode)
    {
        case 0:
            Show_ServoPid();
            break;
        case 1:
            Show_MotorIncPid1();
            break;
        case 2:
            Show_MotorIncPid2();
            break;
        case 3:
            Show_MotorDirPid();
    }
}

void ShowCamera(void)
{
    switch(ShowCamera_Mode)
    {
        case 0:
            Base_Information_One();
            break;
        case 1:
            Base_Information_Two();
            break;
        case 2:
            Show_CameraElementFlag();
            break;
        case 3:
            Show_Island();
    }
}

void Show_ServoPid(void)
{
    TFTSPI_P8X16Str(0, 0, (char *)"Servo_Loc_PID:", u16WHITE, u16BLACK);
    sprintf(txt, "KP=%.2f",Servo_Loc_PID.kp);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KI=%.2f",Servo_Loc_PID.ki);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KD=%.2f",Servo_Loc_PID.kd);
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
    TFTSPI_P8X16Str(0, 0, (char *)"Motor_Inc_PID1:", u16WHITE, u16BLACK);

    sprintf(txt, "KP=%.2f",Motor_Inc_PID1.kp);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KI=%.2f",Motor_Inc_PID1.ki);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "KD=%.2f",Motor_Inc_PID1.kd);
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

void Show_MotorDirPid(void)
{
    TFTSPI_P8X16Str(0, 0, (char *)"MotorDir_PID:", u16WHITE, u16BLACK);
}

void Base_Information_One(void)
{
    sprintf(txt, "Column_Left_L: %3d", Longest_White_Column_Left[0]);
    TFTSPI_P8X16Str(0, 0 , txt, u16WHITE, u16BLACK);
    sprintf(txt, "Column_Left_C: %3d", Longest_White_Column_Left[1]);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Column_Right_L: %3d", Longest_White_Column_Right[0]);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Column_Right_C: %3d", Longest_White_Column_Right[1]);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Start_Left: %3d", Boundry_Start_Left);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Start_Right: %3d", Boundry_Start_Right);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Stop_Line: %3d", Search_Stop_Line);
    TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);
}

void Base_Information_Two(void)
{
    sprintf(txt, "L_Lost_Time=%3d",Left_Lost_Time);
    TFTSPI_P8X16Str(0, 0, txt, u16WHITE, u16BLACK);
    sprintf(txt, "R_Lost_Time=%3d",Right_Lost_Time);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "B_Lost_Time=%3d",Both_Lost_Time);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);

}

void Show_CameraElementFlag(void)
{
    sprintf(txt, "Cross_Flag=%d",CrossWay_Flag);
    TFTSPI_P8X16Str(0, 0, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Island_Flag=%d",Island_Flag);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
}


void Show_CrossWay(void)
{
    sprintf(txt, "Left_Up=%3d",Left_Up_Find);
    TFTSPI_P8X16Str(0, 0, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Right_Up=%3d",Right_Up_Find);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Left_Down=%3d",Left_Down_Find);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Right_Down=%3d",Right_Down_Find);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);

}

void Show_Island(void)
{
    sprintf(txt, "Island_State=%d",Island_State);
    TFTSPI_P8X16Str(0, 0, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Right_Down=%3d",Right_Down_Find);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Mon_change_Right=%3d",Mon_change_Right_Line);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Mon_change_line=%3d",monotonicity_change_line[0]);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "Mon_change_Row=%3d",monotonicity_change_line[1]);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
}

void Show_PIDALL(void)
{
    TFTSPI_P8X16Str(0, 0, (char *)"PIDALL:", u16WHITE, u16BLACK);
    sprintf(txt, "SP=%4.1f",Servo_Loc_PID.kp);
    TFTSPI_P8X16Str(0, 1, txt, u16WHITE, u16BLACK);
    sprintf(txt, "SI=%4.1f",Servo_Loc_PID.ki);
    TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLACK);
    sprintf(txt, "SD=%4.1f",Servo_Loc_PID.kd);
    TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);
    sprintf(txt, "MP=%4.1f",Motor_Inc_PID1.kp);
    TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLACK);
    sprintf(txt, "MI=%4.1f",Motor_Inc_PID1.ki);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);
    sprintf(txt, "MD=%4.1f",Motor_Inc_PID1.kd);
    TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK);
}


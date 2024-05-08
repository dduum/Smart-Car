/*
 * My_Control_Code.c
 *  Created on: 2024
 *      Author: dduu
*/
#include "My_Control_Code.h"

extern key_t Key[];
extern pid_param_t Servo_Loc_PID;           //
extern pid_param_t Motor_Inc_PID1;          //
extern pid_param_t Motor_Inc_PID2;          //

uint8 cnt=0;
uint8 Mode=0;
char txt_a[30];                         //閿熶茎鎲嬫嫹
float Motor1_IncPID=0;
float Motor2_IncPID=0;                  //
float Motor_DirPId=0;                   //
volatile sint16 Battery;                //
volatile float Current_Speed1=0;        //閿熸枻鎷蜂綅m/s
volatile float Current_Speed2=0;
volatile sint16 LPulse;                 //
volatile sint16 YPulse;                 //
int Servo_duty=Servo_Center_Mid;

void Motor_Control(void)
{
    cnt++;  //配置串口发送中断

    //控制电机同样是5ms
    /* 获取编码器值 */
    LPulse = -ENC_GetCounter(ENC4_InPut_P02_8); // 左电机，小车前进为负值
    YPulse = ENC_GetCounter(ENC2_InPut_P33_7);  // 右电机，小车前进为正值

    Current_Speed1=LPulse/1024.0*9.3258/100.0/0.005;        //编译器旋转一圈，小车移动30/50*4.95*3.14=9.3258cm
    Current_Speed2=YPulse/1024.0*9.3258/100.0/0.005;        //

    //转向环PID
//    if(StraightWay_flag)
//    {
//        Motor_DirPId=(float)10*Servo_Loc_error;
//    }
//    else
//    {
//        Motor_DirPId=(float)0.4*Servo_Loc_error;
//    }
    //没加差速
    Motor_DirPId=0.0;

    if(Motor_openFlag==1)
    {
        //速度环PID
        Motor1_IncPID+=PidIncCtrl(&Motor_Inc_PID1,(float)(Target_Speed1-Current_Speed1));
        Motor2_IncPID+=PidIncCtrl(&Motor_Inc_PID2,(float)(Target_Speed2-Current_Speed2));
        //去除电机死区
//        if(Motor_duty1 > 0 && Motor_duty1 < 800) Motor_duty1 = 800;
//        if(Motor_duty1 < 0 && Motor_duty1 > -800) Motor_duty1 = -800;
//        if(Motor_duty2 > 0 && Motor_duty2 < 800) Motor_duty2 = 800;
//        if(Motor_duty2 < 0 && Motor_duty2 > -800) Motor_duty2 = -800;
    }
    else if(Motor_openFlag==0)
    {
        //速度环PID
        Motor1_IncPID+=PidIncCtrl(&Motor_Inc_PID1,(float)(0-Current_Speed1));
        Motor2_IncPID+=PidIncCtrl(&Motor_Inc_PID2,(float)(0-Current_Speed2));
    }

    //电机限幅
    if(Motor1_IncPID > 2000)Motor1_IncPID = 2000;else if(Motor1_IncPID < -2000)Motor1_IncPID = -2000;
    if(Motor_Inc_PID1.out > 2000)Motor_Inc_PID1.out = 2000;else if(Motor_Inc_PID1.out < -2000)Motor_Inc_PID1.out = -2000;

    if(Motor2_IncPID > 2000)Motor2_IncPID = 2000;else if(Motor2_IncPID < -2000)Motor2_IncPID = -2000;
    if(Motor_Inc_PID2.out > 2000)Motor_Inc_PID2.out = 2000;else if(Motor_Inc_PID2.out < -2000)Motor_Inc_PID2.out = -2000;

    //转向和电机驱动融合并限幅
    Motor_duty1=(int)Motor1_IncPID-(int)Motor_DirPId;
    Motor_duty2=(int)Motor2_IncPID+(int)Motor_DirPId;
    if(Motor_duty1 > 2000)Motor_duty1 = 2000;else if(Motor_duty1 < 0)Motor_duty1 = 0;
    if(Motor_duty2 > 2000)Motor_duty2 = 2000;else if(Motor_duty2 < 0)Motor_duty2 = 0;
    //给电机PWM信号
    MotorCtrl(Motor_duty2,Motor_duty1);

    if(cnt>=10)    //每20ms串口发送duty的值
    {
        cnt=0;
//        sprintf(txt_a, "{Motor_duty12}%d,%d\r\n", Motor_duty1,Motor_duty2);
//        UART_PutStr(UART0, txt_a);
//        sprintf(txt_a, "{Servo_Loc_error}%d\r\n", Servo_Loc_error);
//        UART_PutStr(UART0, txt_a);
//        sprintf(txt_a, "{Motor_DirPId}%.2f\r\n", Motor_DirPId);
//        UART_PutStr(UART0, txt_a);
//        sprintf(txt_a, "{Cur_S1,Tar_S1}%.2f,%.2f\r\n", Current_Speed1,Target_Speed1);
//        UART_PutStr(UART0, txt_a);
//        sprintf(txt_a, "{Cur_S2,Tar_S2}%.2f,%.2f\r\n", Current_Speed2,Target_Speed2);
//        UART_PutStr(UART0, txt_a);
    }
}

void Servo_Control(void)
{
    //控制舵机
    float Servo_LocPid;  //方向环误差PID

    Servo_Loc_error=(int)Err_Sum();

//    if(Servo_Loc_error>=10 && Servo_Loc_error<=-10)
//    {
//        Servo_Loc_PID.kp=40;
//    }
//    else
//    {
//        Servo_Loc_PID.kp=20;
//    }

    Servo_LocPid=PidLocCtrl(&Servo_Loc_PID,(float)Servo_Loc_error);   //使用P小的PID
    //Servo_LocPid=PidLocCtrl(&Servo_Loc_PID,(float)Servo_Loc_error)+EKP*Servo_QZ_ERR;

    Servo_duty=(int)(Servo_Center_Mid + Servo_LocPid);

    if (Servo_duty >= Servo_Left_Max)                  //限制幅值
        Servo_duty = Servo_Left_Max;
    else if (Servo_duty <= Servo_Right_Min)            //限制幅值
        Servo_duty = Servo_Right_Min;

    if(Servo_openFlag==1)
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_duty, 100);  //舵机频率为100HZ，初始值为1.5ms中值
    }
    else
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);  //舵机频率为100HZ，初始值为1.5ms中值
    }


}

void Camera_Control(void)
{
//    if(++LED1_Time == 50)   //10*50 = 500ms
//    {
//        LED1_Time = 0;
//        LED_Ctrl(LED1,RVS);     // LED閿熸枻鎷风儊 鎸囩ず閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鐘舵��
//    }

//        Cross_Detect();
    //    Right_Down_Find=Find_Right_Down_Point(LCDH-1,0);
    //    if(Right_Down_Find!=0)
    //    {
    //        Mon_change_Right_Line=Monotonicity_Change_Right(Right_Down_Find-5,0);
    //    }
    //    else
    //    {
    //        Mon_change_Right_Line=Monotonicity_Change_Right(LCDH-1,0);
    //    }

//        Island_Detect();

        for(int i=LCDH-1;i>=0;i--)
        {
            Middle_Line[i]=(Right_Line[i]+Left_Line[i])/2;
//            Bin_Image[i][Left_Line[i]]=0;
//            Bin_Image[i][Middle_Line[i]]=0;
//            Bin_Image[i][Right_Line[i]]=0;
        }
}

void Key_Control(void)
{
    Key_Check(0,Key,KEY0_Pin);
    Key_Check(1,Key,KEY1_Pin);
    Key_Check(2,Key,KEY2_Pin);

    if(Key[0].keyFlag==1)
    {
        Key[0].keyFlag=0;
        Mode=1;
    }
    else if(Key[1].keyFlag==1)
    {
        Key[1].keyFlag=0;
        Mode=2;
    }
    else if(Key[2].keyFlag==1)
    {
        Key[2].keyFlag=0;
        Mode=3;
    }
}


/*
 * My_Control_Code.c
 *  Created on: 2024锟斤拷4锟斤拷21锟斤拷
 *      Author: dduu
*/
#include "My_Control_Code.h"

extern key_t Key[];
extern pid_param_t Servo_Loc_PID;           //锟斤拷锟轿伙拷锟绞絇ID锟斤拷虾锟斤拷锟斤拷锟斤拷
extern pid_param_t Motor_Inc_PID1;          //锟斤拷锟�1锟劫度伙拷PID
extern pid_param_t Motor_Inc_PID2;          //锟斤拷锟�2锟劫度伙拷PID

uint8 cnt=0;
uint8 Mode=0;
char txt_a[30];                         //锟侥憋拷
float Motor1_IncPID=0;
float Motor2_IncPID=0;                  //锟斤拷锟斤拷俣然锟�
float Motor_DirPId=0;                   //锟斤拷锟阶拷锟�
volatile sint16 Battery;                //锟斤拷氐锟斤拷锟紸DC
volatile float Current_Speed1=0;        //锟斤拷位m/s
volatile float Current_Speed2=0;
volatile sint16 LPulse;                 //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�
volatile sint16 YPulse;                 //锟揭憋拷锟斤拷锟斤拷锟斤拷锟斤拷
int Servo_duty=Servo_Center_Mid;

void Motor_Control(void)
{
    cnt++;  //锟斤拷锟矫达拷锟节凤拷锟斤拷锟叫讹拷

    //5ms
    /* 锟斤拷取锟斤拷锟斤拷锟斤拷值 */
    LPulse = -ENC_GetCounter(ENC4_InPut_P02_8); // 锟斤拷锟斤拷锟斤拷小锟斤拷前锟斤拷为锟斤拷值
    YPulse = ENC_GetCounter(ENC2_InPut_P33_7);  // 锟揭碉拷锟斤拷锟叫★拷锟角帮拷锟轿拷锟街�

    Current_Speed1=LPulse/1024.0*12.0576/100.0/0.01/1.357;        //锟斤拷锟斤拷锟斤拷锟斤拷转一圈锟斤拷小锟斤拷锟狡讹拷30/50*4.95*3.14=9.3258cm
    Current_Speed2=YPulse/1024.0*12.0576/100.0/0.01/1.357;        //

    //转锟斤拷PID
//    if(StraightWay_flag)
//    {
//        Motor_DirPId=(float)10*Servo_Loc_error;
//    }
//    else
//    {
//        Motor_DirPId=(float)0.4*Servo_Loc_error;
//    }

    //锟斤拷锟斤拷
    Motor_DirPId=0.0;

    if(Motor_openFlag==1)
    {
        //锟劫度伙拷PID
        Target_Speed1=1;
        Target_Speed2=1;

        Motor1_IncPID+=PidIncCtrl(&Motor_Inc_PID1,(float)(Target_Speed1-Current_Speed1));
        Motor2_IncPID+=PidIncCtrl(&Motor_Inc_PID2,(float)(Target_Speed2-Current_Speed2));
        //去锟斤拷锟斤拷锟斤拷锟斤拷锟�
//        if(Motor_duty1 > 0 && Motor_duty1 < 800) Motor_duty1 = 800;
//        if(Motor_duty1 < 0 && Motor _duty1 > -800) Motor_duty1 = -800;
//        if(Motor_duty2 > 0 && Motor_duty2 < 800) Motor_duty2 = 800;
//        if(Motor_duty2 < 0 && Motor_duty2 > -800) Motor_duty2 = -800;
    }
    else if(Motor_openFlag==0)
    {
        //锟劫度伙拷PID
        Target_Speed1=0;
        Target_Speed2=0;
        Motor1_IncPID+=PidIncCtrl(&Motor_Inc_PID1,(float)(Target_Speed1-Current_Speed1));
        Motor2_IncPID+=PidIncCtrl(&Motor_Inc_PID2,(float)(Target_Speed2-Current_Speed2));
    }

    //锟斤拷锟斤拷薹锟�
    if(Motor1_IncPID > 2000)Motor1_IncPID = 2000;else if(Motor1_IncPID < -2000)Motor1_IncPID = -2000;
    if(Motor_Inc_PID1.out > 2000)Motor_Inc_PID1.out = 2000;else if(Motor_Inc_PID1.out < -2000)Motor_Inc_PID1.out = -2000;

    if(Motor2_IncPID > 2000)Motor2_IncPID = 2000;else if(Motor2_IncPID < -2000)Motor2_IncPID = -2000;
    if(Motor_Inc_PID2.out > 2000)Motor_Inc_PID2.out = 2000;else if(Motor_Inc_PID2.out < -2000)Motor_Inc_PID2.out = -2000;

    //转锟斤拷偷锟斤拷锟斤拷锟斤拷锟节合诧拷锟睫凤拷
    Motor_duty1=(int)Motor1_IncPID-(int)Motor_DirPId;
    Motor_duty2=(int)Motor2_IncPID+(int)Motor_DirPId;
    if(Motor_duty1 > 2000)Motor_duty1 = 2000;else if(Motor_duty1 < 0)Motor_duty1 = 0;
    if(Motor_duty2 > 2000)Motor_duty2 = 2000;else if(Motor_duty2 < 0)Motor_duty2 = 0;
    //锟斤拷锟斤拷锟絇WM锟脚猴拷
    MotorCtrl(Motor_duty2,Motor_duty1);

    if(cnt>=10)    //每20ms锟斤拷锟节凤拷锟斤拷duty锟斤拷值
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
    //锟斤拷锟狡讹拷锟�
    float Servo_LocPid;  //锟斤拷锟斤拷锟斤拷锟絇ID

    Servo_Loc_error=(int)Err_Sum();

//    if(Servo_Loc_error>=10 && Servo_Loc_error<=-10)
//    {
//        Servo_Loc_PID.kp=40;
//    }
//    else
//    {
//        Servo_Loc_PID.kp=20;
//    }

    Servo_LocPid=PidLocCtrl(&Servo_Loc_PID,(float)Servo_Loc_error);   //使锟斤拷P小锟斤拷PID
//    Servo_LocPid=PidLocCtrl(&Servo_Loc_PID,(float)Servo_Loc_error)+EKP*Servo_QZ_ERR;

    Servo_duty=(int)(Servo_Center_Mid + Servo_LocPid);

    if (Servo_duty >= Servo_Left_Max)                  //锟斤拷锟狡凤拷值
        Servo_duty = Servo_Left_Max;
    else if (Servo_duty <= Servo_Right_Min)            //锟斤拷锟狡凤拷值
        Servo_duty = Servo_Right_Min;

    if(Servo_openFlag==1)
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_duty, 100);  //锟斤拷锟狡碉拷锟轿�100HZ锟斤拷锟斤拷始值为1.5ms锟斤拷值
    }
    else
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);  //锟斤拷锟狡碉拷锟轿�100HZ锟斤拷锟斤拷始值为1.5ms锟斤拷值
    }
}

void Camera_Control(void)
{
//    if(++LED1_Time == 50)   //10*50 = 500ms
//    {
//        LED1_Time = 0;
//        LED_Ctrl(LED1,RVS);     // LED锟斤拷烁 指示锟斤拷锟斤拷锟斤拷锟斤拷状态
//    }

        Cross_Detect();
    //    Right_Down_Find=Find_Right_Down_Point(LCDH-1,0);
    //    if(Right_Down_Find!=0)
    //    {
    //        Mon_change_Right_Line=Monotonicity_Change_Right(Right_Down_Find-5,0);
    //    }
    //    else
    //    {
    //        Mon_change_Right_Line=Monotonicity_Change_Right(LCDH-1,0);
    //    }

        Island_Detect();

        for(int i=LCDH-1;i>=0;i--)
        {
            Middle_Line[i]=(Right_Line[i]+Left_Line[i])/2;
            Bin_Image[i][Left_Line[i]]=0;
            Bin_Image[i][Middle_Line[i]]=0;
            Bin_Image[i][Right_Line[i]]=0;
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


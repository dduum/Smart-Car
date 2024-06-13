/*
 * My_Control_Code.c
 *  Created on: 2024
 *      Author: dduu
*/
#include "My_Control_Code.h"

uint8 Key_Value=0;
uint8 Select_SorM=0;
uint8 Select_PID=0;
float Motor_IncPID=0;
float Motor_IncPID1=0;
float Motor_IncPID2=0;
float Current_Speed1=0;               //速度单位m/s
float Current_Speed2=0;
float Current_Speed=0;
long int Current_Tmp_Speed1=0;        //速度单位m/s
long int Current_Tmp_Speed2=0;        //速度单位m/s
int Servo_duty=Servo_Center_Mid;
uint8 Motor_openFlag=0;         //电机启动标志
uint8 Servo_openFlag=0;         //舵机启动标志
short Motor_duty1 = 0;
short Motor_duty2 = 0;
uint8 Look_Line=95;
int Target_Speed=0; //目标速度m/s,100即为1m/s


int Last_err=0;//上一次图像误差
int Last_last_err=0;//上上一次图像误差
float Image_kp=5;
float Image_kd=10;
short Dir_out;
float K_Dir=0;

int Test_err;
int Test_err_d;

volatile sint16 LPulse = 0;          // 速度全局变量
volatile sint16 YPulse = 0;          // 速度全局变量

void Motor_Control(void)
{

    //控制电机是100ms
    LPulse=LPulse_Tmp;
    YPulse=YPulse_Tmp;   //ECPULSE1的值20ms读的，比较小，在100ms中断里面需要*5

    LPulse_Tmp=0;
    YPulse_Tmp=0;        //清空计数五次的值

    //mini车 YPulse/1024.0*30/58*4.95*3.14(cm)/100(m)/0.1(t:ms)  单位m/s  在乘100扩大100倍，相当于Target=100即为1m/s  0.0911
    Current_Speed1=LPulse*7.8511/100;
    Current_Speed2=YPulse*7.8511/100;
//    Current_Speed=(Current_Speed1+Current_Speed2)/2.0;

//    //C车    YPulse/1024.0*30/50*64(mm)/1000(m)/0.1    直径64mm
//    Current_Speed1=LPulse*3.75/100;
//    Current_Speed2=YPulse*3.75/100;
//
//    Low_Pass_Filter((int)ECPULSE1*0.87, &Current_Speed1, &Current_Tmp_Speed1);
//    Low_Pass_Filter((int)ECPULSE2*0.87, &Current_Speed2, &Current_Tmp_Speed2);  //滤波函数

    //两个速度环PID分别控制两个电机
    if(Motor_openFlag)
    {
        Motor_IncPID1=PidIncCtrl(&Motor_Inc_PID1,(float)(Target_Speed - Current_Speed1));
        Motor_IncPID2=PidIncCtrl(&Motor_Inc_PID2,(float)(Target_Speed - Current_Speed2));
    }

    //电机限幅
    if(Motor_IncPID1 > 4000)Motor_IncPID1 = 4000;else if(Motor_IncPID1 < 0)Motor_IncPID1 = 0;
    if(Motor_Inc_PID1.out > 4000)Motor_Inc_PID1.out = 4000;else if(Motor_Inc_PID1.out < 0)Motor_Inc_PID1.out = 0;

    if(Motor_IncPID2 > 4000)Motor_IncPID2 = 4000;else if(Motor_IncPID2 < 0)Motor_IncPID2 = 0;
    if(Motor_Inc_PID2.out > 4000)Motor_Inc_PID2.out = 4000;else if(Motor_Inc_PID2.out < 0)Motor_Inc_PID2.out = 0;

    //一个速度PID同时控制两个电机
//    if(Motor_openFlag)
//    {
//        Motor_IncPID=PidIncCtrl(&Motor_Inc_PID,(float)(Target_Speed - Current_Speed));
//    }
//
//    //电机限幅
//    if(Motor_IncPID > 6000)Motor_IncPID = 6000;else if(Motor_IncPID < -6000)Motor_IncPID = -6000;
//    if(Motor_Inc_PID.out > 6000)Motor_Inc_PID.out = 6000;else if(Motor_Inc_PID.out < -6000)Motor_Inc_PID.out = -6000;

}

float Tmp_FuzzyOut; //该变量没用，只是为了在串口中观看变量值

void Servo_Control_Fuzzy(void)
{
    //控制舵机
    float Fuzzy_out;

    int err=0;
    int err_d=0;
    float e_max=30;
    float e_min=-30;
    float ec_max=4;
    float ec_min=-4;
    float kp_max =Image_kp;
    float kp_min =-Image_kp;
    float ki_max = 0;
    float ki_min = 0;
    float kd_max = Image_kd;
    float kd_min = -Image_kd;

    err=Servo_Loc_error;
    Test_err=err;
    if(err>=e_max)
        err=e_max;
    else if(err<=e_min)
        err=e_min;

    err_d=err-Last_err;
    Test_err_d=err_d;

    if(err_d>=ec_max)
        err=ec_max;
    else if(err_d<=ec_min)
        err=ec_min;

    //模糊pid处理
    Fuzzy_out=Fuzzy_Controller(&Fpid1,e_max,e_min,ec_max,ec_min,kp_max,kp_min,(float)err,(float)err_d,ki_max,ki_min,kd_max,kd_min,(float)Last_err,(float)Last_last_err,0);

    Servo_duty=(int)(Servo_Center_Mid + Fuzzy_out);

    if (Servo_duty >= Servo_Left_Max)                  //限制幅值
        Servo_duty = Servo_Left_Max;
    else if (Servo_duty <= Servo_Right_Min)            //限制幅值
        Servo_duty = Servo_Right_Min;

    if(Servo_openFlag==1)
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_duty, 100);  //舵机频率为100HZ，初始值为1.5ms中值
//        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);
    }
    else
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);  //舵机频率为100HZ，初始值为1.5ms中值
    }

    Last_last_err=Last_err;
    Last_err=Servo_Loc_error;

    //当一副图像到来时,如果需要差速,在方向环中控制会更加灵活
    //速度控制部分
    //差速
    Tmp_FuzzyOut=Fuzzy_out;  //该变量没用，只是为了在串口中观看变量值
    Dir_out=(int)K_Dir*Fuzzy_out;
//    Dir_out=0;

    //两个速度PID同时控制两个电机
    //转向和电机驱动融合并限幅
    Motor_duty1=(int)(Motor_IncPID1-Dir_out);           //*0.94
    Motor_duty2=(int)(Motor_IncPID2+Dir_out);           //*1.06
    if(Motor_duty1 > 4000)Motor_duty1 = 4000;else if(Motor_duty1 < 0)Motor_duty1 = 0;
    if(Motor_duty2 > 4000)Motor_duty2 = 4000;else if(Motor_duty2 < 0)Motor_duty2 = 0;

    //给电机PWM信号
    if(Motor_openFlag==1)
    {
        MotorCtrl(Motor_duty2,Motor_duty1);  //该函数第一个形参是右轮M2，第二个形参是左轮M1
    }
    else
    {
        Motor_Inc_PID1.out=0;
        Motor_Inc_PID1.last_derivative=0;
        Motor_Inc_PID1.last_error=0;
        Motor_Inc_PID2.out=0;
        Motor_Inc_PID2.last_derivative=0;
        Motor_Inc_PID2.last_error=0;
        Motor_IncPID1=0;
        Motor_IncPID2=0;
        Motor_duty2=0;
        Motor_duty1=0;
//            Current_Tmp_Speed1=0;  //低通滤波积分项清零
//            Current_Tmp_Speed2=0;
        MotorCtrl(0,0);
    }

    //一个速度PID同时控制两个电机
//    Motor_duty1=(int)(Motor_IncPID*0.8634-Dir_out);           //大于1.8m/s:0.91758  小于1.8m/s:0.8634
//    Motor_duty2=(int)(Motor_IncPID*1.20244+Dir_out);          //大于1.8m/s:1.12656  小于1.8m/s:1.20244
//    if(Motor_duty1 > 6000)Motor_duty1 = 6000;else if(Motor_duty1 < -6000)Motor_duty1 = -6000;
//    if(Motor_duty2 > 6000)Motor_duty2 = 6000;else if(Motor_duty2 < -6000)Motor_duty2 = -6000;
//
//    //给电机PWM信号
//    if(Motor_openFlag==1)
//    {
//        MotorCtrl(Motor_duty2,Motor_duty1);  //该函数第一个形参是右轮M2，第二个形参是左轮M1
//    }
//    else
//    {
//        Motor_Inc_PID.out=0;
//        Motor_Inc_PID.last_derivative=0;
//        Motor_Inc_PID.last_error=0;
//        Motor_IncPID=0;
//        Motor_duty2=0;
//        Motor_duty1=0;
////            Current_Tmp_Speed1=0;  //低通滤波积分项清零
////            Current_Tmp_Speed2=0;
//        MotorCtrl(0,0);
//    }
}

void Servo_Control_PD(void)
{
    //控制舵机

//    Servo_LocPid=PidLocCtrl(&Servo_Loc_PID,(float)Servo_Loc_error);   //使用P小的PID
    //采取二次项的方式
    Servo_PidLocCtrl(&Servo_Loc_PID,(float)Servo_Loc_error);

    Servo_duty=(int)(Servo_Center_Mid + Servo_Loc_PID.out);

    //舵机限幅
    if (Servo_duty >= Servo_Left_Max)
        Servo_duty = Servo_Left_Max;
    else if (Servo_duty <= Servo_Right_Min)
        Servo_duty = Servo_Right_Min;

    if(Servo_openFlag==1)
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_duty, 100);  //舵机频率为100HZ，初始值为1.5ms中值
//        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);
    }
    else
    {
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);  //舵机频率为100HZ，初始值为1.5ms中值
    }

    Last_last_err=Last_err;
    Last_err=Servo_Loc_error;

    //当一副图像到来时,如果需要差速,在方向环中控制会更加灵活
    //速度控制部分

    //转向和电机驱动融合并限幅
    Motor_duty1=(int)(Motor_IncPID1);  //*0.94
    Motor_duty2=(int)(Motor_IncPID2);  //*1.06
    if(Motor_duty1 > 6000)Motor_duty1 = 6000;else if(Motor_duty1 < -6000)Motor_duty1 = -6000;
    if(Motor_duty2 > 6000)Motor_duty2 = 6000;else if(Motor_duty2 < -6000)Motor_duty2 = -6000;

    //给电机PWM信号
    if(Motor_openFlag==1)
    {
        MotorCtrl(Motor_duty2,Motor_duty1);  //该函数第一个形参是右轮M2，第二个形参是左轮M1
    }
    else
    {
        Motor_Inc_PID1.out=0;
        Motor_Inc_PID1.last_derivative=0;
        Motor_Inc_PID1.last_error=0;
        Motor_Inc_PID2.out=0;
        Motor_Inc_PID2.last_derivative=0;
        Motor_Inc_PID2.last_error=0;
//            Current_Tmp_Speed1=0;  //低通滤波积分项清零
//            Current_Tmp_Speed2=0;
        MotorCtrl(0,0);
    }
}


int change_count=0;//大幅度变化次数

int max_pix=0;
int min_pix=0;


void Key_Control(void)
{
    Key_Check(0,Key,KEY0_Pin);
    Key_Check(1,Key,KEY1_Pin);
    Key_Check(2,Key,KEY2_Pin);
    Key_Check(3,Key,KEY3_Pin);
    Key_Check(4,Key,KEY4_Pin);

    if(Key[0].keyFlag==1)
    {
        Key[0].keyFlag=0;
        Key_Value=1;
    }
    else if(Key[1].keyFlag==1)
    {
        Key[1].keyFlag=0;
        Key_Value=2;
    }
    else if(Key[2].keyFlag==1)
    {
        Key[2].keyFlag=0;
        Key_Value=3;
    }
    else if(Key[3].keyFlag==1)
    {
        Key[3].keyFlag=0;
        Key_Value=4;
    }
    else if(Key[4].keyFlag==1)
    {
        Key[4].keyFlag=0;
        Key_Value=5;
    }
}

void Modify_PID(void)
{
    if(Key_Value==1)
    {
        Key_Value=0;
        data_change_flag=1; //修改了参数，需要写进E2PROM
        if(Select_SorM==0)
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Target_Speed+=20;
                    break;
                case 1:  //I
                    Look_Line++;
                    E2PROM_Write_PID();
                    break;
                case 2:
                    K_Dir+=0.5;
                    break;
            }
            if(Target_Speed>=400)
                Target_Speed=400;
        }
        else if(Select_SorM==1)  //选择ServoPID
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Servo_Loc_PID.kp+=0.1;
                    break;
                case 1:  //I
                    Servo_Loc_PID.kp2+=0.01;
                    break;
                case 2:  //D
                    Servo_Loc_PID.kd+=1;
                    break;
            }
        }
        else if(Select_SorM==2) //选择ServoFuzzy
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Image_kp+=1;
                    break;
                case 1:  //I
                    Image_kd+=1;
                    break;
                case 2:  //D

                    break;
            }
        }
        else if(Select_SorM==3) //选择Motor1
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Motor_Inc_PID1.kp+=0.01;
//                    Motor_Inc_PID.kp+=0.01;
                    break;
                case 1:  //I
                    Motor_Inc_PID1.ki+=0.01;
//                    Motor_Inc_PID.ki+=0.01;
                    break;
                case 2:  //D
                    Motor_Inc_PID1.kd+=0.1;
//                    Motor_Inc_PID.kd+=0.1;
                    break;
            }
        }
        else if(Select_SorM==4) //选择Motor2
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Motor_Inc_PID2.kp+=0.01;
                    break;
                case 1:  //I
                    Motor_Inc_PID2.ki+=0.01;
                    break;
                case 2:  //D
                    Motor_Inc_PID2.kd+=0.1;
                    break;
            }
        }
    }
    else if(Key_Value==2)
    {
        Key_Value=0;
        data_change_flag=1;
        if(Select_SorM==0)
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Target_Speed-=20;
                    break;
                case 1:  //I
                    Look_Line--;
                    E2PROM_Write_PID();
                    break;
                case 2:
                    K_Dir-=0.5;
                    break;
            }
            if(Target_Speed<=0)
                Target_Speed=0;
        }
        else if(Select_SorM==1)  //选择ServoPID
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Servo_Loc_PID.kp-=0.1;
                    break;
                case 1:  //I
                    Servo_Loc_PID.kp2-=0.01;
                    break;
                case 2:  //D
                    Servo_Loc_PID.kd-=1;
                    break;
            }
        }
        else if(Select_SorM==2)  //选择ServoFuzzy
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Image_kp-=1;
                    break;
                case 1:  //I
                    Image_kd-=1;
                    break;
                case 2:  //D

                    break;
            }
        }
        else if(Select_SorM==3) //选择Motor1
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Motor_Inc_PID1.kp-=0.01;
//                    Motor_Inc_PID.kp-=0.01;
                    break;
                case 1:  //I
                    Motor_Inc_PID1.ki-=0.01;
//                    Motor_Inc_PID.ki-=0.01;
                    break;
                case 2:  //D
                    Motor_Inc_PID1.kd-=0.1;
//                    Motor_Inc_PID.kd-=0.1;
                    break;
            }
        }
        else if(Select_SorM==4) //选择Motor2
        {
            switch(Select_PID)
            {
                case 0:  //P
                    Motor_Inc_PID2.kp-=0.01;
                    break;
                case 1:  //I
                    Motor_Inc_PID2.ki-=0.01;
                    break;
                case 2:  //D
                    Motor_Inc_PID2.kd-=0.1;
                    break;
            }
        }
    }
    else if(Key_Value==3)  //选择调P还是I还是D
    {
        Key_Value=0;
        Select_PID++;
        Select_PID%=3;
    }
    else if(Key_Value==4)  //选择调Servo还是Motor
    {
        Key_Value=0;
        Select_PID=0;
        switch_flag=1; //页面更新标志
        Select_SorM++;
        Select_SorM%=5;
    }

    if(switch_flag==1){switch_flag=0;TFTSPI_CLS(u16BLACK);}  //更新页面

    if(Select_SorM==0){Show_Motor();}
    else if(Select_SorM==1){Show_ServoPid();}
    else if(Select_SorM==2){Show_ServoFuzzy();}
    else if(Select_SorM==3){Show_MotorIncPid1();}
    else if(Select_SorM==4){Show_MotorIncPid2();}

}


int Low_Pass_Filter(int encinput,int* Feedback_enc,long int* Feedback_enc_tmp)
{
    int Feedback_enc_Now = 0;
    int tmp = 5;
    int tmp2=tmp*0.5;
    int tmp7;
    Feedback_enc_Now=encinput;                     //编码器当前值
    *Feedback_enc_tmp+=Feedback_enc_Now- *Feedback_enc; //编码器读数差求积
    Feedback_enc_Now=*Feedback_enc_tmp/tmp;                 //取1/20使编码器数值平滑
    tmp7=*Feedback_enc_tmp%tmp;
    if(tmp7>=tmp2)  *Feedback_enc = Feedback_enc_Now + 1;                  //速度值四舍五入
    if(tmp7<=-tmp2) *Feedback_enc = Feedback_enc_Now - 1;
    return *Feedback_enc;                                 //反馈滤波后的速度
}


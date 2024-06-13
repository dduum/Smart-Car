/*
 * Element_handle.c
 *
 *  Created on: 2024年6月3日
 *      Author: dduu
 */
#include <Element_handle.h>

Image_element Element1;
Image_Identify Identify1;
Pulse_Param_t ALLPULSE;
float Angle_in;//进圆环时的角度
float Angle_delta;//角度变化值

/*************************************************************************
*  函数名称：void Image_IdentifyProcess(Image_Identify * Ide)
*  功能说明:   元素识别
*  函数返回：无
*  修改时间：2023年6月10日
*  备    注：
*************************************************************************/
void Image_IdentifyProcess(Image_Identify * Ide)
{
    //未加电磁，注释掉所有元素
    if(Ide->All_Identify==1)//全元素识别
    {
        Image_CrossProcess(&Element1);//十字处理
        Image_LeftCircleProcess(&Element1);//左圆环处理
        Image_RightCircleProcess(&Element1);//右圆环处理
        My_ObstructionProcess(&Element1);//路障处理
        Image_ZebraProcess(&Element1);//斑马线处理
    }
    else if(Ide->Circle_left_Identify==1)
    {
        Image_LeftCircleProcess(&Element1);//左圆环处理
    }
    else if(Ide->Circle_Right_Identify==1)
    {
        Image_RightCircleProcess(&Element1);//右圆环处理
    }
    else if(Ide->Obstruction_Identify==1)
    {
        My_ObstructionProcess(&Element1);//路障处理
    }
    else if(Ide->Zebra_Identify==1)
    {
        Image_ZebraProcess(&Element1);//斑马线处理
    }
}

/*************************************************************************
*  函数名称：void Image_CrossProcess(Image_element* Ele)
*  参数说明：
*  功能说明：十字处理
*  函数返回：无
*  修改时间：2023年6月3日
*  备    注：
*************************************************************************/
void Image_CrossProcess(Image_element* Ele)
{


}


/*************************************************************************
*  函数名称：void Image_LeftCircleProcess(Image_element* Ele)
*  参数说明: 圆环处理函数
*  功能说明：
*  函数返回：无
*  修改时间：2023年5月27日
*  备    注：
*************************************************************************/
void Image_LeftCircleProcess(Image_element* Ele)
{
    if(Ele->Circle_left==0)
    {
        if(1)
        {
            Ele->Circle_left=1;//识别成功，补线
            My_PulseKey(&ALLPULSE, 1, 1);//开
        }

    }
    else if(Ele->Circle_left==1)//圆环状态1先用电磁循迹
    {
        if(1)
        {
            My_PulseClean(&ALLPULSE, 1);
            My_PulseKey(&ALLPULSE, 1, 0);//关
            Ele->Circle_left=0;
        }

        if(ALLPULSE.Circle_Left_Pulse>200)
        {
            if(1)
            {
                My_PulseClean(&ALLPULSE, 1);
                Ele->Circle_left=2;
            }

        }

    }
    else if (Ele->Circle_left==2) {
        if(ALLPULSE.Circle_Left_Pulse>200)
        {
            if(1)
            {
                My_PulseClean(&ALLPULSE, 2);
                Ele->Circle_left=3;
                //记录此时陀螺仪角度

            }

        }

    }
    else if (Ele->Circle_left==3) {

        if(ALLPULSE.Circle_Left_Pulse>1200)
        {
            My_PulseClean(&ALLPULSE, 2);
              Ele->Circle_left=4;
        }
    }
    else if(Ele->Circle_left==4)//改成陀螺仪判断出环岛
    {
        if(ALLPULSE.Circle_Left_Pulse>3000)
        {
//            if(Angle>160)
//            {
//                My_PulseClean(&ALLPULSE, 2);
//                Ele->Circle_left=5;
//                Beep_On;
//            }
//            if(Left_num>120 && Right_num>120)//边线正常
            if(1)
            {
//                    if(ALLPULSE.Circle_Left_Pulse>4600) Big_circle=1;
//                    else Big_circle=0;
                My_PulseClean(&ALLPULSE, 2);
                Ele->Circle_left=5;
            }

        }

    }
    else if(Ele->Circle_left==5)
    {
            /*if(Angle>250)//进入状态六*/
            if(1)
            {
                My_PulseClean(&ALLPULSE, 2);
                Ele->Circle_left=6;
                Identify1.Circle_left_Identify=0;
            }

    }

    if(Ele->Circle_left!=4 && ALLPULSE.Circle_Left_Pulse>2500)
    {
        My_PulseKey(&ALLPULSE, 2, 0);//关
        My_PulseClean(&ALLPULSE, 2);
        Ele->Circle_left=0;
        Identify1.Circle_left_Identify=0;
    }
    else if(Ele->Circle_right==4 && ALLPULSE.Circle_Right_Pulse>8000){
          My_PulseKey(&ALLPULSE, 2, 0);//关
          My_PulseClean(&ALLPULSE, 2);
          Ele->Circle_left=0;
          //Angle=0;
          Identify1.Circle_left_Identify=0;
    }
}

/*************************************************************************
*  函数名称：void Image_RightCircleProcess(Image_element* Ele)
*  参数说明: 圆环处理函数
*  功能说明：
*  函数返回：无
*  修改时间：2023年6月10日
*  备    注：  此处入圆环第一步判断与十字误判率高，需要下一步区分
*************************************************************************/
void Image_RightCircleProcess(Image_element* Ele)
{

}

/*************************************************************************
*  函数名称：void My_ObstructionProcess(Image_element* Ele)
*  参数说明：
*  功能说明：路障处理
*  函数返回：无
*  修改时间：2023年6月3日
*  备    注：
*************************************************************************/
void My_ObstructionProcess(Image_element* Ele)
{

}

/*************************************************************************
*  函数名称：void Image_ZebraProcess(Image_element* Ele)
*  参数说明: 斑马线处理函数
*  功能说明：
*  函数返回：无
*  修改时间：2023年7月11日
*  备    注：
*************************************************************************/
void Image_ZebraProcess(Image_element* Ele)
{
    for(int j=100;j>90;j--)
    {
        int change_cnt=0;
        for(int i=40;i<LCDW-40;i++)
        {
            if(Image_Use[j][i]>max_pix)
            {
                max_pix=Image_Use[j][i];
            }
            if(Image_Use[j][i]<min_pix)
            {
                min_pix=Image_Use[j][i];
            }
            if(Image_Use[j][i]-Image_Use[j][i+1]>=80 || Image_Use[j][i]-Image_Use[j][i+1]<=-80)
            {
                change_cnt++;
            }
        }
        change_count=change_cnt;

        if(change_cnt>=5)  //认为是车库
        {
            Ele->Zebra=1;
            break;
        }
    }

    if(Ele->Zebra==1)
    {
        Ele->Zebra=0;
        Motor_openFlag=0;
        Servo_openFlag=0;
        MotorCtrl(0,0);
        ATOM_PWM_InitConfig(ATOMSERVO1, Servo_Center_Mid, 100);
    }
}

void Set_NULLflag(void)
{
    Element1.Zebra=0;
    Element1.Circle_left=0;
    Element1.Circle_right=0;
    Element1.Crossroad_flag=0;
    Element1.Curve_flag=0;
    Element1.Rampway_flag=0;
    Element1.Straightaway_flag=0;
}


/*************************************************************************
*  函数名称：void Calcu_Pulse(void)
*  参数说明：
*  状态：
*  功能说明：计算全元素脉冲
*  函数返回：无
*  修改时间：2023年5月30日
*  备    注：
*************************************************************************/
void Calcu_Pulse(void)
{
    //100Pulse大约为0.78cm
    for(int i=0;i<6;i++)
        My_PulseCount(&ALLPULSE,i);//计数器计数
}


/*************************************************************************
*  函数名称：void My_PulseCount(Pulse_Param_t * PULSE,int element)
*  参数说明：元素：0十字;1左圆环;2右圆环;3路障;4弯道;5斑马线
*  状态：开或关
*  功能说明：脉冲计数器
*  函数返回：无
*  修改时间：2023年5月30日
*  备    注：
*************************************************************************/
void My_PulseCount(Pulse_Param_t * PULSE,int element)
{
    if(element==0)//十字
    {
        if(PULSE->Cross_Pulse_Key==1)
        {
            PULSE->Cross_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Cross_Pulse=(PULSE->Cross__Pulse_Last*9+PULSE->Cross_Pulse)/10;//滤波得到总计数
            PULSE->Cross__Pulse_Last=PULSE->Cross_Pulse;//记录上一级的值
        }
        else {
            PULSE->Cross_Pulse=0;
            PULSE->Cross__Pulse_Last=0;
        }
    }
    else if(element==1)//左圆环
    {
        if(PULSE->Circle_Left_Pulse_Key==1)
        {
            PULSE->Circle_Left_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Circle_Left_Pulse=(PULSE->Circle_Left_Pulse_Last*9 + PULSE->Circle_Left_Pulse)/10;//滤波得到总计数
            PULSE->Circle_Left_Pulse_Last=PULSE->Circle_Left_Pulse;
        }
        else {
            PULSE->Circle_Left_Pulse=0;
            PULSE->Circle_Left_Pulse_Last=0;
        }
    }
    else if(element==2)//右圆环
    {
        if(PULSE->Circle_Right_Pulse_Key==1)
        {
            PULSE->Circle_Right_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Circle_Right_Pulse=(PULSE->Circle_Right_Pulse_Last*9 + PULSE->Circle_Right_Pulse)/10;//滤波得到总计数
            PULSE->Circle_Right_Pulse_Last=PULSE->Circle_Right_Pulse;
        }
        else {
            PULSE->Circle_Right_Pulse=0;
            PULSE->Circle_Right_Pulse_Last=0;
        }
    }
    else if(element==3)//路障
    {
        if(PULSE->Obstruction_Pulse_Key==1)
        {
            PULSE->Obstruction_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Obstruction_Pulse=(PULSE->Obstruction_Pulse_Last*9 + PULSE->Obstruction_Pulse)/10;//滤波得到总计数
            PULSE->Obstruction_Pulse_Last=PULSE->Obstruction_Pulse;
        }
        else {
            PULSE->Obstruction_Pulse=0;
            PULSE->Obstruction_Pulse_Last=0;
        }
    }
    else if(element==4)//弯道
    {
        if(PULSE->Curve_Pulse_Key==1)
        {
            PULSE->Curve_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Curve_Pulse=(PULSE->Curve_Pulse_Last*9 + PULSE->Curve_Pulse)/10;//滤波得到总计数
            PULSE->Curve_Pulse_Last=PULSE->Curve_Pulse;
        }
        else {
            PULSE->Curve_Pulse=0;
            PULSE->Curve_Pulse_Last=0;
        }
    }
    else if(element==5)//斑马线
    {
        if(PULSE->Zebra_Pulse_Key==1)
        {
            PULSE->Zebra_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Zebra_Pulse=(PULSE->Zebra_Pulse_Last*9 + PULSE->Zebra_Pulse)/10;//滤波得到总计数
            PULSE->Zebra_Pulse_Last=PULSE->Zebra_Pulse;
        }
        else {
            PULSE->Zebra_Pulse=0;
            PULSE->Zebra_Pulse_Last=0;
        }
    }
}


/*************************************************************************
*  函数名称：void My_PulseClean(Pulse_Param_t * PULSE,int element)
*  参数说明：元素：0十字;1左圆环;2右圆环;3路障;4弯道;5斑马线
*  状态：开或关
*  功能说明：脉冲计数器清零
*  函数返回：无
*  修改时间：2023年5月30日
*  备    注：
*************************************************************************/
void My_PulseClean(Pulse_Param_t * PULSE,int element)
{
    if(element==0)//十字
    {
        PULSE->Cross_Pulse=0;
        PULSE->Cross__Pulse_Last=0;

    }
    else if(element==1)//左圆环
    {
        PULSE->Circle_Left_Pulse=0;
        PULSE->Circle_Left_Pulse_Last=0;
    }
    else if(element==2)//右圆环
    {
        PULSE->Circle_Right_Pulse=0;
        PULSE->Circle_Right_Pulse_Last=0;
    }
    else if(element==3)//路障
    {
        PULSE->Obstruction_Pulse=0;
        PULSE->Obstruction_Pulse_Last=0;
    }
    else if(element==4)//弯道
    {
        PULSE->Curve_Pulse=0;
        PULSE->Curve_Pulse_Last=0;
    }
    else if(element==5)//斑马线
    {
        PULSE->Zebra_Pulse=0;
        PULSE->Zebra_Pulse_Last=0;
    }
}

/*************************************************************************
*  函数名称：void Image_IdentifySet(Image_Identify * Ide, Image_element* Ele)
*  功能说明:   元素识别设置
*  函数返回：无
*  修改时间：2023年6月10日 需要进行修改
*  备    注：
*************************************************************************/
void Image_IdentifySet(Image_Identify * Ide, Image_element* Ele)
{

    if(Ele->Obstruction!=0)//路障优先级1
    {
        Ide->Circle_left_Identify=0;
        Ide->Circle_Right_Identify=0;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=1;
        Ide->Zebra_Identify=0;
        Ide->All_Identify=0;//非全元素识别
//        My_ElementClean(Ele,4);
    }
    else if(Ele->Circle_left>1)//左圆环优先级4
    {
        Ide->Circle_left_Identify=1;
        Ide->Circle_Right_Identify=0;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=0;
        Ide->Zebra_Identify=0;
        Ide->All_Identify=0;//非全元素识别
//        My_ElementClean(Ele,2);
    }
    else if(Ele->Circle_right>1)//右圆环优先级5
    {
        Ide->Circle_left_Identify=0;
        Ide->Circle_Right_Identify=1;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=0;
        Ide->Zebra_Identify=0;
        Ide->All_Identify=0;//非全元素识别
//        My_ElementClean(Ele,3);
    }
    else if(Ele->Zebra!=0)//右圆环优先级5
    {
        Ide->Circle_left_Identify=0;
        Ide->Circle_Right_Identify=0;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=0;
        Ide->Zebra_Identify=1;
        Ide->All_Identify=0;//非全元素识别
//        My_ElementClean(Ele,5);
    }

    else {
        //一个元素都没识别，全开
        //1代表开启元素识别
        Ide->Circle_left_Identify=1;
        Ide->Circle_Right_Identify=1;
        Ide->Cross_Identify=1;
        Ide->Obstruction_Identify=1;
        Ide->Zebra_Identify=1;
        Ide->All_Identify=1;//全元素识别
    }
}

/*************************************************************************
*  函数名称：void My_PulseKey(Pulse_Param_t * PULSE,int element,int state)
*  参数说明：元素：0十字;1左圆环;2右圆环;3路障;4弯道;5斑马线
*  状态：1开或0关
*  功能说明：脉冲计数器开关
*  函数返回：无
*  修改时间：2023年5月30日
*  备    注：
*************************************************************************/
void My_PulseKey(Pulse_Param_t * PULSE,int element,unsigned char state)
{
    if(element==0)//十字
    {
       PULSE->Cross_Pulse_Key=state;

    }
    else if(element==1)//左圆环
    {
       PULSE->Circle_Left_Pulse_Key=state;

    }
    else if(element==2)//右圆环
    {
       PULSE->Circle_Right_Pulse_Key=state;
    }
    else if(element==3)//路障
    {
       PULSE->Obstruction_Pulse_Key=state;
    }
    else if(element==4)//弯道
    {
       PULSE->Curve_Pulse_Key=state;
    }
    else if(element==5)//斑马线
    {
       PULSE->Zebra_Pulse_Key=state;
    }
}

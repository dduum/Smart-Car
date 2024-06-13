/*
 * Element_handle.c
 *
 *  Created on: 2024��6��3��
 *      Author: dduu
 */
#include <Element_handle.h>

Image_element Element1;
Image_Identify Identify1;
Pulse_Param_t ALLPULSE;
float Angle_in;//��Բ��ʱ�ĽǶ�
float Angle_delta;//�Ƕȱ仯ֵ

/*************************************************************************
*  �������ƣ�void Image_IdentifyProcess(Image_Identify * Ide)
*  ����˵��:   Ԫ��ʶ��
*  �������أ���
*  �޸�ʱ�䣺2023��6��10��
*  ��    ע��
*************************************************************************/
void Image_IdentifyProcess(Image_Identify * Ide)
{
    //δ�ӵ�ţ�ע�͵�����Ԫ��
    if(Ide->All_Identify==1)//ȫԪ��ʶ��
    {
        Image_CrossProcess(&Element1);//ʮ�ִ���
        Image_LeftCircleProcess(&Element1);//��Բ������
        Image_RightCircleProcess(&Element1);//��Բ������
        My_ObstructionProcess(&Element1);//·�ϴ���
        Image_ZebraProcess(&Element1);//�����ߴ���
    }
    else if(Ide->Circle_left_Identify==1)
    {
        Image_LeftCircleProcess(&Element1);//��Բ������
    }
    else if(Ide->Circle_Right_Identify==1)
    {
        Image_RightCircleProcess(&Element1);//��Բ������
    }
    else if(Ide->Obstruction_Identify==1)
    {
        My_ObstructionProcess(&Element1);//·�ϴ���
    }
    else if(Ide->Zebra_Identify==1)
    {
        Image_ZebraProcess(&Element1);//�����ߴ���
    }
}

/*************************************************************************
*  �������ƣ�void Image_CrossProcess(Image_element* Ele)
*  ����˵����
*  ����˵����ʮ�ִ���
*  �������أ���
*  �޸�ʱ�䣺2023��6��3��
*  ��    ע��
*************************************************************************/
void Image_CrossProcess(Image_element* Ele)
{


}


/*************************************************************************
*  �������ƣ�void Image_LeftCircleProcess(Image_element* Ele)
*  ����˵��: Բ��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2023��5��27��
*  ��    ע��
*************************************************************************/
void Image_LeftCircleProcess(Image_element* Ele)
{
    if(Ele->Circle_left==0)
    {
        if(1)
        {
            Ele->Circle_left=1;//ʶ��ɹ�������
            My_PulseKey(&ALLPULSE, 1, 1);//��
        }

    }
    else if(Ele->Circle_left==1)//Բ��״̬1���õ��ѭ��
    {
        if(1)
        {
            My_PulseClean(&ALLPULSE, 1);
            My_PulseKey(&ALLPULSE, 1, 0);//��
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
                //��¼��ʱ�����ǽǶ�

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
    else if(Ele->Circle_left==4)//�ĳ��������жϳ�����
    {
        if(ALLPULSE.Circle_Left_Pulse>3000)
        {
//            if(Angle>160)
//            {
//                My_PulseClean(&ALLPULSE, 2);
//                Ele->Circle_left=5;
//                Beep_On;
//            }
//            if(Left_num>120 && Right_num>120)//��������
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
            /*if(Angle>250)//����״̬��*/
            if(1)
            {
                My_PulseClean(&ALLPULSE, 2);
                Ele->Circle_left=6;
                Identify1.Circle_left_Identify=0;
            }

    }

    if(Ele->Circle_left!=4 && ALLPULSE.Circle_Left_Pulse>2500)
    {
        My_PulseKey(&ALLPULSE, 2, 0);//��
        My_PulseClean(&ALLPULSE, 2);
        Ele->Circle_left=0;
        Identify1.Circle_left_Identify=0;
    }
    else if(Ele->Circle_right==4 && ALLPULSE.Circle_Right_Pulse>8000){
          My_PulseKey(&ALLPULSE, 2, 0);//��
          My_PulseClean(&ALLPULSE, 2);
          Ele->Circle_left=0;
          //Angle=0;
          Identify1.Circle_left_Identify=0;
    }
}

/*************************************************************************
*  �������ƣ�void Image_RightCircleProcess(Image_element* Ele)
*  ����˵��: Բ��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2023��6��10��
*  ��    ע��  �˴���Բ����һ���ж���ʮ�������ʸߣ���Ҫ��һ������
*************************************************************************/
void Image_RightCircleProcess(Image_element* Ele)
{

}

/*************************************************************************
*  �������ƣ�void My_ObstructionProcess(Image_element* Ele)
*  ����˵����
*  ����˵����·�ϴ���
*  �������أ���
*  �޸�ʱ�䣺2023��6��3��
*  ��    ע��
*************************************************************************/
void My_ObstructionProcess(Image_element* Ele)
{

}

/*************************************************************************
*  �������ƣ�void Image_ZebraProcess(Image_element* Ele)
*  ����˵��: �����ߴ�����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2023��7��11��
*  ��    ע��
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

        if(change_cnt>=5)  //��Ϊ�ǳ���
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
*  �������ƣ�void Calcu_Pulse(void)
*  ����˵����
*  ״̬��
*  ����˵��������ȫԪ������
*  �������أ���
*  �޸�ʱ�䣺2023��5��30��
*  ��    ע��
*************************************************************************/
void Calcu_Pulse(void)
{
    //100Pulse��ԼΪ0.78cm
    for(int i=0;i<6;i++)
        My_PulseCount(&ALLPULSE,i);//����������
}


/*************************************************************************
*  �������ƣ�void My_PulseCount(Pulse_Param_t * PULSE,int element)
*  ����˵����Ԫ�أ�0ʮ��;1��Բ��;2��Բ��;3·��;4���;5������
*  ״̬�������
*  ����˵�������������
*  �������أ���
*  �޸�ʱ�䣺2023��5��30��
*  ��    ע��
*************************************************************************/
void My_PulseCount(Pulse_Param_t * PULSE,int element)
{
    if(element==0)//ʮ��
    {
        if(PULSE->Cross_Pulse_Key==1)
        {
            PULSE->Cross_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Cross_Pulse=(PULSE->Cross__Pulse_Last*9+PULSE->Cross_Pulse)/10;//�˲��õ��ܼ���
            PULSE->Cross__Pulse_Last=PULSE->Cross_Pulse;//��¼��һ����ֵ
        }
        else {
            PULSE->Cross_Pulse=0;
            PULSE->Cross__Pulse_Last=0;
        }
    }
    else if(element==1)//��Բ��
    {
        if(PULSE->Circle_Left_Pulse_Key==1)
        {
            PULSE->Circle_Left_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Circle_Left_Pulse=(PULSE->Circle_Left_Pulse_Last*9 + PULSE->Circle_Left_Pulse)/10;//�˲��õ��ܼ���
            PULSE->Circle_Left_Pulse_Last=PULSE->Circle_Left_Pulse;
        }
        else {
            PULSE->Circle_Left_Pulse=0;
            PULSE->Circle_Left_Pulse_Last=0;
        }
    }
    else if(element==2)//��Բ��
    {
        if(PULSE->Circle_Right_Pulse_Key==1)
        {
            PULSE->Circle_Right_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Circle_Right_Pulse=(PULSE->Circle_Right_Pulse_Last*9 + PULSE->Circle_Right_Pulse)/10;//�˲��õ��ܼ���
            PULSE->Circle_Right_Pulse_Last=PULSE->Circle_Right_Pulse;
        }
        else {
            PULSE->Circle_Right_Pulse=0;
            PULSE->Circle_Right_Pulse_Last=0;
        }
    }
    else if(element==3)//·��
    {
        if(PULSE->Obstruction_Pulse_Key==1)
        {
            PULSE->Obstruction_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Obstruction_Pulse=(PULSE->Obstruction_Pulse_Last*9 + PULSE->Obstruction_Pulse)/10;//�˲��õ��ܼ���
            PULSE->Obstruction_Pulse_Last=PULSE->Obstruction_Pulse;
        }
        else {
            PULSE->Obstruction_Pulse=0;
            PULSE->Obstruction_Pulse_Last=0;
        }
    }
    else if(element==4)//���
    {
        if(PULSE->Curve_Pulse_Key==1)
        {
            PULSE->Curve_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Curve_Pulse=(PULSE->Curve_Pulse_Last*9 + PULSE->Curve_Pulse)/10;//�˲��õ��ܼ���
            PULSE->Curve_Pulse_Last=PULSE->Curve_Pulse;
        }
        else {
            PULSE->Curve_Pulse=0;
            PULSE->Curve_Pulse_Last=0;
        }
    }
    else if(element==5)//������
    {
        if(PULSE->Zebra_Pulse_Key==1)
        {
            PULSE->Zebra_Pulse+=(ECPULSE1+ECPULSE2)/2;
            PULSE->Zebra_Pulse=(PULSE->Zebra_Pulse_Last*9 + PULSE->Zebra_Pulse)/10;//�˲��õ��ܼ���
            PULSE->Zebra_Pulse_Last=PULSE->Zebra_Pulse;
        }
        else {
            PULSE->Zebra_Pulse=0;
            PULSE->Zebra_Pulse_Last=0;
        }
    }
}


/*************************************************************************
*  �������ƣ�void My_PulseClean(Pulse_Param_t * PULSE,int element)
*  ����˵����Ԫ�أ�0ʮ��;1��Բ��;2��Բ��;3·��;4���;5������
*  ״̬�������
*  ����˵�����������������
*  �������أ���
*  �޸�ʱ�䣺2023��5��30��
*  ��    ע��
*************************************************************************/
void My_PulseClean(Pulse_Param_t * PULSE,int element)
{
    if(element==0)//ʮ��
    {
        PULSE->Cross_Pulse=0;
        PULSE->Cross__Pulse_Last=0;

    }
    else if(element==1)//��Բ��
    {
        PULSE->Circle_Left_Pulse=0;
        PULSE->Circle_Left_Pulse_Last=0;
    }
    else if(element==2)//��Բ��
    {
        PULSE->Circle_Right_Pulse=0;
        PULSE->Circle_Right_Pulse_Last=0;
    }
    else if(element==3)//·��
    {
        PULSE->Obstruction_Pulse=0;
        PULSE->Obstruction_Pulse_Last=0;
    }
    else if(element==4)//���
    {
        PULSE->Curve_Pulse=0;
        PULSE->Curve_Pulse_Last=0;
    }
    else if(element==5)//������
    {
        PULSE->Zebra_Pulse=0;
        PULSE->Zebra_Pulse_Last=0;
    }
}

/*************************************************************************
*  �������ƣ�void Image_IdentifySet(Image_Identify * Ide, Image_element* Ele)
*  ����˵��:   Ԫ��ʶ������
*  �������أ���
*  �޸�ʱ�䣺2023��6��10�� ��Ҫ�����޸�
*  ��    ע��
*************************************************************************/
void Image_IdentifySet(Image_Identify * Ide, Image_element* Ele)
{

    if(Ele->Obstruction!=0)//·�����ȼ�1
    {
        Ide->Circle_left_Identify=0;
        Ide->Circle_Right_Identify=0;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=1;
        Ide->Zebra_Identify=0;
        Ide->All_Identify=0;//��ȫԪ��ʶ��
//        My_ElementClean(Ele,4);
    }
    else if(Ele->Circle_left>1)//��Բ�����ȼ�4
    {
        Ide->Circle_left_Identify=1;
        Ide->Circle_Right_Identify=0;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=0;
        Ide->Zebra_Identify=0;
        Ide->All_Identify=0;//��ȫԪ��ʶ��
//        My_ElementClean(Ele,2);
    }
    else if(Ele->Circle_right>1)//��Բ�����ȼ�5
    {
        Ide->Circle_left_Identify=0;
        Ide->Circle_Right_Identify=1;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=0;
        Ide->Zebra_Identify=0;
        Ide->All_Identify=0;//��ȫԪ��ʶ��
//        My_ElementClean(Ele,3);
    }
    else if(Ele->Zebra!=0)//��Բ�����ȼ�5
    {
        Ide->Circle_left_Identify=0;
        Ide->Circle_Right_Identify=0;
        Ide->Cross_Identify=0;
        Ide->Obstruction_Identify=0;
        Ide->Zebra_Identify=1;
        Ide->All_Identify=0;//��ȫԪ��ʶ��
//        My_ElementClean(Ele,5);
    }

    else {
        //һ��Ԫ�ض�ûʶ��ȫ��
        //1������Ԫ��ʶ��
        Ide->Circle_left_Identify=1;
        Ide->Circle_Right_Identify=1;
        Ide->Cross_Identify=1;
        Ide->Obstruction_Identify=1;
        Ide->Zebra_Identify=1;
        Ide->All_Identify=1;//ȫԪ��ʶ��
    }
}

/*************************************************************************
*  �������ƣ�void My_PulseKey(Pulse_Param_t * PULSE,int element,int state)
*  ����˵����Ԫ�أ�0ʮ��;1��Բ��;2��Բ��;3·��;4���;5������
*  ״̬��1����0��
*  ����˵�����������������
*  �������أ���
*  �޸�ʱ�䣺2023��5��30��
*  ��    ע��
*************************************************************************/
void My_PulseKey(Pulse_Param_t * PULSE,int element,unsigned char state)
{
    if(element==0)//ʮ��
    {
       PULSE->Cross_Pulse_Key=state;

    }
    else if(element==1)//��Բ��
    {
       PULSE->Circle_Left_Pulse_Key=state;

    }
    else if(element==2)//��Բ��
    {
       PULSE->Circle_Right_Pulse_Key=state;
    }
    else if(element==3)//·��
    {
       PULSE->Obstruction_Pulse_Key=state;
    }
    else if(element==4)//���
    {
       PULSE->Curve_Pulse_Key=state;
    }
    else if(element==5)//������
    {
       PULSE->Zebra_Pulse_Key=state;
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��10��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.2.2�����ϰ汾
��Target �� TC264DA/TC264D
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
����CIFΪTC264DA�����⣬�����Ĵ������TC264D
����Ĭ�ϳ�ʼ����EMEM��512K������û�ʹ��TC264D��ע�͵�EMEM_InitConfig()��ʼ��������
������\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c��164�����ҡ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/


#include <LQ_OLED096.h>
#include <LQ_EEPROM.h>
#include <LQ_TFT18.h>
#include <LQ_PID.h>


/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////���²���Ϊ���ܲ���/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/*************************************************************************
*  �������ƣ�void Test_EEPROM(void)
*  ����˵����������ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/

void Test_EEPROM(void)
{
    int i;

//  OLED_Init();
//  OLED_P6x8Str(0,3,"eeprom");         //�ַ���

    TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
    TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
    TFTSPI_P8X16Str(0,0,"eeprom",u16WHITE,u16BLACK);

    unsigned long u32wBuff[24];
    unsigned long u32rBuff[24];

    float f32wBuff[24];
//    float f32rBuff[24];

    /* ��ֵ */
    for(i = 0; i < 24; i++)
    {
        u32wBuff[i] = i * 100;
        f32wBuff[i] = i * 2.5f;
    }

    EEPROM_EraseSector(0);
    EEPROM_EraseSector(1);

    TFTSPI_P8X16Str(0,1,"eeporm u write",u16WHITE,u16BLACK);

    /* д�� */
    EEPROM_Write(0, 0, u32wBuff, 24);

    TFTSPI_P8X16Str(0,3,"eeporm u read",u16WHITE,u16BLACK);

    /* ���� */
    EEPROM_Read(0, 0, u32rBuff, 24);


    /* �Ƚ� */
    for(i = 0; i < 9; i++)
    {
        if(u32wBuff[i] != u32rBuff[i])
        {
            TFTSPI_P8X16Str(0,5,"u32error",u16WHITE,u16BLACK);
        }
    }

#pragma warning 557         // ���ξ���
    while (1);
#pragma warning default     // �򿪾���
}


//void test_pid(void)
//{
//    TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
//    TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
//    TFTSPI_P8X16Str(0,0,"eeprom",u16WHITE,u16BLACK);
//
//    int i;
//    float PID_Write[6];
//    float PID_Read[6];
//    PID_Write[0]=Servo_Loc_PID.kp;
//    PID_Write[1]=Servo_Loc_PID.ki;
//    PID_Write[2]=Servo_Loc_PID.kd;
//    PID_Write[3]=Motor_Inc_PID1.kp;
//    PID_Write[4]=Motor_Inc_PID1.ki;
//    PID_Write[5]=Motor_Inc_PID1.kd;
//
//
//    EEPROM_EraseSector(0);
//
////    /* д�� */
//    TFTSPI_P8X16Str(0,2,"pid f write",u16WHITE,u16BLACK);
//
//    EEPROM_Write(0, 0, (unsigned long*)PID_Write, 6);
//
//    /* ���� */
//    TFTSPI_P8X16Str(0,4,"pid f read",u16WHITE,u16BLACK);
//
//    EEPROM_Read(0, 0, (unsigned long*)PID_Read, 6);
//
//    /* �Ƚ� */
//    for(i = 0; i < 6; i++)
//    {
//        if(abs(PID_Write[i]-PID_Read[i])<0.1)
//        {
//            TFTSPI_P8X16Str(0,0,"cornet",u16WHITE,u16BLACK);
//        }
//    }
//    TFTSPI_P8X16Str(0,7,"eeprom is ok",u16WHITE,u16BLACK);
//
//}

void E2PROM_Read_PID(void)
{
    float PID_Read[12];
    EEPROM_Read(0, 0, (unsigned long*)PID_Read, 12);
    Servo_Loc_PID.kp=PID_Read[0];
    Servo_Loc_PID.ki=PID_Read[1];
    Servo_Loc_PID.kd=PID_Read[2];
    Servo_Loc_PID.kp2=PID_Read[3];
    Servo_Loc_PID.kd2=PID_Read[4];
    Motor_Inc_PID1.kp=PID_Read[5];
    Motor_Inc_PID1.ki=PID_Read[6];
    Motor_Inc_PID1.kd=PID_Read[7];
    Motor_Inc_PID2.kp=PID_Read[8];
    Motor_Inc_PID2.ki=PID_Read[9];
    Motor_Inc_PID2.kd=PID_Read[10];
    Look_Line=PID_Read[11];
}

void E2PROM_Write_PID(void)
{
    float PID_Write[12];
    //��������
    EEPROM_EraseSector(0);

    PID_Write[0]=Servo_Loc_PID.kp;
    PID_Write[1]=Servo_Loc_PID.ki;
    PID_Write[2]=Servo_Loc_PID.kd;
    PID_Write[3]=Servo_Loc_PID.kp2;
    PID_Write[4]=Servo_Loc_PID.kd2;
    PID_Write[5]=Motor_Inc_PID1.kp;
    PID_Write[6]=Motor_Inc_PID1.ki;
    PID_Write[7]=Motor_Inc_PID1.kd;
    PID_Write[8]=Motor_Inc_PID2.kp;
    PID_Write[9]=Motor_Inc_PID2.ki;
    PID_Write[10]=Motor_Inc_PID2.kd;
    PID_Write[11]=Look_Line;

    EEPROM_Write(0, 0, (unsigned long*)PID_Write, 12);
}





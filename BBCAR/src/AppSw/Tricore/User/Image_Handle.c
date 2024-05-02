/*
 * Image_Handle.c
 *  ���ܣ�����ͷ����Ѳ��
 *  Created on: 2023��12��10��
 *      Author: dduu
 */
#include "image_Handle.h"

extern unsigned char Bin_Image[LCDH][LCDW];

extern volatile uint8 CrossWay_Flag;

typedef struct{
        uint8 X; //������0~119
        uint8 Y; //������0~159
}Point;

Point A;
Point B;
Point C;
Point D;

uint8 ZUO[120];
uint8 YOU[120];
uint8 ZHONGJIAN[120];

uint8 Lost_Left_Count=0;
uint8 Lost_Right_Count=0;
uint8 Lost_Left_Loc=50;
uint8 Lost_Right_Loc=50;

//����ƫ��
uint8 QIANZHAN=15;
uint8 YUAN,ZHONG,JIN;

uint8 Servo_QZ_ERR=0; //ǰհ���
int Servo_Loc_error=0; //����������

uint8 StraightWay_flag=0; //0Ϊ�����1Ϊֱ��

uint8 ImageSide_LR[2][100];  //���ұ���
uint8 ImageSide_UD[2][160];  //���±���

int ABS(int A)
{
    if(A<=0)
    {
       A=-A;
    }
    return A;
}

uint8 min(uint8 A,uint8 B)
{
    return (A>=B)?B:A;
}

void GetUpDownSide(void)   //��ǰ���ó�Ϊ100����Ϊ160
{
    uint8 last = 50;
    uint8 i = 0, j = 0;
    //��ʼ��,�����±��߳�ʼ��Ϊ�߽�ֵ
    for(uint8 i=0;i<160;i++)
    {
        ImageSide_UD[0][i]=0;
        ImageSide_UD[1][i]=99;
    }

    /* �����߱ȽϽ����� �ж��Ƿ��� */
    for(i = last; i > 0; i--)
    {
        if(Bin_Image[i][80]==0)  //�ҵ��ڵ�
        {
            ImageSide_UD[0][80] = i;
            break;
        }
    }

    for(i = last; i < 100; i++)
    {
        if(Bin_Image[i][80]==0)
        {
            ImageSide_UD[1][80] = i;
            break;
        }
    }

    for(i=80-1;i>0;i--)  //����������
    {
        for(j=ImageSide_UD[0][i+1]+10;(j>0 && j<100);j--)   //�������ϱ���
        {
            if(Bin_Image[j][i]==0)
            {
                ImageSide_UD[0][i]=j;
                break;
            }
        }
        for(j=ImageSide_UD[1][i+1]-10;(j>0 && j<100);j++)  //�������±���
        {
            if(Bin_Image[j][i]==0)
            {
                ImageSide_UD[1][i]=j;
                break;
            }
        }
    }

    for(i=80+1;i<160;i++)  //�����Ұ����
    {
        for(j=ImageSide_UD[0][i-1]+10;(j>0 && j<100);j--)   //�������ϱ���
        {
            if(Bin_Image[j][i]==0)
            {
                ImageSide_UD[0][i]=j;
                break;
            }
        }
        for(j=ImageSide_UD[1][i+1]-10;(j>0 && j<100);j++)  //�������±���
        {
            if(Bin_Image[j][i]==0)
            {
                ImageSide_UD[1][i]=j;
                break;
            }
        }
    }

}

//��forѭ����ʱ��������ñ�������Ϊuint8����0~255��0��-�Ļ�Ϊ255�����ѭ������Ϊ>0����ôѭ���޷�����,����ڱ߽��ʱ��߽�����Ϊ��ʼֵ0/159
void GetImageSide(void)  //�������±�20�У�ʣ��100�������ұ���BinImage[100][160]
{
    //          ������
   //��ʼ��,���������߳�ʼ��Ϊ�߽�ֵ
   for(uint8 i=0;i<100;i++)
   {
       ImageSide_LR[0][i]=0;
       ImageSide_LR[1][i]=159;
   }
   //����ͷ����Ļ�ϵ���ʾΪ�±�Ϊ99���������������𽥵ݼ�
   for(uint8 i=99;i>0;i--)
   {
       //���м�����߽���Ѳ��
       for(uint8 j=80;j>=1;j--)
       {
           if((Bin_Image[i][j-1]==0) && (Bin_Image[i][j]==0) && (Bin_Image[i][j+1]==1)) //
           {
               ImageSide_LR[0][i] = j ;
               break;
           }
       }
       //���м����ұ߽���Ѳ��
       for(uint8 j=80;j<=158;j++)
       {
           if((Bin_Image[i][j-1]==1) && (Bin_Image[i][j]==0) && (Bin_Image[i][j+1]==0))
           {
               ImageSide_LR[1][i] = j;
               break;
           }
       }
   }
}

void Get_ABCD(void)  //��ȡ�����ABCD��������Ѳ�߸����ߵ�������
{
    A.X=100;
    A.Y=2;
    B.X=100;
    B.Y=157;  //��ʼ��
    for(uint8 i=80;i>0;i--)
    {
        if(Bin_Image[A.X][i]==0)
        {
            A.Y=i;
            break;
        }
    }
    for(uint8 i=80;i<159;i++)
    {
        if(Bin_Image[B.X][i]==0)
        {
            B.Y=i;
            break;
        }
    }

    C.X=A.X-1;
    C.Y=A.Y;
    for(uint8 i=C.X;i>1;i--)
    {
        C.X=i;
        for(uint8 j=C.Y-1;j<80;j++)
        {
            if(Bin_Image[i][j]==1)  //�Ӳ��������Ұ׵�
            {
                C.Y=j-1;  //��Ϊ�ڵ�
                break;
            }
        }
        if(Bin_Image[i-1][C.Y]==1 && Bin_Image[i-2][C.Y]==1)  //˵���ҵ��յ�C
        {
            C.X=i;
            break;
        }
    }
    D.X=B.X-1;
    D.Y=B.Y;
    for(uint8 i=D.X;i>1;i--)
    {
        D.X=i;
        for(uint8 j=D.Y+1;j>80;j--)
        {
            if(Bin_Image[i][j]==1)  //�Ӳ��������Ұ׵�
            {
                D.Y=j+1;  //��Ϊ�ڵ�
                break;
            }
        }
        if(Bin_Image[i-1][D.Y]==1 && Bin_Image[i-2][D.Y]==1)  //˵���ҵ��յ�D
        {
            D.X=i;
            break;
        }
    }

    //�����ж�ʮ��·��
    if(ABS(C.X-D.X)<10 && C.X>30 && D.X>30)
    {
        uint8 X=min(C.X,D.X)-1;   //��һ��
        uint8 black=0;
        for(uint8 i=X;i>X-10;i--)
        {
            for(uint8 j=20;j<80;j+=5)
            {
                if(Bin_Image[i][j]==0)
                {
                    black++;
                }
            }
        }
        if(black<10)  //�жϳ�ʮ��·�ڣ����в���
        {
            CrossWay_Flag=1;
        }
    }

    if(CrossWay_Flag)
    {
        float K;
        K=(float)(A.X-C.X)/(C.Y-A.Y);
        for(uint8 i=C.X-1;i>C.X-20;i--)
        {
            Bin_Image[i][(uint8)((C.X-i)/K+C.Y)]=0;
            Bin_Image[i][(uint8)((C.X-i)/K+C.Y+1)]=0;
        }
        K=(float)(B.X-D.X)/(B.Y-D.Y);
        for(uint8 i=D.X-1;i>D.X-20;i--)
        {
            Bin_Image[i][(uint8)((i-D.X)/K+D.Y)]=0;
            Bin_Image[i][(uint8)((i-D.X)/K+D.Y-1)]=0;
        }
        if(ABS(C.X-D.X)>10 || C.X<=30 || D.X<=30)
        {
            CrossWay_Flag=0;
        }
    }
}


//��Ϊ0����Ϊ1
void image_handle(void)
{
    //          ������
    //��ʼ��,���������߳�ʼ��Ϊ�߽�ֵ
    for(uint8 i=0;i<120;i++)
    {
        ZHONGJIAN[i]=79;
        ZUO[i]=0;
        YOU[i]=159;
    }
    //����ͷ����Ļ�ϵ���ʾΪ�±�Ϊ99���������������𽥵ݼ�
    for(uint8 i=119;i>0;i--)
    {
        //���м�����߽���Ѳ��
        for(uint8 j=ZHONGJIAN[i];j>=1;j--)
        {
            if((Bin_Image[i][j-1]==0) && (Bin_Image[i][j]==0) && (Bin_Image[i][j+1]==1)) //
            {
                ZUO[i] =j ;
                break;
            }
        }
        //���м����ұ߽���Ѳ��
        for(uint8 j=ZHONGJIAN[i];j<=158;j++)
        {
            if((Bin_Image[i][j-1]==1) && (Bin_Image[i][j]==0) && (Bin_Image[i][j+1]==0))
            {
                YOU[i] = j;
                break;
            }
        }

        ZHONGJIAN[i] = (ZUO[i] + YOU[i]) /2;

        //���������������ú���Ϳ��
        Bin_Image[i][ZHONGJIAN[i]]=0;
    }
    //ǰհ  ����ƫ��
    JIN=ZHONGJIAN[110];
    ZHONG=ZHONGJIAN[110-QIANZHAN];
    YUAN=ZHONGJIAN[110-QIANZHAN*2];

    if(JIN<ZHONG && ZHONG<YUAN)
    {
        Servo_QZ_ERR=((YUAN-ZHONG)+(ZHONG-JIN))/2;
    }
    else if(JIN<ZHONG && ZHONG>YUAN)
    {
        Servo_QZ_ERR=(ZHONG-JIN)/2;
    }
    else if(JIN>ZHONG && ZHONG>YUAN)
    {
        Servo_QZ_ERR=((JIN-ZHONG)+(ZHONG-YUAN))/2;
    }
    else if(JIN>ZHONG && ZHONG<YUAN)
    {
        Servo_QZ_ERR=(JIN-ZHONG)/2;
    }

    Servo_Loc_error=80-ZHONGJIAN[100];  //�������

}

void Lost_Line_Left(uint8* count,uint8* loc)  //��������߶�������
{
    uint8 flag=0;
    *count=0;
    *loc=50;  //����Ĭ��ֵ
    for(uint8 i=LCDH-1-5;i>0;i--) //����������5�п�����������ͷ��ǵ��µĶ�������
    {
        if(ImageSide_LR[0][i]==0)
        {
            (*count)++;
            if((ImageSide_LR[0][i+1]-ImageSide_LR[0][i]>25) && flag==0)  //��¼������������һ�η���ͻ���λ��
            {
                *loc=i;
                flag=1;
            }
        }
    }
}

void Lost_Line_Right(uint8* count,uint8* loc)  //�����ұ��߶�������
{
    uint8 flag=0;
    *count=0;
    *loc=50;  //����Ĭ��ֵ
    for(uint8 i=LCDH-1-5;i>0;i--) //����������5�п�����������ͷ��ǵ��µĶ�������
    {
        if(ImageSide_LR[1][i]==159)
        {
            (*count)++;
            if((ImageSide_LR[1][i]-ImageSide_LR[1][i+1]>25) && flag==0)  //��¼���ұ��������һ�η���ͻ���λ��
            {
                *loc=i;
                flag=1;
            }
        }
    }
}


void Judge_CrossRoad(void)
{
    Lost_Line_Left(&Lost_Left_Count,&Lost_Left_Loc);
    Lost_Line_Right(&Lost_Right_Count,&Lost_Right_Loc);

    if(Lost_Left_Count>=20 && Lost_Right_Count>=20)            //���Ҷ��߽϶࣬�����ж�ʮ��·��
    {
        uint8 X=min(Lost_Left_Loc,Lost_Right_Loc);   //��һ��
        uint8 black=0;
        for(uint8 i=X;i>X-10;i--)
        {
            for(uint8 j=20;j<140;j+=5)
            {
                if(Bin_Image[i][j]==0)
                {
                    black++;
                }
            }
        }
        if(black<15)  //�����жϳ�ʮ��·�ڣ����в���
        {
            CrossWay_Flag=1;
        }
    }
}



uint8 UpSide[160];


Point Up_Left;     //���Ϲյ�
Point Up_Right;    //���Ϲյ�
Point Down_Left;   //���¹յ�
Point Down_Right;  //���¹յ�

void Camera_Handle(void)
{
    //�Ϲյ�  ��������������ͻ��
    for(uint8 i=0;i<160;i++)
    {
        for(uint8 j=0;j<120;j++)
        {
            if(Bin_Image[j][i]==0 || j==119)  // ?
            {
                UpSide[i]=j;
            }
        }
    }

    for(uint8 i=80;i>0;i--)
    {
        if(UpSide[i-1]<UpSide[i] && UpSide[i]>UpSide[i+1])
        {
            Up_Left.X=UpSide[i];
            Up_Left.Y=i;
        }
    }

    for(uint8 i=80;i<159;i++)
    {
        if(UpSide[i-1]<UpSide[i] && UpSide[i]>UpSide[i+1])
        {
            Up_Right.X=UpSide[i];
            Up_Right.Y=i;
        }
    }

    //�¹յ�  ���ұ߽�������ͻ��
    for(uint8 i=118;i>0;i--)
    {
        if(ZUO[i-1]<ZUO[i] && ZUO[i]>ZUO[i+1])
        {
            Down_Left.X=i;
            Down_Left.Y=ZUO[i];
            break;
        }
    }
    for(uint8 i=118;i>0;i--)
    {
        if(YOU[i+1]>YOU[i] && YOU[i]<YOU[i-1])
        {
            Down_Right.X=i;
            Down_Right.Y=YOU[i];
            break;
        }
    }
}





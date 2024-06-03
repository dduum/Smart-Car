/*
 * image.c
 *
 *  Created on: 2024��4��16��
 *      Author: Macation
 */
#include "image1.h"

int Left_num=Array_Length;
int Right_num=Array_Length;
int dir_left[4];//�����������Ϣ
int dir_right[4];//�ұ���������Ϣ
int Servo_Loc_error=0;

//�����������ΪX���ұ�ΪY
int dir_front[4][2]=   {{0,-1},
                        {1,0},
                        {0,1},
                        {-1,0}};
int dir_frontleft[4][2]=   {{-1,-1},
                            {1,-1},
                            {1,1},
                            {-1,1}};
int dir_frontright[4][2]=   {{1,-1},
                            {1,1},
                            {-1,1},
                            {-1,-1}};
int Image_Lefthand_Line[Array_Length][2];
int Image_Righthand_Line[Array_Length][2];
unsigned char Image_Line[120][160];  //�����ȡ���ߺ��ͼ������
unsigned char Image_centralLine[Image_Length];//��������
int InterPoint[2];

/*************************************************************************
*  �������ƣ�int Image_Threshold_Line(int Y)
*  ����˵�����Ե�������ֵ
*  �������أ���
*  �޸�ʱ�䣺2023��6��15��
*  ��    ע��
*************************************************************************/
int Image_Threshold_Line(int Y)
{
    signed int i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    int MinValue, MaxValue;
    int Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for(i=0;i<LCDW;i++)
    {
        HistoGram[Image_Use[Y][i]]++;
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++)
        ;        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MaxValue] == 0;
            MaxValue--)
        ; //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
        return MaxValue;         // ͼ����ֻ��һ����ɫ
    if (MinValue + 1 == MaxValue)
        return MinValue;        // ͼ����ֻ�ж�����ɫ

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  ��������

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++) {
        Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++) {
        PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
        PixelFore = Amount - PixelBack;           //�������ص���
        OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
        OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
        PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
        MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
        MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore)
                * (MicroBack - MicroFore);   //������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
                {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}
/*************************************************************************
*  �������ƣ�int Image_Findline_Lefthand(int X,int Y,int *num)
*  ����˵����  X��Y����һ��Ѱ�ҵ����������ʼ�㣻 num�Ǳ�������ĳ���
*  ����˵���������Թ�Ѳ��
*  �������أ���
*  �޸�ʱ�䣺2023��4��12��
*  ��    ע��
*************************************************************************/
int Image_Findline_Lefthand(int X,int Y,int num)
{
    int dx,dy;
    int block_size=7;//ÿһ�����ߵĵ���7*7�ķ����������Ӧ��ֵ��
    int clip_value=0;//��ֵ�ü���
    int half = block_size/2; //3
    int step=0,dir=0,turn=0;
    //ѭ����ȷ����(X,Y)�ں��ʷ�Χ�ڣ�����ʹ��7*7����Ӧ
    while(step < num && half < X && X < 160 -half-1 && half < Y && Y < 120-half-1 && turn < 4)
    {
        signed long local_thres=0;//����Ӧ��ֵ
        for(dy=-half; dy<=half; dy++)
        {
            for(dx=-half; dx<= half; dx++)
            {
                local_thres+=Image_Use[Y+dy][X+dx]; //�Ҷ�
            }
        }
        local_thres /= block_size*block_size;
        local_thres -=clip_value;  //��ֵ
        //������ǽ���Թ�                    //-1                       //0
        int front_value = Image_Use[Y+dir_front[dir][1]][X+dir_front[dir][0]];
        int frontleft_value = Image_Use[Y+dir_frontleft[dir][1]][X+dir_frontleft[dir][0]];
        if(front_value < local_thres)
        {
            dir = (dir + 1)%4;
            turn ++;
        }
        else if(frontleft_value < local_thres)
        {
            dir_left[dir]++;  //дԪ���õ�
            X += dir_front[dir][0];
            Y += dir_front[dir][1];
            Image_Lefthand_Line[step][0]=X;
            Image_Lefthand_Line[step][1]=Y;
            Bin_Image[Y][X]=1;             //�߽������߽������ѡһ
            step++;
            turn=0;
        }
        else
        {
            X += dir_frontleft[dir][0];
            Y += dir_frontleft[dir][1];
            dir = (dir + 3)%4;
            Image_Lefthand_Line[step][0]=X;
            Image_Lefthand_Line[step][1]=Y;
            Bin_Image[Y][X]=1;
            dir_left[dir]++;//�߽������߽������ѡһ
            step++;
            turn=0;
        }

    }
    return step;
}
/*************************************************************************
*  �������ƣ�int Image_findSeedBegin(Image_element* Ele, int thres)
*  ����˵���������ӵ���ʼ�㺯��
*  �������أ���
*  �޸�ʱ�䣺2023��4��23��
*  ��    ע��
*************************************************************************/
int Image_findSeedBegin(int thres)
{
    int i=0;
    for(i=79;i>2;i--)
    {
        if(Image_Use[Image_downLine][i-1]>thres && Image_Use[Image_downLine][i]>thres
                && Image_Use[Image_downLine][i+1]>thres)
        {
            return i;    //���м������Ѱ������������������ֵ�ĵ�
        }
    }
    for(i=80;i<LCDW-2;i++)
    {
        if(Image_Use[Image_downLine][i-1]>thres && Image_Use[Image_downLine][i]>thres
                && Image_Use[Image_downLine][i+1]>thres)
        {
            return i;    //���м����ұ�Ѱ������������������ֵ�ĵ�
        }
    }
    return LCDW/2;
}
/*************************************************************************
*  �������ƣ�int Image_Findline_Righthand(int X,int Y,int num)
*  ����˵���� X��Y����һ��Ѱ�ҵ����ұ�����ʼ�� num�Ǳ�������ĳ���
*  ����˵���������Թ�Ѳ��
*  �������أ���
*  �޸�ʱ�䣺2023��4��12��
*  ��    ע��
*************************************************************************/
int Image_Findline_Righthand(int X,int Y,int num)
{
    int dx,dy;
    int block_size=7;//ÿһ�����ߵĵ���7*7�ķ����������Ӧ��ֵ��
    int clip_value=0;//��ֵ�ü���
    int half = block_size/2;
    int step=0,dir=0,turn=0;
    //ѭ����ȷ����(X,Y)�ں��ʷ�Χ�ڣ�����ʹ��7*7����Ӧ

    while(step < num && half < X && X < LCDW -half && half < Y && Y < LCDH -half-1 && turn < 4)
    {
        signed long local_thres=0;//����Ӧ��ֵ
        for(dy=-half; dy<=half; dy++)
        {
            for(dx=-half; dx<= half; dx++)
            {
                local_thres+=Image_Use[Y+dy][X+dx];
            }
        }
        local_thres /= block_size*block_size;
        local_thres -=clip_value;

        //������ǽ���Թ�
        int front_value = Image_Use[Y+dir_front[dir][1]][X+dir_front[dir][0]];
        int frontright_value = Image_Use[Y+dir_frontright[dir][1]][X+dir_frontright[dir][0]];
        if (front_value < local_thres) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (frontright_value < local_thres) {

            dir_right[dir]++;
            X += dir_front[dir][0];
            Y += dir_front[dir][1];
            Image_Righthand_Line[step][0] = X;
            Image_Righthand_Line[step][1] = Y;
            Bin_Image[Y][X]=1;             //�߽������߽������ѡһ

            step++;
            turn = 0;
        } else {

            X += dir_frontright[dir][0];
            Y += dir_frontright[dir][1];
            dir = (dir + 1) % 4;
            Image_Righthand_Line[step][0] = X;
            Image_Righthand_Line[step][1] = Y;
            Bin_Image[Y][X]=1;             //�߽������߽������ѡһ
            dir_right[dir]++;
            step++;
            turn = 0;
        }
    }
    return step;
}
/*************************************************************************
*  �������ƣ�void Image_SeedGrowing(void)
*  ����˵���������������������ұ��ߺ���
*  �������أ���
*  �޸�ʱ�䣺2023��4��12��
*  ��    ע��
*
*************************************************************************/
int threshold;
int Image_SeedGrowing(void)
{
    int threshold1=0;
    int threshold2=0;
    int threshold3=0;
    threshold=0;
    memset(Bin_Image,0,sizeof(Bin_Image));
    memset(Image_Lefthand_Line,0,sizeof(Image_Lefthand_Line));
    memset(Image_Righthand_Line,0,sizeof(Image_Righthand_Line));
    threshold1=Image_Threshold_Line(110);
    threshold2=Image_Threshold_Line(109);
    threshold3=Image_Threshold_Line(108);
    threshold=(threshold1+threshold2+threshold3)/3;
    if(threshold<=0)//ʧ��
    {
        threshold=1;
    }
    //�趨���ұ��߳���
    Left_num=Array_Length;
    Right_num=Array_Length;
    int X1=80;   //��������ʼ��
    int Y1=Image_downLine;
    int X2=X1;
    int Y2=Y1;  //����X1,Y1
    //ɨ�����ʱÿһ�е����
    //��ʼ����ʼ��

    //�ȴ���ʼ������Ѱ����߽�������
    for(; X1>0; X1--)
    {
        if(Image_Use[Y1][X1-1] < threshold)
        {
            break;
        }
    }
    Left_num=Image_Findline_Lefthand(X1,Y1,Left_num);   //X1����㻹�ǰ�ɫ�ģ�����ߵĵ�Ϊ��ɫ

    //�ٴ���ʼ������Ѱ���ұ߽�������
    for(; X2<LCDW -1; X2++)
    {
        if(Image_Use[Y2][X2+1] < threshold)
        {
            break;
        }
    }
    Right_num=Image_Findline_Righthand(X2,Y2,Right_num);  //X2����㻹�ǰ�ɫ��,���ұߵĵ�Ϊ��ɫ

//    Bin_Image[Y1][X1]=1;
//    Bin_Image[Y1][X2]=1;
    Image_seedCentralline(X1,X2);
    //ͼ������////
    //��X1��X2�еõ����������λ��
    Servo_Loc_error=Calc_ERROR();

    return 0;
}

//void Image_printSeedline(void)
//{
//    int i=0;
//    unsigned char x=0;unsigned char y=0;
//    for(i=0; i<Array_Length-1; i++)
//    {
//        x=(unsigned char)Image_Lefthand_Line[i][0];
//        y=(unsigned char)Image_Lefthand_Line[i][1];
//
//    }
//    for(i=0; i<Array_Length-1; i++)
//    {
//        x=(unsigned char)Image_Righthand_Line[i][0];
//        y=(unsigned char)Image_Righthand_Line[i][1];
//    }
//}
/*************************************************************************
*  �������ƣ�void Image_Frameprocessing()
*  ����˵��:   ��ԭͼ�߿�Ȧ������Ϊ��һ���߽�������׼��
*  �������أ���
*  �޸�ʱ�䣺2023��4��5��
*  ��    ע��
*************************************************************************/
void Image_Frameprocessing()
{
    for(int i=0;i<120;i++)
    {
        Image_Use[i][3]=0;
        Image_Use[i][160-3]=0;
    }
}

/*************************************************************************
*  �������ƣ�void Image_seedCentralline(int X1,int X2)
*  ����˵���� ���ұ߽�����Ӻ�����
*  ����˵���������������ҳ��߽��ɨ�ߵ�����
*  �������أ���
*  �޸�ʱ�䣺2023��4��23��
*  ��    ע��
*************************************************************************/
void Image_seedCentralline(int X1,int X2)
{
    unsigned char i,j;
//    unsigned char L1,L2,R1,R2;
    //ɨ�����ʱÿһ�е����
    unsigned char LeftStart=X1+5;
    unsigned char RightStart=X2-5;
    unsigned char Left[Image_Length]={0};
    unsigned char Right[Image_Length]={LCDW-1};
    for(i=Image_downLine-1;i>Image_upLine;i--)//������������ĵ�һ������Image_downLine��һ�У�����ȡ��ҲҪ����һ��
    {
        //��ֹ��㳬��ͼ��Χ
        if(RightStart>LCDW-1)
        {
            RightStart=LCDW-1;
        }
        if(LeftStart<0)
        {
            LeftStart=0;
        }
//        //��ױ��֣�����ڸ���δ�ҵ�����㣬��ͬ��һ��ѭ���Ľ������һ��
//        if(i<Image_downLine-1)
//        {
//            Left[i-Image_upLine]=Left[i+1-Image_upLine];
//            Right[i-Image_upLine]=Right[i+1-Image_upLine];
//
//        }
        //ɨ���ߣ��������һ�е�����������Ӹ��������Բ����м�㿪ʼ������
        for(j=LeftStart;j > 0;j--)
        {
            if(Bin_Image[i][j]==1)//�ҵ������
            {
                Left[i-Image_upLine]=j;

                break;
            }
        }
        //ɨ���ߣ�ͬ��������
        for(j=RightStart;j< LCDW -1;j++)
        {
            if(Bin_Image[i][j]==1)//�ҵ������
            {
                Right[i-Image_upLine]=j;

                break;
            }
        }
        //�滮��һ�ε����
        LeftStart=Left[i-Image_upLine]+10;
        RightStart=Right[i-Image_upLine]-10;

    }

    for(i=0;i<Image_Length;i++)
    {
        Image_centralLine[i]=(Left[i]+Right[i])/2;
//        if(Bin_Image[i+Image_upLine][Image_centralLine[i]]==1)//�ҵ�����λ��
//        {
//            InterPoint[1]=i+Image_upLine;//��
//            InterPoint[0]=Image_centralLine[i];//��
//        }
    }
    //��ͼ���л�������
    for(i=Image_downLine-1;i>Image_upLine-1;i--)
    {
        j=Image_centralLine[i-Image_upLine];
        //�Ӵ֣��������ص�
        Bin_Image[i][j]=1;
        Bin_Image[i][j-1]=1;

    }
}
void showimage()
{
    for (short i = 0; i < LCDH; i++)
    {
        for (short j = 0; j < LCDW; j++)
        {
                Bin_Image[i][j] = Image_Line[i][j];
        }
    }
}

int Calc_ERROR(void)
{
    int Err=0;
    //�������
    for(int i=0;i<5;i++)
    {
        Err+=LCDW/2-Image_centralLine[Look_Line-Image_upLine];
    }
    Err = Err/5;
    return Err;
}

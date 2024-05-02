/*
 * My_Image_Handle.c
 *
 *  Created on: 2024��3��4��
 *      Author: dduu
 */
#include "My_Image_Handle.h"
#include "Image_Handle.h"

#define QianZhan 15

char data_txt[30];

extern unsigned char Bin_Image[LCDH][LCDW];
extern int Servo_Loc_error;


volatile uint8 Straight_Flag;        //ֱ����־
volatile uint8 Curve_Flag;           //�����־
volatile uint8 CrossWay_Flag;          //ʮ��·�ڱ�־
volatile uint8 Island_Flag;            //������־
volatile int White_Column[LCDW];//ÿ�а��г���
volatile int Longest_White_Column_Left[2];  //�洢�������е�������λ��
volatile int Longest_White_Column_Right[2]; //�洢�ұ�����е�������λ��
volatile int Search_Stop_Line;          //������ֹ�У��������������
volatile int Road_Wide[LCDH];           //�������
volatile int Left_Line[LCDH];           //��߽�
volatile int Right_Line[LCDH];          //�ұ߽�
volatile int Middle_Line[LCDH];         //�б߽�
volatile int Left_Lost_Flag[LCDH];      //�������飬0Ϊ�����ߣ�1Ϊ����
volatile int Right_Lost_Flag[LCDH];     //�Ҷ������飬0Ϊ�����ߣ�1Ϊ����
volatile uint8 Right_Island_Flag=0;     //�һ�����־
volatile uint8 Left_Island_Flag=0;      //�󻷵���־
volatile uint8 Island_State=0;          //����״̬��
volatile int Right_Lost_Time=0;        //�Ҷ�������
volatile int Left_Lost_Time=0;         //��������
volatile int Boundry_Start_Left=0;     //��ߵ�һ���Ƕ��ߵ�
volatile int Boundry_Start_Right=0;    //�ұߵ�һ���Ƕ��ߵ�
volatile int Both_Lost_Time=0;         //����ͬʱ������
volatile int Right_Down_Find;          //���¹յ�����
volatile int Left_Down_Find;           //���¹յ�����
volatile int Left_Up_Find;             //���Ϲյ�����
volatile int Right_Up_Find;            //���Ϲյ�����
volatile int Mon_change_Right_Line;     //�ҵ����仯��
volatile int monotonicity_change_line[2];  //�����仯�����
volatile int Right_Up_Guai[2];
volatile int island_state_3_up[2];
volatile float k;


//75 20 38

//˫�����Ѳ��,Ѱ��ͼ�����ұ߽磨��ȡ�������������Ѱ�ұ߽�ķ���)
void Longest_White_Column(void)
{
    int i,j;
    int start_column=20;//����е���������
    int end_column=LCDW-20;
    //�������ʹ��ǰ����
    Longest_White_Column_Left[0] = 0;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
    Longest_White_Column_Left[1] = 20;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
    Longest_White_Column_Right[0] = 0;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
    Longest_White_Column_Right[1] = 140;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��

    Right_Lost_Time = 0;        //�߽綪����
    Left_Lost_Time  = 0;
    Boundry_Start_Left  = 0;    //��һ���Ƕ��ߵ�,����߽���ʼ��
    Boundry_Start_Right = 0;
    Both_Lost_Time = 0;//����ͬʱ������

    for (i = 0; i <=LCDH-1; i++)//��������
    {
        Right_Lost_Flag[i] = 0;
        Left_Lost_Flag[i] = 0;
        Left_Line[i] = 0;
        Right_Line[i] = LCDW-1;
    }
    for(i=0;i<=LCDW-1;i++)
    {
        White_Column[i] = 0;
    }
//
////    //������Ҫ������з�Χ�����޶�
////    //����3״̬��Ҫ�ı������Ѱ�ҷ�Χ
////    if(Right_Island_Flag==1)//�һ�
////    {
////        if(Island_State==3)
////        {
////            start_column=40;
////            end_column=LCDW-20;
////        }
////    }
////    else if(Left_Island_Flag==1)//��
////    {
////        if(Island_State==3)
////        {
////            start_column=20;
////            end_column=LCDW-40;
////        }
////    }
//
//    //��ȡÿ�еİ�ɫ����
    for(i=start_column;i<=end_column;i++)
    {
        for(j=LCDH-1;j>=0;j--)
        {
            if(Bin_Image[j][i]==0)
            {
                break;
            }
            else
            {
                White_Column[i]++;
            }
        }
    }
    //����������������
    Longest_White_Column_Left[0] = 0;
    for(i=start_column;i<=end_column;i++)
    {
        if (Longest_White_Column_Left[0] < White_Column[i])//�������һ��
        {
            Longest_White_Column_Left[0] = White_Column[i];//��0���ǰ��г���
            Longest_White_Column_Left[1] = i;              //��1�����±꣬��j��
        }
    }
//    //���ҵ���������������
    Longest_White_Column_Right[0] = 0;      //��0���ǰ��г���
    for(i=end_column;i>=start_column;i--)//��������ע���������ҵ���������λ�þͿ���ͣ��
    {
        if (Longest_White_Column_Right[0] < White_Column[i])//�������һ��
        {
            Longest_White_Column_Right[0] = White_Column[i];//��0���ǰ��г���
            Longest_White_Column_Right[1] = i;              //��1�����±꣬��j��
        }
    }

    Search_Stop_Line = Longest_White_Column_Left[0];//������ֹ��ѡȡ����������𲻴�����������������һ����
//
//    //�쳣�������forѭ��Search_Stop_Line-1��Ŀ���Ƿ�ֹ����������оͼ�⵽���е��³�����ѭ����
//    //���Search_Stop_Line=0�Ļ��Ῠ������Ҫ-1
//    //bug:��������һ�е�ʱ��ͼ�⵽����
    for (i = LCDH - 1; i >= LCDH-Search_Stop_Line-1; i--)//����Ѳ��
    {
        //bug
        for (j = Longest_White_Column_Left[1]; j >= 0 + 2; j--)//�����ɨ��
        {//��������һ�У����ʵ��ҵ���Ч����Ұ��
            if (Bin_Image[i][j] ==1 && Bin_Image[i][j - 1] == 0 && Bin_Image[i][j - 2] == 0)//�ںڰ���Ϊ������߽�
            {
                Left_Line[i] = j;
                Left_Lost_Flag[i] = 0; //�������飬������1����������0
                break;
            }
            else if(j<=0+2)
            {
                Left_Line[i] = j;//�ҵ�ͷ��û�ҵ��ߣ��Ͱ���Ļ�����ҵ����߽�
                Left_Lost_Flag[i] = 1; //�������飬������1����������0
                break;
            }
        }
        //��������һ�У����ʵ��ҵ���Ч����Ұ��
        for (j = Longest_White_Column_Right[1]; j <= LCDW-1-2; j++)
        {
            if (Bin_Image[i][j] ==1 && Bin_Image[i][j + 1] == 0 && Bin_Image[i][j + 2] == 0)//�׺ںڣ��ҵ��ұ߽�
            {
                Right_Line[i] = j;
                Right_Lost_Flag[i] = 0; //�Ҷ������飬������1����������0
                break;
             }
             else if(j>=LCDW-1-2)//û�ҵ��ұ߽磬����Ļ���Ҹ�ֵ���ұ߽�
             {
                 Right_Line[i] = j;
                 Right_Lost_Flag[i] = 1; //�Ҷ������飬������1����������0
                 break;
             }
         }
     }

    for (i = LCDH - 1; i >= 0; i--)//�������ݳ�������
    {
        if (Left_Lost_Flag[i] == 1)//���߶�����
            Left_Lost_Time++;
        if (Right_Lost_Flag[i] == 1)
            Right_Lost_Time++;
        if (Left_Lost_Flag[i] == 1 && Right_Lost_Flag[i] == 1)//˫�߶�����
            Both_Lost_Time++;
        if (Boundry_Start_Left ==  0 && Left_Lost_Flag[i]  != 1)//��¼��һ���Ƕ��ߵ㣬�߽���ʼ��
            Boundry_Start_Left = i;
        if (Boundry_Start_Right == 0 && Right_Lost_Flag[i] != 1)
            Boundry_Start_Right = i;
        Road_Wide[i]=Right_Line[i]-Left_Line[i];
    }

////    //����3״̬�ı�߽磬���������������Ϊ�����ϵ���������ǲ���Ҫ��Щ�����
////    if(Island_State==3||Island_State==4)
////    {
////        if(Right_Island_Flag==1)//�һ�
////        {
////            for (i = LCDH - 1; i >= 0; i--)//�ұ�ֱ��д�ڱ���
////            {
////                Right_Line[i]=LCDW-1;
////            }
////        }
////        else if(Left_Island_Flag==1)//��
////        {
////            for (i = LCDH - 1; i >= 0; i--)//���ֱ��д�ڱ���
////            {
////                Left_Line[i]=0;      //�ұ���������
////            }
////        }
////    }

}

//����ʵ���������������ߵ������ڶ�����
float Err_Sum(void)
{
    int i;
    float Err=0;
    //�������
     for(i=95;i<=105;i++)
     {
         Err+=(LCDW/2-((Left_Line[i]+Right_Line[i])/2));//����1λ����Ч��2
     }
     Err = Err/10.0;
    return Err;
}

float Cal_Err(void)
{
    //ǰհ  ����ƫ��
    float Err=0;
    int Near=Middle_Line[110];
    int Mid=Middle_Line[110-QianZhan];
    int Far=Middle_Line[110-QianZhan*2];

    if(Near<Mid && Mid<Far)
    {
        Err=(Near+Mid+Far)/3.0;
        Err=(LCDW/2-Err);
    }
    else if(Near<Mid && Mid>Far)
    {
        Err=(Near+Mid)/2.0;
        Err=(LCDW/2-Err);
    }
    else if(Near>Mid && Mid>Far)
    {
        Err=(Near+Mid+Far)/3.0;
        Err=(LCDW/2-Err);
    }
    else if(Near>Mid && Mid<Far)
    {
        Err=(Near+Mid)/2.0;
        Err=(LCDW/2-Err);
    }
    else
    {
        Err=(Near+Mid+Far)/3.0;
        Err=(LCDW/2-Err);
    }

    return Err;
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ֱ�����
  @param     null
  @return    null
  Sample     Straight_Detect()��
  @note      ��������У��߽���ʼ�㣬������ʼ�㣬
-------------------------------------------------------------------------------------------------------------------*/
//void Straight_Detect(void)
//{
//    Straight_Flag=0;
//    if(Search_Stop_Line>=65)//��ֹ�к�Զ
//    {
//        if(Boundry_Start_Left>=68 && Boundry_Start_Right>=65)//��ʼ�㿿��
//        {
//            if(-5<=Servo_Loc_error && Servo_Loc_error<=5)//����С
//            {
//                Straight_Flag=1;//��Ϊ��ֱ��
//            }
//        }
//    }
//    else
//        Straight_Flag=0;
//}

//ֱ�����
void Straight_Detect(void)
{


}

//������
void Curve_Detect(void)
{
    Curve_Flag=0;
    if(Search_Stop_Line>=65)//��ֹ�к�Զ
    {
        if(Boundry_Start_Left>=68 && Boundry_Start_Right>=65)//��ʼ�㿿��
        {
            if(-5<=Servo_Loc_error && Servo_Loc_error<=5)//����С
            {
                Curve_Flag=1;//��Ϊ�����
            }
        }
    }
    else
        Curve_Flag=0;
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ������������յ㣬��ʮ��ʹ��
  @param     �����ķ�Χ��㣬�յ�
  @return    �޸�����ȫ�ֱ���
             Right_Down_Find=0;
             Left_Down_Find=0;
  Sample     Find_Down_Point(int start,int end)
  @note      ������֮��鿴��Ӧ�ı�����ע�⣬û�ҵ�ʱ��Ӧ��������0
-------------------------------------------------------------------------------------------------------------------*/
void Find_Down_Point(int start,int end)
{
    int i,t;
    Right_Down_Find=0;
    Left_Down_Find=0;
    if(start<end)
    {
        t=start;
        start=end;
        end=t;
    }
    if(start>=LCDH-1-5)//����5�����ݲ��ȶ���������Ϊ�߽�����жϣ�����
        start=LCDH-1-5;
    if(end<=LCDH-Search_Stop_Line)
        end=LCDH-Search_Stop_Line;
    if(end<=5)
       end=5;
    for(i=start;i>=end;i--)
    {
        if(Left_Down_Find==0&&//ֻ�ҵ�һ�����������ĵ�
            ABS(Left_Line[i]-Left_Line[i+1])<=5&&//�ǵ����ֵ���Ը���
            ABS(Left_Line[i+1]-Left_Line[i+2])<=5&&
            ABS(Left_Line[i+2]-Left_Line[i+3])<=5&&
              (Left_Line[i]-Left_Line[i-2])>=8&&
              (Left_Line[i]-Left_Line[i-3])>=15&&
              (Left_Line[i]-Left_Line[i-4])>=15)
        {
            Left_Down_Find=i;//��ȡ��������
        }
        if(Right_Down_Find==0&&//ֻ�ҵ�һ�����������ĵ�
           ABS(Right_Line[i]-Right_Line[i+1])<=5&&//�ǵ����ֵ���Ը���
           ABS(Right_Line[i+1]-Right_Line[i+2])<=5&&
           ABS(Right_Line[i+2]-Right_Line[i+3])<=5&&
              (Right_Line[i]-Right_Line[i-2])<=-8&&
              (Right_Line[i]-Right_Line[i-3])<=-15&&
              (Right_Line[i]-Right_Line[i-4])<=-15)
        {
            Right_Down_Find=i;
        }
        if(Left_Down_Find!=0&&Right_Down_Find!=0)//�����ҵ����˳�
        {
            break;
        }
    }
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ������������յ㣬��ʮ��ʹ��
  @param     �����ķ�Χ��㣬�յ�
  @return    �޸�����ȫ�ֱ���
             Left_Up_Find=0;
             Right_Up_Find=0;
  Sample     Find_Up_Point(int start,int end)
  @note      ������֮��鿴��Ӧ�ı�����ע�⣬û�ҵ�ʱ��Ӧ��������0
-------------------------------------------------------------------------------------------------------------------*/
void Find_Up_Point(int start,int end)
{
    int i,t;
    Left_Up_Find=0;
    Right_Up_Find=0;
    if(start<end)
    {
        t=start;
        start=end;
        end=t;
    }
    if(end<=LCDH-Search_Stop_Line)
        end=LCDH-Search_Stop_Line;
    if(end<=5)//��ʱ����зǳ�����ҲҪ�������ֵ㣬��ֹ����Խ��
        end=5;
    if(start>=LCDH-1-5)//����5�����ݲ��ȶ���������Ϊ�߽�����жϣ�����
        start=LCDH-1-5;
    for(i=start;i>=end;i--)
    {
        if(Left_Up_Find==0&&//ֻ�ҵ�һ�����������ĵ�
            ABS(Left_Line[i]-Left_Line[i-1])<=5&&
            ABS(Left_Line[i-1]-Left_Line[i-2])<=5&&
            ABS(Left_Line[i-2]-Left_Line[i-3])<=5&&
              (Left_Line[i]-Left_Line[i+2])>=8&&
              (Left_Line[i]-Left_Line[i+3])>=15&&
              (Left_Line[i]-Left_Line[i+4])>=15)
        {
            Left_Up_Find=i;//��ȡ��������
        }
        if(Right_Up_Find==0&&//ֻ�ҵ�һ�����������ĵ�
            ABS(Right_Line[i]-Right_Line[i-1])<=5&&//��������λ�ò��
            ABS(Right_Line[i-1]-Right_Line[i-2])<=5&&
            ABS(Right_Line[i-2]-Right_Line[i-3])<=5&&
              (Right_Line[i]-Right_Line[i+2])<=-8&&
              (Right_Line[i]-Right_Line[i+3])<=-15&&
              (Right_Line[i]-Right_Line[i+4])<=-15)
        {
            Right_Up_Find=i;//��ȡ��������
        }
        if(Left_Up_Find!=0&&Right_Up_Find!=0)//���������ҵ��ͳ�ȥ
        {
            break;
        }
    }
    if(abs(Right_Up_Find-Left_Up_Find)>=30)//����˺�ѹ�����Ϊ����
    {
        Right_Up_Find=0;
        Left_Up_Find=0;
    }
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ����
  @param     ���ߵ���㣬�յ�
  @return    null
  Sample     Left_Add_Line(int x1,int y1,int x2,int y2);
  @note      ����ֱ���Ǳ߽磬������ǿ��Ŷȸߵ�,��Ҫ�Ҳ�
-------------------------------------------------------------------------------------------------------------------*/
void Left_Add_Line(int x1,int y1,int x2,int y2)     //����,�����Ǳ߽�
{
    int i,max,a1,a2;
    int hx;
    if(x1>=LCDW-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
       x1=LCDW-1;
    else if(x1<=0)
       x1=0;
    if(y1>=LCDH-1)
       y1=LCDH-1;
    else if(y1<=0)
       y1=0;
    if(x2>=LCDW-1)
       x2=LCDW-1;
    else if(x2<=0)
       x2=0;
    if(y2>=LCDH-1)
       y2=LCDH-1;
    else if(y2<=0)
       y2=0;
    a1=y1;
    a2=y2;
    if(a1>a2)//���껥��
    {
        max=a1;
        a1=a2;
        a2=max;
    }
    //������bug���·�ѭ��++ѭ����ֻ����y�Ļ���������û�н���x�Ļ���
    //��������жϣ�����a1��a2�Ĵ�С��ϵ������++����--����
    //�����޸ĸ�λ���в���
    for(i=a1;i<=a2;i++)//����б�ʲ��߼���
    {
        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
        if(hx>=LCDW)
            hx=LCDW;
        else if(hx<=0)
            hx=0;
        Left_Line[i]=hx;
    }
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief     �Ҳ���
  @param     ���ߵ���㣬�յ�
  @return    null
  Sample     Left_Add_Line(int x1,int y1,int x2,int y2);
  @note      ����ֱ���Ǳ߽磬������ǿ��Ŷȸߵ�,��Ҫ�Ҳ�
-------------------------------------------------------------------------------------------------------------------*/
void Right_Add_Line(int x1,int y1,int x2,int y2)     //�Ҳ���,�����Ǳ߽�
{
    int i,max,a1,a2;
    int hx;
    if(x1>=LCDW-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
       x1=LCDW-1;
    else if(x1<=0)
       x1=0;
    if(y1>=LCDH-1)
       y1=LCDH-1;
    else if(y1<=0)
       y1=0;
    if(x2>=LCDW-1)
       x2=LCDW-1;
    else if(x2<=0)
       x2=0;
    if(y2>=LCDH-1)
       y2=LCDH-1;
    else if(y2<=0)
       y2=0;
    a1=y1;
    a2=y2;
    if(a1>a2)//���껥��
    {
        max=a1;
        a1=a2;
        a2=max;
    }
    //������bug���·�ѭ��++ѭ����ֻ����y�Ļ���������û�н���x�Ļ���
    //��������жϣ�����a1��a2�Ĵ�С��ϵ������++����--����
    //�����޸ĸ�λ���в���
    for(i=a1;i<=a2;i++)//����б�ʲ��߼���
    {
        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
        if(hx>=LCDW)
            hx=LCDW;
        else if(hx<=0)
            hx=0;
        Right_Line[i]=hx;
    }
}

int count=0;

void Cross_Detect(void)
{
    count++;
    int down_search_start=0;//�½ǵ�������ʼ��
    CrossWay_Flag=0;
    if(Island_Flag==0)//�뻷�����⿪
    {
        Left_Up_Find=0;
        Right_Up_Find=0;
        if(Both_Lost_Time>=10)//ʮ�ֱض���˫�߶��ߣ�����˫�߶��ߵ�������ٿ�ʼ�ҽǵ�
        {
            Find_Up_Point( LCDH-1, 0 );
            if(Left_Up_Find==0 && Right_Up_Find==0)//ֻҪû��ͬʱ�ҵ������ϵ㣬ֱ�ӽ���
            {
                return;
            }
        }
        if(Left_Up_Find!=0 && Right_Up_Find!=0)//�ҵ������ϵ㣬����Ϊ�ҵ�ʮ����
        {
            CrossWay_Flag=1;//ȷ����Ӧ��־λ�����ڸ�Ԫ�ػ����
            down_search_start=Left_Up_Find>Right_Up_Find?Left_Up_Find:Right_Up_Find;//�������Ϲյ����꿿������Ϊ�µ����������
            Find_Down_Point(LCDH-5,down_search_start+2);//���Ϲյ���2����Ϊ�½ǵ�Ľ�ֹ��
            if(Left_Down_Find<=Left_Up_Find)
            {
                Left_Down_Find=0;//�µ㲻���ܱ��ϵ㻹����
            }
            if(Right_Down_Find<=Right_Up_Find)
            {
                Right_Down_Find=0;//�µ㲻���ܱ��ϵ㻹����
            }
            if(Left_Down_Find!=0&&Right_Down_Find!=0)
            {//�ĸ��㶼�ڣ��������ߣ����������Ȼ����
                Left_Add_Line (Left_Line[Left_Up_Find],Left_Up_Find ,Left_Line[Left_Down_Find] ,Left_Down_Find);
                Right_Add_Line(Right_Line[Right_Up_Find],Right_Up_Find,Right_Line[Right_Down_Find],Right_Down_Find);
            }
            else if(Left_Down_Find==0&&Right_Down_Find!=0)//11//����ʹ�õ���б�ʲ���
            {//������                                     //01
                Lengthen_Left_Boundry(Left_Up_Find-1,LCDH-1);
                Right_Add_Line(Right_Line[Right_Up_Find],Right_Up_Find,Right_Line[Right_Down_Find],Right_Down_Find);
            }
            else if(Left_Down_Find!=0&&Right_Down_Find==0)//11
            {//������                                      //10
                Left_Add_Line (Left_Line [Left_Up_Find ],Left_Up_Find ,Left_Line [Left_Down_Find ] ,Left_Down_Find);
                Lengthen_Right_Boundry(Right_Up_Find-1,LCDH-1);
            }
            else if(Left_Down_Find==0 && Right_Down_Find==0)//11
            {//�����ϵ�                                    //00
                Lengthen_Left_Boundry (Left_Up_Find-1,LCDH-1);
                Lengthen_Right_Boundry(Right_Up_Find-1,LCDH-1);
            }
        }
        else
        {
            CrossWay_Flag=0;
        }
    }

}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ����߽��ӳ�
  @param     �ӳ���ʼ�������ӳ���ĳ��
  @return    null
  Sample     Lengthen_Right_Boundry(int start,int end)��
  @note      ����ʼ��������3���㣬���б�ʣ������ӳ���ֱ��������
-------------------------------------------------------------------------------------------------------------------*/
void Lengthen_Left_Boundry(int start,int end)
{
    int i,t;
    float k=0;
    if(start>=LCDH-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
        start=LCDH-1;
    else if(start<=0)
        start=0;
    if(end>=LCDH-1)
        end=LCDH-1;
    else if(end<=0)
        end=0;
    if(end<start)//++���ʣ����껥��
    {
        t=end;
        end=start;
        start=t;
    }
    //������bug���·�ѭ��++ѭ����ֻ����y�Ļ���������û�н���x�Ļ���
    //��������жϣ�����a1��a2�Ĵ�С��ϵ������++����--����
    //�����޸ĸ�λ���в���
    if(start<=5)//��Ϊ��Ҫ�ڿ�ʼ��������3���㣬������ʼ����ڿ��ϣ��������ӳ���ֻ��ֱ������
    {
        Left_Add_Line(Left_Line[start],start,Left_Line[end],end);
    }
    else
    {
        k=(float)(Left_Line[start]-Left_Line[start-4])/5.0;//�����k��1/б��
        for(i=start;i<=end;i++)
        {
            Left_Line[i]=(int)(i-start)*k+Left_Line[start];//(x=(y-y1)*k+x1),��бʽ����
            if(Left_Line[i]>=LCDW-1)
            {
                Left_Line[i]=LCDW-1;
            }
            else if(Left_Line[i]<=0)
            {
                Left_Line[i]=0;
            }
        }
    }
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ����߽��ӳ�
  @param     �ӳ���ʼ�������ӳ���ĳ��
  @return    null
  Sample     Lengthen_Right_Boundry(int start,int end)��
  @note      ����ʼ��������3���㣬���б�ʣ������ӳ���ֱ��������
-------------------------------------------------------------------------------------------------------------------*/
void Lengthen_Right_Boundry(int start,int end)
{
    int i,t;
    float k=0;
    if(start>=LCDH-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
        start=LCDH-1;
    else if(start<=0)
        start=0;
    if(end>=LCDH-1)
        end=LCDH-1;
    else if(end<=0)
        end=0;
    if(end<start)//++���ʣ����껥��
    {
        t=end;
        end=start;
        start=t;
    }
    //������bug���·�ѭ��++ѭ����ֻ����y�Ļ���������û�н���x�Ļ���
    //��������жϣ�����a1��a2�Ĵ�С��ϵ������++����--����
    //�����޸ĸ�λ���в���
    if(start<=5)//��Ϊ��Ҫ�ڿ�ʼ��������3���㣬������ʼ����ڿ��ϣ��������ӳ���ֻ��ֱ������
    {
        Right_Add_Line(Right_Line[start],start,Right_Line[end],end);
    }
    else
    {
        k=(float)(Right_Line[start]-Right_Line[start-4])/5.0;//�����k��1/б��
        for(i=start;i<=end;i++)
        {
            Right_Line[i]=(int)(i-start)*k+Right_Line[start];//(x=(y-y1)*k+x1),��бʽ����
            if(Right_Line[i]>=LCDW-1)
            {
                Right_Line[i]=LCDW-1;
            }
            else if(Right_Line[i]<=0)
            {
                Right_Line[i]=0;
            }
        }
    }
}

void Lengthen_Right_Boundry_Down(int start,int end)
{
    int i,t;
    float k=0;
    if(start>=LCDH-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
        start=LCDH-1;
    else if(start<=0)
        start=0;
    if(end>=LCDH-1)
        end=LCDH-1;
    else if(end<=0)
        end=0;
    if(end<start)//++���ʣ����껥��
    {
        t=end;
        end=start;
        start=t;
    }
    //������bug���·�ѭ��++ѭ����ֻ����y�Ļ���������û�н���x�Ļ���
    //��������жϣ�����a1��a2�Ĵ�С��ϵ������++����--����
    //�����޸ĸ�λ���в���
    if(start<=5)//��Ϊ��Ҫ�ڿ�ʼ��������3���㣬������ʼ����ڿ��ϣ��������ӳ���ֻ��ֱ������
    {
        Right_Add_Line(Right_Line[start],start,Right_Line[end],end);
    }
    else  //С����:�����ʼ�й��͵Ļ������������л��ѵ�������
    {
        k=(float)(Right_Line[start]-Right_Line[start+4])/4.0;//�����k��1/б��
        for(i=start;i<=end;i++)
        {
            Right_Line[i]=(int)(i-start)*k+Right_Line[start];//(x=(y-y1)*k+x1),��бʽ����
            if(Right_Line[i]>=LCDW-1)
            {
                Right_Line[i]=LCDW-1;
            }
            else if(Right_Line[i]<=0)
            {
                Right_Line[i]=0;
            }
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief     ���½ǵ���
  @param     ��ʼ�㣬��ֹ��
  @return    ���ؽǵ����ڵ��������Ҳ�������0
  Sample     Find_Right_Down_Point(int start,int end);
  @note      �ǵ�����ֵ�ɸ���ʵ��ֵ����
-------------------------------------------------------------------------------------------------------------------*/
int Find_Right_Down_Point(int start,int end)//���ĸ��ǵ㣬����ֵ�ǽǵ����ڵ�����
{
    int i,t;
    int right_down_line=0;
    if(Right_Lost_Time>=0.9*LCDH)//�󲿷ֶ����ߣ�û�йյ��жϵ�����
        return right_down_line;
    if(start<end)
    {
        t=start;
        start=end;
        end=t;
    }
    if(start>=LCDH-1-5)//����5�����ݲ��ȶ���������Ϊ�߽�����жϣ�����
        start=LCDH-1-5;
    if(end<=LCDH-Search_Stop_Line)
        end=LCDH-Search_Stop_Line;
    if(end<=5)
       end=5;
    for(i=start;i>=end;i--)
    {
        if(right_down_line==0 && //ֻ�ҵ�һ�����������ĵ�
           ABS(Right_Line[i]-Right_Line[i+1])<=5 &&  //�ǵ����ֵ���Ը���
           ABS(Right_Line[i+1]-Right_Line[i+2])<=5 &&
           ABS(Right_Line[i+2]-Right_Line[i+3])<=5 &&
              (Right_Line[i]-Right_Line[i-2])<=-5 &&
              (Right_Line[i]-Right_Line[i-3])<=-10 &&
              (Right_Line[i]-Right_Line[i-4])<=-10)
        {
            right_down_line=i;//��ȡ��������
            break;
        }
    }
    return right_down_line;
}


int Find_Right_Up_Point(int start,int end)//���ĸ��ǵ㣬����ֵ�ǽǵ����ڵ�����
{
    int i,t;
    int right_up_line=0;
    if(Right_Lost_Time>=0.9*LCDH)//�󲿷ֶ����ߣ�û�йյ��жϵ�����
        return right_up_line;
    if(start<end)
    {
        t=start;
        start=end;
        end=t;
    }
    if(start>=LCDH-1-5)//����5�����ݲ��ȶ���������Ϊ�߽�����жϣ�����
        start=LCDH-1-5;
    if(end<=LCDH-Search_Stop_Line)
        end=LCDH-Search_Stop_Line;
    if(end<=5)
       end=5;
    for(i=start;i>=end;i--)
    {
        if(right_up_line==0 &&//ֻ�ҵ�һ�����������ĵ�
            ABS(Right_Line[i]-Right_Line[i-1])<=5&&//��������λ�ò��
            ABS(Right_Line[i-1]-Right_Line[i-2])<=5&&
            ABS(Right_Line[i-2]-Right_Line[i-3])<=5&&
              (Right_Line[i]-Right_Line[i+2])<=-8&&
              (Right_Line[i]-Right_Line[i+3])<=-15&&
              (Right_Line[i]-Right_Line[i+4])<=-15)
        {
            right_up_line=i;//��ȡ��������
            break;
        }
    }
    return right_up_line;
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief     �����������Լ��
  @param     ��ʼ�㣬��ֹ��
  @return    ��������0�����������ض��߳�����
  Sample     continuity_change_flag=Continuity_Change_Right(int start,int end)
  @note      �����Ե���ֵ����Ϊ5���ɸ���
-------------------------------------------------------------------------------------------------------------------*/
int Continuity_Change_Right(int start,int end)
{
    int i;
    int t;
    int continuity_change_flag=0;
    if(Right_Lost_Time>=0.9*LCDH)//�󲿷ֶ����ߣ�û��Ҫ�ж���
       return 1;
    if(start>=LCDH-5)//����Խ�籣��
        start=LCDH-5;
    if(end<=5)
       end=5;
    if(start<end)//���Ǵ������ϼ���ģ����˾ͻ���һ��
    {
       t=start;
       start=end;
       end=t;
    }

    for(i=start;i>=end;i--)
    {
        if(ABS(Right_Line[i]-Right_Line[i-1])>=5)//��������ֵ��5���ɸ���
       {
            continuity_change_flag=i;
            break;
       }
    }
    return continuity_change_flag;
}

int Continuity_Change_Left(int start,int end)
{
    int i;
    int t;
    int continuity_change_flag=0;
    if(Left_Lost_Time>=0.9*LCDH)//�󲿷ֶ����ߣ�û��Ҫ�ж���
       return 1;
    if(start>=LCDH-5)//����Խ�籣��
        start=LCDH-5;
    if(end<=5)
       end=5;
    if(start<end)//���Ǵ������ϼ���ģ����˾ͻ���һ��
    {
       t=start;
       start=end;
       end=t;
    }

    for(i=start;i>=end;i--)
    {
        if(ABS(Left_Line[i]-Left_Line[i-1])>=5)//��������ֵ��5���ɸ���
       {
            continuity_change_flag=i;
            break;
       }
    }
    return continuity_change_flag;
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief     ������ͻ����
  @param     ��ʼ�㣬��ֹ��
  @return    �����ڵ��������Ҳ�������0
  Sample     Find_Right_Up_Point(int start,int end);
  @note      ǰ5��5�������С�����������ǽǵ�
-------------------------------------------------------------------------------------------------------------------*/
int Monotonicity_Change_Right(int start,int end)//�����Ըı䣬����ֵ�ǵ����Ըı�����ڵ�����
{
    int i;
    int monotonicity_change_line=0;

    if(Right_Lost_Time>=0.9*LCDH)//�󲿷ֶ����ߣ�û�е������жϵ�����
       return monotonicity_change_line;
    if(start>=LCDH-1-5)//����Խ�籣��
       start=LCDH-1-5;
    if(end<=5)
       end=5;

    if(start<end)//���Ǵ������ϼ���ģ����˾ͻ���һ��
    {
        int t;
        t=start;
        start=end;
        end=t;
    }

    for(i=start;i>=end;i--)//���ȡǰ5��5���ݣ�����ǰ������뷶Χ��Ҫ��
    {
        if(Right_Line[i]==Right_Line[i+5]&&Right_Line[i]==Right_Line[i-5]&&
        Right_Line[i]==Right_Line[i+4]&&Right_Line[i]==Right_Line[i-4]&&
        Right_Line[i]==Right_Line[i+3]&&Right_Line[i]==Right_Line[i-3]&&
        Right_Line[i]==Right_Line[i+2]&&Right_Line[i]==Right_Line[i-2]&&
        Right_Line[i]==Right_Line[i+1]&&Right_Line[i]==Right_Line[i-1])
        {//һ������һ������Ȼ������Ϊ����ת�۵�
            continue;
        }
        else if(Right_Line[i] <Right_Line[i+5]&&Right_Line[i] <Right_Line[i-5]&&
        Right_Line[i] <Right_Line[i+4]&&Right_Line[i] <Right_Line[i-4]&&
        Right_Line[i]<=Right_Line[i+3]&&Right_Line[i]<=Right_Line[i-3]&&
        Right_Line[i]<=Right_Line[i+2]&&Right_Line[i]<=Right_Line[i-2]&&
        Right_Line[i]<=Right_Line[i+1]&&Right_Line[i]<=Right_Line[i-1])
        {//�ͺܱ����������������ǰ5����5�����ģ��Ǿ��ǵ���ͻ���
            monotonicity_change_line=i;
            break;
        }
    }
    return monotonicity_change_line;
}


/*-------------------------------------------------------------------------------------------------------------------
  @brief     ͨ��б�ʣ����㲹��--
  @param     k       ����б��
             startY  ������ʼ��������
             endY    ������������
  @return    null
  Sample     K_Add_Boundry_Left(float k,int startY,int endY);
  @note      ������ֱ�����ڱ�����
-------------------------------------------------------------------------------------------------------------------*/
void K_Add_Boundry_Left(float k,int startX,int startY,int endY)
{
    int i,t;
    if(startY>=LCDH-1)
        startY=LCDH-1;
    else if(startY<=0)
        startY=0;
    if(endY>=LCDH-1)
        endY=LCDH-1;
    else if(endY<=0)
        endY=0;
    if(startY<endY)//--������start��Ҫ��
    {
        t=startY;
        startY=endY;
        endY=t;
    }
    //������bug���·�ѭ��--ѭ������ҪstartҪ��ֻ����y�Ļ���������û�н���x�Ļ���
    //��������жϣ����start��С���Ǿͽ���++����
    //�����޸ĸ�λ���в���
    for(i=startY;i>=endY;i--)
    {
        Left_Line[i]=(int)((i-startY)/k+startX);//(y-y1)=k(x-x1)���Σ�x=(y-y1)/k+x1
        if(Left_Line[i]>=LCDW-1)
        {
            Left_Line[i]=LCDW-1;
        }
        else if(Left_Line[i]<=0)
        {
            Left_Line[i]=0;
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief     ����б�ʻ���
  @param     ����б�ʣ����㣬��һ������
  @return    null
  Sample     K_Draw_Line(k, 20,MT9V03X_H-1 ,0)
  @note      ���ľ���һ���ߣ���Ҫ����ɨ��
-------------------------------------------------------------------------------------------------------------------*/
void K_Draw_Line(float k, int startX, int startY,int endY)
{
    int endX=0;

    if(startX>=LCDW-1)//�޷�����
        startX=LCDW-1;
    else if(startX<=0)
        startX=0;
    if(startY>=LCDH-1)
        startY=LCDH-1;
    else if(startY<=0)
        startY=0;
    if(endY>=LCDH-1)
        endY=LCDH-1;
    else if(endY<=0)
        endY=0;

    endX=(int)((endY-startY)/k+startX);//(y-y1)=k(x-x1)���Σ�x=(y-y1)/k+x1
    Draw_Line(startX,startY,endX,endY);
}

/*-------------------------------------------------------------------------------------------------------------------
  @brief     ����
  @param     ������ʼ�㣬�յ����꣬��һ�����Ϊ2�ĺ���
  @return    null
  Sample     Draw_Line(0, 0,MT9V03X_W-1,MT9V03X_H-1);
             Draw_Line(MT9V03X_W-1, 0,0,MT9V03X_H-1);
                                    ��һ�����
  @note     ���ľ���һ���ߣ���Ҫ����ɨ��
-------------------------------------------------------------------------------------------------------------------*/
void Draw_Line(int startX, int startY, int endX, int endY)
{
    int i,x,y;
    int start=0,end=0;
    if(startX>=LCDW-1)//�޷�����
        startX=LCDW-1;
    else if(startX<=0)
        startX=0;
    if(startY>=LCDH-1)
        startY=LCDH-1;
    else if(startY<=0)
        startY=0;
    if(endX>=LCDW-1)
        endX=LCDW-1;
    else if(endX<=0)
        endX=0;
    if(endY>=LCDH-1)
        endY=LCDH-1;
    else if(endY<=0)
        endY=0;

    if(startX==endX)//һ������
    {
        if (startY > endY)//����
        {
            start=endY;
            end=startY;
        }
        for (i = start; i <= end; i++)
        {
            if(startX<=1)
                startX=1;
            Bin_Image[i][startX]=0;
            Bin_Image[i][startX-1]=0;
        }
    }
    else if(startY == endY)//��һ������
    {
        if (startX > endX)//����
        {
            start=endX;
            end=startX;
        }
        for (i = start; i <= end; i++)
        {
            if(startY<=1)
                startY=1;
            Bin_Image[startY][i]=0;
            Bin_Image[startY-1][i]=0;
        }
    }
    else //����������ˮƽ����ֱ��������������ǳ������
    {
        if(startY>endY)//��ʼ�����
        {
            start=endY;
            end=startY;
        }
        else
        {
            start=startY;
            end=endY;
        }
        for (i = start; i <= end; i++)//�����ߣ���֤ÿһ�ж��кڵ�
        {
            x =(int)(startX+(endX-startX)*(i-startY)/(endY-startY));//����ʽ����
            if(x>=LCDW-1)
                x=LCDW-1;
            else if (x<=1)
                x=1;
            Bin_Image[i][x] = 0;
            Bin_Image[i][x-1] = 0;
        }
        if(startX>endX)
        {
            start=endX;
            end=startX;
        }
        else
        {
            start=startX;
            end=endX;
        }
        for (i = start; i <= end; i++)//�����ߣ���֤ÿһ�ж��кڵ�
        {
            y =(int)(startY+(endY-startY)*(i-startX)/(endX-startX));//����ʽ����
            if(y>=LCDH-1)
                y=LCDH-1;
            else if (y<=0)
                y=0;
            Bin_Image[y][i] = 0;
        }
    }
}

void Island_Detect(void)
{
    Island_Flag=0;
    if(CrossWay_Flag==0)
    {
        if(Island_State==0)
        {
            Right_Down_Find=Find_Right_Down_Point(LCDH-5,50);
            if(Right_Lost_Time>=20 && Right_Lost_Time-Left_Lost_Time>=10 && Search_Stop_Line>=80 &&
                    Boundry_Start_Left>=80 && Boundry_Start_Right>=80 && Right_Down_Find!=0)
            {
                 Island_State=1;
            }
        }
        else if(Island_State==1)
        {
            Right_Down_Find=Find_Right_Down_Point(LCDH-5,50);
            Mon_change_Right_Line=Monotonicity_Change_Right(Right_Down_Find-5,0);
            if(Mon_change_Right_Line!=0)
            {
                //����
                Right_Add_Line(Right_Line[Mon_change_Right_Line],Mon_change_Right_Line,Right_Line[Right_Down_Find],Right_Down_Find);
            }
            else
            {
                Lengthen_Right_Boundry_Down(Right_Down_Find+1,Right_Down_Find+30);
            }

            if(Boundry_Start_Right<=60 && Right_Down_Find==0 && Mon_change_Right_Line!=0 && Right_Lost_Time>=60)
            {
                Island_State=2;
            }
        }
        else if(Island_State==2)
        {
            if(Mon_change_Right_Line!=0)
            {
                monotonicity_change_line[0]=Monotonicity_Change_Right(70,5);//�����Ըı�
                monotonicity_change_line[1]=Right_Line[monotonicity_change_line[0]];
                Right_Add_Line((int)(LCDW-1-(monotonicity_change_line[1]*0.15)),LCDH-1,monotonicity_change_line[1],monotonicity_change_line[0]);
                if((Boundry_Start_Right>=LCDH-5||monotonicity_change_line[0]>50) && monotonicity_change_line[0]==0)//���½��ٲ����߽�3
                {
                    Island_State=3;//�·����ߣ�˵�������Ѿ�������
                }

            }
        }
        else if(Island_State==3)
        {
//            Find_Up_Point(70,5);
//            if(Right_Up_Find!=0)
//            {
//
//            }
            if(k!=0)//�Ѿ��ҵ����ˣ���һ������
            {
                K_Draw_Line(k,30,LCDH-1,0);
                Longest_White_Column();//ˢ�������
            }
            else//�����ҵ�
            {
                Right_Up_Guai[0]=Find_Right_Up_Point(40,10);//�����Ϲյ�
                Right_Up_Guai[1]=Right_Line[Right_Up_Guai[0]];
                if(Right_Up_Guai[0]<10)//�ǵ�λ�ò��ԣ��˳�����
                {
                    Island_State=0;
                    Right_Island_Flag=0;
                }
                if(k==0&&(15<=Right_Up_Guai[0]&&Right_Up_Guai[0]<50)&&(70<Right_Up_Guai[1]&&Right_Up_Guai[1]<150))
                {//���ǵ�����ڸ�����Χ��
                    island_state_3_up[0]= Right_Up_Guai[0];
                    island_state_3_up[1]= Right_Up_Guai[1];
                    k=(float)((float)(LCDH-island_state_3_up[0])/(float)(20-island_state_3_up[1]));
                    K_Draw_Line(k,30,LCDH-1,0);
                    Longest_White_Column();//ˢ����������
                }
            }
//            if((Island_State==3)&&(abs(FJ_Angle)>=60))//ֻ���������ǻ���
//            {
//                k=0;//б������
//                Island_State=4;
//                Longest_White_Column();//�����
//            }
        }
    }

}


/*
 * image.c
 *
 *  Created on: 2024年4月16日
 *      Author: Macation
 */
#include "image1.h"

#define Image_downLine 115
#define Image_upLine 20
#define Array_Length MT9V034_IMAGEH/2+MT9V034_IMAGEW/2
#define Image_Length Image_downLine-Image_upLine

int Left_num=Array_Length;
int Right_num=Array_Length;
int dir_left[4];//左边线生长信息
int dir_right[4];//右边线生长信息

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
unsigned char Image_Line[120][188];  //存放提取边线后的图像数据
unsigned char Image_centralLine[Image_Length];//中线数组
int InterPoint[2];

/*************************************************************************
*  函数名称：int Image_Threshold_Line(int Y)
*  功能说明：对单行找阈值
*  函数返回：无
*  修改时间：2023年6月15日
*  备    注：
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
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    int MinValue, MaxValue;
    int Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for(i=0;i<MT9V034_IMAGEW;i++)
    {
        HistoGram[Image_Data[Y][i]]++;
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++)
        ;        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MaxValue] == 0;
            MaxValue--)
        ; //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++) {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++) {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore)
                * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
                {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}
/*************************************************************************
*  函数名称：int Image_Findline_Lefthand(int X,int Y,int *num)
*  参数说明：  X和Y是上一步寻找到的左边线起始点； num是边线数组的长度
*  功能说明：左手迷宫巡线
*  函数返回：无
*  修改时间：2023年4月12日
*  备    注：
*************************************************************************/
int Image_Findline_Lefthand(int X,int Y,int num)
{
    int dx,dy;
    int block_size=7;//每一个边线的点用7*7的方块进行自适应二值化
    int clip_value=0;//阈值裁剪量
    int half = block_size/2;
    int step=0,dir=0,turn=0;
    //循环，确定点(X,Y)在合适范围内，方可使用7*7自适应
    while(step < num && half < X && X < 188-half-1 && half < Y && Y < 120-half-1 && turn < 4)
    {
        signed long local_thres=0;//自适应阈值
        for(dy=-half; dy<=half; dy++)
        {
            for(dx=-half; dx<= half; dx++)
            {
                local_thres+=Image_Data[Y+dy][X+dx];
            }
        }
        local_thres /= block_size*block_size;
        local_thres -=clip_value;
        //左手摸墙走迷宫
        int front_value = Image_Data[Y+dir_front[dir][1]][X+dir_front[dir][0]];
        int frontleft_value = Image_Data[Y+dir_frontleft[dir][1]][X+dir_frontleft[dir][0]];
        if(front_value < local_thres)
        {
            dir = (dir + 1)%4;
            turn ++;
        }
        else if(frontleft_value < local_thres)
        {   dir_left[dir]++;
            X += dir_front[dir][0];
            Y += dir_front[dir][1];
            Image_Lefthand_Line[step][0]=X;
            Image_Lefthand_Line[step][1]=Y;
            Image_Line[Y][X]=1;             //边界矩阵与边界数组二选一
            step++;
            turn=0;
        }else {

            X += dir_frontleft[dir][0];
            Y += dir_frontleft[dir][1];
            dir = (dir + 3)%4;
            Image_Lefthand_Line[step][0]=X;
            Image_Lefthand_Line[step][1]=Y;
            Image_Line[Y][X]=1;
            dir_left[dir]++;//边界矩阵与边界数组二选一
            step++;
            turn=0;
        }

    }
    return step;
}
/*************************************************************************
*  函数名称：int Image_findSeedBegin(Image_element* Ele, int thres)
*  功能说明：找种子的起始点函数
*  函数返回：无
*  修改时间：2023年4月23日
*  备    注：
*************************************************************************/
int Image_findSeedBegin(int thres)
{
    int i=0;
    for(i=93;i>2;i--)
    {
        if(Image_Data[Image_downLine][i-1]>thres && Image_Data[Image_downLine][i]>thres
                && Image_Data[Image_downLine][i+1]>thres)
        {
            return i;
        }
    }
    for(i=95;i<MT9V034_IMAGEW -2;i++)
    {
        if(Image_Data[Image_downLine][i-1]>thres && Image_Data[Image_downLine][i]>thres
                && Image_Data[Image_downLine][i+1]>thres)
        {
            return i;
        }
    }
    return MT9V034_IMAGEW/2;
}
/*************************************************************************
*  函数名称：int Image_Findline_Righthand(int X,int Y,int num)
*  参数说明： X和Y是上一步寻找到的右边线起始； num是边线数组的长度
*  功能说明：右手迷宫巡线
*  函数返回：无
*  修改时间：2023年4月12日
*  备    注：
*************************************************************************/
int Image_Findline_Righthand(int X,int Y,int num)
{
    int dx,dy;
    int block_size=7;//每一个边线的点用7*7的方块进行自适应二值化
    int clip_value=0;//阈值裁剪量
    int half = block_size/2;
    int step=0,dir=0,turn=0;
    //循环，确定点(X,Y)在合适范围内，方可使用7*7自适应

    while(step < num && half < X && X < MT9V034_IMAGEW-half-1 && half < Y && Y < MT9V034_IMAGEH-half-1 && turn < 4)
    {
        signed long local_thres=0;//自适应阈值
        for(dy=-half; dy<=half; dy++)
        {
            for(dx=-half; dx<= half; dx++)
            {
                local_thres+=Image_Data[Y+dy][X+dx];
            }
        }
        local_thres /= block_size*block_size;
        local_thres -=clip_value;

        //右手摸墙走迷宫
        int front_value = Image_Data[Y+dir_front[dir][1]][X+dir_front[dir][0]];
        int frontright_value = Image_Data[Y+dir_frontright[dir][1]][X+dir_frontright[dir][0]];
        if (front_value < local_thres) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (frontright_value < local_thres) {

            dir_right[dir]++;
            X += dir_front[dir][0];
            Y += dir_front[dir][1];
            Image_Righthand_Line[step][0] = X;
            Image_Righthand_Line[step][1] = Y;
            Image_Line[Y][X]=1;             //边界矩阵与边界数组二选一

            step++;
            turn = 0;
        } else {

            X += dir_frontright[dir][0];
            Y += dir_frontright[dir][1];
            dir = (dir + 1) % 4;
            Image_Righthand_Line[step][0] = X;
            Image_Righthand_Line[step][1] = Y;
            Image_Line[Y][X]=1;             //边界矩阵与边界数组二选一
            dir_right[dir]++;
            step++;
            turn = 0;
        }
    }
    return step;
}
/*************************************************************************
*  函数名称：void Image_SeedGrowing(void)
*  功能说明：用区域生长法找左右边线函数
*  函数返回：无
*  修改时间：2023年4月12日
*  备    注：
*
*************************************************************************/
int Image_SeedGrowing(void)
{
    int threshold=0;
    memset(Image_Line,0,sizeof(Image_Line));
    memset(dir_left,0,sizeof(dir_left));
    memset(dir_right,0,sizeof(dir_right));
    threshold=Image_Threshold_Line(115);
    if(threshold==0)//失败
    {
        return -1;
    }
    //设定左右边线长度
    Left_num=Array_Length;
    Right_num=Array_Length;
    int X1=Image_findSeedBegin(threshold);
    int Y1=Image_downLine;
    int X2=X1;
    int Y2=Y1;
    //扫描边线时每一行的起点
    //初始化起始点

    //先从起始点向左寻找左边界的跳变点
    for(; X1>0; X1--)
    {
        if(Image_Data[Y1][X1-1] < threshold)
        {

            break;
        }
    }
    Left_num=Image_Findline_Lefthand(X1,Y1,Left_num);

    //再从起始点向右寻找右边界的跳变点
    for(; X2<MT9V034_IMAGEW -1; X2++)
    {
        if(Image_Data[Y2][X2+1] < threshold)
          {

            break;
          }
    }
    Right_num=Image_Findline_Righthand(X2,Y2,Right_num);
    if(Left_num<10 && Right_num<10)//寻边线失败
    {
        return -1;
    }
    Image_Line[Y1][X1]=1;
    Image_Line[Y1][X2]=1;
    Image_seedCentralline(X1,X2);
    //图像处理部分////
    //从X1和X2中得到车身的中心位置
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
*  函数名称：void Image_Frameprocessing()
*  功能说明:   将原图边框圈出来，为下一步边界生长做准备
*  函数返回：无
*  修改时间：2023年4月5日
*  备    注：
*************************************************************************/
void Image_Frameprocessing()
{
    for(int i=0;i<MT9V034_IMAGEH;i++)
    {
        Image_Data[i][3]=0;
        Image_Data[i][2]=0;
        Image_Data[i][MT9V034_IMAGEW-4]=0;
        Image_Data[i][MT9V034_IMAGEW-3]=0;
    }
}

/*************************************************************************
*  函数名称：void Image_seedCentralline(int X1,int X2)
*  参数说明： 左右边界的种子横坐标
*  功能说明：区域生长法找出边界后，扫线得中线
*  函数返回：无
*  修改时间：2023年4月23日
*  备    注：
*************************************************************************/
void Image_seedCentralline(int X1,int X2)
{
    unsigned char i,j;
//    unsigned char L1,L2,R1,R2;
    //扫描边线时每一行的起点
    unsigned char LeftStart=X1+5;
    unsigned char RightStart=X2-5;
    unsigned char Left[Image_Length]={0};
    unsigned char Right[Image_Length]={MT9V034_IMAGEW-1};
    for(i=Image_downLine-1;i>Image_upLine;i--)//由于生长法存的第一个点在Image_downLine上一行，所以取点也要在上一行
    {
        //防止起点超过图像范围
        if(RightStart>MT9V034_IMAGEW-1)
        {
            RightStart=MT9V034_IMAGEW-1;
        }
        if(LeftStart<0)
        {
            LeftStart=0;
        }
        //零阶保持，如果在该行未找到跳变点，则同上一个循环的结果保持一致
        if(i<Image_downLine-1)
        {
            Left[i-Image_upLine]=Left[i+1-Image_upLine];
            Right[i-Image_upLine]=Right[i+1-Image_upLine];

        }
        //扫左线，由于最后一行的起点在左种子附近，所以不从中间点开始找跳变
        for(j=LeftStart;j > 0;j--)
        {
            if(Image_Line[i][j]==1)//找到跳变点
            {
                Left[i-Image_upLine]=j;

                break;
            }
        }
        //扫右线，同左线相似
        for(j=RightStart;j< MT9V034_IMAGEW-1;j++)
        {
            if(Image_Line[i][j]==1)//找到跳变点
            {
                Right[i-Image_upLine]=j;

                break;
            }
        }
        //规划下一次的起点
        LeftStart=Left[i-Image_upLine]+10;
        RightStart=Right[i-Image_upLine]-10;

    }

    for(i=0;i<Image_Length;i++)
    {
        Image_centralLine[i]=(Left[i]+Right[i])/2;
        if(Image_Line[i+Image_upLine][Image_centralLine[i]]==1)//找到交点位置
        {
            InterPoint[1]=i+Image_upLine;//行
            InterPoint[0]=Image_centralLine[i];//列
        }
    }
    //在图像中画出中线
    for(i=Image_downLine-1;i>Image_upLine-1;i--)
    {
        j=Image_centralLine[i-Image_upLine];
        //加粗，两个像素点
        Image_Line[i][j]=1;
        Image_Line[i][j-1]=1;

    }
}
void showimage()
{
    for (short i = 0; i < LCDH; i++)
    {
        for (short j = 0; j < LCDW; j++)
        {
                Bin_Image[i][j] = Image_Line[i][j+14];
        }
    }

}

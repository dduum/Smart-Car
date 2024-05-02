/*
 * button.c
 *
 *  Created on: 2024年4月29日
 *      Author: dduu
 */
#include "button.h"

extern sMenu menu;

//有几个按键设置几个
int btnState[3] = {1,1,1};    //按键状态  0-按下  1-未按下
int btnFlag[3] = {0,0,0};     //防止按键重复检测

//获得所有按键状态
static void Button_GetAllState()
{
    btnState[0]=PIN_Read(KEY0_Pin);
    btnState[1]=PIN_Read(KEY1_Pin);
    btnState[2]=PIN_Read(KEY2_Pin);
}

//复位btnFlag
static void resetBtnFlag()   //?
{
    for(int i=0; i<3; i++){
        if(btnState[i]==BtnUp && btnFlag[i]==1){
            btnFlag[i] = 0;
        }
    }
}

//下一个
int isBtnN()
{
    if(btnState[BtnN]==BtnDown && btnFlag[BtnN]==0){
        btnFlag[BtnN] = 1;
        return 1;
    }
    return 0;
}

//确认键
int isBtnE()
{        //防止确认键和返回键同时按下出错
    if(btnState[BtnE]==BtnDown && btnState[BtnR]==BtnUp && btnFlag[BtnE]==0){
        btnFlag[BtnE] = 1;
        return 1;
    }
    return 0;
}

//返回键
int isBtnR()
{
    if(btnState[BtnR]==BtnDown && btnState[BtnE]==BtnUp && btnFlag[BtnR]==0){
        btnFlag[BtnR] = 1;
        return 1;
    }
    return 0;
}

int chooseBuf = 1;    //左右选择时不立即进入该菜单
int switch_flag=0;    //页面更新标志

/* 按键扫描 */
void Button_Scan(void)
{
    Button_GetAllState();

    switch(menu.mode1)
    {
        //主菜单
        case 0:
            if(isBtnE()){          //确认键
                switch_flag=1;
                menu.mode1 = chooseBuf; chooseBuf = 1;
            }else if(isBtnR()){    //返回键（主菜单不用）
            }else if(isBtnN()){    //右键
                switch_flag=1;
                if(chooseBuf<4)
                    chooseBuf++;
                else
                    chooseBuf=1;
            }
            break;
        /*
         * 二级菜单1  电机舵机启动
         */
        case 1:
            switch(menu.mode2)
            {
                /*
                 * 二级菜单选择 电机舵机启动关闭
                 */
                case 0:
                    if(isBtnE()){        //确认键
                        switch_flag=1;
                        menu.mode2 = chooseBuf; chooseBuf = 1;
                    }else if(isBtnR()){  //返回键
                        switch_flag=1;
                        chooseBuf = 1; menu.mode2 = 0; menu.mode1 = 0;
                    }else if(isBtnN()){  //右键
                        switch_flag=1;
                        if(chooseBuf<2) chooseBuf++;
                        else    chooseBuf=1;
                    }
                    break;
                /*
                 * 三级菜单1  App1
                 */
                case 1:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
                /*
                 * 三级菜单2  App2
                 */
                case 2:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                        switch_flag=1;
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
            }
            break;
        /*
         * 二级菜单2
         */
        case 2:
            switch(menu.mode2)
            {
                /*
                 * 二级菜单选择 摄像头
                 */
                case 0:
                    if(isBtnE()){        //确认键
                        switch_flag=1;
                        menu.mode2 = chooseBuf; chooseBuf = 1;
                    }else if(isBtnR()){  //返回键
                        switch_flag=1;
                        chooseBuf = 1; menu.mode2 = 0; menu.mode1 = 0;
                    }else if(isBtnN()){  //右键
                        switch_flag=1;
                        if(chooseBuf<2) chooseBuf++;
                        else    chooseBuf=1;
                    }
                    break;
                /*
                 * 三级菜单1  App1
                 */
                case 1:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                        switch_flag=1;
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
                /*
                 * 三级菜单2  App2
                 */
                case 2:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                        switch_flag=1;
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
            }
            break;
        /*
         * 二级菜单3    PID
         */
        case 3:
            switch(menu.mode2)
            {
                /*
                 * 二级菜单选择
                 */
                case 0:
                    if(isBtnE()){        //确认键
                        switch_flag=1;
                        menu.mode2 = chooseBuf; chooseBuf = 1;
                    }else if(isBtnR()){  //返回键
                        switch_flag=1;
                        chooseBuf = 1; menu.mode2 = 0; menu.mode1 = 0;
                    }else if(isBtnN()){  //右键
                        switch_flag=1;
                        if(chooseBuf<3) chooseBuf++;
                        else chooseBuf=1;
                    }
                    break;
                /*
                 * 三级菜单1  App1
                 */
                case 1:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
                /*
                 * 三级菜单2  App2
                 */
                case 2:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
                    /*
                     * 三级菜单3  App3
                     */
                case 3:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
            }
            break;
            /*
         * 二级菜单4    ENC
         */
        case 4:
            switch(menu.mode2)
            {
                /*
                 * 二级菜单选择
                 */
                case 0:
                    if(isBtnE()){        //确认键
                        switch_flag=1;
                        menu.mode2 = chooseBuf; chooseBuf = 1;
                    }else if(isBtnR()){  //返回键
                        switch_flag=1;
                        chooseBuf = 1; menu.mode2 = 0; menu.mode1 = 0;
                    }else if(isBtnN()){  //右键
                        switch_flag=1;
                        if(chooseBuf<1) chooseBuf++;
                        else chooseBuf=1;
                    }
                    break;
                /*
                 * 三级菜单1  App1
                 */
                case 1:
                    if(isBtnE()){         //确认键（App1中不需要确认键）
                    }else if(isBtnR()){   //返回键
                        switch_flag=1;
                        menu.mode2 = 0;
                    }else if(isBtnN()){   //右键（App1中不需要右键）
                    }
                    break;
            }
            break;
    }
    //复位btnFlag
    resetBtnFlag();
}




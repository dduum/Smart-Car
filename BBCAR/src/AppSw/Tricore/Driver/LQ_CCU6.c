/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 锟斤拷平    台锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟杰科硷拷TC264DA锟斤拷锟侥帮拷
 锟斤拷锟斤拷    写锟斤拷ZYF/chiusir
 锟斤拷E-mail  锟斤拷chiusir@163.com
 锟斤拷锟斤拷锟斤拷姹撅拷锟絍1.1 锟斤拷权锟斤拷锟叫ｏ拷锟斤拷位使锟斤拷锟斤拷锟斤拷锟斤拷系锟斤拷权
 锟斤拷锟斤拷锟斤拷锟铰★拷2020锟斤拷10锟斤拷28锟斤拷
 锟斤拷锟斤拷锟斤拷锟较拷慰锟斤拷锟斤拷械锟街凤拷锟�
 锟斤拷锟斤拷    站锟斤拷http:// www.lqist.cn
 锟斤拷锟皆憋拷锟斤拷锟教★拷http:// longqiu.taobao.com
 ------------------------------------------------
 锟斤拷dev.env.锟斤拷AURIX Development Studio1.2.2锟斤拷锟斤拷锟较版本
 锟斤拷Target 锟斤拷 TC264DA/TC264D
 锟斤拷Crystal锟斤拷 20.000Mhz
 锟斤拷SYS PLL锟斤拷 200MHz
 ________________________________________________________________
 锟斤拷锟斤拷iLLD_1_0_1_11_0锟阶诧拷锟斤拷锟�,

 使锟斤拷锟斤拷锟教碉拷时锟津，斤拷锟斤拷锟斤拷锟矫伙拷锌崭锟斤拷英锟斤拷路锟斤拷锟斤拷
 锟斤拷锟斤拷CIF为TC264DA锟斤拷锟斤拷锟解，锟斤拷锟斤拷锟侥达拷锟斤拷锟斤拷锟絋C264D
 锟斤拷锟斤拷默锟较筹拷始锟斤拷锟斤拷EMEM锟斤拷512K锟斤拷锟斤拷锟斤拷没锟绞癸拷锟絋C264D锟斤拷注锟酵碉拷EMEM_InitConfig()锟斤拷始锟斤拷锟斤拷锟斤拷锟斤拷
 锟斤拷锟斤拷锟斤拷\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c锟斤拷164锟斤拷锟斤拷锟揭★拷
 ________________________________________________________________

 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
 *  锟斤拷    注锟斤拷TC264 锟斤拷锟斤拷锟斤拷CCU6模锟斤拷  每锟斤拷模锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷  锟斤拷锟斤拷锟斤拷时锟斤拷锟叫讹拷
 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <LQ_CCU6.h>


IFX_INTERRUPT(CCU60_CH0_IRQHandler, CCU60_VECTABNUM, CCU60_CH0_PRIORITY);
IFX_INTERRUPT(CCU60_CH1_IRQHandler, CCU60_VECTABNUM, CCU60_CH1_PRIORITY);
IFX_INTERRUPT(CCU61_CH0_IRQHandler, CCU61_VECTABNUM, CCU61_CH0_PRIORITY);
IFX_INTERRUPT(CCU61_CH1_IRQHandler, CCU61_VECTABNUM, CCU61_CH1_PRIORITY);

/** CCU6锟叫讹拷CPU锟斤拷锟� */
const uint8 Ccu6IrqVectabNum[2] = {CCU60_VECTABNUM, CCU61_VECTABNUM};

/** CCU6锟叫讹拷锟斤拷锟饺硷拷 */
const uint8 Ccu6IrqPriority[4] = {CCU60_CH0_PRIORITY, CCU60_CH1_PRIORITY, CCU61_CH0_PRIORITY, CCU61_CH1_PRIORITY};

/** CCU6锟叫断凤拷锟斤拷锟斤拷锟斤拷址 */
const void *Ccu6IrqFuncPointer[4] = {&CCU60_CH0_IRQHandler, &CCU60_CH1_IRQHandler, &CCU61_CH0_IRQHandler,
        &CCU61_CH1_IRQHandler};

/***********************************************************************************************/
/********************************CCU6锟解部锟叫讹拷  锟斤拷锟斤拷锟斤拷******************************************/
/***********************************************************************************************/

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷void CCU60_CH0_IRQHandler(void)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷3锟斤拷30锟斤拷
 *  锟斤拷    注锟斤拷CCU60_CH0使锟矫碉拷锟叫断凤拷锟斤拷锟斤拷
 *************************************************************************/
void CCU60_CH0_IRQHandler (void)
{
    /* 锟斤拷锟斤拷CPU锟叫讹拷  锟斤拷锟斤拷锟叫断诧拷锟斤拷嵌锟斤拷 */
    IfxCpu_enableInterrupts();
    // 锟斤拷锟斤拷卸媳锟街�
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t12PeriodMatch);

    /* 锟矫伙拷锟斤拷锟斤拷 */
    Motor_Control();
    Servo_Control();
}

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷void CCU60_CH1_IRQHandler(void)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷3锟斤拷30锟斤拷
 *  锟斤拷    注锟斤拷CCU60_CH1使锟矫碉拷锟叫断凤拷锟斤拷锟斤拷
 *************************************************************************/
uint8 TimeCnt=0;
void CCU60_CH1_IRQHandler (void)
{
    /* 锟斤拷锟斤拷CPU锟叫讹拷  锟斤拷锟斤拷锟叫断诧拷锟斤拷嵌锟斤拷 */
    IfxCpu_enableInterrupts();

    // 锟斤拷锟斤拷卸媳锟街�
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t13PeriodMatch);

    /* 锟矫伙拷锟斤拷锟斤拷 */
    TimeCnt++;
//    Key_Control();
    Button_Scan();
    if(TimeCnt>=10){
        LED_Ctrl(LED2,RVS);
        TimeCnt=0;
    }

}


/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷void CCU61_CH0_IRQHandler(void)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷3锟斤拷30锟斤拷
 *  锟斤拷    注锟斤拷CCU61_CH0使锟矫碉拷锟叫断凤拷锟斤拷锟斤拷
 *************************************************************************/
void CCU61_CH0_IRQHandler (void)
{
    /* 锟斤拷锟斤拷CPU锟叫讹拷  锟斤拷锟斤拷锟叫断诧拷锟斤拷嵌锟斤拷 */
    IfxCpu_enableInterrupts();

    // 锟斤拷锟斤拷卸媳锟街�
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t12PeriodMatch);

    /* 锟矫伙拷锟斤拷锟斤拷 */
    Camera_Control();


}

uint8 a=10;
uint8 s=50;
uint8 d=100;

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷void CCU61_CH1_IRQHandler(void)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷3锟斤拷30锟斤拷
 *  锟斤拷    注锟斤拷CCU61_CH1使锟矫碉拷锟叫断凤拷锟斤拷锟斤拷
 *************************************************************************/
void CCU61_CH1_IRQHandler (void)
{
    /* 锟斤拷锟斤拷CPU锟叫讹拷  锟斤拷锟斤拷锟叫断诧拷锟斤拷嵌锟斤拷 */
    IfxCpu_enableInterrupts();

    // 锟斤拷锟斤拷卸媳锟街�
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t13PeriodMatch);


}

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷CCU6_InitConfig CCU6
 *  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟斤拷锟叫断筹拷始锟斤拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷ccu6    锟斤拷 ccu6模锟斤拷            CCU60 锟斤拷 CCU61
 *  锟斤拷锟斤拷说锟斤拷锟斤拷channel 锟斤拷 ccu6模锟斤拷通锟斤拷  CCU6_Channel0 锟斤拷 CCU6_Channel1
 *  锟斤拷锟斤拷说锟斤拷锟斤拷us      锟斤拷 ccu6模锟斤拷  锟叫讹拷锟斤拷锟斤拷时锟斤拷  锟斤拷位us
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷3锟斤拷30锟斤拷
 *  锟斤拷    注锟斤拷    CCU6_InitConfig(CCU60, CCU6_Channel0, 100);  // 100us锟斤拷锟斤拷一锟斤拷锟叫讹拷
 *************************************************************************/
void CCU6_InitConfig (CCU6_t ccu6, CCU6_Channel_t channel, uint32 us)
{
    IfxCcu6_Timer_Config timerConfig;

    Ifx_CCU6 * module = IfxCcu6_getAddress((IfxCcu6_Index) ccu6);

    uint8 Index = ccu6 * 2 + channel;

    uint32 period = 0;

    uint64 clk = 0;

    /* 锟截憋拷锟叫讹拷 */
    boolean interrupt_state = disableInterrupts();

    IfxCcu6_Timer_initModuleConfig(&timerConfig, module);

    clk = IfxScuCcu_getSpbFrequency();

    /* 锟斤拷锟斤拷时锟斤拷频锟斤拷  */
    uint8 i = 0;
    while (i++ < 16)
    {
        period = (uint32) (clk * us / 1000000);
        if (period < 0xffff)
        {
            break;
        }
        else
        {
            clk = clk / 2;
        }
    }
    switch (channel)
    {
        case CCU6_Channel0 :
            timerConfig.timer = IfxCcu6_TimerId_t12;
            timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t12PeriodMatch;
            timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;
            timerConfig.base.t12Frequency = (float) clk;
            timerConfig.base.t12Period = period;                                  // 锟斤拷锟矫讹拷时锟叫讹拷
            timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;
            timerConfig.timer12.counterValue = 0;
            timerConfig.interrupt1.typeOfService = Ccu6IrqVectabNum[ccu6];
            timerConfig.interrupt1.priority = Ccu6IrqPriority[Index];
            break;

        case CCU6_Channel1 :
            timerConfig.timer = IfxCcu6_TimerId_t13;
            timerConfig.interrupt2.source = IfxCcu6_InterruptSource_t13PeriodMatch;
            timerConfig.interrupt2.serviceRequest = IfxCcu6_ServiceRequest_2;
            timerConfig.base.t13Frequency = (float) clk;
            timerConfig.base.t13Period = period;
            timerConfig.clock.t13countingInputMode = IfxCcu6_CountingInputMode_internal;
            timerConfig.timer13.counterValue = 0;
            timerConfig.interrupt2.typeOfService = Ccu6IrqVectabNum[ccu6];
            timerConfig.interrupt2.priority = Ccu6IrqPriority[Index];
            break;
    }

    timerConfig.trigger.t13InSyncWithT12 = FALSE;

    IfxCcu6_Timer Ccu6Timer;

    IfxCcu6_Timer_initModule(&Ccu6Timer, &timerConfig);

    IfxCpu_Irq_installInterruptHandler((void*) Ccu6IrqFuncPointer[Index], Ccu6IrqPriority[Index]);          // 锟斤拷锟斤拷锟叫断猴拷锟斤拷锟斤拷锟叫断猴拷

    restoreInterrupts(interrupt_state);

    IfxCcu6_Timer_start(&Ccu6Timer);
}

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷CCU6_DisableInterrupt(CCU6_t ccu6, CCU6_Channel_t channel)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷停止CCU6通锟斤拷锟叫讹拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷ccu6    锟斤拷 ccu6模锟斤拷            CCU60 锟斤拷 CCU61
 *  锟斤拷锟斤拷说锟斤拷锟斤拷channel 锟斤拷 ccu6模锟斤拷通锟斤拷  CCU6_Channel0 锟斤拷 CCU6_Channel1
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷5锟斤拷6锟斤拷
 *  锟斤拷    注锟斤拷
 *************************************************************************/
void CCU6_DisableInterrupt (CCU6_t ccu6, CCU6_Channel_t channel)
{
    Ifx_CCU6 * module = IfxCcu6_getAddress((IfxCcu6_Index) ccu6);
    IfxCcu6_clearInterruptStatusFlag(module, (IfxCcu6_InterruptSource) (7 + channel * 2));
    IfxCcu6_disableInterrupt(module, (IfxCcu6_InterruptSource) (7 + channel * 2));

}

/*************************************************************************
 *  锟斤拷锟斤拷锟斤拷锟狡ｏ拷CCU6_DisableInterrupt(CCU6_t ccu6, CCU6_Channel_t channel)
 *  锟斤拷锟斤拷说锟斤拷锟斤拷使锟斤拷CCU6通锟斤拷锟叫讹拷
 *  锟斤拷锟斤拷说锟斤拷锟斤拷ccu6    锟斤拷 ccu6模锟斤拷            CCU60 锟斤拷 CCU61
 *  锟斤拷锟斤拷说锟斤拷锟斤拷channel 锟斤拷 ccu6模锟斤拷通锟斤拷  CCU6_Channel0 锟斤拷 CCU6_Channel1
 *  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
 *  锟睫革拷时锟戒：2020锟斤拷5锟斤拷6锟斤拷
 *  锟斤拷    注锟斤拷
 *************************************************************************/
void CCU6_EnableInterrupt (CCU6_t ccu6, CCU6_Channel_t channel)
{
    Ifx_CCU6 * module = IfxCcu6_getAddress((IfxCcu6_Index) ccu6);
    IfxCcu6_clearInterruptStatusFlag(module, (IfxCcu6_InterruptSource) (7 + channel * 2));
    IfxCcu6_enableInterrupt(module, (IfxCcu6_InterruptSource) (7 + channel * 2));

}


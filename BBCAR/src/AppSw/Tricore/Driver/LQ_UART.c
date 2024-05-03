/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 銆愬钩    鍙般�戝寳浜緳閭辨櫤鑳界鎶�TC264DA鏍稿績鏉�
 銆愮紪    鍐欍�慫YF/chiusir
 銆怑-mail  銆慶hiusir@163.com
 銆愯蒋浠剁増鏈�慥1.1 鐗堟潈鎵�鏈夛紝鍗曚綅浣跨敤璇峰厛鑱旂郴鎺堟潈
 銆愭渶鍚庢洿鏂般��2020骞�4鏈�10鏃�
 銆愮浉鍏充俊鎭弬鑰冧笅鍒楀湴鍧�銆�
 銆愮綉    绔欍�慼ttp://www.lqist.cn
 銆愭窐瀹濆簵閾恒�慼ttp://longqiu.taobao.com
 ------------------------------------------------
 銆恉ev.env.銆慔ightec4.9.3/Tasking6.3鍙婁互涓婄増鏈�
 銆怲arget 銆� TC264DA
 銆怌rystal銆� 20.000Mhz
 銆怱YS PLL銆� 200MHz
 ________________________________________________________________

 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
 *  澶�    娉細TC264鍙湁15涓浐瀹氱殑GPIO鏀寔澶栭儴涓柇 杩�15涓浐瀹欸PIO鍒嗕负4缁勶紝姣忕粍鍙兘閫夋嫨鍏朵腑涓�涓綔涓哄閮ㄤ腑鏂鑴氫娇鐢�
 *           0锛歅15_4  P33_7  P15_5                             1锛歅14_3  P15_8
 *           2锛歅10_2  P02_1  P00_4  P20_0  P11_10              3锛歅10_3  P14_1  P02_0  P20_9  P15_1
 *          澶栭儴涓柇鏈嶅姟鍑芥暟鍦↙Q_GPIO.c涓�  涓柇浼樺厛绾ч厤缃湪LQ_GPIO.h涓� 鍙互鑷淇敼
 *          涓柇鍦ㄩ偅涓牳鍒濆鍖栵紝涓柇VECTABNUM鍙峰繀椤诲搴旇cpu,鍚﹀垯涓嶄細璋冪敤涓柇鍑芥暟
 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include <LQ_UART.h>
#include <LQ_GPIO.h>

#define ASC_TX_BUFFER_SIZE 64        //锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷锟斤拷
#define ASC_RX_BUFFER_SIZE 64        //锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷锟斤拷

//锟斤拷锟斤拷通锟脚结构锟斤拷
IfxAsclin_Asc g_UartConfig[4];

static uint8 s_AscTxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 s_AscRxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* UART锟叫讹拷 */
IFX_INTERRUPT(UART0_RX_IRQHandler, UART0_VECTABNUM, UART0_RX_PRIORITY);
IFX_INTERRUPT(UART1_RX_IRQHandler, UART1_VECTABNUM, UART1_RX_PRIORITY);
IFX_INTERRUPT(UART2_RX_IRQHandler, UART2_VECTABNUM, UART2_RX_PRIORITY);
IFX_INTERRUPT(UART3_RX_IRQHandler, UART3_VECTABNUM, UART3_RX_PRIORITY);
IFX_INTERRUPT(UART0_TX_IRQHandler, UART0_VECTABNUM, UART0_TX_PRIORITY);
IFX_INTERRUPT(UART1_TX_IRQHandler, UART1_VECTABNUM, UART1_TX_PRIORITY);
IFX_INTERRUPT(UART2_TX_IRQHandler, UART2_VECTABNUM, UART2_TX_PRIORITY);
IFX_INTERRUPT(UART3_TX_IRQHandler, UART3_VECTABNUM, UART3_TX_PRIORITY);
IFX_INTERRUPT(UART0_ER_IRQHandler, UART0_VECTABNUM, UART0_ER_PRIORITY);
IFX_INTERRUPT(UART1_ER_IRQHandler, UART1_VECTABNUM, UART1_ER_PRIORITY);
IFX_INTERRUPT(UART2_ER_IRQHandler, UART2_VECTABNUM, UART2_ER_PRIORITY);
IFX_INTERRUPT(UART3_ER_IRQHandler, UART3_VECTABNUM, UART3_ER_PRIORITY);


/** UART锟叫讹拷CPU锟斤拷锟� */
const uint8 UartIrqVectabNum[4] = {UART0_VECTABNUM, UART1_VECTABNUM, UART2_VECTABNUM, UART3_VECTABNUM};

/** UART锟叫讹拷锟斤拷锟饺硷拷 */
const uint8 UartIrqPriority[12] = {UART0_RX_PRIORITY, UART0_TX_PRIORITY, UART0_ER_PRIORITY, UART1_RX_PRIORITY, UART1_TX_PRIORITY, UART1_ER_PRIORITY,
		                           UART2_RX_PRIORITY, UART2_TX_PRIORITY, UART2_ER_PRIORITY, UART3_RX_PRIORITY, UART3_TX_PRIORITY, UART3_ER_PRIORITY};

/** UART锟叫断凤拷锟斤拷锟斤拷锟斤拷址 */
const void *UartIrqFuncPointer[12] =  {&UART0_RX_IRQHandler, &UART0_TX_IRQHandler, &UART0_ER_IRQHandler,
									   &UART1_RX_IRQHandler, &UART1_TX_IRQHandler, &UART1_ER_IRQHandler,
									   &UART2_RX_IRQHandler, &UART2_TX_IRQHandler, &UART2_ER_IRQHandler,
									   &UART3_RX_IRQHandler, &UART3_TX_IRQHandler, &UART3_ER_IRQHandler,};

/*************************************************************************
*  锟斤拷锟斤拷锟斤拷锟狡ｏ拷void UART0_RX_IRQHandler(void)
*  锟斤拷锟斤拷说锟斤拷锟斤拷UART0_RX_IRQHandler锟叫断凤拷锟斤拷锟斤拷
*  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷
*  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷
*  锟睫革拷时锟戒：2020锟斤拷3锟斤拷30锟斤拷
*  锟斤拷    注锟斤拷
*************************************************************************/

char data[10];

uint8 uart1_data;
void UART0_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[0]);

	/* 用户代码 */
//	uint8 data=UART_GetChar(UART0);
//    if(!CircularBuffer_Write(&bf,data)){
//        //写入失败，缓存满了
//    }

}

void UART0_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[0]);

	/* 锟矫伙拷锟斤拷锟斤拷 */

}

void UART0_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[0]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
	LED_Ctrl(LED0,RVS);

}



void UART1_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[1]);

	/* 用户代码 */
//	  UART_PutChar(UART1, UART_GetChar(UART1));
//	uint8 data=UART_GetChar(UART1);
//    if(!CircularBuffer_Write(&bf,data)){
//        //写入失败，缓存满了
//    }
    uint8 data=UART_GetChar(UART1);
    UART_ReceiveData(data);
}

void UART1_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[1]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
}

void UART1_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[1]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
}

void UART2_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[2]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
	UART_PutChar(UART2, UART_GetChar(UART2));
}

void UART2_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[2]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
}

void UART2_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[2]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
}

void UART3_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[3]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
//	UART_PutChar(UART3, UART_GetChar(UART3));
}

void UART3_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[3]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
}

void UART3_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[3]);

	/* 锟矫伙拷锟斤拷锟斤拷 */
}

/*************************************************************************
*  锟斤拷锟斤拷锟斤拷锟狡ｏ拷void UART_InitConfig(UART_RX_t RxPin, UART_TX_t TxPin, unsigned long baudrate)
*  锟斤拷锟斤拷说锟斤拷锟斤拷锟斤拷锟斤拷模锟斤拷锟绞硷拷锟�
*  锟斤拷锟斤拷说锟斤拷锟斤拷
  * @param    RxPin   锟斤拷 锟斤拷锟节斤拷锟秸管斤拷
  * @param    TxPin   锟斤拷 锟斤拷锟节凤拷锟酵管斤拷
  * @param    baudrate锟斤拷 锟斤拷锟斤拷锟斤拷
*  锟斤拷锟斤拷锟斤拷锟截ｏ拷锟街斤拷
*  锟睫革拷时锟戒：2020锟斤拷3锟斤拷10锟斤拷
*  锟斤拷    注锟斤拷UART_InitConfig(UART0_RX_P14_1,UART0_TX_P14_0, 115200);   //锟斤拷始锟斤拷锟斤拷锟斤拷0 锟斤拷锟斤拷锟斤拷 115200 锟斤拷锟斤拷偶校锟斤拷 1停止位 使锟矫管斤拷P14_0 P14_1
*************************************************************************/
void UART_InitConfig(UART_RX_t RxPin, UART_TX_t TxPin, unsigned long baudrate)
{
	int i,j;
	//锟截憋拷CPU锟叫讹拷
	IfxCpu_disableInterrupts();

	Ifx_P *portRx = PIN_GetModule(RxPin);
	uint8 pinIndexRx = PIN_GetIndex(RxPin);

	Ifx_P *portTx = PIN_GetModule(TxPin);
	uint8 pinIndexTx = PIN_GetIndex(TxPin);

	IfxAsclin_Rx_In  * IfxAsclin_Rx = NULL_PTR;
	IfxAsclin_Tx_Out * IfxAsclin_Tx = NULL_PTR;

	for( i = 0; i < IFXASCLIN_PINMAP_NUM_MODULES; i++)
	{
		for( j = 0; j < IFXASCLIN_PINMAP_RX_IN_NUM_ITEMS; j++)
		{
			if(IfxAsclin_Rx_In_pinTable[i][j] == NULL_PTR)
			{

			}
			else if((unsigned long)portRx == (unsigned long)(IfxAsclin_Rx_In_pinTable[i][j]->pin.port) && pinIndexRx == IfxAsclin_Rx_In_pinTable[i][j]->pin.pinIndex)
			{
				IfxAsclin_Rx = IfxAsclin_Rx_In_pinTable[i][j];
			}
		}

		for(j = 0; j < IFXASCLIN_PINMAP_TX_OUT_NUM_ITEMS; j++)
		{
			if(IfxAsclin_Tx_Out_pinTable[i][j] == NULL_PTR)
			{

			}
			else if((unsigned long)portTx == (unsigned long)(IfxAsclin_Tx_Out_pinTable[i][j]->pin.port) && pinIndexTx == IfxAsclin_Tx_Out_pinTable[i][j]->pin.pinIndex)
			{
				IfxAsclin_Tx = IfxAsclin_Tx_Out_pinTable[i][j];
			}
		}
	}

	if(IfxAsclin_Rx->module != IfxAsclin_Tx->module)
	{
#pragma warning 557         // 锟斤拷锟轿撅拷锟斤拷
		while (1);          // 锟斤拷锟� RX锟斤拷TX 锟角凤拷为同一UART
#pragma warning default     // 锟津开撅拷锟斤拷
	}

	//锟铰斤拷锟斤拷锟斤拷锟斤拷锟矫结构锟斤拷
	IfxAsclin_Asc_Config ascConfig;

	//锟斤拷始锟斤拷模锟斤拷
	IfxAsclin_Asc_initModuleConfig(&ascConfig, IfxAsclin_Tx->module);

	ascConfig.baudrate.baudrate  = (float)baudrate;        //锟斤拷锟斤拷锟斤拷
	ascConfig.frame.frameMode    = IfxAsclin_FrameMode_asc;//锟斤拷锟斤拷帧模式
	ascConfig.frame.dataLength   = IfxAsclin_DataLength_8; //锟斤拷锟捷筹拷锟斤拷
	ascConfig.frame.stopBit      = IfxAsclin_StopBit_1;    //停止位
	ascConfig.frame.shiftDir     = IfxAsclin_ShiftDirection_lsbFirst;//锟斤拷位锟斤拷锟斤拷
	ascConfig.frame.parityBit    = FALSE;//锟斤拷锟斤拷偶校锟斤拷

	unsigned char uartNum = IfxAsclin_getIndex(IfxAsclin_Tx->module);

	//锟叫讹拷锟斤拷锟饺硷拷锟斤拷锟斤拷
	ascConfig.interrupt.rxPriority = UartIrqPriority[uartNum * 3];
	ascConfig.interrupt.txPriority = UartIrqPriority[uartNum * 3 + 1];
	ascConfig.interrupt.erPriority = UartIrqPriority[uartNum * 3 + 2];
	ascConfig.interrupt.typeOfService = UartIrqVectabNum[uartNum];

	//锟斤拷锟秸和凤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷
	ascConfig.txBuffer     = &s_AscTxBuffer[uartNum][0];
	ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;
	ascConfig.rxBuffer     = &s_AscRxBuffer[uartNum][0];
	ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

	IfxAsclin_Asc_Pins pins =
	{
		NULL,                     IfxPort_InputMode_pullUp,        /* CTS pin not used */
		IfxAsclin_Rx,             IfxPort_InputMode_pullUp,        /* Rx pin */
		NULL,                     IfxPort_OutputMode_pushPull,     /* RTS pin not used */
		IfxAsclin_Tx,             IfxPort_OutputMode_pushPull,     /* Tx pin */
		IfxPort_PadDriver_cmosAutomotiveSpeed1
	};
	ascConfig.pins = &pins;

	//锟斤拷锟斤拷锟斤拷锟斤拷峁癸拷锟斤拷锟皆わ拷锟侥诧拷锟斤拷锟斤拷锟斤拷锟侥ｏ拷锟侥筹拷始锟斤拷
	IfxAsclin_Asc_initModule(&g_UartConfig[uartNum], &ascConfig);

	//锟斤拷锟秸ｏ拷锟斤拷锟酵和达拷锟斤拷锟叫讹拷锟斤拷锟斤拷
	IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3],     UartIrqPriority[uartNum * 3]);
	IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3 + 1], UartIrqPriority[uartNum * 3 + 1]);
	IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3 + 2], UartIrqPriority[uartNum * 3 + 2]);

	//锟斤拷锟斤拷CPU锟叫讹拷
	IfxCpu_enableInterrupts();
}

/*************************************************************************
*  鍑芥暟鍚嶇О锛歷oid UART_PutChar(UART_t  uratn, char ch)
*  鍔熻兘璇存槑锛歎ART鍙戦�佸瓧鑺傚嚱鏁�,浣跨敤鍓嶈鍏堝垵濮嬪寲瀵瑰簲涓插彛
*  鍙傛暟璇存槑锛歶ratn 锛� UART0 - UART3/ ch    锛� 瑕佹墦鍗扮殑瀛楃
*  鍑芥暟杩斿洖锛氭棤
*  淇敼鏃堕棿锛�2020骞�3鏈�10鏃�
*  澶�    娉細UART_PutChar(UART0, 'a');  //鎵撳嵃瀛楃a
*************************************************************************/
void UART_PutChar(UART_t  uratn, char ch)
{
	IfxAsclin_Asc_blockingWrite(&g_UartConfig[uratn], ch);
}

/*************************************************************************
*  鍑芥暟鍚嶇О锛歷oid UART_PutStr(UART_t  uratn, char *str)
*  鍔熻兘璇存槑锛歎ART鍙戦�佸瓧绗︿覆鍑芥暟(閬� NULL 鍋滄鍙戦��),浣跨敤鍓嶈鍏堝垵濮嬪寲瀵瑰簲涓插彛
*  鍙傛暟璇存槑锛歶ratn 锛� UART0 - UART3/ str   锛� 瑕佹墦鍗扮殑瀛楃涓插湴鍧�
*  鍑芥暟杩斿洖锛氭棤
*  淇敼鏃堕棿锛�2020骞�3鏈�10鏃�
*  澶�    娉細UART_PutStr(UART3, "123456789"); //鍙戦��9涓瓧鑺�
*************************************************************************/
void UART_PutStr(UART_t  uratn, char *str)
{
   while(*str)
    {
        UART_PutChar(uratn, *str++);
    }
}

/*************************************************************************
*  鍑芥暟鍚嶇О锛歷oid UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len)
*  鍔熻兘璇存槑锛歎ART鍙戦�佸瓧鑺傚嚱鏁�,浣跨敤鍓嶈鍏堝垵濮嬪寲瀵瑰簲涓插彛
*  鍙傛暟璇存槑锛�
* @param    uratn 锛� UART0 - UART3
* @param    buff  锛� 瑕佹墦鍗扮殑瀛楃涓插湴鍧�
* @param    len   锛� 瑕佹墦鍗扮殑闀垮害
*  鍑芥暟杩斿洖锛氭棤
*  淇敼鏃堕棿锛�2020骞�3鏈�10鏃�
*  澶�    娉細UART_PutBuff(UART4, "123456789",5);//瀹為檯鍙戦��5涓瓧鑺傗��1鈥欌��2鈥欌��3鈥欌��4鈥欌��5鈥�
*************************************************************************/
void UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len)
{
    while(len--)
    {
        UART_PutChar(uratn, *buff);
        buff++;
    }
}

/*************************************************************************
*  鍑芥暟鍚嶇О锛欼fx_SizeT UART_GetCount(UART_t  uratn)
*  鍔熻兘璇存槑锛氳幏鍙� 鎺ユ敹缂撳啿鍖� 瀛樻斁褰撳墠鎺ユ敹鏁版嵁涓暟
*  鍙傛暟璇存槑锛� uratn 锛� UART0 - UART3
*  鍑芥暟杩斿洖锛氭棤
*  淇敼鏃堕棿锛�2020骞�3鏈�10鏃�
*  澶�    娉細
*************************************************************************/
uint8 UART_GetCount(UART_t  uratn)
{
	return (uint8)IfxAsclin_Asc_getReadCount(&g_UartConfig[uratn]);
}

/*************************************************************************
*  鍑芥暟鍚嶇О锛歝har UART_GetChar(UART_t  uratn)
*  鍔熻兘璇存槑锛歎ART璇诲彇瀛楄妭 浣跨敤鍓嶈鍏堝垵濮嬪寲瀵瑰簲涓插彛 璋冪敤鍓嶈纭鏈夋帴鏀跺埌鏁版嵁 鍚﹀垯浼氱瓑寰呮暟鎹埌鏉�
*  鍙傛暟璇存槑锛歶ratn 锛� UART0 - UART3
*  鍑芥暟杩斿洖锛氳鍙栧瓧鑺�
*  淇敼鏃堕棿锛�2020骞�3鏈�10鏃�
*  澶�    娉細UART_GetChar(UART3); //鎺ユ敹涓�涓瓧绗�
*************************************************************************/
char UART_GetChar(UART_t  uratn)
{
	uint8 data=0;
	Ifx_SizeT count = 1;

	/* 鑾峰彇鎺ユ敹鍒扮殑涓�涓瓧鑺傛暟鎹� 娉ㄦ剰濡傛灉娌℃湁鎺ユ敹鍒帮紝浼氫竴鐩寸瓑寰� */
	IfxAsclin_Asc_read(&g_UartConfig[uratn], &data, &count, TIME_INFINITE);

	return 	data;
}

/*************************************************************************
*  鍑芥暟鍚嶇О锛歝har UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len)
*  鍔熻兘璇存槑锛氭帴鏀朵竴瀹氶暱搴﹀瓧绗� 浣跨敤鍓嶈鍏堝垵濮嬪寲瀵瑰簲涓插彛 璋冪敤鍓嶈纭鏈夋帴鏀跺埌鏁版嵁 鍚﹀垯浼氭帴鍙楀け璐�
*  鍙傛暟璇存槑锛歶ratn 锛� UART0 - UART3
*  鍑芥暟杩斿洖锛�0:璇诲彇姝ｅ父  鍏朵粬 璇诲彇澶辫触
*  淇敼鏃堕棿锛�2020骞�3鏈�10鏃�
*  澶�    娉細UART_GetChar(UART0, data, 10); //鎺ユ敹10涓瓧绗�
*************************************************************************/
char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len)
{
	Ifx_SizeT count = len;

	if(UART_GetCount(uratn) < len)
	{
		return 1;  //鍒ゆ柇褰撳墠鎺ユ敹鍒扮殑鏁版嵁鏁伴噺 涓嶅璇诲彇闀垮害
	}

	/* 鑾峰彇鎺ユ敹鍒版暟鎹�  */
	IfxAsclin_Asc_read(&g_UartConfig[uratn], data, &count, TIME_INFINITE);
	return 	0;
}








/////////////////////////////////////////////////////////////////////////////////////

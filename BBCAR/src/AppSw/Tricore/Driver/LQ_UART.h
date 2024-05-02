/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
锟斤拷平    台锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟杰科硷拷TC264DA锟斤拷锟侥帮拷
锟斤拷锟斤拷    写锟斤拷ZYF/chiusir
锟斤拷E-mail  锟斤拷chiusir@163.com
锟斤拷锟斤拷锟斤拷姹撅拷锟絍1.1 锟斤拷权锟斤拷锟叫ｏ拷锟斤拷位使锟斤拷锟斤拷锟斤拷锟斤拷系锟斤拷权
锟斤拷锟斤拷锟斤拷锟铰★拷2020锟斤拷10锟斤拷28锟斤拷
锟斤拷锟斤拷锟斤拷锟较拷慰锟斤拷锟斤拷械锟街凤拷锟�
锟斤拷锟斤拷    站锟斤拷http://www.lqist.cn
锟斤拷锟皆憋拷锟斤拷锟教★拷http://longqiu.taobao.com
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
ASC锟届步锟斤拷锟斤拷通锟脚ｏ拷锟斤拷锟斤拷锟斤拷为UART锟斤拷锟斤拷锟斤拷LIN锟斤拷锟斤拷使锟矫ｏ拷
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_ASC_H_
#define _LQ_ASC_H_

#include <Platform_Types.h>
#include <stdint.h>
#include <Ifx_Fifo.h>
#include <Ifx_Types.h>
#include <IfxAsclin.h>
#include <IfxAsclin_Asc.h>
#include <IfxAsclin_PinMap.h>
#include <IfxCpu.h>
#include <IfxCpu_Irq.h>

#include <IfxPort.h>
#include <IfxPort_regdef.h>
#include <LQ_GPIO_LED.h>
#include <My_UART.h>
#include <CircularBuffer.h>

/** UART0锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART0_RX_PRIORITY    120

/** UART0锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART0_TX_PRIORITY    121

/** UART0锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART0_ER_PRIORITY    122

/** UART0锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷 锟叫断癸拷锟侥革拷锟节核癸拷锟斤拷 锟斤拷围锟斤拷0锟斤拷CPU0   1锟斤拷CPU1   3锟斤拷DMA*/
#define  UART0_VECTABNUM    0


/** UART1锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART1_RX_PRIORITY    130

/** UART1锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART1_TX_PRIORITY    131

/** UART1锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART1_ER_PRIORITY    132

/** UART1锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷 锟叫断癸拷锟侥革拷锟节核癸拷锟斤拷 锟斤拷围锟斤拷0锟斤拷CPU0   1锟斤拷CPU1   3锟斤拷DMA*/
#define  UART1_VECTABNUM    0


/** UART2锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART2_RX_PRIORITY    140

/** UART2锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART2_TX_PRIORITY    141

/** UART2锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART2_ER_PRIORITY    142

/** UART2锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷 锟叫断癸拷锟侥革拷锟节核癸拷锟斤拷 锟斤拷围锟斤拷0锟斤拷CPU0   1锟斤拷CPU1   3锟斤拷DMA*/
#define  UART2_VECTABNUM    0


/** UART3锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART3_RX_PRIORITY    150

/** UART3锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART3_TX_PRIORITY    151

/** UART3锟斤拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷   锟斤拷围锟斤拷1-255   锟斤拷锟斤拷越锟斤拷 锟斤拷锟饺硷拷越锟斤拷  注锟斤拷锟斤拷锟饺硷拷锟斤拷要锟截革拷 */
#define  UART3_ER_PRIORITY    152

/** UART3锟叫断凤拷锟斤拷锟斤拷锟斤拷锟饺硷拷 锟叫断癸拷锟侥革拷锟节核癸拷锟斤拷 锟斤拷围锟斤拷0锟斤拷CPU0   1锟斤拷CPU1   3锟斤拷DMA*/
#define  UART3_VECTABNUM    0

/**
  * @brief UART 枚锟斤拷
  */
typedef enum
{
	UART0 = 0,
	UART1,
	UART2,
	UART3
}UART_t;

//L.Q UART RX 锟杰斤拷枚锟斤拷
typedef enum
{
	UART0_RX_P14_1 = 0xB401, UART0_RX_P15_3 = 0xB503,

	UART1_RX_P02_3 = 0xA203, UART1_RX_P11_10= 0xB10A, UART1_RX_P15_1 = 0xB501, UART1_RX_P15_5 = 0xB505, UART1_RX_P20_9 = 0xC009, UART1_RX_P33_13= 0xD30D,

	UART2_RX_P02_0 = 0xA200, UART2_RX_P02_1 = 0xA201, UART2_RX_P10_6 = 0xB006, UART2_RX_P14_3 = 0xB403, UART2_RX_P33_8 = 0xD308,

	UART3_RX_P00_1 = 0xA001, UART3_RX_P15_7 = 0xB507, UART3_RX_P20_3 = 0xC003, UART3_RX_P21_6 = 0xC106

}UART_RX_t;


//L.Q UART TX 锟杰斤拷枚锟斤拷
typedef enum
{
	UART0_TX_P14_0 = 0xB400, UART0_TX_P14_1 = 0xB401, UART0_TX_P15_2 = 0xB502, UART0_TX_P15_3 = 0xB503,

	UART1_TX_P02_2 = 0xA202, UART1_TX_P11_12= 0xB10C, UART1_TX_P15_0 = 0xB500, UART1_TX_P15_1 = 0xB501, UART1_TX_P15_4 = 0xB504, UART1_TX_P15_5 = 0xB505, UART1_TX_P20_10= 0xC00A, UART1_TX_P33_12= 0xD30C, UART1_TX_P33_13 = 0xD30D,

	UART2_TX_P02_0 = 0xA200, UART2_TX_P10_5 = 0xB005, UART2_TX_P14_2 = 0xB402, UART2_TX_P14_3 = 0xB403, UART2_TX_P33_8 = 0xD308, UART2_TX_P33_9 = 0xD309,

	UART3_TX_P00_0 = 0xA000, UART3_TX_P00_1 = 0xA001, UART3_TX_P00_2 = 0xA002,UART3_TX_P15_6 = 0xB506, UART3_TX_P15_7 = 0xB507, UART3_TX_P20_0 = 0xC000, UART3_TX_P20_3 = 0xC003, UART3_TX_P21_7 = 0xC107

}UART_TX_t;

extern CircularBuffer bf;


void UART_InitConfig(UART_RX_t RxPin, UART_TX_t TxPin, unsigned long baudrate);
void UART_PutChar(UART_t  uratn, char ch);
void UART_PutStr(UART_t  uratn, char *str);
void UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len);
uint8 UART_GetCount(UART_t  uratn);
char UART_GetChar(UART_t  uratn);
char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len);

#endif /* 0_APPSW_TRICORE_APP_LQ_ASC_H_ */

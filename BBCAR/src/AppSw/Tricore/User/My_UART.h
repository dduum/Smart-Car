/*
 * My_UART.h
 *
 *  Created on: 2024.4.25
 *      Author: dduu
 */

#ifndef SRC_APPSW_TRICORE_USER_MY_UART_H_
#define SRC_APPSW_TRICORE_USER_MY_UART_H_

#include <LQ_UART.h>
#include <LQ_PID.h>

void UART_hander(void);
void Data_Analyse(void);
void UART_ReceiveData(uint8 data);
void UART_WriteReturn(uint8 sum,uint8 add);
void UART_SaveReturn(uint8 sum,uint8 add);
void UART_SendData(uint8 data1, uint8 data2, uint8 data3);
void UART_SendPar_Cmd00(char name);                         //
void UART_SendPar_Cmd01(uint16 val);                        //
void UART_SendPar_Cmd02(uint16 id , float val);
void UART_SendPar_Cmd03(uint16 id, uint8 type, char name[3]);

#endif /* SRC_APPSW_TRICORE_USER_MY_UART_H_ */
/*
 * image1.h
 *
 *  Created on: 2024Äê4ÔÂ16ÈÕ
 *      Author: Macation
 */

#ifndef SRC_USER_IMAGE1_H_
#define SRC_USER_IMAGE1_H_

#include <LQ_CAMERA.h>
#include <IfxCpu.h>
#include <IfxPort_reg.h>
#include <Platform_Types.h>
#include <stdlib.h>
#include <stdio.h>

#include "LQ_DMA.h"
#include "LQ_GPIO.h"
#include "LQ_UART.h"
#include "LQ_GPIO_LED.h"
#include "LQ_TFT18.h"
#include "string.h"

#define Image_downLine 110
#define Image_upLine 20
#define Array_Length LCDH/2+LCDW/2
#define Image_Length Image_downLine-Image_upLine

extern unsigned char Image_Line[120][160];
extern unsigned char Image_centralLine[];
extern int threshold;
extern int Servo_Loc_error;

int Image_SeedGrowing(void);
void Image_printSeedline(void);
void Image_Frameprocessing(void);
int Image_Threshold_Line(int Y);
void Image_seedCentralline(int X1,int X2);
void showimage(void);
int Calc_ERROR(void);
int Image_findSeedBegin(int thres);
#endif /* SRC_USER_IMAGE1_H_ */

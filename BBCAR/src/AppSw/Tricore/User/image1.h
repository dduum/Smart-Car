/*
 * image1.h
 *
 *  Created on: 2024Äê4ÔÂ16ÈÕ
 *      Author: Macation
 */

#ifndef SRC_USER_IMAGE1_H_
#define SRC_USER_IMAGE1_H_
#include "LQ_CAMERA.h"
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

int Image_SeedGrowing(void);
void Image_printSeedline(void);
void Image_Frameprocessing(void);
int Image_Threshold_Line(int Y);
void Image_seedCentralline(int X1,int X2);
extern unsigned char Image_Line[120][188];
void showimage(void);
int Image_findSeedBegin(int thres);
#endif /* SRC_USER_IMAGE1_H_ */

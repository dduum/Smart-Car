/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技F3277核心板和母板
【编    写】龙邱科技
【E-mail  】chiusir@163.com
【软件版本】V1.0 版权所有，单位使用请先联系授权
【最后更新】2021年3月31日，持续更新，请关注最新版！
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【IDE】IAR7.8 KEIL5.24及以上版本
【Target 】 MM32F3277
【SYS PLL】 120MHz 频率太高可能无法启动system_mm32f327x.c
=================================================================
程序配套视频地址：https://space.bilibili.com/95313236
=================================================================
本程序测试MPU6050DMP功能，配置匿名地面站4.34显示波形
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "../Driver/LQ_SOFTI2C.h"
#include "LQ_MPU6050_DMP.h"
#include "../Driver/LQ_STM.h"
#include "math.h"
#include <string.h>
#define min(a, b) (a < b) ? a : b;

// DMP固件
static const unsigned char dmp_memory[3062] = {
/* bank # 0 */
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00,
0x00, 0x65, 0x00, 0x54, 0xff, 0xef, 0x00, 0x00, 0xfa, 0x80, 0x00, 0x0b, 0x12, 0x82, 0x00, 0x01,
0x03, 0x0c, 0x30, 0xc3, 0x0e, 0x8c, 0x8c, 0xe9, 0x14, 0xd5, 0x40, 0x02, 0x13, 0x71, 0x0f, 0x8e,
0x38, 0x83, 0xf8, 0x83, 0x30, 0x00, 0xf8, 0x83, 0x25, 0x8e, 0xf8, 0x83, 0x30, 0x00, 0xf8, 0x83,
0xff, 0xff, 0xff, 0xff, 0x0f, 0xfe, 0xa9, 0xd6, 0x24, 0x00, 0x04, 0x00, 0x1a, 0x82, 0x79, 0xa1,
0x00, 0x00, 0x00, 0x3c, 0xff, 0xff, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x83, 0x6f, 0xa2,
0x00, 0x3e, 0x03, 0x30, 0x40, 0x00, 0x00, 0x00, 0x02, 0xca, 0xe3, 0x09, 0x3e, 0x80, 0x00, 0x00,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x6e, 0x00, 0x00, 0x06, 0x92, 0x0a, 0x16, 0xc0, 0xdf,
0xff, 0xff, 0x02, 0x56, 0xfd, 0x8c, 0xd3, 0x77, 0xff, 0xe1, 0xc4, 0x96, 0xe0, 0xc5, 0xbe, 0xaa,
0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0b, 0x2b, 0x00, 0x00, 0x16, 0x57, 0x00, 0x00, 0x03, 0x59,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0xfa, 0x00, 0x02, 0x6c, 0x1d, 0x00, 0x00, 0x00, 0x00,
0x3f, 0xff, 0xdf, 0xeb, 0x00, 0x3e, 0xb3, 0xb6, 0x00, 0x0d, 0x22, 0x78, 0x00, 0x00, 0x2f, 0x3c,
0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x42, 0xb5, 0x00, 0x00, 0x39, 0xa2, 0x00, 0x00, 0xb3, 0x65,
0xd9, 0x0e, 0x9f, 0xc9, 0x1d, 0xcf, 0x4c, 0x34, 0x30, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
0x3b, 0xb6, 0x7a, 0xe8, 0x00, 0x64, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* bank # 1 */
0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0xfa, 0x92, 0x10, 0x00, 0x22, 0x5e, 0x00, 0x0d, 0x22, 0x9f,
0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0xff, 0x46, 0x00, 0x00, 0x63, 0xd4, 0x00, 0x00,
0x10, 0x00, 0x00, 0x00, 0x04, 0xd6, 0x00, 0x00, 0x04, 0xcc, 0x00, 0x00, 0x04, 0xcc, 0x00, 0x00,
0x00, 0x00, 0x10, 0x72, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x06, 0x00, 0x02, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x64, 0x00, 0x20, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00,
0x00, 0x00, 0x00, 0x32, 0xf8, 0x98, 0x00, 0x00, 0xff, 0x65, 0x00, 0x00, 0x83, 0x0f, 0x00, 0x00,
0xff, 0x9b, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0xb2, 0x6a, 0x00, 0x02, 0x00, 0x00,
0x00, 0x01, 0xfb, 0x83, 0x00, 0x68, 0x00, 0x00, 0x00, 0xd9, 0xfc, 0x00, 0x7c, 0xf1, 0xff, 0x83,
0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x64, 0x03, 0xe8, 0x00, 0x64, 0x00, 0x28,
0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x16, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
0x00, 0x00, 0x10, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf4, 0x00, 0x00, 0x10, 0x00,
/* bank # 2 */
0x00, 0x28, 0x00, 0x00, 0xff, 0xff, 0x45, 0x81, 0xff, 0xff, 0xfa, 0x72, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x05, 0x00, 0x05, 0xba, 0xc6, 0x00, 0x47, 0x78, 0xa2,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x14,
0x00, 0x00, 0x25, 0x4d, 0x00, 0x2f, 0x70, 0x6d, 0x00, 0x00, 0x05, 0xae, 0x00, 0x0c, 0x02, 0xd0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x64, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x0e,
0x00, 0x00, 0x0a, 0xc7, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0xff, 0xff, 0xff, 0x9c,
0x00, 0x00, 0x0b, 0x2b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x64,
0xff, 0xe5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* bank # 3 */
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x24, 0x26, 0xd3,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x96, 0x00, 0x3c,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0c, 0x0a, 0x4e, 0x68, 0xcd, 0xcf, 0x77, 0x09, 0x50, 0x16, 0x67, 0x59, 0xc6, 0x19, 0xce, 0x82,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xd7, 0x84, 0x00, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x93, 0x8f, 0x9d, 0x1e, 0x1b, 0x1c, 0x19,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x18, 0x85, 0x00, 0x00, 0x40, 0x00,
0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x67, 0x7d, 0xdf, 0x7e, 0x72, 0x90, 0x2e, 0x55, 0x4c, 0xf6, 0xe6, 0x88,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

/* bank # 4 */
0xd8, 0xdc, 0xb4, 0xb8, 0xb0, 0xd8, 0xb9, 0xab, 0xf3, 0xf8, 0xfa, 0xb3, 0xb7, 0xbb, 0x8e, 0x9e,
0xae, 0xf1, 0x32, 0xf5, 0x1b, 0xf1, 0xb4, 0xb8, 0xb0, 0x80, 0x97, 0xf1, 0xa9, 0xdf, 0xdf, 0xdf,
0xaa, 0xdf, 0xdf, 0xdf, 0xf2, 0xaa, 0xc5, 0xcd, 0xc7, 0xa9, 0x0c, 0xc9, 0x2c, 0x97, 0xf1, 0xa9,
0x89, 0x26, 0x46, 0x66, 0xb2, 0x89, 0x99, 0xa9, 0x2d, 0x55, 0x7d, 0xb0, 0xb0, 0x8a, 0xa8, 0x96,
0x36, 0x56, 0x76, 0xf1, 0xba, 0xa3, 0xb4, 0xb2, 0x80, 0xc0, 0xb8, 0xa8, 0x97, 0x11, 0xb2, 0x83,
0x98, 0xba, 0xa3, 0xf0, 0x24, 0x08, 0x44, 0x10, 0x64, 0x18, 0xb2, 0xb9, 0xb4, 0x98, 0x83, 0xf1,
0xa3, 0x29, 0x55, 0x7d, 0xba, 0xb5, 0xb1, 0xa3, 0x83, 0x93, 0xf0, 0x00, 0x28, 0x50, 0xf5, 0xb2,
0xb6, 0xaa, 0x83, 0x93, 0x28, 0x54, 0x7c, 0xf1, 0xb9, 0xa3, 0x82, 0x93, 0x61, 0xba, 0xa2, 0xda,
0xde, 0xdf, 0xdb, 0x81, 0x9a, 0xb9, 0xae, 0xf5, 0x60, 0x68, 0x70, 0xf1, 0xda, 0xba, 0xa2, 0xdf,
0xd9, 0xba, 0xa2, 0xfa, 0xb9, 0xa3, 0x82, 0x92, 0xdb, 0x31, 0xba, 0xa2, 0xd9, 0xba, 0xa2, 0xf8,
0xdf, 0x85, 0xa4, 0xd0, 0xc1, 0xbb, 0xad, 0x83, 0xc2, 0xc5, 0xc7, 0xb8, 0xa2, 0xdf, 0xdf, 0xdf,
0xba, 0xa0, 0xdf, 0xdf, 0xdf, 0xd8, 0xd8, 0xf1, 0xb8, 0xaa, 0xb3, 0x8d, 0xb4, 0x98, 0x0d, 0x35,
0x5d, 0xb2, 0xb6, 0xba, 0xaf, 0x8c, 0x96, 0x19, 0x8f, 0x9f, 0xa7, 0x0e, 0x16, 0x1e, 0xb4, 0x9a,
0xb8, 0xaa, 0x87, 0x2c, 0x54, 0x7c, 0xba, 0xa4, 0xb0, 0x8a, 0xb6, 0x91, 0x32, 0x56, 0x76, 0xb2,
0x84, 0x94, 0xa4, 0xc8, 0x08, 0xcd, 0xd8, 0xb8, 0xb4, 0xb0, 0xf1, 0x99, 0x82, 0xa8, 0x2d, 0x55,
0x7d, 0x98, 0xa8, 0x0e, 0x16, 0x1e, 0xa2, 0x2c, 0x54, 0x7c, 0x92, 0xa4, 0xf0, 0x2c, 0x50, 0x78,
/* bank # 5 */
0xf1, 0x84, 0xa8, 0x98, 0xc4, 0xcd, 0xfc, 0xd8, 0x0d, 0xdb, 0xa8, 0xfc, 0x2d, 0xf3, 0xd9, 0xba,
0xa6, 0xf8, 0xda, 0xba, 0xa6, 0xde, 0xd8, 0xba, 0xb2, 0xb6, 0x86, 0x96, 0xa6, 0xd0, 0xf3, 0xc8,
0x41, 0xda, 0xa6, 0xc8, 0xf8, 0xd8, 0xb0, 0xb4, 0xb8, 0x82, 0xa8, 0x92, 0xf5, 0x2c, 0x54, 0x88,
0x98, 0xf1, 0x35, 0xd9, 0xf4, 0x18, 0xd8, 0xf1, 0xa2, 0xd0, 0xf8, 0xf9, 0xa8, 0x84, 0xd9, 0xc7,
0xdf, 0xf8, 0xf8, 0x83, 0xc5, 0xda, 0xdf, 0x69, 0xdf, 0x83, 0xc1, 0xd8, 0xf4, 0x01, 0x14, 0xf1,
0xa8, 0x82, 0x4e, 0xa8, 0x84, 0xf3, 0x11, 0xd1, 0x82, 0xf5, 0xd9, 0x92, 0x28, 0x97, 0x88, 0xf1,
0x09, 0xf4, 0x1c, 0x1c, 0xd8, 0x84, 0xa8, 0xf3, 0xc0, 0xf9, 0xd1, 0xd9, 0x97, 0x82, 0xf1, 0x29,
0xf4, 0x0d, 0xd8, 0xf3, 0xf9, 0xf9, 0xd1, 0xd9, 0x82, 0xf4, 0xc2, 0x03, 0xd8, 0xde, 0xdf, 0x1a,
0xd8, 0xf1, 0xa2, 0xfa, 0xf9, 0xa8, 0x84, 0x98, 0xd9, 0xc7, 0xdf, 0xf8, 0xf8, 0xf8, 0x83, 0xc7,
0xda, 0xdf, 0x69, 0xdf, 0xf8, 0x83, 0xc3, 0xd8, 0xf4, 0x01, 0x14, 0xf1, 0x98, 0xa8, 0x82, 0x2e,
0xa8, 0x84, 0xf3, 0x11, 0xd1, 0x82, 0xf5, 0xd9, 0x92, 0x50, 0x97, 0x88, 0xf1, 0x09, 0xf4, 0x1c,
0xd8, 0x84, 0xa8, 0xf3, 0xc0, 0xf8, 0xf9, 0xd1, 0xd9, 0x97, 0x82, 0xf1, 0x49, 0xf4, 0x0d, 0xd8,
0xf3, 0xf9, 0xf9, 0xd1, 0xd9, 0x82, 0xf4, 0xc4, 0x03, 0xd8, 0xde, 0xdf, 0xd8, 0xf1, 0xad, 0x88,
0x98, 0xcc, 0xa8, 0x09, 0xf9, 0xd9, 0x82, 0x92, 0xa8, 0xf5, 0x7c, 0xf1, 0x88, 0x3a, 0xcf, 0x94,
0x4a, 0x6e, 0x98, 0xdb, 0x69, 0x31, 0xda, 0xad, 0xf2, 0xde, 0xf9, 0xd8, 0x87, 0x95, 0xa8, 0xf2,
0x21, 0xd1, 0xda, 0xa5, 0xf9, 0xf4, 0x17, 0xd9, 0xf1, 0xae, 0x8e, 0xd0, 0xc0, 0xc3, 0xae, 0x82,
/* bank # 6 */
0xc6, 0x84, 0xc3, 0xa8, 0x85, 0x95, 0xc8, 0xa5, 0x88, 0xf2, 0xc0, 0xf1, 0xf4, 0x01, 0x0e, 0xf1,
0x8e, 0x9e, 0xa8, 0xc6, 0x3e, 0x56, 0xf5, 0x54, 0xf1, 0x88, 0x72, 0xf4, 0x01, 0x15, 0xf1, 0x98,
0x45, 0x85, 0x6e, 0xf5, 0x8e, 0x9e, 0x04, 0x88, 0xf1, 0x42, 0x98, 0x5a, 0x8e, 0x9e, 0x06, 0x88,
0x69, 0xf4, 0x01, 0x1c, 0xf1, 0x98, 0x1e, 0x11, 0x08, 0xd0, 0xf5, 0x04, 0xf1, 0x1e, 0x97, 0x02,
0x02, 0x98, 0x36, 0x25, 0xdb, 0xf9, 0xd9, 0x85, 0xa5, 0xf3, 0xc1, 0xda, 0x85, 0xa5, 0xf3, 0xdf,
0xd8, 0x85, 0x95, 0xa8, 0xf3, 0x09, 0xda, 0xa5, 0xfa, 0xd8, 0x82, 0x92, 0xa8, 0xf5, 0x78, 0xf1,
0x88, 0x1a, 0x84, 0x9f, 0x26, 0x88, 0x98, 0x21, 0xda, 0xf4, 0x1d, 0xf3, 0xd8, 0x87, 0x9f, 0x39,
0xd1, 0xaf, 0xd9, 0xdf, 0xdf, 0xfb, 0xf9, 0xf4, 0x0c, 0xf3, 0xd8, 0xfa, 0xd0, 0xf8, 0xda, 0xf9,
0xf9, 0xd0, 0xdf, 0xd9, 0xf9, 0xd8, 0xf4, 0x0b, 0xd8, 0xf3, 0x87, 0x9f, 0x39, 0xd1, 0xaf, 0xd9,
0xdf, 0xdf, 0xf4, 0x1d, 0xf3, 0xd8, 0xfa, 0xfc, 0xa8, 0x69, 0xf9, 0xf9, 0xaf, 0xd0, 0xda, 0xde,
0xfa, 0xd9, 0xf8, 0x8f, 0x9f, 0xa8, 0xf1, 0xcc, 0xf3, 0x98, 0xdb, 0x45, 0xd9, 0xaf, 0xdf, 0xd0,
0xf8, 0xd8, 0xf1, 0x8f, 0x9f, 0xa8, 0xca, 0xf3, 0x88, 0x09, 0xda, 0xaf, 0x8f, 0xcb, 0xf8, 0xd8,
0xf2, 0xad, 0x97, 0x8d, 0x0c, 0xd9, 0xa5, 0xdf, 0xf9, 0xba, 0xa6, 0xf3, 0xfa, 0xf4, 0x12, 0xf2,
0xd8, 0x95, 0x0d, 0xd1, 0xd9, 0xba, 0xa6, 0xf3, 0xfa, 0xda, 0xa5, 0xf2, 0xc1, 0xba, 0xa6, 0xf3,
0xdf, 0xd8, 0xf1, 0xba, 0xb2, 0xb6, 0x86, 0x96, 0xa6, 0xd0, 0xca, 0xf3, 0x49, 0xda, 0xa6, 0xcb,
0xf8, 0xd8, 0xb0, 0xb4, 0xb8, 0xd8, 0xad, 0x84, 0xf2, 0xc0, 0xdf, 0xf1, 0x8f, 0xcb, 0xc3, 0xa8,
/* bank # 7 */
0xb2, 0xb6, 0x86, 0x96, 0xc8, 0xc1, 0xcb, 0xc3, 0xf3, 0xb0, 0xb4, 0x88, 0x98, 0xa8, 0x21, 0xdb,
0x71, 0x8d, 0x9d, 0x71, 0x85, 0x95, 0x21, 0xd9, 0xad, 0xf2, 0xfa, 0xd8, 0x85, 0x97, 0xa8, 0x28,
0xd9, 0xf4, 0x08, 0xd8, 0xf2, 0x8d, 0x29, 0xda, 0xf4, 0x05, 0xd9, 0xf2, 0x85, 0xa4, 0xc2, 0xf2,
0xd8, 0xa8, 0x8d, 0x94, 0x01, 0xd1, 0xd9, 0xf4, 0x11, 0xf2, 0xd8, 0x87, 0x21, 0xd8, 0xf4, 0x0a,
0xd8, 0xf2, 0x84, 0x98, 0xa8, 0xc8, 0x01, 0xd1, 0xd9, 0xf4, 0x11, 0xd8, 0xf3, 0xa4, 0xc8, 0xbb,
0xaf, 0xd0, 0xf2, 0xde, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xd8, 0xf1, 0xb8, 0xf6,
0xb5, 0xb9, 0xb0, 0x8a, 0x95, 0xa3, 0xde, 0x3c, 0xa3, 0xd9, 0xf8, 0xd8, 0x5c, 0xa3, 0xd9, 0xf8,
0xd8, 0x7c, 0xa3, 0xd9, 0xf8, 0xd8, 0xf8, 0xf9, 0xd1, 0xa5, 0xd9, 0xdf, 0xda, 0xfa, 0xd8, 0xb1,
0x85, 0x30, 0xf7, 0xd9, 0xde, 0xd8, 0xf8, 0x30, 0xad, 0xda, 0xde, 0xd8, 0xf2, 0xb4, 0x8c, 0x99,
0xa3, 0x2d, 0x55, 0x7d, 0xa0, 0x83, 0xdf, 0xdf, 0xdf, 0xb5, 0x91, 0xa0, 0xf6, 0x29, 0xd9, 0xfb,
0xd8, 0xa0, 0xfc, 0x29, 0xd9, 0xfa, 0xd8, 0xa0, 0xd0, 0x51, 0xd9, 0xf8, 0xd8, 0xfc, 0x51, 0xd9,
0xf9, 0xd8, 0x79, 0xd9, 0xfb, 0xd8, 0xa0, 0xd0, 0xfc, 0x79, 0xd9, 0xfa, 0xd8, 0xa1, 0xf9, 0xf9,
0xf9, 0xf9, 0xf9, 0xa0, 0xda, 0xdf, 0xdf, 0xdf, 0xd8, 0xa1, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xac,
0xde, 0xf8, 0xad, 0xde, 0x83, 0x93, 0xac, 0x2c, 0x54, 0x7c, 0xf1, 0xa8, 0xdf, 0xdf, 0xdf, 0xf6,
0x9d, 0x2c, 0xda, 0xa0, 0xdf, 0xd9, 0xfa, 0xdb, 0x2d, 0xf8, 0xd8, 0xa8, 0x50, 0xda, 0xa0, 0xd0,
0xde, 0xd9, 0xd0, 0xf8, 0xf8, 0xf8, 0xdb, 0x55, 0xf8, 0xd8, 0xa8, 0x78, 0xda, 0xa0, 0xd0, 0xdf,
/* bank # 8 */
0xd9, 0xd0, 0xfa, 0xf8, 0xf8, 0xf8, 0xf8, 0xdb, 0x7d, 0xf8, 0xd8, 0x9c, 0xa8, 0x8c, 0xf5, 0x30,
0xdb, 0x38, 0xd9, 0xd0, 0xde, 0xdf, 0xa0, 0xd0, 0xde, 0xdf, 0xd8, 0xa8, 0x48, 0xdb, 0x58, 0xd9,
0xdf, 0xd0, 0xde, 0xa0, 0xdf, 0xd0, 0xde, 0xd8, 0xa8, 0x68, 0xdb, 0x70, 0xd9, 0xdf, 0xdf, 0xa0,
0xdf, 0xdf, 0xd8, 0xf1, 0xa8, 0x88, 0x90, 0x2c, 0x54, 0x7c, 0x98, 0xa8, 0xd0, 0x5c, 0x38, 0xd1,
0xda, 0xf2, 0xae, 0x8c, 0xdf, 0xf9, 0xd8, 0xb0, 0x87, 0xa8, 0xc1, 0xc1, 0xb1, 0x88, 0xa8, 0xc6,
0xf9, 0xf9, 0xda, 0x36, 0xd8, 0xa8, 0xf9, 0xda, 0x36, 0xd8, 0xa8, 0xf9, 0xda, 0x36, 0xd8, 0xa8,
0xf9, 0xda, 0x36, 0xd8, 0xa8, 0xf9, 0xda, 0x36, 0xd8, 0xf7, 0x8d, 0x9d, 0xad, 0xf8, 0x18, 0xda,
0xf2, 0xae, 0xdf, 0xd8, 0xf7, 0xad, 0xfa, 0x30, 0xd9, 0xa4, 0xde, 0xf9, 0xd8, 0xf2, 0xae, 0xde,
0xfa, 0xf9, 0x83, 0xa7, 0xd9, 0xc3, 0xc5, 0xc7, 0xf1, 0x88, 0x9b, 0xa7, 0x7a, 0xad, 0xf7, 0xde,
0xdf, 0xa4, 0xf8, 0x84, 0x94, 0x08, 0xa7, 0x97, 0xf3, 0x00, 0xae, 0xf2, 0x98, 0x19, 0xa4, 0x88,
0xc6, 0xa3, 0x94, 0x88, 0xf6, 0x32, 0xdf, 0xf2, 0x83, 0x93, 0xdb, 0x09, 0xd9, 0xf2, 0xaa, 0xdf,
0xd8, 0xd8, 0xae, 0xf8, 0xf9, 0xd1, 0xda, 0xf3, 0xa4, 0xde, 0xa7, 0xf1, 0x88, 0x9b, 0x7a, 0xd8,
0xf3, 0x84, 0x94, 0xae, 0x19, 0xf9, 0xda, 0xaa, 0xf1, 0xdf, 0xd8, 0xa8, 0x81, 0xc0, 0xc3, 0xc5,
0xc7, 0xa3, 0x92, 0x83, 0xf6, 0x28, 0xad, 0xde, 0xd9, 0xf8, 0xd8, 0xa3, 0x50, 0xad, 0xd9, 0xf8,
0xd8, 0xa3, 0x78, 0xad, 0xd9, 0xf8, 0xd8, 0xf8, 0xf9, 0xd1, 0xa1, 0xda, 0xde, 0xc3, 0xc5, 0xc7,
0xd8, 0xa1, 0x81, 0x94, 0xf8, 0x18, 0xf2, 0xb0, 0x89, 0xac, 0xc3, 0xc5, 0xc7, 0xf1, 0xd8, 0xb8,
/* bank # 9 */
0xb4, 0xb0, 0x97, 0x86, 0xa8, 0x31, 0x9b, 0x06, 0x99, 0x07, 0xab, 0x97, 0x28, 0x88, 0x9b, 0xf0,
0x0c, 0x20, 0x14, 0x40, 0xb0, 0xb4, 0xb8, 0xf0, 0xa8, 0x8a, 0x9a, 0x28, 0x50, 0x78, 0xb7, 0x9b,
0xa8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31, 0xf1, 0xbb, 0xab,
0x88, 0x00, 0x2c, 0x54, 0x7c, 0xf0, 0xb3, 0x8b, 0xb8, 0xa8, 0x04, 0x28, 0x50, 0x78, 0xf1, 0xb0,
0x88, 0xb4, 0x97, 0x26, 0xa8, 0x59, 0x98, 0xbb, 0xab, 0xb3, 0x8b, 0x02, 0x26, 0x46, 0x66, 0xb0,
0xb8, 0xf0, 0x8a, 0x9c, 0xa8, 0x29, 0x51, 0x79, 0x8b, 0x29, 0x51, 0x79, 0x8a, 0x24, 0x70, 0x59,
0x8b, 0x20, 0x58, 0x71, 0x8a, 0x44, 0x69, 0x38, 0x8b, 0x39, 0x40, 0x68, 0x8a, 0x64, 0x48, 0x31,
0x8b, 0x30, 0x49, 0x60, 0x88, 0xf1, 0xac, 0x00, 0x2c, 0x54, 0x7c, 0xf0, 0x8c, 0xa8, 0x04, 0x28,
0x50, 0x78, 0xf1, 0x88, 0x97, 0x26, 0xa8, 0x59, 0x98, 0xac, 0x8c, 0x02, 0x26, 0x46, 0x66, 0xf0,
0x89, 0x9c, 0xa8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31, 0xa9,
0x88, 0x09, 0x20, 0x59, 0x70, 0xab, 0x11, 0x38, 0x40, 0x69, 0xa8, 0x19, 0x31, 0x48, 0x60, 0x8c,
0xa8, 0x3c, 0x41, 0x5c, 0x20, 0x7c, 0x00, 0xf1, 0x87, 0x98, 0x19, 0x86, 0xa8, 0x6e, 0x76, 0x7e,
0xa9, 0x99, 0x88, 0x2d, 0x55, 0x7d, 0xd8, 0xb1, 0xb5, 0xb9, 0xa3, 0xdf, 0xdf, 0xdf, 0xae, 0xd0,
0xdf, 0xaa, 0xd0, 0xde, 0xf2, 0xab, 0xf8, 0xf9, 0xd9, 0xb0, 0x87, 0xc4, 0xaa, 0xf1, 0xdf, 0xdf,
0xbb, 0xaf, 0xdf, 0xdf, 0xb9, 0xd8, 0xb1, 0xf1, 0xa3, 0x97, 0x8e, 0x60, 0xdf, 0xb0, 0x84, 0xf2,
0xc8, 0xf8, 0xf9, 0xd9, 0xde, 0xd8, 0x93, 0x85, 0xf1, 0x4a, 0xb1, 0x83, 0xa3, 0x08, 0xb5, 0x83,
/* bank # 10 */
0x9a, 0x08, 0x10, 0xb7, 0x9f, 0x10, 0xd8, 0xf1, 0xb0, 0xba, 0xae, 0xb0, 0x8a, 0xc2, 0xb2, 0xb6,
0x8e, 0x9e, 0xf1, 0xfb, 0xd9, 0xf4, 0x1d, 0xd8, 0xf9, 0xd9, 0x0c, 0xf1, 0xd8, 0xf8, 0xf8, 0xad,
0x61, 0xd9, 0xae, 0xfb, 0xd8, 0xf4, 0x0c, 0xf1, 0xd8, 0xf8, 0xf8, 0xad, 0x19, 0xd9, 0xae, 0xfb,
0xdf, 0xd8, 0xf4, 0x16, 0xf1, 0xd8, 0xf8, 0xad, 0x8d, 0x61, 0xd9, 0xf4, 0xf4, 0xac, 0xf5, 0x9c,
0x9c, 0x8d, 0xdf, 0x2b, 0xba, 0xb6, 0xae, 0xfa, 0xf8, 0xf4, 0x0b, 0xd8, 0xf1, 0xae, 0xd0, 0xf8,
0xad, 0x51, 0xda, 0xae, 0xfa, 0xf8, 0xf1, 0xd8, 0xb9, 0xb1, 0xb6, 0xa3, 0x83, 0x9c, 0x08, 0xb9,
0xb1, 0x83, 0x9a, 0xb5, 0xaa, 0xc0, 0xfd, 0x30, 0x83, 0xb7, 0x9f, 0x10, 0xb5, 0x8b, 0x93, 0xf2,
0x02, 0x02, 0xd1, 0xab, 0xda, 0xde, 0xd8, 0xf1, 0xb0, 0x80, 0xba, 0xab, 0xc0, 0xc3, 0xb2, 0x84,
0xc1, 0xc3, 0xd8, 0xb1, 0xb9, 0xf3, 0x8b, 0xa3, 0x91, 0xb6, 0x09, 0xb4, 0xd9, 0xab, 0xde, 0xb0,
0x87, 0x9c, 0xb9, 0xa3, 0xdd, 0xf1, 0xb3, 0x8b, 0x8b, 0x8b, 0x8b, 0x8b, 0xb0, 0x87, 0xa3, 0xa3,
0xa3, 0xa3, 0xb2, 0x8b, 0xb6, 0x9b, 0xf2, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3,
0xa3, 0xf1, 0xb0, 0x87, 0xb5, 0x9a, 0xa3, 0xf3, 0x9b, 0xa3, 0xa3, 0xdc, 0xba, 0xac, 0xdf, 0xb9,
0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3,
0xd8, 0xd8, 0xd8, 0xbb, 0xb3, 0xb7, 0xf1, 0xaa, 0xf9, 0xda, 0xff, 0xd9, 0x80, 0x9a, 0xaa, 0x28,
0xb4, 0x80, 0x98, 0xa7, 0x20, 0xb7, 0x97, 0x87, 0xa8, 0x66, 0x88, 0xf0, 0x79, 0x51, 0xf1, 0x90,
0x2c, 0x87, 0x0c, 0xa7, 0x81, 0x97, 0x62, 0x93, 0xf0, 0x71, 0x71, 0x60, 0x85, 0x94, 0x01, 0x29,
/* bank # 11 */
0x51, 0x79, 0x90, 0xa5, 0xf1, 0x28, 0x4c, 0x6c, 0x87, 0x0c, 0x95, 0x18, 0x85, 0x78, 0xa3, 0x83,
0x90, 0x28, 0x4c, 0x6c, 0x88, 0x6c, 0xd8, 0xf3, 0xa2, 0x82, 0x00, 0xf2, 0x10, 0xa8, 0x92, 0x19,
0x80, 0xa2, 0xf2, 0xd9, 0x26, 0xd8, 0xf1, 0x88, 0xa8, 0x4d, 0xd9, 0x48, 0xd8, 0x96, 0xa8, 0x39,
0x80, 0xd9, 0x3c, 0xd8, 0x95, 0x80, 0xa8, 0x39, 0xa6, 0x86, 0x98, 0xd9, 0x2c, 0xda, 0x87, 0xa7,
0x2c, 0xd8, 0xa8, 0x89, 0x95, 0x19, 0xa9, 0x80, 0xd9, 0x38, 0xd8, 0xa8, 0x89, 0x39, 0xa9, 0x80,
0xda, 0x3c, 0xd8, 0xa8, 0x2e, 0xa8, 0x39, 0x90, 0xd9, 0x0c, 0xd8, 0xa8, 0x95, 0x31, 0x98, 0xd9,
0x0c, 0xd8, 0xa8, 0x09, 0xd9, 0xff, 0xd8, 0x01, 0xda, 0xff, 0xd8, 0x95, 0x39, 0xa9, 0xda, 0x26,
0xff, 0xd8, 0x90, 0xa8, 0x0d, 0x89, 0x99, 0xa8, 0x10, 0x80, 0x98, 0x21, 0xda, 0x2e, 0xd8, 0x89,
0x99, 0xa8, 0x31, 0x80, 0xda, 0x2e, 0xd8, 0xa8, 0x86, 0x96, 0x31, 0x80, 0xda, 0x2e, 0xd8, 0xa8,
0x87, 0x31, 0x80, 0xda, 0x2e, 0xd8, 0xa8, 0x82, 0x92, 0xf3, 0x41, 0x80, 0xf1, 0xd9, 0x2e, 0xd8,
0xa8, 0x82, 0xf3, 0x19, 0x80, 0xf1, 0xd9, 0x2e, 0xd8, 0x82, 0xac, 0xf3, 0xc0, 0xa2, 0x80, 0x22,
0xf1, 0xa6, 0x2e, 0xa7, 0x2e, 0xa9, 0x22, 0x98, 0xa8, 0x29, 0xda, 0xac, 0xde, 0xff, 0xd8, 0xa2,
0xf2, 0x2a, 0xf1, 0xa9, 0x2e, 0x82, 0x92, 0xa8, 0xf2, 0x31, 0x80, 0xa6, 0x96, 0xf1, 0xd9, 0x00,
0xac, 0x8c, 0x9c, 0x0c, 0x30, 0xac, 0xde, 0xd0, 0xde, 0xff, 0xd8, 0x8c, 0x9c, 0xac, 0xd0, 0x10,
0xac, 0xde, 0x80, 0x92, 0xa2, 0xf2, 0x4c, 0x82, 0xa8, 0xf1, 0xca, 0xf2, 0x35, 0xf1, 0x96, 0x88,
0xa6, 0xd9, 0x00, 0xd8, 0xf1, 0xff
};

static signed char gyro_orientation[9] = {-1, 0, 0,
0,-1, 0,
0, 0, 1};
// dmp_set_fifo_rate用
const unsigned char regs_end[12] = {0xFE, 0xF2, 0xAB, 0xc4, 0xAA, 0xF1, 0xDF, 0xDF, 0xBB, 0xAF, 0xDF, 0xDF};

unsigned short inv_row_2_scale(const signed char *row)
{
  unsigned short b;
  
  if (row[0] > 0) 		b = 0;
  else if (row[0] < 0) 	b = 4;
  else if (row[1] > 0) 	b = 1;
  else if (row[1] < 0) 	b = 5;
  else if (row[2] > 0) 	b = 2;
  else if (row[2] < 0) 	b = 6;
  else 					b = 7;      // error
  return b;
}

// DMP初始化，初始化原函数调用顺序为
/* 	inv_mpu.c						mpu_init()
* 	inv_mpu.c						mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL)
* 	inv_mpu.c						mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)
* 	inv_mpu.c						mpu_set_sample_rate(DEFAULT_MPU_HZ)
* 	inv_mpu_dmp_motion_driver.c		dmp_load_motion_driver_firmware()
* 	inv_mpu_dmp_motion_driver.c		dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))
* 	inv_mpu_dmp_motion_driver.c		dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL)
* 	inv_mpu_dmp_motion_driver.c		dmp_set_fifo_rate(DEFAULT_MPU_HZ)
* 	inv_mpu.c						mpu_run_self_test(gyro, accel)
* 	inv_mpu.c						mpu_set_dmp_state(1)
**************************************************************************/
int LQ_DMP_Init(void)
{
  unsigned char lqda[6], rev;
  // firmware用
  unsigned short   ii;
  unsigned short   this_write;
  unsigned char cur[16];
  unsigned char tmp[10];			// firmware只用2个，dmp_enable_feature用10个
  // dmp_set_orientation用
  unsigned short scalar;
  
  lqda[0] = 0x80; if(LQ_I2C_Write(0x68, 0x6B, 1, &(lqda[0])))	return 1;	// 复位
  delayms(100);														// 延迟
  lqda[0] = 0x00; if(LQ_I2C_Write(0x68, 0x6B, 1, &(lqda[0])))	return 2;	// 唤醒6050
  
  if(LQ_I2C_Read(0x68, 0x06, 6, lqda)) return 3;							// 读0x06寄存器
  
  rev = ((lqda[5] & 0x01) << 2) | ((lqda[3] & 0x01) << 1) | (lqda[1] & 0x01); // 读时序得到的值一直是固定的，rev等于0x10
  if(rev != 2) return 4;										// 这之后st.chip_cfg.accel_half = 0;
  
  if(mpu_set_gyro_fsr(2000)) 	return 5;								// 这之后st.chip_cfg.gyro_fsr = 3;
  if(mpu_set_accel_fsr(2)) 	return 6;								// 这之后st.chip_cfg.accel_fsr = 0;
  if(mpu_set_lpf(42)) 		return 7;								// 这之后st.chip_cfg.lpf = 3;
  if(mpu_set_sample_rate(50)) return 8;								// 这之后st.chip_cfg.sample_rate = 50;
  
  // mpu_configure_fifo(0);
  lqda[0] = 0x00; if(LQ_I2C_Write(0x68, 0x38, 1, &(lqda[0]))) return 10;	// 这之后st.chip_cfg.int_enable = 0;
  
  // mpu_set_bypass(0);
  lqda[0] = 0x00; if(LQ_I2C_Read(0x68, 0x6A, 1, &(lqda[0]))) 	return 11;
  lqda[0] = 0x20; if(LQ_I2C_Write(0x68, 0x6A, 1, &(lqda[0]))) return 12;
  delayms(3);
  lqda[0] = 0x80; if(LQ_I2C_Write(0x68, 0x37, 1, &(lqda[0]))) return 13;	// 这之后st.chip_cfg.bypass_mode = 0;
  
  //mpu_set_sensors(0);
  lqda[0] = 0x40; if(LQ_I2C_Write(0x68, 0x6B, 1, &(lqda[0]))) return 14; 	// 这之后st.chip_cfg.clk_src = 0;
  lqda[0] = 0x3F; if(LQ_I2C_Write(0x68, 0x6C, 1, &(lqda[0]))) return 15; 	// 这之后st.chip_cfg.sensors = 0; 														   
  //      st.chip_cfg.lp_accel_mode = 0;
  delayms(50);
  // 结束mpu_init()
  
  // mpu_set_sensors(0x70 | 0x08)  
  lqda[0] = 0x01; if(LQ_I2C_Write(0x68, 0x6B, 1,  &(lqda[0]))) return 16; // 这之后st.chip_cfg.clk_src = 0x01;
  
  lqda[0] = 0x00; if(LQ_I2C_Write(0x68, 0x6C, 1,  &(lqda[0]))) return 17;
  // 实际未运行mpu_set_int_latched(0);
  // 在这之后st.chip_cfg.sensors = 0x78; 
  // 	      st.chip_cfg.lp_accel_mode = 0;
  delayms(50);
  // 结束
  
  // mpu_configure_fifo(0x70 | 0x08)									// 在这之后st.chip_cfg.fifo_enable = 0x78;							
  // 其中set_int_enable(1);
  lqda[0] = 0x01; if(LQ_I2C_Write(0x68, 0x38, 1, &(lqda[0]))) return 18;	// 在这之后st.chip_cfg.int_enable = 0x01;
  // 其中mpu_reset_fifo(void)
  lqda[0] = 0x00; if(LQ_I2C_Write(0x68, 0x38, 1, &(lqda[0]))) return 19;
  lqda[0] = 0x00; if(LQ_I2C_Write(0x68, 0x23, 1, &(lqda[0]))) return 20;
  lqda[0] = 0x00; if(LQ_I2C_Write(0x68, 0x6A, 1, &(lqda[0]))) return 21;
  lqda[0] = 0x04; if(LQ_I2C_Write(0x68, 0x6A, 1, &(lqda[0]))) return 22;
  lqda[0] = 0x40; if(LQ_I2C_Write(0x68, 0x6A, 1, &(lqda[0]))) return 23;
  lqda[0] = 0x01; if(LQ_I2C_Write(0x68, 0x38, 1, &(lqda[0]))) return 24;
  lqda[0] = 0x78; if(LQ_I2C_Write(0x68, 0x23, 1, &(lqda[0]))) return 25;
  // 结束
  
  // mpu_set_sample_rate(DEFAULT_MPU_HZ)
  mpu_set_sample_rate(200);
  // 结束
  
  // dmp_load_motion_driver_firmware()
  // 其中mpu_load_firmware(DMP_CODE_SIZE, dmp_memory, sStartAddress, DMP_SAMPLE_RATE);
  // mpu_load_firmware(3062, dmp_memory, 0x0400, 200);
  for (ii = 0; ii < 3062; ii += this_write)
  {
    this_write = min(16, 3062 - ii);
    if(mpu_write_mem(ii, this_write, (unsigned char*)&dmp_memory[ii])) return -1;
    if(mpu_read_mem(ii, this_write, cur)) return -1;
    if(memcmp(dmp_memory+ii, cur, this_write)) return -1;
  }
  tmp[0] = 0x04; tmp[1] = 0x00; if(LQ_I2C_Write(0x68, 0x70, 2, tmp)) return -1;	// 这之后st.chip_cfg.dmp_loaded = 1; 
  //		st.chip_cfg.dmp_sample_rate = 200;
  // 结束
  
  // dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))
  // 其中inv_orientation_matrix_to_scalar(gyro_orientation)  
  scalar = inv_row_2_scale(gyro_orientation);
  scalar |= inv_row_2_scale(gyro_orientation + 3) << 3;
  scalar |= inv_row_2_scale(gyro_orientation + 6) << 6;
  dmp_set_orientation(scalar);												// 在这之后dmp.orient = scalar;
  // 结束
  
  // dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL)
  //  				  0x010 | 0x001 | 0x002 | 0x040 | 0x100 | 0x020 = 0x173
  /* Set integration scale factor. */
  tmp[0] = 0x02;
  tmp[1] = 0xCA;
  tmp[2] = 0xE3;
  tmp[3] = 0x09;
  mpu_write_mem(104, 4, tmp);
  
  /* Send sensor lqda to the FIFO. */
  tmp[0] = 0xA3;
  tmp[1] = 0xC0;
  tmp[2] = 0xC8;
  tmp[3] = 0xC2;
  tmp[4] = 0xC4;
  tmp[5] = 0xCC;
  tmp[6] = 0xC6;
  tmp[7] = 0xA3;
  tmp[8] = 0xA3;
  tmp[9] = 0xA3;
  mpu_write_mem(2727,10,tmp);
  
  /* Send gesture lqda to the FIFO. */
  tmp[0] = 0x20;
  mpu_write_mem(2742,1,tmp);
  
  //    dmp_enable_gyro_cal(1);
  tmp[0] = 0xb8;
  tmp[1] = 0xaa;
  tmp[2] = 0xb3;
  tmp[3] = 0x8d;
  tmp[4] = 0xb4;
  tmp[5] = 0x98;
  tmp[6] = 0x0d;
  tmp[7] = 0x35;
  tmp[8] = 0x5d;
  mpu_write_mem(1208, 9, tmp);
  
  tmp[0] = 0xB2;
  tmp[1] = 0x8B;
  tmp[2] = 0xB6;
  tmp[3] = 0x9B;
  mpu_write_mem(2722, 4, tmp);
  
  /* Enable tap. */
  tmp[0] = 0xF8;
  mpu_write_mem(2224, 1, tmp);
  
  //    dmp_set_tap_thresh(0x07, 250);
  tmp[0] = 0x50;
  tmp[1] = 0x00;
  tmp[2] = 0x3C;
  tmp[3] = 0x00;
  if (mpu_write_mem(468, 2, tmp)) return -1;
  if (mpu_write_mem(292, 2, tmp+2)) return -1;
  if (mpu_write_mem(472, 2, tmp)) return -1;
  if (mpu_write_mem(296, 2, tmp+2)) return -1;
  if (mpu_write_mem(476, 2, tmp)) return -1;
  if (mpu_write_mem(300, 2, tmp+2)) return -1;
  
  //    dmp_set_tap_axes(0x07);
  tmp[0] = 0x3F;
  if (mpu_write_mem(328, 1, tmp)) return -1;
  
  //    dmp_set_tap_count(1);
  tmp[0] = 0x00;
  if (mpu_write_mem(335, 1, tmp)) return -1;
  
  //    dmp_set_tap_time(100);
  tmp[0] = 0x00;
  tmp[1] = 0x14;
  if (mpu_write_mem(478, 2, tmp))	return -1;
  
  //    dmp_set_tap_time_multi(500);
  tmp[0] = 0x00;
  tmp[1] = 0x64;
  if (mpu_write_mem(474, 2, tmp))	return -1;
  
  //    dmp_set_shake_reject_thresh(GYRO_SF, 200);
  tmp[0] = 0x00;
  tmp[1] = 0x00;
  tmp[2] = 0x00;
  tmp[3] = 0xEA;
  if (mpu_write_mem(348, 4, tmp)) return -1;
  
  //    dmp_set_shake_reject_time(40);
  tmp[0] = 0x00;
  tmp[1] = 0x08;
  if (mpu_write_mem(346, 2, tmp)) return -1;
  
  //    dmp_set_shake_reject_timeout(10);
  tmp[0] = 0x00;
  tmp[1] = 0x02;
  if (mpu_write_mem(344, 2, tmp)) return -1;
  
  //
  tmp[0] = 0xD9;
  mpu_write_mem(1853, 1, tmp);
  
  //    dmp_enable_lp_quat(0);
  memset(tmp, 0x8B, 4);
  if (mpu_write_mem(2712, 4, tmp)) return -1;
  mpu_reset_fifo_in_dmp_enable_feature();
  
  //	dmp_enable_6x_lp_quat(1);
  tmp[0] = 0x20;
  tmp[1] = 0x28;
  tmp[2] = 0x30;
  tmp[3] = 0x38;
  mpu_write_mem(2718, 4, tmp);
  mpu_reset_fifo_in_dmp_enable_feature();
  
  /* Pedometer is always enabled. */
  mpu_reset_fifo_in_dmp_enable_feature();
  // 																在这之后 dmp.feature_mask = 0x17B; 
  //		   																dmp.packet_length = 32;
  // 结束
  
  // dmp_set_fifo_rate(DEFAULT_MPU_HZ)
  // dmp_set_fifo_rate(200)
  tmp[0] = 0x00;
  tmp[1] = 0x01;
  if (mpu_write_mem(534, 2, tmp)) return -1;
  if (mpu_write_mem(2753, 12, (unsigned char*)regs_end)) return -1;
  // 																在这之后 dmp.fifo_rate = 200;
  // 结束
  
  // run_self_test();
  
  /* 待测试 */
  
  // 结束
  
  // mpu_set_dmp_state(1)
  /* Disable lqda ready interrupt. */
  //    set_int_enable(0);
  tmp[0] = 0x00;
  if (LQ_I2C_Write(0x68, 0x38, 1, tmp)) return -1; 					// 在这之后st.chip_cfg.int_enable = 0;
  
  /* Disable bypass mode. */
  //实际未运行mpu_set_bypass(0);
  /* Keep constant sample rate, FIFO rate controlled by DMP. */
  mpu_set_sample_rate(200);
  /* Remove FIFO elements. */
  tmp[0] = 0x00;
  if (LQ_I2C_Write(0x68, 0x23, 1, tmp)) return -1;					// 在这之后st.chip_cfg.dmp_on = 1;
  /* Enable DMP interrupt. */
  //    set_int_enable(1); 
  tmp[0] = 0x02;
  if (LQ_I2C_Write(0x68, 0x38, 1, tmp)) return -1;					// 在这之后st.chip_cfg.int_enable = 0x02;
  mpu_reset_fifo_in_mpu_set_dmp_state();
  // 结束
  
  return 0;
}

// 陀螺仪测量范围
int mpu_set_gyro_fsr(unsigned short fsr)
{
  unsigned char lqda = 0;
  
  switch(fsr) 
  {
  case 250: lqda = 0 << 3; break;
  case 500: lqda = 1 << 3; break;
  case 1000: lqda = 2 << 3; break;
  case 2000: lqda = 3 << 3; break;
  default: return -1;
  }
  if(LQ_I2C_Write(0x68, 0x1B, 1, &lqda)) return -1;
  
  return 0;
}

// 加速度计测量范围
int mpu_set_accel_fsr(unsigned char fsr)
{
  unsigned char lqda = 0;
  
  switch (fsr) 
  {
  case 2: lqda = 0 << 3; break;
  case 4: lqda = 1 << 3; break;
  case 8: lqda = 2 << 3; break;
  case 16: lqda = 3 << 3; break;
  default : return -1;
  }
  
  if (LQ_I2C_Write(0x68, 0x1C, 1, &lqda)) return -1;
  
  return 0;
}

// 设置数字低通滤波
int mpu_set_lpf(unsigned short lpf)
{
  unsigned char lqda = 0;
  
  if (lpf >= 188) 		lqda = 1;
  else if (lpf >= 98) 	lqda = 2;
  else if (lpf >= 42) 	lqda = 3;
  else if (lpf >= 20) 	lqda = 4;
  else if (lpf >= 10) 	lqda = 5;
  else lqda = 6;
  
  if (LQ_I2C_Write(0x68, 0x1A, 1, &lqda)) return -1;
  
  return 0;
}

// 设置采样频率
int mpu_set_sample_rate(unsigned short rate)
{
  unsigned char lqda;
  
  if(rate < 4) 			rate = 4;
  else if(rate > 1000) 	rate = 1000;
  
  lqda = 1000 / rate - 1;
  if(LQ_I2C_Write(0x68, 0x19, 1, &lqda)) return -1;
  
  mpu_set_lpf(lqda>>2);
  return 0;
}

int dmp_set_orientation(unsigned short orient)
{
  unsigned char gyro_regs[3], accel_regs[3];
  const unsigned char gyro_axes[3] = {0x4C, 0xCD, 0x6C};
  const unsigned char accel_axes[3] = {0x0C, 0xC9, 0x2C};
  const unsigned char gyro_sign[3] = {0x36, 0x56, 0x76};
  const unsigned char accel_sign[3] = {0x26, 0x46, 0x66};
  
  gyro_regs[0] = gyro_axes[orient & 3];
  gyro_regs[1] = gyro_axes[(orient >> 3) & 3];
  gyro_regs[2] = gyro_axes[(orient >> 6) & 3];
  accel_regs[0] = accel_axes[orient & 3];
  accel_regs[1] = accel_axes[(orient >> 3) & 3];
  accel_regs[2] = accel_axes[(orient >> 6) & 3];
  
  /* Chip-to-body, axes only. */
  if (mpu_write_mem(1062, 3, gyro_regs)) return -1;
  if (mpu_write_mem(1066, 3, accel_regs)) return -1;
  
  memcpy(gyro_regs, gyro_sign, 3);
  memcpy(accel_regs, accel_sign, 3);
  if (orient & 4) {
    gyro_regs[0] |= 1;
    accel_regs[0] |= 1;
  }
  if (orient & 0x20) {
    gyro_regs[1] |= 1;
    accel_regs[1] |= 1;
  }
  if (orient & 0x100) {
    gyro_regs[2] |= 1;
    accel_regs[2] |= 1;
  }
  
  /* Chip-to-body, sign only. */
  if (mpu_write_mem(1088, 3, gyro_regs)) return -1;
  if (mpu_write_mem(1073, 3, accel_regs)) return -1;
  return 0;
}
// mpu写函数，mem_addr一般为16位，先从高到低发送16位地址到0x6D寄存器，再发送length长度的数据到0x6F寄存器
int mpu_write_mem(unsigned short mem_addr, unsigned short length, unsigned char *lqda)
{
  unsigned char tmp[2];
  
  if (!lqda)
    return -1;
  
  tmp[0] = (unsigned char)(mem_addr >> 8);
  tmp[1] = (unsigned char)(mem_addr & 0xFF);
  
  /* Check bank boundaries. */
  if (tmp[1] + length > 256)
    return -1;
  
  if (LQ_I2C_Write(0x68, 0x6D, 2, tmp))
    return -1;
  if (LQ_I2C_Write(0x68, 0x6F, length, lqda))
    return -1;
  return 0;
}
// mpu读函数，mem_addr一般为16位，先从高到低发送16位地址到0x6D寄存器，再从0x6F寄存器读取length长度的数据到lqda
int mpu_read_mem(unsigned short mem_addr, unsigned short length, unsigned char *lqda)
{
  unsigned char tmp[2];
  
  if (!lqda) return -1;
  
  tmp[0] = (unsigned char)(mem_addr >> 8);
  tmp[1] = (unsigned char)(mem_addr & 0xFF);
  
  /* Check bank boundaries. */
  if (tmp[1] + length > 256) return -1;
  
  if (LQ_I2C_Write(0x68, 0x6D, 2, tmp)) return -1;
  if (LQ_I2C_Read(0x68, 0x6F, length, lqda)) return -1;
  return 0;
}

// dmp_enable_feature用，dmp_on = 0
// 其它用需要重新写
int mpu_reset_fifo_in_dmp_enable_feature(void)
{
  unsigned char lqda;
  
  lqda = 0;
  if (LQ_I2C_Write(0x68, 0x38, 1, &lqda)) return -1;
  if (LQ_I2C_Write(0x68, 0x23, 1, &lqda)) return -1;
  if (LQ_I2C_Write(0x68, 0x6A, 1, &lqda)) return -1;
  lqda = 0x04;
  if (LQ_I2C_Write(0x68, 0x6A, 1, &lqda)) return -1;
  lqda = 0x40;
  if (LQ_I2C_Write(0x68, 0x6A, 1, &lqda)) return -1;
  lqda = 0x01;
  if (LQ_I2C_Write(0x68, 0x38, 1, &lqda)) return -1;
  lqda = 0x78;
  if (LQ_I2C_Write(0x68, 0x23, 1, &lqda)) return -1;
  
  return 0;
}

// dmp_on = 1
int mpu_reset_fifo_in_mpu_set_dmp_state(void)
{
  unsigned char lqda; 
  lqda = 0;
  if (LQ_I2C_Write(0x68, 0x38, 1, &lqda)) return -1;
  if (LQ_I2C_Write(0x68, 0x23, 1, &lqda)) return -1;
  if (LQ_I2C_Write(0x68, 0x6A, 1, &lqda)) return -1; 
  lqda = 0x0C;
  if (LQ_I2C_Write(0x68, 0x6A, 1, &lqda)) return -1; 
  lqda = 0xC0;
  if (LQ_I2C_Write(0x68, 0x6A, 1, &lqda)) return -1;
  lqda = 0x02;
  if (LQ_I2C_Write(0x68, 0x38, 1, &lqda)) return -1;
  lqda = 0x00;
  if (LQ_I2C_Write(0x68, 0x23, 1, &lqda)) return -1;
  return 0;
}

// 以下为从FIFO读取原始值并计算角度。

// q30需要定义为32位的浮点型
const double q30 = 1073741824.0;
float gyro_Roll,gyro_Pitch,gyro_Yaw;//XYZ三轴旋转角度、角速度
short   gyro[3], accel[3], sensors;
float   Pitch, Roll,Yaw;
float   q0 = 1.0f;
float   q1 = 0.0f;
float   q2 = 0.0f;
float   q3 = 0.0f;

int LQ_DMP_Read(void)
{
    unsigned char   more;
    double   temp = 0;
    long   quat[4];

    //unsigned char more;
    static float G_Y,Z_G_Y,G_P,Z_G_P,G_R,Z_G_R;
    static int i= 0;
        static int j = 0;


    if(dmp_read_fifo(gyro, accel, quat, &sensors, &more))
        return 1;
  
    if (sensors & 0x100 )
    {
        q0 = quat[0] / q30;
        q1 = quat[1] / q30;
        q2 = quat[2] / q30;
        q3 = quat[3] / q30;
        temp = -2 * q1 * q3 + 2 * q0* q2;
        //Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;
        if(temp == 1)
            return 2;
        else if(temp == -1)
            return 3;
        else if(temp < 0)
                        Roll = -atan( sqrt( temp * temp / (1 - temp * temp) ) ) * 57.3;
                else
                        Roll = +atan( sqrt( temp * temp / (1 - temp * temp) ) ) * 57.3;

        Pitch = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
        Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
        gyro_Pitch=gyro[0]-Z_G_P; //角速度手动调零
        gyro_Roll =gyro[1]-Z_G_R; //角速度手动调零
        gyro_Yaw  =gyro[2]-Z_G_Y; //角速度手动调零

        if(j==0&&gyro_Yaw<+150&&gyro_Yaw>-150)
                {   //静止等待2.5秒
                  i++;
                  if(i>=2)
                  {
                    G_Y+=gyro_Yaw;
                    G_P+=gyro_Pitch;
                    G_R+=gyro_Roll;
                    if(i==10)
                    {
                      Z_G_Y=G_Y/400;
                      Z_G_P=G_P/400;
                      Z_G_R=G_R/400;
                      i=0;j=1;
                    }
                  }
                }
        if(j==1&&gyro_Yaw<+3000&&gyro_Yaw>-3000)
                {
                  if(gyro_Yaw>-0.01&&gyro_Yaw<+0.01)
                    gyro_Yaw=0;
                  Yaw +=gyro_Yaw*0.005*0.0615;
                }

                //角速度积分获取Yaw角(Yaw +=gyro_Yaw*时间*比例系数)，角速度积分的好处是不存在临界突变，缺点是时间长角度会漂移
    }
    return 0;
}

int dmp_read_fifo(short *gyro, short *accel, long *quat, short *sensors, unsigned char *more)
{
  unsigned char fifo_data[32];
  unsigned char ii = 0;
  unsigned short fifo_count;
  unsigned char tmp[2];
  long quat_q14[4], quat_mag_sq;
  sensors[0] = 0;
  
  /* Get a packet. */
  //	if (mpu_read_fifo_stream(32, fifo_data, more)) return -1;
  // addr = 0x68	fifi_count_h = 0x72
  if (LQ_I2C_Read(0x68, 0x72, 2, tmp)) return -1;
  fifo_count = (tmp[0] << 8) | tmp[1];
  // length = 32
  if (fifo_count < 32) 
  {
    more[0] = 0;
    return -2;
  }
  // max_fifo >> 1 = 0x200 = 512
  if (fifo_count > 512) 
  {
    /* FIFO is 50% full, better check overflow bit. */
    // int_status = 0x3A
    if (LQ_I2C_Read(0x68, 0x3A, 1, tmp)) return -1;
    // BIT_FIFO_OVERFLOW = 0x10
    if (tmp[0] & 0x10) 
    {
      mpu_reset_fifo_in_mpu_set_dmp_state();
      return -3;
    }
  }
  // fifo_r_w = 0x74	length = 32
  if (LQ_I2C_Read(0x68, 0x74, 32, fifo_data)) return -1;
  more[0] = fifo_count / 31;
  
  /* Parse DMP packet. */
  quat[0] = ((long)fifo_data[0] << 24) | ((long)fifo_data[1] << 16) | ((long)fifo_data[2] << 8) | fifo_data[3];
  quat[1] = ((long)fifo_data[4] << 24) | ((long)fifo_data[5] << 16) | ((long)fifo_data[6] << 8) | fifo_data[7];
  quat[2] = ((long)fifo_data[8] << 24) | ((long)fifo_data[9] << 16) | ((long)fifo_data[10] << 8) | fifo_data[11];
  quat[3] = ((long)fifo_data[12] << 24) | ((long)fifo_data[13] << 16) | ((long)fifo_data[14] << 8) | fifo_data[15];
  ii += 16;
  /* We can detect a corrupted FIFO by monitoring the quaternion lqda and
  * ensuring that the magnitude is always normalized to one. This
  * shouldn't happen in normal operation, but if an I2C error occurs,
  * the FIFO reads might become misaligned.
  *
  * Let's start by scaling down the quaternion lqda to avoid double
  * math.
  */
  quat_q14[0] = quat[0] >> 16;
  quat_q14[1] = quat[1] >> 16;
  quat_q14[2] = quat[2] >> 16;
  quat_q14[3] = quat[3] >> 16;
  quat_mag_sq = quat_q14[0] * quat_q14[0] + quat_q14[1] * quat_q14[1] + quat_q14[2] * quat_q14[2] + quat_q14[3] * quat_q14[3];
  if ((quat_mag_sq < 0xF000000L) || (quat_mag_sq > 0x11000000L)) 
  {
    /* Quaternion is outside of the acceptable threshold. */
    mpu_reset_fifo_in_mpu_set_dmp_state();
    sensors[0] = 0;
    return -4;
  }
  sensors[0] |= 0x100;
  
  accel[0] = ((short)fifo_data[ii+0] << 8) | fifo_data[ii+1];
  accel[1] = ((short)fifo_data[ii+2] << 8) | fifo_data[ii+3];
  accel[2] = ((short)fifo_data[ii+4] << 8) | fifo_data[ii+5];
  ii += 6;
  sensors[0] |= 0x08;
  
  gyro[0] = ((short)fifo_data[ii+0] << 8) | fifo_data[ii+1];
  gyro[1] = ((short)fifo_data[ii+2] << 8) | fifo_data[ii+3];
  gyro[2] = ((short)fifo_data[ii+4] << 8) | fifo_data[ii+5];
  ii += 6;
  sensors[0] |= 0x70;
  
  /* Gesture lqda is at the end of the DMP packet. Parse it and call
  * the gesture callbacks (if registered).
  */
  //	decode_gesture(fifo_data + ii);  
  return 0;
}

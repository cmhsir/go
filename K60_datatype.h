#ifndef __K60_DATATYPE_H__
#define __K60_DATATYPE_H__

//这个.h文件把所有的函数都包含在内


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>

#include "common\MK60N512VMD100.h"   

/*

  printf.h
  printf.c

  crt0.s

  K60_datatype.h

  MK60N512VMD100.h

  vectors.c

  vectors.h

  都是包含在common文件夹之下的

*/


typedef void              VOID;
typedef unsigned long     DWORD, ULONG, U32,u32,uint32;
typedef long              LONG, S32;
typedef int               INT;
typedef unsigned short    WORD, U16, u16;
typedef short             S16, SHORT;
typedef unsigned char     BYTE, U8, UCHAR, BOOL,uchar,u8,uint8;
typedef char              S8, CHAR;
typedef float             FLOAT;
typedef unsigned short int	uint16; /* 16 bits */

#include "common\Vectors.h"
#include "common\_printf.h"
#include "GPIO.h"
#include "MCG.h"
#include "PIT0.h"
#include "OLED.h"
#include "flash.h"
#include "ADC.h"
#include "iic.h"
#include "PWM.h"
#include "bsp.h"
#include "exti.h"
#include "DMA.h"
#include "sccb.h"
#include "common.h"
#include "locatingEye.h"



#ifndef TRUE
#define TRUE         (1)
#endif

#ifndef FALSE
#define FALSE        (0)
#endif


#define  SYS_CLK                        (125000000L)     // 125MHz
#define  PERIPH_SYS_CLK                 (ULONG)(SYS_CLK/(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> 24)+ 1))

/***DEF+**********************************************************************/
/* Data value and direction of chip pins define.                             */
/***DEF-**********************************************************************/

#define LVL_H                (1)    /* High level of pin value. */
#define LVL_L                (0)    /* Low level of pin value. */
#define DIR_I                (0)    /* Input direction of pin. */
#define DIR_O                (1)    /* Output direction of pin. */

/***DEF+**********************************************************************/
/* Data value define.                                                        */
/***DEF-**********************************************************************/

#define NULL_BYTE            (0xFF)
#define NULL_WORD            (0xFFFF)
#define NULL_DWORD           (0xFFFFFFFF)
#define NULL_PTR             (0)
#define VAL_OK               (0)
#define VAL_ERR              (1)



//#define ROW   240
//#define COL   320
#define ROW   80
#define COL   100


extern char Pix_Data[ROW][COL];
extern char Is_SendPhoto;
extern int  V_Cnt,AD;



#endif   
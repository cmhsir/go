#ifndef __K60_OLED_H__
#define __K60_OLED_H__
#include "K60_datatype.h"

#define byte  char
#define uint unsigned int

#define SCL_PIN PORTC,5
#define SDA_PIN PORTC,7
#define RST_PIN PORTC,9
#define DC_PIN PORTC,11

#define INIT 0

#define LED_SCL_Init  Gpio_init(PORT_E,8,1,INIT) // ʱ�ӳ�ʼ������D0

#define LED_SDA_Init  Gpio_init(PORT_E,4,1,INIT)//���ݿ�D0      //D1

#define LED_RST_Init  Gpio_init(PORT_E,5,1,INIT)//��λ���ܵ�ƽ

#define LED_DC_Init   Gpio_init(PORT_E,7,1,INIT)//ƫ�ó���

#define LED_SCLH  Gpio_set(PORT_E,8,1)// ʱ�Ӷ��� 
#define LED_SCLL  Gpio_set(PORT_E,8,0)

#define LED_SDAH  Gpio_set(PORT_E,4,1)//���ݿ�D0
#define LED_SDAL  Gpio_set(PORT_E,4,0)

#define LED_RSTH  Gpio_set(PORT_E,5,1)//��λ���ܵ�ƽ
#define LED_RSTL  Gpio_set(PORT_E,5,0)

#define LED_DCH   Gpio_set(PORT_E,7,1)
#define LED_DCL   Gpio_set(PORT_E,7,0)//ƫ�ó���

/************************************************/

void  LEDPIN_Init(void);   //LED�������ų�ʼ��

void  OLED_Init(void);

 void LED_CLS(void);
 
 void LED_Set_Pos(byte x, byte y);//�������꺯��
 void LED_WrDat(U8 data);   //д���ݺ���
 
 void LED_P6x8Char(byte x,byte y,byte ch);
 void LED_P6x8Str(byte x,byte y,byte ch[]);
 void LED_P8x16Char(byte x,byte y,byte ch);
 void LED_P8x16Str(byte x,byte y,byte ch[]);
 
void  LED_P14x16Str(byte x,byte y,byte ch[]);
 
 void LED_PrintBMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]);
 
 void LED_Fill(byte dat);
 
 void LED_PrintValueC(U8 x, U8 y,char data);
 void LED_PrintValueI(U8 x, U8 y, int data);
 void LED_PrintValueF(U8 x, U8 y, float data, U8 num);

 void LED_Cursor(U8 cursor_column, U8 cursor_row);
 extern char logo[];
 

#endif

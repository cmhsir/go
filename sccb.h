<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
#ifndef __SCCB_H__
#define __SCCB_H__

//--- Ĭ��SCL��PE1   SDA��PE0------//
void sccb_init(void);                           //��ʼ��SCCB�˿�ΪGPIO
void sccb_wait(void);                           //SCCBʱ����ʱ
void sccb_start(void);                          //��ʼ��־
void sccb_stop(void);                           //ֹͣ��־
U8 sccb_sendByte(U8 data);
void sccb_regWrite(U8 device,U8 address,U8 data);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   Gpio_init(PORT_E,1,1,1)      //SCL-PE1����Ϊ����˿�
#define SDA_OUT   Gpio_init(PORT_E,0,1,0)      //SDA-PE0����Ϊ����˿�
#define SDA_IN    Gpio_init(PORT_E,0,0,0)      //SDA-PE0����Ϊ����˿�

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  Gpio_set(PORT_E,1,1)
#define SCL_LOW   Gpio_set(PORT_E,1,0)
#define SDA_HIGH  Gpio_set(PORT_E,0,1)
#define SDA_LOW   Gpio_set(PORT_E,0,0)
#define SDA_DATA  Gpio_get(PORT_E,0) 



=======
/******************** (C) COPYRIGHT 2012-2013 �Ĭ�Ƽ� DEMOK*********
 * �ļ���         �� sccb.h
 * ����           �� OV����ͷSCCB����ͷ�ļ�
 *
 * ʵ��ƽ̨       �� �Ĭ�Ƽ�DEMOK Kinetis������
 * ����           �� �Ĭ�Ƽ�DEMOK Kinetis����С��

 * �Ա�����       �� http://shop60443799.taobao.com/
 * ������������   �� 1030923155@qq.com 
 * ��������QQȺ   �� 103360642

 * ����޶�ʱ��    ��2012-11-12
 * �޶�����        ����
**********************************************************************************/
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
#ifndef __SCCB_H__
#define __SCCB_H__

//--- Ĭ��SCL��PE1   SDA��PE0------//
void sccb_init(void);                           //��ʼ��SCCB�˿�ΪGPIO
void sccb_wait(void);                           //SCCBʱ����ʱ
void sccb_start(void);                          //��ʼ��־
void sccb_stop(void);                           //ֹͣ��־
U8 sccb_sendByte(U8 data);
void sccb_regWrite(U8 device,U8 address,U8 data);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   Gpio_init(PORT_E,1,1,1)      //SCL-PE1����Ϊ����˿�
#define SDA_OUT   Gpio_init(PORT_E,0,1,0)      //SDA-PE0����Ϊ����˿�
#define SDA_IN    Gpio_init(PORT_E,0,0,0)      //SDA-PE0����Ϊ����˿�

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  Gpio_set(PORT_E,1,1)
#define SCL_LOW   Gpio_set(PORT_E,1,0)
#define SDA_HIGH  Gpio_set(PORT_E,0,1)
#define SDA_LOW   Gpio_set(PORT_E,0,0)
#define SDA_DATA  Gpio_get(PORT_E,0) 



>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
#endif
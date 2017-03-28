/******************** (C) COPYRIGHT 2012-2013 �Ĭ�Ƽ� DEMOK*********
 * �ļ���         �� sccb.c
 * ����           �� OV����ͷSCCB��������
 *
 * ʵ��ƽ̨       �� �Ĭ�Ƽ�DEMOK Kinetis������
 * ����           �� �Ĭ�Ƽ�DEMOK Kinetis����С��

 * �Ա�����       �� http://shop60443799.taobao.com/
 * ������������   �� 1030923155@qq.com 
 * ��������QQȺ   �� 103360642

 * ����޶�ʱ��    ��2012-11-12
 * �޶�����        ����
**********************************************************************************/

#include "K60_datatype.h"
#include "sccb.h"
#include "GPIO.h"



/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�sccb_init
*  ����˵������ʼ��SCCB  ����SCL��PTA10 SDA��PTA11
*  ����˵������
*  �������أ���
*
*************************************************************************/
//-------��ʼ��PA10  PA11ΪGPIO--------//
void sccb_init(void)
{
  PORT_PCR_REG(PORTC_BASE_PTR, 14) = (0 | PORT_PCR_MUX(1) );
  PORT_PCR_REG(PORTC_BASE_PTR, 17) = (0 | PORT_PCR_MUX(1) );
}

/************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�sccb_wait
*  ����˵����SCCB��ʱ����Ӧ̫С
*  ����˵������
*  �������أ���
*
*************************************************************************/
void sccb_wait(void)
{
  U8 i;
  
  for( i=0; i<100; i++)
  {
    asm ("nop");
  }
}
/************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�sccb_start
*  ����˵����SCCB����λ
*  ����˵������
*  �������أ���
*
*************************************************************************/
void sccb_start(void)
{
  SCL_OUT;
  SDA_OUT;
 
  SDA_HIGH;
  //sccb_wait();
  SCL_HIGH;
  sccb_wait();
  SDA_LOW;
  sccb_wait();
  SCL_LOW;
}

/************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�sccb_stop
*  ����˵����SCCBֹͣλ
*  ����˵������
*  �������أ���
*
*************************************************************************/
void sccb_stop(void)
{
  SCL_OUT;
  SDA_OUT;
  
  SDA_LOW;
  sccb_wait();
  SCL_HIGH;
  sccb_wait();
  SDA_HIGH;
  sccb_wait();
}

/************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�sccb_sendByte
*  ����˵������SCCB�����Ϸ���һ���ֽ�
*  ����˵����data Ҫ���͵��ֽ�����
*  �������أ���
*
*************************************************************************/
U8 sccb_sendByte(U8 data)
{
   U8 i;
   U8 ack;
  SDA_OUT;
  for( i=0; i<8; i++)
  {
    if(data & 0x80)
      SDA_HIGH;
    else 
      SDA_LOW;
    data <<= 1;
    sccb_wait();
    SCL_HIGH;
    sccb_wait();
    SCL_LOW;
    sccb_wait();
  }
  SDA_HIGH;
  SDA_IN;
  sccb_wait();
  SCL_HIGH;
  sccb_wait();
  ack = SDA_DATA;
  SCL_LOW;
  sccb_wait();
  return ack;
}


/************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�sccb_regWrite
*  ����˵����ͨ��SCCB������ָ���豸��ָ����ַ����ָ������
*  ����˵����device---�豸��  ��д������
*            address---д���ݵļĴ���
*            data---д������
*  �������أ�ack=1δ�յ�Ӧ��(ʧ��)    ack=0�յ�Ӧ��(�ɹ�)
*
*************************************************************************/
void sccb_regWrite(U8 device,U8 address,U8 data)
{
  U8 i;
  U8 ack;
  for( i=0; i<20; i++)
  {
    sccb_start();
    ack = sccb_sendByte(device);
    if( ack == 1 )
    {
     // sccb_stop();
      continue;
    }
    
    ack = sccb_sendByte(address);
    if( ack == 1 )
    {
     // sccb_stop();
      continue;
    }
    
    ack = sccb_sendByte(data);
    if( ack == 1 )
    {
     // sccb_stop();
      continue;
    }
    
    sccb_stop();
    if( ack == 0 ) break;
  }
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include "K60_datatype.h"
#include "sccb.h"
#include "GPIO.h"

/*************************************************************************
*                             极之队开发小组
*
*  函数名称：sccb_init
*  功能说明：初始化SCCB  其中SCL接PTE1 SDA接PTE0
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
//-------初始化PE1  PE0为GPIO--------//
void sccb_init(void)
{
  PORT_PCR_REG(PORTE_BASE_PTR, 1) = (0 | PORT_PCR_MUX(1) );
  PORT_PCR_REG(PORTE_BASE_PTR, 0) = (0 | PORT_PCR_MUX(1) );
}

/************************************************************************
*                             极之队开发小组
*
*  函数名称：sccb_wait
*  功能说明：SCCB延时，不应太小
*  参数说明：无
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_start
*  功能说明：SCCB启动位
*  参数说明：无
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_stop
*  功能说明：SCCB停止位
*  参数说明：无
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_sendByte
*  功能说明：在SCCB总线上发送一个字节
*  参数说明：data 要发送的字节内容
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_regWrite
*  功能说明：通过SCCB总线向指定设备的指定地址发送指定内容
*  参数说明：device---设备号  读写有区别
*            address---写数据的寄存器
*            data---写的内容
*  函数返回：ack=1未收到应答(失败)    ack=0收到应答(成功)
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
=======
/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK*********
 * 文件名         ： sccb.c
 * 描述           ： OV摄像头SCCB驱动函数
 *
 * 实验平台       ： 岱默科技DEMOK Kinetis开发板
 * 作者           ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺       ： http://shop60443799.taobao.com/
 * 技术交流邮箱   ： 1030923155@qq.com 
 * 技术交流QQ群   ： 103360642

 * 最后修订时间    ：2012-11-12
 * 修订内容        ：无
**********************************************************************************/

>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
#include "K60_datatype.h"
#include "sccb.h"
#include "GPIO.h"

/*************************************************************************
*                             极之队开发小组
*
*  函数名称：sccb_init
*  功能说明：初始化SCCB  其中SCL接PTE1 SDA接PTE0
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
//-------初始化PE1  PE0为GPIO--------//
void sccb_init(void)
{
  PORT_PCR_REG(PORTE_BASE_PTR, 1) = (0 | PORT_PCR_MUX(1) );
  PORT_PCR_REG(PORTE_BASE_PTR, 0) = (0 | PORT_PCR_MUX(1) );
}

/************************************************************************
*                             极之队开发小组
*
*  函数名称：sccb_wait
*  功能说明：SCCB延时，不应太小
*  参数说明：无
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_start
*  功能说明：SCCB启动位
*  参数说明：无
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_stop
*  功能说明：SCCB停止位
*  参数说明：无
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_sendByte
*  功能说明：在SCCB总线上发送一个字节
*  参数说明：data 要发送的字节内容
*  函数返回：无
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
*                             极之队开发小组
*
*  函数名称：sccb_regWrite
*  功能说明：通过SCCB总线向指定设备的指定地址发送指定内容
*  参数说明：device---设备号  读写有区别
*            address---写数据的寄存器
*            data---写的内容
*  函数返回：ack=1未收到应答(失败)    ack=0收到应答(成功)
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
>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
}
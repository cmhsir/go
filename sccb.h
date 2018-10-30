<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
#ifndef __SCCB_H__
#define __SCCB_H__

//--- 默认SCL接PE1   SDA接PE0------//
void sccb_init(void);                           //初始化SCCB端口为GPIO
void sccb_wait(void);                           //SCCB时序延时
void sccb_start(void);                          //起始标志
void sccb_stop(void);                           //停止标志
U8 sccb_sendByte(U8 data);
void sccb_regWrite(U8 device,U8 address,U8 data);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   Gpio_init(PORT_E,1,1,1)      //SCL-PE1设置为输出端口
#define SDA_OUT   Gpio_init(PORT_E,0,1,0)      //SDA-PE0设置为输出端口
#define SDA_IN    Gpio_init(PORT_E,0,0,0)      //SDA-PE0设置为输入端口

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  Gpio_set(PORT_E,1,1)
#define SCL_LOW   Gpio_set(PORT_E,1,0)
#define SDA_HIGH  Gpio_set(PORT_E,0,1)
#define SDA_LOW   Gpio_set(PORT_E,0,0)
#define SDA_DATA  Gpio_get(PORT_E,0) 



=======
/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK*********
 * 文件名         ： sccb.h
 * 描述           ： OV摄像头SCCB驱动头文件
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
#ifndef __SCCB_H__
#define __SCCB_H__

//--- 默认SCL接PE1   SDA接PE0------//
void sccb_init(void);                           //初始化SCCB端口为GPIO
void sccb_wait(void);                           //SCCB时序延时
void sccb_start(void);                          //起始标志
void sccb_stop(void);                           //停止标志
U8 sccb_sendByte(U8 data);
void sccb_regWrite(U8 device,U8 address,U8 data);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   Gpio_init(PORT_E,1,1,1)      //SCL-PE1设置为输出端口
#define SDA_OUT   Gpio_init(PORT_E,0,1,0)      //SDA-PE0设置为输出端口
#define SDA_IN    Gpio_init(PORT_E,0,0,0)      //SDA-PE0设置为输入端口

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  Gpio_set(PORT_E,1,1)
#define SCL_LOW   Gpio_set(PORT_E,1,0)
#define SDA_HIGH  Gpio_set(PORT_E,0,1)
#define SDA_LOW   Gpio_set(PORT_E,0,0)
#define SDA_DATA  Gpio_get(PORT_E,0) 



>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
#endif
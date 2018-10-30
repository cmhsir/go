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



#endif
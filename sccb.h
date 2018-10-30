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



#endif
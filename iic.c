#include "K60_datatype.h"

#define CTRL_REG1 0x20     
#define CTRL_REG2 0x21     
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

#define SlaveAddress   0xD2          
//定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改

#define somenop();   asm("nop"); asm("nop");asm("nop"); asm("nop");

//置0置1
#define SCL_set(x)  Gpio_set(PORT_B,2,x)
#define SDA_set(x)  Gpio_set(PORT_B,3,x) 

#define SCL_dir(x)  Gpio_init(PORT_B, 2, x, 0)
#define SDA_dir(x)  Gpio_init(PORT_B, 3, x, 0)

#define SCL_read    Gpio_get(PORT_B,2)
#define SDA_read    Gpio_get(PORT_B,3)


/*************************************************************/
/*                        初始化IIC                          */
/*************************************************************/
void INIT_IIC(void) 
{

  SCL_dir(1);
  SCL_dir(1);

  SCL_set(1);
  SDA_set(1);
 
}

/*************************************************************/
/*                         启动IIC                           */
/*************************************************************/
void I2Cstart(void) 
{
  SCL_dir(1);
  SDA_dir(1);
  
  SDA_set(1);
  somenop();
  SCL_set(1);
  somenop();
  somenop();
  SDA_set(0);
  somenop();
  somenop();
  SCL_set(0);
}

/*************************************************************/
/*                         停止IIC                           */
/*************************************************************/
void I2Cstop(void) 
{
  SCL_dir(1);
  SDA_dir(1);
  
  SCL_set(1);
  SDA_set(0);
  somenop();
  somenop();
  SDA_set(1); 
  somenop(); 
  somenop();
}

/**************************************
接收应答信号
**************************************/
void I2Crecack()
{
    SCL_dir(1);
    SDA_dir(0);
 
    SCL_set(1);                    //拉高时钟线
    somenop();
    somenop();                 //延时
    while(SDA_read==1);
    SCL_set(0);                    //拉低时钟线
    somenop();
    somenop();                 //延时

}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void I2Csendack(char ack)
{
    SCL_dir(1);
    SDA_dir(1);
    
    if(ack==1) 
    {     
       SDA_set(1);                  //写应答信号
       SCL_set(1);                    //拉高时钟线
       somenop();
       somenop();
       SCL_set(0);                    //拉低时钟线
       somenop();
       somenop();
    } 
    else
    {
       SDA_set(0);                  //写应答信号
       SCL_set(1);                    //拉高时钟线                    //拉高时钟线
       somenop();
       somenop();
       SCL_set(0);                    //拉低时钟线
       somenop();
       somenop();
    }
}

/*************************************************************/
/*                       IIC发送数据                         */
/*************************************************************/
void I2Csend(byte data) 
{
 unsigned char i=8;
 
 SCL_dir(1);
 SDA_dir(1);
 
 for (i=0; i<8; i++)         //8位计数器
 {
        SDA_set((data&0x80)>>7);               //送数据口
        data=data<<1;
        SCL_set(1);                //拉高时钟线
        somenop();
        somenop();             //延时
        SCL_set(0);                //拉低时钟线
        somenop();
        somenop();             //延时
 }
    
 I2Crecack();
}

/*************************************************************/
/*                       IIC接收数据                         */
/*************************************************************/
signed char I2Creceive(void) 
{ 
    byte i;
    byte dat = 0;
    
    SCL_dir(1);
    SDA_dir(0);

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;                              //这里的1是 00000001
        SCL_set(1);                //拉高时钟线
        somenop();
        somenop();             //延时
        dat |= SDA_read;             //读数据      SDA  00000000 or 00000001         
        SCL_set(0);                //拉低时钟线
        somenop();
        somenop();             //延时
    }
    return dat;
}




//单字节写入*******************************************
void Single_WriteL3G4200D(uchar REG_Address,uchar REG_data)
{
    I2Cstart();                  //起始信号
    I2Csend(SlaveAddress);   //发送设备地址+写信号
    I2Csend(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    I2Csend(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    I2Cstop();                   //发送停止信号
}

//单字节读取*****************************************
uchar Single_ReadL3G4200D(uchar REG_Address)
{ 
    uchar REG_data;
    I2Cstart();                          //起始信号
    I2Csend(SlaveAddress);           //发送设备地址+写信号
    I2Csend(REG_Address);            //发送存储单元地址，从0开始        
    I2Cstart();                          //起始信号
    I2Csend(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=I2Creceive();              //读出寄存器数据
    I2Csendack(1);  
    I2Cstop();                           //停止信号
    return REG_data; 
}

//初始化L3G4200D，根据需要请参考pdf，第27页，进行修改************************
void InitL3G4200D()
{
   Single_WriteL3G4200D(CTRL_REG1, 0x0f);   //  0x0f=00001111  普通模式   X Y Z 启用。
   Single_WriteL3G4200D(CTRL_REG2, 0x00);   //  选择高通滤波模式和高通截止频率  此为普通模式
   Single_WriteL3G4200D(CTRL_REG3, 0x08);   //  0x08=0000 1000    DRDY/INT2 数据准备(0: Disable; 1: Enable)默认0 
   Single_WriteL3G4200D(CTRL_REG4, 0x00 );  //  选择量程    满量程选择（默认 00）（00：250dps)
   Single_WriteL3G4200D(CTRL_REG5, 0x00);   //   篎FIFO使能，高通滤波使
}

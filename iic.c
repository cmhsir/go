#include "K60_datatype.h"

#define CTRL_REG1 0x20     
#define CTRL_REG2 0x21     
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

#define SlaveAddress   0xD2          
//����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�

#define somenop();   asm("nop"); asm("nop");asm("nop"); asm("nop");

//��0��1
#define SCL_set(x)  Gpio_set(PORT_B,2,x)
#define SDA_set(x)  Gpio_set(PORT_B,3,x) 

#define SCL_dir(x)  Gpio_init(PORT_B, 2, x, 0)
#define SDA_dir(x)  Gpio_init(PORT_B, 3, x, 0)

#define SCL_read    Gpio_get(PORT_B,2)
#define SDA_read    Gpio_get(PORT_B,3)


/*************************************************************/
/*                        ��ʼ��IIC                          */
/*************************************************************/
void INIT_IIC(void) 
{

  SCL_dir(1);
  SCL_dir(1);

  SCL_set(1);
  SDA_set(1);
 
}

/*************************************************************/
/*                         ����IIC                           */
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
/*                         ֹͣIIC                           */
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
����Ӧ���ź�
**************************************/
void I2Crecack()
{
    SCL_dir(1);
    SDA_dir(0);
 
    SCL_set(1);                    //����ʱ����
    somenop();
    somenop();                 //��ʱ
    while(SDA_read==1);
    SCL_set(0);                    //����ʱ����
    somenop();
    somenop();                 //��ʱ

}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void I2Csendack(char ack)
{
    SCL_dir(1);
    SDA_dir(1);
    
    if(ack==1) 
    {     
       SDA_set(1);                  //дӦ���ź�
       SCL_set(1);                    //����ʱ����
       somenop();
       somenop();
       SCL_set(0);                    //����ʱ����
       somenop();
       somenop();
    } 
    else
    {
       SDA_set(0);                  //дӦ���ź�
       SCL_set(1);                    //����ʱ����                    //����ʱ����
       somenop();
       somenop();
       SCL_set(0);                    //����ʱ����
       somenop();
       somenop();
    }
}

/*************************************************************/
/*                       IIC��������                         */
/*************************************************************/
void I2Csend(byte data) 
{
 unsigned char i=8;
 
 SCL_dir(1);
 SDA_dir(1);
 
 for (i=0; i<8; i++)         //8λ������
 {
        SDA_set((data&0x80)>>7);               //�����ݿ�
        data=data<<1;
        SCL_set(1);                //����ʱ����
        somenop();
        somenop();             //��ʱ
        SCL_set(0);                //����ʱ����
        somenop();
        somenop();             //��ʱ
 }
    
 I2Crecack();
}

/*************************************************************/
/*                       IIC��������                         */
/*************************************************************/
signed char I2Creceive(void) 
{ 
    byte i;
    byte dat = 0;
    
    SCL_dir(1);
    SDA_dir(0);

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;                              //�����1�� 00000001
        SCL_set(1);                //����ʱ����
        somenop();
        somenop();             //��ʱ
        dat |= SDA_read;             //������      SDA  00000000 or 00000001         
        SCL_set(0);                //����ʱ����
        somenop();
        somenop();             //��ʱ
    }
    return dat;
}




//���ֽ�д��*******************************************
void Single_WriteL3G4200D(uchar REG_Address,uchar REG_data)
{
    I2Cstart();                  //��ʼ�ź�
    I2Csend(SlaveAddress);   //�����豸��ַ+д�ź�
    I2Csend(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
    I2Csend(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
    I2Cstop();                   //����ֹͣ�ź�
}

//���ֽڶ�ȡ*****************************************
uchar Single_ReadL3G4200D(uchar REG_Address)
{ 
    uchar REG_data;
    I2Cstart();                          //��ʼ�ź�
    I2Csend(SlaveAddress);           //�����豸��ַ+д�ź�
    I2Csend(REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ        
    I2Cstart();                          //��ʼ�ź�
    I2Csend(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=I2Creceive();              //�����Ĵ�������
    I2Csendack(1);  
    I2Cstop();                           //ֹͣ�ź�
    return REG_data; 
}

//��ʼ��L3G4200D��������Ҫ��ο�pdf����27ҳ�������޸�************************
void InitL3G4200D()
{
   Single_WriteL3G4200D(CTRL_REG1, 0x0f);   //  0x0f=00001111  ��ͨģʽ   X Y Z ���á�
   Single_WriteL3G4200D(CTRL_REG2, 0x00);   //  ѡ���ͨ�˲�ģʽ�͸�ͨ��ֹƵ��  ��Ϊ��ͨģʽ
   Single_WriteL3G4200D(CTRL_REG3, 0x08);   //  0x08=0000 1000    DRDY/INT2 ����׼��(0: Disable; 1: Enable)Ĭ��0 
   Single_WriteL3G4200D(CTRL_REG4, 0x00 );  //  ѡ������    ������ѡ��Ĭ�� 00����00��250dps)
   Single_WriteL3G4200D(CTRL_REG5, 0x00);   //   �FFIFOʹ�ܣ���ͨ�˲�ʹ
}

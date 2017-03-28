#include "K60_datatype.h"
extern  u8  Image_Sort_History[3][ROW][COL];
void BSP_init()
{
    WatchdogDisable();  //���Ź�

   
    VECTableInit();

 
    SIM_SCGC5 |= (    SIM_SCGC5_PORTA_MASK     //PORTA��B��C��D��E��ʱ�ӿ���
                      | SIM_SCGC5_PORTB_MASK
                      | SIM_SCGC5_PORTC_MASK
                      | SIM_SCGC5_PORTD_MASK
                      | SIM_SCGC5_PORTE_MASK 
                  );
    
    PLL_Init();
    
    //OLED��ʼ��
    OLED_Init();
    
    //OLED����
    LED_Fill(0xFF);
    LED_Fill(0x00);
    
    //OLED��ʾͼƬ
    //LED_PrintBMP(0,0,127,7,logo);
  
    //----------SCCB�Ĵ�������---------------//
    //sccb_regWrite(0x42,0x11,0x03);      //��ַ0X11-�ж��ķ�Ƶ(640*240)           PCLK:166ns   HREF:254.6us   VSYN:133.6ms
    //sccb_regWrite(0x42,0x14,0x24);      //��ַ0X14-QVGA(320*120)                  PCLK:332ns   HREF:509.6us   VSYN:133.6ms
    //sccb_regWrite(0x42,0x28,0x20);      //��ַ0X28-�����ɼ�ģʽ(320*240)              PCLK:666ns   HREF:509.6us   VSYN:133.6ms
    //sccb_wait();

    //����ͷ���ݴ��������
    Gpio_init(PORT_D, 0, 0, 0);
    Gpio_init(PORT_D, 1, 0, 0);
    Gpio_init(PORT_D, 2, 0, 0);
    Gpio_init(PORT_D, 3, 0, 0);
    Gpio_init(PORT_D, 4, 0, 0);
    Gpio_init(PORT_D, 5, 0, 0);
    Gpio_init(PORT_D, 6, 0, 0);
    Gpio_init(PORT_D, 7, 0, 0);
          //PTE[0:7]  Y[0:7]
    
    //PTC8�����ж�,���жϣ����ж�����Ϊ����״̬
    Gpio_init(PORT_C,18,0,0);  // PCLK
    Gpio_init(PORT_C,17,0,0);  // VSYN
    Gpio_init(PORT_C,16,0,0);  // HREF
    PORTC_PCR18|=PORT_PCR_IRQC(1);   
    //DMA_transmit_init((void *)&GPIOD_PDIR, Pix_Data,COL,51);
    DMA_transmit_init((void *)&GPIOD_PDIR, Image_Sort_History[0],COL,51);
    
    //����ͷ�ⲿ�ж�ʹ��
    exti_init();
    
    //����ʹ�ܣ����ڷ�������ͷ����
    UART_Init(PERIPH_SYS_CLK,9600,UART4);
    
    EnableInterrupts;
  
}
<<<<<<< HEAD
#include "K60_datatype.h"
extern  u8  Image_Sort_History[3][ROW][COL];
u32 time = 9000000;//��ʱ����
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

    //��ʼ��PWM���ţ��Լ�ռ�ձ�
    PWM_Init(PWM_PIN_PTA10,PWM_FRE_DIV_FACTOR_128,0);//��������ΪA10��5.12ms,�����أ�ת����
    PWM_Init(PWM_PIN_PTA6,PWM_FRE_DIV_FACTOR_64,0);//�����1
    PWM_Init(PWM_PIN_PTA7,PWM_FRE_DIV_FACTOR_64,0);//�����1
    PWM_Init(PWM_PIN_PTA8,PWM_FRE_DIV_FACTOR_64,0);//�����2
    PWM_Init(PWM_PIN_PTA9,PWM_FRE_DIV_FACTOR_64,0);//�����2
    PWM_Output(PWM_PIN_PTA10,692);//����692��С�ң���������750������630�����Ҹ���55
    
    //��ʼ�������������Լ�DMA��ע��ÿһ������ͨ��ֻ��ʹ��һ�Σ�����ʹ�õ����ĸ���ͬ��GPIOͨ������·�������
    Gpio_init(PORT_A, 5, 0, 0);//��ʼ������
    Gpio_init(PORT_B, 9, 0, 0);
//    Gpio_init(PORT_D, 9, 0, 0);
//    Gpio_init(PORT_E, 9, 0, 0);
    DMA_count_Init(DMA_CH2, PTA5, 0x7FFF, DMA_rising_up);//ͨ��DMA2������A5���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
    DMA_count_Init(DMA_CH3, PTB9, 0x7FFF, DMA_rising_up);//ͨ��DMA3������B9���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
//    DMA_count_Init(DMA_CH4, PTD9, 0x7FFF, DMA_rising_up);//ͨ��DMA4������D9���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
//    DMA_count_Init(DMA_CH5, PTE9, 0x7FFF, DMA_rising_up);//ͨ��DMA5������E9���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
    //count = DMA_count_get(DMA_CHn)��ȡͨ��n���������
    
    //��ʼ�����뿪��
    Gpio_init(PORT_A, 11, 0, 0);
    Gpio_init(PORT_A, 12, 0, 0);
    Gpio_init(PORT_A, 13, 0, 0);
    Gpio_init(PORT_A, 14, 0, 0);
    Gpio_init(PORT_A, 15, 0, 0);
    Gpio_init(PORT_A, 16, 0, 0);
    Gpio_init(PORT_A, 17, 0, 0);
    Gpio_init(PORT_A, 19, 0, 0);
    
    //OLED��ʼ��
    OLED_Init();
    
    //OLED����
    LED_Fill(0xFF);
    LED_Fill(0x00);
    
    //OLED��ʾͼƬ
    LED_PrintBMP(0,0,127,7,logo);
    LED_P14x16Str(18,0,"�ɿƴ�֮��");
    while(time--);
  
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
    //DMA_transmit_init((void *)&GPIOD_PDIR, Pix_Data,COL,51);//ʹ����λ����ʾʱ���������
    DMA_transmit_init((void *)&GPIOD_PDIR, Image_Sort_History[0],COL,51);
    
    //����ͷ�ⲿ�ж�ʹ��
    exti_init();
    
    //����ʹ�ܣ����ڷ�������ͷ����
    UART_Init(PERIPH_SYS_CLK,9600,UART4);
    
    EnableInterrupts;
  
=======
#include "K60_datatype.h"
extern  u8  Image_Sort_History[3][ROW][COL];
u32 time = 9000000;//��ʱ����
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

    //��ʼ��PWM���ţ��Լ�ռ�ձ�
    PWM_Init(PWM_PIN_PTA10,PWM_FRE_DIV_FACTOR_128,0);//��������ΪA10��5.12ms,�����أ�ת����
    PWM_Init(PWM_PIN_PTA6,PWM_FRE_DIV_FACTOR_64,0);//�����1
    PWM_Init(PWM_PIN_PTA7,PWM_FRE_DIV_FACTOR_64,0);//�����1
    PWM_Init(PWM_PIN_PTA8,PWM_FRE_DIV_FACTOR_64,0);//�����2
    PWM_Init(PWM_PIN_PTA9,PWM_FRE_DIV_FACTOR_64,0);//�����2
    PWM_Output(PWM_PIN_PTA10,692);//����692��С�ң���������750������630�����Ҹ���55
    
    //��ʼ�������������Լ�DMA��ע��ÿһ������ͨ��ֻ��ʹ��һ�Σ�����ʹ�õ����ĸ���ͬ��GPIOͨ������·�������
    Gpio_init(PORT_A, 5, 0, 0);//��ʼ������
    Gpio_init(PORT_B, 9, 0, 0);
//    Gpio_init(PORT_D, 9, 0, 0);
//    Gpio_init(PORT_E, 9, 0, 0);
    DMA_count_Init(DMA_CH2, PTA5, 0x7FFF, DMA_rising_up);//ͨ��DMA2������A5���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
    DMA_count_Init(DMA_CH3, PTB9, 0x7FFF, DMA_rising_up);//ͨ��DMA3������B9���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
//    DMA_count_Init(DMA_CH4, PTD9, 0x7FFF, DMA_rising_up);//ͨ��DMA4������D9���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
//    DMA_count_Init(DMA_CH5, PTE9, 0x7FFF, DMA_rising_up);//ͨ��DMA5������E9���������ֵΪ0x7FFF�������ش�����Դ��ַIO�˿��ڲ�����
    //count = DMA_count_get(DMA_CHn)��ȡͨ��n���������
    
    
    //OLED��ʼ��
    OLED_Init();
    
    //OLED����
    LED_Fill(0xFF);
    LED_Fill(0x00);
    
    //OLED��ʾͼƬ
    LED_PrintBMP(0,0,127,7,logo);
    LED_P14x16Str(18,0,"�ɿƴ�֮��");
    while(time--);
  
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
    //DMA_transmit_init((void *)&GPIOD_PDIR, Pix_Data,COL,51);//ʹ����λ����ʾʱ���������
    DMA_transmit_init((void *)&GPIOD_PDIR, Image_Sort_History[0],COL,51);
    
    //����ͷ�ⲿ�ж�ʹ��
    exti_init();
    
    //����ʹ�ܣ����ڷ�������ͷ����
    UART_Init(PERIPH_SYS_CLK,9600,UART4);
    
    EnableInterrupts;
  
>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
}
<<<<<<< HEAD
#include "K60_datatype.h"
extern  u8  Image_Sort_History[3][ROW][COL];
u32 time = 9000000;//延时启动
void BSP_init()
{
    WatchdogDisable();  //看门狗

   
    VECTableInit();

 
    SIM_SCGC5 |= (    SIM_SCGC5_PORTA_MASK     //PORTA，B，C，D，E口时钟开启
                      | SIM_SCGC5_PORTB_MASK
                      | SIM_SCGC5_PORTC_MASK
                      | SIM_SCGC5_PORTD_MASK
                      | SIM_SCGC5_PORTE_MASK 
                  );
    
    PLL_Init();

    //初始化PWM引脚，以及占空比
    PWM_Init(PWM_PIN_PTA10,PWM_FRE_DIV_FACTOR_128,0);//设置引脚为A10，5.12ms,上升沿，转向舵机
    PWM_Init(PWM_PIN_PTA6,PWM_FRE_DIV_FACTOR_64,0);//电机正1
    PWM_Init(PWM_PIN_PTA7,PWM_FRE_DIV_FACTOR_64,0);//电机反1
    PWM_Init(PWM_PIN_PTA8,PWM_FRE_DIV_FACTOR_64,0);//电机正2
    PWM_Init(PWM_PIN_PTA9,PWM_FRE_DIV_FACTOR_64,0);//电机反2
    PWM_Output(PWM_PIN_PTA10,692);//对中692，小右，大左，左满750，右满630，左右各差55
    
    //初始化编码器引脚以及DMA，注意每一个引脚通道只能使用一次，这里使用的是四个不同的GPIO通道，四路检测和输出
    Gpio_init(PORT_A, 5, 0, 0);//初始化引脚
    Gpio_init(PORT_B, 9, 0, 0);
//    Gpio_init(PORT_D, 9, 0, 0);
//    Gpio_init(PORT_E, 9, 0, 0);
    DMA_count_Init(DMA_CH2, PTA5, 0x7FFF, DMA_rising_up);//通道DMA2，引脚A5，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
    DMA_count_Init(DMA_CH3, PTB9, 0x7FFF, DMA_rising_up);//通道DMA3，引脚B9，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
//    DMA_count_Init(DMA_CH4, PTD9, 0x7FFF, DMA_rising_up);//通道DMA4，引脚D9，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
//    DMA_count_Init(DMA_CH5, PTE9, 0x7FFF, DMA_rising_up);//通道DMA5，引脚E9，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
    //count = DMA_count_get(DMA_CHn)获取通道n的脉冲次数
    
    //初始化拨码开关
    Gpio_init(PORT_A, 11, 0, 0);
    Gpio_init(PORT_A, 12, 0, 0);
    Gpio_init(PORT_A, 13, 0, 0);
    Gpio_init(PORT_A, 14, 0, 0);
    Gpio_init(PORT_A, 15, 0, 0);
    Gpio_init(PORT_A, 16, 0, 0);
    Gpio_init(PORT_A, 17, 0, 0);
    Gpio_init(PORT_A, 19, 0, 0);
    
    //OLED初始化
    OLED_Init();
    
    //OLED清屏
    LED_Fill(0xFF);
    LED_Fill(0x00);
    
    //OLED显示图片
    LED_PrintBMP(0,0,127,7,logo);
    LED_P14x16Str(18,0,"辽科大极之队");
    while(time--);
  
    //----------SCCB寄存器配置---------------//
    //sccb_regWrite(0x42,0x11,0x03);      //地址0X11-中断四分频(640*240)           PCLK:166ns   HREF:254.6us   VSYN:133.6ms
    //sccb_regWrite(0x42,0x14,0x24);      //地址0X14-QVGA(320*120)                  PCLK:332ns   HREF:509.6us   VSYN:133.6ms
    //sccb_regWrite(0x42,0x28,0x20);      //地址0X28-连续采集模式(320*240)              PCLK:666ns   HREF:509.6us   VSYN:133.6ms
    //sccb_wait();

    //摄像头数据传输的引脚
    Gpio_init(PORT_D, 0, 0, 0);
    Gpio_init(PORT_D, 1, 0, 0);
    Gpio_init(PORT_D, 2, 0, 0);
    Gpio_init(PORT_D, 3, 0, 0);
    Gpio_init(PORT_D, 4, 0, 0);
    Gpio_init(PORT_D, 5, 0, 0);
    Gpio_init(PORT_D, 6, 0, 0);
    Gpio_init(PORT_D, 7, 0, 0);
          //PTE[0:7]  Y[0:7]
    
    //PTC8像素中断,行中断，场中断设置为输入状态
    Gpio_init(PORT_C,18,0,0);  // PCLK
    Gpio_init(PORT_C,17,0,0);  // VSYN
    Gpio_init(PORT_C,16,0,0);  // HREF
    PORTC_PCR18|=PORT_PCR_IRQC(1);   
    //DMA_transmit_init((void *)&GPIOD_PDIR, Pix_Data,COL,51);//使用上位机显示时解除此屏蔽
    DMA_transmit_init((void *)&GPIOD_PDIR, Image_Sort_History[0],COL,51);
    
    //摄像头外部中断使能
    exti_init();
    
    //串口使能，用于发送摄像头数据
    UART_Init(PERIPH_SYS_CLK,9600,UART4);
    
    EnableInterrupts;
  
=======
#include "K60_datatype.h"
extern  u8  Image_Sort_History[3][ROW][COL];
u32 time = 9000000;//延时启动
void BSP_init()
{
    WatchdogDisable();  //看门狗

   
    VECTableInit();

 
    SIM_SCGC5 |= (    SIM_SCGC5_PORTA_MASK     //PORTA，B，C，D，E口时钟开启
                      | SIM_SCGC5_PORTB_MASK
                      | SIM_SCGC5_PORTC_MASK
                      | SIM_SCGC5_PORTD_MASK
                      | SIM_SCGC5_PORTE_MASK 
                  );
    
    PLL_Init();

    //初始化PWM引脚，以及占空比
    PWM_Init(PWM_PIN_PTA10,PWM_FRE_DIV_FACTOR_128,0);//设置引脚为A10，5.12ms,上升沿，转向舵机
    PWM_Init(PWM_PIN_PTA6,PWM_FRE_DIV_FACTOR_64,0);//电机正1
    PWM_Init(PWM_PIN_PTA7,PWM_FRE_DIV_FACTOR_64,0);//电机反1
    PWM_Init(PWM_PIN_PTA8,PWM_FRE_DIV_FACTOR_64,0);//电机正2
    PWM_Init(PWM_PIN_PTA9,PWM_FRE_DIV_FACTOR_64,0);//电机反2
    PWM_Output(PWM_PIN_PTA10,692);//对中692，小右，大左，左满750，右满630，左右各差55
    
    //初始化编码器引脚以及DMA，注意每一个引脚通道只能使用一次，这里使用的是四个不同的GPIO通道，四路检测和输出
    Gpio_init(PORT_A, 5, 0, 0);//初始化引脚
    Gpio_init(PORT_B, 9, 0, 0);
//    Gpio_init(PORT_D, 9, 0, 0);
//    Gpio_init(PORT_E, 9, 0, 0);
    DMA_count_Init(DMA_CH2, PTA5, 0x7FFF, DMA_rising_up);//通道DMA2，引脚A5，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
    DMA_count_Init(DMA_CH3, PTB9, 0x7FFF, DMA_rising_up);//通道DMA3，引脚B9，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
//    DMA_count_Init(DMA_CH4, PTD9, 0x7FFF, DMA_rising_up);//通道DMA4，引脚D9，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
//    DMA_count_Init(DMA_CH5, PTE9, 0x7FFF, DMA_rising_up);//通道DMA5，引脚E9，计数最大值为0x7FFF，上升沿触发且源地址IO端口内部上拉
    //count = DMA_count_get(DMA_CHn)获取通道n的脉冲次数
    
    
    //OLED初始化
    OLED_Init();
    
    //OLED清屏
    LED_Fill(0xFF);
    LED_Fill(0x00);
    
    //OLED显示图片
    LED_PrintBMP(0,0,127,7,logo);
    LED_P14x16Str(18,0,"辽科大极之队");
    while(time--);
  
    //----------SCCB寄存器配置---------------//
    //sccb_regWrite(0x42,0x11,0x03);      //地址0X11-中断四分频(640*240)           PCLK:166ns   HREF:254.6us   VSYN:133.6ms
    //sccb_regWrite(0x42,0x14,0x24);      //地址0X14-QVGA(320*120)                  PCLK:332ns   HREF:509.6us   VSYN:133.6ms
    //sccb_regWrite(0x42,0x28,0x20);      //地址0X28-连续采集模式(320*240)              PCLK:666ns   HREF:509.6us   VSYN:133.6ms
    //sccb_wait();

    //摄像头数据传输的引脚
    Gpio_init(PORT_D, 0, 0, 0);
    Gpio_init(PORT_D, 1, 0, 0);
    Gpio_init(PORT_D, 2, 0, 0);
    Gpio_init(PORT_D, 3, 0, 0);
    Gpio_init(PORT_D, 4, 0, 0);
    Gpio_init(PORT_D, 5, 0, 0);
    Gpio_init(PORT_D, 6, 0, 0);
    Gpio_init(PORT_D, 7, 0, 0);
          //PTE[0:7]  Y[0:7]
    
    //PTC8像素中断,行中断，场中断设置为输入状态
    Gpio_init(PORT_C,18,0,0);  // PCLK
    Gpio_init(PORT_C,17,0,0);  // VSYN
    Gpio_init(PORT_C,16,0,0);  // HREF
    PORTC_PCR18|=PORT_PCR_IRQC(1);   
    //DMA_transmit_init((void *)&GPIOD_PDIR, Pix_Data,COL,51);//使用上位机显示时解除此屏蔽
    DMA_transmit_init((void *)&GPIOD_PDIR, Image_Sort_History[0],COL,51);
    
    //摄像头外部中断使能
    exti_init();
    
    //串口使能，用于发送摄像头数据
    UART_Init(PERIPH_SYS_CLK,9600,UART4);
    
    EnableInterrupts;
  
>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
}
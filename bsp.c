#include "K60_datatype.h"
extern  u8  Image_Sort_History[3][ROW][COL];
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
    
    //OLED初始化
    OLED_Init();
    
    //OLED清屏
    LED_Fill(0xFF);
    LED_Fill(0x00);
    
    //OLED显示图片
    //LED_PrintBMP(0,0,127,7,logo);
  
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
    //DMA_transmit_init((void *)&GPIOD_PDIR, Pix_Data,COL,51);
    DMA_transmit_init((void *)&GPIOD_PDIR, Image_Sort_History[0],COL,51);
    
    //摄像头外部中断使能
    exti_init();
    
    //串口使能，用于发送摄像头数据
    UART_Init(PERIPH_SYS_CLK,9600,UART4);
    
    EnableInterrupts;
  
}
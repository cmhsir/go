#include "K60_datatype.h"
/**************************************************************************************************
*                        K60              定位眼
*                      VCC(5V/3V3)        VCC(5V)
*                      PTD[0:7]           Y[0:7]
*                      PTC18              PCLK
*                      PTC17              HREF
*                      PTC16              VSYN
*                      GND                GND
*              K60与串口模块接线方式：
*                      PTE24接RX    PTE25接TX   默认使用K60的串口4 
*             上位机设置：波特率115200   
*                         行数列数根据拨码开关的状态对照以下真值表在K60_datatype.h中修改ROW和COL
*                                        拨码开关真值表
*                             拨码开关状态        分辨率（列数*行数）
*                                  11                320*240
*                                  10                160*120
*                                  01                100*80
*                                  10                80*60
*  实验操作：打开摄像头上位机，设定行数和列数的值和K60_datatype.h文件中的宏定义一致
*            波特率为115200，开始接收图像
****************************************************************************************************/
//char Pix_Data[ROW][COL]={0};
char Is_SendPhoto=0;
int  V_Cnt=0;
//void zhong(void);
//{
//  int temp；
//    if(Uart_Getch(UART4))
//      temp=Uart_Getch(UART4);
//
//}

void main()
{ 
//    int  m=0,n=0;
    int i = 50;
    u8 temp;
    BSP_init();
    PWM_Init(PWM_PIN_PTA10,PWM_FRE_DIV_FACTOR_128,0);//设置引脚为A10，5.12ms,上升沿
    PWM_Init(PWM_PIN_PTA6,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Init(PWM_PIN_PTA7,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Init(PWM_PIN_PTA8,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Init(PWM_PIN_PTA9,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Output(PWM_PIN_PTA10,695);//对中702，小右，大左，左满774，右满630，左右各差72
    while(1)
    {
//      PWM_Output(PWM_PIN_PTA10,702);//对中702，小右，大左，左满774，右满630，左右各差72
//      PWM_Output(PWM_PIN_PTA6,250);PWM_Output(PWM_PIN_PTA7,0);//左轮 最大250 A6 正转
//      PWM_Output(PWM_PIN_PTA9,250);PWM_Output(PWM_PIN_PTA8,0);//右轮 最大250 A9 正转
        if(Is_SendPhoto)
        { 
            DisableInterrupts;
  //          //发送一帧数据
  //          Uart_SendByte(UART4,0xFF);//图像头   
  //          for(m=0; m<ROW; m++)
  //          {
  //            for(n=0;n<COL ;n++)
  //            {
  //               if(Pix_Data[m][n] == 0xFF) 
  //                 Pix_Data[m][n]--;
  //               Uart_SendByte(UART4,Pix_Data[m][n]);
  //            }
  //          }
            LocatingEye_OriginalImage_FixedThreshold_OledPrint();//信标检测方式
            EnableInterrupts;   
        } 
        //Uart_SendByte(UART4,Uart_Getch(UART4));  //测试串口
        temp = Uart_Getch(UART4);
        Uart_SendByte(UART4,temp);
        temp -= 48;
        switch(temp)
        {
            case 0: PWM_Output(PWM_PIN_PTA10,695);//中
                break;
            case 1: PWM_Output(PWM_PIN_PTA10,760);//左
                break;
            case 2: PWM_Output(PWM_PIN_PTA10,630);//右
                break;
            case 3: 
                if(i <= 240)//加速
                {
                    i += 10;
                    PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                    PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
                }
                break;
            case 4: 
                if(i >= 50)//减速
                {
                    i -= 10;
                    PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                    PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
                }
                break;
             case 5: //停止
                  PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
                  PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
        }
    }
}







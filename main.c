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
char Pix_Data[ROW][COL]={0};
char Is_SendPhoto=0;
int  V_Cnt=0;

void go(void);
void view(void);

void main()
{ 
    BSP_init();
    while(1)
    {
        if(Is_SendPhoto)
        { 
            DisableInterrupts;
            //view();//上位机显示摄像头图片
            LocatingEye_OriginalImage_FixedThreshold_OledPrint();//信标检测方式
            EnableInterrupts;   
        }
        //go();//蓝牙控制车跑
     }
}

void view(void)//上位机显示摄像头图片
{
    int  m=0,n=0;
    //发送一帧数据
    Uart_SendByte(UART4,0xFF);//图像头   
    for(m=0; m<ROW; m++)
    {
      for(n=0;n<COL ;n++)
      {
         if(Pix_Data[m][n] == 0xFF) 
           Pix_Data[m][n]--;
         Uart_SendByte(UART4,Pix_Data[m][n]);
      }
    }
}

void go(void)//蓝牙控制车跑
{
    int i = 0;
    u8 temp;
    //Uart_SendByte(UART4,Uart_Getch(UART4));  //测试串口
    temp = Uart_Getch(UART4);//蓝牙遥控，程序会死在这里，接收到数据才执行
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
            if(i <= 250)//加速
            {
                if(i < 250)
                    i += 10;
                else
                    i = 250;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
        case 4: 
            if(i >= 0)//减速
            {
                if(i >= 50)
                    i -= 10;
                else
                    i = 0;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
         case 5: //停止
              i = 0;
              PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
    }
}






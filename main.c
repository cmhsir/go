#include "K60_datatype.h"
/**************************************************************************************************
*                        K60              ��λ��
*                      VCC(5V/3V3)        VCC(5V)
*                      PTD[0:7]           Y[0:7]
*                      PTC18              PCLK
*                      PTC17              HREF
*                      PTC16              VSYN
*                      GND                GND
*              K60�봮��ģ����߷�ʽ��
*                      PTE24��RX    PTE25��TX   Ĭ��ʹ��K60�Ĵ���4 
*             ��λ�����ã�������115200   
*                         �����������ݲ��뿪�ص�״̬����������ֵ����K60_datatype.h���޸�ROW��COL
*                                        ���뿪����ֵ��
*                             ���뿪��״̬        �ֱ��ʣ�����*������
*                                  11                320*240
*                                  10                160*120
*                                  01                100*80
*                                  10                80*60
*  ʵ�������������ͷ��λ�����趨������������ֵ��K60_datatype.h�ļ��еĺ궨��һ��
*            ������Ϊ115200����ʼ����ͼ��
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
            //view();//��λ����ʾ����ͷͼƬ
            LocatingEye_OriginalImage_FixedThreshold_OledPrint();//�ű��ⷽʽ
            EnableInterrupts;   
        }
        //go();//�������Ƴ���
     }
}

void view(void)//��λ����ʾ����ͷͼƬ
{
    int  m=0,n=0;
    //����һ֡����
    Uart_SendByte(UART4,0xFF);//ͼ��ͷ   
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

void go(void)//�������Ƴ���
{
    int i = 0;
    u8 temp;
    //Uart_SendByte(UART4,Uart_Getch(UART4));  //���Դ���
    temp = Uart_Getch(UART4);//����ң�أ����������������յ����ݲ�ִ��
    Uart_SendByte(UART4,temp);
    temp -= 48;
    switch(temp)
    {
        case 0: PWM_Output(PWM_PIN_PTA10,695);//��
            break;
        case 1: PWM_Output(PWM_PIN_PTA10,760);//��
            break;
        case 2: PWM_Output(PWM_PIN_PTA10,630);//��
            break;
        case 3: 
            if(i <= 250)//����
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
            if(i >= 0)//����
            {
                if(i >= 50)
                    i -= 10;
                else
                    i = 0;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
         case 5: //ֹͣ
              i = 0;
              PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
    }
}






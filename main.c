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
//char Pix_Data[ROW][COL]={0};
char Is_SendPhoto=0;
int  V_Cnt=0;
//void zhong(void);
//{
//  int temp��
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
    PWM_Init(PWM_PIN_PTA10,PWM_FRE_DIV_FACTOR_128,0);//��������ΪA10��5.12ms,������
    PWM_Init(PWM_PIN_PTA6,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Init(PWM_PIN_PTA7,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Init(PWM_PIN_PTA8,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Init(PWM_PIN_PTA9,PWM_FRE_DIV_FACTOR_64,0);
    PWM_Output(PWM_PIN_PTA10,695);//����702��С�ң���������774������630�����Ҹ���72
    while(1)
    {
//      PWM_Output(PWM_PIN_PTA10,702);//����702��С�ң���������774������630�����Ҹ���72
//      PWM_Output(PWM_PIN_PTA6,250);PWM_Output(PWM_PIN_PTA7,0);//���� ���250 A6 ��ת
//      PWM_Output(PWM_PIN_PTA9,250);PWM_Output(PWM_PIN_PTA8,0);//���� ���250 A9 ��ת
        if(Is_SendPhoto)
        { 
            DisableInterrupts;
  //          //����һ֡����
  //          Uart_SendByte(UART4,0xFF);//ͼ��ͷ   
  //          for(m=0; m<ROW; m++)
  //          {
  //            for(n=0;n<COL ;n++)
  //            {
  //               if(Pix_Data[m][n] == 0xFF) 
  //                 Pix_Data[m][n]--;
  //               Uart_SendByte(UART4,Pix_Data[m][n]);
  //            }
  //          }
            LocatingEye_OriginalImage_FixedThreshold_OledPrint();//�ű��ⷽʽ
            EnableInterrupts;   
        } 
        //Uart_SendByte(UART4,Uart_Getch(UART4));  //���Դ���
        temp = Uart_Getch(UART4);
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
                if(i <= 240)//����
                {
                    i += 10;
                    PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                    PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
                }
                break;
            case 4: 
                if(i >= 50)//����
                {
                    i -= 10;
                    PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                    PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
                }
                break;
             case 5: //ֹͣ
                  PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
                  PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
        }
    }
}







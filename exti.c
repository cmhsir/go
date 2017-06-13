
#include "K60_datatype.h"

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�exti_init
*  ����˵����EXTI�ⲿGPIO�жϳ�ʼ��
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*            exti_cfg    ����ѡ�����������ѡ��
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/

void exti_init()
{
   SIM_SCGC5 |= (   SIM_SCGC5_PORTC_MASK  //�������ж�PTC18��PTC19��
                 );
   
   PORTC_PCR17|=PORT_PCR_MUX(1)|PORT_PCR_IRQC(10)|PORT_PCR_PE_MASK;
   // ����GPIO , �½��ش��� ,�����������������裬���ж�
   
   PORTC_PCR16|=PORT_PCR_MUX(1)|PORT_PCR_IRQC(9)|PORT_PCR_PE_MASK;
   // ����GPIO , �����ش��� ,�����������������裬���ж�
   
   enable_irq(89);
   //��PORTC�ж�
}
   
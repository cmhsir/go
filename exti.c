
#include "K60_datatype.h"

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：exti_init
*  功能说明：EXTI外部GPIO中断初始化
*  参数说明：PORTx       端口号（PORTA,PORTB,PORTC,PORTD,PORTE）
*            n           端口引脚
*            exti_cfg    触发选项和上拉下拉选项
*  函数返回：无
*  修改时间：2012-1-20
*  备    注：
*************************************************************************/

void exti_init()
{
   SIM_SCGC5 |= (   SIM_SCGC5_PORTC_MASK  //场，行中断PTC18，PTC19口
                 );
   
   PORTC_PCR17|=PORT_PCR_MUX(1)|PORT_PCR_IRQC(10)|PORT_PCR_PE_MASK;
   // 复用GPIO , 下降沿触发 ,开启上拉或下拉电阻，场中断
   
   PORTC_PCR16|=PORT_PCR_MUX(1)|PORT_PCR_IRQC(9)|PORT_PCR_PE_MASK;
   // 复用GPIO , 上升沿触发 ,开启上拉或下拉电阻，行中断
   
   enable_irq(89);
   //开PORTC中断
}
   
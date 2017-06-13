

#include "K60_datatype.h"

__ramfunc static void SetSysDividers(ULONG uiOutDiv1, ULONG uiOutDiv2, ULONG uiOutDiv3, ULONG uiOutDiv4);


void PLL_Init(void)
{

    MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK;
    //RANGE:Ϊ����ѡ������Ƶ��Χ8M~32M
    //HGO:���þ���Ϊ���������
    //EREFS:�ⲿ����
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(5); 
    //CLKS:ѡ���ⲿ�ο�ʱ��
    //FRDIV����Ƶ��FLL�ⲿ�ο���Ƶ��
    //��FLL������ο�ʱ�������ⲿ����ʱ��
    //��ͨ������FRDIV��������Ծ���Ĳο�ʱ�ӷ�Ƶ��
    //��Ƶ���ʱ�ӿ����ṩ��FLL�ٱ�Ƶ,ע�⣺��Ƶ���ṩ��FLL��Ƶ�Ĳο�ʱ�Ӳ��ó���32K��
    while (!(MCG_S & MCG_S_OSCINIT_MASK)){}
    ////�ȴ����໷��ʼ������  
    while (MCG_S & MCG_S_IREFST_MASK){}
    ////�ȴ�ʱ���л����ⲿ�ο�ʱ��  
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT)!= 0x2){}
    //�ȴ�MCGOUTCLK�л����ⲿʱ�����  
    
    MCG_C5 = MCG_C5_PRDIV(0x13);
    ////��Ƶ��2~4MHz֮�䣬��Ƶ��Ƶ��2.5MHz                 
    SetSysDividers(0, 1, 1, 3);        
    // MCG=PLL, core=MCG, bus=MCG/2  62.5MHZ, FlexBus=MCG/2, Flash clock=MCG/4
    MCG_C6 = MCG_C6_PLLS_MASK |MCG_C6_VDIV(26);//(24+x)
    ////ѡ��PLL����Ƶ50��=125MHZ  
    while (!(MCG_S & MCG_S_PLLST_MASK))// wait until source of PLLS clock is PLL clock
    {
        ;   
    }
    // �ȴ��л���PLL
    
    while (!(MCG_S & MCG_S_LOCK_MASK)) // wait until PLL is locked
    {
        ;
    }
    //�ȴ�PLL����Ƶ��  
    
    MCG_C1 &= ~MCG_C1_CLKS_MASK;       
    //CLKS=00��PLL���
    
    while (((MCG_S & MCG_S_CLKST_MASK) // wait until Output of the PLL is selected 
          >> MCG_S_CLKST_SHIFT) != 0x3)
    {
        ;
    }
    //CLKST=11��ѡ��PLL������
 
}

/***FUNC+*********************************************************************/
/* Name   : SetSysDividers                                                   */
/* Descrp : This routine must be placed in RAM.It is a                       */
/*          workaround for errata e2448.Flash prefetch must                  */
/*          be disabled when the flash clock divider is                      */
/*          changed.This cannot be performed while executing                 */
/*          out of flash.There must be a short delay after                   */
/*          the clock dividers are changed before prefetch                   */
/*          can be re-enabled.                                               */
/* Input  : None.                                                            */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
__ramfunc static void SetSysDividers(ULONG uiOutDiv1, ULONG uiOutDiv2, ULONG uiOutDiv3, ULONG uiOutDiv4)
{

    ULONG uiTemp;
  
    INT  i;
  
 
    // store present value of FMC_PFAPR
    uiTemp = FMC_PFAPR; 
  
    // set M0PFD through M7PFD to 1 to disable prefetch
    FMC_PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK
              | FMC_PFAPR_M4PFD_MASK | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK
              | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
  
    // set clock dividers to desired value  
    SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(uiOutDiv1) | SIM_CLKDIV1_OUTDIV2(uiOutDiv2) 
                | SIM_CLKDIV1_OUTDIV3(uiOutDiv3) | SIM_CLKDIV1_OUTDIV4(uiOutDiv4);

    // wait for dividers to change
    for (i = 0; i < uiOutDiv4; i++)
    {
        ;   
    }
 
    // re-store original value of FMC_PFAPR
    FMC_PFAPR = uiTemp; 
  
} 



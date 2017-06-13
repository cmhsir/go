

#include "K60_datatype.h"

__ramfunc static void SetSysDividers(ULONG uiOutDiv1, ULONG uiOutDiv2, ULONG uiOutDiv3, ULONG uiOutDiv4);


void PLL_Init(void)
{

    MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK;
    //RANGE:为晶振选择甚高频范围8M~32M
    //HGO:设置晶振为高增益操作
    //EREFS:外部振荡器
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(5); 
    //CLKS:选择外部参考时钟
    //FRDIV：锁频环FLL外部参考分频。
    //当FLL的输入参考时钟来自外部晶振时，
    //可通过设置FRDIV对这个来自晶振的参考时钟分频。
    //分频后的时钟可以提供给FLL再倍频,注意：分频后提供给FLL倍频的参考时钟不得超过32K。
    while (!(MCG_S & MCG_S_OSCINIT_MASK)){}
    ////等待锁相环初始化结束  
    while (MCG_S & MCG_S_IREFST_MASK){}
    ////等待时钟切换到外部参考时钟  
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT)!= 0x2){}
    //等待MCGOUTCLK切换到外部时钟输出  
    
    MCG_C5 = MCG_C5_PRDIV(0x13);
    ////分频在2~4MHz之间，分频后频率2.5MHz                 
    SetSysDividers(0, 1, 1, 3);        
    // MCG=PLL, core=MCG, bus=MCG/2  62.5MHZ, FlexBus=MCG/2, Flash clock=MCG/4
    MCG_C6 = MCG_C6_PLLS_MASK |MCG_C6_VDIV(26);//(24+x)
    ////选择PLL，倍频50倍=125MHZ  
    while (!(MCG_S & MCG_S_PLLST_MASK))// wait until source of PLLS clock is PLL clock
    {
        ;   
    }
    // 等待切换到PLL
    
    while (!(MCG_S & MCG_S_LOCK_MASK)) // wait until PLL is locked
    {
        ;
    }
    //等待PLL锁定频率  
    
    MCG_C1 &= ~MCG_C1_CLKS_MASK;       
    //CLKS=00，PLL输出
    
    while (((MCG_S & MCG_S_CLKST_MASK) // wait until Output of the PLL is selected 
          >> MCG_S_CLKST_SHIFT) != 0x3)
    {
        ;
    }
    //CLKST=11：选择PLL输出完成
 
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



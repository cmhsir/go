#include "K60_datatype.h"

void Timer0_Init(void)
{
 
    // PIT clock enable:
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
    
    // enable the clock for PIT Timers:
    PIT_MCR = 0;
     
    // config the period of PIT0:
    PIT_LDVAL0 = PIT0_INIT_VAL;
    
    // enable interrupt for PIT0:
    PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK;  
    // TIE=1:Interrupt will be requested whenever TIF is set
    
    enable_irq(IRQ_NUM_PIT0); //68
    
}

/******************************************************************
Function:           EnableTimer0
Description:        Initialize timer
Calls:
Called By:          NONE
Input:              NONE
Output:             NONE
Return:             NONE
******************************************************************/

void EnableTimer0(void) 
{
    ENABLE_PIT0;   
}

/******************************************************************
Function:           DisableTimer0
Description:        Initialize timer
Calls:
Called By:          NONE
Input:              NONE
Output:             NONE
Return:             NONE
******************************************************************/

void DisableTimer0(void) 
{  
    DISABLE_PIT0;  
}






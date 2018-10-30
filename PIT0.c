<<<<<<< HEAD
#include "K60_datatype.h"

void Timer_Init(U8 timer0_ms, U8 timer1_ms)
{
 
    // PIT clock enable:
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
    
    // enable the clock for PIT Timers:
    PIT_MCR = 0;
     
    // config the period of PIT0:
    PIT_LDVAL0 = timer0_ms*PIT0_INIT_VAL;
    // config the period of PIT1:
    PIT_LDVAL1 = timer1_ms*PIT1_INIT_VAL;
    
    // enable interrupt for PIT0:
    PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK; 
    // enable interrupt for PIT1:
    PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK;
    // TIE=1:Interrupt will be requested whenever TIF is set
    
    enable_irq(IRQ_NUM_PIT0); //68
    enable_irq(IRQ_NUM_PIT1); //69
    
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
void EnableTimer1(void) 
{
    ENABLE_PIT1;   
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
void DisableTimer1(void) 
{  
    DISABLE_PIT1;  
}
<<<<<<< HEAD
=======

void Cleartimer0(void)
{
    CLR_PIT0;
    PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //计时器使能
}
void Cleartimer1(void)
{
    CLR_PIT1;
    PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //计时器使能
}
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64

void Cleartimer0(void)
{
    CLR_PIT0;
    PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //计时器使能
}
void Cleartimer1(void)
{
    CLR_PIT1;
    PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //计时器使能
}



=======
#include "K60_datatype.h"

void Timer_Init(U8 timer0_ms, U8 timer1_ms)
{
 
    // PIT clock enable:
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
    
    // enable the clock for PIT Timers:
    PIT_MCR = 0;
     
    // config the period of PIT0:
    PIT_LDVAL0 = timer0_ms*PIT0_INIT_VAL;
    // config the period of PIT1:
    PIT_LDVAL1 = timer1_ms*PIT1_INIT_VAL;
    
    // enable interrupt for PIT0:
    PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK; 
    // enable interrupt for PIT1:
    PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK;
    // TIE=1:Interrupt will be requested whenever TIF is set
    
    enable_irq(IRQ_NUM_PIT0); //68
    enable_irq(IRQ_NUM_PIT1); //69
    
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
void EnableTimer1(void) 
{
    ENABLE_PIT1;   
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
void DisableTimer1(void) 
{  
    DISABLE_PIT1;  
}

void Cleartimer0(void)
{
    CLR_PIT0;
    PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //计时器使能
}
void Cleartimer1(void)
{
    CLR_PIT1;
    PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //计时器使能
}




>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99

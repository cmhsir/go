#ifndef __K60_PIT0_H__
#define __K60_PIT0_H__

#define   IRQ_NUM_PIT0       68

#define   PIT0_INIT_VAL                            62500  // 0.001s/(1/62.5*1000000)


#define   ENABLE_PIT0                              do{PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;}while(0)
#define   DISABLE_PIT0                             do{PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;}while(0)

#define   CLR_PIT0                                 do{PIT_TFLG0 |= PIT_TFLG_TIF_MASK;}while(0) 


void Timer0_Init(void);
void Timer0_isr(void);
void EnableTimer0(void) ;
void DisableTimer0(void) ;

#endif
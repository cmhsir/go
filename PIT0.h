#ifndef __K60_PIT0_H__
#define __K60_PIT0_H__

#define   IRQ_NUM_PIT0       68
#define   IRQ_NUM_PIT1       69

#define   PIT0_INIT_VAL                            62500  // 0.001s/(1/62.5*1000000)
#define   PIT1_INIT_VAL                            62500  // 0.001s/(1/62.5*1000000)

#define   ENABLE_PIT0                              do{PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;}while(0)
#define   DISABLE_PIT0                             do{PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;}while(0)
#define   ENABLE_PIT1                              do{PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;}while(0)
#define   DISABLE_PIT1                             do{PIT_TCTRL1 &= ~PIT_TCTRL_TEN_MASK;}while(0)

#define   CLR_PIT0                                 do{PIT_TFLG0 |= PIT_TFLG_TIF_MASK;}while(0) 
#define   CLR_PIT1                                 do{PIT_TFLG1 |= PIT_TFLG_TIF_MASK;}while(0) 


void Timer_Init(U8 timer0_ms, U8 timer1_ms);
void Timer0_isr(void);
void Timer1_isr(void);
void EnableTimer0(void);
void EnableTimer1(void);
void DisableTimer0(void);
void DisableTimer1(void);
void Cleartimer0(void);
void Cleartimer1(void);

#endif
<<<<<<< HEAD

#ifndef __K60_PWM_H__
#define __K60_PWM_H__

#define PWM_CH0                      0
#define PWM_CH1                      1
#define PWM_CH2                      2
#define PWM_CH3                      3
#define PWM_CH4                      4
#define PWM_CH5                      5
#define PWM_CH6                      6
#define PWM_CH7                      7

#define PWM_PIN_PTA0                 0     // FTM0_CH5
#define PWM_PIN_PTA1                 1     // FTM0_CH6
#define PWM_PIN_PTA2                 2     // FTM0_CH7
#define PWM_PIN_PTA3                 3     // FTM0_CH0
#define PWM_PIN_PTA4                 4     // FTM0_CH1
#define PWM_PIN_PTA5                 5     // FTM0_CH2
#define PWM_PIN_PTA6                 6     // FTM0_CH3 
#define PWM_PIN_PTA7                 7     // FTM0_CH4

#define PWM_PIN_PTA8                 8     // FTM1_CH0
#define PWM_PIN_PTA9                 9     // FTM1_CH1

#define PWM_PIN_PTA10                10    // FTM2_CH0
#define PWM_PIN_PTA11                11    // FTM2_CH1

#define PWM_PIN_PTA12                12    // FTM1_CH0
#define PWM_PIN_PTA13                13    // FTM1_CH1

#define PWM_PIN_PTB0                 14    // FTM1_CH0
#define PWM_PIN_PTB1                 15    // FTM1_CH1
#define PWM_PIN_PTB18                16    // FTM2_CH0
#define PWM_PIN_PTB19                17    // FTM2_CH1

#define PWM_PIN_PTC1                 18    // FTM0_CH0
#define PWM_PIN_PTC2                 19    // FTM0_CH1
#define PWM_PIN_PTC3                 20    // FTM0_CH2
#define PWM_PIN_PTC4                 21    // FTM0_CH3

#define PWM_PIN_PTD4                 22    // FTM0_CH4
#define PWM_PIN_PTD5                 23    // FTM0_CH5
#define PWM_PIN_PTD6                 24    // FTM0_CH6
#define PWM_PIN_PTD7                 25    // FTM0_CH7

#define PWM_FRE_DIV_FACTOR_1         0
#define PWM_FRE_DIV_FACTOR_2         1
#define PWM_FRE_DIV_FACTOR_4         2
#define PWM_FRE_DIV_FACTOR_8         3
#define PWM_FRE_DIV_FACTOR_16        4
#define PWM_FRE_DIV_FACTOR_32        5
#define PWM_FRE_DIV_FACTOR_64        6
#define PWM_FRE_DIV_FACTOR_128       7

#define PWM_MODE_HIGH_ACTIVE         0
#define PWM_MODE_LOW_ACTIVE          1 

// f[sys]=48M, f[PWM]=48K
#define PWM_FRE_FACTOR               249 
#define PWM_FRE_FACTOR1               4999 //修改周期。5.12ms
// f[PWM] = (f[sys]/PWM_FRE_DIV_FACTOR)/(PWM_FRE_FACTOR+1)=96MHZ/2/250          
// PWM_FRE_FACTOR = f[sys]/PWM_FRE_DIV_FACTOR/f[PWM]-1

void PWM_Init(U8 ucPin, U8 ucDivFactor, U8 ucPWMMode);
void PWM_Output(U8 ucPin, U16 ucDuty);
//void pwm_set(U8 pin, U16 duty);

void FTM2_QUAD_init();
void FTM1_QUAD_init();


=======

#ifndef __K60_PWM_H__
#define __K60_PWM_H__

#define PWM_CH0                      0
#define PWM_CH1                      1
#define PWM_CH2                      2
#define PWM_CH3                      3
#define PWM_CH4                      4
#define PWM_CH5                      5
#define PWM_CH6                      6
#define PWM_CH7                      7

#define PWM_PIN_PTA0                 0     // FTM0_CH5
#define PWM_PIN_PTA1                 1     // FTM0_CH6
#define PWM_PIN_PTA2                 2     // FTM0_CH7
#define PWM_PIN_PTA3                 3     // FTM0_CH0
#define PWM_PIN_PTA4                 4     // FTM0_CH1
#define PWM_PIN_PTA5                 5     // FTM0_CH2
#define PWM_PIN_PTA6                 6     // FTM0_CH3 
#define PWM_PIN_PTA7                 7     // FTM0_CH4

#define PWM_PIN_PTA8                 8     // FTM1_CH0
#define PWM_PIN_PTA9                 9     // FTM1_CH1

#define PWM_PIN_PTA10                10    // FTM2_CH0
#define PWM_PIN_PTA11                11    // FTM2_CH1

#define PWM_PIN_PTA12                12    // FTM1_CH0
#define PWM_PIN_PTA13                13    // FTM1_CH1

#define PWM_PIN_PTB0                 14    // FTM1_CH0
#define PWM_PIN_PTB1                 15    // FTM1_CH1
#define PWM_PIN_PTB18                16    // FTM2_CH0
#define PWM_PIN_PTB19                17    // FTM2_CH1

#define PWM_PIN_PTC1                 18    // FTM0_CH0
#define PWM_PIN_PTC2                 19    // FTM0_CH1
#define PWM_PIN_PTC3                 20    // FTM0_CH2
#define PWM_PIN_PTC4                 21    // FTM0_CH3

#define PWM_PIN_PTD4                 22    // FTM0_CH4
#define PWM_PIN_PTD5                 23    // FTM0_CH5
#define PWM_PIN_PTD6                 24    // FTM0_CH6
#define PWM_PIN_PTD7                 25    // FTM0_CH7

#define PWM_FRE_DIV_FACTOR_1         0
#define PWM_FRE_DIV_FACTOR_2         1
#define PWM_FRE_DIV_FACTOR_4         2
#define PWM_FRE_DIV_FACTOR_8         3
#define PWM_FRE_DIV_FACTOR_16        4
#define PWM_FRE_DIV_FACTOR_32        5
#define PWM_FRE_DIV_FACTOR_64        6
#define PWM_FRE_DIV_FACTOR_128       7

#define PWM_MODE_HIGH_ACTIVE         0
#define PWM_MODE_LOW_ACTIVE          1 

// f[sys]=48M, f[PWM]=48K
#define PWM_FRE_FACTOR               249 
#define PWM_FRE_FACTOR1               4999 //修改周期。5.12ms
// f[PWM] = (f[sys]/PWM_FRE_DIV_FACTOR)/(PWM_FRE_FACTOR+1)=96MHZ/2/250          
// PWM_FRE_FACTOR = f[sys]/PWM_FRE_DIV_FACTOR/f[PWM]-1

void PWM_Init(U8 ucPin, U8 ucDivFactor, U8 ucPWMMode);
void PWM_Output(U8 ucPin, U16 ucDuty);
//void pwm_set(U8 pin, U16 duty);

void FTM2_QUAD_init();
void FTM1_QUAD_init();


>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
#endif 
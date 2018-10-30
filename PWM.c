<<<<<<< HEAD

#include "K60_datatype.h"


#ifdef  __cplusplus
extern "C" {
#endif

/******************************************************************************************************************/
/*PWM port                                                                                                        */
/******************************************************************************************************************/

/***FUNC+*********************************************************************/
/* Name   : PWM_Init                                                         */
/* Descrp : initialize PWM                                                   */
/* Input  : None                                                             */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
  
void FTM2_QUAD_init()
{
    PORTB_PCR18=PORT_PCR_MUX(6);//设置PTB18为正交解码功能
    PORTB_PCR18|=0x03;
    PORTB_PCR19=PORT_PCR_MUX(6);//设置PTB19为正交解码功能
    PORTB_PCR19|=0x03;
    
    SIM_SCGC3|=SIM_SCGC3_FTM2_MASK;  //使能FTM时钟
    FTM2_MODE|=FTM_MODE_WPDIS_MASK;  //写禁止保护
    
    FTM2_QDCTRL|=FTM_QDCTRL_QUADMODE_MASK; //AB相同时确定方向和计数值
    
    FTM2_CNTIN=0;//FTMCNT,TOF
    FTM2_MOD=65535;
    
    FTM2_QDCTRL|=FTM_QDCTRL_QUADEN_MASK;//启用FTM2正交解码模式
    FTM2_MODE|=FTM_MODE_FTMEN_MASK;
    FTM2_CNT=0;//CNT
}

void FTM1_QUAD_init()
{
    PORTA_PCR12=PORT_PCR_MUX(7);//设置PTB18为正交解码功能
    PORTA_PCR12|=0x03;
    PORTA_PCR13=PORT_PCR_MUX(7);//设置PTB19为正交解码功能
    PORTA_PCR13|=0x03;
    
    
    SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;  //使能FTM时钟
    FTM1_MODE|=FTM_MODE_WPDIS_MASK;  //写禁止保护
    
    FTM1_QDCTRL|=FTM_QDCTRL_QUADMODE_MASK; //AB相同时确定方向和计数值
    
    FTM1_CNTIN=0;
    FTM1_MOD=65535;
    
    FTM1_QDCTRL|=FTM_QDCTRL_QUADEN_MASK;//启用FTM2正交解码模式
    FTM1_MODE|=FTM_MODE_FTMEN_MASK;
    FTM1_CNT=0;
}

            //输出引脚  //FTM分频时钟   //对齐方式
void PWM_Init(U8 ucPin, U8 ucDivFactor, U8 ucPWMMode)
{
      
    FTM_MemMapPtr pstFTMModule;
    
    UCHAR  ucFTMCh;
    
    
    // 1. config port for PWM:   
    switch (ucPin)
    {
        case PWM_PIN_PTA0:
                         //对应的端口设置成GPIO输出
            PORTA_PCR0 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH5;
            break;       
        
        case PWM_PIN_PTA1:
            
            PORTA_PCR1 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTA2:
            
            PORTA_PCR2 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        case PWM_PIN_PTA3:
            
            PORTA_PCR3 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;  
                
        case PWM_PIN_PTA4:
            
            PORTA_PCR4 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;       
        
        case PWM_PIN_PTA5:
            
            PORTA_PCR5 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;
            
        case PWM_PIN_PTA6:
            
            PORTA_PCR6 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTA7:
            
            PORTA_PCR7 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4;
            break;
            
        case PWM_PIN_PTA8:
            
            PORTA_PCR8 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTA9:
            
            PORTA_PCR9 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM1_BASE_PTR; 
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA10:
            
            PORTA_PCR10 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA11:
            
            PORTA_PCR11 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA12:
            
            PORTA_PCR12 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA13:
            
            PORTA_PCR13 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB0:
            
            PORTB_PCR0 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTB1:
            
            PORTB_PCR1 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB18:
            
            PORTB_PCR18 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTB19:
            
            PORTB_PCR19 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC1:
            
            PORTC_PCR1 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTC2:
            
            PORTC_PCR2 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC3:
            
            PORTC_PCR3 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;  
                
        case PWM_PIN_PTC4:
            
            PORTC_PCR4 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTD4:
            
            PORTD_PCR4 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4; 
            break;       
        
        case PWM_PIN_PTD5:
            
            PORTD_PCR5 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH5;
            break;
            
        case PWM_PIN_PTD6:
            
            PORTD_PCR6 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTD7:
            
            PORTD_PCR7 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        default:
        
            return;
    }
    
// 2. FTM clock enable: 
    if (FTM0_BASE_PTR == pstFTMModule)   
    {
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;	
        //FTM0的时钟打开
    }
    else if (FTM1_BASE_PTR == pstFTMModule)
    {
        SIM_SCGC6 |=SIM_SCGC6_FTM1_MASK;
    }
    else
    {
        SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
    }
    
// 3. config PWM:   
    //ucDivFactor为分频系数，总线时钟分频得到FTM时钟
    //ucDivFactor对应FTMx_SC寄存器的PC位，总线时钟分频得到FTM时钟
    
    
    ucDivFactor &= 0x07;
    
    pstFTMModule->SC |= (FTM_SC_CLKS(1)             
                        |FTM_SC_PS(ucDivFactor));   
    
    pstFTMModule->CNTIN = 0;
    
    
    if(ucPin==PWM_PIN_PTA10)
    {
      pstFTMModule->MOD   = PWM_FRE_FACTOR1; 
    }
    else
    {
      pstFTMModule->MOD   = PWM_FRE_FACTOR;
    }
    
  
    FTM_CnSC_REG(pstFTMModule,ucFTMCh) |= FTM_CnSC_MSB_MASK;       // MSB=1:Edge-aligned PWM
    
       
    if (PWM_MODE_LOW_ACTIVE == ucPWMMode)
    {
        FTM_CnSC_REG(pstFTMModule,ucFTMCh) |= FTM_CnSC_ELSA_MASK;  // ELSA=1:Low active	
    }
    
    else
    {
        FTM_CnSC_REG(pstFTMModule,ucFTMCh) |= FTM_CnSC_ELSB_MASK;  // ELSB ELSL=10:High active
        FTM_CnSC_REG(pstFTMModule,ucFTMCh) &= ~FTM_CnSC_ELSA_MASK;
    }
                              
    FTM_CnV_REG(pstFTMModule,ucFTMCh) = 0;                         // 0% for initiation
                
}

/***FUNC+*********************************************************************/
/* Name   : PWM_Output                                                       */
/* Descrp : output for PWM                                                   */
/* Input  : None                                                             */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
void PWM_Output(U8 ucPin, U16 ucDuty)
{
    
    FTM_MemMapPtr pstFTMModule;
    
    U8  ucFTMCh;
       
    switch (ucPin)
    {
        case PWM_PIN_PTA0:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH5;
            break;       
        
        case PWM_PIN_PTA1:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTA2:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        case PWM_PIN_PTA3:
            
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;  
                
        case PWM_PIN_PTA4:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;       
        
        case PWM_PIN_PTA5:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;
            
        case PWM_PIN_PTA6:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTA7:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4;
            break;
            
        case PWM_PIN_PTA8:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTA9:
            
            pstFTMModule = FTM1_BASE_PTR; 
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA10:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA11:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA12:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA13:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB0:

            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTB1:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB18:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTB19:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC1:
            
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTC2:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC3:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;  
                
        case PWM_PIN_PTC4:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTD4:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4; 
            break;       
        
        case PWM_PIN_PTD5:
            
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH5;
            break;
            
        case PWM_PIN_PTD6:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTD7:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        default:
        
            return;
    }
    if(ucPin==PWM_PIN_PTA10)
    {
          if (ucDuty >= 4999)//mod   //修改周期。5.12ms
        {
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = 4999;  //修改周期。5.12ms
        }
        
        else
        {    
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = ucDuty ;
        }
    }
    else
    {
        if (ucDuty >= 250)//mod
        {
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = 250;
        }
        else
        {    
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = ucDuty ;
        }
    }
    
    
}


//void pwm_set(U8 pin, U16 duty)
//{
//    duty *= 10;
//    if(duty >= 250)
//        duty = 250;
//    PWM_Output(pin, duty);
//}

#ifdef  __cplusplus
}
#endif
=======

#include "K60_datatype.h"


#ifdef  __cplusplus
extern "C" {
#endif

/******************************************************************************************************************/
/*PWM port                                                                                                        */
/******************************************************************************************************************/

/***FUNC+*********************************************************************/
/* Name   : PWM_Init                                                         */
/* Descrp : initialize PWM                                                   */
/* Input  : None                                                             */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
  
void FTM2_QUAD_init()
{
    PORTB_PCR18=PORT_PCR_MUX(6);//设置PTB18为正交解码功能
    PORTB_PCR18|=0x03;
    PORTB_PCR19=PORT_PCR_MUX(6);//设置PTB19为正交解码功能
    PORTB_PCR19|=0x03;
    
    SIM_SCGC3|=SIM_SCGC3_FTM2_MASK;  //使能FTM时钟
    FTM2_MODE|=FTM_MODE_WPDIS_MASK;  //写禁止保护
    
    FTM2_QDCTRL|=FTM_QDCTRL_QUADMODE_MASK; //AB相同时确定方向和计数值
    
    FTM2_CNTIN=0;//FTMCNT,TOF
    FTM2_MOD=65535;
    
    FTM2_QDCTRL|=FTM_QDCTRL_QUADEN_MASK;//启用FTM2正交解码模式
    FTM2_MODE|=FTM_MODE_FTMEN_MASK;
    FTM2_CNT=0;//CNT
}

void FTM1_QUAD_init()
{
    PORTA_PCR12=PORT_PCR_MUX(7);//设置PTB18为正交解码功能
    PORTA_PCR12|=0x03;
    PORTA_PCR13=PORT_PCR_MUX(7);//设置PTB19为正交解码功能
    PORTA_PCR13|=0x03;
    
    
    SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;  //使能FTM时钟
    FTM1_MODE|=FTM_MODE_WPDIS_MASK;  //写禁止保护
    
    FTM1_QDCTRL|=FTM_QDCTRL_QUADMODE_MASK; //AB相同时确定方向和计数值
    
    FTM1_CNTIN=0;
    FTM1_MOD=65535;
    
    FTM1_QDCTRL|=FTM_QDCTRL_QUADEN_MASK;//启用FTM2正交解码模式
    FTM1_MODE|=FTM_MODE_FTMEN_MASK;
    FTM1_CNT=0;
}

            //输出引脚  //FTM分频时钟   //对齐方式
void PWM_Init(U8 ucPin, U8 ucDivFactor, U8 ucPWMMode)
{
      
    FTM_MemMapPtr pstFTMModule;
    
    UCHAR  ucFTMCh;
    
    
    // 1. config port for PWM:   
    switch (ucPin)
    {
        case PWM_PIN_PTA0:
                         //对应的端口设置成GPIO输出
            PORTA_PCR0 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH5;
            break;       
        
        case PWM_PIN_PTA1:
            
            PORTA_PCR1 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTA2:
            
            PORTA_PCR2 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        case PWM_PIN_PTA3:
            
            PORTA_PCR3 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;  
                
        case PWM_PIN_PTA4:
            
            PORTA_PCR4 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;       
        
        case PWM_PIN_PTA5:
            
            PORTA_PCR5 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;
            
        case PWM_PIN_PTA6:
            
            PORTA_PCR6 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTA7:
            
            PORTA_PCR7 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4;
            break;
            
        case PWM_PIN_PTA8:
            
            PORTA_PCR8 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTA9:
            
            PORTA_PCR9 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM1_BASE_PTR; 
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA10:
            
            PORTA_PCR10 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA11:
            
            PORTA_PCR11 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA12:
            
            PORTA_PCR12 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA13:
            
            PORTA_PCR13 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB0:
            
            PORTB_PCR0 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTB1:
            
            PORTB_PCR1 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB18:
            
            PORTB_PCR18 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTB19:
            
            PORTB_PCR19 = PORT_PCR_MUX(0x3) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC1:
            
            PORTC_PCR1 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTC2:
            
            PORTC_PCR2 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC3:
            
            PORTC_PCR3 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;  
                
        case PWM_PIN_PTC4:
            
            PORTC_PCR4 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTD4:
            
            PORTD_PCR4 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4; 
            break;       
        
        case PWM_PIN_PTD5:
            
            PORTD_PCR5 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK;
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH5;
            break;
            
        case PWM_PIN_PTD6:
            
            PORTD_PCR6 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTD7:
            
            PORTD_PCR7 = PORT_PCR_MUX(0x4) | PORT_PCR_DSE_MASK; 
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        default:
        
            return;
    }
    
// 2. FTM clock enable: 
    if (FTM0_BASE_PTR == pstFTMModule)   
    {
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;	
        //FTM0的时钟打开
    }
    else if (FTM1_BASE_PTR == pstFTMModule)
    {
        SIM_SCGC6 |=SIM_SCGC6_FTM1_MASK;
    }
    else
    {
        SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
    }
    
// 3. config PWM:   
    //ucDivFactor为分频系数，总线时钟分频得到FTM时钟
    //ucDivFactor对应FTMx_SC寄存器的PC位，总线时钟分频得到FTM时钟
    
    
    ucDivFactor &= 0x07;
    
    pstFTMModule->SC |= (FTM_SC_CLKS(1)             
                        |FTM_SC_PS(ucDivFactor));   
    
    pstFTMModule->CNTIN = 0;
    
    
    if(ucPin==PWM_PIN_PTA10)
    {
      pstFTMModule->MOD   = PWM_FRE_FACTOR1; 
    }
    else
    {
      pstFTMModule->MOD   = PWM_FRE_FACTOR;
    }
    
  
    FTM_CnSC_REG(pstFTMModule,ucFTMCh) |= FTM_CnSC_MSB_MASK;       // MSB=1:Edge-aligned PWM
    
       
    if (PWM_MODE_LOW_ACTIVE == ucPWMMode)
    {
        FTM_CnSC_REG(pstFTMModule,ucFTMCh) |= FTM_CnSC_ELSA_MASK;  // ELSA=1:Low active	
    }
    
    else
    {
        FTM_CnSC_REG(pstFTMModule,ucFTMCh) |= FTM_CnSC_ELSB_MASK;  // ELSB ELSL=10:High active
        FTM_CnSC_REG(pstFTMModule,ucFTMCh) &= ~FTM_CnSC_ELSA_MASK;
    }
                              
    FTM_CnV_REG(pstFTMModule,ucFTMCh) = 0;                         // 0% for initiation
                
}

/***FUNC+*********************************************************************/
/* Name   : PWM_Output                                                       */
/* Descrp : output for PWM                                                   */
/* Input  : None                                                             */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
void PWM_Output(U8 ucPin, U16 ucDuty)
{
    
    FTM_MemMapPtr pstFTMModule;
    
    U8  ucFTMCh;
       
    switch (ucPin)
    {
        case PWM_PIN_PTA0:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH5;
            break;       
        
        case PWM_PIN_PTA1:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTA2:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        case PWM_PIN_PTA3:
            
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;  
                
        case PWM_PIN_PTA4:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;       
        
        case PWM_PIN_PTA5:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;
            
        case PWM_PIN_PTA6:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTA7:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4;
            break;
            
        case PWM_PIN_PTA8:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTA9:
            
            pstFTMModule = FTM1_BASE_PTR; 
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA10:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA11:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTA12:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTA13:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB0:

            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;       
        
        case PWM_PIN_PTB1:
            
            pstFTMModule = FTM1_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTB18:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTB19:
            
            pstFTMModule = FTM2_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC1:
            
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH0;
            break;
            
        case PWM_PIN_PTC2:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH1;
            break;
            
        case PWM_PIN_PTC3:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH2;
            break;  
                
        case PWM_PIN_PTC4:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH3;
            break;
            
        case PWM_PIN_PTD4:
            
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH4; 
            break;       
        
        case PWM_PIN_PTD5:
            
            pstFTMModule = FTM0_BASE_PTR; 
            ucFTMCh = PWM_CH5;
            break;
            
        case PWM_PIN_PTD6:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH6;
            break;
            
        case PWM_PIN_PTD7:
             
            pstFTMModule = FTM0_BASE_PTR;
            ucFTMCh = PWM_CH7;
            break;
            
        default:
        
            return;
    }
    if(ucPin==PWM_PIN_PTA10)
    {
          if (ucDuty >= 4999)//mod   //修改周期。5.12ms
        {
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = 4999;  //修改周期。5.12ms
        }
        
        else
        {    
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = ucDuty ;
        }
    }
    else
    {
        if (ucDuty >= 250)//mod
        {
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = 250;
        }
        else
        {    
            FTM_CnV_REG(pstFTMModule,ucFTMCh) = ucDuty ;
        }
    }
    
    
}


//void pwm_set(U8 pin, U16 duty)
//{
//    duty *= 10;
//    if(duty >= 250)
//        duty = 250;
//    PWM_Output(pin, duty);
//}

#ifdef  __cplusplus
}
#endif
>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99

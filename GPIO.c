<<<<<<< HEAD
#include "K60_datatype.h"

volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; 
//定义五个指针数组保存 GPIOx 的地址
volatile struct PORT_MemMap *PORTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};


void time_delay_ms(unsigned int count_val)
{
  SIM_SCGC5|=SIM_SCGC5_LPTIMER_MASK; //Turn on clock to LPTMR module
  LPTMR0_CMR = count_val; //Set compare value
  LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK; //Use 1Khz LPO clock and bypass prescaler
  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; //Start counting

  while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)) {} //Wait for counter to reach compare value

  LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK; //Clear Timer Compare Flag

  return;
}

void delay(int xsm)
{
  int i,j;
  for(i=0;i<xsm;i++)
    for(j=0;j<1000;j++);
}

//===========================================================================
//函数名称：gpio_init
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
//函数返回：函数执行状态。0=成功，其它为异常。
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//          dir：引脚方向。 1=输出，0=输入。
//          state：引脚初始状态。1=高电平，0=低电平
//功能概要：初始化端口作为GPIO引脚的功能。
//===========================================================================
U8 Gpio_init(U8 port, U8 pin, U8 dir, U8 state)
{
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    PORT_MemMapPtr p  = Gpio_get_port_addr(port);
    
    if (!p) return 1;  //参数错误
     
    //设定通用端口引脚控制寄存器的值，设定为GPIO功能
    PORT_PCR_REG(p, pin) = (0|PORT_PCR_MUX(1));

    if(dir == 1) //若引脚被定义为输出
    {
        GPIO_PDDR_REG(pt) |= (1<<pin);
    
        //设定引脚初始化状态
        if(state == 1)
            BSET(pin, GPIO_PDOR_REG(pt));
        else
            BCLR(pin, GPIO_PDOR_REG(pt));
    }
    else //若引脚被定义为输入 
    {
        BCLR(pin, GPIO_PDDR_REG(pt));
    }

    return 0;  //成功返回
}

//===========================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//          state：引脚初始状态。1=高电平，0=低电平
//功能概要：设置指定引脚状态。
//===========================================================================
void Gpio_set(U8 port, U8 pin, U8 state)
{
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
        
    if (state == 0) //控制为低电平
        BCLR(pin, GPIO_PDOR_REG(pt));
    else            //控制为高电平
        BSET(pin, GPIO_PDOR_REG(pt));
}

//===========================================================================
//函数名称：gpio_get
//函数返回：指定引脚状态。0=低电平，1=高电平。
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//功能概要：获取指定引脚状态。
//===========================================================================
U8 Gpio_get(U8 port, U8 pin)
{
    U8 i; 
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //查看引脚状态
    i = BGET(pin, GPIO_PDIR_REG(pt));
    return i;     //返回引脚状态（0或1）
}

//===========================================================================
//函数名称gpio_reverse
//函数返回：无
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//功能概要：反转指定引脚状态。
//===========================================================================
void Gpio_reverse(U8 port, U8 pin)
{
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //设置输出取反寄存器的相应位为1，反转指定引脚状态  
    BSET(pin, GPIO_PTOR_REG(pt));
}

//===========================================================================
//函数名称：gpio_get_port_addr
//函数返回：端口号对应的端口寄存器组指针
//参数说明：无
//功能概要：将端口号转换成端口寄存器组指针。内部调用。
//===========================================================================
PORT_MemMapPtr Gpio_get_port_addr (U8 port)
{
    PORT_MemMapPtr p;
    
    switch(port)
    {
    case PORT_A:
        p = PORTA_BASE_PTR;
        break;
    case PORT_B:
        p = PORTB_BASE_PTR;
        break;
    case PORT_C:
        p = PORTC_BASE_PTR;
        break;
    case PORT_D:
        p = PORTD_BASE_PTR;
        break;
    case PORT_E:
        p = PORTE_BASE_PTR;
        break;
    default:
        return 0; //输入参数无效返回
    }
    
    return p;
}

//===========================================================================
//函数名称：gpio_get_pt_addr
//函数返回：端口号对应的GPIO端口寄存器组指针
//参数说明：无
//功能概要：将端口号转换成端口寄存器组指针。内部调用。
//===========================================================================
GPIO_MemMapPtr Gpio_get_pt_addr(U8 port)
{
    GPIO_MemMapPtr p;
    
    switch(port)
    {
    case PORT_A:
        p = PTA_BASE_PTR;
        break;
    case PORT_B:
        p = PTB_BASE_PTR;
        break;
    case PORT_C:
        p = PTC_BASE_PTR;
        break;
    case PORT_D:
        p = PTD_BASE_PTR;
        break;
    case PORT_E:
        p = PTE_BASE_PTR;
        break;
    default:
        return 0; //输入参数无效返回
    }
    
    return p;
=======
#include "K60_datatype.h"

volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; 
//定义五个指针数组保存 GPIOx 的地址
volatile struct PORT_MemMap *PORTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};


void time_delay_ms(unsigned int count_val)
{
  SIM_SCGC5|=SIM_SCGC5_LPTIMER_MASK; //Turn on clock to LPTMR module
  LPTMR0_CMR = count_val; //Set compare value
  LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK; //Use 1Khz LPO clock and bypass prescaler
  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; //Start counting

  while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)) {} //Wait for counter to reach compare value

  LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK; //Clear Timer Compare Flag

  return;
}

void delay(int xsm)
{
  int i,j;
  for(i=0;i<xsm;i++)
    for(j=0;j<1000;j++);
}

//===========================================================================
//函数名称：gpio_init
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
//函数返回：函数执行状态。0=成功，其它为异常。
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//          dir：引脚方向。 1=输出，0=输入。
//          state：引脚初始状态。1=高电平，0=低电平
//功能概要：初始化端口作为GPIO引脚的功能。
//===========================================================================
U8 Gpio_init(U8 port, U8 pin, U8 dir, U8 state)
{
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    PORT_MemMapPtr p  = Gpio_get_port_addr(port);
    
    if (!p) return 1;  //参数错误
     
    //设定通用端口引脚控制寄存器的值，设定为GPIO功能
    PORT_PCR_REG(p, pin) = (0|PORT_PCR_MUX(1));

    if(dir == 1) //若引脚被定义为输出
    {
        GPIO_PDDR_REG(pt) |= (1<<pin);
    
        //设定引脚初始化状态
        if(state == 1)
            BSET(pin, GPIO_PDOR_REG(pt));
        else
            BCLR(pin, GPIO_PDOR_REG(pt));
    }
    else //若引脚被定义为输入 
    {
        BCLR(pin, GPIO_PDDR_REG(pt));
    }

    return 0;  //成功返回
}

//===========================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//          state：引脚初始状态。1=高电平，0=低电平
//功能概要：设置指定引脚状态。
//===========================================================================
void Gpio_set(U8 port, U8 pin, U8 state)
{
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
        
    if (state == 0) //控制为低电平
        BCLR(pin, GPIO_PDOR_REG(pt));
    else            //控制为高电平
        BSET(pin, GPIO_PDOR_REG(pt));
}

//===========================================================================
//函数名称：gpio_get
//函数返回：指定引脚状态。0=低电平，1=高电平。
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//功能概要：获取指定引脚状态。
//===========================================================================
U8 Gpio_get(U8 port, U8 pin)
{
    U8 i; 
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //查看引脚状态
    i = BGET(pin, GPIO_PDIR_REG(pt));
    return i;     //返回引脚状态（0或1）
}

//===========================================================================
//函数名称gpio_reverse
//函数返回：无
//参数说明：port：端口号。由宏定义。
//          pin：引脚号。0～31。
//功能概要：反转指定引脚状态。
//===========================================================================
void Gpio_reverse(U8 port, U8 pin)
{
    //将GPIO端口号转换成端口寄存器组指针
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //设置输出取反寄存器的相应位为1，反转指定引脚状态  
    BSET(pin, GPIO_PTOR_REG(pt));
}

//===========================================================================
//函数名称：gpio_get_port_addr
//函数返回：端口号对应的端口寄存器组指针
//参数说明：无
//功能概要：将端口号转换成端口寄存器组指针。内部调用。
//===========================================================================
PORT_MemMapPtr Gpio_get_port_addr (U8 port)
{
    PORT_MemMapPtr p;
    
    switch(port)
    {
    case PORT_A:
        p = PORTA_BASE_PTR;
        break;
    case PORT_B:
        p = PORTB_BASE_PTR;
        break;
    case PORT_C:
        p = PORTC_BASE_PTR;
        break;
    case PORT_D:
        p = PORTD_BASE_PTR;
        break;
    case PORT_E:
        p = PORTE_BASE_PTR;
        break;
    default:
        return 0; //输入参数无效返回
    }
    
    return p;
}

//===========================================================================
//函数名称：gpio_get_pt_addr
//函数返回：端口号对应的GPIO端口寄存器组指针
//参数说明：无
//功能概要：将端口号转换成端口寄存器组指针。内部调用。
//===========================================================================
GPIO_MemMapPtr Gpio_get_pt_addr(U8 port)
{
    GPIO_MemMapPtr p;
    
    switch(port)
    {
    case PORT_A:
        p = PTA_BASE_PTR;
        break;
    case PORT_B:
        p = PTB_BASE_PTR;
        break;
    case PORT_C:
        p = PTC_BASE_PTR;
        break;
    case PORT_D:
        p = PTD_BASE_PTR;
        break;
    case PORT_E:
        p = PTE_BASE_PTR;
        break;
    default:
        return 0; //输入参数无效返回
    }
    
    return p;
>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
}
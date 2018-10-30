<<<<<<< HEAD
#include "K60_datatype.h"

volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; 
//�������ָ�����鱣�� GPIOx �ĵ�ַ
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
//�������ƣ�gpio_init
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
//�������أ�����ִ��״̬��0=�ɹ�������Ϊ�쳣��
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//          dir�����ŷ��� 1=�����0=���롣
//          state�����ų�ʼ״̬��1=�ߵ�ƽ��0=�͵�ƽ
//���ܸ�Ҫ����ʼ���˿���ΪGPIO���ŵĹ��ܡ�
//===========================================================================
U8 Gpio_init(U8 port, U8 pin, U8 dir, U8 state)
{
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    PORT_MemMapPtr p  = Gpio_get_port_addr(port);
    
    if (!p) return 1;  //��������
     
    //�趨ͨ�ö˿����ſ��ƼĴ�����ֵ���趨ΪGPIO����
    PORT_PCR_REG(p, pin) = (0|PORT_PCR_MUX(1));

    if(dir == 1) //�����ű�����Ϊ���
    {
        GPIO_PDDR_REG(pt) |= (1<<pin);
    
        //�趨���ų�ʼ��״̬
        if(state == 1)
            BSET(pin, GPIO_PDOR_REG(pt));
        else
            BCLR(pin, GPIO_PDOR_REG(pt));
    }
    else //�����ű�����Ϊ���� 
    {
        BCLR(pin, GPIO_PDDR_REG(pt));
    }

    return 0;  //�ɹ�����
}

//===========================================================================
//�������ƣ�gpio_set
//�������أ���
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//          state�����ų�ʼ״̬��1=�ߵ�ƽ��0=�͵�ƽ
//���ܸ�Ҫ������ָ������״̬��
//===========================================================================
void Gpio_set(U8 port, U8 pin, U8 state)
{
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
        
    if (state == 0) //����Ϊ�͵�ƽ
        BCLR(pin, GPIO_PDOR_REG(pt));
    else            //����Ϊ�ߵ�ƽ
        BSET(pin, GPIO_PDOR_REG(pt));
}

//===========================================================================
//�������ƣ�gpio_get
//�������أ�ָ������״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//���ܸ�Ҫ����ȡָ������״̬��
//===========================================================================
U8 Gpio_get(U8 port, U8 pin)
{
    U8 i; 
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //�鿴����״̬
    i = BGET(pin, GPIO_PDIR_REG(pt));
    return i;     //��������״̬��0��1��
}

//===========================================================================
//��������gpio_reverse
//�������أ���
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//���ܸ�Ҫ����תָ������״̬��
//===========================================================================
void Gpio_reverse(U8 port, U8 pin)
{
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //�������ȡ���Ĵ�������ӦλΪ1����תָ������״̬  
    BSET(pin, GPIO_PTOR_REG(pt));
}

//===========================================================================
//�������ƣ�gpio_get_port_addr
//�������أ��˿ںŶ�Ӧ�Ķ˿ڼĴ�����ָ��
//����˵������
//���ܸ�Ҫ�����˿ں�ת���ɶ˿ڼĴ�����ָ�롣�ڲ����á�
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
        return 0; //���������Ч����
    }
    
    return p;
}

//===========================================================================
//�������ƣ�gpio_get_pt_addr
//�������أ��˿ںŶ�Ӧ��GPIO�˿ڼĴ�����ָ��
//����˵������
//���ܸ�Ҫ�����˿ں�ת���ɶ˿ڼĴ�����ָ�롣�ڲ����á�
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
        return 0; //���������Ч����
    }
    
    return p;
=======
#include "K60_datatype.h"

volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; 
//�������ָ�����鱣�� GPIOx �ĵ�ַ
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
//�������ƣ�gpio_init
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
//�������أ�����ִ��״̬��0=�ɹ�������Ϊ�쳣��
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//          dir�����ŷ��� 1=�����0=���롣
//          state�����ų�ʼ״̬��1=�ߵ�ƽ��0=�͵�ƽ
//���ܸ�Ҫ����ʼ���˿���ΪGPIO���ŵĹ��ܡ�
//===========================================================================
U8 Gpio_init(U8 port, U8 pin, U8 dir, U8 state)
{
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    PORT_MemMapPtr p  = Gpio_get_port_addr(port);
    
    if (!p) return 1;  //��������
     
    //�趨ͨ�ö˿����ſ��ƼĴ�����ֵ���趨ΪGPIO����
    PORT_PCR_REG(p, pin) = (0|PORT_PCR_MUX(1));

    if(dir == 1) //�����ű�����Ϊ���
    {
        GPIO_PDDR_REG(pt) |= (1<<pin);
    
        //�趨���ų�ʼ��״̬
        if(state == 1)
            BSET(pin, GPIO_PDOR_REG(pt));
        else
            BCLR(pin, GPIO_PDOR_REG(pt));
    }
    else //�����ű�����Ϊ���� 
    {
        BCLR(pin, GPIO_PDDR_REG(pt));
    }

    return 0;  //�ɹ�����
}

//===========================================================================
//�������ƣ�gpio_set
//�������أ���
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//          state�����ų�ʼ״̬��1=�ߵ�ƽ��0=�͵�ƽ
//���ܸ�Ҫ������ָ������״̬��
//===========================================================================
void Gpio_set(U8 port, U8 pin, U8 state)
{
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
        
    if (state == 0) //����Ϊ�͵�ƽ
        BCLR(pin, GPIO_PDOR_REG(pt));
    else            //����Ϊ�ߵ�ƽ
        BSET(pin, GPIO_PDOR_REG(pt));
}

//===========================================================================
//�������ƣ�gpio_get
//�������أ�ָ������״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//���ܸ�Ҫ����ȡָ������״̬��
//===========================================================================
U8 Gpio_get(U8 port, U8 pin)
{
    U8 i; 
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //�鿴����״̬
    i = BGET(pin, GPIO_PDIR_REG(pt));
    return i;     //��������״̬��0��1��
}

//===========================================================================
//��������gpio_reverse
//�������أ���
//����˵����port���˿ںš��ɺ궨�塣
//          pin�����źš�0��31��
//���ܸ�Ҫ����תָ������״̬��
//===========================================================================
void Gpio_reverse(U8 port, U8 pin)
{
    //��GPIO�˿ں�ת���ɶ˿ڼĴ�����ָ��
    GPIO_MemMapPtr pt = Gpio_get_pt_addr(port);
    //�������ȡ���Ĵ�������ӦλΪ1����תָ������״̬  
    BSET(pin, GPIO_PTOR_REG(pt));
}

//===========================================================================
//�������ƣ�gpio_get_port_addr
//�������أ��˿ںŶ�Ӧ�Ķ˿ڼĴ�����ָ��
//����˵������
//���ܸ�Ҫ�����˿ں�ת���ɶ˿ڼĴ�����ָ�롣�ڲ����á�
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
        return 0; //���������Ч����
    }
    
    return p;
}

//===========================================================================
//�������ƣ�gpio_get_pt_addr
//�������أ��˿ںŶ�Ӧ��GPIO�˿ڼĴ�����ָ��
//����˵������
//���ܸ�Ҫ�����˿ں�ת���ɶ˿ڼĴ�����ָ�롣�ڲ����á�
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
        return 0; //���������Ч����
    }
    
    return p;
>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99
}
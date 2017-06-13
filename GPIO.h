#ifndef __K60_GPIO_H__
#define __K60_GPIO_H__

//芯片端口名定义
#define PORT_MAX_NUM 5  //端口数量(保留给RTOS使用)

//各GPIO口统一名称:PORT_A、 PORT_B、 PORT_C、 PORT_D、PORT_E
#define PORT_A   0      
#define PORT_B   1
#define PORT_C   2
#define PORT_D   3
#define PORT_E   4

//灯状态宏定义（灯亮、灯暗对应的物理电平由硬件接法决定）
#define LED_ON        0         //灯亮
#define LED_OFF       1         //灯暗

#define PIN_IN        0
#define PIN_OUT       1


//置位、清位、获得寄存器一位的状态
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //获得寄存器一位的状态


#define PSET(Pin,Register)  ((Register)|= (Pin))    //置寄存器的1 byte
#define PCLR(Pin,Register)  ((Register) &= ~(Pin))  //清寄存器的1 byte

extern volatile struct GPIO_MemMap *GPIOx[5]; //定义五个指针数组保存 GPIOx 的地址
extern volatile struct PORT_MemMap *PORTX[5];

typedef enum PTxn
{
    /*  PTA端口    */ //0~31
    PTA0,
    PTA1,
    PTA2,
    PTA3,
    PTA4,
    PTA5,
    PTA6,
    PTA7,
    PTA8,
    PTA9,
    PTA10,
    PTA11,
    PTA12,
    PTA13,
    PTA14,
    PTA15,
    PTA16,
    PTA17,
    PTA18,
    PTA19,
    PTA20,
    PTA21,
    PTA22,
    PTA23,
    PTA24,
    PTA25,
    PTA26,
    PTA27,
    PTA28,
    PTA29,
    PTA30,
    PTA31,

    /*  PTB端口    */   //32~63
    PTB0,
    PTB1,
    PTB2,
    PTB3,
    PTB4,
    PTB5,
    PTB6,
    PTB7,
    PTB8,
    PTB9,
    PTB10,
    PTB11,
    PTB12,
    PTB13,
    PTB14,
    PTB15,
    PTB16,
    PTB17,
    PTB18,
    PTB19,
    PTB20,
    PTB21,
    PTB22,
    PTB23,
    PTB24,
    PTB25,
    PTB26,
    PTB27,
    PTB28,
    PTB29,
    PTB30,
    PTB31,

    /*  PTC端口    */
    PTC0,
    PTC1,
    PTC2,
    PTC3,
    PTC4,
    PTC5,
    PTC6,
    PTC7,
    PTC8,
    PTC9,
    PTC10,
    PTC11,
    PTC12,
    PTC13,
    PTC14,
    PTC15,
    PTC16,
    PTC17,
    PTC18,
    PTC19,
    PTC20,
    PTC21,
    PTC22,
    PTC23,
    PTC24,
    PTC25,
    PTC26,
    PTC27,
    PTC28,
    PTC29,
    PTC30,
    PTC31,

    /*  PTD端口    */
    PTD0,
    PTD1,
    PTD2,
    PTD3,
    PTD4,
    PTD5,
    PTD6,
    PTD7,
    PTD8,
    PTD9,
    PTD10,
    PTD11,
    PTD12,
    PTD13,
    PTD14,
    PTD15,
    PTD16,
    PTD17,
    PTD18,
    PTD19,
    PTD20,
    PTD21,
    PTD22,
    PTD23,
    PTD24,
    PTD25,
    PTD26,
    PTD27,
    PTD28,
    PTD29,
    PTD30,
    PTD31,

    /*  PTE端口    */
    PTE0,
    PTE1,
    PTE2,
    PTE3,
    PTE4,
    PTE5,
    PTE6,
    PTE7,
    PTE8,
    PTE9,
    PTE10,
    PTE11,
    PTE12,
    PTE13,
    PTE14,
    PTE15,
    PTE16,
    PTE17,
    PTE18,
    PTE19,
    PTE20,
    PTE21,
    PTE22,
    PTE23,
    PTE24,
    PTE25,
    PTE26,
    PTE27,
    PTE28,
    PTE29,
    PTE30,
    PTE31,

} PTxn;


U8 Gpio_init(U8 port, U8 pin, U8 dir, U8 state);
void Gpio_set(U8 port, U8 pin, U8 state);
U8 Gpio_get(U8 port, U8 pin);
void Gpio_set_Pin(U8 port, U8 pin);
U32 Gpio_get_Pin(U8 port);
void Gpio_reverse(U8 port, U8 pin);
PORT_MemMapPtr Gpio_get_port_addr (U8 port);
GPIO_MemMapPtr Gpio_get_pt_addr(U8 port);
void time_delay_ms(unsigned int count_val);
void delay(int xsm);

#endif  


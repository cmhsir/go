#include "K60_datatype.h"
    
#define COUNTSADDR   0x4004000C  //(&counttempaddr)
#define COUNTDADDR   0x4004000C  //(&counttempaddr)

U32 count_init[16];         //用来保存16个通道的初始化计数值

void DMA_transmit_init(void *SADDR, void *DADDR,uint32 count,uint8 source)
{
        /* 开启时钟 */
       SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //打开DMA模块时钟
       
       SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //打开DMA多路复用器时钟
       
       DMAMUX_CHCFG1=0;                           //初始化前关闭该通道
       
       DMAMUX_CHCFG1=DMAMUX_CHCFG_SOURCE(source); //DMA通道1对应32号DMA请求，即FTM1 Channel 0 
       
       DMA_TCD1_CITER_ELINKNO=DMA_CITER_ELINKNO_CITER(count);//当前主循环次数,采集 点数 
       DMA_TCD1_BITER_ELINKNO=DMA_BITER_ELINKNO_BITER(count);//起始主循环次数，采集点数 
       
       DMA_TCD1_SADDR  =(u32)SADDR;
      
       DMA_TCD1_DADDR = (u32)DADDR;     
       // 设置目的地址
       
       
       DMA_TCD1_NBYTES_MLNO=DMA_NBYTES_MLNO_NBYTES(1);      //每次读取一字节
       
       DMA_TCD1_SOFF=0;        //每次传送源地址不变
       DMA_TCD1_SLAST=0;       //主循环结束后源地址不变 
       
       DMA_TCD1_DLASTSGA=0;  //主循环结束后即一列的数据采集完毕保持目的地址，自动指向下一行数据
       DMA_TCD1_DOFF=1;      //每次写目的地址加1,需要根据定义的数组类型来定
       
       DMA_TCD1_ATTR=DMA_ATTR_SSIZE(0)|DMA_ATTR_DSIZE(0);//源数据8bit，目的数据8bit 
       
       
       DMA_TCD1_CSR= DMA_CSR_DREQ_MASK;         //DMA通道1主循环结束后停止硬件请求
       
       DMA_TCD1_CSR|=DMA_CSR_INTMAJOR_MASK;    //使能DMA1中断 
       
       DMAMUX_CHCFG1|=DMAMUX_CHCFG_ENBL_MASK; //DMA通道1使能 
       
       DMA_ERQ |= DMA_ERQ_ERQ1_MASK;          //使能通道1的服务请求
       
       //set_irq_priority (63, 0);              //设置中断优先级
       DMA_EN(DMA_CH1);
       
       enable_irq(1);                        //开DMA通道1主循环结束中断  
       
}


/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：DMA_count_Init
*  功能说明：DMA累加计数初始化
*  参数说明：DMA_CHn              通道号（DMA_CH0 ~ DMA_CH15）
*            PTxn                 触发端口
*            count                累加计数中断值
*            DMA_Count_cfg        DMA传输配置
*  函数返回：无
*  修改时间：2012-1-20
*  备    注：
*************************************************************************/
//DMA进行脉冲累加不需要传输数据，只需要利用每次DMA传送之后，CITER自动减一
//减少的数值即为产生的脉冲数目

void DMA_count_Init(DMA_CHn CHn, PTxn ptxn, u32 count, DMA_Count_cfg cfg)
{
    u8 byten = DMA_BYTE1;
    u8 BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //计算传输字节数
    
    if(count > 0x7FFF )
      count = 0x7FFF;
    
    count_init[CHn] = count;

    /* 开启时钟 */
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //打开DMA模块时钟
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //打开DMA多路复用器时钟

    /* 配置 DMA 通道 的 传输控制块 TCD ( Transfer Control Descriptor ) */
    DMA_SADDR(CHn) =    (u32)COUNTSADDR;                    // 设置  源地址
    DMA_DADDR(CHn) =    (u32)COUNTDADDR;                    // 设置目的地址
    DMA_SOFF(CHn)  =    0;                                  // 设置源地址不变
    DMA_DOFF(CHn)  =    0;                                  // 每次传输后，目的地址不变

    DMA_ATTR(CHn)  =    (0
                         | DMA_ATTR_SMOD(0x0)                // 源地址模数禁止  Source address modulo feature is disabled
                         | DMA_ATTR_SSIZE(byten)             // 源数据位宽 ：DMA_BYTEn  。    SSIZE = 0 -> 8-bit ，SSIZE = 1 -> 16-bit ，SSIZE = 2 -> 32-bit ，SSIZE = 4 -> 16-byte
                         | DMA_ATTR_DMOD(0x0)                // 目标地址模数禁止
                         | DMA_ATTR_DSIZE(byten)             // 目标数据位宽 ：DMA_BYTEn  。  设置参考  SSIZE
                        );

    DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(count); //当前主循环次数
    DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKYES_BITER(count);//起始主循环次数

    DMA_CR &= ~DMA_CR_EMLM_MASK;                            // CR[EMLM] = 0

    DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(BYTEs); // 通道每次传输字节数，这里设置为BYTEs个字节。注：值为0表示传输4GB */

    /* 配置 DMA 传输结束后的操作 */
    DMA_SLAST(CHn)      =   -count;                              //调整  源地址的附加值,主循环结束后恢复  源地址
    DMA_DLAST_SGA(CHn)  =   0;                                  //调整目的地址的附加值,主循环结束后恢复目的地址或者保持地址
    DMA_CSR(CHn)        =   (0
                             | DMA_CSR_DREQ_MASK            //主循环结束后停止硬件请求
                             | DMA_CSR_INTMAJOR_MASK        //主循环结束后产生中断
                            );

    /* 配置 DMA 触发源 */
    DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
            | DMAMUX_CHCFG_ENBL_MASK                        /* Enable routing of DMA request */
            | DMAMUX_CHCFG_SOURCE((ptxn >> 5) + DMA_Port_A) /* 通道触发传输源:     */
                                             );

    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << (ptxn>>5));        //开启PORTx端口
    GPIO_PDDR_REG(GPIOx[(ptxn>>5)]) &= ~(1 << (ptxn & 0x1f));//设置端口方向为输入
    PORT_PCR_REG(PORTX[(ptxn>>5)], (ptxn & 0x1F)) = ( 0
            | PORT_PCR_MUX(1)               // 复用GPIO
            | PORT_PCR_IRQC(cfg & 0x03 )    // 确定触发模式
            | ((cfg & 0xc0 ) >> 6)          // 开启上拉或下拉电阻，或者没有
                                                    );
    GPIO_PDDR_REG(GPIOx[(ptxn>>5)]) &= ~(1 << (ptxn && 0x1F));                                                      //输入模式

    /* 开启中断 */
    DMA_EN(CHn);                                    //使能通道CHn 硬件请求
    DMA_IRQ_EN(CHn);                                //允许DMA通道传输
}





U32 DMA_count_get(DMA_CHn CHn)
{
    U32 temp =  count_init[CHn] - DMA_CITER_ELINKNO(CHn);
    return temp;
}



void DMA_count_reset(DMA_CHn CHn)
{
    DMA_CITER_ELINKNO(CHn) = count_init[CHn] ;
}




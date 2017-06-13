#include "K60_datatype.h"
    
#define COUNTSADDR   0x4004000C  //(&counttempaddr)
#define COUNTDADDR   0x4004000C  //(&counttempaddr)

U32 count_init[16];         //��������16��ͨ���ĳ�ʼ������ֵ

void DMA_transmit_init(void *SADDR, void *DADDR,uint32 count,uint8 source)
{
        /* ����ʱ�� */
       SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
       
       SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //��DMA��·������ʱ��
       
       DMAMUX_CHCFG1=0;                           //��ʼ��ǰ�رո�ͨ��
       
       DMAMUX_CHCFG1=DMAMUX_CHCFG_SOURCE(source); //DMAͨ��1��Ӧ32��DMA���󣬼�FTM1 Channel 0 
       
       DMA_TCD1_CITER_ELINKNO=DMA_CITER_ELINKNO_CITER(count);//��ǰ��ѭ������,�ɼ� ���� 
       DMA_TCD1_BITER_ELINKNO=DMA_BITER_ELINKNO_BITER(count);//��ʼ��ѭ���������ɼ����� 
       
       DMA_TCD1_SADDR  =(u32)SADDR;
      
       DMA_TCD1_DADDR = (u32)DADDR;     
       // ����Ŀ�ĵ�ַ
       
       
       DMA_TCD1_NBYTES_MLNO=DMA_NBYTES_MLNO_NBYTES(1);      //ÿ�ζ�ȡһ�ֽ�
       
       DMA_TCD1_SOFF=0;        //ÿ�δ���Դ��ַ����
       DMA_TCD1_SLAST=0;       //��ѭ��������Դ��ַ���� 
       
       DMA_TCD1_DLASTSGA=0;  //��ѭ��������һ�е����ݲɼ���ϱ���Ŀ�ĵ�ַ���Զ�ָ����һ������
       DMA_TCD1_DOFF=1;      //ÿ��дĿ�ĵ�ַ��1,��Ҫ���ݶ����������������
       
       DMA_TCD1_ATTR=DMA_ATTR_SSIZE(0)|DMA_ATTR_DSIZE(0);//Դ����8bit��Ŀ������8bit 
       
       
       DMA_TCD1_CSR= DMA_CSR_DREQ_MASK;         //DMAͨ��1��ѭ��������ֹͣӲ������
       
       DMA_TCD1_CSR|=DMA_CSR_INTMAJOR_MASK;    //ʹ��DMA1�ж� 
       
       DMAMUX_CHCFG1|=DMAMUX_CHCFG_ENBL_MASK; //DMAͨ��1ʹ�� 
       
       DMA_ERQ |= DMA_ERQ_ERQ1_MASK;          //ʹ��ͨ��1�ķ�������
       
       //set_irq_priority (63, 0);              //�����ж����ȼ�
       DMA_EN(DMA_CH1);
       
       enable_irq(1);                        //��DMAͨ��1��ѭ�������ж�  
       
}


/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�DMA_count_Init
*  ����˵����DMA�ۼӼ�����ʼ��
*  ����˵����DMA_CHn              ͨ���ţ�DMA_CH0 ~ DMA_CH15��
*            PTxn                 �����˿�
*            count                �ۼӼ����ж�ֵ
*            DMA_Count_cfg        DMA��������
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
//DMA���������ۼӲ���Ҫ�������ݣ�ֻ��Ҫ����ÿ��DMA����֮��CITER�Զ���һ
//���ٵ���ֵ��Ϊ������������Ŀ

void DMA_count_Init(DMA_CHn CHn, PTxn ptxn, u32 count, DMA_Count_cfg cfg)
{
    u8 byten = DMA_BYTE1;
    u8 BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //���㴫���ֽ���
    
    if(count > 0x7FFF )
      count = 0x7FFF;
    
    count_init[CHn] = count;

    /* ����ʱ�� */
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //��DMA��·������ʱ��

    /* ���� DMA ͨ�� �� ������ƿ� TCD ( Transfer Control Descriptor ) */
    DMA_SADDR(CHn) =    (u32)COUNTSADDR;                    // ����  Դ��ַ
    DMA_DADDR(CHn) =    (u32)COUNTDADDR;                    // ����Ŀ�ĵ�ַ
    DMA_SOFF(CHn)  =    0;                                  // ����Դ��ַ����
    DMA_DOFF(CHn)  =    0;                                  // ÿ�δ����Ŀ�ĵ�ַ����

    DMA_ATTR(CHn)  =    (0
                         | DMA_ATTR_SMOD(0x0)                // Դ��ַģ����ֹ  Source address modulo feature is disabled
                         | DMA_ATTR_SSIZE(byten)             // Դ����λ�� ��DMA_BYTEn  ��    SSIZE = 0 -> 8-bit ��SSIZE = 1 -> 16-bit ��SSIZE = 2 -> 32-bit ��SSIZE = 4 -> 16-byte
                         | DMA_ATTR_DMOD(0x0)                // Ŀ���ַģ����ֹ
                         | DMA_ATTR_DSIZE(byten)             // Ŀ������λ�� ��DMA_BYTEn  ��  ���òο�  SSIZE
                        );

    DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(count); //��ǰ��ѭ������
    DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKYES_BITER(count);//��ʼ��ѭ������

    DMA_CR &= ~DMA_CR_EMLM_MASK;                            // CR[EMLM] = 0

    DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(BYTEs); // ͨ��ÿ�δ����ֽ�������������ΪBYTEs���ֽڡ�ע��ֵΪ0��ʾ����4GB */

    /* ���� DMA ���������Ĳ��� */
    DMA_SLAST(CHn)      =   -count;                              //����  Դ��ַ�ĸ���ֵ,��ѭ��������ָ�  Դ��ַ
    DMA_DLAST_SGA(CHn)  =   0;                                  //����Ŀ�ĵ�ַ�ĸ���ֵ,��ѭ��������ָ�Ŀ�ĵ�ַ���߱��ֵ�ַ
    DMA_CSR(CHn)        =   (0
                             | DMA_CSR_DREQ_MASK            //��ѭ��������ֹͣӲ������
                             | DMA_CSR_INTMAJOR_MASK        //��ѭ������������ж�
                            );

    /* ���� DMA ����Դ */
    DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
            | DMAMUX_CHCFG_ENBL_MASK                        /* Enable routing of DMA request */
            | DMAMUX_CHCFG_SOURCE((ptxn >> 5) + DMA_Port_A) /* ͨ����������Դ:     */
                                             );

    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << (ptxn>>5));        //����PORTx�˿�
    GPIO_PDDR_REG(GPIOx[(ptxn>>5)]) &= ~(1 << (ptxn & 0x1f));//���ö˿ڷ���Ϊ����
    PORT_PCR_REG(PORTX[(ptxn>>5)], (ptxn & 0x1F)) = ( 0
            | PORT_PCR_MUX(1)               // ����GPIO
            | PORT_PCR_IRQC(cfg & 0x03 )    // ȷ������ģʽ
            | ((cfg & 0xc0 ) >> 6)          // �����������������裬����û��
                                                    );
    GPIO_PDDR_REG(GPIOx[(ptxn>>5)]) &= ~(1 << (ptxn && 0x1F));                                                      //����ģʽ

    /* �����ж� */
    DMA_EN(CHn);                                    //ʹ��ͨ��CHn Ӳ������
    DMA_IRQ_EN(CHn);                                //����DMAͨ������
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




#include "K60_datatype.h"
#include "flash.h"


/***FUNC+*********************************************************************/
/* Name   : Flash_init                                                       */
/* Descrp : ��ʼ��flashģ��                                                  */
/* Input  : None.                                                            */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
void Flash_init(void)
{
    //���FMC������
    Flash_sign_off();
    
    // ��ֹ���Ź�
    WDOG_UNLOCK = 0xC520;
    WDOG_UNLOCK = 0xD928;
    WDOG_STCTRLH = 0;    // ��ֹ���Ź�
    
    // �ȴ��������
    while(!(FTFL_FSTAT & CCIF));
    
    // ������ʳ����־λ
    FTFL_FSTAT = ACCERR | FPVIOL;
}

/***FUNC+*********************************************************************/
/* Name   : Flash_erase_sector                                               */
/* Descrp : ɾ��FLASH����                                                    */
/* Input  : sectorNo�������ţ�K60N512ʵ��ʹ��0~255��.                        */

/*512K,��Ϊ256��������ÿ������2K

Output : 0=��������0=�쳣��.                                              */
/* Return : 0=��������0=�쳣��..                                             */   
/***FUNC-*********************************************************************/

U8 Flash_erase_sector(U16 sectorNo)
{
    union
    {
        U32  word;
        U8   byte1[4];
    } dest;
    
    dest.word    = (U32)(sectorNo*(1<<11));

    // ���ò�������
    FTFL_FCCOB0 = ERSSCR; // ������������
    
    // ����Ŀ���ַ
    FTFL_FCCOB1 = dest.byte1[2];
    FTFL_FCCOB2 = dest.byte1[1];
    FTFL_FCCOB3 = dest.byte1[0];
    
    // ִ����������
    if(1 == Flash_cmd_launch())    //��ִ��������ִ���
        return 1;     //�����������
   
    // ������sector0ʱ��������豸
    if(dest.word <= 0x800)
    {
        // д��4�ֽ�
        FTFL_FCCOB0 = PGM4; 
        // ����Ŀ���ַ
        FTFL_FCCOB1 = 0x00;
        FTFL_FCCOB2 = 0x04;
        FTFL_FCCOB3 = 0x0C;
        // ����
        FTFL_FCCOB4 = 0xFF;
        FTFL_FCCOB5 = 0xFF;
        FTFL_FCCOB6 = 0xFF;
        FTFL_FCCOB7 = 0xFE;
        // ִ����������
        if(1 == Flash_cmd_launch())  //��ִ��������ִ���
            return 2;   //�����������
    }  
    
    return 0;  //�ɹ�����
}

/***FUNC+*********************************************************************/
/* Name   : Flash_read                                                       */
/* Descrp : flash��ȡ����                                                    */
/* Input  : sectNo��Ŀ�������� ��K60N512ʵ��ʹ��0~255��                      */
/*          offset:��ȡ�����ڲ�ƫ�Ƶ�ַ��0~2043��                            */
/*          cnt����ȡ�ֽ���Ŀ��0~2043��                                      */
/*          buf��Դ���ݻ������׵�ַ                                          */
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/

U8 Flash_readBUF(U16 sectNo,U16 offset,U16 cnt,U8*bBuf)
{
    U32 wAddr = 0;
    wAddr = sectNo * 2048 + offset;
    while (cnt--)
   {
     *bBuf++=*(UCHAR *)wAddr++;
   }
   return TRUE;
}

/***FUNC+*********************************************************************/
/* Name   : Flash_write                                                      */

/* Descrp : flashд����� */

/* Input  : sectNo��Ŀ�������� ��K60N512ʵ��ʹ��0~255��                      */
/*          offset:д�������ڲ�ƫ�Ƶ�ַ��0~2043��                            */
/*          cnt��д���ֽ���Ŀ��0~2043��                                      */
/*          buf��Դ���ݻ������׵�ַ                                          */

/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
U8 Flash_writeBUF(U16 sectNo,U16 offset,U16 cnt,U8 buf[])
{
    U32 size;
    U32 destaddr;
    
    union
    {
        U32   word;
        U8  byte2[4];
    } dest;
    
    if(offset%4 != 0)
        return 1;   //�����趨����ƫ����δ���루4�ֽڶ��룩
    
    // ����д������
    FTFL_FCCOB0 = PGM4;
    destaddr = (U32)(sectNo*(1<<11) + offset);//�����ַ
    dest.word = destaddr;
    for(size=0; size<cnt; size+=4, dest.word+=4, buf+=4)
    {
        // ����Ŀ���ַ
        FTFL_FCCOB1 = dest.byte2[2];
        FTFL_FCCOB2 = dest.byte2[1];
        FTFL_FCCOB3 = dest.byte2[0];
 
        // ��������
        FTFL_FCCOB4 = buf[3];
        FTFL_FCCOB5 = buf[2];
        FTFL_FCCOB6 = buf[1];
        FTFL_FCCOB7 = buf[0];
        
        if(1 == Flash_cmd_launch()) 
            return 2;  //д���������
    }
    
    return 0;  //�ɹ�ִ��
}

U8 Flash_writeDATA16(U16 sectNo,U16 offset,U16 DATA)
{
    U32 destaddr;  
    union
    {
        U32   word;
        U8  byte3[4];
    } dest;
    union
    {
        U32   Data;
        U8  data[2];
    } dest1;	
     if(offset%4 != 0)
        return 1;   //�����趨����ƫ����δ���루4�ֽڶ��룩//�˴���ʾ���棬���ǰ�ȫ�ġ���
    // ����д������
    destaddr = (U32)(sectNo*(1<<11) + offset);//�����ַ
    dest.word = destaddr;
    dest1.Data = DATA;
        // ����Ŀ���ַ
        FTFL_FCCOB0 = PGM4;
        FTFL_FCCOB1 = dest.byte3[2];
        FTFL_FCCOB2 = dest.byte3[1];
        FTFL_FCCOB3 = dest.byte3[0];
 
        // ��������
        {    //FTFL_FCCOB4 =dest1.data[3];
            // FTFL_FCCOB5 =dest1.data[2];
             FTFL_FCCOB6 =dest1.data[1];
             FTFL_FCCOB7 =dest1.data[0];
        
        if(1 == Flash_cmd_launch()) 
            return 2;  //д���������
        }
    return 0;  //�ɹ�ִ��
}
U8 Flash_writeDATA8(U16 sectNo,U16 offset,U8 DATA)
{
    U32 destaddr;  
    union
    {
        U32   word;
        U8  byte4[4];
    } dest;
    union
    {
        U32   Data;
        U8  data[1];
    } dest1;	
     if(offset%4 != 0)
        return 1;   //�����趨����ƫ����δ���루4�ֽڶ��룩//�˴���ʾ���棬���ǰ�ȫ�ġ���
    // ����д������
    destaddr = (U32)(sectNo*(1<<11) + offset);//�����ַ
    dest.word = destaddr;
    dest1.Data = DATA;
        // ����Ŀ���ַ
        FTFL_FCCOB0 = PGM4;
        FTFL_FCCOB1 = dest.byte4[2];
        FTFL_FCCOB2 = dest.byte4[1];
        FTFL_FCCOB3 = dest.byte4[0];
 
        // ��������
        {    //FTFL_FCCOB4 =dest1.data[3];
            // FTFL_FCCOB5 =dest1.data[2];
             FTFL_FCCOB7 =dest1.data[0];
        
        if(1 == Flash_cmd_launch()) 
            return 2;  //д���������
        }
    return 0;  //�ɹ�ִ��
}

/***FUNC+*********************************************************************/
/* Name   : Flash_sign_off                                                   */
/* Descrp : flashд�����                                                    */
/* Input  : ����Flash�洢�����������FlashԤ��ȡ����                         */
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
void Flash_sign_off(void)
{  
    // �������
    FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
    FMC_PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;
}

/***FUNC+*********************************************************************/
/* Name   : Flash_cmd_launch                                                 */
/* Descrp : ����Flash����                                                    */
/* Input  : ����Flash�洢�����������FlashԤ��ȡ����                         */
/* Output : 0-�ɹ� 1-ʧ��.                                                   */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
U32 Flash_cmd_launch(void)
{
    // ������ʴ����־λ�ͷǷ����ʱ�־λ
    FTFL_FSTAT = ACCERR | FPVIOL;
    
    // ��������
    FTFL_FSTAT = CCIF;

    // �ȴ��������
    while(!(FTFL_FSTAT & CCIF));

    // �������־
    if(FTFL_FSTAT & (ACCERR | FPVIOL | MGSTAT0))
        return 1 ; //ִ���������
  
    return 0; //ִ������ɹ�
}

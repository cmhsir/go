#include "K60_datatype.h"
#include "flash.h"


/***FUNC+*********************************************************************/
/* Name   : Flash_init                                                       */
/* Descrp : 初始化flash模块                                                  */
/* Input  : None.                                                            */   
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
void Flash_init(void)
{
    //清除FMC缓冲区
    Flash_sign_off();
    
    // 禁止看门狗
    WDOG_UNLOCK = 0xC520;
    WDOG_UNLOCK = 0xD928;
    WDOG_STCTRLH = 0;    // 禁止看门狗
    
    // 等待命令完成
    while(!(FTFL_FSTAT & CCIF));
    
    // 清除访问出错标志位
    FTFL_FSTAT = ACCERR | FPVIOL;
}

/***FUNC+*********************************************************************/
/* Name   : Flash_erase_sector                                               */
/* Descrp : 删除FLASH扇区                                                    */
/* Input  : sectorNo：扇区号（K60N512实际使用0~255）.                        */

/*512K,分为256个扇区，每个扇区2K

Output : 0=正常；非0=异常。.                                              */
/* Return : 0=正常；非0=异常。..                                             */   
/***FUNC-*********************************************************************/

U8 Flash_erase_sector(U16 sectorNo)
{
    union
    {
        U32  word;
        U8   byte1[4];
    } dest;
    
    dest.word    = (U32)(sectorNo*(1<<11));

    // 设置擦除命令
    FTFL_FCCOB0 = ERSSCR; // 擦除扇区命令
    
    // 设置目标地址
    FTFL_FCCOB1 = dest.byte1[2];
    FTFL_FCCOB2 = dest.byte1[1];
    FTFL_FCCOB3 = dest.byte1[0];
    
    // 执行命令序列
    if(1 == Flash_cmd_launch())    //若执行命令出现错误
        return 1;     //擦除命令错误
   
    // 若擦除sector0时，则解锁设备
    if(dest.word <= 0x800)
    {
        // 写入4字节
        FTFL_FCCOB0 = PGM4; 
        // 设置目标地址
        FTFL_FCCOB1 = 0x00;
        FTFL_FCCOB2 = 0x04;
        FTFL_FCCOB3 = 0x0C;
        // 数据
        FTFL_FCCOB4 = 0xFF;
        FTFL_FCCOB5 = 0xFF;
        FTFL_FCCOB6 = 0xFF;
        FTFL_FCCOB7 = 0xFE;
        // 执行命令序列
        if(1 == Flash_cmd_launch())  //若执行命令出现错误
            return 2;   //解锁命令错误
    }  
    
    return 0;  //成功返回
}

/***FUNC+*********************************************************************/
/* Name   : Flash_read                                                       */
/* Descrp : flash读取操作                                                    */
/* Input  : sectNo：目标扇区号 （K60N512实际使用0~255）                      */
/*          offset:读取扇区内部偏移地址（0~2043）                            */
/*          cnt：读取字节数目（0~2043）                                      */
/*          buf：源数据缓冲区首地址                                          */
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

/* Descrp : flash写入操作 */

/* Input  : sectNo：目标扇区号 （K60N512实际使用0~255）                      */
/*          offset:写入扇区内部偏移地址（0~2043）                            */
/*          cnt：写入字节数目（0~2043）                                      */
/*          buf：源数据缓冲区首地址                                          */

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
        return 1;   //参数设定错误，偏移量未对齐（4字节对齐）
    
    // 设置写入命令
    FTFL_FCCOB0 = PGM4;
    destaddr = (U32)(sectNo*(1<<11) + offset);//计算地址
    dest.word = destaddr;
    for(size=0; size<cnt; size+=4, dest.word+=4, buf+=4)
    {
        // 设置目标地址
        FTFL_FCCOB1 = dest.byte2[2];
        FTFL_FCCOB2 = dest.byte2[1];
        FTFL_FCCOB3 = dest.byte2[0];
 
        // 拷贝数据
        FTFL_FCCOB4 = buf[3];
        FTFL_FCCOB5 = buf[2];
        FTFL_FCCOB6 = buf[1];
        FTFL_FCCOB7 = buf[0];
        
        if(1 == Flash_cmd_launch()) 
            return 2;  //写入命令错误
    }
    
    return 0;  //成功执行
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
        return 1;   //参数设定错误，偏移量未对齐（4字节对齐）//此处提示警告，但是安全的……
    // 设置写入命令
    destaddr = (U32)(sectNo*(1<<11) + offset);//计算地址
    dest.word = destaddr;
    dest1.Data = DATA;
        // 设置目标地址
        FTFL_FCCOB0 = PGM4;
        FTFL_FCCOB1 = dest.byte3[2];
        FTFL_FCCOB2 = dest.byte3[1];
        FTFL_FCCOB3 = dest.byte3[0];
 
        // 拷贝数据
        {    //FTFL_FCCOB4 =dest1.data[3];
            // FTFL_FCCOB5 =dest1.data[2];
             FTFL_FCCOB6 =dest1.data[1];
             FTFL_FCCOB7 =dest1.data[0];
        
        if(1 == Flash_cmd_launch()) 
            return 2;  //写入命令错误
        }
    return 0;  //成功执行
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
        return 1;   //参数设定错误，偏移量未对齐（4字节对齐）//此处提示警告，但是安全的……
    // 设置写入命令
    destaddr = (U32)(sectNo*(1<<11) + offset);//计算地址
    dest.word = destaddr;
    dest1.Data = DATA;
        // 设置目标地址
        FTFL_FCCOB0 = PGM4;
        FTFL_FCCOB1 = dest.byte4[2];
        FTFL_FCCOB2 = dest.byte4[1];
        FTFL_FCCOB3 = dest.byte4[0];
 
        // 拷贝数据
        {    //FTFL_FCCOB4 =dest1.data[3];
            // FTFL_FCCOB5 =dest1.data[2];
             FTFL_FCCOB7 =dest1.data[0];
        
        if(1 == Flash_cmd_launch()) 
            return 2;  //写入命令错误
        }
    return 0;  //成功执行
}

/***FUNC+*********************************************************************/
/* Name   : Flash_sign_off                                                   */
/* Descrp : flash写入操作                                                    */
/* Input  : 配置Flash存储控制器，清除Flash预读取缓冲                         */
/* Output : None.                                                            */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
void Flash_sign_off(void)
{  
    // 清除缓冲
    FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
    FMC_PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;
}

/***FUNC+*********************************************************************/
/* Name   : Flash_cmd_launch                                                 */
/* Descrp : 启动Flash命令                                                    */
/* Input  : 配置Flash存储控制器，清除Flash预读取缓冲                         */
/* Output : 0-成功 1-失败.                                                   */
/* Return : None.                                                            */   
/***FUNC-*********************************************************************/
U32 Flash_cmd_launch(void)
{
    // 清除访问错误标志位和非法访问标志位
    FTFL_FSTAT = ACCERR | FPVIOL;
    
    // 启动命令
    FTFL_FSTAT = CCIF;

    // 等待命令结束
    while(!(FTFL_FSTAT & CCIF));

    // 检查错误标志
    if(FTFL_FSTAT & (ACCERR | FPVIOL | MGSTAT0))
        return 1 ; //执行命令出错
  
    return 0; //执行命令成功
}

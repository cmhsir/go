/***FUNC+*********************************************************************/
/* Name   : Flash_init                                                       */
/***MODU+********************************************************************/
/* Copyright (c) 2012.04  WH, All Rights Reserved.                          */
/*  WebSite     : http://un-el.taobao.com/                                  */
/*  QQȺ        : 226846867 (Kinetis ARM)                                   */
/*  Email       : dragonhzw@163.com                                         */
/*  FileName    : Flash.h                                                   */
/*  Description : The Flash module                                          */
/*  History     :                                                           */                                                       
/*     [Author]   [Date]      [Version]    [Description]                    */              
/*     [1] dragonhzw   2012/04/09  Ver 1.0.0    Initial file.               */
/*                                                                          */
/*  Built with IAR Embedded Workbench for ARM 6.30                          */
/***MODU-********************************************************************/
#ifndef __K60_FLASH_H__
#define __K60_FLASH_H__

/***DEF+**********************************************************************/
/* Flash�������궨�� ���ڲ�ʹ��                                              */
/***DEF-**********************************************************************/ 
#define CCIF    (1<<7)
#define ACCERR  (1<<5)
#define FPVIOL  (1<<4)
#define MGSTAT0 (1<<0)

/***DEF+**********************************************************************/
/* Flash����궨�壬�ڲ�ʹ��                                                 */
/***DEF-**********************************************************************/
#define RD1BLK    0x00   // ������Flash
#define RD1SEC    0x01   // ����������
#define PGMCHK    0x02   // д����
#define RDRSRC    0x03   // ��Ŀ������
#define PGM4      0x06   // д�볤��
#define ERSBLK    0x08   // ��������Flash
#define ERSSCR    0x09   // ����Flash����
#define PGMSEC    0x0B   // д������
#define RD1ALL    0x40   // �����еĿ�
#define RDONCE    0x41   // ֻ��һ��
#define PGMONCE   0x43   // ֻдһ��
#define ERSALL    0x44   // �������п�
#define VFYKEY    0x45   // ��֤���ŷ���Կ��
#define PGMPART   0x80   // д�����
#define SETRAM    0x81   // �趨FlexRAM����
#define	flash_readDATA(sectorNo,offset,type)		(*(type *)((U32)(((sectorNo)<<11) + (offset))))	
/*****************************************************************************/
/*                         Function Declare                                  */
/*****************************************************************************/
void Flash_init(void);
U8   Flash_erase_sector(U16 sectorNo);

void Flash_sign_off(void);
U32 Flash_cmd_launch(void);

U8 Flash_readBUF(U16 sectNo,U16 offset,U16 cnt,U8*bBuf);
U8 Flash_writeBUF(U16 sectNo,U16 offset,U16 cnt,U8 buf[]);

U8 Flash_writeDATA16(U16 sectNo,U16 offset,U16 DATA);
U8 Flash_writeDATA8(U16 sectNo,U16 offset,U8 DATA);
/*****************************************************************************/
/*                         Function Declare                                  */
/*****************************************************************************/
#endif /* __K60_FLASH_H__ */
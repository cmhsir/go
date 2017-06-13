#ifndef _LOC_EYE_H_
#define _LOC_EYE_H_

uint8 OTSU_threshold(uint8 *pic,uint16 num);
void LCD_PrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum);
void gaussianFilter(uint8 * data,int width,int height);//¸ßË¹Í¼ÏñÂË²¨
void image();
void Frame_Difference();
void LocatingEye_OriginalImage_OtsuThreshold_OledPrint();
void LocatingEye_OriginalImage_FixedThreshold_OledPrint();
void LocatingEye_DifferenceImage_FixThreshold_OledPrint();
void DemokToolPrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum);

#endif
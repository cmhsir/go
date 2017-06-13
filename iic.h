#ifndef _iic_H_
#define _iic_H_


#define OUT_X_L        0x28
#define OUT_X_H        0x29
#define OUT_Y_L        0x2A
#define OUT_Y_H        0x2B
#define OUT_Z_L        0x2C
#define OUT_Z_H        0x2D

extern void InitL3G4200D();
extern void INIT_IIC();
extern void Single_WriteL3G4200D(uchar REG_Address,uchar REG_data);
extern uchar Single_ReadL3G4200D(uchar REG_Address);


#endif


#ifndef _COMMON_H_
#define _COMMON_H_



int sign(int x);// 求符号
int fsign(float x);// 求符号
int add(int x,int y);//死区
float fadd(float x,float y);//死区
int ade(int x,int y);       //限幅
float fade(float x,float y);       //限幅
int nec(int x,int a,int b);//死区加限幅
float fnec(float x,float a,float b);//死区加限幅
int cyc(int a,int b);//周期
int max3(int a, int b, int c);
int min3(int a, int b, int c);
float fmax2(float a, float b);
float fmin2(float a, float b);
float absf(float x);
int min( int a, int b);
unsigned int my_sqrt(unsigned int x);
void Delay_MS(uint32 ms);
void bubble_sort(uint8 a[], uint8 n) ;       

#endif
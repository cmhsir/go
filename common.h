#ifndef _COMMON_H_
#define _COMMON_H_



int sign(int x);// �����
int fsign(float x);// �����
int add(int x,int y);//����
float fadd(float x,float y);//����
int ade(int x,int y);       //�޷�
float fade(float x,float y);       //�޷�
int nec(int x,int a,int b);//�������޷�
float fnec(float x,float a,float b);//�������޷�
int cyc(int a,int b);//����
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
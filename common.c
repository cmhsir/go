#include "K60_datatype.h"


int sign(int x){if(x>0)return 1;else if(x<0)return -1;else return 0;}// �����
int fsign(float x){if(x>0)return 1;else if(x<0)return -1;else return 0;}// �����
int add(int x,int y){if(-y<x&&x<y)return 0;else if(x>0)return x-y;else return x+y;}//����
float fadd(float x,float y){if(-y<x&&x<y)return 0;else if(x>0)return x-y;else return x+y;}//����
int ade(int x,int y){if(x<-y)return -y;else if(x>y)return y;else return x;}        //�޷�
float fade(float x,float y){if(x<-y)return -y;else if(x>y)return y;else return x;}        //�޷�
int nec(int x,int a,int b){if(x<a)return 0;else if(x>b)return b-a;else return x-a;}//�������޷�
float fnec(float x,float a,float b){if(x<a)return 0;else if(x>b)return b-a;else return x-a;}//�������޷�
int cyc(int a,int b){while(a<0)a+=b;while(a>=b)a-=b;return a;}//����
int max3(int a, int b, int c){if(a>b)if(a>c)return a;else return c;else if(b>c)return b;else return c;}
int min3(int a, int b, int c){if(a<b)if(a<c)return a;else return c;else if(b<c)return b;else return c;}
float fmax2(float a, float b){if(a>b)return a;else return b;}
float fmin2(float a, float b){if(a<b)return a;else return b;}


/**********************С������ʼ*****************************/
float absf(float x)
{
    if(x>=0.0) return x;
    else  return -x;
}

int min( int a, int b)
{
    if(a>b) return b;
    else  return a;
}


//�������
unsigned int my_sqrt(unsigned int x)     
{
  unsigned char ans=0,p=0x80;
  while(p!=0)
  {
    ans+=p;
    if(ans*ans>x)
    {
      ans-=p;
    }
    p=(unsigned char)(p/2);
  }
  return(ans);
}


// ��ʱ����
void Delay_MS(uint32 ms)
{
   while(ms--);
}

//ð������
void bubble_sort(uint8 a[], uint8 n)        
{
  for(uint8 i =0 ; i< n-1; ++i) 
  {
    for(uint8 j = 0; j < n-i-1; ++j) 
    {
      if(a[j] > a[j+1]) 
      {
        uint8 tmp = a[j] ; 
        a[j] = a[j+1] ;  
        a[j+1] = tmp;  
      }
    } 
  }  
}
<<<<<<< HEAD
#include "K60_datatype.h"

u8 Image_Sort_History[2][ROW][COL]={0};     // ͼ������
u8 Image_Difference[2][ROW][COL]={0};       // ֡������
//extern u8 Image_Difference_Result[ROW][COL];

int Area = 0, X_axis = 0, Y_axis = 0;
u16 Target_Count=0;
u16 Found_Count,Lost_Count;
u8 Frame_Threshold=60;//֡����ֵ
u16 threshold=140;//ͼ���ֵ����ֵ

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  ����˵����������λ����OLED��ʾԭʼͼ�񣬷ָ���ֵʹ�ô���㷨
*            ���㷨��������ʾ�ʹ�������׵�˫��������
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_OledPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);  //����㷨��ȡ��̬��ֵ

  for(i=0;i<ROW;i++)
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;    // С����ֵ����ɫ������OLED��ʾ��0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;   // ������ֵ����ɫ������OLED��ʾ��1
      }
    }   

    LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED��ʾͼ��
}

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_OriginalImage_FixedThreshold_OledPrint
*  ����˵����������λ����OLED��ʾԭʼͼ�񣬷ָ���ֵʹ��ʹ�ù̶���ֵ
*            ���㷨��������ʾ�ʹ����ű�ԽҰ���ű�
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_OriginalImage_FixedThreshold_OledPrint()
{
  u16 i,j;
  
  threshold= 240;      // �̶���ֵ�ָ�
  
  Area = 0;//�������Чֵ
  X_axis = 0;
  Y_axis = 0;
  
  for(i=0;i<ROW;i++)  
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;          // С����ֵ����ɫ������OLED��ʾ��0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;          // ������ֵ���ű꣬OLED��ʾ��1
        Area++;                                 //�����С
        X_axis += j;                            //x������
        Y_axis += i;                            //y������
<<<<<<< HEAD
=======
      }
    }
  
  X_axis = X_axis / Area;                       //ȡx����һ֡��������ĵ� 
  Y_axis = Y_axis / Area;                       //ȡy����һ֡��������ĵ�

    //LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED��ʾͼ��
}


/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_DifferenceImage_FixThreshold_OledPrint
*  ����˵����������λ����OLED��ʾ���ͼ�񣬷ָ���ֵʹ��ʹ�ù̶���ֵ
*            
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_DifferenceImage_FixThreshold_OledPrint()
{
    u16 i=0,j=0;

   for(i=0;i<ROW;i++)//ͼ����Ƹ�ֵ
   {
      for(j=0;j<COL;j++)
      {
        Image_Difference[0][i][j]=abs(Image_Sort_History[0][i][j]-Image_Sort_History[1][i][j]);
        //Image_Sort_History[2][i][j]=Image_Sort_History[1][i][j];
        Image_Sort_History[1][i][j]=Image_Sort_History[0][i][j];
        
        //Image_Difference[1][i][j]=Image_Difference[0][i][j];
        
      }
   }
   
   Frame_Threshold = OTSU_threshold((uint8 *)Image_Difference[0],ROW*COL);//��̬��ֵ
   Frame_Threshold = 40;
   
   for(i=0;i<ROW;i++)//3֡���ݵ���
    for(j=0;j<COL;j++) 
    {
      if(Image_Difference[0][i][j]<Frame_Threshold)
      {
        Image_Difference[1][i][j]=0;//����֡��С����ֵ����0
      }     
      else 
      {
        Image_Difference[1][i][j]=1;//����֡��С����ֵ����0
      }
    }   

    LCD_PrintImage((uint8 *)Image_Difference[1],ROW,COL);
         
}


/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  ����˵����������λ����ͼ����λ����ʾԭʼͼ�񣬷ָ���ֵʹ�ô���㷨
*            ���㷨��������ʾ�ʹ�������׵�˫��������
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_DemokToolPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);//��̬��ֵ
  for(i=0;i<ROW;i++)//3֡���ݵ���
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0x00;//����֡��С����ֵ����0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=0xFE;//����֡��С����ֵ����0
      }
    }   
  
  
  Uart_SendByte(UART5,0xFF);//ͼ��ͷ   
  for(i=0;i<ROW;i++)//3֡���ݵ���
    for(j=0;j<COL;j++) 
    {
      Uart_SendByte(UART5,Image_Sort_History[0][i][j]);
    }
  

    //DemokToolPrintImage((uint8 *)Image_Sort_History[0],ROW,COL);
}

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�OTSU_threshold
*  ����˵�����������㷨 ��̬��ֵ
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
#define Gourd 256
uint8 OTSU_threshold(uint8 *pic,uint16 num)
{
   uint16 i=0;
   uint16 Histogram[Gourd];
   for (i=0;i<Gourd;i++)Histogram[i]=0;//��������

   for (i=0;i<num;i++)
   {
       Histogram[(int)pic[i]*Gourd/256]++;
   }

  float pt[Gourd],w[Gourd],u[Gourd],o[Gourd],Ut;

  pt[0]=(float)Histogram[0]/num;
  w[0]=pt[0];
  u[0]=w[0];

  for(i=1;i<Gourd;i++)
  {
    pt[i]=(float)Histogram[i]/num;
    w[i]=w[i-1]+pt[i];
    u[i]=u[i-1]+i*pt[i];
  };
  Ut=u[Gourd-1];

  for(i=0;i<Gourd;i++)
  {
    o[i]=(1-pt[i])*(u[i]*u[i]/w[i]+(u[i]-Ut)*(u[i]-Ut)/(1-w[i]));
  };

  int maxi=0;
  float maxo=0;

  for(i=0;i<Gourd;i++)
  {
    if(o[i]!=0x7FC0000)
    if(o[i]>maxo){maxo=o[i];maxi=i;}

  }
  return maxi*256/Gourd;
}


/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LCD_PrintImage
*  ����˵����Һ����ʾͼ��
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LCD_PrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum)
{
  uint8 ucData;
  uint32 i,j,k;
  uint32 usRowTmp;
  for(i = 0; i <8; i++) //��������ɨ��
  {
    LED_Set_Pos(0,i);
    usRowTmp =i*8;    //���㵱ǰ�����е��±�
    for(j =0; j <128; j++) //��ɨ��
    {
      ucData = 0;
      for(k = 0; k < 8; k++) //��i���ж���8��ɨ��
      {
        ucData = ucData >> 1;
        //if((pucTable+(usRowNum-((usRowTmp + k)*usRowNum)/64)*usColumnNum)[(j*usColumnNum)/128]<230)
        if((pucTable+(usRowNum-((usRowTmp + k)*usRowNum)/64)*usColumnNum)[(j*usColumnNum)/128]==1)   
        {
          ucData = ucData|0x80;
        }
       }
      LED_WrDat(ucData);
    }
  }
}

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�gaussianFilter
*  ����˵������˹�˲��㷨
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void gaussianFilter(uint8 * data,int width,int height)//��˹ͼ���˲�
{
    int i, j, index, sum;
    int templates[9] = { 1, 2, 1,
                         2, 4, 2,
                         1, 2, 1 };
    sum = height*width*sizeof(uint8);
    uint8 *tmpdata=(uint8*)malloc(sum);
    memcpy((char*)tmpdata,(char*)data,sum);
    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width - 1;j++)
        {
            index = sum = 0;
            for(int m = i - 1;m < i + 2;m++)
            {
                for(int n = j - 1; n < j + 2;n++)
                {
                    sum +=
                        tmpdata[m * width + n] *
                        templates[index++];
                }
            }
            data[i * width + j] = sum / 16;
        }
    }
    free(tmpdata);
}


=======
#include "K60_datatype.h"

u8 Image_Sort_History[2][ROW][COL]={0};     // ͼ������
u8 Image_Difference[2][ROW][COL]={0};       // ֡������
//extern u8 Image_Difference_Result[ROW][COL];

int Area = 0, X_axis = 0, Y_axis = 0;
u16 Target_Count=0;
u16 Found_Count,Lost_Count;
u8 Frame_Threshold=60;//֡����ֵ
u16 threshold=140;//ͼ���ֵ����ֵ

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  ����˵����������λ����OLED��ʾԭʼͼ�񣬷ָ���ֵʹ�ô���㷨
*            ���㷨��������ʾ�ʹ�������׵�˫��������
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_OledPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);  //����㷨��ȡ��̬��ֵ

  for(i=0;i<ROW;i++)
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;    // С����ֵ����ɫ������OLED��ʾ��0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;   // ������ֵ����ɫ������OLED��ʾ��1
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
      }
    }
  
  X_axis = X_axis / Area;                       //ȡx����һ֡��������ĵ� 
  Y_axis = Y_axis / Area;                       //ȡy����һ֡��������ĵ�

    //LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED��ʾͼ��
}

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_OriginalImage_FixedThreshold_OledPrint
*  ����˵����������λ����OLED��ʾԭʼͼ�񣬷ָ���ֵʹ��ʹ�ù̶���ֵ
*            ���㷨��������ʾ�ʹ����ű�ԽҰ���ű�
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_OriginalImage_FixedThreshold_OledPrint()
{
  u16 i,j;
  
  threshold= 240;      // �̶���ֵ�ָ�
  
  Area = 0;//�������Чֵ
  X_axis = 0;
  Y_axis = 0;
  
  for(i=0;i<ROW;i++)  
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;          // С����ֵ����ɫ������OLED��ʾ��0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;          // ������ֵ���ű꣬OLED��ʾ��1
        Area++;                                 //�����С
        X_axis += j;                            //x������
        Y_axis += i;                            //y������
      }
    }
  
  X_axis = X_axis / Area;                       //ȡx����һ֡��������ĵ� 
  Y_axis = Y_axis / Area;                       //ȡy����һ֡��������ĵ�

    //LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED��ʾͼ��
}


/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_DifferenceImage_FixThreshold_OledPrint
*  ����˵����������λ����OLED��ʾ���ͼ�񣬷ָ���ֵʹ��ʹ�ù̶���ֵ
*            
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_DifferenceImage_FixThreshold_OledPrint()
{
    u16 i=0,j=0;

   for(i=0;i<ROW;i++)//ͼ����Ƹ�ֵ
   {
      for(j=0;j<COL;j++)
      {
        Image_Difference[0][i][j]=abs(Image_Sort_History[0][i][j]-Image_Sort_History[1][i][j]);
        //Image_Sort_History[2][i][j]=Image_Sort_History[1][i][j];
        Image_Sort_History[1][i][j]=Image_Sort_History[0][i][j];
        
        //Image_Difference[1][i][j]=Image_Difference[0][i][j];
        
      }
   }
   
   Frame_Threshold = OTSU_threshold((uint8 *)Image_Difference[0],ROW*COL);//��̬��ֵ
   Frame_Threshold = 40;
   
   for(i=0;i<ROW;i++)//3֡���ݵ���
    for(j=0;j<COL;j++) 
    {
      if(Image_Difference[0][i][j]<Frame_Threshold)
      {
        Image_Difference[1][i][j]=0;//����֡��С����ֵ����0
      }     
      else 
      {
        Image_Difference[1][i][j]=1;//����֡��С����ֵ����0
      }
    }   

    LCD_PrintImage((uint8 *)Image_Difference[1],ROW,COL);
         
}


/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  ����˵����������λ����ͼ����λ����ʾԭʼͼ�񣬷ָ���ֵʹ�ô���㷨
*            ���㷨��������ʾ�ʹ�������׵�˫��������
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_DemokToolPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);//��̬��ֵ
  for(i=0;i<ROW;i++)//3֡���ݵ���
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0x00;//����֡��С����ֵ����0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=0xFE;//����֡��С����ֵ����0
      }
    }   
  
  
  Uart_SendByte(UART5,0xFF);//ͼ��ͷ   
  for(i=0;i<ROW;i++)//3֡���ݵ���
    for(j=0;j<COL;j++) 
    {
      Uart_SendByte(UART5,Image_Sort_History[0][i][j]);
    }
  

    //DemokToolPrintImage((uint8 *)Image_Sort_History[0],ROW,COL);
}

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�OTSU_threshold
*  ����˵�����������㷨 ��̬��ֵ
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
#define Gourd 256
uint8 OTSU_threshold(uint8 *pic,uint16 num)
{
   uint16 i=0;
   uint16 Histogram[Gourd];
   for (i=0;i<Gourd;i++)Histogram[i]=0;//��������

   for (i=0;i<num;i++)
   {
       Histogram[(int)pic[i]*Gourd/256]++;
   }

  float pt[Gourd],w[Gourd],u[Gourd],o[Gourd],Ut;

  pt[0]=(float)Histogram[0]/num;
  w[0]=pt[0];
  u[0]=w[0];

  for(i=1;i<Gourd;i++)
  {
    pt[i]=(float)Histogram[i]/num;
    w[i]=w[i-1]+pt[i];
    u[i]=u[i-1]+i*pt[i];
  };
  Ut=u[Gourd-1];

  for(i=0;i<Gourd;i++)
  {
    o[i]=(1-pt[i])*(u[i]*u[i]/w[i]+(u[i]-Ut)*(u[i]-Ut)/(1-w[i]));
  };

  int maxi=0;
  float maxo=0;

  for(i=0;i<Gourd;i++)
  {
    if(o[i]!=0x7FC0000)
    if(o[i]>maxo){maxo=o[i];maxi=i;}

  }
  return maxi*256/Gourd;
}


/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�LCD_PrintImage
*  ����˵����Һ����ʾͼ��
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void LCD_PrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum)
{
  uint8 ucData;
  uint32 i,j,k;
  uint32 usRowTmp;
  for(i = 0; i <8; i++) //��������ɨ��
  {
    LED_Set_Pos(0,i);
    usRowTmp =i*8;    //���㵱ǰ�����е��±�
    for(j =0; j <128; j++) //��ɨ��
    {
      ucData = 0;
      for(k = 0; k < 8; k++) //��i���ж���8��ɨ��
      {
        ucData = ucData >> 1;
        //if((pucTable+(usRowNum-((usRowTmp + k)*usRowNum)/64)*usColumnNum)[(j*usColumnNum)/128]<230)
        if((pucTable+(usRowNum-((usRowTmp + k)*usRowNum)/64)*usColumnNum)[(j*usColumnNum)/128]==1)   
        {
          ucData = ucData|0x80;
        }
       }
      LED_WrDat(ucData);
    }
  }
}

/*************************************************************************
*                      ��֮��DEMOK ��λ������ͷ����С��
*
*  �������ƣ�gaussianFilter
*  ����˵������˹�˲��㷨
*  �޸�ʱ�䣺2015-12-06
*  ��    ע��
*************************************************************************/
void gaussianFilter(uint8 * data,int width,int height)//��˹ͼ���˲�
{
    int i, j, index, sum;
    int templates[9] = { 1, 2, 1,
                         2, 4, 2,
                         1, 2, 1 };
    sum = height*width*sizeof(uint8);
    uint8 *tmpdata=(uint8*)malloc(sum);
    memcpy((char*)tmpdata,(char*)data,sum);
    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width - 1;j++)
        {
            index = sum = 0;
            for(int m = i - 1;m < i + 2;m++)
            {
                for(int n = j - 1; n < j + 2;n++)
                {
                    sum +=
                        tmpdata[m * width + n] *
                        templates[index++];
                }
            }
            data[i * width + j] = sum / 16;
        }
    }
    free(tmpdata);
}


>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99

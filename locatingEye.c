<<<<<<< HEAD
#include "K60_datatype.h"

u8 Image_Sort_History[2][ROW][COL]={0};     // 图像数组
u8 Image_Difference[2][ROW][COL]={0};       // 帧差数组
//extern u8 Image_Difference_Result[ROW][COL];

int Area = 0, X_axis = 0, Y_axis = 0;
u16 Target_Count=0;
u16 Found_Count,Lost_Count;
u8 Frame_Threshold=60;//帧间阈值
u16 threshold=140;//图像二值化阈值

/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  功能说明：驱动定位眼在OLED显示原始图像，分割阈值使用大津算法
*            此算法适用于显示和处理常规组白底双黑线赛道
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_OledPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);  //大津算法获取动态阈值

  for(i=0;i<ROW;i++)
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;    // 小于阈值，深色背景，OLED显示置0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;   // 大于阈值，白色赛道，OLED显示置1
      }
    }   

    LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED显示图像
}

/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_OriginalImage_FixedThreshold_OledPrint
*  功能说明：驱动定位眼在OLED显示原始图像，分割阈值使用使用固定阈值
*            此算法适用于显示和处理信标越野组信标
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_OriginalImage_FixedThreshold_OledPrint()
{
  u16 i,j;
  
  threshold= 240;      // 固定阈值分割
  
  Area = 0;//面积的有效值
  X_axis = 0;
  Y_axis = 0;
  
  for(i=0;i<ROW;i++)  
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;          // 小于阈值，深色背景，OLED显示置0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;          // 大于阈值，信标，OLED显示置1
        Area++;                                 //面积大小
        X_axis += j;                            //x轴坐标
        Y_axis += i;                            //y轴坐标
<<<<<<< HEAD
=======
      }
    }
  
  X_axis = X_axis / Area;                       //取x轴在一帧画面的中心点 
  Y_axis = Y_axis / Area;                       //取y轴在一帧画面的中心点

    //LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED显示图像
}


/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_DifferenceImage_FixThreshold_OledPrint
*  功能说明：驱动定位眼在OLED显示差分图像，分割阈值使用使用固定阈值
*            
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_DifferenceImage_FixThreshold_OledPrint()
{
    u16 i=0,j=0;

   for(i=0;i<ROW;i++)//图像递推赋值
   {
      for(j=0;j<COL;j++)
      {
        Image_Difference[0][i][j]=abs(Image_Sort_History[0][i][j]-Image_Sort_History[1][i][j]);
        //Image_Sort_History[2][i][j]=Image_Sort_History[1][i][j];
        Image_Sort_History[1][i][j]=Image_Sort_History[0][i][j];
        
        //Image_Difference[1][i][j]=Image_Difference[0][i][j];
        
      }
   }
   
   Frame_Threshold = OTSU_threshold((uint8 *)Image_Difference[0],ROW*COL);//动态阈值
   Frame_Threshold = 40;
   
   for(i=0;i<ROW;i++)//3帧数据递推
    for(j=0;j<COL;j++) 
    {
      if(Image_Difference[0][i][j]<Frame_Threshold)
      {
        Image_Difference[1][i][j]=0;//两点帧差小于阈值，置0
      }     
      else 
      {
        Image_Difference[1][i][j]=1;//两点帧差小于阈值，置0
      }
    }   

    LCD_PrintImage((uint8 *)Image_Difference[1],ROW,COL);
         
}


/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  功能说明：驱动定位眼在图像上位机显示原始图像，分割阈值使用大津算法
*            此算法适用于显示和处理常规组白底双黑线赛道
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_DemokToolPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);//动态阈值
  for(i=0;i<ROW;i++)//3帧数据递推
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0x00;//两点帧差小于阈值，置0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=0xFE;//两点帧差小于阈值，置0
      }
    }   
  
  
  Uart_SendByte(UART5,0xFF);//图像头   
  for(i=0;i<ROW;i++)//3帧数据递推
    for(j=0;j<COL;j++) 
    {
      Uart_SendByte(UART5,Image_Sort_History[0][i][j]);
    }
  

    //DemokToolPrintImage((uint8 *)Image_Sort_History[0],ROW,COL);
}

/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：OTSU_threshold
*  功能说明：经典大津算法 动态阈值
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
#define Gourd 256
uint8 OTSU_threshold(uint8 *pic,uint16 num)
{
   uint16 i=0;
   uint16 Histogram[Gourd];
   for (i=0;i<Gourd;i++)Histogram[i]=0;//数组清零

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
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LCD_PrintImage
*  功能说明：液晶显示图像
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LCD_PrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum)
{
  uint8 ucData;
  uint32 i,j,k;
  uint32 usRowTmp;
  for(i = 0; i <8; i++) //完整组行扫描
  {
    LED_Set_Pos(0,i);
    usRowTmp =i*8;    //计算当前所在行的下标
    for(j =0; j <128; j++) //列扫描
    {
      ucData = 0;
      for(k = 0; k < 8; k++) //在i组中对这8行扫描
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
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：gaussianFilter
*  功能说明：高斯滤波算法
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void gaussianFilter(uint8 * data,int width,int height)//高斯图像滤波
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

u8 Image_Sort_History[2][ROW][COL]={0};     // 图像数组
u8 Image_Difference[2][ROW][COL]={0};       // 帧差数组
//extern u8 Image_Difference_Result[ROW][COL];

int Area = 0, X_axis = 0, Y_axis = 0;
u16 Target_Count=0;
u16 Found_Count,Lost_Count;
u8 Frame_Threshold=60;//帧间阈值
u16 threshold=140;//图像二值化阈值

/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  功能说明：驱动定位眼在OLED显示原始图像，分割阈值使用大津算法
*            此算法适用于显示和处理常规组白底双黑线赛道
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_OledPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);  //大津算法获取动态阈值

  for(i=0;i<ROW;i++)
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;    // 小于阈值，深色背景，OLED显示置0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;   // 大于阈值，白色赛道，OLED显示置1
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
      }
    }
  
  X_axis = X_axis / Area;                       //取x轴在一帧画面的中心点 
  Y_axis = Y_axis / Area;                       //取y轴在一帧画面的中心点

    //LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED显示图像
}

/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_OriginalImage_FixedThreshold_OledPrint
*  功能说明：驱动定位眼在OLED显示原始图像，分割阈值使用使用固定阈值
*            此算法适用于显示和处理信标越野组信标
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_OriginalImage_FixedThreshold_OledPrint()
{
  u16 i,j;
  
  threshold= 240;      // 固定阈值分割
  
  Area = 0;//面积的有效值
  X_axis = 0;
  Y_axis = 0;
  
  for(i=0;i<ROW;i++)  
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0;          // 小于阈值，深色背景，OLED显示置0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=1;          // 大于阈值，信标，OLED显示置1
        Area++;                                 //面积大小
        X_axis += j;                            //x轴坐标
        Y_axis += i;                            //y轴坐标
      }
    }
  
  X_axis = X_axis / Area;                       //取x轴在一帧画面的中心点 
  Y_axis = Y_axis / Area;                       //取y轴在一帧画面的中心点

    //LCD_PrintImage((uint8 *)Image_Sort_History[1],ROW,COL);  //OLED显示图像
}


/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_DifferenceImage_FixThreshold_OledPrint
*  功能说明：驱动定位眼在OLED显示差分图像，分割阈值使用使用固定阈值
*            
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_DifferenceImage_FixThreshold_OledPrint()
{
    u16 i=0,j=0;

   for(i=0;i<ROW;i++)//图像递推赋值
   {
      for(j=0;j<COL;j++)
      {
        Image_Difference[0][i][j]=abs(Image_Sort_History[0][i][j]-Image_Sort_History[1][i][j]);
        //Image_Sort_History[2][i][j]=Image_Sort_History[1][i][j];
        Image_Sort_History[1][i][j]=Image_Sort_History[0][i][j];
        
        //Image_Difference[1][i][j]=Image_Difference[0][i][j];
        
      }
   }
   
   Frame_Threshold = OTSU_threshold((uint8 *)Image_Difference[0],ROW*COL);//动态阈值
   Frame_Threshold = 40;
   
   for(i=0;i<ROW;i++)//3帧数据递推
    for(j=0;j<COL;j++) 
    {
      if(Image_Difference[0][i][j]<Frame_Threshold)
      {
        Image_Difference[1][i][j]=0;//两点帧差小于阈值，置0
      }     
      else 
      {
        Image_Difference[1][i][j]=1;//两点帧差小于阈值，置0
      }
    }   

    LCD_PrintImage((uint8 *)Image_Difference[1],ROW,COL);
         
}


/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LocatingEye_OriginalImage_OtsuThreshold_OledPrint
*  功能说明：驱动定位眼在图像上位机显示原始图像，分割阈值使用大津算法
*            此算法适用于显示和处理常规组白底双黑线赛道
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LocatingEye_OriginalImage_OtsuThreshold_DemokToolPrint()
{
  u16 i,j;
  threshold=OTSU_threshold((uint8 *)Image_Sort_History[0],ROW*COL);//动态阈值
  for(i=0;i<ROW;i++)//3帧数据递推
    for(j=0;j<COL;j++) 
    {
      if(Image_Sort_History[0][i][j]<threshold)
      {
        Image_Sort_History[1][i][j]=0x00;//两点帧差小于阈值，置0
      }     
      else 
      {
        Image_Sort_History[1][i][j]=0xFE;//两点帧差小于阈值，置0
      }
    }   
  
  
  Uart_SendByte(UART5,0xFF);//图像头   
  for(i=0;i<ROW;i++)//3帧数据递推
    for(j=0;j<COL;j++) 
    {
      Uart_SendByte(UART5,Image_Sort_History[0][i][j]);
    }
  

    //DemokToolPrintImage((uint8 *)Image_Sort_History[0],ROW,COL);
}

/*************************************************************************
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：OTSU_threshold
*  功能说明：经典大津算法 动态阈值
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
#define Gourd 256
uint8 OTSU_threshold(uint8 *pic,uint16 num)
{
   uint16 i=0;
   uint16 Histogram[Gourd];
   for (i=0;i<Gourd;i++)Histogram[i]=0;//数组清零

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
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：LCD_PrintImage
*  功能说明：液晶显示图像
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void LCD_PrintImage(uint8 *pucTable, uint16 usRowNum, uint16 usColumnNum)
{
  uint8 ucData;
  uint32 i,j,k;
  uint32 usRowTmp;
  for(i = 0; i <8; i++) //完整组行扫描
  {
    LED_Set_Pos(0,i);
    usRowTmp =i*8;    //计算当前所在行的下标
    for(j =0; j <128; j++) //列扫描
    {
      ucData = 0;
      for(k = 0; k < 8; k++) //在i组中对这8行扫描
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
*                      极之队DEMOK 定位眼摄像头开发小组
*
*  函数名称：gaussianFilter
*  功能说明：高斯滤波算法
*  修改时间：2015-12-06
*  备    注：
*************************************************************************/
void gaussianFilter(uint8 * data,int width,int height)//高斯图像滤波
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

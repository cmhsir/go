<<<<<<< HEAD
#include "K60_datatype.h"
/**************************************************************************************************
*                        K60              定位眼
*                      VCC(5V/3V3)        VCC(5V)
*                      PTD[0:7]           Y[0:7]
*                      PTC18              PCLK
*                      PTC17              HREF
*                      PTC16              VSYN
*                      GND                GND
*              K60与串口模块接线方式：
*                      PTE24接RX    PTE25接TX   默认使用K60的串口4 
*             上位机设置：波特率115200   
*                         行数列数根据拨码开关的状态对照以下真值表在K60_datatype.h中修改ROW和COL
*                                        拨码开关真值表
*                             拨码开关状态        分辨率（列数*行数）
*                                  11                320*240
*                                  10                160*120
*                                  01                100*80
*                                  10                80*60
*  实验操作：打开摄像头上位机，设定行数和列数的值和K60_datatype.h文件中的宏定义一致
*            波特率为115200，开始接收图像
****************************************************************************************************/
extern  u8  Image_Sort_History[3][ROW][COL];
extern  u32   time;
extern  int Area, X_axis, Y_axis;//在摄像头取的

//char Pix_Data[ROW][COL]={0};
char Is_SendPhoto=0;
int  V_Cnt=0, timer0count = 0, timer1count = 0, FPS = 0, showFPS = 0, count = 0, xb_lose = 0;
<<<<<<< HEAD
int  speedset = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, speedave = 0, dirave[2][3] = {0}, dir[3][10] = {0}, dirturn = 0, direrr[4] = {0}, record[2][12] = {0};
int  setfps = 0, ok = 0, stop = 0, key[8] = {0}, arrive = 0, speedcount[8] = {0}, start = 0, dircentral = 0;
float Areave = 0, dirindex = 0, speedinit = 0, recordave[4] = {0}, avevalue = 0, value = 0;


=======
<<<<<<< HEAD
int  speedset = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, speedave = 0, dirave[2][3] = {0}, dir[3][10] = {0}, dirturn = 0, direrr[4] = {0}, record[11] = {0};
int  setfps = 0, ok = 0, stop = 0, key[8] = {0}, arrive = 0, speedcount = 0;
float Areave = 0, dirindex = 0, speedinit = 0, recordave[4] = {0};

=======
<<<<<<< HEAD
int  speedset = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, speedave = 0, dirave[2][3] = {0}, dir[3][10] = {0}, dirturn = 0, direrr[4] = {0}, record[11] = {0};
int  setfps = 0, ok = 0, stop = 0, key[8] = {0}, arrive = 0, speedcount = 0;
float Areave = 0, dirindex = 0, speedinit = 0, recordave[4] = {0};

=======
int  speedinit = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, speedave = 0, dirave[2][3] = {0}, dir[3][10] = {0}, dirturn = 0, direrr[4] = {0}, record[11] = {0}, recordave[3] = {0};
int  setfps = 0, ok = 0, stop = 0, key[8] = {0};
float Areave = 0, dirindex = 0;


>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
//DIRPID调节函数
struct 
{  
    float setdir;  
    float actualdir;  
    float err;  
    float lasterr; 
    float sumerr;
    float kp,ki,kd;  
    float controldir; 
}dirpid;  
void DIRPID(float dir) 
{  
    dirpid.setdir=dir;          //期望值
    dirpid.actualdir=0.0;       //实际值
    dirpid.err=0.0;             //误差
    dirpid.lasterr=0.0;         //最近一次误差
    dirpid.sumerr=0.0;          //误差总和
    dirpid.controldir=0.0;      //输出的控制值
<<<<<<< HEAD
    dirpid.kp=0.25;              //P参数
    dirpid.ki=0.0;              //I参数
    dirpid.kd=0.6;              //D参数,速度越大，参数越小
}  
float dirpidturn(float dir) 
{ 
=======
    dirpid.kp=0.5;              //P参数
    dirpid.ki=0.0;              //I参数
    dirpid.kd=0.25;              //D参数
}  
float dirpidturn(float dir) 
{ 
    dirpid.actualdir=dir;  
    dirpid.err=dirpid.setdir - dirpid.actualdir;
    dirpid.sumerr+=dirpid.err;
    dirpid.controldir=dirpid.kp*dirpid.err+dirpid.ki*dirpid.sumerr+dirpid.kd*(dirpid.err-dirpid.lasterr);  
    dirpid.lasterr=dirpid.err;
    return dirpid.controldir; 
}  

//SPEEDPID调节函数
struct 
{  
    float setspeed;  
    float actualspeed;  
    float err;  
    float lasterr;  
    float kp,ki,kd;  
    float controlspeed;  
    float sumerr; 
}speedpid;  
void SPEEDPID() 
{  
    speedpid.setspeed=0.0;  
    speedpid.actualspeed=0.0;  
    speedpid.err=0.0;  
    speedpid.lasterr=0.0;  
    speedpid.controlspeed=0.0;  
    speedpid.sumerr=0.0;  
    speedpid.kp=0.5;  
    speedpid.ki=0.05;  
    speedpid.kd=0.0; 
}  
float speedpidturn(float setspeed, float inspeed) 
{  
    speedpid.setspeed=setspeed;
    speedpid.actualspeed=inspeed;
    speedpid.err=speedpid.setspeed - speedpid.actualspeed;
    speedpid.sumerr+=speedpid.err;
    speedpid.controlspeed=speedpid.kp*speedpid.err+speedpid.ki*speedpid.sumerr+speedpid.kd*(speedpid.err-speedpid.lasterr);  
    speedpid.lasterr=speedpid.err;  
    return speedpid.controlspeed; 
}  

void bt_go(void);       //蓝牙控制车跑
void Camera(void);      //采集摄像头的数据
void Cameraview(void);  //上位机显示摄像头图片
void position(void);    //算法识别信标的位置
void pidcontrol(void);  //pid控制
void lcdshow(void);     //显示数据

float speedms(float ms)  //输出控制车ms米每秒
{
    float outms;
    outms = ms*68/43*500/200/0.2*1.37;//车轮的齿轮和编码器的齿轮比例为68/43，编码器一圈500个脉冲，每5ms采集一次脉冲，则200次为1秒，0.2m为小车轮子周长
    return outms;               //求每5ms多少个脉冲，1.37为实际测量误差比例
}

void all_init(void)     //总初始化
{
    BSP_init();
    
    //初始化定时器
    Timer_Init(1,5);    //同时初始化定时器0、1，定时器0为1ms触发，定时器1为5ms触发
    EnableTimer0();     //开启定时器1
    EnableTimer1();     //开启定时器2
    
    DIRPID(50);         //初始化方向pid，同时设定期望中间值为50
    
    SPEEDPID();         //初始化速度pid
    speedinit = (int)speedms(2);     //初始速度
}
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f

//DIRPID调节函数
struct 
{  
    float setdir;  
    float actualdir;  
    float err;  
    float lasterr; 
    float sumerr;
    float kp,ki,kd;  
    float controldir; 
}dirpid;  
void DIRPID(float dir) 
{  
    dirpid.setdir=dir;          //期望值
    dirpid.actualdir=0.0;       //实际值
    dirpid.err=0.0;             //误差
    dirpid.lasterr=0.0;         //最近一次误差
    dirpid.sumerr=0.0;          //误差总和
    dirpid.controldir=0.0;      //输出的控制值
    dirpid.kp=0.5;              //P参数
    dirpid.ki=0.0;              //I参数
    dirpid.kd=0.25;              //D参数
}  
float dirpidturn(float dir) 
{ 
<<<<<<< HEAD
=======
    
    all_init();
    
    while(1)
    {
      
        if(stop == 0)
            switch(timer0count)
            {
                case 0: 
                        if(ok == 0)Camera();
                        break;
                case 1:
                        if(ok == 1)position();
                        break;
                case 2:
                        if(ok == 2)pidcontrol();
                        break;
                case 3:
                        lcdshow();
                        break;
                case 4:
                        ok = 0;
                        break;
                
            }
        else
        {
          
//            if(stop >= 2)//重启系统
//            {
//                DisableInterrupts;
//                all_init();
//                stop = 0;
//            }
                
            PWM_Output(PWM_PIN_PTA10,680);
            PWM_Output(PWM_PIN_PTA6,80);PWM_Output(PWM_PIN_PTA7,0);//右轮
            PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,80);//左轮
        }
        
        
        //LED_P6x8Str(5,1,"abc");
        //bt_go();//蓝牙控制车跑
     }
}

void Camera(void)
{
    if(Is_SendPhoto)
    { 
        DisableInterrupts;
        //Cameraview();//上位机显示摄像头图片
        LocatingEye_OriginalImage_FixedThreshold_OledPrint();//信标检测方式
        
        FPS++;
        
        ok = 1;
        
        EnableInterrupts;   
    }

}

void position(void)             //算法识别信标的位置
{
    u16 i, z, numb;
    
    numb = 0;
    
    while(numb < 9)//保存最近十帧画面数据
    {
        dir[0][numb] = dir[0][numb+1];      //x轴坐标
        dir[1][numb] = dir[1][numb+1];      //y轴坐标
        dir[2][numb] = dir[2][numb+1];      //面积大小
        numb++;
    }
    
    dir[0][numb] = X_axis;      //x轴坐标
    dir[1][numb] = Y_axis;      //y轴坐标
    dir[2][numb] = Area;        //面积大小
    
  
    if(dir[0][numb] != 0)//记录丢失信标前的十帧数据
    {
      
        z = 0;
        while(z < 9)
        {
            record[z] = record[z+1];
            z++;
        }
        record[9] = dir[0][numb];
        count++;
        if(count == 6)
            record[10] = dir[2][numb];
      
    }
    else
    {
        if(record[9] >= 60)//确认信标丢失
        {
            xb_lose = 1;
        }
        else
            xb_lose = 0;
        count = 0;
    }
    
    setfps = 3;//需要求的平均的最近帧数，最小为1，最大为10
    
    Areave = 0;
    dirave[0][0] = 0;
    dirave[1][0] = 0;
    
    for(i = 0; i < setfps; i++)
    {
        Areave += dir[2][9-i];
        dirave[0][0] += dir[0][9-i];
        dirave[1][0] += dir[1][9-i];
//        if(numb >= 1)
//            direrr[numb] = dir[0][numb] - dir[0][numb-1];
    }
    dirave[0][0] = dirave[0][0]/setfps;
    dirave[1][0] = dirave[1][0]/setfps;
    Areave = Areave/setfps;//取三帧数据，求面积平均值
    
    ok = 2;
}

void pidcontrol(void)//pid控制小车的舵机和速度
{
  
//    direrr[2] = (direrr[1]*direrr[1]/direrr[0] + dirave)*1.2;
//    direrr[3] = (int)realizepid((float)direrr[2]);
//    direrr[2] = direrr[3] + dirave[0][0];
//    
//    if(dirave[0][0] >= 0 && dirave[0][0] <= 120)//定位信标控制方向
//        dirturn = 760 - dirave[0][0];
//    else
//        if(dirave[0][0] > 120)
//            dirturn = 620;
//        else
//            dirturn = 740;
    
/***************************************************
                    控制方向算法
***************************************************/
  
    if(Areave <= 10 && Areave > 0)//根据小车与信标的距离计算合适的转向倍数
        dirindex = Areave / 25;
    else
        if((Areave <= 60 && Areave > 10))
            dirindex = Areave / (25 + (Areave - 10) / 2);
        else
            dirindex = Areave / (50 + (Areave - 60) / 3);
    
    if(dirindex >= 1.6)//最大倍数为1.6，大了舵机可能会超出范围
        dirindex = 1.6;
  
    if(xb_lose == 1)//信标丢失
    {
        if(record[9] != 0)
            dirturn = (int)(680 + dirpidturn((float)record[9]) * 1.6);
    }
    else
    {
        if(dirave[0][0] != 0)
            dirturn = (int)(680 + dirpidturn((float)dirave[0][0]) * dirindex);//定位信标控制方向
    }
    speedinit = (int)speedms(2);
    if(Areave >= 250 || dir[1][9] >= 60)//到达信标
    {  
        if(dirave[0][0] <= 50)
        {
            dirturn = 610; //右
        }
        else
        {
            dirturn = 750; //左
        }
        speedinit = (int)speedms(1);
    }
    if(Areave == 0)
        if(xb_lose == 0)
        {
            dirturn = 750; //左
        }
        else
        {
            if(record[9] <= 100)
                record[9]++;
            if(record[9] >= 100)
                dirturn = 610;
        }
    
    //防止溢出
    if(dirturn >= 750)
        dirturn = 750;
    if(dirturn <= 610)
        dirturn = 610;
       
/***************************************************
                    控制速度算法
***************************************************/
    
   
    
    if(record[10] <= 0)//加速跑
    {
        if(Areave <= 200 && Areave > 50)//接近信标
        {
            outspeedz = (int)(speedinit + ((200 - Areave) - record[10]) * 0.5);//控制小车减速度
            outspeedy = (int)(speedinit + ((200 - Areave) - record[10]) * 0.5);
        }
        
        if(Areave <= 50 && Areave > 0)//距离信标远
        {
            outspeedz = (int)(speedinit + (Areave - record[10]) * 1.6);//控制小车加速度
            outspeedy = (int)(speedinit + (Areave - record[10]) * 1.6);
        }
    }
    else//匀速跑
    {
        outspeedz = speedinit;
        outspeedy = speedinit; 
    }
    
    

    outspeedz = (int)speedpidturn(speedinit,(float)inspeedz);
    outspeedy = (int)speedpidturn(speedinit,(float)inspeedy);
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
    PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,outspeedy);//右轮
    PWM_Output(PWM_PIN_PTA9,outspeedz);PWM_Output(PWM_PIN_PTA8,0);//左轮
    
    ok = 3;
    
}

void lcdshow()
{
    LED_PrintValueI(0,0,dirave[0][0]);//x轴坐标
    LED_PrintValueI(0,2,dirturn);//方向
    LED_PrintValueI(0,4,(int)Areave);
    LED_PrintValueI(0,6,inspeedz);
    LED_PrintValueI(64,6,record[9]);
        
    if(showFPS)//显示摄像头的帧数，右上角
    {
        LED_P6x8Char(116,0,showFPS / 10 + 48);
        LED_P6x8Char(122,0,showFPS % 10 + 48);
    }
    
//    LED_PrintValueI(0,0,record[2]);
//    LED_PrintValueI(0,2,record[3]);
//    LED_PrintValueI(0,4,record[4]);
//    LED_PrintValueI(0,6,record[5]);
//    LED_PrintValueI(64,0,record[6]);
//    LED_PrintValueI(64,2,record[7]);
//    LED_PrintValueI(64,4,record[8]);
//    LED_PrintValueI(64,6,record[9]);
}
                    
void Cameraview(void)//上位机显示摄像头图片
{
    int  m=0,n=0;
    //发送一帧数据
    Uart_SendByte(UART4,0xFF);//图像头   
    for(m=0; m<ROW; m++)
    {
        for(n=0;n<COL ;n++)
        {
           if(Pix_Data[m][n] == 0xFF) 
              Pix_Data[m][n]--;
           Uart_SendByte(UART4,Pix_Data[m][n]);
        }
    }
}

void bt_go(void)//蓝牙控制车跑
{
    int i = 0;//有问题
    u8 temp;
    //Uart_SendByte(UART4,Uart_Getch(UART4));  //测试串口
    temp = Uart_Getch(UART4);//蓝牙遥控，程序会死在这里，接收到数据才执行
    Uart_SendByte(UART4,temp);
    temp -= 48;
    switch(temp)
    {
        case 0: PWM_Output(PWM_PIN_PTA10,695);//中
            break;
        case 1: PWM_Output(PWM_PIN_PTA10,760);//左
            break;
        case 2: PWM_Output(PWM_PIN_PTA10,630);//右
            break;
        case 3: 
            if(i <= 250)//加速
            {
                if(i < 250)
                    i += 10;
                else
                    i = 250;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
        case 4: 
            if(i >= 0)//减速
            {
                if(i >= 50)
                    i -= 10;
                else
                    i = 0;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
         case 5: //停止
              i = 0;
              PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
    }
}
//PIT中断服务函数
void Timer0_isr()
{
    
    if(timer0count > 5)
    {
        timer0count = 0;
      
/***************************************************
                    获取左右轮转速
***************************************************/
        
        inspeedz = DMA_count_get(DMA_CH3);
        inspeedy = DMA_count_get(DMA_CH2);
        DMA_count_reset(DMA_CH2);
        DMA_count_reset(DMA_CH3);
      
    }
    else
        timer0count++;


    Cleartimer0();
}
//PIT中断服务函数
void Timer1_isr()
{
  
    timer1count++;
    if(timer1count == 200)
    {
        if(abs(inspeedz - inspeedy) >= 30 || inspeedz < 5 || inspeedy < 5)
             stop++;
        else
             stop = 0;
        showFPS = FPS;
        FPS = 0;
        timer1count = 0;
    }
    else 
        showFPS = 0;
    if(timer1count == 100)
    {
        key[0] = Gpio_get(PORT_A, 19);
        key[1] = Gpio_get(PORT_A, 17);
        key[2] = Gpio_get(PORT_A, 16);
        key[3] = Gpio_get(PORT_A, 15);
        key[4] = Gpio_get(PORT_A, 14);
        key[5] = Gpio_get(PORT_A, 13);
        key[6] = Gpio_get(PORT_A, 12);
        key[7] = Gpio_get(PORT_A, 11);
    }
  
    Cleartimer1();
}




=======
#include "K60_datatype.h"
/**************************************************************************************************
*                        K60              定位眼
*                      VCC(5V/3V3)        VCC(5V)
*                      PTD[0:7]           Y[0:7]
*                      PTC18              PCLK
*                      PTC17              HREF
*                      PTC16              VSYN
*                      GND                GND
*              K60与串口模块接线方式：
*                      PTE24接RX    PTE25接TX   默认使用K60的串口4 
*             上位机设置：波特率115200   
*                         行数列数根据拨码开关的状态对照以下真值表在K60_datatype.h中修改ROW和COL
*                                        拨码开关真值表
*                             拨码开关状态        分辨率（列数*行数）
*                                  11                320*240
*                                  10                160*120
*                                  01                100*80
*                                  10                80*60
*  实验操作：打开摄像头上位机，设定行数和列数的值和K60_datatype.h文件中的宏定义一致
*            波特率为115200，开始接收图像
****************************************************************************************************/
extern  u8  Image_Sort_History[3][ROW][COL];
extern  u32   time;
extern  int Area, X_axis, Y_axis;//在摄像头取的

//char Pix_Data[ROW][COL]={0};
char Is_SendPhoto=0;
int  V_Cnt=0, timer0count = 0, timer1count = 0, FPS = 0, showFPS = 0, count = 0, xb_lose = 0;
int  speedinit = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, numb = 0, speedave = 0, dirave[2][3] = {0}, dir[2][3] = {0}, dirturn = 0, direrr[4] = {0}, record[11] = {0}, recordave[3] = {0};
int  setfps = 0;
float Areave = 0, dirindex = 0;


//DIRPID调节函数
struct 
{  
    float setdir;  
    float actualdir;  
    float err;  
    float lasterr;  
    float kp,kd;  
    float controldir; 
}dirpid;  
void DIRPID(float dir) 
{  
    dirpid.setdir=dir;          //期望值
    dirpid.actualdir=0.0;       //实际值
    dirpid.err=0.0;             //误差
    dirpid.lasterr=0.0;         //最近一次误差
    dirpid.controldir=0.0;      //输出的控制值
    dirpid.kp=1.0;              //P参数
    dirpid.kd=0.1;              //D参数
}  
float dirpidturn(float dir) 
{ 
    dirpid.actualdir=dir;  
    dirpid.err=dirpid.setdir - dirpid.actualdir;
    dirpid.controldir=dirpid.kp*dirpid.err+dirpid.kd*(dirpid.err-dirpid.lasterr);  
    dirpid.lasterr=dirpid.err;
    return dirpid.controldir; 
}  

//SPEEDPID调节函数
struct 
{  
    float setspeed;  
    float actualspeed;  
    float err;  
    float lasterr;  
    float kp,ki,kd;  
    float controlspeed;  
    float sumerr; 
}speedpid;  
void SPEEDPID() 
{  
    speedpid.setspeed=0.0;  
    speedpid.actualspeed=0.0;  
    speedpid.err=0.0;  
    speedpid.lasterr=0.0;  
    speedpid.controlspeed=0.0;  
    speedpid.sumerr=0.0;  
    speedpid.kp=0.2;  
    speedpid.ki=0.015;  
    speedpid.kd=0.2; 
}  
float speedpidturn(float speed, float Areave) 
{  
    float index = 0;
    speedpid.setspeed=speed;
    speedpid.actualspeed=(250 - Areave) / 2;
    speedpid.err=speedpid.actualspeed - speedpid.setspeed;
//    if(abs((int)speedpid.err)>200)           //变积分过程
//    {
//        index=0.0;
//    }
//    else 
//        if(abs((int)speedpid.err)<180)
//        {
//            index=1.0;
//            pid.sumerr+=speedpid.err;
//        }else
//        {
//            index=(200-abs((int)speedpid.err))/20;
//            speedpid.sumerr+=speedpid.err;
//        } 
    speedpid.sumerr+=speedpid.err;
    speedpid.controlspeed=speedpid.kp*speedpid.err+index*speedpid.ki*speedpid.sumerr+speedpid.kd*(speedpid.err-speedpid.lasterr);  
    speedpid.lasterr=speedpid.err;  
    return speedpid.controlspeed; 
}  

void bt_go(void);       //蓝牙控制车跑
void Camera(void);      //采集摄像头的数据
void Cameraview(void);  //上位机显示摄像头图片
void position(void);    //算法识别信标的位置
void pidcontrol(void);  //pid控制
void lcdshow(void);     //显示数据
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64

//DIRPID调节函数
struct 
{  
    float setdir;  
    float actualdir;  
    float err;  
    float lasterr; 
    float sumerr;
    float kp,ki,kd;  
    float controldir; 
}dirpid;  
void DIRPID(float dir) 
{  
    dirpid.setdir=dir;          //期望值
    dirpid.actualdir=0.0;       //实际值
    dirpid.err=0.0;             //误差
    dirpid.lasterr=0.0;         //最近一次误差
    dirpid.sumerr=0.0;          //误差总和
    dirpid.controldir=0.0;      //输出的控制值
    dirpid.kp=0.5;              //P参数
    dirpid.ki=0.0;              //I参数
    dirpid.kd=0.25;              //D参数
}  
float dirpidturn(float dir) 
{ 
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    dirpid.actualdir=dir;  
    dirpid.err=dirpid.setdir - dirpid.actualdir;
    dirpid.sumerr+=dirpid.err;
    dirpid.controldir=dirpid.kp*dirpid.err+dirpid.ki*dirpid.sumerr+dirpid.kd*(dirpid.err-dirpid.lasterr);  
    dirpid.lasterr=dirpid.err;
    return dirpid.controldir; 
}  

//SPEEDPID调节函数
struct 
{  
<<<<<<< HEAD
    float setspeedz, setspeedy;  
    float actualspeedz, actualspeedy;  
    float errz, erry;  
    float lasterrz, lasterry;  
    float kp,ki,kd;  
    float controlspeedz, controlspeedy;  
    float sumerrz, sumerry; 
}speedpid;  
void SPEEDPID() 
{  
    speedpid.setspeedz=0.0;  
    speedpid.actualspeedz=0.0;  
    speedpid.errz=0.0;  
    speedpid.lasterrz=0.0;  
    speedpid.controlspeedz=0.0;  
    speedpid.sumerrz=0.0;
    speedpid.setspeedy=0.0;  
    speedpid.actualspeedy=0.0;  
    speedpid.erry=0.0;  
    speedpid.lasterry=0.0;  
    speedpid.controlspeedy=0.0;
    speedpid.sumerry=0.0;
=======
    float setspeed;  
    float actualspeed;  
    float err;  
    float lasterr;  
    float kp,ki,kd;  
    float controlspeed;  
    float sumerr; 
}speedpid;  
void SPEEDPID() 
{  
    speedpid.setspeed=0.0;  
    speedpid.actualspeed=0.0;  
    speedpid.err=0.0;  
    speedpid.lasterr=0.0;  
    speedpid.controlspeed=0.0;  
    speedpid.sumerr=0.0;  
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    speedpid.kp=0.5;  
    speedpid.ki=0.05;  
    speedpid.kd=0.0; 
}  
<<<<<<< HEAD
float speedpidturn(float setspeedz, float inspeedz,float setspeedy, float inspeedy) 
{  
    speedpid.setspeedz=setspeedz;
    speedpid.actualspeedz=inspeedz;
    speedpid.errz=speedpid.setspeedz - speedpid.actualspeedz;
    speedpid.sumerrz+=speedpid.errz;
    speedpid.controlspeedz=speedpid.kp*speedpid.errz+speedpid.ki*speedpid.sumerrz+speedpid.kd*(speedpid.errz-speedpid.lasterrz);  
    speedpid.lasterrz=speedpid.errz;
    speedpid.setspeedy=setspeedy;
    speedpid.actualspeedy=inspeedy;
    speedpid.erry=speedpid.setspeedy - speedpid.actualspeedy;
    speedpid.sumerry+=speedpid.erry;
    speedpid.controlspeedy=speedpid.kp*speedpid.erry+speedpid.ki*speedpid.sumerry+speedpid.kd*(speedpid.erry-speedpid.lasterry);  
    speedpid.lasterry=speedpid.erry;  
    return speedpid.controlspeedz;
=======
float speedpidturn(float setspeed, float inspeed) 
{  
    speedpid.setspeed=setspeed;
    speedpid.actualspeed=inspeed;
    speedpid.err=speedpid.setspeed - speedpid.actualspeed;
    speedpid.sumerr+=speedpid.err;
    speedpid.controlspeed=speedpid.kp*speedpid.err+speedpid.ki*speedpid.sumerr+speedpid.kd*(speedpid.err-speedpid.lasterr);  
    speedpid.lasterr=speedpid.err;  
    return speedpid.controlspeed; 
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
}  

void bt_go(void);       //蓝牙控制车跑
void Camera(void);      //采集摄像头的数据
void Cameraview(void);  //上位机显示摄像头图片
void position(void);    //算法识别信标的位置
<<<<<<< HEAD
void pidcontroldir(void);  //pid控制方向
void pidcontroldir2(void);
void pidcontrolspeed(void);  //pid控制速度
=======
void pidcontrol(void);  //pid控制
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
void lcdshow(void);     //显示数据

float speedms(float ms)  //输出控制车ms米每秒
{
    float outms;
    outms = ms*68/43*500/200/0.2*1.37;//车轮的齿轮和编码器的齿轮比例为68/43，编码器一圈500个脉冲，每5ms采集一次脉冲，则200次为1秒，0.2m为小车轮子周长
<<<<<<< HEAD
    return outms;               //求每5ms多少个脉冲，1.37为实际测量误差比例, 一圈为1083个脉冲
}

float speedinms(float inms)
{
    float ms;
    ms = inms*3500;             //车轮20厘米一圈，一圈需要700个脉冲，1m3500个脉冲
    return ms;
}

void distance(void)             //编码器算距离
{
    speedcount[0] = DMA_count_get(DMA_CH2);
    speedcount[3] = DMA_count_get(DMA_CH3);
    if(timer0count == 2)
    {
        speedcount[2] += speedcount[0];
        speedcount[5] += speedcount[3];
    }
    else
    {
        speedcount[2] += speedcount[0] - speedcount[1];
        speedcount[5] += speedcount[3] - speedcount[4];
    }
    speedcount[1] = speedcount[0];
    speedcount[4] = speedcount[3];
    speedcount[6] = (speedcount[2]+speedcount[5])/2;
=======
    return outms;               //求每5ms多少个脉冲，1.37为实际测量误差比例
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
}

void all_init(void)     //总初始化
{
    BSP_init();
    
    //初始化定时器
    Timer_Init(1,5);    //同时初始化定时器0、1，定时器0为1ms触发，定时器1为5ms触发
    EnableTimer0();     //开启定时器1
    EnableTimer1();     //开启定时器2
    
    DIRPID(50);         //初始化方向pid，同时设定期望中间值为50
    
    SPEEDPID();         //初始化速度pid
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    
    //获取拨码开关的值
    key[0] = Gpio_get(PORT_B, 0);//初始速度选择
    key[1] = Gpio_get(PORT_B, 1);
    key[2] = Gpio_get(PORT_B, 2);//卡死重启系统
    key[3] = Gpio_get(PORT_B, 3);//是否加速
    key[4] = Gpio_get(PORT_B, 4);//方案选择
    
<<<<<<< HEAD
    speedinit = 1.5;         //默认为1m/s
    avevalue = 450;
    if(key[0] == 1)
    {
        speedinit = 2.0;     //单位为m/s
        dirpid.kd=0.8;
        value = 100;
        if(key[3] == 1)
          avevalue = 350 - 30;
        else
          avevalue = 350;
    }
    if(key[1] == 1)
    {
        speedinit = 2.7;     //单位为m/s
        dirpid.kd=0.75;
        value = 110;
        if(key[3] == 1)
          avevalue = 270 - 30;
        else
          avevalue = 270;
    }
    if(key[0] == 1 && key[1] == 1)
    {
        speedinit = 3.0;     //单位为m/s
        dirpid.kd=1.0;
        value = 130;
        if(key[3] == 1)
          avevalue = 200 - 30;
        else
          avevalue = 200;
    }
    
    speedset = (int)speedms(speedinit);     //初始速度
    
    dircentral = 680;        //舵机中间值
=======
    speedinit = 1.0;         //默认为1m/s
    if(key[0] == 1)
        speedinit = 1.5;     //单位为m/s
    if(key[1] == 1)
        speedinit = 2.0;     //单位为m/s
    if(key[0] == 1 && key[1] == 1)
=======
<<<<<<< HEAD
    
    key[0] = Gpio_get(PORT_A, 19);//获取拨码开关的值
    key[1] = Gpio_get(PORT_A, 17);
    key[2] = Gpio_get(PORT_A, 16);
    key[3] = Gpio_get(PORT_A, 15);
    key[4] = Gpio_get(PORT_A, 14);
    key[5] = Gpio_get(PORT_A, 13);
    key[6] = Gpio_get(PORT_A, 12);
    key[7] = Gpio_get(PORT_A, 11);
    
    speedinit = 1.0;
    if(key[7] == 1)
        speedinit = 1.5;     //单位为m/s
    if(key[6] == 1)
        speedinit = 2.0;     //单位为m/s
    if(key[6] == 1 && key[7] == 1)
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
        speedinit = 2.5;     //单位为m/s
    
    speedset = (int)speedms(speedinit);     //初始速度
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
}

void main()
{ 
    
    all_init();
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
    speedinit = 80;     //初始速度
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    
    while(1)
    {
      
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
        if(stop == 0)
            switch(timer0count)
            {
                case 0: 
                        if(ok == 0)Camera();
                        break;
                case 1:
                        if(ok == 1)position();
                        break;
                case 2:
<<<<<<< HEAD
                        if(ok == 2 && key[4] == 0)pidcontroldir();
                        if(ok == 2 && key[4] == 1)pidcontroldir2();
                        break;
                case 3:
                        if(ok == 3)pidcontrolspeed();
                        break;
                case 4:
                        lcdshow();
=======
                        if(ok == 2)pidcontrol();
                        break;
                case 3:
                        lcdshow();
                        break;
                case 4:
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
                        ok = 0;
                        break;
                
            }
        else
        {
<<<<<<< HEAD
              PWM_Output(PWM_PIN_PTA10,dircentral);
              PWM_Output(PWM_PIN_PTA6,80);PWM_Output(PWM_PIN_PTA7,0);//右轮
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,80);//左轮
              if(stop >= 2 && key[2] == 1)//重启系统
              {
                  DisableInterrupts;
                  all_init();
                  stop = 0;
                  start = 0;
                  ok = 0;
                  timer0count = 0;
                  speedpid.sumerrz = 0;
                  speedpid.sumerry = 0;
              }
        }
        
        if(start >= 14)
            stop = 2;
        
=======
<<<<<<< HEAD
                if(stop >= 2 && key[2] == 1)//重启系统
                {
                    DisableInterrupts;
                    all_init();
                    stop = 0;
                }
                PWM_Output(PWM_PIN_PTA10,680);
                PWM_Output(PWM_PIN_PTA6,80);PWM_Output(PWM_PIN_PTA7,0);//右轮
                PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,80);//左轮
=======
          
//            if(stop >= 2)//重启系统
//            {
//                DisableInterrupts;
//                all_init();
//                stop = 0;
//            }
                
            PWM_Output(PWM_PIN_PTA10,680);
            PWM_Output(PWM_PIN_PTA6,80);PWM_Output(PWM_PIN_PTA7,0);//右轮
            PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,80);//左轮
=======
      
        switch(timer0count)
        {
            case 0: 
                    Camera();
                    break;
            case 1:
                    position();
                    break;
            case 2:
                    pidcontrol();
                    break;
            case 3:
                    lcdshow();
                    break;
            case 4:
                    break;
            
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
        }
        
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
        
        //LED_P6x8Str(5,1,"abc");
        //bt_go();//蓝牙控制车跑
     }
}

void Camera(void)
{
    if(Is_SendPhoto)
    { 
<<<<<<< HEAD
        DisableInterrupts;
=======
<<<<<<< HEAD
        DisableInterrupts;
=======
<<<<<<< HEAD
        DisableInterrupts;
=======
        //DisableInterrupts;
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
        //Cameraview();//上位机显示摄像头图片
        LocatingEye_OriginalImage_FixedThreshold_OledPrint();//信标检测方式
        
        FPS++;
<<<<<<< HEAD
        
        if(start == 0 && Area == 0)
        {
            ok = 0;
            timer0count = 0;
            lcdshow();
            DisableTimer0();
        }
        else
        {
            ok = 1;
            EnableTimer0();
            if(start == 0)
                start = 1;
        }
        
        EnableInterrupts;   
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
        
        ok = 1;
        
        EnableInterrupts;   
<<<<<<< HEAD
=======
=======
        //EnableInterrupts;   
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    }

}

void position(void)             //算法识别信标的位置
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    u16 i, z, numb;
    
    numb = 0;
    
    while(numb < 9)//保存最近十帧画面数据
    {
        dir[0][numb] = dir[0][numb+1];      //x轴坐标
        dir[1][numb] = dir[1][numb+1];      //y轴坐标
        dir[2][numb] = dir[2][numb+1];      //面积大小
        numb++;
    }
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
    u16 z;
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    
    dir[0][numb] = X_axis;      //x轴坐标
    dir[1][numb] = Y_axis;      //y轴坐标
    dir[2][numb] = Area;        //面积大小
<<<<<<< HEAD
    
=======
<<<<<<< HEAD
    
=======
<<<<<<< HEAD
    
=======
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
  
    if(dir[0][numb] != 0)//记录丢失信标前的十帧数据
    {
      
        z = 0;
        while(z < 9)
        {
<<<<<<< HEAD
            record[0][z] = record[0][z+1];
            record[1][z] = record[1][z+1];
            z++;
        }
        record[0][9] = dir[0][numb];
        record[1][9] = dir[1][numb];
        
        record[0][11] = record[0][9]+(record[0][9]-record[0][8])*(record[0][9]-record[0][8])/(record[0][8]-record[0][7]);//预测信标下一个位置
        record[1][11] = record[1][9]+(record[1][9]-record[1][8])*(record[1][9]-record[1][8])/(record[1][8]-record[1][7]);//预测信标下一个位置
        count++;
        if(count == 6)
            record[0][10] = dir[2][numb];
        
    }
    else
    {
        if(record[0][9] >= 60 && record[0][11] >= 60)//确认信标丢失
            xb_lose = 1;
        else
            xb_lose = 0;
        
        count = 0;
    }
    
=======
            record[z] = record[z+1];
            z++;
        }
        record[9] = dir[0][numb];
        count++;
        if(count == 6)
            record[10] = dir[2][numb];
      
    }
    else
    {
        if(record[9] >= 60)//确认信标丢失
<<<<<<< HEAD
            xb_lose = 1;
=======
        {
            xb_lose = 1;
        }
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
        else
            xb_lose = 0;
        count = 0;
    }
    
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    setfps = 3;//需要求的平均的最近帧数，最小为1，最大为10
    
    Areave = 0;
    dirave[0][0] = 0;
    dirave[1][0] = 0;
    
    for(i = 0; i < setfps; i++)
    {
        Areave += dir[2][9-i];
        dirave[0][0] += dir[0][9-i];
        dirave[1][0] += dir[1][9-i];
//        if(numb >= 1)
//            direrr[numb] = dir[0][numb] - dir[0][numb-1];
    }
    dirave[0][0] = dirave[0][0]/setfps;
    dirave[1][0] = dirave[1][0]/setfps;
    Areave = Areave/setfps;//取三帧数据，求面积平均值
    
    
<<<<<<< HEAD
    for(i = 0; i < 3; i++)//记录信标大小的变化
=======
<<<<<<< HEAD
    for(i = 0; i < 3; i++)//记录信标大小的变化
=======
    for(i = 0; i < 3; i++)
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    {
        recordave[i] = recordave[i+1];
    }
    recordave[2] = Areave;
    
<<<<<<< HEAD
    recordave[3] = recordave[2]+(recordave[2]-recordave[1])*(recordave[2]-recordave[1])/(recordave[1]-recordave[0]);//预测信标下一个面积
    
      
    ok = 2;
}

void pidcontroldir(void)//pid控制小车的舵机和速度
{
  
//    int recorderr = 0;
    
=======
<<<<<<< HEAD
    recordave[3] = recordave[2]+(recordave[2]-recordave[1])*(recordave[2]-recordave[1])/(recordave[1]-recordave[0]);//预测信标下一个位置
    
      
    ok = 2;
=======
    recordave[3] = recordave[2]+(recordave[2]-recordave[1])*(recordave[2]-recordave[1])/(recordave[1]-recordave[0]);
    
      
    ok = 2;
=======
    numb++;
    setfps = 3;//需要求的平均的最近帧数
    
    if(numb == setfps)//为计算准确使用此方法
    {   
        numb--;
        while(numb != 0 )
        {
          numb--;
          Areave += dir[2][numb];
          dirave[0][0] += dir[0][numb];
          dirave[1][0] += dir[1][numb];
//          if(numb >= 1)
//              direrr[numb] = dir[0][numb] - dir[0][numb-1];
        }
        dirave[0][0] = dirave[0][0]/setfps;
        dirave[1][0] = dirave[1][0]/setfps;
        Areave = Areave/setfps;//取三帧数据，求面积平均值
    }
    
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
}

void pidcontrol(void)//pid控制小车的舵机和速度
{
  
<<<<<<< HEAD
=======
//    direrr[2] = (direrr[1]*direrr[1]/direrr[0] + dirave)*1.2;
//    direrr[3] = (int)realizepid((float)direrr[2]);
//    direrr[2] = direrr[3] + dirave[0][0];
//    
//    if(dirave[0][0] >= 0 && dirave[0][0] <= 120)//定位信标控制方向
//        dirturn = 760 - dirave[0][0];
//    else
//        if(dirave[0][0] > 120)
//            dirturn = 620;
//        else
//            dirturn = 740;
    
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
/***************************************************
                    控制方向算法
***************************************************/
  
<<<<<<< HEAD
      
    if(dir[1][9] >= 20 && arrive == 0)//到达信标
    {  
        arrive = 1;
    }
      
    if(arrive == 1)
        dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * dirindex);//定位信标控制方向
    
    if(arrive != 1)  
    {
        dirpid.setdir = 44;
        
        dirindex = 1.6;
        
        if(arrive != 3)
            dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * dirindex);//定位信标控制方向
        
        if(Areave == 0)
        {
            
            if(xb_lose == 0)
            {
                dirturn = 760; //左
            }
            else
            {
                if(record[0][9] <= 100)
                    record[0][9]++;
            }
            
//                if(record[9] >= 100)
//                    dirturn = 600;
        }
    }
    
    
    //防止溢出
    if(dirturn >= 760)
        dirturn = 760;
    if(dirturn <= 600)
        dirturn = 600;
       
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
    
    ok = 3;
    
}

void pidcontroldir2()
{
    
/***************************************************
                    控制方向算法
***************************************************/
  
      
    if(dir[1][9] >= 20)//到达信标
    {  
        arrive = 2;
    }
      
    if(arrive == 2)
        dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * dirindex);//定位信标控制方向
    
    if(arrive != 2)  
    {
        dirpid.setdir = 50;
        
        dirindex = 1.6;
      
        if(xb_lose == 1)//信标丢失
        {
            dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * 1.6);
        }
        else
        {
            dirturn = (int)(dircentral + dirpidturn((float)dirave[0][0]) * dirindex);//定位信标控制方向
        }
        
        if(Areave == 0)
        {
            if(xb_lose == 0)
            {
                dirturn = 760;  //左
            }
            else
            {
                if(record[0][9] <= 100)
                    record[0][9]++;
                dirturn = (int)(dircentral - (record[0][9]-50)*1.6);
            }
            
//                if(record[9] >= 100)
//                    dirturn = 600;
            if(arrive == 4)
            {
                if(start == 1 || (start >= 5 && start <= 7) || start >= 12)
                {
                    dirturn =dircentral + 80; //左
                    record[0][9] = 1;
                }
                if((start >= 2 && start <= 4) || (start >= 8 && start <= 11))
                {
                    dirturn =dircentral - 80; //右
                    record[0][9] = 100;
                }
                arrive = 0;
                start++;
=======
<<<<<<< HEAD
    if(key[4] == 1)
    {
        if(Areave >= 300 || dir[1][9] >= 60)//到达信标
        {  
=======
<<<<<<< HEAD
    if(Areave >= 300 || dir[1][9] >= 60)//到达信标
    {  
        if(dirave[0][0] <= 50)
        {
            dirturn = 610; //右
        }
        else
        {
            dirturn = 750; //左
        }
        arrive = 1;
    }
    else
    {
        if(recordave[3] >= 300)
        {
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
            if(dirave[0][0] <= 50)
            {
                dirturn = 610; //右
            }
            else
            {
                dirturn = 750; //左
            }
            arrive = 1;
        }
<<<<<<< HEAD
        else
        {
            if(recordave[3] >= 300)
            {
                if(dirave[0][0] <= 50)
                {
                    dirturn = 610; //右
                }
                else
                {
                    dirturn = 750; //左
                }
                arrive = 1;
            }
        }
    }
//    else
//    {
//        if(Areave >= 200 || dir[1][9] >= 50)//到达信标
//        {
//            if(dirave[0][0] <= 50)
//            {
//                DIRPID(10);  //右
//            }
//            else
//            {
//                DIRPID(90);  //左
//            }
//            arrive = 2;
//        }
//        else
//        {
//            if(recordave[3] >= 200)
//            {
//                if(dirave[0][0] <= 50)
//                {
//                    DIRPID(10);  //右
//                }
//                else
//                {
//                    DIRPID(90);  //左
//                }
//                arrive = 2;
//            }
//        }
//    }
    
    if(arrive != 1)  
    {
=======
    }
    
    if(arrive == 1)
    {
        if(dirturn < 680)
            dirturn = 610;
        else
            dirturn = 750;
    }
    else
    {
      
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
        if(Areave <= 10 && Areave > 0)//根据小车与信标的距离计算合适的转向倍数
            dirindex = Areave / 25;
        else
            if((Areave <= 60 && Areave > 10))
                dirindex = Areave / (25 + (Areave - 10) / 2);
            else
                dirindex = Areave / (50 + (Areave - 60) / 3);
        
        if(dirindex >= 1.6)//最大倍数为1.6，大了舵机可能会超出范围
            dirindex = 1.6;
      
        if(xb_lose == 1)//信标丢失
        {
            if(record[9] != 0)
                dirturn = (int)(680 + dirpidturn((float)record[9]) * 1.6);
        }
        else
        {
            if(dirave[0][0] != 0)
                dirturn = (int)(680 + dirpidturn((float)dirave[0][0]) * dirindex);//定位信标控制方向
        }
        
        if(Areave == 0)
<<<<<<< HEAD
        {
=======
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
            if(xb_lose == 0)
            {
                dirturn = 760; //左
            }
            else
            {
                if(record[9] <= 100)
                    record[9]++;
<<<<<<< HEAD
            }
            if(record[9] >= 100 || arrive == 3)
            {
                dirturn = 600; //右
                record[9] = 100;
                arrive = 0;
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
            }
        }
    }
    
    
<<<<<<< HEAD
=======
=======
                if(record[9] >= 100)
                    dirturn = 600;
            }
    }
    
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    //防止溢出
    if(dirturn >= 760)
        dirturn = 760;
    if(dirturn <= 600)
        dirturn = 600;
       
<<<<<<< HEAD
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
    
    ok = 3;
    
}
void pidcontrolspeed()
{
  
    float recordaveerr[2] = {0};
    int recorderr = 0;
    int speedmix = 0;
    int jiasu = 0;
    
=======
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
/***************************************************
                    控制速度算法
***************************************************/
    
<<<<<<< HEAD
    recorderr = abs(record[0][9] - record[0][8]);
    
    if(recordave[2] != 0 && key[3] == 1 && arrive == 0 && recorderr < 20)
    {
        recordaveerr[0] = recordave[2] - recordave[1];
        recordaveerr[1] = speedinit*10;
        if(recordaveerr[0] <= recordaveerr[1] && recordaveerr[0] >= 2)//加速跑
        {
            speedset += (int)recordaveerr[0]*3;//控制小车加速度
        }
        jiasu = 1;
    }
    else//匀速跑
    {
        if(jiasu >= 1)
        {
            speedset = (int)speedms(speedinit*0.1);
            
            jiasu++;
            if(jiasu == 5)
                jiasu = 0;
        }
        else
            speedset = (int)speedms(speedinit);
//        if(arrive == 1 || recorderr >= 0)
//        {
//            speedset = (int)(speedms(speedinit)*0.5);
//            if(recorderr >= 30)
//                speedset = (int)(speedms(speedinit)*30/recorderr);
//        }
    }
    
    speedmix = (int)(speedms(speedinit)*1.8);
    if(speedset >= speedmix)//防止加速过快，最大为初始速度的两倍
        speedset = speedmix;
    
    if(start <= 1)
        speedset = speedset*2;
      
    if(dirturn >= 720)
    {
        speedpidturn(speedset*0.5,inspeedz,speedset,inspeedy);
    }
    else
    {
        if(dirturn <= 640)
        {
            speedpidturn(speedset,inspeedz,speedset*0.5,inspeedy);
        }
        else
        {
            speedpidturn(speedset,inspeedz,speedset,inspeedy);
        }
    }
    
    outspeedz = (int)speedpid.controlspeedz;
    outspeedy = (int)speedpid.controlspeedy;
    
    if(arrive != 0 && speedset < inspeedz && speedset < inspeedy && start != 13)
    {
        PWM_Output(PWM_PIN_PTA6,3);PWM_Output(PWM_PIN_PTA7,0);//右轮
        PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,3);//左轮
    }
    else
    {
        PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,outspeedy);//右轮
        PWM_Output(PWM_PIN_PTA9,outspeedz);PWM_Output(PWM_PIN_PTA8,0);//左轮

    }
    
    ok = 4;
    
}
void lcdshow()
{
    LED_PrintValueI(0,0,dirave[0][0]);//x轴坐标
    LED_PrintValueI(0,2,dir[1][9]);//y轴坐标
    LED_PrintValueI(0,6,dirturn);//方向
    LED_PrintValueI(0,4,(int)Areave);
//    LED_PrintValueI(0,6,inspeedz);
    LED_PrintValueI(64,6,speedcount[6]);
=======
<<<<<<< HEAD
    if(recordave[2] != 0 && key[3] == 1)
    {
        if(recordave[2] - recordave[1] <= speedinit*10 && recordave[2] - recordave[1] >= 2)//加速跑
        {
            speedset += (int)((recordave[2]-recordave[1]));//控制小车加速度
=======
    if(recordave[2] != 0)
    {
        if(recordave[2] - recordave[1] <= 20 && recordave[2] - recordave[1] >= 2)//加速跑
        {
            speedset += (int)((recordave[2]-recordave[1])/3);//控制小车加速度
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
        }
    }
    else//匀速跑
    {
        speedset = (int)speedms(speedinit); 
    }
    
<<<<<<< HEAD
    if(speedset >= (int)(speedms(speedinit)*1.2))//防止加速过快，最大为初始速度的两倍
        speedset = (int)(speedms(speedinit)*1.2);
    
    outspeedz = (int)speedpidturn(speedset,inspeedz);//pid调节速度
    outspeedy = (int)speedpidturn(speedset,inspeedy);
=======
    outspeedz = (int)speedpidturn(speedset,(float)inspeedz);
    outspeedy = (int)speedpidturn(speedset,(float)inspeedy);
=======
    if(Areave <= 10 && Areave > 0)//根据小车与信标的距离计算合适的转向倍数
        dirindex = Areave / 25;
    else
        if((Areave <= 60 && Areave > 10))
            dirindex = Areave / (25 + (Areave - 10) / 2);
        else
            dirindex = Areave / (50 + (Areave - 60) / 3);
    
    if(dirindex >= 1.6)//最大倍数为1.6，大了舵机可能会超出范围
        dirindex = 1.6;
  
    if(xb_lose == 1)//信标丢失
    {
        dirturn = (int)(680 + dirpidturn((float)record[9]) * 1.6);
    }
    else
    {
        dirturn = (int)(680 + dirpidturn((float)dirave[0][0]) * dirindex);//定位信标控制方向
    }
       
/***************************************************
                    控制速度算法
***************************************************/
    
    if(Areave >= 250 || dir[1][numb] >= 60)//到达信标
    {  
        outspeedz = speedinit; 
        outspeedy = speedinit;
        if(dirave[0][0] <= 50)
            dirturn = 600; //右
        else
            dirturn = 760; //左
        Delay_MS(500);
    }
    
    if(record[10] <= 0)//加速跑
    {
        if(Areave <= 200 && Areave > 50)//接近信标
        {
            outspeedz = (int)(speedinit + (200 - Areave) * 0.5);//控制小车减速度
            outspeedy = (int)(speedinit + (200 - Areave) * 0.5);
        }
        
        if(Areave <= 50 && Areave > 0)//距离信标远
        {
            outspeedz = (int)(speedinit + Areave * 1.6);//控制小车加速度
            outspeedy = (int)(speedinit + Areave * 1.6);
        }
    }
    else//匀速跑
    {
        outspeedz = speedinit;
        outspeedy = speedinit; 
    }
    
    if(Areave == 0)
    {
        if(xb_lose == 0)
        {
            dirturn = 760; //左
            outspeedz = speedinit - 20;
            outspeedy = speedinit + 10; //到达信标后围绕信标转的速度
        }
        else
        {
            if(record[9] <= 100)
                record[9]++;
            outspeedz = speedinit + 10;
            outspeedy = speedinit - 20; 
        }
        
//        count++;
//        if(count >= 200)
//        {
//            BSP_init();
//            count = 0;
//        }
    }
    else
    {
//        if(ave >= 80)
//            ave = 80;
//        speedz = 250 - Areave;
//        speedy = speedz;
//        if(count >= 1000)
//        {
//            dirturn = 600; //右
//            count = 0;
//        }
    }
    
    speedpidturn(outspeedz,record[10]);
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
    PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,outspeedy);//右轮
    PWM_Output(PWM_PIN_PTA9,outspeedz);PWM_Output(PWM_PIN_PTA8,0);//左轮
    
<<<<<<< HEAD
    ok = 3;
    
=======
<<<<<<< HEAD
    ok = 3;
    
=======
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
}

void lcdshow()
{
<<<<<<< HEAD
    LED_PrintValueI(0,0,dirave[0][0]);//x轴坐标
    //LED_PrintValueI(0,0,dir[1][9]);//y轴坐标
=======
<<<<<<< HEAD
    //LED_PrintValueI(0,0,dirave[0][0]);//x轴坐标
    LED_PrintValueI(0,0,dir[1][9]);//y轴坐标
    LED_PrintValueI(0,2,dirturn);//方向
    LED_PrintValueI(0,4,(int)Areave);
    LED_PrintValueI(0,6,inspeedz);
    LED_PrintValueI(64,6,record[9]);
=======
    LED_PrintValueI(0,0,dirave[0][0]);//x轴坐标
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
    LED_PrintValueI(0,2,dirturn);//方向
    LED_PrintValueI(0,4,(int)Areave);
    LED_PrintValueI(0,6,inspeedz);
    LED_PrintValueI(64,6,inspeedy);
<<<<<<< HEAD
=======
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
        
    if(showFPS)//显示摄像头的帧数，右上角
    {
        LED_P6x8Char(116,0,showFPS / 10 + 48);
        LED_P6x8Char(122,0,showFPS % 10 + 48);
    }
    
//    LED_PrintValueI(0,0,record[2]);
//    LED_PrintValueI(0,2,record[3]);
//    LED_PrintValueI(0,4,record[4]);
//    LED_PrintValueI(0,6,record[5]);
//    LED_PrintValueI(64,0,record[6]);
//    LED_PrintValueI(64,2,record[7]);
//    LED_PrintValueI(64,4,record[8]);
//    LED_PrintValueI(64,6,record[9]);
}
                    
void Cameraview(void)//上位机显示摄像头图片
{
    int  m=0,n=0;
    //发送一帧数据
    Uart_SendByte(UART4,0xFF);//图像头   
    for(m=0; m<ROW; m++)
    {
        for(n=0;n<COL ;n++)
        {
           if(Pix_Data[m][n] == 0xFF) 
              Pix_Data[m][n]--;
           Uart_SendByte(UART4,Pix_Data[m][n]);
        }
    }
}

void bt_go(void)//蓝牙控制车跑
{
    int i = 0;//有问题
    u8 temp;
    //Uart_SendByte(UART4,Uart_Getch(UART4));  //测试串口
    temp = Uart_Getch(UART4);//蓝牙遥控，程序会死在这里，接收到数据才执行
    Uart_SendByte(UART4,temp);
    temp -= 48;
    switch(temp)
    {
        case 0: PWM_Output(PWM_PIN_PTA10,695);//中
            break;
        case 1: PWM_Output(PWM_PIN_PTA10,760);//左
            break;
        case 2: PWM_Output(PWM_PIN_PTA10,630);//右
            break;
        case 3: 
            if(i <= 250)//加速
            {
                if(i < 250)
                    i += 10;
                else
                    i = 250;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
        case 4: 
            if(i >= 0)//减速
            {
                if(i >= 50)
                    i -= 10;
                else
                    i = 0;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
         case 5: //停止
              i = 0;
              PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
    }
}
//PIT中断服务函数
void Timer0_isr()
{
    
    if(timer0count > 5)
    {
        timer0count = 0;
      
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
    }
    else
        timer0count++;
    
    if(timer0count == 2)
    {
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
/***************************************************
                    获取左右轮转速
***************************************************/
        
        inspeedz = DMA_count_get(DMA_CH3);
        inspeedy = DMA_count_get(DMA_CH2);
        DMA_count_reset(DMA_CH2);
        DMA_count_reset(DMA_CH3);
<<<<<<< HEAD
    }
    
    distance();
    switch(arrive)
    {
        case 0: 
                speedcount[2] = 0;
                speedcount[5] = 0;
                break;
        case 1:
                if(speedcount[6] >= speedinms(10/(value - 50)))
                {
                  
                   speedcount[2] = 0;
                   speedcount[5] = 0;
                   
                   
                   if((start >= 6 && start <= 7) || start >= 12)
                   {
                       if(dirpid.setdir >= value)
                       {
                          arrive = 3;
                       }
                       else
                          dirpid.setdir += 10;
                   }
                   else
                   {
                       if(dirpid.setdir <= 100 - value)
                       {
                          arrive = 3;
                       }
                       else
                          dirpid.setdir -= 10;
                   }
                     
                }
                break;
        case 2:
                if(speedcount[6] >= speedinms(0.16/(value- 50)))
                {
                  
                   speedcount[2] = 0;
                   speedcount[5] = 0;
                   
                   if(dirpid.setdir >= value)
                   {
                      arrive = 4;
                   }
                   else
                      dirpid.setdir += 10;
                     
                }
                break;
        case 3:
                if((start >= 6 && start <= 7) || start >= 12)
                {
                    dirturn =dircentral + 80; //左
                    record[0][9] = 1;
                }
                if((start >= 1 && start <= 5) || (start >= 8 && start <= 11))
                {
                    dirturn =dircentral - 80; //右
                    record[0][9] = 100;
                }
                if(speedcount[6] >= speedinms(0.26))//1700
                {
                    arrive = 0;
                    start++;
                }
                break;
        
    }
    
    if(record[0][9] >= 100)
    {
        dirturn = (int)(dircentral - (record[0][9]-50)*1.6);
    }
    PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
    
    
//    if(Gpio_get(PORT_C, 3) == 0)//每隔1ms获取光电开关管的状态
//    {
//        if(dirturn > 680)
//              dirturn = 750;
//        else
//              dirturn = 610;
//        PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
//    }
=======
<<<<<<< HEAD
    }
    if(arrive == 1)
    {
       speedcount = DMA_count_get(DMA_CH3) + DMA_count_get(DMA_CH2);
       if(speedcount >= 10)
       {
          if(record[9] > 50)
              arrive = 3;
          else
              arrive = 0;
          
=======
<<<<<<< HEAD
    }
    if(arrive == 1)
    {
       speedcount += DMA_count_get(DMA_CH3) + DMA_count_get(DMA_CH2);
       if(speedcount >= 5)
       {
          arrive = 0;
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
          speedcount = 0;
          
          if(dirturn > 680)
              dirturn = 610;
          else
              dirturn = 750;
          PWM_Output(PWM_PIN_PTA10,dirturn);//舵机转向
       }
    }
<<<<<<< HEAD
    
//    if(arrive == 2)
//    {
//          arrive = 0;
//          DIRPID(50);
//    }
=======
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0

    Cleartimer0();
}
//PIT中断服务函数
void Timer1_isr()
{
  
    timer1count++;
    if(timer1count == 200)
    {
<<<<<<< HEAD
        if((abs(inspeedz - inspeedy) >= 25 * speedinit || (inspeedz < 10 && inspeedz > 3) || (inspeedy < 10 && inspeedy > 3)) && start >= 2)
=======
<<<<<<< HEAD
        if(abs(inspeedz - inspeedy) >= 40 || inspeedz < 5 || inspeedy < 5)
=======
        if(abs(inspeedz - inspeedy) >= 30 || inspeedz < 5 || inspeedy < 5)
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
             stop++;
        else
             stop = 0;
        showFPS = FPS;
        FPS = 0;
        timer1count = 0;
    }
    else 
        showFPS = 0;
<<<<<<< HEAD

=======
<<<<<<< HEAD

=======
=======
      
    }
    else
        timer0count++;
>>>>>>> 0bbc041506cd1da35f54924a6edd506d903fab64

  
    Cleartimer1();
}

    Cleartimer0();
}
//PIT中断服务函数
void Timer1_isr()
{
  
    timer1count++;
    if(timer1count == 200)
    {
        showFPS = FPS;
        FPS = 0;
        timer1count = 0;
    }
    else 
        showFPS = 0;
>>>>>>> 06a8d79eeefa28bd979699cddc6314d3239f9a1f
>>>>>>> ea795226d5a6285dcc1d64d20c7447dd0387f0c0
  
    Cleartimer1();
}




>>>>>>> 9a9e21913515c6321b3c1bf806a3b405f1c4cc99

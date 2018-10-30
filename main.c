#include "K60_datatype.h"
/**************************************************************************************************
*                        K60              ��λ��
*                      VCC(5V/3V3)        VCC(5V)
*                      PTD[0:7]           Y[0:7]
*                      PTC18              PCLK
*                      PTC17              HREF
*                      PTC16              VSYN
*                      GND                GND
*              K60�봮��ģ����߷�ʽ��
*                      PTE24��RX    PTE25��TX   Ĭ��ʹ��K60�Ĵ���4 
*             ��λ�����ã�������115200   
*                         �����������ݲ��뿪�ص�״̬����������ֵ����K60_datatype.h���޸�ROW��COL
*                                        ���뿪����ֵ��
*                             ���뿪��״̬        �ֱ��ʣ�����*������
*                                  11                320*240
*                                  10                160*120
*                                  01                100*80
*                                  10                80*60
*  ʵ�������������ͷ��λ�����趨������������ֵ��K60_datatype.h�ļ��еĺ궨��һ��
*            ������Ϊ115200����ʼ����ͼ��
****************************************************************************************************/
extern  u8  Image_Sort_History[3][ROW][COL];
extern  u32   time;
extern  int Area, X_axis, Y_axis;//������ͷȡ��

//char Pix_Data[ROW][COL]={0};
char Is_SendPhoto=0;
int  V_Cnt=0, timer0count = 0, timer1count = 0, FPS = 0, showFPS = 0, count = 0, xb_lose = 0;
int  speedset = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, speedave = 0, dirave[2][3] = {0}, dir[3][10] = {0}, dirturn = 0, direrr[4] = {0}, record[2][12] = {0};
int  setfps = 0, ok = 0, stop = 0, key[8] = {0}, arrive = 0, speedcount[8] = {0}, start = 0, dircentral = 0;
float Areave = 0, dirindex = 0, speedinit = 0, recordave[4] = {0}, avevalue = 0, value = 0;


//DIRPID���ں���
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
    dirpid.setdir=dir;          //����ֵ
    dirpid.actualdir=0.0;       //ʵ��ֵ
    dirpid.err=0.0;             //���
    dirpid.lasterr=0.0;         //���һ�����
    dirpid.sumerr=0.0;          //����ܺ�
    dirpid.controldir=0.0;      //����Ŀ���ֵ
    dirpid.kp=0.25;              //P����
    dirpid.ki=0.0;              //I����
    dirpid.kd=0.6;              //D����,�ٶ�Խ�󣬲���ԽС
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

//SPEEDPID���ں���
struct 
{  
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
    speedpid.kp=0.5;  
    speedpid.ki=0.05;  
    speedpid.kd=0.0; 
}  
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
}  

void bt_go(void);       //�������Ƴ���
void Camera(void);      //�ɼ�����ͷ������
void Cameraview(void);  //��λ����ʾ����ͷͼƬ
void position(void);    //�㷨ʶ���ű��λ��
void pidcontroldir(void);  //pid���Ʒ���
void pidcontroldir2(void);
void pidcontrolspeed(void);  //pid�����ٶ�
void lcdshow(void);     //��ʾ����

float speedms(float ms)  //������Ƴ�ms��ÿ��
{
    float outms;
    outms = ms*68/43*500/200/0.2*1.37;//���ֵĳ��ֺͱ������ĳ��ֱ���Ϊ68/43��������һȦ500�����壬ÿ5ms�ɼ�һ�����壬��200��Ϊ1�룬0.2mΪС�������ܳ�
    return outms;               //��ÿ5ms���ٸ����壬1.37Ϊʵ�ʲ���������, һȦΪ1083������
}

float speedinms(float inms)
{
    float ms;
    ms = inms*3500;             //����20����һȦ��һȦ��Ҫ700�����壬1m3500������
    return ms;
}

void distance(void)             //�����������
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
}

void all_init(void)     //�ܳ�ʼ��
{
    BSP_init();
    
    //��ʼ����ʱ��
    Timer_Init(1,5);    //ͬʱ��ʼ����ʱ��0��1����ʱ��0Ϊ1ms��������ʱ��1Ϊ5ms����
    EnableTimer0();     //������ʱ��1
    EnableTimer1();     //������ʱ��2
    
    DIRPID(50);         //��ʼ������pid��ͬʱ�趨�����м�ֵΪ50
    
    SPEEDPID();         //��ʼ���ٶ�pid
    
    //��ȡ���뿪�ص�ֵ
    key[0] = Gpio_get(PORT_B, 0);//��ʼ�ٶ�ѡ��
    key[1] = Gpio_get(PORT_B, 1);
    key[2] = Gpio_get(PORT_B, 2);//��������ϵͳ
    key[3] = Gpio_get(PORT_B, 3);//�Ƿ����
    key[4] = Gpio_get(PORT_B, 4);//����ѡ��
    
    speedinit = 1.5;         //Ĭ��Ϊ1m/s
    avevalue = 450;
    if(key[0] == 1)
    {
        speedinit = 2.0;     //��λΪm/s
        dirpid.kd=0.8;
        value = 100;
        if(key[3] == 1)
          avevalue = 350 - 30;
        else
          avevalue = 350;
    }
    if(key[1] == 1)
    {
        speedinit = 2.7;     //��λΪm/s
        dirpid.kd=0.75;
        value = 110;
        if(key[3] == 1)
          avevalue = 270 - 30;
        else
          avevalue = 270;
    }
    if(key[0] == 1 && key[1] == 1)
    {
        speedinit = 3.0;     //��λΪm/s
        dirpid.kd=1.0;
        value = 130;
        if(key[3] == 1)
          avevalue = 200 - 30;
        else
          avevalue = 200;
    }
    
    speedset = (int)speedms(speedinit);     //��ʼ�ٶ�
    
    dircentral = 680;        //����м�ֵ
}

void main()
{ 
    
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
                        if(ok == 2 && key[4] == 0)pidcontroldir();
                        if(ok == 2 && key[4] == 1)pidcontroldir2();
                        break;
                case 3:
                        if(ok == 3)pidcontrolspeed();
                        break;
                case 4:
                        lcdshow();
                        ok = 0;
                        break;
                
            }
        else
        {
              PWM_Output(PWM_PIN_PTA10,dircentral);
              PWM_Output(PWM_PIN_PTA6,80);PWM_Output(PWM_PIN_PTA7,0);//����
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,80);//����
              if(stop >= 2 && key[2] == 1)//����ϵͳ
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
        
        
        //LED_P6x8Str(5,1,"abc");
        //bt_go();//�������Ƴ���
     }
}

void Camera(void)
{
    if(Is_SendPhoto)
    { 
        DisableInterrupts;
        //Cameraview();//��λ����ʾ����ͷͼƬ
        LocatingEye_OriginalImage_FixedThreshold_OledPrint();//�ű��ⷽʽ
        
        FPS++;
        
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
    }

}

void position(void)             //�㷨ʶ���ű��λ��
{
    u16 i, z, numb;
    
    numb = 0;
    
    while(numb < 9)//�������ʮ֡��������
    {
        dir[0][numb] = dir[0][numb+1];      //x������
        dir[1][numb] = dir[1][numb+1];      //y������
        dir[2][numb] = dir[2][numb+1];      //�����С
        numb++;
    }
    
    dir[0][numb] = X_axis;      //x������
    dir[1][numb] = Y_axis;      //y������
    dir[2][numb] = Area;        //�����С
    
  
    if(dir[0][numb] != 0)//��¼��ʧ�ű�ǰ��ʮ֡����
    {
      
        z = 0;
        while(z < 9)
        {
            record[0][z] = record[0][z+1];
            record[1][z] = record[1][z+1];
            z++;
        }
        record[0][9] = dir[0][numb];
        record[1][9] = dir[1][numb];
        
        record[0][11] = record[0][9]+(record[0][9]-record[0][8])*(record[0][9]-record[0][8])/(record[0][8]-record[0][7]);//Ԥ���ű���һ��λ��
        record[1][11] = record[1][9]+(record[1][9]-record[1][8])*(record[1][9]-record[1][8])/(record[1][8]-record[1][7]);//Ԥ���ű���һ��λ��
        count++;
        if(count == 6)
            record[0][10] = dir[2][numb];
        
    }
    else
    {
        if(record[0][9] >= 60 && record[0][11] >= 60)//ȷ���ű궪ʧ
            xb_lose = 1;
        else
            xb_lose = 0;
        
        count = 0;
    }
    
    setfps = 3;//��Ҫ���ƽ�������֡������СΪ1�����Ϊ10
    
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
    Areave = Areave/setfps;//ȡ��֡���ݣ������ƽ��ֵ
    
    
    for(i = 0; i < 3; i++)//��¼�ű��С�ı仯
    {
        recordave[i] = recordave[i+1];
    }
    recordave[2] = Areave;
    
    recordave[3] = recordave[2]+(recordave[2]-recordave[1])*(recordave[2]-recordave[1])/(recordave[1]-recordave[0]);//Ԥ���ű���һ�����
    
      
    ok = 2;
}

void pidcontroldir(void)//pid����С���Ķ�����ٶ�
{
  
//    int recorderr = 0;
    
/***************************************************
                    ���Ʒ����㷨
***************************************************/
  
      
    if(dir[1][9] >= 20 && arrive == 0)//�����ű�
    {  
        arrive = 1;
    }
      
    if(arrive == 1)
        dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * dirindex);//��λ�ű���Ʒ���
    
    if(arrive != 1)  
    {
        dirpid.setdir = 44;
        
        dirindex = 1.6;
        
        if(arrive != 3)
            dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * dirindex);//��λ�ű���Ʒ���
        
        if(Areave == 0)
        {
            
            if(xb_lose == 0)
            {
                dirturn = 760; //��
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
    
    
    //��ֹ���
    if(dirturn >= 760)
        dirturn = 760;
    if(dirturn <= 600)
        dirturn = 600;
       
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//���ת��
    
    ok = 3;
    
}

void pidcontroldir2()
{
    
/***************************************************
                    ���Ʒ����㷨
***************************************************/
  
      
    if(dir[1][9] >= 20)//�����ű�
    {  
        arrive = 2;
    }
      
    if(arrive == 2)
        dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * dirindex);//��λ�ű���Ʒ���
    
    if(arrive != 2)  
    {
        dirpid.setdir = 50;
        
        dirindex = 1.6;
      
        if(xb_lose == 1)//�ű궪ʧ
        {
            dirturn = (int)(dircentral + dirpidturn((float)record[0][9]) * 1.6);
        }
        else
        {
            dirturn = (int)(dircentral + dirpidturn((float)dirave[0][0]) * dirindex);//��λ�ű���Ʒ���
        }
        
        if(Areave == 0)
        {
            if(xb_lose == 0)
            {
                dirturn = 760;  //��
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
                    dirturn =dircentral + 80; //��
                    record[0][9] = 1;
                }
                if((start >= 2 && start <= 4) || (start >= 8 && start <= 11))
                {
                    dirturn =dircentral - 80; //��
                    record[0][9] = 100;
                }
                arrive = 0;
                start++;
            }
        }
    }
    
    
    //��ֹ���
    if(dirturn >= 760)
        dirturn = 760;
    if(dirturn <= 600)
        dirturn = 600;
       
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//���ת��
    
    ok = 3;
    
}
void pidcontrolspeed()
{
  
    float recordaveerr[2] = {0};
    int recorderr = 0;
    int speedmix = 0;
    int jiasu = 0;
    
/***************************************************
                    �����ٶ��㷨
***************************************************/
    
    recorderr = abs(record[0][9] - record[0][8]);
    
    if(recordave[2] != 0 && key[3] == 1 && arrive == 0 && recorderr < 20)
    {
        recordaveerr[0] = recordave[2] - recordave[1];
        recordaveerr[1] = speedinit*10;
        if(recordaveerr[0] <= recordaveerr[1] && recordaveerr[0] >= 2)//������
        {
            speedset += (int)recordaveerr[0]*3;//����С�����ٶ�
        }
        jiasu = 1;
    }
    else//������
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
    if(speedset >= speedmix)//��ֹ���ٹ��죬���Ϊ��ʼ�ٶȵ�����
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
        PWM_Output(PWM_PIN_PTA6,3);PWM_Output(PWM_PIN_PTA7,0);//����
        PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,3);//����
    }
    else
    {
        PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,outspeedy);//����
        PWM_Output(PWM_PIN_PTA9,outspeedz);PWM_Output(PWM_PIN_PTA8,0);//����

    }
    
    ok = 4;
    
}
void lcdshow()
{
    LED_PrintValueI(0,0,dirave[0][0]);//x������
    LED_PrintValueI(0,2,dir[1][9]);//y������
    LED_PrintValueI(0,6,dirturn);//����
    LED_PrintValueI(0,4,(int)Areave);
//    LED_PrintValueI(0,6,inspeedz);
    LED_PrintValueI(64,6,speedcount[6]);
        
    if(showFPS)//��ʾ����ͷ��֡�������Ͻ�
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
                    
void Cameraview(void)//��λ����ʾ����ͷͼƬ
{
    int  m=0,n=0;
    //����һ֡����
    Uart_SendByte(UART4,0xFF);//ͼ��ͷ   
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

void bt_go(void)//�������Ƴ���
{
    int i = 0;//������
    u8 temp;
    //Uart_SendByte(UART4,Uart_Getch(UART4));  //���Դ���
    temp = Uart_Getch(UART4);//����ң�أ����������������յ����ݲ�ִ��
    Uart_SendByte(UART4,temp);
    temp -= 48;
    switch(temp)
    {
        case 0: PWM_Output(PWM_PIN_PTA10,695);//��
            break;
        case 1: PWM_Output(PWM_PIN_PTA10,760);//��
            break;
        case 2: PWM_Output(PWM_PIN_PTA10,630);//��
            break;
        case 3: 
            if(i <= 250)//����
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
            if(i >= 0)//����
            {
                if(i >= 50)
                    i -= 10;
                else
                    i = 0;
                PWM_Output(PWM_PIN_PTA6,i);PWM_Output(PWM_PIN_PTA7,0);
                PWM_Output(PWM_PIN_PTA9,i);PWM_Output(PWM_PIN_PTA8,0);
            }
            break;
         case 5: //ֹͣ
              i = 0;
              PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,0);
              PWM_Output(PWM_PIN_PTA9,0);PWM_Output(PWM_PIN_PTA8,0);
    }
}
//PIT�жϷ�����
void Timer0_isr()
{
    
    if(timer0count > 5)
    {
        timer0count = 0;
      
    }
    else
        timer0count++;
    
    if(timer0count == 2)
    {
/***************************************************
                    ��ȡ������ת��
***************************************************/
        
        inspeedz = DMA_count_get(DMA_CH3);
        inspeedy = DMA_count_get(DMA_CH2);
        DMA_count_reset(DMA_CH2);
        DMA_count_reset(DMA_CH3);
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
                    dirturn =dircentral + 80; //��
                    record[0][9] = 1;
                }
                if((start >= 1 && start <= 5) || (start >= 8 && start <= 11))
                {
                    dirturn =dircentral - 80; //��
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
    PWM_Output(PWM_PIN_PTA10,dirturn);//���ת��
    
    
//    if(Gpio_get(PORT_C, 3) == 0)//ÿ��1ms��ȡ��翪�عܵ�״̬
//    {
//        if(dirturn > 680)
//              dirturn = 750;
//        else
//              dirturn = 610;
//        PWM_Output(PWM_PIN_PTA10,dirturn);//���ת��
//    }

    Cleartimer0();
}
//PIT�жϷ�����
void Timer1_isr()
{
  
    timer1count++;
    if(timer1count == 200)
    {
        if((abs(inspeedz - inspeedy) >= 25 * speedinit || (inspeedz < 10 && inspeedz > 3) || (inspeedy < 10 && inspeedy > 3)) && start >= 2)
             stop++;
        else
             stop = 0;
        showFPS = FPS;
        FPS = 0;
        timer1count = 0;
    }
    else 
        showFPS = 0;

  
    Cleartimer1();
}





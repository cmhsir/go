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
int  speedinit = 0, inspeedz = 0, inspeedy = 0, outspeedz = 0, outspeedy = 0, numb = 0, speedave = 0, dirave[2][3] = {0}, dir[2][3] = {0}, dirturn = 0, direrr[4] = {0}, record[11] = {0}, recordave[3] = {0};
int  setfps = 0;
float Areave = 0, dirindex = 0;


//DIRPID���ں���
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
    dirpid.setdir=dir;          //����ֵ
    dirpid.actualdir=0.0;       //ʵ��ֵ
    dirpid.err=0.0;             //���
    dirpid.lasterr=0.0;         //���һ�����
    dirpid.controldir=0.0;      //����Ŀ���ֵ
    dirpid.kp=1.0;              //P����
    dirpid.kd=0.1;              //D����
}  
float dirpidturn(float dir) 
{ 
    dirpid.actualdir=dir;  
    dirpid.err=dirpid.setdir - dirpid.actualdir;
    dirpid.controldir=dirpid.kp*dirpid.err+dirpid.kd*(dirpid.err-dirpid.lasterr);  
    dirpid.lasterr=dirpid.err;
    return dirpid.controldir; 
}  

//SPEEDPID���ں���
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
//    if(abs((int)speedpid.err)>200)           //����ֹ���
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

void bt_go(void);       //�������Ƴ���
void Camera(void);      //�ɼ�����ͷ������
void Cameraview(void);  //��λ����ʾ����ͷͼƬ
void position(void);    //�㷨ʶ���ű��λ��
void pidcontrol(void);  //pid����
void lcdshow(void);     //��ʾ����

void main()
{ 
    BSP_init();
    
    //��ʼ����ʱ��
    Timer_Init(1,5);    //ͬʱ��ʼ����ʱ��0��1����ʱ��0Ϊ1ms��������ʱ��1Ϊ5ms����
    EnableTimer0();     //������ʱ��1
    EnableTimer1();     //������ʱ��2
    
    DIRPID(50);         //��ʼ������pid��ͬʱ�趨�����м�ֵΪ50
    
    SPEEDPID();         //��ʼ���ٶ�pid
    speedinit = 80;     //��ʼ�ٶ�
    
    while(1)
    {
      
      
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
            
        }
        
        
        //LED_P6x8Str(5,1,"abc");
        //bt_go();//�������Ƴ���
     }
}

void Camera(void)
{
    if(Is_SendPhoto)
    { 
        //DisableInterrupts;
        //Cameraview();//��λ����ʾ����ͷͼƬ
        LocatingEye_OriginalImage_FixedThreshold_OledPrint();//�ű��ⷽʽ
        
        FPS++;
        //EnableInterrupts;   
    }

}

void position(void)             //�㷨ʶ���ű��λ��
{
    u16 z;
    
    dir[0][numb] = X_axis;      //x������
    dir[1][numb] = Y_axis;      //y������
    dir[2][numb] = Area;        //�����С
  
    if(dir[0][numb] != 0)//��¼��ʧ�ű�ǰ��ʮ֡����
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
        if(record[9] >= 60)//ȷ���ű궪ʧ
        {
            xb_lose = 1;
        }
        else
            xb_lose = 0;
        count = 0;
    }
    
    numb++;
    setfps = 3;//��Ҫ���ƽ�������֡��
    
    if(numb == setfps)//Ϊ����׼ȷʹ�ô˷���
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
        Areave = Areave/setfps;//ȡ��֡���ݣ������ƽ��ֵ
    }
    
}

void pidcontrol(void)//pid����С���Ķ�����ٶ�
{
  
//    direrr[2] = (direrr[1]*direrr[1]/direrr[0] + dirave)*1.2;
//    direrr[3] = (int)realizepid((float)direrr[2]);
//    direrr[2] = direrr[3] + dirave[0][0];
//    
//    if(dirave[0][0] >= 0 && dirave[0][0] <= 120)//��λ�ű���Ʒ���
//        dirturn = 760 - dirave[0][0];
//    else
//        if(dirave[0][0] > 120)
//            dirturn = 620;
//        else
//            dirturn = 740;
    
/***************************************************
                    ���Ʒ����㷨
***************************************************/
  
    if(Areave <= 10 && Areave > 0)//����С�����ű�ľ��������ʵ�ת����
        dirindex = Areave / 25;
    else
        if((Areave <= 60 && Areave > 10))
            dirindex = Areave / (25 + (Areave - 10) / 2);
        else
            dirindex = Areave / (50 + (Areave - 60) / 3);
    
    if(dirindex >= 1.6)//�����Ϊ1.6�����˶�����ܻᳬ����Χ
        dirindex = 1.6;
  
    if(xb_lose == 1)//�ű궪ʧ
    {
        dirturn = (int)(680 + dirpidturn((float)record[9]) * 1.6);
    }
    else
    {
        dirturn = (int)(680 + dirpidturn((float)dirave[0][0]) * dirindex);//��λ�ű���Ʒ���
    }
       
/***************************************************
                    �����ٶ��㷨
***************************************************/
    
    if(Areave >= 250 || dir[1][numb] >= 60)//�����ű�
    {  
        outspeedz = speedinit; 
        outspeedy = speedinit;
        if(dirave[0][0] <= 50)
            dirturn = 600; //��
        else
            dirturn = 760; //��
        Delay_MS(500);
    }
    
    if(record[10] <= 0)//������
    {
        if(Areave <= 200 && Areave > 50)//�ӽ��ű�
        {
            outspeedz = (int)(speedinit + (200 - Areave) * 0.5);//����С�����ٶ�
            outspeedy = (int)(speedinit + (200 - Areave) * 0.5);
        }
        
        if(Areave <= 50 && Areave > 0)//�����ű�Զ
        {
            outspeedz = (int)(speedinit + Areave * 1.6);//����С�����ٶ�
            outspeedy = (int)(speedinit + Areave * 1.6);
        }
    }
    else//������
    {
        outspeedz = speedinit;
        outspeedy = speedinit; 
    }
    
    if(Areave == 0)
    {
        if(xb_lose == 0)
        {
            dirturn = 760; //��
            outspeedz = speedinit - 20;
            outspeedy = speedinit + 10; //�����ű��Χ���ű�ת���ٶ�
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
//            dirturn = 600; //��
//            count = 0;
//        }
    }
    
    speedpidturn(outspeedz,record[10]);
    
    PWM_Output(PWM_PIN_PTA10,dirturn);//���ת��
    PWM_Output(PWM_PIN_PTA6,0);PWM_Output(PWM_PIN_PTA7,outspeedy);//����
    PWM_Output(PWM_PIN_PTA9,outspeedz);PWM_Output(PWM_PIN_PTA8,0);//����
    
}

void lcdshow()
{
    LED_PrintValueI(0,0,dirave[0][0]);//x������
    LED_PrintValueI(0,2,dirturn);//����
    LED_PrintValueI(0,4,(int)Areave);
    LED_PrintValueI(0,6,inspeedz);
    LED_PrintValueI(64,6,inspeedy);
        
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
      
/***************************************************
                    ��ȡ������ת��
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
//PIT�жϷ�����
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
  
    Cleartimer1();
}





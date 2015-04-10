/**
 * wdg.c file for STM32F103.
 * Describtion: wdg window module
 * Author: qinfei 2015.03.27
 * Version: GatewayV1.0
 * Support:qf.200806@163.com
 */
#include "wdg.h"
#include "leds.h"

/*����WWDG������������ֵ,Ĭ��Ϊ���.*/
u8 WWDG_CNT = 0x7f;

/**
 * ��ʼ�����ڿ��Ź�
 * tr: T[6:0] ���ڴ洢��������ֵ
 * wr: W[6:0] ���ڴ洰��ֵ
 * fprer: ���ڿ��Ź���ʵ�����ã���2λ��Ч
 * Fwwdg = PCLK1/4095/2^fprer
 */
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);//WWDGʱ��ʹ��
    WWDG_CNT=tr&WWDG_CNT;/*��ʼ��WWDG_CNT. */

    WWDG_SetPrescaler(fprer);//����IWDGԤ��Ƶֵ
    WWDG_SetWindowValue(wr);//���ô���ֵ95

    WWDG_Enable(WWDG_CNT);//ʹ�ܿ��Ź�,����counter.:127                 
    WWDG_ClearFlag();// Clear EWI flag 

    WWDG_NVIC_Init();//��ʼ�����ڿ��Ź� NVIC
    WWDG_EnableIT();//�������ڿ��Ź��ж�
} 

/*��ʼ�����ڿ��Ź� NVIC*/
void WWDG_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;//WWDG�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ2�������ȼ�3����2	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//��ռ2�������ȼ�3����2	
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
    NVIC_Init(&NVIC_InitStructure);//NVIC��ʼ��
}

/*���ڿ��Ź��жϷ������*/
void WWDG_IRQHandler(void)
{
    WWDG_SetCounter(WWDG_CNT);//���ڿ��Ź�ι��
    WWDG_ClearFlag();
    //LED1 = !LED1;
}















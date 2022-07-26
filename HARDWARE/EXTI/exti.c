#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

/**
************************************************************
* @file         
* @brief        
* @author    xiaoming
* @date       2022.2.12
* @version  ����V1.4 Ӳ��V1.4
* @note   �������ⲿ�жϳ�ʼ��
*
*
*
***********************************************************/

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��



   //GPIOA.12	  �ж����Լ��жϳ�ʼ������ �½��ش��� KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   //GPIOA.7	  �ж����Լ��жϳ�ʼ������ �����ش��� KEY1
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}
/**
* @brief ����KEY1 PA7 �жϴ�������
* @param 
* @return 
*/
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==1)	 //����KEY1 PA7
	{
		if(Mode == 4) Mode =1;
		else Mode = Mode +1;
		LED=!LED;

	}		 
	EXTI_ClearITPendingBit(EXTI_Line7);  //���LINE4�ϵ��жϱ�־λ  
}

/**
* @brief ����KEY2 PA12 �жϴ�������
* @param 
* @return 
*/
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	 //����KEY2
	{
		Mode = 0;
		LED=!LED;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line12);  //���LINE4�ϵ��жϱ�־λ  
}

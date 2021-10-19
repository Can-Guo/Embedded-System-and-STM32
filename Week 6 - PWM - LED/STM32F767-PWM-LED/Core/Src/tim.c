/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

//��ʱ��3���
TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
	//��ʼ����ʱ��PWM��ʱ������
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 100-1; //Ԥ��Ƶϵ��PRE
	htim3.Init.Period = 20000-1;   //ARR�Ĵ�����ֵ
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;  
	
	HAL_TIM_PWM_Init(&htim3);
	
	
	//��ʱ������Ƚϳ�ʼ���ṹ��
	
	TIM_OC_InitTypeDef oc_init;
	

	oc_init.Pulse = 10000; //�ȽϼĴ���CCR��ֵ   10000/20000 = 50%
	
	//���ռ�ձ�����Ҫ��˵�����
	
	oc_init.OCMode = TIM_OCMODE_PWM1;
	oc_init.OCPolarity = TIM_OCPOLARITY_LOW;   //���ڶ������Ҫ��Ϊ�ߵ�ƽ��Ч��oc_init.OCPolarity = TIM_OCPOLARITY_HIGH;
	
	//��ʼ��PWM������Ƚ�ͨ��
	
	HAL_TIM_PWM_ConfigChannel(&htim3,&oc_init,TIM_CHANNEL_4);	
	
	//ʹ�ܶ�ʱ����PWMͨ��
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	
	
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
	//ʹ�ܶ�ʱ��ʱ��ͨ����GPIOʱ��ͨ��
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//������Ӧ��GPIO
	GPIO_InitTypeDef gpio_struct;
	
	gpio_struct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	gpio_struct.Mode = GPIO_MODE_AF_PP;
	gpio_struct.Pull = GPIO_PULLUP;
	gpio_struct.Speed = GPIO_SPEED_FAST;
	gpio_struct.Alternate = GPIO_AF2_TIM3;
		
	//LED0,LED1
	HAL_GPIO_Init(GPIOB,&gpio_struct);
		
	gpio_struct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	
	//servo 0, servo 1
	HAL_GPIO_Init(GPIOA,&gpio_struct);
		
	

	
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

void PWM_Pulse_Config(TIM_HandleTypeDef htim,uint16_t ccr4) //,uint16_t ccr2,uint16_t ccr3,uint16_t ccr4)
{
	if(htim.Instance==TIM3)
	{

		TIM3->CCR4 = ccr4;
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

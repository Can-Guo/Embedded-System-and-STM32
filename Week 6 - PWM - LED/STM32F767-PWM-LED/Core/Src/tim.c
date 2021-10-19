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

//定时器3句柄
TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
	//初始化定时器PWM的时基部分
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 100-1; //预分频系数PRE
	htim3.Init.Period = 20000-1;   //ARR寄存器的值
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;  
	
	HAL_TIM_PWM_Init(&htim3);
	
	
	//定时器输出比较初始化结构体
	
	TIM_OC_InitTypeDef oc_init;
	

	oc_init.Pulse = 10000; //比较寄存器CCR的值   10000/20000 = 50%
	
	//舵机占空比是需要查说明书的
	
	oc_init.OCMode = TIM_OCMODE_PWM1;
	oc_init.OCPolarity = TIM_OCPOLARITY_LOW;   //对于舵机，需要改为高电平有效。oc_init.OCPolarity = TIM_OCPOLARITY_HIGH;
	
	//初始化PWM的输出比较通道
	
	HAL_TIM_PWM_ConfigChannel(&htim3,&oc_init,TIM_CHANNEL_4);	
	
	//使能定时器的PWM通道
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	
	
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
	//使能定时器时钟通道，GPIO时钟通道
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//配置相应的GPIO
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

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
#include "main.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 10000-1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 5000-1;
	
	
	HAL_TIM_Base_Init(&htim3);
	
	HAL_TIM_Base_Start_IT(&htim3);

	
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
	//使能时钟
	__HAL_RCC_TIM3_CLK_ENABLE();
	//中断
	HAL_NVIC_SetPriority(TIM3_IRQn,0,0);     
	HAL_NVIC_EnableIRQ(TIM3_IRQn); 


}


void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//用户自定义程序，LED，串口等
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	
	
}



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

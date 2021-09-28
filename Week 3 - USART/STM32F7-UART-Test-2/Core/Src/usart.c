/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;


/* USART1 init function */

void MX_USART1_UART_Init(void)
{
	huart1.Instance = USART1 ;
	
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Mode = UART_MODE_TX_RX ;
	huart1.Init.Parity = UART_PARITY_NONE ;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE ;
	
	HAL_UART_Init(&huart1);
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
	GPIO_InitTypeDef gpioa_init ;
	
	    /* USART1 clock enable */
  __HAL_RCC_USART1_CLK_ENABLE();

  __HAL_RCC_GPIOA_CLK_ENABLE();
	
	gpioa_init.Pin = GPIO_PIN_9 | GPIO_PIN_10 ;
	gpioa_init.Mode = GPIO_MODE_AF_PP ;
	gpioa_init.Pull = GPIO_NOPULL ;
	gpioa_init.Speed = GPIO_SPEED_HIGH;
	gpioa_init.Alternate = GPIO_AF7_USART1;
	
	
	
  HAL_GPIO_Init(GPIOA,&gpioa_init);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
 
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

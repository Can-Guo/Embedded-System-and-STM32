/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */

	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION12b;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.EOCSelection = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.NbrOfDiscConversion = 0;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	
	HAL_ADC_Init(&hadc1);
	
	
	ADC_ChannelConfTypeDef adc_channel;
	
	adc_channel.Channel = ADC_CHANNEL_TEMPSENSOR;
	adc_channel.Offset = 0;
	adc_channel.Rank = 1;
	adc_channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	
	HAL_ADC_ConfigChannel(&hadc1,&adc_channel);
	
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}


uint16_t Get_Temp_ADC(int times)
{
	
	float temp = 0.0;
	
	for(int t=0;t<times;t++)
	{	
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		temp += HAL_ADC_GetValue(&hadc1);
		HAL_Delay(10);
	}
	
	return (uint16_t) temp/times; // n次ADC的均值
}

float Get_Temp(int times)
{
	uint16_t Temp_adc = Get_Temp_ADC(times);
	
	// ADC值 -> 电压值 -> 温度
	float Temp_voltage = Temp_adc * 3.3 / 4096; //ADC值转换为电压值
 	float Temperature = (Temp_voltage - 0.76)/0.0025 + 25;   //根据电压值与温度的关系，得到温度值
	
	//LED提示
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
	HAL_Delay(200);
	
	return Temperature;
}



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

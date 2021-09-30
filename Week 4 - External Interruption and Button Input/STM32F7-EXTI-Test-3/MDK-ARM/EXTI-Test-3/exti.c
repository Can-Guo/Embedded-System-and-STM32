#include "main.h"
#include "exti.h"

void EXTI_Init(void)

{
	//使能时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	
	//初始化GPIO
	GPIO_InitTypeDef gpio_init_1;
	
	gpio_init_1.Pin = GPIO_PIN_0;
	gpio_init_1.Mode = GPIO_MODE_IT_RISING;
	gpio_init_1.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA,&gpio_init_1);
	
	gpio_init_1.Pin = GPIO_PIN_13;
	gpio_init_1.Mode = GPIO_MODE_IT_FALLING;
	gpio_init_1.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC,&gpio_init_1);
	
	gpio_init_1.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	HAL_GPIO_Init(GPIOH,&gpio_init_1);
	
	
		
	
	
	//配置中断优先级，使能中断通道
	HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	
	
}

void EXTI0_IRQHandler()           
{
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}


void EXTI2_IRQHandler()           
{
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}




void EXTI3_IRQHandler()           
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
	
}




void EXTI15_10_IRQHandler()           
{
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}


void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
	HAL_Delay(50);
	
	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:
		
			if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1)
			{
				//用户自定义功能1
				LED0_Flash;
			
			break;
			}
		

		case GPIO_PIN_2:
			
			if (HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)==0)
			{
				//用户自定义功能2
				LED1_Flash;
			
			break;
			}
			
		case GPIO_PIN_3:
			
			if (HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)==0)
			{
				//用户自定义功能3
				LED0_1_Flash;
			
			break;
			}
			
		case GPIO_PIN_13:
			
			if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0)
			{
				//用户自定义功能4
			
			break;
			}	
	
	}
	
}



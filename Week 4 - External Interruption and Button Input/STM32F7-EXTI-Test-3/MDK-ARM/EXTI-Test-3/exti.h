


#define LED0_Flash HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
#define LED1_Flash HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);

#define LED0_1_Flash {HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0); HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);}


void EXTI_Init(void);

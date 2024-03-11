/******************************************************************************
The program is built to handle the problem of changing LED status. The button
is configured for pin PC15 and changes the LED status at pin PC13.
Author: KhoiNT
******************************************************************************/

/******************************************************************************
	* Include
******************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdint.h"

/******************************************************************************
	* Prototype
******************************************************************************/
void RCC_Config(void);
void GPIO_Config(void);
void LED_toggle(void);

/******************************************************************************
	* Code
******************************************************************************/
int main() {
	RCC_Config();
	GPIO_Config();
	
	while(1) {
	 if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)) {
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15));
		LED_toggle();
	 }
	}

	return 0;
}

/**
  * @brief  Enables or disables peripheral clock.
  * @param  None.
  * @return None.
  */
void RCC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
						parameters in the GPIO_InitStruct.
  * @param  None.
  * @return None.
  */
void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	/* Config pin PC13 as Led's pin */
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* Config pin PC15 as Button's pin */
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
  * @brief  Toggle the LED.
  * @param  None.
  * @return None.
  */
//void LED_toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
void LED_toggle(void) {
	if ( GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13) ) {
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	} else {
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
}

/******************************************************************************
	* End of file
******************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdint.h"

void RCC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	/* Config pin PC13 as Led's pin */
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* Config pin PC5 as Button's pin */
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//void LED_toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
void LED_toggle(void) {
	if ( GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_13) ) {
		GPIO_ResetBits(GPIOA,GPIO_Pin_13);
	} else {
		GPIO_SetBits(GPIOA,GPIO_Pin_13);
	}
}

int main() {
	RCC_Config();
	GPIO_Config();
	
	while(1) {
	 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)) {
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5));
		LED_toggle();
	 }
	}

	return 0;
}
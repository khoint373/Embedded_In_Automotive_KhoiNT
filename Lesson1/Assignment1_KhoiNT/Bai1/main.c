#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdint.h"

void RCC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP; 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void delay(__IO uint32_t timedelay){ 
	for(int i=0; i<timedelay; i++){}
}

void LED_Chase(uint8_t count) {
	uint8_t index;
	uint8_t index1;
	uint8_t PortVal;
	
	for (index = 0; index < count ; index++) {
		PortVal = 0;
		
		for (index1 = 0; index1 < 4u; index1++) {
			GPIO_Write(GPIOB,PortVal);
			PortVal = PortVal << 1u;
			delay(5000000);
		}
	}
}

int main ( ) {
	RCC_Config();
	GPIO_Config();
	
	while (1) {
		LED_Chase(5u);
	}
}
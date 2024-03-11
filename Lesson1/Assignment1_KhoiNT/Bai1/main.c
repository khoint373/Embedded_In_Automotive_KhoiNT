/******************************************************************************
The program is written to perform the problem of making 5 LEDs chase 3 times.
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
	* Definition
******************************************************************************/
#define Times_Of_Chase        3u
#define TimeDelay             5000000u
#define Number_Of_Led         5u
/******************************************************************************
	* Prototype
******************************************************************************/
void RCC_Config(void);
void GPIO_Config(void);
void delay(__IO uint32_t timedelay);
void LED_Chase(uint8_t count);

/******************************************************************************
	* Code
******************************************************************************/
int main(void) {
	RCC_Config();
	GPIO_Config();
	
	while (1) {
		LED_Chase(Times_Of_Chase);
	}
}

/**
  * @brief  Enables or disables peripheral clock.
  * @param  None.
  * @return None.
  */
void RCC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
						parameters in the GPIO_InitStruct.
  * @param  None.
  * @return None.
  */
void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | \
																GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP; 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  Create a period of time to stop doing nothing.
  * @param  timedelay: a period of time to stop.
  * @return None
  */
void delay(__IO uint32_t timedelay){ 
	for(int i=0; i<timedelay; i++){}
}

/**
  * @brief  Create the LED chasing effect.
  * @param  count: number of times performed.
  * @return None
  */
void LED_Chase(uint8_t count) {
	uint8_t index;
	uint8_t index1;
	uint16_t PortVal;
	
	for (index = 0; index < count ; index++) {
		PortVal = 0x00;
		
		for (index1 = 0; index1 < Number_Of_Led; index1++) {
			PortVal = (1u << index1 );
			GPIO_Write(GPIOA,PortVal);
			delay(TimeDelay);
		}
	}
}

/******************************************************************************
	* End of file
******************************************************************************/
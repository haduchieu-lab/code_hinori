#include "uart.h"
//#include "nvic.h"
#include <string.h>


void USART_Config(void){
	
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	
	
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitTypeDefStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitTypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_3;	
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}



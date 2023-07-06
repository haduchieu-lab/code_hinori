#ifndef __UART_H
#define __UART_H
#endif

#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_gpio.h"

#define BAUDRATE 9600

void USART_Config(void);
//void USART_Print(const char* text);
//void USART_Println(const char* text);
//void Delay(uint16_t time);

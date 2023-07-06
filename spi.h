#ifndef __SPI_H
#define __SPI_H

#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_spi.h"
#include "stm32f0xx_dma.h"
#include "stdio.h"

#define			STATUS_ADDR					0
#define 		VOLT_IN_ADDR				2
#define 		AMP_IN_ADDR					4
#define 		VOLT_OUT1_ADDR			6
#define 		VOLT_OUT2_ADDR			8
#define 		TEMPERATURE_ADDR		10
#define			FREQUENCE_ADDR			11

void SPI_Config(void);
uint8_t SPI_Get_Status(void);
uint16_t SPI_Get_Voltage_In(void);
uint16_t SPI_Get_Amp_In(void);
uint16_t SPI_Get_Voltage_Out1(void);
uint16_t SPI_Get_Voltage_Out2(void);
uint8_t SPI_Get_Temperature(void);
uint8_t SPI_Get_Frequence(void);
void LCD_Calculator_WS(void);
#endif

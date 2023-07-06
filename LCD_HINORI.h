#ifndef __LCD_HINORI_H
#define __LCD_HINORI_H

#include "HT1623.h"
#include <stm32f0xx_tim.h>
#include <stm32f0xx.h>
#include <stm32f0xx_rcc.h>
#include "stm32f0xx_flash.h"
#include <stdbool.h>
#include <stdio.h>

#define INIT													0
#define	STANBY												1
#define	NORMAL_LOADING								2
#define	NORMAL_OVERVOLTAGE						3
#define	NORMAL_UNDERVOLTAGE						4
#define	NORMAL_OVERLOAD								5
#define	ABNORMAL_OVERVOLTAGE					6
#define	ABNORMAL_UNDERVOLTAGE					7
#define	ABNORMAL_OVERLOAD							8
#define	RESET													9
#define	ERROR													10

#define FLASH_PAGE_SIZE                ((uint16_t)0x400)
#define FLASH_PAGE_ADDR								 ((uint32_t)0x08003400)
#define WS_ADDR												 ((uint32_t)0x08003400)

#define BT_EN 												GPIO_Pin_0
#define PWEN													GPIO_Pin_1

void LCD_BEGIN(void);

void LCD_NORMAL_LOADING_MODE(void);
void LCD_NORMAL_OVERVOLTAGE_MODE(void);
void LCD_NORMAL_UNDERVOLTAGE_MODE(void);
void LCD_NORMAL_OVERLOAD_MODE(void);
void LCD_ABNORMAL_OVERVOLTAGE_MODE(void);
void LCD_ABNORMAL_UNDERVOLTAGE_MODE(void);
void LCD_ABNORMAL_OVERLOAD_MODE(void);
void LCD_INIT_MODE(void);
void LCD_STANBY_MODE(void);
void LCD_RESET_MODE(void);

void LCD_VOLTAGE_IN(void);
void LCD_AMP_IN(void);
void LCD_VOLTAGE_OUT1(void);
void LCD_VOLTAGE_OUT2(void);
void LCD_WAT_POWER(void);
void LCD_TEMPERATURE_FREQ(void);
void LCD_GRAPH(void);
void LCD_OVERVOLTAGE(void);

void LCD_INVERT_WAT_POWER(void);
void LCD_INVERT_TEMPERATURE_FREQ(void);
void LCD_INVERT_GRAPH(void);
void LCD_INVERT_OVERVOLTAGE(void);

void LCD_Set_Voltage_In(uint16_t _val);
void LCD_Set_Mode(uint8_t _mode);
void LCD_Set_Voltage_Out1(uint16_t _val);
void LCD_Set_Voltage_Out2(uint16_t _val);
void LCD_Set_Amp_In(uint16_t _val);
void LCD_Set_Temperature(uint8_t _val);
void LCD_Set_Frequence(uint8_t _val);
void LCD_Set_Wattage(uint32_t _wat);
void LCD_Save_WS(void);
void LCD_Clear_WS(void);
void LCD_Toggle_PWEN(void);
void LCD_Press_BTEN(void);
void LCD_Init_PWEN(void);
#endif

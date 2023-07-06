#ifndef __HT1623_H
#define __HT1623_H

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include <stdint.h>

#define SEG_A				0
#define SEG_B				1
#define SEG_C				2
#define SEG_D				3
#define SEG_E				4
#define SEG_F				5
#define SEG_G				6

#define DIGIT1_ADDR	0x00
#define DIGIT2_ADDR	0x04
#define DIGIT3_ADDR 0x08

#define DIGIT4_ADDR 0x40
#define DIGIT5_ADDR 0x44
#define DIGIT6_ADDR 0x48
#define DIGIT7_ADDR 0x4C

#define DIGIT8_ADDR 0x3C
#define DIGIT9_ADDR 0x38
#define DIGIT10_ADDR 0x34
#define DIGIT11_ADDR 0x30
#define DIGIT12_ADDR 0x2C

#define DIGIT13_ADDR 0x0C
#define DIGIT14_ADDR 0x10
#define DIGIT15_ADDR 0x14
#define DIGIT16_ADDR 0x18
#define DIGIT17_ADDR 0x1C
#define DIGIT18_ADDR 0x20
#define DIGIT19_ADDR 0x24
#define DIGIT20_ADDR 0x28

#define EN			 		 0x01
#define DIS		 			 0x00

#define CS					GPIO_Pin_10
#define WR					GPIO_Pin_9
#define DATA				GPIO_Pin_1

#define LCD_ON 			0x02
#define LCD_OFF 		0x03
#define SYS_EN 			0x01
#define TIMER_EN		0x06
#define NORMAL			0xE3
#define TONE_2K			0x60
#define RC_32				0x18


#define F1 					0xA0
#define F2 					0xA1
#define F4 					0xA2
#define F8 					0xA3
#define F16 				0xA4
#define F32 				0xA5
#define F64 				0xA6
#define F128				0xA7

#define WDT_EN			0x03
#define EXT_32K			0x1C

#define S0					0x01
#define S1					0x02
#define S2					0x04
#define S3					0x08
#define S4					0x10
#define S5					0x20
#define S6					0x40
#define S7					0x80

#define S8					0x01
#define S9					0x02
#define S10					0x04
#define S11					0x08
#define S12					0x10
#define R0					0x20
#define R1					0x40
#define R2					0x80

#define R3					0x01
#define DP					0x02




void HT1623_Config(void);
void HT1623_Begin(void);
void HT1623_WriteCmd(uint8_t cmd);
void HT1623_WriteData(uint8_t addr, uint8_t data);
void HT1623_CmdMode(void);
void HT1623_Digit_1(uint8_t _value, uint8_t _status, uint8_t _addr);
void HT1623_Digit_2(uint8_t _value, uint8_t _status, uint8_t _addr);
void HT1623_Digit_3(uint8_t _value, uint8_t _status, uint8_t _addr);
void HT1623_Digit_4(uint8_t _value, uint8_t _status, uint8_t _addr);
void HT1623_SR(int32_t _addr ,uint8_t _status, uint8_t _type);

void HT1623_ClearSR(void);
#endif

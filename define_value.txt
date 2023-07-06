#define SEG_A				0
#define SEG_B				1
#define SEG_C				2
#define SEG_D				3
#define SEG_E				4
#define SEG_F				5
#define SEG_G				6

#define   DIGIT1_ADDR	0x28// cụm thứ 2
#define	  DIGIT2_ADDR	0x30
#define   DIGIT3_ADDR	0x38

#define   DIGIT4_ADDR	0x40// cum thứ 3
#define   DIGIT5_ADDR	0x48
#define   DIGIT6_ADDR	0x50

#define   DIGIT7_ADDR	0x00 // cụm đầu tiên xuất hiện
#define   DIGIT8_ADDR	0x08
#define   DIGIT9_ADDR	0x10
#define   DIGIT10_ADDR	0x18
#define   DIGIT11_ADDR	0x20

#define   DIGIT12_ADDR	0x58// cụm thứ 4
#define   DIGIT13_ADDR	0x60
#define   DIGIT14_ADDR	0x68
#define   DIGIT15_ADDR	0x70

#define   DIGIT16_ADDR	0x78//cụm thứ 5
#define   DIGIT17_ADDR	0x80
#define   DIGIT18_ADDR	0x88

#define   DIGIT19_ADDR	0x90//cụm thứ 6
#define   DIGIT20_ADDR	0x98
#define   DIGIT21_ADDR	0xA0

#define   DIGIT22_ADDR	0xA8//cụm thứ 7
#define   DIGIT23_ADDR	0xB0
#define   DIGIT24_ADDR	0xB8

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


//chia nhỏ thành các cụm 8 bit, mỗi bit đại diện cho trạng thái đó

#define S5					0x01// bit 0
#define S6					0x02// bit 1
#define S7					0x04// bit 2
#define S8 					0x08// bit 3
#define S9					0x10// bit 4
#define S10					0x20// bit 5
#define S11					0x40// bit 6
#define S12					0x80// bit 7

#define S13					0x01
#define S14					0x02
#define S15					0x04
#define S16					0x08
#define S17					0x10
#define S18					0x20
#define S19					0x40
#define S20					0x80

#define R0					0x01
#define R1					0x02
#define R2					0x04
#define R3					0x08
#define P1					0x10
#define P2					0x20
#define P3					0x40
#define P4					0x80


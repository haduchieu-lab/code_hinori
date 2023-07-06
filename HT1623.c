#include "HT1623.h"

uint8_t temp;
uint8_t i;
uint8_t _seg;
uint8_t S_Flag_1 = 0;
uint8_t S_Flag_2 = 0;
uint8_t S_Flag_3 = 0;

void _delay(uint8_t time);
void _write_bit(uint8_t _bit);
uint8_t _convert_7_segment(uint8_t _value);
void _enCS(void);
void _disCS(void);
void _cmdMode(void);
void _writeCmd(uint8_t cmd);


void HT1623_Config(void){
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = CS;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDefStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitTypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = WR;
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = DATA;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDefStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitTypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitTypeDefStructure);	
	
	GPIO_SetBits(GPIOA, CS);
	GPIO_SetBits(GPIOA, WR);
	GPIO_SetBits(GPIOB, DATA);
	
}

void HT1623_Begin(void){
	_enCS();	
	_cmdMode();
	_writeCmd(SYS_EN);	
	_writeCmd(RC_32);	
	_writeCmd(F128);	
	_writeCmd(TIMER_EN);	
	_writeCmd(WDT_EN);
	//_writeCmd(TONE_2K);
	_disCS();
}


void _cmdMode(void){
	_write_bit(1);
	_write_bit(0);
	_write_bit(0);
}

void _writeMode(void){
	_write_bit(1);
	_write_bit(0);
	_write_bit(1);
}

void _enCS(void){
	GPIO_ResetBits(GPIOA, CS);
}

void _disCS(void){
	GPIO_SetBits(GPIOA, CS);	
	GPIO_SetBits(GPIOB, DATA);	
}

void _writeCmd(uint8_t cmd){
	temp = 0x80;	
	for(i=0; i<8; i++){
		_write_bit(temp & cmd);
		temp = temp >> 1;	
	}	
	_write_bit(0);	
	GPIO_ResetBits(GPIOA, WR);	
}


void HT1623_WriteData(uint8_t addr, uint8_t data){	
	temp = 0x40;	
	for(i=0; i<7; i++){
		_write_bit(temp & addr);
		temp = temp >> 1;	
	}	
	temp = 0x01;
	for(i=0; i<4; i++){
		_write_bit(temp & data);
		temp = temp << 1;	
	}	
}

void HT1623_Digit_1(uint8_t _value, uint8_t _status, uint8_t _addr){

	_seg = _convert_7_segment(_value);		
	_enCS();
	_writeMode();	
	temp = 0x40;		
	
	for(i=0; i<7; i++){
		_write_bit(_addr & temp);
		temp = temp >> 1;	
	}	
	
	if(_status == DIS){
		for(i=0; i<12; i++)
			_write_bit(0);
		_disCS();	
		return;
	}
	
	temp = 0x01;
	
	_write_bit(_seg & (temp << SEG_D));
	_write_bit(_seg & (temp << SEG_E));
	_write_bit(_seg & (temp << SEG_F));
	_write_bit(_seg & (temp << SEG_A));
	
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	
	
	if(_addr == DIGIT1_ADDR)
		_write_bit(S_Flag_1 & S1);
	else if(_addr == DIGIT3_ADDR)
		_write_bit(S_Flag_1 & S0);
	else
		_write_bit(0);
	
	_write_bit(_seg & (temp << SEG_C));
	_write_bit(_seg & (temp << SEG_G));
	_write_bit(_seg & (temp << SEG_B));
	_disCS();	
}

void HT1623_Digit_2(uint8_t _value, uint8_t _status, uint8_t _addr){	
	
	_seg = _convert_7_segment(_value);		
	_enCS();
	_writeMode();	
	temp = 0x40;		
	
	for(i=0; i<7; i++){
		_write_bit(_addr & temp);
		temp = temp >> 1;	
	}	
	
	
	if(_status == DIS){
		for(i=0; i<12; i++)
			_write_bit(0);
		_disCS();	
		return;
	}
	
	
	temp = 0x01;
	
	_write_bit(_seg & (temp << SEG_D));
	_write_bit(_seg & (temp << SEG_A));
	_write_bit(_seg & (temp << SEG_F));
	_write_bit(_seg & (temp << SEG_E));
	
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	
	if(_addr ==  DIGIT13_ADDR)
		_write_bit(S_Flag_1 & S6);
	else if(_addr == DIGIT14_ADDR)
		_write_bit(S_Flag_1 & S5);
	else if(_addr == DIGIT15_ADDR)
		_write_bit(S_Flag_2 & R1);
	else if(_addr == DIGIT16_ADDR)
		_write_bit(S_Flag_1 & S2);
	else if(_addr == DIGIT17_ADDR)
		_write_bit(S_Flag_2 & S11);
	else if(_addr == DIGIT18_ADDR)
		_write_bit(S_Flag_1 & S4);
	else if(_addr == DIGIT19_ADDR)
		_write_bit(S_Flag_1 & S3);
	else if(_addr == DIGIT20_ADDR)
		_write_bit(S_Flag_2 & S12);

	
	_write_bit(_seg & (temp << SEG_B));
	_write_bit(_seg & (temp << SEG_G));
	_write_bit(_seg & (temp << SEG_C));
	_disCS();	
}


void HT1623_Digit_3(uint8_t _value, uint8_t _status, uint8_t _addr){

	_seg = _convert_7_segment(_value);	
	_enCS();
	_writeMode();	
	temp = 0x40;		
	
	for(i=0; i<7; i++){
		_write_bit(_addr & temp);
		temp = temp >> 1;	
	}	
	
	if(_status == DIS){
		for(i=0; i<12; i++)
			_write_bit(0);
		_disCS();	
		return;
	}
	
	temp = 0x01;
	
	if(_addr == DIGIT12_ADDR )
		_write_bit(S_Flag_2 & S8);
	else if(_addr == DIGIT11_ADDR)
		_write_bit(S_Flag_1 & S7);
	else if(_addr == DIGIT10_ADDR)
		_write_bit(S_Flag_2 & R0);
	else if(_addr == DIGIT9_ADDR)
		_write_bit(S_Flag_2 & S9);
	else if(_addr == DIGIT8_ADDR)
		_write_bit(S_Flag_2 & S10);
	
	_write_bit(_seg & (temp << SEG_C));
	_write_bit(_seg & (temp << SEG_G));
	_write_bit(_seg & (temp << SEG_B));
	
	
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	
	_write_bit(_seg & (temp << SEG_A));
	_write_bit(_seg & (temp << SEG_D));
	_write_bit(_seg & (temp << SEG_E));
	_write_bit(_seg & (temp << SEG_F));
	_disCS();	
}

void HT1623_Digit_4(uint8_t _value, uint8_t _status, uint8_t _addr){
	
	_seg = _convert_7_segment(_value);	
	_enCS();
	_writeMode();	
	temp = 0x40;		
	
	for(i=0; i<7; i++){
		_write_bit(_addr & temp);
		temp = temp >> 1;	
	}	
	
	
	if(_status == DIS){
		for(i=0; i<12; i++)
			_write_bit(0);
		_disCS();	
		return;
	}
	
	temp = 0x01;
	
	_write_bit(_seg & (temp << SEG_D));
	_write_bit(_seg & (temp << SEG_A));
	_write_bit(_seg & (temp << SEG_F));
	_write_bit(_seg & (temp << SEG_E));
	
	
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	_write_bit(0);
	
	if(_addr == DIGIT5_ADDR)
		_write_bit(S_Flag_3 & DP);
	else if(_addr == DIGIT6_ADDR)
		_write_bit(S_Flag_3 & R3);
	else if(_addr == DIGIT7_ADDR)
		_write_bit(S_Flag_2 & R2);
	else if(_addr == DIGIT4_ADDR)
		_write_bit(0);
	
	_write_bit(_seg & (temp << SEG_B));
	_write_bit(_seg & (temp << SEG_G));
	_write_bit(_seg & (temp << SEG_C));
	_disCS();	
}


uint8_t _convert_7_segment(uint8_t _value){
	if(_value == 0)
		return 0x3F;
	else if(_value == 1)
		return 0x06;
	else if(_value == 2)
		return 0x05B;
	else if(_value == 3)
		return 0x4F;
	else if(_value == 4)
		return 0x66;
	else if(_value == 5)
		return 0x6D;
	else if(_value == 6)
		return 0x7D;
	else if(_value == 7)
		return 0x07;
	else if(_value == 8)
		return 0x7F;
	else if(_value == 9)
		return 0x6F;
	else
		return 0x77;
	
}

void _write_bit(uint8_t _bit){
	
	GPIO_ResetBits(GPIOA, WR);
	
	if(_bit == 0)
		GPIO_ResetBits(GPIOB, DATA);
	else
		GPIO_SetBits(GPIOB, DATA);
	_delay(1);
	GPIO_SetBits(GPIOA, WR);
	_delay(1);
}


void _delay(uint8_t time){
	uint32_t time_n = time * 10;
	while(time_n > 0){
		time_n--;
	}
}

void HT1623_SR(int32_t _addr ,uint8_t _status, uint8_t _type){
	if(_status){
		if(_type == 0)
			S_Flag_1 = S_Flag_1 | _addr;
		else if(_type == 1)
			S_Flag_2 = S_Flag_2 | _addr;
		else	
			S_Flag_3 = S_Flag_3 | _addr;
	}
		
	else{
		if(_type == 0)
			S_Flag_1 = S_Flag_1 & ~_addr;
		else if(_type == 1)
			S_Flag_2 = S_Flag_2 & ~_addr;
		else	
			S_Flag_3 = S_Flag_3 & ~_addr;
	}
		
}

void HT1623_ClearSR(void){
	S_Flag_1 = 0;
	S_Flag_2 = 0;
	S_Flag_3 = 0;
}

#include "LCD_HINORI.h"


uint16_t 			_amp_in 					= 0;
uint16_t 			_voltage_in 			= 0;
uint16_t			_voltage_out1 		= 0;
uint16_t			_voltage_out2 		= 0;
uint32_t 			_wattage 					= 0;
uint32_t 			_ws 							= 0;
uint8_t				_temperature 			= 0;
uint8_t				_frequence 				= 0;

uint8_t				_power_flag 			= 0;
uint8_t				_freq_flag 				= 0;
uint8_t				_graph_flag				= 0;
uint8_t				_overvoltage_flag					= 0;

uint8_t 			_temp_lcd;
uint32_t      _temp_lcd_2;
uint8_t 			_mode 						= INIT;
NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;


void 			_reset(void);
void 			_start(void);
uint32_t 	_get_ws(void);
//uint8_t		_btnFlag = 0;
uint16_t		_countPressBTN = 0;


static void _delayMS(uint16_t time){
	uint32_t time_n=  time*1600;
	while(time_n != 0)	{time_n--;}

}

void LCD_Press_BTEN(void){
	if(GPIO_ReadInputDataBit(GPIOA, BT_EN) == 0){	
		_countPressBTN += 1;
	}
	
}


void LCD_Toggle_PWEN(void){
	if(_countPressBTN > 50 && _countPressBTN < 5000){
		if(GPIO_ReadInputDataBit(GPIOA, BT_EN) == 1){
			_countPressBTN = 0;
			GPIO_WriteBit(GPIOA, PWEN,(BitAction)~GPIO_ReadOutputDataBit(GPIOA, PWEN));
		}
	}
	else if(_countPressBTN == 1){
		LCD_Clear_WS();
		printf("7");
	}
	else if(_countPressBTN > 5000){
		if(GPIO_ReadInputDataBit(GPIOA, BT_EN) == 1){
			_countPressBTN = 0;
		}
	}
}

void LCD_Init_PWEN(void){
	GPIO_WriteBit(GPIOA, PWEN,(BitAction)SET);
}

void LCD_BEGIN(void){
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitTypeDefStructure.GPIO_Pin = BT_EN;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IN;	
	GPIO_InitTypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = PWEN;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDefStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitTypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	HT1623_Config();
	HT1623_Begin();
	
	/* TIM3 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);

	 /* Enable the TIM1 gloabal Interrupt */	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 1000;
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 3000;
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* Enable the TIM14 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 2000;
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	/* Enable the TIM16 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 500;
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);
	
	/* Enable the TIM17 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM17_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 500;
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM3, ENABLE);
	
	TIM_ClearFlag(TIM14, TIM_FLAG_Update);
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM14, ENABLE);

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1, ENABLE);

	TIM_ClearFlag(TIM16, TIM_FLAG_Update);
	TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);
	
	TIM_ClearFlag(TIM17, TIM_FLAG_Update);
	TIM_ITConfig(TIM17, TIM_IT_Update, ENABLE);
}

void LCD_NORMAL_LOADING_MODE(void){
	
	_reset();
	_mode = NORMAL_LOADING;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	HT1623_SR(S2, DIS, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S4, EN, 0);
	HT1623_SR(S9, DIS, 1);
	HT1623_SR(S10, DIS, 1);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);
	HT1623_SR(DP, EN, 2);
	HT1623_SR(R0, EN, 1);
	
	_start();
}



void LCD_NORMAL_OVERVOLTAGE_MODE(void){
	
	_reset();
	_mode = NORMAL_OVERVOLTAGE;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);	
	HT1623_SR(S2, DIS, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S4, EN, 0);	
	HT1623_SR(S9, EN, 1);
	HT1623_SR(S10, DIS, 0);	
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);	
	HT1623_SR(DP, EN, 2);
	HT1623_SR(R0, EN, 1);	
	_start();
}

void LCD_NORMAL_UNDERVOLTAGE_MODE(void){
	
	_reset();
	_mode = NORMAL_UNDERVOLTAGE;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	
	HT1623_SR(S4, EN, 0);
	
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);
	HT1623_SR(DP, EN, 2);
	HT1623_SR(R0, EN, 1);
	
	HT1623_SR(S2, DIS, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S9, DIS, 1);
	
	_start();
}

void LCD_NORMAL_OVERLOAD_MODE(void){
	
	_reset();
	_mode = NORMAL_OVERLOAD;
	
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	HT1623_SR(S2, EN, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S4, EN, 0);
	
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);
	HT1623_SR(DP, EN, 2);
	HT1623_SR(R0, EN, 1);
	
	HT1623_SR(S9, DIS, 1);
	HT1623_SR(S10, DIS, 1);

	_start();
}

void LCD_ABNORMAL_OVERVOLTAGE_MODE(void){
	
	
	_reset();
	_mode = ABNORMAL_OVERVOLTAGE;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	HT1623_SR(S2, DIS, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S4, DIS, 0);
	HT1623_SR(S9, EN, 1);
	HT1623_SR(S10, DIS, 1);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);		
	HT1623_SR(R0, DIS, 1);
	HT1623_SR(R1, DIS, 1);
	HT1623_SR(R2, DIS, 1);
	HT1623_SR(R3, DIS, 2);
	HT1623_SR(DP, EN, 2);
	
	_start();
}

void LCD_ABNORMAL_UNDERVOLTAGE_MODE(void){
	
	_reset();
	_mode = ABNORMAL_UNDERVOLTAGE;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	HT1623_SR(S2, DIS, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S4, DIS, 0);
	HT1623_SR(S9, DIS, 1);
	HT1623_SR(S10, EN, 1);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);		
	HT1623_SR(R0, DIS, 1);
	HT1623_SR(R1, DIS, 1);
	HT1623_SR(R2, DIS, 1);
	HT1623_SR(R3, DIS, 2);
	HT1623_SR(DP, EN, 2);

	_start();
}

void LCD_ABNORMAL_OVERLOAD_MODE(void){
	
	_reset();
	_mode = ABNORMAL_OVERLOAD;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	HT1623_SR(S2, EN, 0);
	HT1623_SR(S3, DIS, 0);
	HT1623_SR(S4, DIS, 0);
	HT1623_SR(S9, DIS, 1);
	HT1623_SR(S10, DIS, 1);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);		
	HT1623_SR(R0, DIS, 1);
	HT1623_SR(R1, DIS, 1);
	HT1623_SR(R2, DIS, 1);
	HT1623_SR(R3, DIS, 2);
	HT1623_SR(DP, EN, 2);

	_start();
}

void LCD_INIT_MODE(void){
	
	_reset();
	_mode = INIT;
	
	HT1623_SR(S0, EN, 0);
	HT1623_SR(S1, EN, 0);
	HT1623_SR(S2, EN, 0);
	HT1623_SR(S3, EN, 0);
	HT1623_SR(S4, EN, 0);
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 1);
	HT1623_SR(S10, EN, 1);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, EN, 1);		
	HT1623_SR(R0, EN, 1);
	HT1623_SR(R1, EN, 1);
	HT1623_SR(R2, EN, 1);
	HT1623_SR(R3, EN, 2);
	HT1623_SR(DP, EN, 2);
	
	_wattage = 88888;
	_ws = 88888;
	_frequence = 88;
	_temperature = 88;
	_voltage_in = 888;
	_voltage_out1 = 888;
	_voltage_out2 = 888;
	_amp_in = 8888;
	
	_start();
	
}

void LCD_STANBY_MODE(void){
	
	_reset();
	_mode = STANBY;
	
	HT1623_SR(S0, DIS, 0);
	HT1623_SR(S1, DIS, 0);
	HT1623_SR(S2, DIS, 0);
	HT1623_SR(S3, EN, 0);
	HT1623_SR(S4, DIS, 0);
//	HT1623_SR(S5, EN, 0);
//	HT1623_SR(S6, EN, 0);
//	HT1623_SR(S7, EN, 0);
//	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, DIS, 1);
	HT1623_SR(S10, DIS, 1);
	HT1623_SR(S11, EN, 1);
	HT1623_SR(S12, DIS, 1);		
	HT1623_SR(R0, DIS, 1);
	HT1623_SR(R1, DIS, 1);
	HT1623_SR(R2, DIS, 1);
	HT1623_SR(R3, DIS, 2);
	HT1623_SR(DP, EN, 2);

	_start();
}

void LCD_RESET_MODE(void){
	
	
	_reset();
	_mode = RESET;
	
	HT1623_Digit_1(0, DIS, DIGIT1_ADDR);
	HT1623_Digit_1(0, DIS, DIGIT2_ADDR);
	HT1623_Digit_1(0, DIS, DIGIT3_ADDR);
	
	HT1623_Digit_2(0, DIS, DIGIT4_ADDR);
	HT1623_Digit_2(0, DIS, DIGIT5_ADDR);
	HT1623_Digit_2(0, DIS, DIGIT6_ADDR);
	HT1623_Digit_2(0, DIS, DIGIT7_ADDR);
	
	HT1623_Digit_3(0, DIS, DIGIT8_ADDR);
	HT1623_Digit_3(0, DIS, DIGIT9_ADDR);
	HT1623_Digit_3(0, DIS, DIGIT10_ADDR);
	HT1623_Digit_3(0, DIS, DIGIT11_ADDR);
	HT1623_Digit_3(0, DIS, DIGIT12_ADDR);
	
	HT1623_Digit_4(0, DIS, DIGIT13_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT14_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT15_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT16_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT17_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT18_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT19_ADDR);
	HT1623_Digit_4(0, DIS, DIGIT20_ADDR);
	
//	_start();
}

void LCD_VOLTAGE_IN(void){

	HT1623_Digit_1(_voltage_in % 10, EN, DIGIT3_ADDR);
	HT1623_Digit_1((_voltage_in % 100) / 10, EN, DIGIT2_ADDR);
	HT1623_Digit_1(_voltage_in / 100, EN, DIGIT1_ADDR);
	
}

void LCD_AMP_IN(void){
	
	if(_amp_in > 9999){
		HT1623_SR(DP, DIS, 2);
		_temp_lcd_2 = _amp_in / 100;
	}
	else{
		HT1623_SR(DP, EN, 2);
		_temp_lcd_2 = _amp_in;
	}
		

	HT1623_Digit_4((_temp_lcd_2) % 10, EN, DIGIT7_ADDR);	
	HT1623_Digit_4((_temp_lcd_2 / 10) % 10, EN, DIGIT6_ADDR);	
	HT1623_Digit_4((_temp_lcd_2 / 100) % 10, EN, DIGIT5_ADDR);
	HT1623_Digit_4((_temp_lcd_2 / 1000) % 10, EN, DIGIT4_ADDR);
}

void LCD_VOLTAGE_OUT1(void){

	HT1623_Digit_2( (_voltage_out1) % 10, EN, DIGIT17_ADDR);	
	HT1623_Digit_2((_voltage_out1 / 10) % 10, EN, DIGIT16_ADDR);	
	HT1623_Digit_2((_voltage_out1 / 100) % 10, EN, DIGIT15_ADDR);
	
}

void LCD_VOLTAGE_OUT2(void){

	HT1623_Digit_2((_voltage_out2) % 10, EN, DIGIT20_ADDR);
	HT1623_Digit_2((_voltage_out2 / 10) % 10, EN, DIGIT19_ADDR);	
	HT1623_Digit_2((_voltage_out2 / 100) % 10, EN, DIGIT18_ADDR);
	
}

void LCD_WAT_POWER(void){

	if(_power_flag == 0){
		HT1623_SR(S7, EN, 0);
		HT1623_SR(S8, DIS, 1);		
		_temp_lcd_2 = _wattage;
	}
	else{		
		HT1623_SR(S7, DIS, 0);
		HT1623_SR(S8, EN, 1);
		_temp_lcd_2 = _ws / 3600000;
	}
	if(_mode == INIT){
		HT1623_SR(S7, EN, 0);
		HT1623_SR(S8, EN, 1);
	}
	_temp_lcd = _temp_lcd_2 % 10;
	HT1623_Digit_3(_temp_lcd, EN, DIGIT12_ADDR);
	
	_temp_lcd = (_temp_lcd_2 / 10) % 10;
	HT1623_Digit_3(_temp_lcd, EN, DIGIT11_ADDR);
	
	_temp_lcd = (_temp_lcd_2 / 100) % 10;
	HT1623_Digit_3(_temp_lcd, EN, DIGIT10_ADDR);
	
	_temp_lcd = (_temp_lcd_2 / 1000) % 10;
	HT1623_Digit_3(_temp_lcd, EN, DIGIT9_ADDR);
	
	_temp_lcd = (_temp_lcd_2 / 10000) % 10;
	HT1623_Digit_3(_temp_lcd, EN, DIGIT8_ADDR);
	
	
}

void LCD_TEMPERATURE_FREQ(void){
	if(_freq_flag == 0){
		HT1623_SR(S5, EN, 0);
		HT1623_SR(S6, DIS, 0);
		_temp_lcd_2 = _temperature;
	}
	else{
		HT1623_SR(S5, DIS, 0);
		HT1623_SR(S6, EN, 0);
		_temp_lcd_2 = _frequence;
	}
	
	if(_mode == INIT){
		HT1623_SR(S5, EN, 0);
		HT1623_SR(S6, EN, 0);
	}
	HT1623_Digit_2((_temp_lcd_2 % 10), EN, DIGIT14_ADDR);
	HT1623_Digit_2((_temp_lcd_2 /10) % 10, EN, DIGIT13_ADDR);
	
}

void LCD_GRAPH(void){
	if(_mode > NORMAL_OVERLOAD || _mode < NORMAL_LOADING)
		return;
	if(_graph_flag == 0){
		HT1623_SR(R1, EN, 1);
		HT1623_SR(R2, DIS, 1);
		HT1623_SR(R3, DIS, 2);
	}
	else if(_graph_flag == 1){
		HT1623_SR(R1, DIS, 1);
		HT1623_SR(R2, EN, 1);
		HT1623_SR(R3, DIS, 2);
	}
	else{
		HT1623_SR(R1, DIS, 1);
		HT1623_SR(R2, DIS, 1);
		HT1623_SR(R3, EN, 2);
	}
	LCD_AMP_IN();
	LCD_VOLTAGE_OUT1();	
}

void LCD_OVERVOLTAGE(void){
	if(_overvoltage_flag == 0){
		if(_mode == NORMAL_OVERVOLTAGE)
			HT1623_SR(S9, EN, 1);
		else if(_mode == NORMAL_UNDERVOLTAGE)
			HT1623_SR(S10, EN, 1);
		else if(_mode == NORMAL_OVERLOAD)
			HT1623_SR(S2, EN, 0);
		
	}
	else{
		if(_mode == NORMAL_OVERVOLTAGE)
			HT1623_SR(S9, DIS, 1);
		else if(_mode == NORMAL_UNDERVOLTAGE)
			HT1623_SR(S10, DIS, 1);
		else if(_mode == NORMAL_OVERLOAD)
			HT1623_SR(S2, DIS, 0);
	}
	LCD_WAT_POWER();
	LCD_VOLTAGE_OUT1();
	
}

void LCD_INVERT_WAT_POWER(void){
	_power_flag = ~_power_flag;
}

void LCD_INVERT_TEMPERATURE_FREQ(void){
	_freq_flag = ~_freq_flag;
}

void LCD_INVERT_GRAPH(void){
	_graph_flag = _graph_flag + 1;
	if(_graph_flag == 3)
		_graph_flag = 0;
}
void LCD_INVERT_OVERVOLTAGE(void){
	_overvoltage_flag = ~_overvoltage_flag;
}

void LCD_Set_Voltage_In(uint16_t _val){
	if(_val == _voltage_in)
		return;
	_voltage_in = _val;
	_wattage = _voltage_in * _amp_in / 100;
	LCD_VOLTAGE_IN();
	LCD_WAT_POWER();
}

void LCD_Set_Mode(uint8_t _mode_spi){
	
	if(_mode_spi == _mode)
		return;
	
	
	if(_mode_spi == INIT)
		LCD_INIT_MODE();
	else if(_mode_spi == RESET)
		LCD_RESET_MODE();
	else if(_mode_spi == STANBY)
		LCD_STANBY_MODE();
	else if(_mode_spi == NORMAL_LOADING)
		LCD_NORMAL_LOADING_MODE();
	else if(_mode_spi == NORMAL_OVERVOLTAGE)
		LCD_NORMAL_OVERVOLTAGE_MODE();
	else if(_mode_spi == NORMAL_UNDERVOLTAGE)
		LCD_NORMAL_UNDERVOLTAGE_MODE();
	else if(_mode_spi == NORMAL_OVERLOAD)
		LCD_NORMAL_OVERLOAD_MODE();
	else if(_mode_spi == ABNORMAL_OVERVOLTAGE)
		LCD_ABNORMAL_OVERVOLTAGE_MODE();
	else if(_mode_spi == ABNORMAL_UNDERVOLTAGE)
		LCD_ABNORMAL_UNDERVOLTAGE_MODE();
	else if(_mode_spi == ABNORMAL_OVERLOAD)
		LCD_ABNORMAL_OVERLOAD_MODE();
	else 
		LCD_NORMAL_LOADING_MODE();
	
}

void LCD_Set_Voltage_Out1(uint16_t _val){
	if(_val == _voltage_out1)
		return;
	_voltage_out1 = _val;
	LCD_VOLTAGE_OUT1();
}

void LCD_Set_Voltage_Out2(uint16_t _val){
	if(_val == _voltage_out2)
		return;
	_voltage_out2 = _val;
	LCD_VOLTAGE_OUT2();
}

void LCD_Set_Amp_In(uint16_t _val){
	if(_val == _amp_in)
		return;
	_amp_in = _val;
	_wattage = _voltage_in * _amp_in / 100;
	LCD_AMP_IN();
	LCD_WAT_POWER();
}

void LCD_Set_Temperature(uint8_t _val){
	if(_val == _temperature)
		return;
	_temperature = _val;
	LCD_TEMPERATURE_FREQ();
}

void LCD_Set_Frequence(uint8_t _val){
	if(_val == _frequence)
		return;
	_frequence = _val;
	LCD_TEMPERATURE_FREQ();
}

void LCD_Set_Wattage(uint32_t _wat){
	if(_wat == _wattage )
		return;
	_wattage = _wat;
}

void LCD_Calculator_WS(void){
	_ws += _voltage_in * _amp_in / 100;
}
void LCD_Save_WS(void){
	if(_mode == INIT || _mode == RESET)
			return;
	FLASH_Unlock();
	while(FLASH_ErasePage(FLASH_PAGE_ADDR) != FLASH_COMPLETE);	
	while(FLASH_ProgramWord(WS_ADDR, _ws) != FLASH_COMPLETE);
	FLASH_Lock();
}

uint32_t _get_ws(void){
	return (uint32_t)(*(__IO uint32_t*) WS_ADDR);
}

void _reset(void){
	HT1623_ClearSR();
	TIM_Cmd(TIM3, DISABLE);
	TIM_Cmd(TIM14, DISABLE);
	TIM_Cmd(TIM1, DISABLE);
	TIM_Cmd(TIM16, DISABLE);
	TIM_Cmd(TIM17, DISABLE);
	if(_mode != INIT & _mode != RESET & _mode != STANBY)
		LCD_Save_WS();
	_wattage = 0;
	_ws = 0;
	_frequence = 0;
	_temperature = 0;
	_voltage_in = 0;
	_voltage_out1 = 0;
	_voltage_out2 = 0;
	_amp_in = 0;
	_power_flag = 0;
	_freq_flag = 0;
	_graph_flag = 0;
	_overvoltage_flag = 0;
}

void _start(void){
	
	LCD_VOLTAGE_IN();
	LCD_AMP_IN();
	LCD_VOLTAGE_OUT1();
	LCD_VOLTAGE_OUT2();
	LCD_WAT_POWER();
	LCD_TEMPERATURE_FREQ();
	LCD_GRAPH();
	if(_mode != INIT & _mode != RESET){
		TIM_Cmd(TIM3, ENABLE);
		TIM_Cmd(TIM14, ENABLE);
		TIM_Cmd(TIM1, ENABLE);
		_ws = _get_ws();
	}

	if(_mode == NORMAL_OVERVOLTAGE || _mode == NORMAL_UNDERVOLTAGE || _mode == NORMAL_OVERLOAD || _mode == NORMAL_LOADING)
		TIM_Cmd(TIM16, ENABLE);
	
	if(_mode == NORMAL_OVERVOLTAGE || _mode == NORMAL_UNDERVOLTAGE || _mode == NORMAL_OVERLOAD)
		TIM_Cmd(TIM17, ENABLE);

}

void LCD_Clear_WS(void){
	FLASH_Unlock();
	while(FLASH_ErasePage(FLASH_PAGE_ADDR) != FLASH_COMPLETE);	
	while(FLASH_ProgramWord(WS_ADDR, (uint32_t)0) != FLASH_COMPLETE);
	FLASH_Lock();
}

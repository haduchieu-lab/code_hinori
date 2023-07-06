#include "spi.h"

uint8_t _receive_buffer[12];

void _delay_ms(uint16_t time);

void SPI_Config(void){
	SPI_InitTypeDef SPI_InitTypeDefStructure;
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*		Configuration GPIO of SPI		*/
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitTypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitTypeDefStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_5;	
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_6;	
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_InitTypeDefStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_Init(GPIOA, &GPIO_InitTypeDefStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);
	
	/*					Configuration DMA							*/
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr 				= (uint32_t)&(SPI1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr 						= (uint32_t)&_receive_buffer;
	DMA_InitStructure.DMA_DIR 											= DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize 								= 12;
	DMA_InitStructure.DMA_PeripheralInc 						= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 								= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize 				= DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 						= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode 											= DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority 									= DMA_Priority_High;
	DMA_InitStructure.DMA_M2M 											= DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel2, ENABLE);
	
	
	/*					Configuration SPI1						*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_I2S_DeInit(SPI1);
	SPI_InitTypeDefStructure.SPI_Direction 					= SPI_Direction_1Line_Rx;
	SPI_InitTypeDefStructure.SPI_Mode 							= SPI_Mode_Slave;
	SPI_InitTypeDefStructure.SPI_DataSize 					= SPI_DataSize_16b;
	SPI_InitTypeDefStructure.SPI_CPOL 							= SPI_CPOL_Low;
	SPI_InitTypeDefStructure.SPI_CPHA 							= SPI_CPHA_1Edge;
	SPI_InitTypeDefStructure.SPI_NSS 								= SPI_NSS_Hard;
	SPI_InitTypeDefStructure.SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_16;
	SPI_InitTypeDefStructure.SPI_FirstBit 					= SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitTypeDefStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
//	SPI_SSOutputCmd(SPI1, ENABLE);
//	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
//	SPI_NSSPulseModeCmd(SPI1, ENABLE);
//	SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_Rx);
	DMA_ITConfig(DMA1_Channel2, DMA_IT_HT, ENABLE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
	//SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	SPI_Cmd(SPI1, ENABLE);
	
	/*				Configuration DMA SPI1				*/
	
	
}

uint8_t SPI_Get_Status(void){
	printf("%d\n", _receive_buffer[STATUS_ADDR]);
	return _receive_buffer[STATUS_ADDR];
}

uint16_t SPI_Get_Voltage_In(void){
	return (uint16_t) ((uint16_t)(_receive_buffer[VOLT_IN_ADDR]) | (uint16_t)_receive_buffer[VOLT_IN_ADDR + 1] <<8 );
}

uint16_t SPI_Get_Amp_In(void){
	return (uint16_t) ((uint16_t)(_receive_buffer[AMP_IN_ADDR]) | (uint16_t)_receive_buffer[AMP_IN_ADDR + 1] <<8 );
}

uint16_t SPI_Get_Voltage_Out1(void){
	return (uint16_t) ((uint16_t)(_receive_buffer[VOLT_OUT1_ADDR]) | (uint16_t)_receive_buffer[VOLT_OUT1_ADDR + 1] <<8 );
}

uint16_t SPI_Get_Voltage_Out2(void){
	return (uint16_t) ((uint16_t)(_receive_buffer[VOLT_OUT2_ADDR]) | (uint16_t)_receive_buffer[VOLT_OUT2_ADDR + 1] <<8 );
}

uint8_t SPI_Get_Temperature(void){
	return _receive_buffer[TEMPERATURE_ADDR];
}

uint8_t SPI_Get_Frequence(void){
	return _receive_buffer[FREQUENCE_ADDR];
}


void _delay_ms(uint16_t time){
	uint32_t time_n=  time*1000;
	while(time_n != 0)	{time_n--;}
}

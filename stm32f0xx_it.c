/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "LCD_HINORI.h"

uint16_t _temp;
/** @addtogroup STM32F0xx_StdPeriph_Templates
  * @{
  */
	


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void TIM3_IRQHandler(void){
	LCD_WAT_POWER();
	LCD_INVERT_WAT_POWER();
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
}

void TIM14_IRQHandler(void){
	LCD_TEMPERATURE_FREQ();
	LCD_INVERT_TEMPERATURE_FREQ();
	TIM_ClearFlag(TIM14, TIM_FLAG_Update);	
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void){
	LCD_Calculator_WS();
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
}

void TIM16_IRQHandler(void){
	LCD_GRAPH();
	LCD_INVERT_GRAPH();
	TIM_ClearFlag(TIM16, TIM_FLAG_Update);	
}


void TIM17_IRQHandler(void){
	LCD_OVERVOLTAGE();
	LCD_INVERT_OVERVOLTAGE();
	TIM_ClearFlag(TIM17, TIM_FLAG_Update);	
}

void SPI1_IRQHandler(void){
//	_temp = SPI_I2S_ReceiveData16(SPI1);
//	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_FLAG_RXNE)){
		printf("%d\n", SPI_ReceiveData8(SPI1));
		SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_RXNE);
//	}

}

void DMA1_Channel2_3_IRQHandler(void){
	DMA_ClearITPendingBit(DMA1_IT_HT2);
	
//	while(DMA_GetFlagStatus(DMA1_FLAG_HT2)){}
//	
//	DMA_ClearFlag(DMA1_FLAG_HT2);
		
	_temp = SPI_Get_Status();
	LCD_Set_Mode(_temp);
	
	if(_temp == INIT || _temp == RESET || _temp == STANBY)
		return;
	LCD_Set_Voltage_In(SPI_Get_Voltage_In());
	
	LCD_Set_Amp_In(SPI_Get_Amp_In());
	
	LCD_Set_Voltage_Out1(SPI_Get_Voltage_Out1());
	
	LCD_Set_Voltage_Out2(SPI_Get_Voltage_Out2());
	
	LCD_Set_Temperature(SPI_Get_Temperature());

	LCD_Set_Frequence(SPI_Get_Frequence());
}


/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 



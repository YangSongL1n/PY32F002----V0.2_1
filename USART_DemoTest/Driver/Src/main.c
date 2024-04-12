/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "py32f0xx_hal_uart.h"
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Error_Handler(void);
void APP_USARTConfig(void);
void KEY_LED_Init(void);
uint8_t Key_GetNum(void);

void LED1_Turn(void);
void LED2_Turn(void);
uint8_t KeyNum;
uint8_t Sta=0;// 状态
int main(void)
{
 
  HAL_Init();
	KEY_LED_Init();
  BSP_USART_Config(); // bsp级配置
  while (1)
  {
		
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
				Sta++;
			switch (Sta)
			{
					
			case 1:
				{
				printf("page 0\xff\xff\xff");	
				LED1_Turn();
				}	
				break;
			case 2:
				{
				printf("page 1\xff\xff\xff");	
				LED2_Turn();
			
				}	
			break;
			case 3:Sta=0;		break;
		default:

		
			break;
			}
		
		}
	}	
	
}



/*******************************************************************************//**
* @brief LED IO口配置
* @brief 按键：PB0; LED1:PB1; LED2:PB2

*********************************************************************************/

void  KEY_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();                          /* GPIOA时钟使能 */

  /* 初始化GPIOA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;            /* 推挽输出 */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                    /* 使能上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO速度 */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                /* GPIO初始化 */
	
	
	 __HAL_RCC_GPIOB_CLK_ENABLE();                          /* GPIOB时钟使能 */

  /* 初始化GPIOB0/1/2 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2; 
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                    /* 使能上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO速度 */

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                /* GPIO初始化 */
	
	
}
/**
  * @brief  按键被按下判断函数
  * @param  无
  * @retval Key_Num
  */
uint8_t Key_GetNum(void)
{
	
	uint8_t Key_Num = 0;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0)
		{

		HAL_Delay(15);
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0);
		HAL_Delay(15);
		Key_Num = 1;	
	}
	
	return  Key_Num;
}
/**
  * @brief  LED翻转
  * @param  无
  * @retval Key_Num
  */

void LED1_Turn(void)
{
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==0)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	}
}
void LED2_Turn(void)
{
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==0)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
	}
}
/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/

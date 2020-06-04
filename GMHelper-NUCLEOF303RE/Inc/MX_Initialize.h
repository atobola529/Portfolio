/*
 * MX_Initialize.h
 *
 *  Created on: May 4, 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_MX_INITIALIZE_H_
#define INC_MX_INITIALIZE_H_

#include "stm32f3xx_hal.h"

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Buzzer_Pin GPIO_PIN_0
#define Buzzer_GPIO_Port GPIOC
#define Button_T1_Pin GPIO_PIN_1
#define Button_T1_GPIO_Port GPIOA
#define Button_T2_Pin GPIO_PIN_2
#define Button_T2_GPIO_Port GPIOA
#define Board_LED_Pin GPIO_PIN_5
#define Board_LED_GPIO_Port GPIOA
#define SPI_SDA_Pin GPIO_PIN_10
#define SPI_SDA_GPIO_Port GPIOB
#define RGB1_GREEN_Pin GPIO_PIN_6
#define RGB1_GREEN_GPIO_Port GPIOC
#define RGB1_RED_Pin GPIO_PIN_8
#define RGB1_RED_GPIO_Port GPIOC
#define RGB1_BLUE_Pin GPIO_PIN_9
#define RGB1_BLUE_GPIO_Port GPIOC
#define SPI_SCK_Pin GPIO_PIN_8
#define SPI_SCK_GPIO_Port GPIOA
#define DigitalKey_Pin GPIO_PIN_11
#define DigitalKey_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define RGB_BLUE_Pin GPIO_PIN_10
#define RGB_BLUE_GPIO_Port GPIOC
#define RGB_RED_Pin GPIO_PIN_11
#define RGB_RED_GPIO_Port GPIOC
#define RGB_GREEN_Pin GPIO_PIN_12
#define RGB_GREEN_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_3
#define LCD_CS_GPIO_Port GPIOB
#define LCD_A0_Pin GPIO_PIN_4
#define LCD_A0_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_5
#define LCD_RST_GPIO_Port GPIOB

ADC_HandleTypeDef hadc3;
ADC_HandleTypeDef hadc4;

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim15;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC3_Init(void);
void MX_ADC4_Init(void);
void MX_TIM6_Init(void);
void MX_TIM7_Init(void);
void MX_TIM15_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void Error_Handler(void);

#endif /* INC_MX_INITIALIZE_H_ */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
extern ADC_HandleTypeDef hadc3; //>>MYCFG<<
extern ADC_HandleTypeDef hadc4;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim15;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
extern void SystemClock_Config(void); //>>MYCFG<<
extern void MX_GPIO_Init(void);
extern void MX_ADC3_Init(void);
extern void MX_ADC4_Init(void);
extern void MX_TIM6_Init(void);
extern void MX_TIM7_Init(void);
extern void MX_TIM15_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
  SystemClock_Config(); //MYCFG//
  MX_GPIO_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM15_Init();
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_Delay(100);
  //-----INIT LCDTFT-----
  ST7735_Init();
  CS_L();
  ST7735_AddrSet(0,0,128,128);
  CS_H();
  ST7735_Clear(COLOR565_BLACK);
  ST7735_Orientation(scr_180);
  ST7735_PutStr5x7(55, 55, "HALO?", COLOR565_ALICE_BLUE, COLOR565_BLACK);

  //-----START STUFF-----
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_ADC_Start(&hadc3);
  HAL_ADC_Start(&hadc4);
  ADCKeyboard_Start();
  //-----MENU-----
  MainMenu_Display();

  //-----TESTING-----
  //Buzzer_PlayTrack1();


  while (1)
  {
	  uint8_t y;
	  char buff[10];
	  char *pbuff = &buff;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//DisplayPluggedKey();
	Buzzer_note_duration_service();
	MainMenu_service();
	  //DisplayPluggedKey();
	  //ADCKeyboard_GetButtonsState(&y);
	  //if(y < Button_ANY) ST7735_PutStr5x7(30, 30, itoa((1+RNG_Random())%18, pbuff, 10), COLOR565_BEIGE, COLOR565_BLACK);

  }
  /* USER CODE END 3 */
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

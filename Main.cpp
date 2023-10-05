/**
 * @file Main.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Main source file.
 * 
 * @copyright Copyright (c) 2023, silvio3105
 * 
 */

/*
	Copyright (c) 2023, silvio3105 (www.github.com/silvio3105)

	Access and use of this Project and its contents are granted free of charge to any Person.
	The Person is allowed to copy, modify and use The Project and its contents only for non-commercial use.
	Commercial use of this Project and its contents is prohibited.
	Modifying this License and/or sublicensing is prohibited.

	THE PROJECT AND ITS CONTENT ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESSED OR IMPLIED WARRANTY.
	THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PREVIOUS NOTICE.
	THE AUTHOR IS NOT RESPONSIBLE FOR DAMAGE OF ANY KIND OR LIABILITY CAUSED BY USING THE CONTENTS OF THIS PROJECT.

	This License shall be included in all functional textual files.
*/


// ----- INCLUDE FILES
#include 			"Main.hpp"

#include			<cmsis_os2.h>


// ----- DEFINES


// ----- MACRO FUNCTIONS


// ----- TYPEDEFS


// ----- ENUMS


// ----- STRUCTS


// ----- CLASSES	


// ----- VARIABLES


// ----- STATIC FUNCTION DECLARATIONS
static void sysClockInit(void);

// ----- FUNCTION DEFINITIONS
osThreadId_t task;
void thread1(void *argument);

void thread1(void *argument) 
{
	while (1)
	{
		osDelay(400);	
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}

}

osThreadId_t task2;
void thread2(void *argument);

void thread2(void *argument) 
{
	while (1)
	{
		osDelay(750);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}

}

int main(void)
{
	GPIO_InitTypeDef gpioInit;

	HAL_Init();
	sysClockInit();

	__HAL_RCC_GPIOC_CLK_ENABLE();
	gpioInit.Pin = GPIO_PIN_13;
	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &gpioInit);

	osKernelInitialize();
	task = osThreadNew(thread1, NULL, NULL);
	task2 = osThreadNew(thread2, NULL, NULL);
	
	while (osKernelGetState() != osKernelReady);
	osKernelStart();

	while (1);
}


// ----- STATIC FUNCTION DEFINITIONS
static void sysClockInit(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
															|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}


// END WITH NEW LINE

/**
 * @file Main.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Main source file.
 * @version v1.0r1
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

#define 			SML_IMPLEMENTATION
#include			"SML.hpp"

#include			<stdio.h>


// ----- STM32 STUFF
UART_HandleTypeDef huart1;

static void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void Error_Handler(void);

#define LED_GPIO_Port		GPIOC
#define LED_Pin				GPIO_PIN_13


// ----- STATIC FUNCTION DECLARATIONS
SML_PRINT_HANDLER(uartOut);
SML_COPY_HANDLER(copyHandler);


// ----- VARIABLES
SML::Logger<256> Serial = SML::Logger<256>(uartOut);
SML::Logger<128> Log = SML::Logger<128>(uartOut, "[LOGGER] ");
SML::Copier Copy = SML::Copier(copyHandler);


// ----- DEBUG STUFF
#if defined(DEBUG_EXAMPLE) && defined(DEBUG) && defined(DEBUG_HANDLER)
	void DEBUG_HANDLER(const char* str, ...);

	#if DEBUG_LEVEL <= 3
		#define __EXAMPLE_ERROR_LOG DEBUG_HANDLER
	#else
		#define __EXAMPLE_ERROR_LOG(...)
	#endif
	#if DEBUG_LEVEL <= 2
		#define __EXAMPLE_WARNING_LOG DEBUG_HANDLER
	#else
		#define __EXAMPLE_WARNING_LOG(...)
	#endif
	#if DEBUG_LEVEL <= 1
		#define __EXAMPLE_INFO_LOG DEBUG_HANDLER
	#else
		#define __EXAMPLE_INFO_LOG(...)
	#endif
	#if DEBUG_LEVEL == 0
		#define __EXAMPLE_VERBOSE_LOG DEBUG_HANDLER
	#else
		#define __EXAMPLE_VERBOSE_LOG(...)
	#endif
#else 
	#define __EXAMPLE_ERROR_LOG(...)
	#define __EXAMPLE_WARNING_LOG(...)
	#define __EXAMPLE_INFO_LOG(...)
	#define __EXAMPLE_VERBOSE_LOG(...)
#endif

__SML_DEBUG_HANDLER(Serial)

// ----- APPLICATION ENTRY
int main(void)
{
	// STM32 STUFF
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	Serial.print("Simple Miscellaneous Library(SML) example\n\n");

	__EXAMPLE_ERROR_LOG("This is debug error log\n");
	__EXAMPLE_WARNING_LOG("This is debug warning log\n");
	__EXAMPLE_INFO_LOG("This is debug info log\n");
	__EXAMPLE_VERBOSE_LOG("This is debug verbose log\n");

	// LOGGER
	Log.print("Example uses built-in logger object.\n", 37);
	Log.printf("Logger state is: %s\n", Serial.getState() == SML::State_t::On ? "on" : "off");
	Log.setState(SML::State_t::Off);
	Log.print("This will not be printed!\n");
	Log.setState(SML::State_t::On);
	Log.print("Logger is back online!\n\n----- MACROS\n");

	// ARRAY SIZE
	uint8_t array8[6];
	uint32_t array32[5];
	Serial.printf("array8 has %u members\n", __SML_ARRAY_LEN(array8));
	Serial.printf("array32 has %u members\n", __SML_ARRAY_LEN(array32));

	// BBIT AND BIT
	uint8_t x = 0b01100010; // 98
	Serial.printf("bit 5 = %u; bit 4 = %u\n", __SML_BIT_GET(x, 5), __SML_BIT_GET(x, 4));
	Serial.printf("bit 5 power = %u; bit 4 power = %u; bit 1 power = %u\n", __SML_BIT_POWER(x, 5), __SML_BIT_POWER(x, 4), __SML_BIT_POWER(x, 1));

	// BIT SET, CLEAR AND TOGGLE
	Serial.printf("x value after clearing bit 5 = %u\n", __SML_BIT_CLEAR(x, 5));
	Serial.printf("x value after setting bit 7 = %u\n", __SML_BIT_SET(x, 7));
	Serial.printf("x value after toggling bit 2 = %u\n\n----- FUNCTIONS\n", __SML_BIT_TOGGLE(x, 2));

	// SCALE
	x = 50;
	Serial.printf("scale x 0-100 range to 0-250 range: x = %u -> x' = %u\n", x, SML::scale<uint8_t>(x, 0, 100, 0, 250));	

	// ABS VALUE
	Serial.printf("|420| = %u; |-50| = %u\n", SML::abs<int16_t>(420), SML::abs<int8_t>(-50));

	// MIN AND MAX
	Serial.printf("min(100, 500) = %u; max(100, 500) = %u\n", SML::min<uint16_t>(100, 500), SML::max<uint16_t>(100, 500));
	Serial.printf("min(100, 50, 1000) = %u; max(100, 50, 1000) = %u\n", SML::min<uint16_t>(100, 50, 1000), SML::max<uint16_t>(100, 50, 1000));

	// SWAP ENDIAN
	array32[0] = 0x11223344;
	SML::swapEndian(&array32[1], &array32[0], sizeof(array32[0]));
	Serial.printf("0x%02X%02X%02X%02X swapped is 0x%02X%02X%02X%02X\n", ((uint8_t*)&array32[0])[0], ((uint8_t*)&array32[0])[1], ((uint8_t*)&array32[0])[2], ((uint8_t*)&array32[0])[3], ((uint8_t*)&array32[1])[0], ((uint8_t*)&array32[1])[1], ((uint8_t*)&array32[1])[2], ((uint8_t*)&array32[1])[3]);

	// SUM ALL DIGITS
	Serial.printf("sum of all digits from number 12345678: %u\n", SML::sumDigits<uint32_t>(12345678));	

	// LENGTH
	char str[] = "Hello World!";
	char* str1 = nullptr;
	char str2[] = "Hello";
	char str3[] = "Hellio";
	Serial.printf("\n----- STRING MANIPULATIONS\nlength until NULL: %u\nlength until space: %u\n", SML::len(str), SML::len(str, ' '));

	// COUNT
	Serial.printf("number of Ls in string: %u\nnumber of Ls in string before space: %u\n", SML::count(str, 'l'), SML::count(str, 'l', ' '));

	// TOKENIZE
	str1 = SML::tok(str, ' ');
	Serial.printf("tok: '%s'  -  '%s'\n", str, str1);

	// COMPARE
	Serial.printf("%s and %s are %s\n%s and %s are %s\n", str, str2, SML::cmp(str, str2) == SML::Return_t::Ok ? "equal" : "not equal", str, str1, SML::cmp(str, str1) == SML::Return_t::Ok ? "equal" : "not equal");
	Serial.printf("%s and %s are %s\n%s and %s until first L are %s\n", str2, str3, SML::cmp(str2, str3) == SML::Return_t::Ok ? "equal" : "not equal", str2, str3, SML::cmp(str2, str3, 'l') == SML::Return_t::Ok ? "equal" : "not equal");	

	// DATA OBJECT
	uint32_t d[5] = { 10, 20, 30, 40, 50 };
	uint32_t anotherD[5] = { 1000, 10, 1 };
	SML::Data<uint32_t> testData(d, 5);

	Serial.print("\n ----- DATA OBJECT\ndata from data object: ");
	for (uint8_t i = 0; i < testData.len(); i++) Serial.printf("%u ", testData.get()[i]);

	testData.set(anotherD, __SML_ARRAY_LEN(anotherD));
	Serial.print("\nnew data: ");
	for (uint8_t i = 0; i < testData.len(); i++) Serial.printf("%u ", testData.get()[i]);
	Serial.print("\n", 1);

	// STRING PARSER
	char inputStr[] = "Word1,Word2-Word3.Word4/Word5";
	SML::Data<char>out;

	SML::parse(inputStr, ',', 0, '-', 0, out);
	Serial.printf("\n----- STRING PARSER\nbegin of 'Word2': '%s'\n", out.get());

	SML::parse(inputStr, ',', 0, '-', 0, out, SML::Answer_t::Yes);
	Serial.printf("same parser with modify on: '%s'\n", out.get());

	char in[] = "Word1,Word2,Word3";
	SML::parser_t parseList[] = {
		{
			.endSeparator = ',',
			.endSeparatorCnt = 0
		},

		{
			.endSeparator = ',',
			.endSeparatorCnt = 0
		},

		{
			.endSeparator = ',',
			.endSeparatorCnt = 0
		}				
	};

	SML::parse(in, parseList, __SML_ARRAY_LEN(parseList), SML::Answer_t::No, SML::Answer_t::Yes);
	Serial.printf("sorted multi parser without modify on: '%s' - '%s' - '%s'\n", parseList[0].output.get(), parseList[1].output.get(), parseList[2].output.get());

	SML::parse(in, parseList, __SML_ARRAY_LEN(parseList), SML::Answer_t::Yes, SML::Answer_t::Yes);
	Serial.printf("sorted multi parser with modify on: '%s' - '%s' - '%s'\n", parseList[0].output.get(), parseList[1].output.get(), parseList[2].output.get());	

	char in2[] = "Word1,Word2,Word3.Word4,Word5";
	SML::parser_t parse[] = {
		{ // OUTPUT: Word2,Word3.Word4
			.endSeparator = ',',
			.endSeparatorCnt = 1,
			.startSeparator = ',',
			.startSeparatorCnt = 0
		},

		{ // OUTPUT: Word3.Word4,Word5
			.endSeparator = '\0',
			.endSeparatorCnt = 0,
			.startSeparator = ',',
			.startSeparatorCnt = 1
		}				
	};	

	SML::parse(in2, parse, __SML_ARRAY_LEN(parse));
	Serial.print("unsorted multi parser without modify on: '");

	for (uint8_t i = 0; i < parse[0].output.len(); i++) Serial.printf("%c", parse[0].output.get()[i]);
	Serial.print("' - '");
	for (uint8_t i = 0; i < parse[1].output.len(); i++) Serial.printf("%c", parse[1].output.get()[i]);
	Serial.print("'\n");

	// RING BUFFER
	SML::RingBuffer<char, 64> ring; // 64 chars in ring buffer
	char rb[] = "ello World!"; // 11 chars
	char rbout[32] = { '\0' };

	Serial.printf("\n----- RING BUFFER\nring buffer size: %u\nnum of free data: %u\nnum of used data: %u\n", ring.size(), ring.free(), ring.used());

	// Write single data
	ring.write('H');

	// Write multiple data
	ring.write(rb, SML::len(rb));
	Serial.printf("num of free data after writing: %u\nnum of used data after writing: %u\n", ring.free(), ring.used());

	// Read single data
	ring.read(rbout[0]);
	Serial.printf("read single data: '%s'\n", rbout);

	// Read multiple data from ring buffer
	ring.read(rbout, __SML_ARRAY_LEN(rbout));
	Serial.printf("read multiple data: '%s'\n", rbout);

	Serial.printf("ring buffer is %s, used %u, free %u\n", ring.isFull() == SML::Return_t::Ok ? "full" : "not full", ring.used(), ring.free());

	// Flush ring buffer
	ring.flush();

	// COPY
	Serial.print("\n-----COPY\nvalues before copy: ");
	for (uint8_t i = 0; i < __SML_ARRAY_LEN(anotherD); i++) Serial.printf("%u ", anotherD[i]);
	Serial.print("\nValues after copy: ");
	Copy.copy(d, anotherD, sizeof(anotherD));
	for (uint8_t i = 0; i < __SML_ARRAY_LEN(anotherD); i++) Serial.printf("%u ", anotherD[i]);
	Serial.print("\n");

	// SPEED TEST
	uint32_t a = 0, b = 0;
	volatile uint16_t lenX = 0;
	volatile SML::Return_t resX = SML::Return_t::NA;
	(void)lenX;
	(void)resX;

	Serial.print("\n----- SPEED TEST:\n");

	// LENGTH
	char lenStr[] = "Hello, World!";

	a = HAL_GetTick();
	for (uint16_t i = 0; i < 1000; i++) lenX = SML::len(lenStr);
	b = HAL_GetTick();
	Serial.printf("len() x1000: %ums\n", b - a);

	// COMPARE
	a = HAL_GetTick();
	for (uint16_t i = 0; i < 10000; i++) resX = SML::cmp(lenStr, lenStr);
	b = HAL_GetTick();
	Serial.printf("cmp() x10000: %ums\n", b - a);

	// PARSER
	char parserStr[] = "Word1,Word2-Word3.Word4/Word5";

	a = HAL_GetTick();
	for (uint16_t i = 0; i < 10000; i++) SML::parse(parserStr, ',', 0, '-', 0, out);
	b = HAL_GetTick();
	Serial.printf("parse() x10000: %ums\n", b - a);	

	char outStr[32];
	a = HAL_GetTick();
	for (uint16_t i = 0; i < 10000; i++) sscanf(&parserStr[6], "%s-", outStr);
	b = HAL_GetTick();	
	Serial.printf("sscanf() x10000: %ums '%s'\n", b - a, outStr);	

	while (1)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(250);
	}
}

// ----- STATIC FUNCTION DEFINITIONS
SML_PRINT_HANDLER(uartOut)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&buffer[0], len, 500);
	Serial.done();
}

SML_COPY_HANDLER(copyHandler)
{
	SML::copy(source, destination, len);
	return SML::Return_t::Ok;
}


// ----- STM32HAL STUFF
static void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
															|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

static void MX_USART1_UART_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_USART1_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
}

static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PC14 PC15 */
	GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PD0 PD1 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
													|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
													|GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
													|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
													|GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
													|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure peripheral I/O remapping */
	__HAL_AFIO_REMAP_PD01_ENABLE();

}


static void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}



// END WITH NEW LINE

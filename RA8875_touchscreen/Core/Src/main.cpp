/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.hpp"

int main(void)
{
    HAL_Init();

    SystemClock_Config(SYS_CLOCK_FREQ_48_MHZ);

	Adafruit_RA8875 tft = Adafruit_RA8875(csPort, csPin, rstPort, rstPin);

      /* Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480' */
    if (!tft.begin(RA8875_800x480)) {
        Error_Handler();
    }

    tft.displayOn(true);
    tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
    tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
    tft.PWM1out(255);

    // With hardware acceleration this is instant
    tft.fillScreen(RA8875_WHITE);

    // Play with PWM
    for (uint8_t i=255; i!=0; i-=5 )
    {
        tft.PWM1out(i);
        HAL_Delay(10);
    }
    for (uint8_t i=0; i!=255; i+=5 )
    {
        tft.PWM1out(i);
        HAL_Delay(10);
    }
    tft.PWM1out(255);

    tft.fillScreen(RA8875_RED);
    HAL_Delay(500);
    tft.fillScreen(RA8875_YELLOW);
    HAL_Delay(500);
    tft.fillScreen(RA8875_GREEN);
    HAL_Delay(500);
    tft.fillScreen(RA8875_CYAN);
    HAL_Delay(500);
    tft.fillScreen(RA8875_MAGENTA);
    HAL_Delay(500);
    tft.fillScreen(RA8875_BLACK);

    // Try some GFX acceleration!
    tft.drawCircle(100, 100, 50, RA8875_BLACK);
    tft.fillCircle(100, 100, 49, RA8875_GREEN);

    tft.fillRect(11, 11, 398, 198, RA8875_BLUE);
    tft.drawRect(10, 10, 400, 200, RA8875_GREEN);
    tft.fillRoundRect(200, 10, 200, 100, 10, RA8875_RED);
    tft.drawPixel(10,10,RA8875_BLACK);
    tft.drawPixel(11,11,RA8875_BLACK);
    tft.drawLine(10, 10, 200, 100, RA8875_RED);
    tft.drawTriangle(200, 15, 250, 100, 150, 125, RA8875_BLACK);
    tft.fillTriangle(200, 16, 249, 99, 151, 124, RA8875_YELLOW);
    tft.drawEllipse(300, 100, 100, 40, RA8875_BLACK);
    tft.fillEllipse(300, 100, 98, 38, RA8875_GREEN);
    // Argument 5 (curvePart) is a 2-bit value to control each corner (select 0, 1, 2, or 3)
    tft.drawCurve(50, 100, 80, 40, 2, RA8875_BLACK);
    tft.fillCurve(50, 100, 78, 38, 2, RA8875_WHITE);

    // pinMode(RA8875_INT, INPUT);
    // digitalWrite(RA8875_INT, HIGH);

    tft.touchEnable(true);

    while (1)
    {
        // Your main loop
    }
}

// C functions needed by HAL
extern "C" {
    void SystemClock_Config(uint8_t clock_freq)
    {
        RCC_OscInitTypeDef osc_init;
        RCC_ClkInitTypeDef clk_init;

        uint32_t FLatency = 0;

        osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        osc_init.HSIState = RCC_HSI_ON;
        osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        osc_init.PLL.PLLState = RCC_PLL_ON;
        osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

        switch(clock_freq)
        {
            case SYS_CLOCK_FREQ_48_MHZ:
            {
                osc_init.PLL.PLLM = 8;
                osc_init.PLL.PLLN = 96;
                osc_init.PLL.PLLP = 4;
                osc_init.PLL.PLLQ = 4;

                clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
                clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
                clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
                clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
                clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

                FLatency = FLASH_ACR_LATENCY_1WS;

                break;
            }
            case SYS_CLOCK_FREQ_72_MHZ:
            {
                osc_init.PLL.PLLM = 8;
                osc_init.PLL.PLLN = 72;
                osc_init.PLL.PLLP = 2;
                osc_init.PLL.PLLQ = 3;

                clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
                clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
                clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
                clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
                clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

                FLatency = FLASH_ACR_LATENCY_1WS;

                break;
            }
            case SYS_CLOCK_FREQ_120_MHZ:
            {
                osc_init.PLL.PLLM = 8;
                osc_init.PLL.PLLN = 120;
                osc_init.PLL.PLLP = 2;
                osc_init.PLL.PLLQ = 5;

                clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
                clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
                clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
                clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
                clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

                FLatency = FLASH_ACR_LATENCY_1WS;

                break;
            }
            default:
                return;
        }
        if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
        {
            Error_Handler();
        }

        if (HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK)
        {
            Error_Handler();
        }

        /*Configure the systick timer interrupt frequency (for every 1 ms) */
        uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
        HAL_SYSTICK_Config(hclk_freq/1000);

        /**Configure the Systick
        */
        HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

        /* SysTick_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    }

}

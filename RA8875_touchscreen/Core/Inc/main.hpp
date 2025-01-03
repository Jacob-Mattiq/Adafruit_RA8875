/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_HPP
#define __MAIN_HPP

#include "Adafruit_RA8875.hpp"
#include "SPI.hpp"
#include "GPIO.hpp"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <cstring>

GPIO_TypeDef* csPort = GPIOB;
uint16_t csPin = GPIO_PIN_0;
GPIO_TypeDef* rstPort = GPIOA;
uint16_t rstPin = GPIO_PIN_4;

#define SYS_CLOCK_FREQ_48_MHZ 48
#define SYS_CLOCK_FREQ_72_MHZ 72
#define SYS_CLOCK_FREQ_120_MHZ 120
#define SYS_CLOCK_FREQ_168_MHZ 168

extern "C" {

  void SystemClock_Config(uint8_t clock_freq);

}

#endif /* __MAIN_H */

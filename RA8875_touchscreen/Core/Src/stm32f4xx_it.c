/*
 * it.c
 *
 *  Created on: Dec 11, 2024
 *      Author: jarla
 */
#include "stm32f4xx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

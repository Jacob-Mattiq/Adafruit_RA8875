/*
 * GPIO.hpp
 *
 *  Created on: Dec 1, 2024
 *      Author: jarla
 */

#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <cstring>

// Define constants
#define PIN_LOW				0
#define PIN_HIGH			1

#define PP_OUTPUT_MODE		0
#define INPUT_MODE			1
#define OD_OUTPUT_MODE		2
#define AF_MODE_SPI_1_2		3
#define AF_MODE_SPI_3		4


#define NO_PULL				0
#define	PULL_DOWN			1
#define PULL_UP				2

class GPIO {
	public:
		 // Default constructor
        GPIO() : _port(nullptr), _pin(0), _mode(0), _pull(0) {}

		// Main constructor
        GPIO(GPIO_TypeDef* port, uint16_t pin, uint8_t mode, uint8_t pull);

		// Assignment operator (needed for reconfiguring GPIO pins)
		GPIO& operator=(const GPIO& other);

		// Method declerations
		void init(uint8_t mode, uint8_t pull);
		void write(GPIO_PinState state);
		uint8_t read(void);
		void toggle(void);

	private:
		GPIO_TypeDef* _port;
		uint16_t _pin;
		uint8_t _mode;
        uint8_t _pull;
};




#endif /* GPIO_H */

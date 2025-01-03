#ifndef SPI_HPP
#define SPI_HPP

#include "GPIO.hpp"
#include "error_handler.hpp"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <cstring>

//Clock Enable Macros for SPIx peripherals
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1 << 15))


#define DEVICE_MODE_MASTER 1
#define DEVICE_MODE_SLAVE 0

#define SPI_MODE_0 0
#define SPI_MODE_1 1
#define SPI_MODE_2 2
#define SPI_MODE_3 3
    
// Baud Rate Prescaler
#define BR_DIV2  0
#define BR_DIV4  1
#define BR_DIV8  2
#define BR_DIV16 3
#define BR_DIV32 4
#define BR_DIV64 5
#define BR_DIV128 6
#define BR_DIV256 7

// SPI Configuration Structure (needed for initialization)
struct SPI_Config {
    uint8_t SPI_DeviceMode;   // Master/Slave
    uint8_t SPI_Mode;         // Clock polarity and phase
    uint8_t SPI_BaudRate;     // Clock speed
    SPI_TypeDef* SPIx;        // SPIx peripheral
};

class SPI {
    public:
        // Constructor
        SPI(const SPI_Config &config);
    
        // Initialize with configuration
        void init(const SPI_Config& config);
        
        // Core functions needed by RA8875
        uint8_t transfer(uint8_t data);  // Single byte transfer
        uint16_t transfer16(uint16_t data);
        void begin(void);
        void end(void);

    private:
        SPI_TypeDef* _pSPIx;
        SPI_HandleTypeDef _spiHandle;
        GPIO _sck;
        GPIO _miso;
        GPIO _mosi;
                
        void configureClock(void);
};

#endif

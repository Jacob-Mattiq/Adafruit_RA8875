#include "SPI.hpp"

SPI::SPI(const SPI_Config &config):
    _pSPIx(config.SPIx),
    // Initialize GPIO pins based on which SPI peripheral is being used
    _sck((config.SPIx == SPI1) ? GPIOA : (config.SPIx == SPI2) ? GPIOB : GPIOC,
         (config.SPIx == SPI1) ? GPIO_PIN_5 : (config.SPIx == SPI2) ? GPIO_PIN_13 : GPIO_PIN_10,
         (config.SPIx == SPI3) ? AF_MODE_SPI_3 : AF_MODE_SPI_1_2,
         NO_PULL),
    _miso((config.SPIx == SPI1) ? GPIOA : (config.SPIx == SPI2) ? GPIOB : GPIOC,
          (config.SPIx == SPI1) ? GPIO_PIN_6 : (config.SPIx == SPI2) ? GPIO_PIN_14 : GPIO_PIN_11,
          (config.SPIx == SPI3) ? AF_MODE_SPI_3 : AF_MODE_SPI_1_2,
          NO_PULL),
    _mosi((config.SPIx == SPI1) ? GPIOA : (config.SPIx == SPI2) ? GPIOB : GPIOC,
          (config.SPIx == SPI1) ? GPIO_PIN_7 : (config.SPIx == SPI2) ? GPIO_PIN_15 : GPIO_PIN_12,
          (config.SPIx == SPI3) ? AF_MODE_SPI_3 : AF_MODE_SPI_1_2,
          NO_PULL)
{
    init(config);
}

void SPI::init(const SPI_Config &config) {
    SPI_InitTypeDef _spiInit;

     // Set device mode (Master/Slave)
    _spiInit.Mode = (config.SPI_DeviceMode == DEVICE_MODE_MASTER) ? 
                    SPI_MODE_MASTER : SPI_MODE_SLAVE;
    
    // Set clock polarity and phase based on SPI mode
    switch(config.SPI_Mode) {
        case SPI_MODE_0:
            _spiInit.CLKPolarity = SPI_POLARITY_LOW;
            _spiInit.CLKPhase = SPI_PHASE_1EDGE;
            break;
        case SPI_MODE_1:
            _spiInit.CLKPolarity = SPI_POLARITY_LOW;
            _spiInit.CLKPhase = SPI_PHASE_2EDGE;
            break;
        case SPI_MODE_2:
            _spiInit.CLKPolarity = SPI_POLARITY_HIGH;
            _spiInit.CLKPhase = SPI_PHASE_1EDGE;
            break;
        case SPI_MODE_3:
            _spiInit.CLKPolarity = SPI_POLARITY_HIGH;
            _spiInit.CLKPhase = SPI_PHASE_2EDGE;
            break;
    }
    
    // Set baud rate
    switch(config.SPI_BaudRate) {
        case BR_DIV2:   _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;   break;
        case BR_DIV4:   _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;   break;
        case BR_DIV8:   _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;   break;
        case BR_DIV16:  _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;  break;
        case BR_DIV32:  _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;  break;
        case BR_DIV64:  _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;  break;
        case BR_DIV128: _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128; break;
        case BR_DIV256: _spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; break;
    }

    _spiInit.Direction = SPI_DIRECTION_2LINES; // full-duplex
    _spiInit.DataSize = SPI_DATASIZE_8BIT;
    _spiInit.NSS = SPI_NSS_SOFT;
    _spiInit.FirstBit = SPI_FIRSTBIT_MSB;

    _pSPIx = config.SPIx;
    _spiHandle.Instance = _pSPIx;
    _spiHandle.Init = _spiInit;

    configureClock();

    // Initialize SPI using HAL
    if(HAL_SPI_Init(&_spiHandle) != HAL_OK) {
        Error_Handler();
    }
}

void SPI::configureClock() {
    if(_pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
    else if(_pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
    else if(_pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
}

uint8_t SPI::transfer(uint8_t data) {
    // Wait until TXE is set (Transmit buffer empty)
    while (!(_pSPIx->SR & SPI_SR_TXE));
    
    // Send data
    _pSPIx->DR = data;
    
    // Wait until RXNE is set (Receive buffer not empty)
    while (!(_pSPIx->SR & SPI_SR_RXNE));
    
    // Return received data
    return _pSPIx->DR;
}

uint16_t SPI::transfer16(uint16_t data) {
    uint16_t received = 0;
    // Send high byte first (MSB)
    received = transfer((data >> 8) & 0xFF);
    // Send low byte
    received |= transfer(data & 0xFF);

    return received;
}

void SPI::begin(void) {
    _pSPIx->CR1 |= SPI_CR1_SPE;
}

void SPI::end(void) {
    while (_pSPIx->SR & SPI_SR_BSY);  // Wait until not busy
    _pSPIx->CR1 &= ~SPI_CR1_SPE;
}
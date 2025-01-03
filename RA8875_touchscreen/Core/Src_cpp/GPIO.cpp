#include "GPIO.hpp"

GPIO::GPIO(GPIO_TypeDef* port, uint16_t pin, uint8_t mode, uint8_t pull):
    _port(port),
    _pin(pin),
    _mode(mode),
    _pull(pull)
{
    init(mode, pull);
}

GPIO& GPIO::operator=(const GPIO& other) {
    if (this != &other) {
        _port = other._port;
        _pin = other._pin;
        _mode = other._mode;
        _pull = other._pull;
        init(_mode, _pull);
    }
    return *this;
}

void GPIO::init(uint8_t mode, uint8_t pull) {
    if(_port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if(_port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if(_port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if(_port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if(_port == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitTypeDef gpiopininit = {0};

    gpiopininit.Pin = _pin;

    switch(mode) {
        case PP_OUTPUT_MODE:
            gpiopininit.Mode = GPIO_MODE_OUTPUT_PP;
            break;
        case INPUT_MODE:
            gpiopininit.Mode = GPIO_MODE_INPUT;
            break;
        case OD_OUTPUT_MODE:
            gpiopininit.Mode = GPIO_MODE_OUTPUT_OD;
            break;
        case AF_MODE_SPI_1_2:
            gpiopininit.Mode = GPIO_MODE_AF_PP;
            gpiopininit.Alternate = GPIO_AF5_SPI1;
            break;
        case AF_MODE_SPI_3:
            gpiopininit.Mode = GPIO_MODE_AF_PP;
            gpiopininit.Alternate = GPIO_AF6_SPI3;
            break;
    }

    switch(pull) {
        case NO_PULL:
            gpiopininit.Pull = GPIO_NOPULL;
            break;
        case PULL_DOWN:
            gpiopininit.Pull = GPIO_PULLDOWN;
            break;
        case PULL_UP:
            gpiopininit.Pull = GPIO_PULLUP;
            break;
    }

	HAL_GPIO_Init(_port, &gpiopininit);
}

void GPIO::write(GPIO_PinState state) {
    HAL_GPIO_WritePin(_port, _pin, state);
}

uint8_t GPIO::read() {
    return HAL_GPIO_ReadPin(_port, _pin);
}

void GPIO::toggle() {
    HAL_GPIO_TogglePin(_port, _pin);
}

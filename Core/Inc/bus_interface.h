/*
 * bus_interface.h
 *
 *  Created on: 29 apr 2026
 *      Author: docge
 */

#ifndef __BUS_INTERFACE_H
#define __BUS_INTERFACE_H

#include "spi.h"
#include "i2c.h"


//#include "main.h"
//👉 daarin zit uiteindelijk ook:
//#include "stm32g0xx_hal.h"
//👉 daarin zit uiteindelijk ook:
//#include <stdint.h>

//#include "main.h"
//#include "gpio.h"
//#include "spi.h"
//#include "i2c.h"
//#include "usart.h"
//#include "tim.h"


typedef struct
{
    SPI_HandleTypeDef *hspi; // Komt uit HAL
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;   // zie stm32g0xx_hal_gpio.h waarom dit uint16_t is
    GPIO_TypeDef *miso_port;
    uint16_t miso_pin;   // zie stm32g0xx_hal_gpio.h waarom dit uint16_t is

} SPI_Interface_t;


typedef struct
{
    I2C_HandleTypeDef *hi2c; // Komt uit HAL
    uint16_t address;

} I2C_Interface_t;



typedef enum IO_EXP_BusType
{
    BUS_SPI,
    BUS_I2C
	//MCP23S17_SPI_t,
	//MCP23017_I2C_t,

}  BusConnType_t;


// let op .. volgenee is variable maken, terwijl we een alias willen.
// Maar we kunnen ook gelijk zonder alias de naam gebruiken.
// Maakt ene varialble :  I2C_Interface_t  IO_EXP_I2C_Interface_t;
// Maakt een alias :  typedef SPI_Interface_t IO_EXP_SPI_Interface_t;


typedef struct {

	BusConnType_t bus_t;

    union {
			SPI_Interface_t spi;
			I2C_Interface_t i2c;
    	} dev;

}  Device_BusConnection_t;


//typedef SPI_Interface_t CC1101_Device_BusConnection_t;



#endif /* INC_BUS_INTERFACE_H_ */

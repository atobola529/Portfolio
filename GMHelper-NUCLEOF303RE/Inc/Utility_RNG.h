/*
 * Utility_RNG.h
 *
 *  Created on: 16 maj 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_UTILITY_RNG_H_
#define INC_UTILITY_RNG_H_

#include "stm32f3xx_hal.h"
#include "MX_Initialize.h"

uint32_t RNG_Random();
uint32_t RNG_seed1();
uint32_t RNG_seed2();
#endif /* INC_UTILITY_RNG_H_ */

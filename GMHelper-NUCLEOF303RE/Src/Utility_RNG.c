/*
 * Utility_RNG.c
 *
 *  Created on: 16 maj 2020
 *      Author: h4XX0rZ
 */

#include "Utility_RNG.h"

uint32_t x;

uint32_t RNG_Random()
{
	uint32_t a,b,c;
	a = RNG_seed1();
	b = RNG_seed2();
	c = ((a << 1) ^ (7 >> b));
	x += 65837;
	a = (a^(7>>c)^x^(4<<b));
	b = (c+(a<<5));
	c = (c+((b>>1)^a));
	return (c>>3);
}

uint32_t RNG_seed1()
{
	return htim7.Instance->CNT;
}

uint32_t RNG_seed2()
{
	return htim6.Instance->CNT;
}

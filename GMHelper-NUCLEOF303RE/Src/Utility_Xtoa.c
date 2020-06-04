/*
 * Xtoa.c
 *
 *  Created on: May 3, 2020
 *      Author: h4XX0rZ
 */

#include <stdint.h>
#include <Utility_Xtoa.h>

#define MAX_PRECISION	(10)


void reverse(char* begin,char* end);

char* itoa(int value, char* buffer, int base)
{
	static const char digits[]="0123456789abcdef";

	char* buffer_copy=buffer;
	int32_t sign=0;
	int32_t quot,rem;

	if ((base>=2)&&(base<=16))				// is the base valid?
	{
		if (base == 10 && (sign = value) < 0)// negative value and base == 10? store the copy (sign)
			value = -value;					// make it positive

		do
		{
			quot=value/base;				// calculate quotient and remainder
			rem=value%base;
			*buffer++ = digits[rem];		// append the remainder to the string
		} while ((value=quot));				// loop while there is something to convert

		if (sign<0)							// was the value negative?
			*buffer++='-';					// append the sign

		reverse(buffer_copy,buffer-1);		// reverse the string
	}

	*buffer='\0';
	return buffer_copy;
}

void reverse(char* begin,char* end)
{
	char temp;

	while (end>begin)
	{
		temp=*end;
		*end--=*begin;
		*begin++=temp;
	}
}

static const double rounders[MAX_PRECISION + 1] =
{
	0.5,				// 0
	0.05,				// 1
	0.005,				// 2
	0.0005,				// 3
	0.00005,			// 4
	0.000005,			// 5
	0.0000005,			// 6
	0.00000005,			// 7
	0.000000005,		// 8
	0.0000000005,		// 9
	0.00000000005		// 10
};

char * ftoa(double f, char * buf, int precision)
{
	char * ptr = buf;
	char * p = ptr;
	char * p1;
	char c;
	long intPart;

	// check precision bounds
	if (precision > MAX_PRECISION)
		precision = MAX_PRECISION;

	// sign stuff
	if (f < 0)
	{
		f = -f;
		*ptr++ = '-';
	}

	if (precision < 0)  // negative precision == automatic precision guess
	{
		if (f < 1.0) precision = 6;
		else if (f < 10.0) precision = 5;
		else if (f < 100.0) precision = 4;
		else if (f < 1000.0) precision = 3;
		else if (f < 10000.0) precision = 2;
		else if (f < 100000.0) precision = 1;
		else precision = 0;
	}

	// round value according the precision
	if (precision)
		f += rounders[precision];

	// integer part...
	intPart = f;
	f -= intPart;

	if (!intPart)
		*ptr++ = '0';
	else
	{
		// save start pointer
		p = ptr;

		// convert (reverse order)
		while (intPart)
		{
			*p++ = '0' + intPart % 10;
			intPart /= 10;
		}

		// save end pos
		p1 = p;

		// reverse result
		while (p > ptr)
		{
			c = *--p;
			*p = *ptr;
			*ptr++ = c;
		}

		// restore end pos
		ptr = p1;
	}

	// decimal part
	if (precision)
	{
		// place decimal point
		*ptr++ = '.';

		// convert
		while (precision--)
		{
			f *= 10.0;
			c = f;
			*ptr++ = '0' + c;
			f -= c;
		}
	}

	// terminating zero
	*ptr = 0;

	return buf;
}


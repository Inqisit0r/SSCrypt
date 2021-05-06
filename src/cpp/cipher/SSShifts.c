#include "SSShifts.h"

void ssLeftShift(uint8_t* in, size_t inSize)
{
	size_t a = inSize - 1;
	size_t i = 0;
	for (i; i < a; ++i)
	{
		in[i] = in[i + 1];
	}
	in[i] = 0x00;
}

void ssRightShift(uint8_t* in, size_t inSize)
{
	size_t a = inSize - 1;
	size_t b = inSize - 2;
	size_t i = 0;
	for (i; i < a; ++i)
	{
		in[a - i] = in[b - i];
	}
	in[0] = 0x00;
}
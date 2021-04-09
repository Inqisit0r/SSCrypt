#include "..\..\h\cipher\SSSwaps.h"

uint16_t swap16(uint16_t a)
{
	return(((a >> 8) & 0x00FF) | ((a << 8) & 0xFF00));
}

uint16_t swab16(uint8_t* a)
{
	uint16_t result = 0;
	result = ((result + *(a)) << 8) | (result + *(a + 1));
	return (result);
}

void swat16(uint16_t a, uint8_t* b)
{
	b[0] = (uint8_t)(a >> 8);
	b[1] = (uint8_t)(a);
}


uint32_t swap32(uint32_t a)
{
	return (((a >> 24) & 0x000000FF) | ((a >> 8) & 0x0000FF00) | ((a << 8) & 0x00FF0000) | ((a << 24) & 0xFF000000));
}

uint32_t swab32(uint8_t* a)
{
	uint32_t result = 0;
	for (int i = 0; i < 3; ++i)
	{
		result = (result | *(a + i)) << 8;
	}
	result = result + *(a + 3);
	return (result);
}

void swat32(uint32_t a, uint8_t* b)
{
	b[0] = (uint8_t)(a >> 24);
	b[1] = (uint8_t)(a >> 16);
	b[2] = (uint8_t)(a >> 8);
	b[3] = (uint8_t)(a);
}


uint64_t swap64(uint64_t a)
{
	uint64_t result = 0;
	uint32_t a0 = swap32((uint32_t)a);
	uint32_t a1 = swap32((uint32_t)(a >> 32));
	result = ((result | a0) << 32) | a1;
	return result;
}

uint64_t swab64(uint8_t* a)
{
	uint64_t result = 0;
	for (int i = 0; i < 7; ++i)
	{
		result = (result | *(a + i)) << 8;
	}
	result = result + *(a + 7);
	return (result);
}

void swat64(uint64_t a, uint8_t* b)
{
	b[0] = (uint8_t)(a >> 56);
	b[1] = (uint8_t)(a >> 48);
	b[2] = (uint8_t)(a >> 40);
	b[3] = (uint8_t)(a >> 32);
	b[4] = (uint8_t)(a >> 24);
	b[5] = (uint8_t)(a >> 16);
	b[6] = (uint8_t)(a >> 8);
	b[7] = (uint8_t)(a);
	swab64(b);
}

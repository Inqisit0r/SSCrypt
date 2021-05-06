#include "SSConvertors.h"

uint64_t ssConv8to64(uint8_t* a)
{
	uint64_t res = 0;
	for (int i = 0; i < 7; ++i)
	{
		res = (res | a[i]) << 8;
	}
	res = res | a[7];
	return res;
}

uint8_t ssConv64to8(uint64_t a)
{
	uint8_t res[8] = { 0 };
	res[0] = (uint8_t)(a >> 56);
	res[1] = (uint8_t)(a >> 48);
	res[2] = (uint8_t)(a >> 40);
	res[3] = (uint8_t)(a >> 32);
	res[4] = (uint8_t)(a >> 24);
	res[5] = (uint8_t)(a >> 16);
	res[6] = (uint8_t)(a >> 8);
	res[7] = (uint8_t)(a);
	return res;
}

void ssSet64to8(uint64_t a, uint8_t* b)
{
	b[0] = (uint8_t)(a >> 56);
	b[1] = (uint8_t)(a >> 48);
	b[2] = (uint8_t)(a >> 40);
	b[3] = (uint8_t)(a >> 32);
	b[4] = (uint8_t)(a >> 24);
	b[5] = (uint8_t)(a >> 16);
	b[6] = (uint8_t)(a >> 8);
	b[7] = (uint8_t)(a);
}
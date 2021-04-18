#include "SSPadding.h"
#include <stdint.h>

ssStatus ssPadding01(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize)
{
	if (inSize <= outSize)
	{
		size_t i = 0;
		for (i; i < inSize; ++i)
		{
			out[i] = in[i];
		}
		for (; i < outSize; ++i)
		{
			out[i] = 0x00;
		}
		return SSStatusSuccess;
	}
	else
		return SSStatusError;
}

ssStatus ssPadding02(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize)
{
	if (inSize <= outSize)
	{
		size_t i = 0;
		for (i; i < inSize; ++i)
		{
			out[i] = in[i];
		}
		if (inSize < outSize)
		{
			out[i] = 0x10;
			++i;
		}
		for (; i < outSize; ++i)
		{
			out[i] = 0x00;
		}
		return SSStatusSuccess;
	}
	else
		return SSStatusError;
}

ssStatus ssPadding03(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize)
{
	if (inSize == outSize)
		return SSStatusSuccess;
	else if (inSize < outSize)
	{
		return ssPadding02(in, inSize, out, outSize);
	}
	else
		return SSStatusError;
}

ssStatus ssPaddingCTR(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize)
{
	
}

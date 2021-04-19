#include "SSPadding.h"
#include <stdint.h>

void ssPadding01(uint8_t* in, size_t inSize, uint8_t* block, size_t blockSize)
{
	size_t i = 0;
	for  (i; i < inSize; ++i)
	{
		block[i] = in[i];
	}
	for (i; i < blockSize; ++i)
	{
		block[i] = 0x00;
	}
}

void ssPadding02(uint8_t* in, size_t inSize, uint8_t* block, size_t blockSize)
{
	size_t i = 0;
	for (i; i < inSize; ++i)
	{
		block[i] = in[i];
	}
	if (inSize < blockSize)
	{
		block[i] = 0x10;
		++i;
	}
	for (i; i < blockSize; ++i)
	{
		block[i] = 0x00;
	}
}

void ssPadding03(uint8_t* in, size_t inSize, uint8_t* block, size_t blockSize)
{
	if (inSize < blockSize)
	{
		ssPadding02(in, inSize, block, blockSize);
	}
}

ssStatus ssPaddingMAGMA00(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize)
{
	if ((in == NULL) || (inSize == 0) || (block == NULL))
	{
		if (blockSize != NULL)
		{
			*blockSize = 8;
			return SSStatusSuccess;
		}
		else if (blockSize == NULL)
			return SSStatusInvalidParameter;
	}
	ssPadding01(in, inSize, block, MAGMA_BLOCK_SIZE);
	return SSStatusSuccess;
}

ssStatus ssPaddingMAGMA01(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize)
{
	if ((in == NULL) || (inSize == 0) || (block == NULL))
	{
		if (blockSize != NULL)
		{
			*blockSize = 8;
			return SSStatusSuccess;
		}
		else if (blockSize == NULL)
			return SSStatusInvalidParameter;
	}
	ssPadding03(in, inSize, block, MAGMA_BLOCK_SIZE);
	return SSStatusSuccess;
}

ssStatus ssPaddingKyznechik(uint8_t* in, size_t inSize, uint8_t* block, size_t blockSize)
{
	return SSStatusNotSupported;
}

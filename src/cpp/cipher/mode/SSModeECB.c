#include "SSMode.h"

ssStatus ssModeECB(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t* outSize,
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	size_t i = 0;
	size_t blockSize = 0;
	ssStatus status = SSStatusSuccess;
	if ((key == NULL) || (keySize == 0))
	{
		return SSStatusInvalidParameter;
	}
	if (SSStatusSuccess != (status = padding(NULL, 0, NULL, &blockSize)))
	{
		return status;
	}
	if (blockSize == 0)
	{
		return SSStatusError;
	}
	for (i; blockSize + i < inSize; i += blockSize)
	{
		if (SSStatusSuccess != (status = cipher(in + i, key, out + i)))
		{
			return status;
		}
	}
	if (blockSize != inSize)
	{
		uint8_t block = (uint8_t*)malloc(blockSize);
		if (SSStatusSuccess != (status = padding(in, inSize - i, block, &blockSize)))
		{
			if (block)
			{
				free(block);
			}
			return status;
		}
	}
	return SSStatusSuccess;
}
#include "SSMode.h"

void ssIncrement8(uint8_t* in, size_t inSize)
{
	size_t i = 1;
	do
	{
		*(in + inSize - i) += 1;
	} 	while ((*(in + inSize - i++) == 0) && (inSize - i >= 0));	// Постинкремент используется, чтобы проверить значение;
																	// inSize - i = 0 для i[0]
}

ssStatus ssModeCTR(
	const uint8_t* in, 
	size_t inSize, 
	const uint8_t* key, 
	size_t keySize, 
	uint8_t* out, 
	size_t outSize, 
	const uint8_t* iv,
	size_t ivSize,
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* CTR, size_t* CTRSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out), 
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	ssStatus status = SSStatusSuccess;
	uint8_t* buffer = NULL;
	uint8_t* CTR = NULL;
	size_t i = 0;
	size_t blockSize = 0;
	if ((in == NULL) || (inSize == 0) || (key == NULL) || (keySize == 0) || (out == NULL) || (outSize == 0) || (iv == NULL) || (ivSize == 0))
	{
		status = SSStatusInvalidParameter;
		goto CleanUp;
	}
	if (SSStatusSuccess != (status = padding(NULL, 0, NULL, &blockSize)))
	{
		goto CleanUp;
	}
	if (blockSize == 0)
	{
		status = SSStatusError;
		goto CleanUp;
	}
	CTR = (uint8_t*)malloc(blockSize);
	if (SSStatusSuccess != (status = init(iv, ivSize, CTR, &blockSize)))
	{
		goto CleanUp;
	}

	buffer = (uint8_t*)malloc(blockSize);
	for (i; blockSize + i <= inSize; i += blockSize)
	{
		if (SSStatusSuccess != (status = cipher(CTR, key, buffer)))
		{
			goto CleanUp;
		}
		ssIncrement8(CTR, blockSize);
		for (size_t k = 0; k < blockSize; ++k)
		{
			out[i + k] = buffer[k] ^ in[i + k];
		}
	}

	if (i != inSize)
	{
		if (SSStatusSuccess != (status = cipher(CTR, key, buffer)))
		{
			goto CleanUp;
		}
		for (i; i < inSize; ++i)
		{
			out[i] = in[i] ^ buffer[i % 8];
		}
	}
CleanUp:
	if (CTR)
	{
		free(CTR);
	}
	if (buffer)
	{
		free(buffer);
	}
	return status;
}
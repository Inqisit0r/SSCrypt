#include "SSMode.h"

ssStatus ssModeOFB(
	const uint8_t* in, 
	size_t inSize, 
	const uint8_t* key, 
	size_t keySize, 
	uint8_t* out, 
	size_t outSize, 
	const uint8_t* iv, 
	size_t ivSize, 
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* OFB, size_t* OFBSize), 
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out), 
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	ssStatus status = SSStatusSuccess;
	size_t i = 0;
	size_t blockSize = 0;
	uint8_t* OFB = NULL;
	uint8_t* bufferOut = NULL;
	uint8_t* bufferIn = NULL;
	size_t OFBSize = 0;

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
	OFBSize = 2 * blockSize;
	OFB = (uint8_t*)malloc(2 * blockSize);
	bufferOut = (uint8_t*)malloc(blockSize);
	bufferIn = (uint8_t*)malloc(blockSize);
	if (SSStatusSuccess != (status = init(iv, ivSize, OFB, &OFBSize)))
	{
		goto CleanUp;
	}
	if (OFBSize == 0)
	{
		status = SSStatusError;
		goto CleanUp;
	}
	
	for (i; blockSize + i <= inSize; i += blockSize)
	{
		if (SSStatusSuccess != (status = (cipher(OFB, key, bufferOut))))
		{
			goto CleanUp;
		}
		if (OFBSize != blockSize)
		{
			//Обновление iv и запись криптограммы в out
			for (size_t k = 0; k < blockSize; ++k)
			{
				OFB[k] = OFB[blockSize + k];
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				OFB[blockSize + k] = bufferOut[k];
				out[i + k] = bufferOut[k] ^ in[i + k];
			}
		}
		else if (OFBSize == blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ in[i + k];
			}
		}
	}

	if (i != inSize)
	{
		if (SSStatusSuccess != (status = (cipher(bufferIn, key, bufferOut))))
		{
			goto CleanUp;
		}
		for (i; i < inSize; ++i)
		{
			out[i] = in[i] ^ bufferOut[i % 8];
		}
	}

CleanUp:
	if (OFB)
	{
		free(OFB);
	}
	if (bufferIn)
	{
		free(bufferIn);
	}	
	if (bufferOut)
	{
		free(bufferOut);
	}
	return status;
}
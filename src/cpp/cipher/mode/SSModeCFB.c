#include "SSMode.h"

ssStatus ssEncryptModeCFB(
	const uint8_t* in, 
	size_t inSize, 
	const uint8_t* key, 
	size_t keySize, 
	uint8_t* out, 
	size_t outSize, 
	const uint8_t* iv, 
	size_t ivSize, 
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* CFB, size_t* OFBSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out), 
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	ssStatus status = SSStatusSuccess;
	size_t i = 0;
	size_t blockSize = 0;
	uint8_t* CFB = NULL;
	uint8_t* bufferOut = NULL;

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
	CFB = (uint8_t*)malloc(ivSize);
	if (SSStatusSuccess != (status = init(iv, ivSize, CFB, &ivSize)))
	{
		goto CleanUp;
	}

	bufferOut = (uint8_t*)malloc(blockSize);
	for (i; blockSize + i <= inSize; i += blockSize)
	{
		if (SSStatusSuccess != (status = (cipher(CFB, key, bufferOut))))
		{
			goto CleanUp;
		}
		if (ivSize != blockSize)
		{
			for (size_t k = 0; k < ivSize - blockSize; ++k)
			{
				CFB[k] = CFB[blockSize + k];
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ in[i + k];
				CFB[ivSize - blockSize + k] = out[i + k];
			}
		}
		else if (ivSize == blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ in[i + k];
				CFB[k] = out[i + k];
			}
		}
	}

	if (i != inSize)
	{
		if (SSStatusSuccess != (status = cipher(CFB, key, bufferOut)))
		{
			goto CleanUp;
		}
		for (i; i < inSize; ++i)
		{
			out[i] = in[i] ^ bufferOut[i % 8];
		}
	}

CleanUp:
	if (CFB)
	{
		free(CFB);
	}
	if (bufferOut)
	{
		free(bufferOut);
	}
	return status;
}

ssStatus ssDecryptModeCFB(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	const uint8_t* iv,
	size_t ivSize,
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* CFB, size_t* OFBSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	ssStatus status = SSStatusSuccess;
	size_t i = 0;
	size_t blockSize = 0;
	uint8_t* CFB = NULL;
	uint8_t* bufferOut = NULL;

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
	CFB = (uint8_t*)malloc(ivSize);
	if (SSStatusSuccess != (status = init(iv, ivSize, CFB, &ivSize)))
	{
		goto CleanUp;
	}

	bufferOut = (uint8_t*)malloc(blockSize);
	for (i; blockSize + i <= inSize; i += blockSize)
	{
		if (SSStatusSuccess != (status = (cipher(CFB, key, bufferOut))))
		{
			goto CleanUp;
		}
		if (ivSize != blockSize)
		{
			for (size_t k = 0; k < ivSize - blockSize; ++k)
			{
				CFB[k] = CFB[blockSize + k];
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ in[i + k];
				CFB[ivSize - blockSize + k] = in[i + k];
			}
		}
		else if (ivSize == blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ in[i + k];
				CFB[k] = in[i + k];
			}
		}
	}

	if (i != inSize)
	{
		if (SSStatusSuccess != (status = cipher(CFB, key, bufferOut)))
		{
			goto CleanUp;
		}
		for (i; i < inSize; ++i)
		{
			out[i] = in[i] ^ bufferOut[i % 8];
		}
	}

CleanUp:
	if (CFB)
	{
		free(CFB);
	}
	if (bufferOut)
	{
		free(bufferOut);
	}
	return status;
}
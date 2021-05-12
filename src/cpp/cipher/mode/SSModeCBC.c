#include "SSMode.h"

ssStatus ssEncryptModeCBC(
	const uint8_t* in, 
	size_t inSize, 
	const uint8_t* key, 
	size_t keySize, 
	uint8_t* out, 
	size_t outSize, 
	const uint8_t* iv, 
	size_t ivSize, 
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* CBC, size_t* OFBSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out), 
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	ssStatus status = SSStatusSuccess;
	size_t i = 0;
	size_t blockSize = 0;
	uint8_t* CBC = NULL;
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
	CBC = (uint8_t*)malloc(ivSize);
	if (SSStatusSuccess != (status = init(iv, ivSize, CBC, &ivSize)))
	{
		goto CleanUp;
	}

	bufferOut = (uint8_t*)malloc(blockSize);
	for (i; blockSize + i <= inSize; i += blockSize)
	{
		if (ivSize != blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				CBC[k] = in[i + k] ^ CBC[k];
			}
			if (SSStatusSuccess != (status = (cipher(CBC, key, bufferOut))))
			{
				goto CleanUp;
			}
			for (size_t k = 0; k < ivSize - blockSize; ++k)
			{
				CBC[k] = CBC[blockSize + k];
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				CBC[ivSize - blockSize + k] = bufferOut[k];
				out[i + k] = bufferOut[k];
			}
		}
		else if (ivSize == blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				CBC[k] = in[i + k] ^ CBC[k];
			}
			if (SSStatusSuccess != (status = (cipher(CBC, key, bufferOut))))
			{
				goto CleanUp;
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				CBC[k] = bufferOut[k];
				out[i + k] = bufferOut[k];
			}
		}
	}

	if (i != inSize)
	{
		uint8_t* block = (uint8_t*)malloc(blockSize);
		if (SSStatusSuccess != (status = padding(in, inSize - i, block, &blockSize)))
		{
			if (block)
			{
				free(block);
			}
			goto CleanUp;
		}
		if (SSStatusSuccess != (status = cipher(CBC, key, out + i)))
		{
			if (block)
			{
				free(block);
			}
			goto CleanUp;
		}
	}

CleanUp:
	if (CBC)
	{
		free(CBC);
	}
	if (bufferOut)
	{
		free(bufferOut);
	}
	return status;
}

ssStatus ssDecryptModeCBC(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	const uint8_t* iv,
	size_t ivSize,
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* CBC, size_t* OFBSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	ssStatus status = SSStatusSuccess;
	size_t i = 0;
	size_t blockSize = 0;
	uint8_t* CBC = NULL;
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
	CBC = (uint8_t*)malloc(ivSize);
	bufferOut = (uint8_t*)malloc(blockSize);
	if (SSStatusSuccess != (status = init(iv, ivSize, CBC, &ivSize)))
	{
		goto CleanUp;
	}

	for (i; blockSize + i <= inSize; i += blockSize)
	{
		if (SSStatusSuccess != (status = (cipher(&in[i], key, bufferOut))))
		{
			goto CleanUp;
		}
		if (ivSize != blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ CBC[k];
			}
			for (size_t k = 0; k < ivSize - blockSize; ++k)
			{
				CBC[k] = CBC[blockSize + k];
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				CBC[ivSize - blockSize + k] = in[i + k];
			}
		}
		else if (ivSize == blockSize)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				out[i + k] = bufferOut[k] ^ CBC[k];
				CBC[k] = in[i + k];
			}
		}
	}

	if (i != inSize)
	{
		uint8_t* block = (uint8_t*)malloc(blockSize);
		if (SSStatusSuccess != (status = padding(in, inSize - i, block, &blockSize)))
		{
			if (block)
			{
				free(block);
			}
			goto CleanUp;
		}
		if (SSStatusSuccess != (status = cipher(&in[i], key, bufferOut)))
		{
			if (block)
			{
				free(block);
			}
			goto CleanUp;
		}
		for (size_t k = 0; k < blockSize; ++k)
		{
			out[i + k] = bufferOut[k] ^ CBC[k];
		}
	}

CleanUp:
	if (CBC)
	{
		free(CBC);
	}
	if (bufferOut)
	{
		free(bufferOut);
	}
	return status;
}
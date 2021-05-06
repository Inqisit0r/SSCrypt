#include "SSMode.h"

ssStatus ssModeMAC(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	ssStatus(*padding01)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize))
{
	uint8_t* B = NULL;
	uint8_t* K = NULL;
	uint8_t* buffer = NULL;
	uint8_t* bufferIn = NULL;
	size_t i = 0;
	size_t blockSize = 0;
	ssStatus status = SSStatusSuccess;
	if ((in == NULL) || (inSize == 0) || (key == NULL) || (keySize == 0) || (out == NULL) || (outSize == 0))
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
	B = (uint8_t*)malloc(blockSize);
	K = (uint8_t*)malloc(blockSize);

	//Получаем R
	memset(K, 0x00, blockSize);

	if (SSStatusSuccess != (status = cipher(K, key, K)))
	{
		goto CleanUp;
	}

	//Получаем B
	memset(B, 0x00, blockSize - 2);
	if (blockSize == MAGMA_BLOCK_SIZE)
	{
		B[blockSize - 1] = 0x1b;
	}
	else if (blockSize == KYZNECHIK_BLOCK_SIZE)
	{
		B[blockSize - 1] = 0x87;
	}
	else	
	{
		status = SSStatusNotSupported;
		goto CleanUp;
	}
	
	if ((blockSize == MAGMA_BLOCK_SIZE) || (blockSize == KYZNECHIK_BLOCK_SIZE))
	{
		//Получаем K1
		uint64_t a = ssConv8to64(K);
		uint64_t b = ssConv64to8(B);
		if (a >> 63)
		{
			a = (a << 1) ^ b;
		}
		else
		{
			a = a << 1;
		}
		//Получаем K2
		if (inSize % blockSize != 0)
		{
			if (a >> 63)
			{
				a = (a << 1) ^ b;
			}
			else
			{
				a = a << 1;
			}
		}
		ssSet64to8(a, K);
	}
	else if ((blockSize != MAGMA_BLOCK_SIZE) && (blockSize != KYZNECHIK_BLOCK_SIZE))
	{
		status = SSStatusNotSupported;
		goto CleanUp;
	}

	//Вычисляем имитовставку
	buffer = (uint8_t*)malloc(blockSize);
	bufferIn = (uint8_t*)malloc(blockSize);

	if (inSize != blockSize)
	{
		for (size_t k = 0; k < blockSize; ++k)
		{
			buffer[k] = in[k];
		}
		while (i + blockSize <= inSize - 2 * blockSize)
		{
			if (SSStatusSuccess != (status = cipher(buffer, key, out)))
			{
				goto CleanUp;
			}
			i += blockSize;
			for (size_t k = 0; k < blockSize; ++k)
			{
				buffer[k] = in[i + k] ^ out[k];
			}
		}
		if (SSStatusSuccess != (status = cipher(buffer, key, out)))
		{
			goto CleanUp;
		}
		i += blockSize;

		if (inSize % blockSize == 0)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				buffer[k] = in[i + k] ^ out[k] ^ K[k];
			}
			if (SSStatusSuccess != (status = cipher(buffer, key, out)))
			{
				goto CleanUp;
			}
		}
		else if (inSize % blockSize != 0)
		{
			if (SSStatusSuccess != (status = padding01(in[i], inSize, bufferIn, blockSize)))
			{
				goto CleanUp;
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				buffer[k] = bufferIn[k] ^ out[k] ^ K[k];
			}
			if (SSStatusSuccess != (status = cipher(buffer, key, out)))
			{
				goto CleanUp;
			}
		}
	}
	else if (inSize == blockSize)
	{
		if (inSize % blockSize == 0)
		{
			for (size_t k = 0; k < blockSize; ++k)
			{
				buffer[k] = in[k] ^ K[k];
			}
			if (SSStatusSuccess != (status = cipher(buffer, key, out)))
			{
				goto CleanUp;
			}
		}
		else if (inSize % blockSize != 0)
		{
			if (SSStatusSuccess != (status = padding01(in, inSize, bufferIn, blockSize)))
			{
				goto CleanUp;
			}
			for (size_t k = 0; k < blockSize; ++k)
			{
				buffer[k] = bufferIn[k] ^ K[k];
			}
			if (SSStatusSuccess != (status = cipher(buffer, key, out)))
			{
				goto CleanUp;
			}
		}
	}

CleanUp:
	if (B)
	{
		free(B);
	}
	if (K)
	{
		free(K);
	}
	if (buffer)
	{
		free(buffer);
	}
	if (bufferIn)
	{
		free(bufferIn);
	}
	return status;
}
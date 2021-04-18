#include "SSMode.h"

void getBlock(uint8_t* in, size_t blockSize, uint8_t* out, int k)
{
	for (int i = 0; i < (int)(blockSize / 8); ++i)
	{
		out[i] = in[k * 8 + i];
	}
}

void setBlock(uint8_t* in, size_t blockSize, uint8_t* out, int k)
{
	for (int i = 0; i < (int)(blockSize / 8); ++i)
	{
		out[k * 8 + i] = in[i];
	}
}

ssStatus ssEncryptModeCTR(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize)
{
	if (blockSize == 64)
	{
		return SSStatusSuccess;
	}
	else if (blockSize == 128)
		return SSStatusNotSupported;
}

ssStatus ssDecryptModeCTR(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize)
{
	if (blockSize == 64)
	{
		return SSStatusSuccess;
	}
	else if (blockSize == 128)
		return SSStatusNotSupported;
}

ssStatus ssModeCTR(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, int reverse)
{
	if ((in == NULL) || (key == NULL) || (out == NULL) || ((blockSize % 8) != 0))
	{
		return SSStatusInvalidParameter;
	}

	if (reverse == 0x00)
		ssEncryptModeCTR(in, inSize, key, keySize, out, outSize, blockSize);
	else if (reverse == 0x01)
		ssDecryptModeCTR(in, inSize, key, keySize, out, outSize, blockSize);
	else
		return SSStatusError;
}
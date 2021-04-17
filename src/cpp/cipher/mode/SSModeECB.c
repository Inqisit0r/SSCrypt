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

ssStatus ssEncryptModeECB(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, ssPaddingMode padding)
{
	if (blockSize == 64)
	{
		uint8_t inMagmaBlock[8] = { 0 };
		uint8_t outMagmaBlock[8] = { 0 };
			for (int i = 0; i < (int)(outSize / 8); ++i)
			{
				getBlock(in, 64, inMagmaBlock, i);
				ssSwab8_64(inMagmaBlock);
				ssEncryptBlockMagma(inMagmaBlock, key, outMagmaBlock);
				ssSwab8_64(outMagmaBlock);
				setBlock(outMagmaBlock, 64, out, i);
			}
			return SSStatusSuccess;
	}
	else if (blockSize == 128)
		return SSStatusNotSupported;
}

ssStatus ssDecryptModeECB(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, ssPaddingMode padding)
{
	if (blockSize == 64)
	{
		uint8_t inMagmaBlock[8] = { 0 };
		uint8_t outMagmaBlock[8] = { 0 };
		for (int i = 0; i < (int)(outSize / 8); ++i)
		{
			getBlock(in, 64, inMagmaBlock, i);
			ssSwab8_64(inMagmaBlock);
			ssDecryptBlockMagma(inMagmaBlock, key, outMagmaBlock);
			ssSwab8_64(outMagmaBlock);
			setBlock(outMagmaBlock, 64, out, i);
		}
		return SSStatusSuccess;
	}
	else if (blockSize == 128)
		return SSStatusNotSupported;
}

ssStatus ssModeECB(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, ssPaddingMode padding, int reverse)
{
	if ((in == NULL) || (key == NULL) || (out == NULL) || ((blockSize % 8) != 0))
	{
		return SSStatusInvalidParameter;
	}

	if (padding == ssIdPadding00)
		ssPadding01(in, inSize, out, outSize);
	else if (padding == ssIdPadding01)
		ssPadding03(in, inSize, out, outSize);
	else
		return SSStatusInvalidParameter;

	if (reverse == 0x00)
		ssEncryptModeECB(in, inSize, key, keySize, out, outSize, blockSize, padding);
	else if (reverse == 0x01)
		ssDecryptModeECB(in, inSize, key, keySize, out, outSize, blockSize, padding);
	else
		return SSStatusError;
}
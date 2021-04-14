#include "SSEcb.h"

ssStatus ecb(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize)
{
	if ((in == NULL) || (key == NULL) || (out == NULL) || ((blockSize % 8) != 0))
	{
		return SSStatusInvalidParameter;
	}
	//if (blockSize == 64)
	//{

	//}
	return SSStatusNotSupported;
}

void padding(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize)
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
}
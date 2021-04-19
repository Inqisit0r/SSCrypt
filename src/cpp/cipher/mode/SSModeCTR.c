#include "SSMode.h"

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
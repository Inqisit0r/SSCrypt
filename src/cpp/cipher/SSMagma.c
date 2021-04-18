#include "SSMagma.h"

uint32_t getRoundKey(int i, uint8_t* k)
{
	if (i < 24)
	{
		return ssSwap32(*((uint32_t*)(k + (i % 8) * 4)));
	}
	else
	{
		return ssSwap32(*((uint32_t*)(k + (7 - (i % 8)) * 4)));
	}
}

uint32_t t(uint32_t a)
{
	uint32_t result = 0;
	for (int i = 0; i < 8; ++i)
	{
		result = (result << 4) | s_box[i][(a << (4 * i) & 0xF0000000) >> 28];
	}
	return result;
}

uint32_t g(uint32_t a, uint32_t k)
{
	uint32_t sum = t(a + k);
	uint32_t result = sum;
	result = result << 11 | result >> 21;
	return result;
}

uint64_t G(uint32_t a1, uint32_t a0, uint32_t k)
{
	uint64_t result = a0;
	result <<= 32;
	result |= g(a0, k) ^ a1;
	return result;
}

uint64_t G1(uint32_t a1, uint32_t a0, uint32_t k)
{
	uint64_t result = g(a0, k) ^ a1;
	result <<= 32;
	result |= a0;
	return result;
}

void encrypt(uint8_t* input, uint8_t* key, uint8_t* output)
{
	uint64_t in = ssSwap64(conv8to64(input));
	uint64_t out = 0;
	int i = 0;

	uint32_t a1 = (uint32_t)(in >> 32);
	uint32_t a0 = (uint32_t)in;

	for (i; i < 31; ++i)
	{
		out = G(a1, a0, getRoundKey(i, key));
		a1 = a0;
		a0 = (uint32_t)(out);
	}
	out = G1(a1, a0, getRoundKey(31, key));
	ssSwat64(ssSwap64(out), output);
}

void decrypt(uint8_t* input, uint8_t* key, uint8_t* output)
{
	uint64_t in = ssSwap64(conv8to64(input));
	uint64_t out = 0;
	int i = 0;

	uint32_t b1 = (uint32_t)(in >> 32);
	uint32_t b0 = (uint32_t)in;

	for (i; i < 31; ++i)
	{
		out = G(b1, b0, getRoundKey((31 - i), key));
		b1 = b0;
		b0 = (uint32_t)(out);
	}
	out = G1(b1, b0, getRoundKey(0, key));
	ssSwat64(ssSwap64(out), output);
}

ssStatus crypt(uint8_t* in, uint8_t* key, uint8_t* out, int reverse)
{
	if ((in == NULL) || (key == NULL) || (out == NULL))
	{
		return SSStatusInvalidParameter;
	}
	if (reverse == 0x00)
	{
		encrypt(in, key, out);
		return SSStatusSuccess;
	}
	else if (reverse == 0x01)
	{
		decrypt(in, key, out); 
		return SSStatusSuccess;
	}
	return SSStatusError;
}

ssStatus ssEncryptBlockMagma(uint8_t* in, uint8_t* key, uint8_t* out)
{
	return crypt(in, key, out, 0x00);
}

ssStatus ssDecryptBlockMagma(uint8_t* in, uint8_t* key, uint8_t* out)
{
	return crypt(in, key, out, 0x01);
}
#ifndef SSMODE_H
#define SSMODE_H

#include "SSPadding.h"
#include "SSMagma.h"
#include "SSShifts.h"
#include <stdio.h>

ssStatus ssModeECB(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

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
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

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
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

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
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

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
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

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
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

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
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

ssStatus ssModeMAC(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	ssStatus(*padding01)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

#endif //!SSMODE_H
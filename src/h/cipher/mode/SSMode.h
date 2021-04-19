#ifndef SSMODE_H
#define SSMODE_H

#include "SSPadding.h"
#include "SSMagma.h"

/** @brief Шифрование, используя режим шифрование ECB
* 
*	@param[reverse = 0x00] - зашифрование
*	@param[reverse = 0x01] - расшифрование
*/
ssStatus ssModeECB(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t* outSize,
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

ssStatus ssModeCTR(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, int reverse);

#endif //!SSMODE_H
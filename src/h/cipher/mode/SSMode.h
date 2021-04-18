#ifndef SSMODE_H
#define SSMODE_H

#include "SSPadding.h"
#include "SSMagma.h"

/** @brief ����������, ��������� ����� ���������� ECB
* 
*	@param[reverse = 0x00] - ������������
*	@param[reverse = 0x01] - �������������
*/
ssStatus ssModeECB(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, ssPaddingMode padding, ssCipherAlgorithms algorythm, int reverse);

ssStatus ssModeCTR(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize, int reverse);

#endif //!SSMODE_H
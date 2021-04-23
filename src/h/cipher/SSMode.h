#ifndef SSMODE_H
#define SSMODE_H

#include "SSPadding.h"
#include "SSMagma.h"
#include <stdio.h>

/*  @brief ����������, ��������� ����� ���������� ECB
* 
*	@param[reverse = 0x00] - ������������
*	@param[reverse = 0x01] - �������������
*/
ssStatus ssModeECB(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

/*	@brief ����������, ��������� ����� ���������� CTR
*
*	@param[iv]		- ������ �������������, ������ 32-� �����
*	@param[*init]	- ������� ���������� iv �� ������� ������� blockSize 
*					  (������������: ssPaddingMAGMA00, ��� ssPaddingKYZNECHIK00)
*/
ssStatus ssModeCTR(
	const uint8_t* in,
	size_t inSize,
	const uint8_t* key,
	size_t keySize,
	uint8_t* out,
	size_t outSize,
	const uint8_t* iv,
	size_t ivSize,
	ssStatus(*init)(uint8_t* iv, size_t ivSize, uint8_t* CTR, size_t CTRSize),
	ssStatus(*cipher)(uint8_t* in, uint8_t* key, uint8_t* out),
	ssStatus(*padding)(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize));

#endif //!SSMODE_H
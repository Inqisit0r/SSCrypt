#ifndef SSCIPHER_H
#define SSCIPHER_H

#include "SSCipher_p.h"

/** @brief ��������� ���������� */
typedef enum ssCipherAlgorithms_t {
	ssIdCipherAlgorithmMagma,
	ssIdCipherAlgorithmKyznechik
} ssCipherAlgorithms;

/** @brief ������ ���������� */
typedef enum ssCipherMode_t {
	ssIdCipherModeECB,
	ssIdCipherModeCTR,
	ssIdCipherModeOFB,
	ssIdCipherModeCBC,
	ssIdCipherModeCFB,
	ssIdCipherModeMAC
} ssCipherMode;

/** @brief �������� */
typedef enum ssPaddingMode_t {
	ssIdPadding00,
	ssIdPadding01,
	ssIdPaddingCTR
} ssPaddingMode;

/** @brief ���������� �������� �������� ������� "vIn" ������� "sInSize",
*		��������� ��������� � �������� ������ "vOut" ��� ����������� ������� ��������� � "psOutSize".
*		�������� � ����� ���������� ����������� � ���������� "eAlgorithm", "eMode" ��������������.
*		��� ��������� ������� ���������� ���������� �������� ������ ������������� � "cvIv" �������� "psIvSize".
*		���� �������� "vOut" = null, �� � ��������� "psOutSize" ����� ������ ����������� ������ ������ ��� ���������� ������� "cvIn".
*		������� ������� � "psOutSize" ����������� ����������� ������������� ����.
*
*	@param[in]		eAlgorithm	�������� ����������
*	@param[in]		eMode		����� ����������
*	@param[in]		cvIn		������� ������� ������
*	@param[in]		sInSize		������ �������� ������� (� ������)
*	@param[in]		cvKey		�������� ������� ������
*	@param[in]		sKeySize	������ ��������� ������� (� ������)
*	@param[in]		cvIv		������� ������ � �������� �������������
*	@param[in]		psIvSize	������ ������� ������������� (� ������)
*	@param[out]		vOut		�������� ������� ������
*	@param[in_out]	psOutSize	������ ��������� ������� (� ������)
*	@return ������ ��������
*/
ssStatus ssEncrypt(
	__in	ssCipherAlgorithms	eAlgorithm,
	__in	ssCipherMode		eMode,
	__in	const void*			cvIn,
	__in	size_t				sInSize,
	__in	const void*			cvKey,
	__in	size_t				sKeySize,
	__in	const void*			cvIv,
	__in	size_t				psIvSize,
	__out	void*				vOut,
	__inout	size_t*				psOutSize);

/** @brief ������������� �������� �������� ������� "vIn" ������� "sInSize",
*		��������� ��������� � �������� ������ "vOut" ��� ����������� ������� ��������� � "psOutSize".
*		�������� � ����� ���������� ����������� � ���������� "eAlgorithm", "eMode" ��������������.
*		��� ��������� ������� ���������� ���������� �������� ������ ������������� � "cvIv" �������� "psIvSize".
*		���� �������� "vOut" = null, �� � ��������� "psOutSize" ����� ������ ����������� ������ ������ ��� ���������� ������� "cvIn".
*
*	@param[in]		eAlgorithm	�������� ����������
*	@param[in]		eMode		����� ����������
*	@param[in]		cvIn		������� ������� ������
*	@param[in]		sInSize		������ �������� ������� (� ������)
*	@param[in]		cvKey		�������� ������� ������
*	@param[in]		sKeySize	������ ��������� ������� (� ������)
*	@param[in]		cvIv		������� ������ � �������� �������������
*	@param[in]		psIvSize	������ ������� ������������� (� ������)
*	@param[out]		vOut		�������� ������� ������
*	@param[in_out]	psOutSize	������ ��������� ������� (� ������)
*	@return ������ ��������
*/
ssStatus ssDecrypt(
	__in	ssCipherAlgorithms	eAlgorithm,
	__in	ssCipherMode		eMode,
	__in	const void*			cvIn,
	__in	size_t				sInSize,
	__in	const void*			cvKey,
	__in	size_t				sKeySize,
	__in	const void*			cvIv,
	__in	size_t				psIvSize,
	__out	void*				vOut,
	__inout	size_t*				psOutSize);

/** @brief ��������� ��� �������� ��������� ���������� */
typedef struct ssEncryptionCtx_t ssEncryptionCtx;

/** @brief ������������� ��������� ��� ��������� ����������
*
*	@param[in_out]	sCtx	�������� ����������
*	@return ������ ��������
*/
ssStatus ssEncryptionCtxInit(
	__inout ssEncryptionCtx* sCtx);

/** @brief ������� ��������� ����������
*
*	@param[in_out]	sCtx	�������� ����������
*	@return ������ ��������
*/
ssStatus ssEncryptionCtxFree(
	__in ssEncryptionCtx* sCtx);

/** @brief ����� ���������� (����������� ���������� ��������)*/
typedef enum ssCipherPropertyName_t {
	ssCipherPropertyAlgorithm,
	ssCipherPropertyMode
} ssCipherPropertyName;

/** @brief ��������� ���������� � ��������
*
*	@param[in_out]	sCtx			��������
*	@param[in]		ePropertyKey	���� ���������
*	@param[in]		strValue		������������� �������� ���������
*	@return ������ ��������
*/
ssStatus ssEncryptionSetProperty(
	__inout	ssEncryptionCtx			sCtx,
	__in	ssCipherPropertyName	ePropertyKey,
	__in	const char*				strValue);

/** @brief ����� ���������� (������� �������) */
typedef enum ssCipherPropertyByteVectorName_t {
	ssCipherPropertyIV,
	ssCipherPropertyKey
} ssCipherPropertyByteVectorName;

/** @brief ��������� ���������� � ��������
*
*	@param[in_out]	sCtx			��������
*	@param[in]		ePropertyKey	���� ���������
*	@param[in]		cvValue			������� ������ - �������� ���������
*	@return ������ ��������
*/
ssStatus ssEncryptionSetPropertyByteVector(
	__inout	ssEncryptionCtx					sCtx,
	__in	ssCipherPropertyByteVectorName	ePropertyKey,
	__in	const void*						cvValue);

/** @brief �������� ���������� �������� ����� "cvIn", ���������� ���������� ����� �������������� �� �����.
*		���� ����� ������� � �������� � ��������� ������� ����������� �� ���������� tnEncryptionUpdate().
*		���� �������� "vOut"=null, � �������� "psOutSize" ����� ������� ������ ������� ����������� ��� ��������� ��������� ��������.
*		������� ���������� � "psOutSize" ����������� ����������� ������������� ����.
*
*	@param[in]		sCtx		�������� ����������
*	@param[in]		cvIn		������� ������� ������
*	@param[in]		sInSize		������ �������� ������� (� ������)
*	@param[out]		vOut		�������� ������� ������
*	@param[in_out]	psOutSize	������ ��������� ������� (� ������)
*	@return ������ ��������
*/
ssStatus ssEncryptionUpdate(
	__in	ssEncryptionCtx	sCtx,
	__in	const void*		cvIn,
	__in	size_t			sInSize,
	__out	void*			vOut,
	__inout	size_t*			psOutSize);

/** @brief ����������� Update ��������� ����������. ��������� ���� ����� �� ������������� �������� �� ������� ����� � ����������.
*		���� �������� "vOut"=null, � �������� "psOutSize" ����� ������� ������ ������� ����������� ��� ��������� ��������� ��������.
*		������� ���������� � "psOutSize" ����������� ����������� ������������� ����.
*
*	@param[in]		sCtx		�������� ����������
*	@param[in]		cvIn		������� ������� ������
*	@param[in]		sInSize		������ �������� ������� (� ������)
*	@param[out]		vOut		�������� ������� ������
*	@param[in_out]	psOutSize	������ ��������� ������� (� ������)
*	@return ������ ��������
*/
ssStatus ssEncryptionFinalUpdate(
	__in	ssEncryptionCtx sCtx,
	__in	const void*		cvIn,
	__in	size_t			sInSize,
	__out	void*			vOut,
	__inout	size_t*			psOutSize);

#endif //!SSCIPHER_H
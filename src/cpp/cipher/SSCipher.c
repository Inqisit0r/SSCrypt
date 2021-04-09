#include "../../../include/SSCipher.h"
#include "../../h/cipher/SSCipher_p.h"

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
	__inout	size_t*				psOutSize)
{
	return SSStatusNotSupported;
}

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
	__inout	size_t*				psOutSize)
{
	return SSStatusNotSupported;
}

ssStatus ssEncryptionCtxInit(
	__inout ssEncryptionCtx* sCtx)
{
	return SSStatusNotSupported;
}

ssStatus ssEncryptionCtxFree(
	__in ssEncryptionCtx* sCtx)
{
	return SSStatusNotSupported;
}

ssStatus ssEncryptionSetProperty(
	__inout	ssEncryptionCtx			sCtx,
	__in	ssCipherPropertyName	ePropertyKey,
	__in	const char*				strValue)
{
	return SSStatusNotSupported;
}

ssStatus ssEncryptionSetPropertyByteVector(
	__inout	ssEncryptionCtx					sCtx,
	__in	ssCipherPropertyByteVectorName	ePropertyKey,
	__in	const void*						cvValue)
{
	return SSStatusNotSupported;
}

ssStatus ssEncryptionUpdate(
	__in	ssEncryptionCtx	sCtx,
	__in	const void*		cvIn,
	__in	size_t			sInSize,
	__out	void*			vOut,
	__inout	size_t*			psOutSize)
{
	return SSStatusNotSupported;
}

ssStatus ssEncryptionFinalUpdate(
	__in	ssEncryptionCtx sCtx,
	__in	const void*		cvIn,
	__in	size_t			sInSize,
	__out	void*			vOut,
	__inout	size_t*			psOutSize)
{
	return SSStatusNotSupported;
}

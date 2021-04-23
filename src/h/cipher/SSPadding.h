#ifndef SSPADDING_H
#define SSPADDING_H

#define MAGMA_BLOCK_SIZE 8
#define KYZNECHIK_BLOCK_SIZE 16

#include "SSCrypt.h"
#include "Source.h"

ssStatus ssPaddingMAGMA00(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize);

ssStatus ssPaddingMAGMA01(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize);

ssStatus ssPaddingKYZNECHIK00(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize);

ssStatus ssPaddingKYZNECHIK01(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize);

#endif //!SSPADDING_H
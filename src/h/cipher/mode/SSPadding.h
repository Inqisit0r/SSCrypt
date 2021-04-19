#ifndef SSPADDING_H
#define SSPADDING_H

#define MAGMA_BLOCK_SIZE 8

#include "SSCrypt.h"
#include "Source.h"

ssStatus ssPaddingMAGMA00(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize);

ssStatus ssPaddingMAGMA01(uint8_t* in, size_t inSize, uint8_t* block, size_t* blockSize);

#endif //!SSPADDING_H
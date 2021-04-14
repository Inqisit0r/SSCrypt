#ifndef SSECB_H
#define SSECB_H

#include "SSMagma.h"

ssStatus ecb(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize);

#endif //!SSECB_H
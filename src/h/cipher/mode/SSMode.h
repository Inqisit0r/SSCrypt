#ifndef SSMODE_H
#define SSMODE_H

#include "SSPadding.h"
#include "SSMagma.h"

ssStatus ssModeECB(uint8_t* in, size_t inSize, uint8_t* key, size_t keySize, uint8_t* out, size_t outSize, size_t blockSize);

#endif //!SSMODE_H
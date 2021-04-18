#ifndef SSPADDING_H
#define SSPADDING_H

#include "SSCrypt.h"
#include "Source.h"

ssStatus ssPadding01(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize);

ssStatus ssPadding02(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize);

ssStatus ssPadding03(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize);

ssStatus ssPaddingCTR(uint8_t* in, size_t inSize, uint8_t* out, size_t outSize);

#endif //!SSPADDING_H
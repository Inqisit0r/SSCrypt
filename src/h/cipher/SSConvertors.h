#ifndef SSCONVERTORS_H
#define SSCONVERTORS_H

#include "Source.h"

uint64_t ssConv8to64(uint8_t* a);

uint8_t ssConv64to8(uint64_t a);

void ssSet64to8(uint64_t a, uint8_t* b);

#endif //!SSCONVERTORS_H

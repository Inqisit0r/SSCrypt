#ifndef SSSWAPS_H
#define SSSWAPS_H

#include "Source.h"

uint16_t ssSwap16(uint16_t a);

uint16_t ssSwab16(uint8_t* a);

void ssSwat16(uint16_t a, uint8_t* b);


uint32_t ssSwap32(uint32_t a);

uint32_t ssSwab32(uint8_t* a);

void ssSwat32(uint32_t a, uint8_t* b);


uint64_t ssSwap64(uint64_t a);

uint64_t ssSwab64(uint8_t* a);

void ssSwat64(uint64_t a, uint8_t* b);

#endif //!SSSWAPS_H

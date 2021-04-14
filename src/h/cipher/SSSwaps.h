#ifndef SSSWAPS_H
#define SSSWAPS_H

#include "Source.h"

uint16_t swap16(uint16_t a);

uint16_t swab16(uint8_t* a);

void swat16(uint16_t a, uint8_t* b);


uint32_t swap32(uint32_t a);

uint32_t swab32(uint8_t* a);

void swat32(uint32_t a, uint8_t* b);


uint64_t swap64(uint64_t a);

uint64_t swab64(uint8_t* a);

void swat64(uint64_t a, uint8_t* b);

#endif //!SSSWAPS_H

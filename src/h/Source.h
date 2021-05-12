#ifndef SOURCE_H
#define SOURCE_H

#include <stdint.h>
#include "SSStatus.h"
#include <string.h>
#include <stdlib.h>

#ifndef bool
typedef int ssbool;
#endif
#ifndef ssfalse
#define ssfalse 0x00
#endif
#ifndef sstrue
#define sstrue !ssfalse
#endif


#endif //SOURCE_H
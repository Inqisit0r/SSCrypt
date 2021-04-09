#ifndef SSPCIPHER_H
#define SSPCIPHER_H

#include "../Source.h"
#include "../../../include/SSStatus.h"

struct ssEncryptionCtx_t {
	uint8_t* initializationVector;
	size_t initializationVectorSize;
};

#endif //!SSPCIPHER_H

#ifndef SSSTATUS_H
#define SSSTATUS_H

typedef enum ssStatus_t {
	SSStatusSuccess\
	= 0x00000000,
	SSStatusError\
	= 0x80000000,
	SSStatusInvalidParameter\
	= 0x80000001,
	SSStatusNotSupported\
	= 0x80000002
} ssStatus;

#endif //!SSSTATUS_H

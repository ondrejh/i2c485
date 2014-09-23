/** comm.h communication module header */

#ifndef __COMM_H__
#define __COMM_H__

#include <inttypes.h>

#define FRAME_MAX_LENGTH 64
#define CR 0x0D
#define LF 0x0A

void comm_rx_char(uint8_t c, uint8_t error);

#endif

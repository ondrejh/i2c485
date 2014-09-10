/** comm.c communication module

   It's used as the receive buffer of the uart.c module.
   Implementing ModBus ASCII mode like protocol. */

#include <inttypes.h>

#include "comm.h"

#include <avr/io.h>
#define LED_SWAP() do{PORTC^=0x02;}while(0)

/// hex char into int conversion
int8_t hexc2int(uint8_t c)
{
    if ((c>='0') && (c<='9')) return c-'0'; // 0 - 9
    if ((c>='A') && (c<='F')) return c-'A'+10; // A - F
    return -1; // error (no hex char)
}

void use_checked_frame(uint8_t addr, uint8_t fcn, uint8_t* data, uint8_t dlen)
{
    LED_SWAP();
}

void use_frame(uint8_t* frame, uint8_t flen)
{
    uint8_t addr = *frame++;
    uint8_t fcn = *frame++;
    uint8_t lrc = addr + fcn;

    for (int i=2;i<(flen-1);i++) lrc += *frame++;

    if (lrc==frame[flen-1])
    {
        use_checked_frame(addr,fcn,&frame[2],flen-3);
    }
    //else lrc error
}

void comm_rx_char(uint8_t c, uint8_t error)
{
    static uint8_t frame[FRAME_MAX_LENGTH];
    static uint8_t frame_ptr = 0;
    static uint8_t high_nibbles = 0x80;

    if ((error!=0)||(c==':')) // start
    {
        frame_ptr = 0;
        high_nibbles = 0;
    }
    else if (c==CR) // end
    {
        use_frame(frame,frame_ptr);
    }
    else if (c!=LF)
    {
        if (high_nibbles==0x80) high_nibbles=hexc2int(c);
        else
        {
            if (frame_ptr<FRAME_MAX_LENGTH) frame[frame_ptr++] = (high_nibbles<<4)|hexc2int(c);
            high_nibbles = 0x80;
        }
    }
}

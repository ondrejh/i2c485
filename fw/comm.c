/** comm.c communication module

   It's used as the receive buffer of the uart.c module.
   Implementing ModBus ASCII mode like protocol. */

#include <inttypes.h>

#include "comm.h"
//#include "uart.h"

#include <avr/io.h>
#define LED_SWAP() do{PORTC^=0x02;}while(0)

#define BROADCAST_ADDRESS 0x00

const uint8_t* manufacturer_name = (const uint8_t*)"ondrejh.ck@email.cz";
const uint8_t* product_code = (const uint8_t*)"i2c485";
const uint8_t* version_number = (const uint8_t*)"0.0001beta";

uint8_t device_address = 0x01;

void build_message(uint8_t* message, uint8_t addr, uint8_t fcn, uint8_t* data, uint8_t dlen)
{
}

/** hex char into int conversion
 The function is called from within comm_rx_char function.
 Later on it should be placed somewhere in the utils module. */
int8_t hexc2int(uint8_t c)
{
    if ((c>='0') && (c<='9')) return c-'0'; // 0 - 9
    if ((c>='A') && (c<='F')) return c-'A'+10; // A - F
    return -1; // error (no hex char)
}

/** the function is called from use_frame when lrc checksum fits
 Here is the right place to connect all the actions regarding to ascii modbus communication.
 Now it only changing LED status to show that something was correctly received. */
void use_checked_frame(uint8_t addr, uint8_t fcn, uint8_t* data, uint8_t dlen)
{
    if (addr==device_address)
    {
        switch (fcn)
        {
            default: // unknown function code

                break;
        }
    }
    else if (addr==BROADCAST_ADDRESS)
    {

    }
    LED_SWAP();
}

/** decompose incomming modbus ascii frame and check lrc
 The function gets whole frame buffer, decomposes it to address, function and data
 and checks lrc of the frame. If the LRC fits it pushes the data into use_checked frame function */
void use_frame(uint8_t* frame, uint8_t flen)
{
    uint8_t addr = *frame++;
    uint8_t fcn = *frame++;
    uint8_t lrc = addr + fcn;

    for (int i=2;i<(flen-1);i++) lrc += *frame++;
    lrc = 0xFF-lrc+1;

    if (lrc==*frame)
    {
        use_checked_frame(addr,fcn,&frame[2],flen-3);
    }
}

/** receive incommin character and put it into the frame buffer
 The function is connected to uart rx. It fills the frame buffer and
 if the message end condition is found it parses the frame buffer to
 the use_frame function */
void comm_rx_char(uint8_t c, uint8_t error)
{
    static uint8_t frame[FRAME_MAX_LENGTH];
    static uint8_t frame_ptr = 0;
    static uint8_t high_nibbles = 0x80;

    if ((error!=0)||(c==':')) // start
    {
        frame_ptr = 0;
        high_nibbles = 0x80;
    }
    else if ((c!=LF)&&(c!=CR))
    {
        if (high_nibbles==0x80) high_nibbles=hexc2int(c);
        else
        {
            if (frame_ptr<FRAME_MAX_LENGTH) frame[frame_ptr++] = (high_nibbles<<4)|hexc2int(c);
            high_nibbles = 0x80;
        }
    }
    else if (c==LF) use_frame(frame,frame_ptr);
}

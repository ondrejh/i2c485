/** uart module */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdbool.h>

#include "uart.h"
#include "comm.h"

#define TXBUFFLEN 32

uint8_t txbuffer[TXBUFFLEN];
uint8_t txbuf_inptr = 0;
uint8_t txbuf_outptr = 0;

/*/// hex char into int conversion
int8_t hexc2int(uint8_t c)
{
    if ((c>='0') && (c<='9')) return c-'0'; // 0 - 9
    if ((c>='A') && (c<='F')) return c-'A'+10; // A - F
    return -1; // error (no hex char)
}

/// int into hex char conversion
uint8_t int2hexc(int8_t i)
{
    if ((i>=0) && (i<=9)) return ('0'+i);
    if ((i>=0x0A) && (i<=0x0F)) return ('A'+i-10);
    return 0xFF;
}

/// dec char into int conversion
int8_t decc2int(char c)
{
    if ((c>='0') && (c<='9')) return c-'0'; // 0 - 9
    return -1; // error (no dec char)
}

int strlen(char* str)
{
    int cnt=0;
    for(;;)
    {
        if (*str++=='\0') return cnt;
        cnt++;
    }
}

void strcp(char* deststr, char* str)
{
    char c;
    do {
        c=*str++;
        *deststr++=c;
    }
    while (c!='\0');
}

/// print dec value
void sprint_int(char* str, int i)
{
    bool neg = false;
    char s[7];
    int8_t ptr=0;
    int dec = i;

    if (dec<0) {neg=true; dec=-dec;}

    do
    {
        s[ptr++]=int2hexc(dec%10);
        dec/=10;
    }
    while ((dec!=0) && (ptr<6));

    if (neg) s[ptr++]='-';

    ptr--;

    do
    {
        *str++ = s[ptr--];
    }
    while (ptr>=0);
    *str++='\0';
}*/

/// uart putchar function
int8_t uart_putchar(uint8_t c)
{
    // calculate buffer pointer
    uint8_t next_bufptr = txbuf_inptr+1;
    if (next_bufptr>=TXBUFFLEN) next_bufptr=0;
    // test for risk of buffer overflow
    if (next_bufptr==txbuf_outptr)
        return -1; // buffer full error
    txbuffer[txbuf_inptr]=c;
    // test if its first char (if yes then start tx)
    if (txbuf_outptr==txbuf_inptr)
    {
        TXEN_ON();
        UDR0 = c;

    } else UCSR0B |= (1<<UDRIE0);

    // push buffer pointer
    txbuf_inptr=next_bufptr;
    // return OK
    return 0;
}

/// printf
uint8_t uart_puts(char* str)
{
    uint8_t cnt = 0;
    char c = *str++;
    while(c!='\0')
    {
        if (uart_putchar(c)==0)
        {
            c = *str++;
            cnt++;
        }
        else break;
    }
    return cnt;
}

/// uart initialization
void init_uart(void)
{
    UCSR0A = (1<<U2X0);
    UCSR0B = (1<<RXCIE0) | (1<<TXCIE0) | /*(1<<UDRE0) |*/ (1<<TXEN0) | (1<<RXEN0);
    UCSR0C = (2<<UPM00) | (2<<UCSZ00); // parity EVEN, 7bits
    //UBRR0 = 5; // 9.6kBaud / 3.6864MHz/8
    UBRR0 = 2; // 19.2kBaud / 3.6864MHz/8
    TXEN_INIT();
}

/// receive complette interrupt handler
SIGNAL (USART_RX_vect)
//void usart_rx(void)
{
    uint8_t c;
    uint8_t error = 0;

    // test error flags
    if (UCSR0A&((1<<FE0)|(1<<DOR0)|(1<<UPE0))) error=1;

    c = UDR0;

    comm_rx_char(c,error);
}

/// tx buffer empty interrupt handler
SIGNAL (USART_UDRE_vect)
{
    // calculate buffer pointer
    uint8_t next_bufptr = txbuf_outptr+1;
    if (next_bufptr>=TXBUFFLEN) next_bufptr=0;

    // push buffer pointer
    txbuf_outptr=next_bufptr;

    // test if something left in the buffer (if any then transmitt it)
    if (txbuf_outptr!=txbuf_inptr)
    {
        TXEN_ON();
        UDR0=txbuffer[txbuf_outptr];
    }
    else
    {
        UCSR0B &= ~(1<<UDRIE0);
    }

}

/// transmit complette interrupt handler
SIGNAL (USART_TX_vect)
{
    if (UCSR0A & (1<<UDRE0)) TXEN_OFF();
}

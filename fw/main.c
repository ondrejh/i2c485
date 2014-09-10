/*
 */

#define F_CPU 3686400UL/8  // 3.68 MHz div 8 (460.8 kHz)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

#include "uart.h"

#define LED_INIT() do{PORTC&=0x02;DDRC|=0x02;}while(0)
#define LED_ON() do{PORTC|=0x02;}while(0)
#define LED_OFF() do{PORTC&=~0x02;}while(0)
#define LED_SWAP() do{PORTC^=0x02;}while(0)

int main(void)
{
    // init port
    LED_INIT();
    init_uart();
    sei();

    while (1) //loop
    {
        /*uart_puts("Ahoj");
        uart_puts("\n\r");
        LED_SWAP();*/
        _delay_ms(500);
    }

    return 0;
}

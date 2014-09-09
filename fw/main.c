/*
 */

#define F_CPU 3686400UL/8  // 3.68 MHz div 8 (460.8 kHz)

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "uart.c"

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

    int cnt = 0;

    while (1) //loop
    {
        cnt++; if (cnt>9) cnt=0;

        uart_puts("Ahoj");
        uart_putchar('0'+cnt);
        uart_puts("\n\r");
        LED_SWAP();
        _delay_ms(500);
    }

    return 0;
}

/*
 * soft_uart.c - GPIO-based UART
 * 04-07-2026 E. Brombaugh
 */

#ifndef __soft_uart__
#define __soft_uart__

#include <stdint.h>

void soft_uart_init(void);
void soft_uart_tx(uint8_t data);

#endif

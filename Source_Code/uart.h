#ifndef UART_H
#define UART_H

#include<LPC21xx.h>
extern unsigned char digits[5];
extern unsigned char validation;

void UART0_INIT(void);
void UART0_TX(unsigned char);
void UART0_STR(const char *);
void UART0_RX(void);
unsigned int UART0_INTEGER(const unsigned char *);

#endif

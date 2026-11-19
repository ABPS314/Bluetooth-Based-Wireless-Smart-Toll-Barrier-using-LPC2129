#ifndef LCD_H
#define LCD_H

#include <LPC21xx.h>

/* LCD data pins: D4, D5, D6, D7 */
#define DATA_PINS   (0x0F << 4)

/* LCD control pins */
#define RS          (1 << 8)
#define E           (1 << 9)

/* Function declarations */
void LCD_INIT(void);
void LCD_SEND_NIBBLE(unsigned char);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_ENABLE(void);
void delay_ms(unsigned int);
void LCD_STRING(unsigned char*);

#endif

#include "lcd.h"

/* Generate Enable pulse to latch data into LCD */
void LCD_ENABLE(void)
{
    IOSET0 = E;             // Enable HIGH
    delay_ms(1);            // Enable pulse duration
    IOCLR0 = E;             // Enable LOW
}

/*
 * Sends only one 4-bit nibble to LCD.
 * Used during initialisation before normal 4-bit communication.
 */
void LCD_SEND_NIBBLE(unsigned char data)
{
    IOCLR0 = DATA_PINS;                 // Clear previous data
    IOSET0 = ((data & 0x0F) << 4);     // Place nibble on P0.4-P0.7

    IOCLR0 = RS;                        // RS = 0: Instruction register

    LCD_ENABLE();                       // Latch the nibble
}

/*
 * LCD initialisation sequence.
 * Synchronises LCD and configures 4-bit interface.
 */
void LCD_INIT(void)
{
   
    IODIR0 |= DATA_PINS | RS | E;
    delay_ms(50);                       // Wait for LCD power-up

    /*
     * Force LCD into 4-bit communication mode.
     * Send individual nibbles, not complete commands.
     */
	/*Before communicating with hardware, 
	  establish a known initial state rather 
	  than assuming its internal state.*/
	
	//Establish known 8-bit interface state repetedly for 3 times 
    LCD_SEND_NIBBLE(0x03);// 0x03 =0011 0000
    delay_ms(5);

    LCD_SEND_NIBBLE(0x03);
    delay_ms(1);

    LCD_SEND_NIBBLE(0x03);
    delay_ms(1);
//Switch to 4-bit interface state
    LCD_SEND_NIBBLE(0x02); //0x02=0000 0010 in normal 8 bit  
    delay_ms(1);

    /* Normal 4-bit command communication starts here */

    LCD_COMMAND(0x28);  // 4-bit mode, 2 lines, 5x8 font
    LCD_COMMAND(0x0C);  // Display ON, cursor OFF
    LCD_COMMAND(0x01);  // Clear display
    delay_ms(2);
    LCD_COMMAND(0x06);  // Cursor increments, no display shift
}

/*
 * Sends an 8-bit command in two 4-bit transfers.
 * Upper nibble is transmitted first.
 */
void LCD_COMMAND(unsigned char cmd)
{
    IOCLR0 = DATA_PINS;
    IOCLR0 = RS;  // RS = 0: Command mode

    /* Transmit upper nibble */
    IOSET0 = ((cmd >> 4) & 0x0F) << 4;
    LCD_ENABLE();

    /* Transmit lower nibble */
    IOCLR0 = DATA_PINS;
    IOSET0 = (cmd & 0x0F) << 4;
    LCD_ENABLE();

    /* Allow command execution */
    delay_ms(2);
}

/*
 * Sends an 8-bit character as display data.
 * RS is HIGH for both nibble transfers.
 */
void LCD_DATA(unsigned char data)
{
    IOCLR0 = DATA_PINS;
    IOSET0 = RS;   // RS = 1: Data mode

    /* Transmit upper nibble */
    IOSET0 = ((data >> 4) & 0x0F) << 4;
    LCD_ENABLE();

    /* Transmit lower nibble */
    IOCLR0 = DATA_PINS;
    IOSET0 = RS;
    IOSET0 = (data & 0x0F) << 4;
    LCD_ENABLE();

    delay_ms(1);
}

/*
 * Millisecond delay using Timer1.
 *
 * Assumption: PCLK = 15 MHz.
 * Prescaler = 14999 gives a 1 ms timer tick.
 */
void delay_ms(unsigned int ms)
{
    T1TCR = 0x02;             // Reset Timer1
    T1PR = 14999;             // 15000 PCLK cycles = 1 ms
    T1TCR = 0x01;             // Start Timer1
    while (T1TC < ms);        // Wait for required milliseconds
    T1TCR = 0x00;             // Stop Timer1
}

void LCD_STRING(unsigned char*str)
{
	while(*str)
	{
		LCD_DATA(*str++);
	}
}

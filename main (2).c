#include <LPC21xx.h>
#include "ir_sensor.h"
#include "uart.h"
#include "lcd.h"
#include "servo.h"

volatile unsigned char object_detected = 0;

int main(void)
{
    unsigned char auth;
    unsigned char attempts;
    unsigned int key = 1234;
    unsigned int pass;

    IR_INIT();
    UART0_INIT();
    LCD_INIT();
	SERVO_INIT();

	SERVO_CLOSE();

    while(1)
    {
        while(object_detected == 0);

        // Vehicle detection status
        LCD_COMMAND(0x01);
        LCD_COMMAND(0x80);
        LCD_STRING("Vehicle Detected");

        delay_ms(2000);

        // Payment information
        LCD_COMMAND(0x01);
        LCD_COMMAND(0x80);
        LCD_STRING("Pay Toll");

        LCD_COMMAND(0xC0);
        LCD_STRING("Amount: Rs. 50");

        UART0_STR("---Pay The Toll---\r\n");
        UART0_STR("Amount = Rs. 50\r\n");

        delay_ms(2000);

        // Initialize authorization process
        auth = 0;
        attempts = 0;

        // Maximum three attempts
        while(auth == 0 && attempts < 3)
        {
            UART0_RX();

            if(validation == 1)
            {
                pass = UART0_INTEGER(digits);

                if(pass == key)
                {
                    auth = 1;

                    UART0_STR("Payment Verified!\r\n");

                    LCD_COMMAND(0x01);
                    LCD_COMMAND(0x80);
                    LCD_STRING("Payment Verified");
                }
                else
                {
                    attempts++;

                    if(attempts < 3)
                    {
                        LCD_COMMAND(0x01);
                        LCD_COMMAND(0x80);
                        LCD_STRING("Wrong Key!");

                        LCD_COMMAND(0xC0);
                        LCD_STRING("Try Again");

                        UART0_STR("Wrong Key! Try Again.\r\n");
                    }
                }
            }
            else
            {
                attempts++;

                if(attempts < 3)
                {
                    LCD_COMMAND(0x01);
                    LCD_COMMAND(0x80);
                    LCD_STRING("Invalid Input!");

                    LCD_COMMAND(0xC0);
                    LCD_STRING("Try Again");

                    UART0_STR("Invalid Input! Try Again.\r\n");
                }
            }
        }

        // Authorization result
        if(auth == 1)
        {
            // OPEN TOLL GATE
    		SERVO_OPEN();
			LCD_COMMAND(0x01);
			LCD_COMMAND(0x80);
    		LCD_STRING("Gate Open");

    		UART0_STR("Gate Opened!\r\n");

    		// Keep gate open for 5 seconds
   			delay_ms(5000);

    		// CLOSE TOLL GATE
   	 		SERVO_CLOSE();

    		LCD_COMMAND(0x01);
    		LCD_COMMAND(0x80);
    		LCD_STRING("Gate Closed");

    		UART0_STR("Gate Closed!\r\n");

    		delay_ms(1000);
            object_detected = 0;
        }
        else
        {
            LCD_COMMAND(0x01);
            LCD_COMMAND(0x80);
            LCD_STRING("Access Denied");

            LCD_COMMAND(0xC0);
            LCD_STRING("Call Operator");

            UART0_STR("Maximum attempts reached.\r\n");

            object_detected = 0;
        }
    }
}

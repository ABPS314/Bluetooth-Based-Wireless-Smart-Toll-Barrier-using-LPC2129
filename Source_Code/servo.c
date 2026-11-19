#include"servo.h"

void SERVO_INIT(void)
{
    PINSEL1 = (PINSEL1 & ~(3U << 10)) | (1U << 10);

    PWMTCR = 0x02;

    PWMPR = 14;

    PWMMR0 = 19999;
    PWMMR5 = 1500;

    PWMMCR = 0x02;
    PWMPCR = 0x2000;

    PWMLER = 0x21;

    PWMTCR = 0x09;
}

void SERVO_OPEN(void)
{
    PWMMR5 = 1999;
    PWMLER = 0x20;
}

void SERVO_CLOSE(void)
{
    PWMMR5 = 999;
    PWMLER = 0x20;
}

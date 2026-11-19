#include"ir_sensor.h"
extern volatile unsigned char object_detected;

void IR_INTERRUPT(void)__irq
{
	EXTINT=0X01;
	object_detected=1;
	VICVectAddr=0;
}

void IR_INIT(void)
{
	PINSEL1&=~(3<<0);
	PINSEL1|=(1<<0);
	VICIntSelect=0x00;
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(int)IR_INTERRUPT;
	EXTMODE=0X01;
	EXTPOLAR=0X00;
	EXTINT=0X01;
	VICIntEnable=(1<<14);
}

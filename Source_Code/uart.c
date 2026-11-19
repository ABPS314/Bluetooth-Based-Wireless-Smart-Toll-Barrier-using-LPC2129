#include"uart.h"
unsigned char digits[5];
unsigned char validation;

void UART0_INIT(void)
{
	PINSEL0=0x05;
	U0LCR=0X83;
	U0DLL=97;
	U0LCR=0X03;
}

void UART0_TX(unsigned char ch)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=ch;
}

void UART0_STR(const char *str)
{
	while(*str)
	{
		UART0_TX(*str++);
	}
}

void UART0_RX(void)
{
	unsigned char ch;
	unsigned int i=0;
	validation =1;
	for(i=0;i<4;i++)
	{
		while((U0LSR&1)==0);
		ch=U0RBR;
		if(ch>='0' && ch<='9')
		{
			digits[i]=ch;
		}
		else
			validation =0;
	}
	digits[4]='\0';
	
}

unsigned int UART0_INTEGER(const unsigned char *d)
{
	unsigned int i;
	unsigned int pass=0;
	for(i=0;i<4;i++)
	{
		pass=pass*10+((*d)-'0');
		d++;
	}
	return pass;
}

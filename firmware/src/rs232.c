/*
 * rs232.c
 *
 * Created: 29.11.2012 23:01:08
 *  Author: Bernhard
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>

#include "rs232.h"


//Struktur des RingBuffers
typedef struct stRingBuffer{
	char cBuf[RX_BUFFER_SIZE];
	char *pcWrite;
	char *pcRead;
	uint8_t uiUsedWords;
	unsigned int bWpOverflow:1;
	unsigned int bRpOverflow:1;
}stRingBuffer;

stRingBuffer rs232_stRingBuffer;



/************************************************************************/
/*    PROTOTYPES                                                        */
/************************************************************************/
void rs232_init()
{
		
	uint8_t t;
	t=UDR1; //RX-Buffer löschen
	UBRR1 = 25; //@115200BAUD
	//UBRR1   = 51; //19200 baud
	UCSR1A |= (DOUBLE_SPEED << U2X1);
	UCSR1B |= ((1<<RXCIE1)|(0<<TXCIE1)|(0<<UDRIE1)|(1<<RXEN1)|(1<<TXEN1)|(0<<UCSZ12));
	UCSR1C |= ((SYNCRONOUS<<UMSEL10)|(PARITY<<UPM11)|(PARTIY_ODD<<UPM10)|(SECOND_STOPBIT<<USBS1)
			  |(1<<UCSZ11)|(1<<UCSZ10)|(FALLING_SYNC<<UCPOL1));
				  
	
	DDRD |= (1<<PIND3);
	//Init Ringbuffer
	rs232_stRingBuffer.uiUsedWords = 0;
	rs232_stRingBuffer.bRpOverflow = 0;
	rs232_stRingBuffer.bWpOverflow = 0;
	rs232_stRingBuffer.pcRead  = &rs232_stRingBuffer.cBuf[0];
	rs232_stRingBuffer.pcWrite = &rs232_stRingBuffer.cBuf[1];	
}


void rs232_putC(char c)
{
	while(!(UCSR1A & (1<<5)));
	UDR1=c;
}

void rs232_print(unsigned char *s,uint8_t len)
{
	for(uint8_t i = 0; i<len;i++)
	{
		rs232_putC(*s);
		s++;
	}
}



// Absenden eines Strings über RS232
void rs232_printf(char *s)
{
	while(*s!=0)
	{
		rs232_putC(*s);
		s++;
	}
}

//Zeichen aus dem Buffer lesen
char rs232_getC(void)
{
	char c;
	//check position of read pointer
	if ((rs232_stRingBuffer.pcWrite > rs232_stRingBuffer.pcRead)||(rs232_stRingBuffer.bRpOverflow != rs232_stRingBuffer.bWpOverflow))
	{
		c= *rs232_stRingBuffer.pcRead;
		rs232_stRingBuffer.uiUsedWords --;  //decrement word counter
		
		if (rs232_stRingBuffer.pcRead == &rs232_stRingBuffer.cBuf[RX_BUFFER_SIZE])
		{
			rs232_stRingBuffer.pcRead = &rs232_stRingBuffer.cBuf[0];
			rs232_stRingBuffer.bWpOverflow = ~rs232_stRingBuffer.bRpOverflow;
		}
		else
		{
			rs232_stRingBuffer.pcRead++;
		}	
		return c;
	}
	return -1;		
}


//Zeichenkette aus dem Buffer lesen
uint8_t rs232_readBuffer(char *dest, uint8_t len)
{
	if (len <= (RX_BUFFER_SIZE - rs232_stRingBuffer.uiUsedWords))
	{
		uint8_t count= 0;
		do 
		{
			*dest = rs232_getC();
			dest++;
		} while (count < len);	
	}
	
	return 0;
}


/************************************************************************/
/*     Interrupt Standard Routines                                      */
/************************************************************************/
//TEST ISR

ISR(USART1_RX_vect)
{
	char buf;
	buf = UDR1;
	rs232_putC(buf);
}

/*
ISR(USART1_RX_vect)
{
	//check position of writePointer
	if ((rs232_stRingBuffer.pcWrite < rs232_stRingBuffer.pcRead)||(rs232_stRingBuffer.bRpOverflow == rs232_stRingBuffer.bWpOverflow))
	{
		*rs232_stRingBuffer.pcWrite = UDR1; //write into buffer
		rs232_stRingBuffer.uiUsedWords ++;  //increment word counter
		
		if (rs232_stRingBuffer.pcWrite == &rs232_stRingBuffer.cBuf[RX_BUFFER_SIZE]) //check buffer overflow
		{
			rs232_stRingBuffer.pcWrite = &rs232_stRingBuffer.cBuf[0];
			rs232_stRingBuffer.bWpOverflow = ~rs232_stRingBuffer.bWpOverflow;
		}
		else
		{
			rs232_stRingBuffer.pcWrite++;
		}
	}
	else rs232_printf("\n\rNAK");		
}
*/

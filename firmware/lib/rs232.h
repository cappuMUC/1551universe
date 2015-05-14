/*
 * rs232.h
 *
 * Created: 29.11.2012 23:02:13
 *  Author: Bernhard
 */ 

/* Description
 *	Diese Bibliothek stellt die grundlegende Kommunikation über die
 *	serielle UART des Mikroprozessors her. Die Funktionen beschränken
 *	sich auf die rudimentäre Übertragung von einzelnen Zeichen oder
 *	Zeichenketten beliebiger Länge. Eingehende Zeichen werden in einen
 *	Ringpuffer geschrieben, welcher dann im Hauptprogramm gecheckt und
 *  ausgelesen werden kann.
 *
 */

/* TODO
 *	Auswahl der Anzahl der zu Übertragenden Bits pro Frame.
 *
 *
 */

#ifndef RS232_H_
#define RS232_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/
#include <avr/io.h>
/************************************************************************/
/* DEFINES                                                              */
/************************************************************************/
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define BAUD 9600 
#define PARITY 0
#define PARTIY_ODD 0
#define SECOND_STOPBIT 0
#define DOUBLE_SPEED 0
#define SYNCRONOUS 0
#define FALLING_SYNC 0

#define RX_BUFFER_SIZE 32

/************************************************************************/
/* GLOBAL VARIABLES                                                     */
/************************************************************************/
/************************************************************************/
/* PROTOTYPES                                                           */
/************************************************************************/

//Initialisiert die serielle Schnittstelle (TODO Baudrate wählbar?!)
void rs232_init(void);

//Funktionen zum Senden
//**********************************************
//Sendet ein einzelnes Byte
void rs232_putC(char c);

//Sendet ein einzelnes Word (16Bit)
void rs232_putW(uint16_t WORD);

//Sendet eine Zeichenkette von bestimmter Länge
void rs232_print(unsigned char *s, uint8_t len);

//Sendet einen String
void rs232_printf(char *s);

//Funktionen zum Empfangen
//**********************************************
uint8_t rs232_checkBuffer(void);
char rs232_getC(void);
uint8_t rs232_readBuffer(char *dest, uint8_t len);

#endif /* RS232_H_ */

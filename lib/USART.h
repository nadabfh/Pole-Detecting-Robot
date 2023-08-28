#ifndef USART_H
#define USART_H
#include <avr/io.h> 

void initialisationUart();
void transmissionUart (uint8_t donnee);
void transmissionUart (const char* chaine);
uint8_t receptionUart();

#endif
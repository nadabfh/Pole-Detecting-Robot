/*Programme qui initialise l’UART avant la transmission d’informations pour permettre la communication avec
 l’ordinateur à 2400 bauds et qui active RX (réception) et TX(transmission),
 et défini le format des trames de données pour 8bits, 1 bit d’arrêt et sans parité.
 * 
 * Fichier : USART.cpp
 * Auteur  : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date    : 13 mars 2023
 */


#include "USART.h"
#include <avr/io.h>
#include <string.h>

void initialisationUart() {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    
    UCSR0A |= (1 << RXC0) | (1 << TXC0);
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C |= (1 << USBS0) | (3 << UCSZ00);
}

void transmissionUart ( uint8_t donnee ) {
    while (!( UCSR0A & (1<<UDRE0))) {};
    UDR0 = donnee;
}

void transmissionUart(const char* chaine) {
    uint8_t longueur = strlen(chaine);
    for (uint8_t i = 0; i < longueur; ++i) 
        transmissionUart(chaine[i]);
}

uint8_t receptionUart() {
    while (!(UCSR0A & (1 << RXC0))) {};
    return UDR0;
}
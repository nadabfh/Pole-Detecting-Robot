/*
 * Ce programme contient les fonctions pour jouer des notes musicales en utilisant le piezo connecté à un microcontrôleur AVR.
 * Les fonctions incluent :
 * 1. joueNote : Joue une note donnée en utilisant le timer/counter du microcontrôleur.
 * 2. arreterJouer : Arrête de jouer la note actuelle.

 * Fichier : son.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 20 Avril 2023
 */
#include "son.h"
#include <avr/io.h>

Musique::Musique() 
{
    DDRB |= (1 << PB3) | (1 << PB5);
}

void Musique::jouerNote(uint8_t note) 
{
    
   if ( (note >= 45) && (note <= 81) )
    {   
        double frequence = notes[note - 45];
        double periode = F_CPU / frequence / 2 / 256;
        OCR0A = periode;
        PORTB &= ~(1 << PB5);

        TCCR0A |= (1 << WGM01) | (1 << COM0A0);
        TCCR0A &= ~(1 << COM0A1);
        TCCR0B = (1 << CS02);
    }
}

void Musique::arreterJouer() 
{
    TCCR0A = 0;
}
/*
 * Ce fichier implémente les fonctions nécessaires pour la détection des poteaux par le robot.
Le robot utilise des capteurs pour détecter les poteaux et enregistrer leurs positions.
Les fonctions incluent la détection des poteaux, l'enregistrement de leurs positions,
et la gestion des différents modes de fonctionnement du robot
 * Fichier : main.cpp
 * Auteur  : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date    : 20 mars 2023
 */

#include "modes.h"
#include "USART.h"
#include <stdio.h>
#include "position.h"
#include "detectionPoteau.h"
//INT1 bouton blanc = Transmission
//INT0 bouton intEn = Détection

DetectionPoteau objetDetection ;


volatile uint8_t gIntEn = 0;
volatile uint8_t gBlanc = 0;

void initialiserPort(){

    DDRB |= (1 << PORTB0) | (1 << PORTB1);
    DDRD |= (1<<PORTD0) | (1<<PORTD1) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
}

void initialisation ( void ) {
    cli ();
    initialiserPort();
    EIMSK |= (1 << INT0) | (1 << INT1);
    EICRA |= (1 << ISC01) | (1 << ISC00) ; 
    sei ();

    initialisationUart();
}
ISR ( INT0_vect ) {
    
    _delay_ms ( anti_rebond );
    gIntEn = 1;
}

ISR ( INT1_vect ) {
    
    _delay_ms ( anti_rebond );
    gBlanc = 1;
}

int main() {
    initialisation();
    //initialisationUart();
    bool robotTourne = true;
    bool detectionCommence = false;
    bool premiereEcriture = false;
    bool premiereAmbre = false;
    Del delUse = Del(PORTB);

    while (robotTourne){
        while ((gIntEn > 0) || (detectionCommence == true) ) {
            
            gIntEn = 0;
            gBlanc = 0;

            while ( (gIntEn <= 0) && (gBlanc <= 0) ){
                menu(Modes::DETECTION, premiereAmbre);
            }

            Sens orienteChoisi = Sens::HAUT;
            
            if (gIntEn > 0) {
                orienteChoisi = Sens::HAUT;
                delUse.allumerDel(Couleur::VERT);
                _delay_ms(2000);
                delUse.allumerDel(Couleur::ETEINT);
                
            } else if (gBlanc > 0) {
                orienteChoisi = Sens::DROITE;
                delUse.allumerDel(Couleur::ROUGE);
                _delay_ms(2000);
                delUse.allumerDel(Couleur::ETEINT);
            }

            if (premiereEcriture == false){
                objetDetection.premiereEcriture();
                premiereEcriture = true;
            }
            
            objetDetection.detection(orienteChoisi);

            gIntEn++;
            detectionCommence = true;

            if (objetDetection.aucunPoteau == true){
                robotTourne = false;
                detectionCommence = false;
                gIntEn = 0;
            }

        }  
        if (gBlanc > 0) {
            menu(Modes::TRANSMISSION, premiereAmbre);
        }
    
    
    }
}
    
#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include "can.h"
#include "pwm.h"
#include "del.h"
#include "son.h"
#include "memoire_24.h"
#include "moteur.h"
#include "USART.h"
#include <util/delay.h>
#include "position.h"
#include <stdio.h>


/*
bool tourneDroite = true;
bool estDectecte = false;
uint8_t duree = 0;
uint8_t premiereIntensite ;
uint16_t angle;
bool deja_bouge = false;
*/
const static uint8_t INTENSITE_CHERCHER = 15;
const static uint8_t INTENSITE_ARRET = 70;
const static uint8_t DECALAGE = 2;
const static uint8_t DELAI_ECRITURE = 5;
const static uint16_t DELAI_ARRET = 650;
const uint8_t PIN_DROITE = PD7;
const uint8_t PIN_GAUCHE = PD6;
const uint16_t adresseNbrePoteaux = 0x0000;

enum class EtatRobot {CHERCHER, SUIVRE, FIN, RIEN};


class DetectionPoteau {
public:
    DetectionPoteau() = default ;

    uint16_t adresse = 0x0000 ;
    uint8_t nPoteau = 0x00 ;
    bool aucunPoteau = false;
    Position pos ;

    void premiereEcriture();
    void detection(Sens orientation);


};
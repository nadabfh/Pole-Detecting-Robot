/*
 * Fonctions d'initialisation et d'ajustement du timer1 en mode PWM
 * Fichier : pwm.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 13 mars 2023
 */

#include "pwm.h"
#include <avr/io.h>

void initialisationPwm() {
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
  TCCR1B |= (1 << CS11);
  TCCR1C = 0;
}

void ajusterPwm(double ratioA, double ratioB) {
  OCR1A = ratioA / 100.0 * UINT8_MAX;
  OCR1B = ratioB / 100.0 * UINT8_MAX;
}
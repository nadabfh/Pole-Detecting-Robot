/*Programme qui permet de configurer un TIMER en choisissant son numéro parmi
les options disponibles (0, 1 ou 2). À partir de ces choix, les registres de la minuterie
 correspondante sont configurés grâce à un switch/case.
 * Fichier : configuration.cpp
 * Auteur  : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date    : 13 mars 2023
 */

#include <configuration.h>

void Configuration::partirMinuterie (uint16_t duree, uint8_t gMinuterieExpiree, uint8_t numeroMinuterie) {
  switch (numeroMinuterie){
    case 0:
      TCNT0 = 0;
      OCR0A = duree;
      TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
      TCCR0B |= (1 << CS02) | (1 << CS10);
      TCCR0B &= ~(1 << CS01);
      TCCR1C = 0;
      TIMSK0 |= (1 << OCIE0A);
      break;
    case 1:
      TCNT1 = 0;
      OCR1A = duree;
      TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
      TCCR1B |= (1 << CS12) | (1 << CS10);
      TCCR1B &= ~(1 << CS11);
      TCCR1C = 0;
      TIMSK1 |= (1 << OCIE1A);
      break;
    case 2:
      TCNT2 = 0;
      OCR2A = duree;
      TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
      TCCR2B |= (1 << CS22) | (1 << CS20);
      TCCR2B &= ~(1 << CS21);
      TCCR1C = 0;
      TIMSK2 |= (1 << OCIE2A);
      break;
  }
}